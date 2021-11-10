####
# Arduino.cmake:
#
# This file acts as a template for the fprime platform files used by the CMake system.
# These files specify build flags, compiler directives, and must specify an include
# directory for system includes like "StandardTypes.hpp".

# ### Platform File Loading ###
#
# The user rarely needs to specify a platform file directly. It will be specified based on the data
# in the chosen Toolchain file, or by the CMake system itself. However, if the user want to control
# which platform file is used, the load is specified by the following rules:
#
# If the user specifies the platform from the command line using the command line option
# `-DPLATFORM=<NAME>` then that platform file will be used e.g. `-DPLATFORM=Darwin` will load the
# Darwin.cmake regardless of the Host system. This is usually used only in the case of running UTs.
#
# If the user specifies a CMake Toolchain file, then the platform file `${CMAKE_SYSTEM_NAME}.cmake`
# will be used. `${CMAKE_SYSTEM_NAME}` is set in the toolchain file.
#
# Otherwise, CMake sets the `${CMAKE_SYSTEM_NAME}` to be that of the Host system, and that platform
# will be used. e.g. when building on Linux, the platform file "Linux.cmake" will be used.
####

## Specify the OS type include directive
add_definitions(-DTGT_OS_TYPE_BAREMETAL)
add_definitions(-DFW_BAREMETAL_SCHEDULER=1)

# Specify CMAKE C and CXX compile flags. DO NOT clear existing flags
set(FPRIME_USE_BAREMETAL_SCHEDULER ON CACHE BOOL "Uses the baremetal scheduler")

include_directories(SYSTEM "${CMAKE_CURRENT_LIST_DIR}/../../ATmega/ATmegaTypes")
include_directories(SYSTEM "${CMAKE_CURRENT_LIST_DIR}/../../ATmega/ATmegaTypes/Arduino")
