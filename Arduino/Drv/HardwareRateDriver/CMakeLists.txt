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
# Check the Linux build
if (FPRIME_ARDUINO)
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverArduino.cpp")
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverLinux.cpp")
endif()
register_fprime_module()
