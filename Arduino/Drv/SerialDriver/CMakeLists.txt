####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/SerialDriver.fppl"
  "${CMAKE_CURRENT_LIST_DIR}/SerialDriver.cpp"
)
# Check the Linux build
if(FPRIME_ARDUINO)
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/SerialDriverArduino.cpp")
# Teensyduino additions
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/SerialDriverLinux.cpp")
endif()
register_fprime_module()
