""" Harvest the Arduino CLI for compilation arguments.

This script harvests the command line arguments, compiler/linker commands, and built archive from a build of a test INO
file in Arduino.  This allows the program to know how arduino should compile C and C++ files.

@author lestarch
"""
import argparse
import itertools
import os
import re
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


def get_path_from_flagged(item: str) -> Path:
    """ Flag and path item to path """
    if item.startswith("-"):
        try:
            return Path(item[item.index("=") +1:])
        except ValueError:
            return Path(item[2:])
    return Path(item)

def make_sketch(directory: Path, libraries: List[str]) -> Dict[str, Path]:
    """Create a sketch folder with at least a C, C++, and assembly file

    Arduino must compile sketches and in order to determine the necessary compilation information we must create a
    sketch that uses each of these constructs for compilation. This function will generate a sketch using these
    constructs and return the mapping of the type extension (c, cpp, S) to the path to that created file

    Args:
        directory: directory to create the sketch within
        libraries: list of libraries to include in the sketch

    Returns:
        mapping between file extension string and temporary file
    """
    libraries = libraries if libraries else []
    mappings = {extension: directory / f"special_input_file.{ extension }" for extension in ["S", "c", "cpp"]}
    for _, path in mappings.items():
        path.touch()
    # Create main sketch as an ino file such that it is a valid sketch
    with open((directory / f"{ directory.name }.ino"), "w") as file_handle:
        include_set = "\n".join(f"#include <{library}.h>" for library in libraries)
        file_handle.write(include_set + "\nvoid setup() {}\nvoid loop() {}")
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


def parse_archive_commands(output_lines: List[str], token: str, removal_count: int) -> Tuple[str, List[str]]:
    """Parse compilation commands and flags per type

    This function will parse out each command needed to construct each .a archive. These
    commands are parsed in the section after the "Compiling core..." message

    Args:
        output_lines: lines of the output of arduino-cli
        token: ar or ranlib to search for
        removal_count: count of items to strip off end

    Return:
        tuple of ar commands and args or ranlib and args
    """
    archive_lines = lines_between(output_lines, "Compiling core...", "Linking everything together...")
    shell_splits = [shlex.split(line) for line in archive_lines]
    shell_splits = [splits for splits in shell_splits if (splits + [""])[0].endswith(token)]
    if not shell_splits:
        return "", [""]
    shell_split = shell_splits[0]
    return shell_split[0], shell_split[1:(-1 * removal_count)]


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


def linker_cli_tokens(output_lines: List[str]):
    """ Return the linker command line tokens """
    # Find lines that match the linking call
    linking_lines = lines_between(output_lines, "Linking everything together...")
    linking_lines = [linking_line for linking_line in linking_lines if "core.a" in linking_line]
    if not linking_lines:
        raise Exception(f"Failed to find linking lines")
    linker_shell_split = shlex.split(linking_lines[0])
    return linker_shell_split


def parse_include_directories(output_lines: List[str]):
    """ Parse all include directories """
    shell_split = [shlex.split(line) for line in output_lines]
    return [item[2:] for item in itertools.chain.from_iterable(shell_split) if item.startswith("-I")]

def parse_prebuild_code(output_lines: List[str], sketch_name: str):
    """ Parse prebuilt code from arduino cli """
    linker_shell_split = linker_cli_tokens(output_lines)
    # Figure out the path to the core library
    core_library = filter(lambda item: item.endswith("core.a"), linker_shell_split)
    if not core_library:
        raise Exception(f"Failed to find core.a in linking line")
    core_path = Path(list(core_library)[0])
    core_library_code = filter(lambda item: ".o" in item and not sketch_name in item, linker_shell_split)
    return [core_path] + [Path(obj) for obj in core_library_code]


def parse_linker_commands(output_lines: List[str], output_directory: Path) -> List[str]:
    """Parse out the linker and post-linker commands

    This function will parse out the linker command as well as the post linker command steps. These can then be used to
    construct the necessary build steps to replace arduino-cli.

    Args:
        output_lines: lines from arduino CLI
        sketch_name: name of sketch
    Return:
        List of post linker commands filtered for input / outputs
    """
    regex = re.compile(rf"{os.sep}.*{os.sep}arduino-sketch[^{os.sep}]*{os.sep}")
    linker_shell_split = linker_cli_tokens(output_lines)
    def filter_function(item: str) -> bool:
        """Filters out -o flag, input and output specifiers"""
        return (
            item != "-o"
            and not item.endswith("ino.elf")
            and not ".o" in item
            and not item.endswith("core.a")
            and not item.startswith("-L")
        )
    necessary_command_values = filter(filter_function, linker_shell_split)
    rewritten_values = [regex.sub(str(output_directory) + os.sep, value) for value in necessary_command_values]
    return rewritten_values


