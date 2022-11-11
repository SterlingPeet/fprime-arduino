####
# arduino-support.cmake:
#
# Support for arduino supported boards using the arduino-cli utility. Note: users must install boards through
# arduino-cli otherwise they will not work.
#
# @author lestarch
####
cmake_minimum_required(VERSION 3.16)

if (NOT DEFINED ARDUINO_FQBN)
    message(FATAL_ERROR "Variable ARDUINO_FQDN must be set to use arduino-support")
endif()

find_program(ARDUINO_CLI_WRAPPER "arduino-cli-wrapper")
if (NOT ARDUINO_CLI_WRAPPER)
    message(FATAL_ERROR "The arduino-cli-wrapper is required to build with this toolchain: https://github.com/SterlingPeet/arduino-cli-cmake-wrapper")
endif()

# Execute the python wrapper
execute_process(COMMAND
    "${ARDUINO_CLI_WRAPPER}" -b "${ARDUINO_FQBN}" -o "${CMAKE_BINARY_DIR}"
    OUTPUT_VARIABLE WRAPPER_OUTPUT
    RESULT_VARIABLE RET_CODE
)
if (NOT RET_CODE EQUAL 0)
    message(FATAL_ERROR "Could not run 'arduino-cli' please install 'arduino-cli' and board '${ARDUINO_FQBN}'.")
endif()
# Read each bit of information from the output variable
list(POP_FRONT WRAPPER_OUTPUT ARDUINO_CORE_PATH)
list(POP_FRONT WRAPPER_OUTPUT CMAKE_ASM_COMPILER)
list(POP_FRONT WRAPPER_OUTPUT CMAKE_ASM_FLAGS_INIT)
list(POP_FRONT WRAPPER_OUTPUT CMAKE_C_COMPILER)
list(POP_FRONT WRAPPER_OUTPUT CMAKE_C_FLAGS_INIT)
list(POP_FRONT WRAPPER_OUTPUT CMAKE_CXX_COMPILER)
list(POP_FRONT WRAPPER_OUTPUT CMAKE_CXX_FLAGS_INIT)
list(POP_FRONT WRAPPER_OUTPUT CMAKE_LINKER)
list(POP_FRONT WRAPPER_OUTPUT CMAKE_EXE_LINKER_FLAGS_INIT)

# Convert flag | separated lists to expected ' ' separated lists
string(REPLACE "|" " " CMAKE_ASM_FLAGS_INIT "${CMAKE_ASM_FLAGS_INIT}")
string(REPLACE "|" " " CMAKE_C_FLAGS_INIT   "${CMAKE_C_FLAGS_INIT}")
string(REPLACE "|" " " CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
string(REPLACE "|" " " CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT}")

set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
# Debug messages fot arduino settings
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
if (CMAKE_DEBUG_OUTPUT)
    message(STATUS "[arduino-support] Detected ASM  settings: ${CMAKE_ASM_COMPILER} ${CMAKE_ASM_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected C    settings: ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected C++  settings: ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected link settings: ${CMAKE_LINKER} ${CMAKE_EXE_LINKER_FLAGS_INIT}")
    message(STATUS "[arduino-support] Arduino core: ${ARDUINO_CORE_PATH}")
endif()
# Establish a link library for the arduino core
link_libraries("${ARDUINO_CORE_PATH}")
set(FPRIME_ARDUINO TRUE)
