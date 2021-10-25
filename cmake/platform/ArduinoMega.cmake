####
# platform.cmake.template:
#
# This file acts as a template for the fprime platform files used by the CMake system.
# These files specify build flags, compiler directives, and must specify an include
# directory for system includes like "StandardTypes.hpp".
#
# Follow all the steps in this template to create a platform file. Ensure
# to remove the platform-failsafe (step 1) and fill in all <SOMETHING> tags.
#
# **Note:** If the user desires to set compiler paths, and other CMake toolchain settings, a
#           toolchain file should be constructed. See: [toolchain.md](toolchain.md)
#
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
#
# ### Filling In CMake Platform by Eample ###
#
# F prime platform files are used to set F prime specific settings. This allows the user to control
# some aspects of the F prime build at the top-leve. This means setting global include directories
# compiler definitions for the platform, threading libraries, etc. The bare-minimum platform file
# should specify an include directory for "StandardTypes.hpp" and a threading libaray if using
# active components with OS supported threads. This can be done with the following lines:
#
# ```
# FIND_PACKAGE ( Threads REQUIRED )
# include_directories(SYSTEM "${FPRIME_CORE_DIR}/Fw/Types/Linux")
# ```
#
# **Note:** much of this is done already in *-common.cmake for Linux. If using a linux-like system,
#           this can be included to save time.
#
# **Note:** if copying the template, delete the message with FATAL_ERROR line. This is a fail-safe
#           to prevent a raw-copy from being treated as a valid toolchain file.
####

## STEP 1: DELETE the following fail-safe line
#message(FATAL_ERROR "\n[F-PRIME] Platform must be filled before use.\n")

## STEP 2: Specify the OS type include directive i.e. LINUX or DARWIN
add_definitions(-DTGT_OS_TYPE_BAREMETAL)
add_definitions(-DFW_BAREMETAL_SCHEDULER=1)

# STEP 3: Specify CMAKE C and CXX compile flags. DO NOT clear existing flags
set(FPRIME_USE_BAREMETAL_SCHEDULER ON CACHE BOOL "Uses the baremetal scheduler")

# STEP 4: Specify that a thread package should be searched in the toolchain
#         directory. NOTE: when running without threads, remove this line.
#message(STATUS "Requiring thread library")
#FIND_PACKAGE ( Threads REQUIRED )

# STEP 5: Specify a directory containing the "StandardTypes.hpp" headers, as well
#         as other system headers. Other global headers can be placed here.
#         Note: Typically, the Linux directory is a good default, as it grabs
#         standard types from <stdint.h>.

#  LINUX REFERENCSE stdint.h DIRECTLY
include_directories(SYSTEM "${FPRIME_PROJECT_ROOT}/ATmega/ATmegaTypes")
include_directories(SYSTEM "${FPRIME_PROJECT_ROOT}/ATmega/ATmegaTypes/AVR")