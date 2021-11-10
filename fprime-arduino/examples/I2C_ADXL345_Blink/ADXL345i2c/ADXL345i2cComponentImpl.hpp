// ======================================================================
// \title  ADXL345i2cComponentImpl.hpp
// \author vagrant
// \brief  hpp file for ADXL345i2c component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ADXL345i2c_HPP
#define ADXL345i2c_HPP

#include "ATmega/examples/I2C_ADXL345_Blink/ADXL345i2c/ADXL345i2cComponentAc.hpp"

namespace Arduino {

  class ADXL345i2cComponentImpl :
    public ADXL345i2cComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ADXL345i2c
      //!
      ADXL345i2cComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ADXL345i2c
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ADXL345i2c
      //!
      ~ADXL345i2cComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Setup the outboard hardware ADXL345
      //!
      bool init_accel_hw(void);

      //! Convert the raw data to engineering units (G Force)
      //!
      F32 raw2eng(
          U8 raw_accel_high,
          U8 raw_accel_low,
          I16 &raw
      );

      U8 m_i2c_addr;

      bool m_hw_init;

      BYTE m_writeBufferData[2];
      Fw::Buffer m_writeBuffer;

      BYTE m_readBufferData[8];
      Fw::Buffer m_readBuffer;

    };

} // end namespace Arduino

#endif
