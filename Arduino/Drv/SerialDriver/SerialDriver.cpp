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

  SerialDriverComponentImpl ::
    SerialDriverComponentImpl(
        const char* compName
    ) :
      SerialDriverComponentBase(compName),
      m_port_number(0), // TODO: Should be configurable
      m_port_pointer(static_cast<POINTER_CAST>(NULL)),
      m_local_buffer(m_data, SERIAL_BUFFER_SIZE)
  {

  }

  SerialDriverComponentImpl ::
    ~SerialDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void SerialDriverComponentImpl ::
    write_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
      write_data(fwBuffer);
  }

  void SerialDriverComponentImpl ::
    readPoll_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
      read_data(fwBuffer);
  }

  void SerialDriverComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum, /*!< The port number*/
        NATIVE_UINT_TYPE context /*!< The call order*/
    )
  {
      m_local_buffer.setSize(SERIAL_BUFFER_SIZE);
      read_data(m_local_buffer);
      if (m_local_buffer.getSize() > 0) {
          readCallback_out(0, m_local_buffer);
      }
  }

} // end namespace Svc
