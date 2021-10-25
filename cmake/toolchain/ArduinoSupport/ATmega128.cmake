####
# ATmega128.cmake:
#
# Arduino MegaCore ATmega128 support file. This file ensures that the
# ATmega128 can be useds as a target for the CMake system's output. This
# sets the Arduino target to be the MegaCore ATmega128.
####

# MCU unit and loader script used
set(ARDUINO_MCU "ATmega128")
string(TOLOWER "${ARDUINO_MCU}" ARDUINO_MCU_LOWER)
set(MCU_LD "${ARDUINO_MCU_LOWER}.ld")

# set(ARDUINO_PACKAGE_DIR "${FPRIME_CURRENT_BUILD_ROOT}/ATmega/vendor/MegaCore-2.0.2/" CACHE PATH "Location of downloaded board package (up to the version number)")
set(ARDUINO_PACKAGE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../ATmega/vendor/MegaCore-2.0.2/" CACHE PATH "Location of downloaded board package (up to the version number)")

set(ARDUINO_SRC_DIR "${ARDUINO_PACKAGE_DIR}/cores/MegaCore/" CACHE PATH "arduino SRC")
set(ARDUINO_VARIANT_SRC_DIR "${ARDUINO_PACKAGE_DIR}/variants/64-pin-avr/" CACHE PATH "Location of appropriate pins_arduino.h")

if(NOT DEFINED ARDUINO_CORE_DEFINES)
    set(ARDUINO_CORE_DEFINES "TIMSK1=TIMSK;TIMER1_A_PIN=13") # -DTIMER1_A_PIN=13 -DTIMER1_B_PIN=14")
    #define TIMER1_B_PIN   14
endif()

# Set the Arduino values required for the build
if(NOT DEFINED ARDUINO_FREQ)
    set(ARDUINO_FREQ 8000000)
endif()
message("Processor Speed ARDUINO_FREQ set to ${ARDUINO_FREQ}")
set(ARDUINO_ARDUINO_NUM 10805)
set(ARDUINO_TEENSYDUINO_NUM 144)
set(ARDUINO_CPU_ARCH  ${ARDUINO_MCU_LOWER})

# Teensy extras (maybe not needed)
set(ARDUINO_CPU_FLAGS "")
set(ARDUINO_LIBS "")
set(ARDUINO_SHIM_SOURCES "")
