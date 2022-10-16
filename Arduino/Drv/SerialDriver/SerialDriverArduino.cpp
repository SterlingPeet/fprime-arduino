// ======================================================================
// \title  SerialDriverImpl.cpp
// \author lestarch
// \brief  cpp file for SerialDriver component implementation class
// ======================================================================

#include <Arduino/Drv/SerialDriver/SerialDriver.hpp>
#include <FprimeArduino.hpp>
#include <Os/Log.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Arduino {

void SerialDriver::configure(FwIndexType port_number, PlatformIntType baud) {
    switch (port_number) {
        case 0:
            m_port_pointer = reinterpret_cast<POINTER_CAST>(&Serial);
            break;
        case 1:
            m_port_pointer = reinterpret_cast<POINTER_CAST>(&Serial1);
            break;
            // case 2:
            //     m_port_pointer = reinterpret_cast<POINTER_CAST>(&Serial2);
            //     break;
            // case 3:
            //     m_port_pointer = reinterpret_cast<POINTER_CAST>(&Serial3);
            //     break;
    }
    reinterpret_cast<HardwareSerial*>(m_port_pointer)->begin(baud);
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void SerialDriver ::write_data(Fw::Buffer& fwBuffer) {
    reinterpret_cast<HardwareSerial*>(m_port_pointer)
        ->write(reinterpret_cast<U8*>(fwBuffer.getData()), fwBuffer.getSize());
}

void SerialDriver ::read_data(Fw::Buffer& fwBuffer) {
    HardwareSerial* serial_ptr = reinterpret_cast<HardwareSerial*>(m_port_pointer);
    int byte = 0;
    NATIVE_UINT_TYPE count = 0;
    U8* raw_data = reinterpret_cast<U8*>(fwBuffer.getData());
    while ((serial_ptr->available() > 0) && (count < fwBuffer.getSize()) && ((byte = serial_ptr->read()) != -1)) {
        *(raw_data + count) = static_cast<U8>(byte);
        count++;
    }
    fwBuffer.setSize(count);
}
}  // namespace Arduino
