// ======================================================================
// \title  LoopbackSerialComponentImpl.cpp
// \author vagrant
// \brief  cpp file for LoopbackSerial component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <ATmega/examples/Serial_Loopback_Blink/LoopbackSerial/LoopbackSerialComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <Arduino.h>

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  LoopbackSerialComponentImpl ::
#if FW_OBJECT_NAMES == 1
    LoopbackSerialComponentImpl(
        const char *const compName
    ) :
      LoopbackSerialComponentBase(compName)
#else
    LoopbackSerialComponentImpl(void)
#endif
    ,writeBufferData{0xDE, 0xAD, 0xBE, 0xEF}
    ,readBufferData{0x0, 0x0, 0x0, 0x0}
  {
    writeBuffer.setsize(4);
    writeBuffer.setdata(reinterpret_cast<NATIVE_UINT_TYPE>(writeBufferData));
    readBuffer.setsize(4);
    readBuffer.setdata(reinterpret_cast<NATIVE_UINT_TYPE>(readBufferData));
  }

  void LoopbackSerialComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    LoopbackSerialComponentBase::init(instance);
    Serial.begin(115200);
    Serial.println("Initialized Serial Loopback Component");
  }

  LoopbackSerialComponentImpl ::
    ~LoopbackSerialComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void LoopbackSerialComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // TODO
    Serial.print("Write: 0x");
    Serial.print(writeBufferData[0], HEX);
    Serial.print(" 0x");
    Serial.print(writeBufferData[1], HEX);
    Serial.print(" 0x");
    Serial.print(writeBufferData[2], HEX);
    Serial.print(" 0x");
    Serial.println(writeBufferData[3], HEX);

    Drv::SerialReadStatus status;

    serialWrite_out(portNum, writeBuffer);
    serialRead_out(portNum, readBuffer, status);
    
    Serial.print("Read: 0x");
    Serial.print(readBufferData[0], HEX);
    Serial.print(" 0x");
    Serial.print(readBufferData[1], HEX);
    Serial.print(" 0x");
    Serial.print(readBufferData[2], HEX);
    Serial.print(" 0x");
    Serial.println(readBufferData[3], HEX);
  }

} // end namespace Arduino
