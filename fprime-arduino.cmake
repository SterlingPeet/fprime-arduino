# Disable targets not supported on Arduino
set_target_properties(
    Svc_LinuxTime
    Drv_SocketIpDriver
    PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Os")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/ArduinoTime")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/SerialDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/HardwareRateDriver")

