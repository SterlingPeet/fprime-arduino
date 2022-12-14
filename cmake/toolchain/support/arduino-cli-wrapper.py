""" Harvest the Arduino CLI for compilation arguments.

This script harvests the command line arguments, compiler/linker commands, and built archive from a build of a test INO
file in Arduino.  This allows the program to know how arduino should compile C and C++ files.

@author lestarch
"""
import argparse
import shlex
import shutil
import subprocess
import sys
import tempfile

from pathlib import Path
from typing import Dict, List, Tuple


HELP_TEXT = """Tool used to parse settings from a compilation run of Arduino CLI.

This tool will run a test compilation 
"""


def make_sketch(directory: Path) -> Dict[str, Path]:
    """Create a sketch folder with at least a C, C++, and assembly file

    Arduino must compile sketches and in order to determine the necessary compilation information we must create a
    sketch that uses each of these constructs for compilation. This function will generate a sketch using these
    constructs and return the mapping of the type extension (c, cpp, S) to the path to that created file

    Args:
        directory: directory to create the sketch within

    Returns:
        mapping between file extension string and temporary file
    """
    mappings = {extension: directory / f"special_input_file.{ extension }" for extension in ["S", "c", "cpp"]}
    for _, path in mappings.items():
        path.touch()
    # Create main sketch as an ino file such that it is a valid sketch
    with open((directory / f"{ directory.name }.ino"), "w") as file_handle:
        file_handle.write("#include <Wire.h>\nvoid setup() {}\nvoid loop() {}")
    return mappings


def compile_sketch(board: str, directory: Path) -> str:
    """Compile the sketch to product core and output text.

    This will compile a sketch directory and produce the necessary core archive and output text. This information is
    created with the --clean flag to prevent cross-talk from any other builds. The board to compile against is passed in
    along with the directory containing the sketch. In order to capture all necessary information this command is run
    in verbose mode.

    Args:
        directory: sketch directory to compile
        board: compile board target FQBN

    Returns:
        standard out of the compiled sketch run
    """
    process_return = subprocess.run(
        ["arduino-cli", "compile", "-v", "--clean", "-b", board, str(directory)],
        check=True,
        text=True,
        stdout=subprocess.PIPE,
    )
    return process_return.stdout


def lines_between(output_lines: List[str], start_phrase: str, end_phrase: str = None) -> List[str]:
    """Subset the supplied lines into those between start_phrase and end_phrase

    This function will return the subset of the input lines between start_phrase and end_phrase. These lines are
    non-inclusive not containing either the start or end phrase.

    Args:
        output_lines: lines to subset
        start_phrase: start string
        end_phrase: end string
    Returns:
        List of lines between start and end strings
    """
    start_index = output_lines.index(start_phrase)
    stop_index = -1 if end_phrase is None else output_lines.index(end_phrase)
    return output_lines[(start_index + 1) : stop_index]


def parse_compilation_commands(output_lines: List[str], mapping: Dict[str, Path]) -> Dict[str, List[str]]:
    """Parse compilation commands and flags per type

    This function will parse out each command needed to compile each of the types specified in the mapping object. These
    commands are parsed in the section after the "Compiling sketch..." message

    Args:
        output_lines: lines of the output of arduino-cli
        mapping: mapping of type to path to object

    Return:
        mapping of type (cpp, c, S) to a list of needed command lines (command, flags)
    """
    output_mapping = {}
    compilation_lines = lines_between(output_lines, "Compiling sketch...", "Compiling libraries...")

    for file_type, path in mapping.items():
        filename = path.name
        matching_lines = filter(
            lambda compilation_line: f"{ filename }.o" in compilation_line,
            compilation_lines,
        )
        if not matching_lines:
            raise Exception(f"Failed to find compilation line for { filename }")
        shell_split = shlex.split(list(matching_lines)[0])

        def filter_function(item: str) -> bool:
            """Filters out -o flag, input and output specifiers"""
            return item != "-o" and not item.endswith(filename) and not item.endswith(f"{ filename }.o") and item != "-c"

        necessary_command_values = list(filter(filter_function, shell_split))
        expected_command_values = shell_split[:1] + shell_split[2:-3]
        assert (
            necessary_command_values == expected_command_values
        ), f"Necessary arguments are usually all but the last 3:\n\t{necessary_command_values}\n\t{expected_command_values}"
        output_mapping[file_type] = necessary_command_values
    return output_mapping