def parse_finalization_commands(output_lines: List[str]):
    """Parse out the finalization steps of the build process

    This function will parse matching commands after the linker step such that they can be replayed.

    Args:
        output_lines: lines from arduino CLI
    Return:
        List of post linker commands filtered for input / outputs
    """
    reg = re.compile(r".*\.ino(\.elf)?")
    excludes = ["g++", "gcc", "ld"]  # Keep objcopy and size tokens
    # Find lines that match the linking call
    post_linking_lines = lines_between(output_lines, "Linking everything together...")
    # Find lines where the list of matches on that line across possible tokens is a non-empty list
    post_linking_lines = [line for line in post_linking_lines if [token for token in excludes if token not in line]]
    if not post_linking_lines:
        return []  # No follow-up lines
    post_shell_split_sets = [shlex.split(line) for line in post_linking_lines]
    post_shell_split_sets = [split for split in post_shell_split_sets if Path((split + [""])[0]).is_file()]
    post_shell_split_sets = [split_set for split_set in post_shell_split_sets if split_set]
    post_shell_split_sets = [[reg.sub("<INPUT>", item) for item in split_set] for split_set in post_shell_split_sets]
    return post_shell_split_sets


def detect_copy_files(output_lines: List[str], names: List[str]):
    """ All copy files """
    shell_split = [shlex.split(line) for line in output_lines]
    copies =  [item for item in itertools.chain.from_iterable(shell_split) if Path(item).name in names]
    return [get_path_from_flagged(item) for item in copies]


def detect_build_settings(output_lines: List[str], mappings: Dict[str, Path], output_directory:Path):
    """ Detect the build settings """
    command_mappings = parse_compilation_commands(output_lines, mappings)
    linker_args = parse_linker_commands(output_lines, output_directory)
    ar, ar_args = parse_archive_commands(output_lines, "ar", 2)
    ranlib, ranlib_args = parse_archive_commands(output_lines, "ranlib", 1)
    post_commands = parse_finalization_commands(output_lines)

    for output_type in ["S", "c", "cpp"]:
        print(command_mappings[output_type][0], end=";")
        print("|".join(command_mappings[output_type][1:]), end=";")
    print(ar, end=";")
    print("|".join(ar_args), end=";")
    print(ranlib, end=";")
    print("|".join(ranlib_args), end=";")
    print(linker_args[0], end=";")
    print("|".join(linker_args[1:]), end=";")
    for command in post_commands:
        print("|".join(command), end=";")

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
        "-d",
        "--detect-settings",
        action="store_true",
        help="Tell fprime-arduino to detect build settings",
        default=False,
    )
    parser.add_argument(
        "-g",
        "--generate-code",
        action="store_true",
        help="Tell fprime-arduino to build support code",
        default=False,
    )
    parser.add_argument(
        "-i",
        "--includes",
        action="store_true",
        help="Tell fprime-arduino to list include directories",
        default=False,
    )
    parser.add_argument(
        "-l",
        "--libraries",
        type=str,
        nargs="*",
        help="List of arduino libraries to use (e.g. Wire.h)",
        required=False,
    )
    parser.add_argument(
        "-c",
        "--copy",
        type=str,
        nargs="*",
        help="List of extra filenames to copy and remap to new directory in generate step",
        required=False,
    )
    parser.add_argument(
        "--properties",
        type=str,
        nargs="*",
        help="List of build properties to supply",
        required=False,
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
            mappings = make_sketch(directory, arguments.libraries)
            compile_output = compile_sketch(arguments.board, directory)

            output_lines = compile_output.split("\n")
            if arguments.detect_settings:
                detect_build_settings(output_lines, mappings, arguments.output)
            if arguments.includes:
                print(";".join(parse_include_directories(output_lines)), end="")
            if arguments.generate_code:
                code_units = parse_prebuild_code(output_lines, directory.name)
                arguments.output.mkdir(exist_ok=True)
                code_destinations = [arguments.output / unit.name for unit in code_units]
                copies = detect_copy_files(output_lines, arguments.copy) if arguments.copy else []
                copy_destinations = [arguments.output / copy.name for copy in copies]
                for unit, dest in list(zip(code_units, code_destinations)) + list(zip(copies, copy_destinations)):
                    shutil.copy2(unit, dest)
                print(";".join([str(dest) for dest in code_destinations]), end="")
        except Exception as exc:
            print(f"[ERROR] Problem occurred while mining Arduino. {exc}", file=sys.stderr)
            raise
            return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
