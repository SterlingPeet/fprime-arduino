####
# teensy32.cmake:
#
# Teensy 3.2 support file. This file ensures that the Teensy 3.2 can be useds as a target for the
# CMake system's output. This sets the teensy target to be the most beloved teensy 32. Bless this
# beautiful little chip.
####

# MCU unit and loader script used by the Teensy 3.2
set(ARDUINO_MCU "ATmega2560")
string(TOLOWER "${ARDUINO_MCU}" ARDUINO_MCU_LOWER)
set(MCU_LD "${ARDUINO_MCU_LOWER}.ld")

# Set the Teensy 3.2 values required for the overlord building program
set(ARDUINO_FREQ 16000000)
set(ARDUINO_ARDUINO_NUM 10805)
set(ARDUINO_TEENSYDUINO_NUM 144)
set(ARDUINO_CPU_ARCH  ${ARDUINO_MCU_LOWER})

# Teensy extras (maybe not needed)
set(ARDUINO_CPU_FLAGS "")
set(ARDUINO_LIBS "")
set(ARDUINO_SHIM_SOURCES "")