def parse_linker_commands(output_lines: List[str]):
    """Parse out the linker and post-linker commands

    This function will parse out the linker command as well as the post linker command steps. These can then be used to
    construct the necessary build steps to replace arduino-cli.

    Args:
        output_lines: lines from arduino CLI
    Return:
        List of post linker commands filtered for input / outputs
    """
    # Find lines that match the linking call
    linking_lines = lines_between(output_lines, "Linking everything together...")
    if not linking_lines:
        raise Exception(f"Failed to find linking lines")
    linker_shell_split = shlex.split(linking_lines[0])
    # Figure out the path to the core library
    core_library = filter(lambda item: item.endswith("core.a"), linker_shell_split)
    if not core_library:
        raise Exception(f"Failed to find core in linking line")
    core_path = Path(list(core_library)[0])

    def filter_function(item: str) -> bool:
        """Filters out -o flag, input and output specifiers"""
        return (
            item != "-o"
            and not item.endswith("ino.elf")
            and not item.endswith(".o")
            and not item.endswith("core.a")
            and not item.endswith(str(core_path.parent.parent))
        )

    necessary_command_values = list(filter(filter_function, linker_shell_split))
    return core_path, necessary_command_values


def parse_finalization_commands(output_lines: List[str]):
    """Parse out the finalization steps of the build process

    This function will parse matching commands after the linker step such that they can be replayed.

    Args:
        output_lines: lines from arduino CLI
    Return:
        List of post linker commands filtered for input / outputs
    """
    matching_tokens = ["objcopy", "size"]  # Keep objcopy and size tokens
    # Find lines that match the linking call
    post_linking_lines = lines_between(output_lines, "Linking everything together...")
    # Find lines where the list of matches on that line across possible tokens is a non-empty list
    post_linking_lines = [line for line in post_linking_lines if [token for token in matching_tokens if token in line]]
    if not post_linking_lines:
        return []  # No follow-up lines
    post_shell_split_sets = [shlex.split(line) for line in post_linking_lines]
    post_shell_split_sets = [split_set for split_set in post_shell_split_sets if split_set]
    objcopy_sets = [split_set for split_set in post_shell_split_sets if "objcopy" in split_set[0]]
    objcopy_sets = [set[:-2] + ["<INPUT>", f"<INPUT>{Path(set[-1]).suffix}"] for set in objcopy_sets]

    size_sets = [split_set[:-1] + ["<INPUT>"] for split_set in post_shell_split_sets if "size" in split_set[0]]
    return objcopy_sets + size_sets

def parse_arguments(arguments: List[str]) -> argparse.Namespace:
    """Parse input arguments to influence the execution.

    The script needs to know where to copy the core library into the build system. Additionally, the board target is
    needed in order to properly compile. These settings are parsed out of the command line input arguments using the
    argparse module.

    Args:
        arguments: command line argument list to be parsed

    Returns:
        Namespace containing parsed arguments
    """
    parser = argparse.ArgumentParser(description=HELP_TEXT)
    parser.add_argument(
        "-b",
        "--board",
        type=str,
        help="Target board FQBN supplied to the arduino build",
        required=True,
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        help="Output destination for the pre-compiled arduino core",
        required=True,
    )
    return parser.parse_args(arguments)


def main(arguments: List[str]):
    """Perform entrypoint functions"""
    arguments = parse_arguments(arguments)

    with tempfile.TemporaryDirectory() as directory:
        try:
            directory = Path(directory)
            mappings = make_sketch(directory)
            compile_output = compile_sketch(arguments.board, directory)

            output_lines = compile_output.split("\n")
            command_mappings = parse_compilation_commands(output_lines, mappings)
            core_path, linker_args = parse_linker_commands(output_lines)
            post_commands = parse_finalization_commands(output_lines)

            core_destination = arguments.output / core_path.name
            shutil.copy2(core_path, core_destination)

            # Output destined for CMake
            print(str(core_destination), end=";")
            for output_type in ["S", "c", "cpp"]:
                print(command_mappings[output_type][0], end=";")
                print("|".join(command_mappings[output_type][1:]), end=";")
            print(linker_args[0], end=";")
            print("|".join(linker_args[1:]), end=";")
            for command in post_commands:
                print("|".join(command), end=";")
        except Exception as exc:
            print(f"[ERROR] Problem occurred while mining Arduino. {exc}", file=sys.stderr)
            return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
