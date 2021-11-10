// ======================================================================
// \title  ADXL345i2cComponentImpl.cpp
// \author vagrant
// \brief  cpp file for ADXL345i2c component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <ADXL345i2cComponentImpl.hpp>
#include <Arduino.h>

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ADXL345i2cComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ADXL345i2cComponentImpl(
        const char *const compName
    ) :
      ADXL345i2cComponentBase(compName)
#else
    ADXL345i2cComponentImpl(void)
#endif
  {
    m_writeBuffer.setdata((U64)m_writeBufferData);
    m_writeBuffer.setsize(2);
    m_readBuffer.setdata((U64)m_readBufferData);
    m_readBuffer.setsize(2);
    m_i2c_addr = 0x53;
    m_hw_init = false;
  }

  void ADXL345i2cComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ADXL345i2cComponentBase::init(instance);
    Serial.begin(115200);
    Serial.print("Initialized I2C ADXL Component ");
#if FW_OBJECT_NAMES == 1
    // Serial.print(m_compName);
#endif
    Serial.println();
  }

  ADXL345i2cComponentImpl ::
    ~ADXL345i2cComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ADXL345i2cComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    I16 rawX;
    I16 rawY;
    I16 rawZ;
    F32 X_val;
    F32 Y_val;
    F32 Z_val;
    // First, Check if outboard hw is initialized
    if(!m_hw_init)
    {
      // If not, try to initialize
      m_hw_init = init_accel_hw();
    }
    else
    {
      // If so, read back the XYZ Accels
      // Serial.print("go:");
      m_readBuffer.setsize(6);
      m_writeBuffer.setsize(1);
      m_writeBufferData[0] = 0x32;
      i2cTransaction_out(0, m_i2c_addr, m_writeBuffer, m_readBuffer);
      // Convert them from raw to G
      X_val = raw2eng(m_readBufferData[1], m_readBufferData[0], rawX);
      Y_val = raw2eng(m_readBufferData[3], m_readBufferData[2], rawY);
      Z_val = raw2eng(m_readBufferData[5], m_readBufferData[4], rawZ);
      // Print them out?
      Serial.print("Accel: X ");
      Serial.print(X_val);
      Serial.print(", Y ");
      Serial.print(Y_val);
      Serial.print(", Z ");
      Serial.println(Z_val);

    }
  }

  bool ADXL345i2cComponentImpl :: init_accel_hw(void)
  {
    bool ret = false;
    Serial.print("Checking Device Signature: 0x");
    Serial.print(m_i2c_addr, HEX);
    m_readBuffer.setsize(1);
    m_writeBuffer.setsize(1);
    m_writeBufferData[0] = 0x00; // Device Signature Register
    i2cTransaction_out(0, m_i2c_addr, m_writeBuffer, m_readBuffer);
    Serial.println(m_readBufferData[0], HEX);

    if(m_readBufferData[0] == 0xE5)
    {
      Serial.println("Turning on ADXL345");
      m_readBuffer.setsize(0);
      m_writeBuffer.setsize(2);
      m_writeBufferData[0] = 0x2D; // Power Status Register
      m_writeBufferData[1] = 0x08; // Turn on internal power
      i2cTransaction_out(0, m_i2c_addr, m_writeBuffer, m_readBuffer);

      Serial.print("Setting Scale and Sensitivity to Full");
      m_readBuffer.setsize(0);
      m_writeBuffer.setsize(2);
      m_writeBufferData[0] = 0x31; // Scale and Sensitivity Register
      m_writeBufferData[1] = 0x0B; // Full
      i2cTransaction_out(0, m_i2c_addr, m_writeBuffer, m_readBuffer);
      ret = true;
    }
    else
    {
      Serial.println("Wrong signature!!!");
    }
    return ret;
  }

  F32  ADXL345i2cComponentImpl ::
    raw2eng(
          U8 raw_accel_high,
          U8 raw_accel_low,
          I16 &raw
      )
  {
    raw = (uint16_t)(raw_accel_low | raw_accel_high << 8);
    return (F32)raw / 256.0;
  }

} // end namespace Arduino
