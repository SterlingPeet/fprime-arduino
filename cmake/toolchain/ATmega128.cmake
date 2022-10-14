####
# ATmega128.cmake:
#
# Arduino MegaCore ATmega128 support file. This file ensures that the
# ATmega128 can be useds as a target for the CMake system's output. This
# sets the Arduino target to be the MegaCore ATmega128.
####


# System setup for MegaCore
set(CMAKE_SYSTEM_NAME "ArduinoFw")
set(CMAKE_SYSTEM_PROCESSOR "avr")
set(CMAKE_CROSSCOMPILING 1)

# Teensy 31 is used to compile for the ATmega128
set(ARDUINO_FQBN "MegaCore:avr:128")
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../../ATmega/vendor/libraries/TimerOne")