// ======================================================================
// \title  SerialDriverImpl.cpp
// \author lestarch
// \brief  cpp file for SerialDriver component implementation class
// ======================================================================

#include <Arduino/Drv/SerialDriver/SerialDriver.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

SerialDriver ::SerialDriver(const char* compName)
    : SerialDriverComponentBase(compName),
      m_port_pointer(static_cast<POINTER_CAST>(NULL)),
      m_local_buffer(m_data, SERIAL_BUFFER_SIZE) {}

SerialDriver ::~SerialDriver(void) {}

void SerialDriver ::init(const NATIVE_INT_TYPE instance) {
    SerialDriverComponentBase::init(instance);
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Drv::SendStatus SerialDriver ::send_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    write_data(fwBuffer);
    deallocate_out(0, fwBuffer);
    return Drv::SendStatus::SEND_OK;
}

Drv::PollStatus SerialDriver ::poll_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    read_data(fwBuffer);
    return Drv::PollStatus::POLL_OK;
}

void SerialDriver::recvReturn_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    // Intentionally does nothing. Could check return
}

void SerialDriver ::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    m_local_buffer.setSize(SERIAL_BUFFER_SIZE);
    read_data(m_local_buffer);
    if (m_local_buffer.getSize() > 0) {
        recv_out(0, m_local_buffer, Drv::RecvStatus::RECV_OK);
    }
}

}  // namespace Arduino
