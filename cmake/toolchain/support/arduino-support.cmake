####
# arduino-support.cmake:
#
# Support for arduino supported boards using the arduino-cli utility. Note: users must install boards, libraries, and
# cores through the arduino-cli utility in order to use those parts of arduino with this toolchain. Additionally, this
# toolchain provides for the following functions:
#
# - include_arduino_libraries: called to add arduino libraries into the toolchain. The user may use these libraries and
#     the final executable will be linked against these libraries.
# - finalize_arduino_executable: called on a deployment target to attach the arduino specific steps and libraries to it.
#
# @author lestarch
####
cmake_minimum_required(VERSION 3.16)
set(FPRIME_ARDUINO TRUE)
set(ARDUINO_WRAPPER_PATH "${CMAKE_CURRENT_LIST_DIR}/arduino-cli-wrapper.py")

####
# Function `run_arduino_wrapper`:
#
# Runs `arduino-cli` and forwards all supplied arguments to it. Output text will be set into the variable
# `WRAPPER_OUTPUT`.
#
# Args:
#   *: forwarded as CLI arguments to `arduino-cli`
#
# Returns: WRAPPER_OUTPUT containing standard-output of the `arduino-cli` run.
####
function(run_arduino_wrapper)
    find_program(PYTHON NAMES python3 python)
    if (NOT PYTHON)
        message(FATAL_ERROR "Python3 is required to be on path for arduino-support toolchain")
    elseif (NOT DEFINED ARDUINO_FQBN)
        message(FATAL_ERROR "Variable ARDUINO_FQDN must be set to use arduino-support")
    endif()
    set(EXECUTE_ARGS "${PYTHON}" "${ARDUINO_WRAPPER_PATH}" ${ARGN})
    if (CMAKE_DEBUG_OUTPUT)
        string(REPLACE ";" " " INVOCATION "${EXECUTE_ARGS}")
        message(STATUS "[arduino-cli] Invocation: ${INVOCATION}")
    endif()

    # Execute the python wrapper
    execute_process(COMMAND
            ${EXECUTE_ARGS}
        OUTPUT_VARIABLE WRAPPER_OUTPUT
        RESULT_VARIABLE RET_CODE
    )
    if (NOT RET_CODE EQUAL 0)
        message(FATAL_ERROR "Could not run 'arduino-cli' please install 'arduino-cli' and board '${ARDUINO_FQBN}'.")
    endif()
    set(WRAPPER_OUTPUT "${WRAPPER_OUTPUT}" PARENT_SCOPE)
endfunction(run_arduino_wrapper)

