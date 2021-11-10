####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerComponentAi.xml"
  "${CMAKE_CURRENT_LIST_DIR}/LedBlinker.cpp"
)
# Check the Linux build
if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerLinux.cpp")
# ArduinoMega additions
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerArduino.cpp")
endif()
register_fprime_module()
# Add ArduinoMega dependency
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()
