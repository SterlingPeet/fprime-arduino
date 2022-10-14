####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriver.cpp"
)
message(STATUS "<${FPRIME_ARDUINO}> and <${CMAKE_SYSTEM_PROCESSOR}>")
# Check the Linux build
if (FPRIME_ARDUINO AND CMAKE_SYSTEM_PROCESSOR STREQUAL "avr")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverAvr.cpp")
elseif (FPRIME_ARDUINO AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverArm.cpp")
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverLinux.cpp")
endif()
register_fprime_module()