####
# Function `set_arduino_build_settings`:
#
# Detects compiler settings from `arduino-cli`. Compiles a test sketch in order to detect these settings. Sets necessary
# tool variables for CMake to run.
#
####
function(set_arduino_build_settings)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY PARENT_SCOPE)
    # Check if a file cache was created already: prescan (..), try-compile (../..), or prescan try-compile (../../..)
    if (EXISTS "${CMAKE_BINARY_DIR}/../arduino-cli-compiler-settings.txt")
        file(READ "${CMAKE_BINARY_DIR}/../arduino-cli-compiler-settings.txt" WRAPPER_OUTPUT)
    elseif (EXISTS "${CMAKE_BINARY_DIR}/../../arduino-cli-compiler-settings.txt")
        file(READ "${CMAKE_BINARY_DIR}/../../arduino-cli-compiler-settings.txt" WRAPPER_OUTPUT)
    elseif (EXISTS "${CMAKE_BINARY_DIR}/../../../arduino-cli-compiler-settings.txt")
        file(READ "${CMAKE_BINARY_DIR}/../../../arduino-cli-compiler-settings.txt" WRAPPER_OUTPUT)
    # Detect settings if these have not been detected before
    elseif(NOT DEFINED CMAKE_C_COMPILER)
        run_arduino_wrapper("--detect-settings" "-b" "${ARDUINO_FQBN}" "--properties" ${ARDUINO_BUILD_PROPERTIES})
        file(WRITE "${CMAKE_BINARY_DIR}/arduino-cli-compiler-settings.txt" "${WRAPPER_OUTPUT}")
    # Detect settings from file if they were already set
    else()
        file(READ "${CMAKE_BINARY_DIR}/arduino-cli-compiler-settings.txt" WRAPPER_OUTPUT)
    endif()
    # Read each bit of information from the output variable
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_ASM_COMPILER)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_ASM_FLAGS_INIT)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_C_COMPILER)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_C_FLAGS_INIT)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_CXX_COMPILER)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_CXX_FLAGS_INIT)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_AR)
    list(POP_FRONT WRAPPER_OUTPUT ARDUINO_AR_FLAGS)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_RANLIB)
    list(POP_FRONT WRAPPER_OUTPUT ARDUINO_RANLIB_FLAGS)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_LINKER)
    list(POP_FRONT WRAPPER_OUTPUT CMAKE_EXE_LINKER_FLAGS_INIT)
    set_property(GLOBAL PROPERTY ARDUINO_FINAL_COMMANDS "${WRAPPER_OUTPUT}")

    # Convert flag | separated lists to expected ' ' separated lists
    string(REPLACE "|" " " CMAKE_ASM_FLAGS_INIT "${CMAKE_ASM_FLAGS_INIT}")
    string(REPLACE "|" " " CMAKE_C_FLAGS_INIT   "${CMAKE_C_FLAGS_INIT}")
    string(REPLACE "|" " " CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
    string(REPLACE "|" " " ARDUINO_AR_FLAGS           "${ARDUINO_AR_FLAGS}")
    string(REPLACE "|" " " ARDUINO_RANLIB_FLAGS       "${ARDUINO_RANLIB_FLAGS}")
    string(REPLACE "|" " " CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT}")
    SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> ${ARDUINO_AR_FLAGS} <TARGET> <OBJECTS>")
    SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> ${ARDUINO_AR_FLAGS} <TARGET> <OBJECTS>")
    set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
    foreach(SETTING
        CMAKE_ASM_COMPILER CMAKE_ASM_FLAGS_INIT
        CMAKE_C_COMPILER CMAKE_C_FLAGS_INIT
        CMAKE_CXX_COMPILER CMAKE_CXX_FLAGS_INIT
        CMAKE_AR CMAKE_C_ARCHIVE_CREATE CMAKE_CXX_ARCHIVE_CREATE
        CMAKE_RANLIB
        CMAKE_LINKER CMAKE_EXE_LINKER_FLAGS_INIT CMAKE_CXX_LINK_EXECUTABLE
    )
        set(${SETTING} "${${SETTING}}" PARENT_SCOPE)
    endforeach()
endfunction(set_arduino_build_settings)

# Setup the arduino build settings, and output when debugging
set_arduino_build_settings()
if (CMAKE_DEBUG_OUTPUT)
    message(STATUS "[arduino-support] Detected ASM  settings: ${CMAKE_ASM_COMPILER} ${CMAKE_ASM_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected C    settings: ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected C++  settings: ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected AR   settings: ${CMAKE_AR} ${ARDUINO_AR_FLAGS}")
    message(STATUS "[arduino-support] Detected link settings: ${CMAKE_LINKER} ${CMAKE_EXE_LINKER_FLAGS_INIT}")
endif()

####
# Function `setup_arduino_libraries`:
#
# Helper function to build arduino libraries and core libraries for use in linking
####
function(setup_arduino_libraries)
    if (FPRIME_PRESCAN)
        return()
    endif()
    get_property(ARDUINO_LIBRARY_LIST_LOCAL GLOBAL PROPERTY ARDUINO_LIBRARY_LIST)
    run_arduino_wrapper("--generate-code" "-b" "${ARDUINO_FQBN}" "-o" "${CMAKE_BINARY_DIR}/arduino-cli-core" "-g" "--libraries" ${ARDUINO_LIBRARY_LIST_LOCAL})
    list(POP_FRONT WRAPPER_OUTPUT CORE_LIBRARY)

    link_libraries("${CORE_LIBRARY}")

    # Setup an extra arduino libraries object
    add_library(arduino_libraries_objects OBJECT IMPORTED GLOBAL)
    set_target_properties(arduino_libraries_objects PROPERTIES IMPORTED_OBJECTS "${WRAPPER_OUTPUT}")
    target_link_libraries(arduino_libraries_objects INTERFACE "${CORE_LIBRARY}")

    # Make each arduino interface library dependent on the common arduino setup
    foreach(LIBRARY IN LISTS ARDUINO_LIBRARY_LIST_LOCAL)
        target_link_libraries("${LIBRARY}" INTERFACE arduino_libraries_objects ${CORE_LIBRARY})
    endforeach()
endfunction(setup_arduino_libraries)

####
# Function `include_arduino_libraries`:
#
# Uses `arduino-cli` to detect include paths for libraries supplied to this call. Allows these libraries to be used by
# adding a dependency to the library's name.
#
# Args:
#   *: list of arduino library name without spaces (e.g. Wire or Adafruit_LSM6DS). Must be install via `arduino-cli`.
#####
function(include_arduino_libraries)
    if (FPRIME_PRESCAN)
        return()
    endif()
    get_property(ARDUINO_LIBRARY_LIST_LOCAL GLOBAL PROPERTY ARDUINO_LIBRARY_LIST)
    # Filter list to new libraries
    foreach(LIBRARY IN LISTS ARGN)
        if (NOT LIBRARY IN_LIST ARDUINO_LIBRARY_LIST_LOCAL)
            list(APPEND NEW_ARDUINO_LIBRARIES "${LIBRARY}")
        endif()
    endforeach()
    # Break if there are no new libraries
    if ("${NEW_ARDUINO_LIBRARIES}" STREQUAL "")
        return()
    endif()
    run_arduino_wrapper("--generate-code" "-b" "${ARDUINO_FQBN}" "-i" "--libraries" ${NEW_ARDUINO_LIBRARIES})
    # Setup library include directories
    foreach(LIBRARY IN LISTS NEW_ARDUINO_LIBRARIES)
        add_library("${LIBRARY}" INTERFACE)
        target_include_directories("${LIBRARY}" INTERFACE ${WRAPPER_OUTPUT})
    endforeach()
    # Add library to list of libraries
    list(APPEND ARDUINO_LIBRARY_LIST_LOCAL ${NEW_ARDUINO_LIBRARIES})
    set_property(GLOBAL PROPERTY ARDUINO_LIBRARY_LIST ${ARDUINO_LIBRARY_LIST_LOCAL})
endfunction(include_arduino_libraries)

####
# Function `finalize_arduino_executable`:
#
# Attach the arduino libraries to a given target (e.g. executable/deployment). Additionally sets up finialization steps
# for the executable (e.g. building hex files, calculating size, etc).
#
# Args:
#    TARGET_NAME: target name to setup and build a hex file
####
function(finalize_arduino_executable TARGET_NAME)
    if (FPRIME_PRESCAN)
        return()
    endif()
    setup_arduino_libraries()
    target_link_libraries("${TARGET_NAME}" PUBLIC $<TARGET_OBJECTS:arduino_libraries_objects>)
    get_property(FINALIZE_COMMANDS GLOBAL PROPERTY ARDUINO_FINAL_COMMANDS)
    set(COMMAND_SET_ARGUMENTS)
    set(INSTALL_FILES)
    while(FINALIZE_COMMANDS)
        list(POP_FRONT FINALIZE_COMMANDS COMMAND_SET)
        string(REPLACE "<INPUT>" "$<TARGET_FILE:${TARGET_NAME}>" COMMAND_SET_WITH_INPUT "${COMMAND_SET}")
        string(REPLACE "|" ";" COMMAND_SET_LIST "${COMMAND_SET_WITH_INPUT}")
        list(APPEND COMMAND_SET_ARGUMENTS COMMAND ${COMMAND_SET_LIST})
    endwhile(FINALIZE_COMMANDS)
    list(APPEND COMMAND_SET_ARGUMENTS COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "$<TARGET_FILE:${TARGET_NAME}>.hex" "${CMAKE_INSTALL_PREFIX}/${TOOLCHAIN_NAME}/bin")
    add_custom_command(
        TARGET "${TARGET_NAME}" POST_BUILD ${COMMAND_SET_ARGUMENTS}
    )
endfunction(finalize_arduino_executable)

