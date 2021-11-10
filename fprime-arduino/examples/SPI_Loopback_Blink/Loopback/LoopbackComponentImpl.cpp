// ======================================================================
// \title  LoopbackComponentImpl.cpp
// \author vagrant
// \brief  cpp file for Loopback component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <ATmega/examples/SPI_Loopback_Blink/Loopback/LoopbackComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <Arduino.h>

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  LoopbackComponentImpl ::
#if FW_OBJECT_NAMES == 1
    LoopbackComponentImpl(
        const char *const compName
    ) :
      LoopbackComponentBase(compName)
#else
    LoopbackComponentImpl(void)
#endif
    ,spiWriteBuffer{0xDE, 0xAD, 0xBE, 0xEF}
    ,spiReadBuffer{0x00, 0x00, 0x00, 0x00}
  {
    writeBuffer.setsize(4);
    writeBuffer.setdata(reinterpret_cast<NATIVE_UINT_TYPE>(spiWriteBuffer));
    readBuffer.setsize(4);
    readBuffer.setdata(reinterpret_cast<NATIVE_UINT_TYPE>(spiReadBuffer));
  }

  void LoopbackComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    LoopbackComponentBase::init(instance);
    Serial.begin(115200);
    Serial.print("Initialized Loopback component");
    Serial.println();
  }

  LoopbackComponentImpl ::
    ~LoopbackComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void LoopbackComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // TODO
    Serial.print("DDRB: ");
    Serial.println(DDRB, HEX);

    Serial.print("Write: 0x");
    Serial.print(spiWriteBuffer[0], HEX);
    Serial.print(" 0x");
    Serial.print(spiWriteBuffer[1], HEX);
    Serial.print(" 0x");
    Serial.print(spiWriteBuffer[2], HEX);
    Serial.print(" 0x");
    Serial.println(spiWriteBuffer[3], HEX);

    SpiTransaction_out(0, writeBuffer, readBuffer);

    Serial.print("Read: 0x");
    Serial.print(spiReadBuffer[0], HEX);
    Serial.print(" 0x");
    Serial.print(spiReadBuffer[1], HEX);
    Serial.print(" 0x");
    Serial.print(spiReadBuffer[2], HEX);
    Serial.print(" 0x");
    Serial.println(spiReadBuffer[3], HEX);
  }

} // end namespace Arduino
