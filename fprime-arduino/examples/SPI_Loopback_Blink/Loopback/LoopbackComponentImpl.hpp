// ======================================================================
// \title  LoopbackComponentImpl.hpp
// \author vagrant
// \brief  hpp file for Loopback component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef Loopback_HPP
#define Loopback_HPP

#include "ATmega/examples/SPI_Loopback_Blink/Loopback/LoopbackComponentAc.hpp"

namespace Arduino {

  class LoopbackComponentImpl :
    public LoopbackComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Loopback
      //!
      LoopbackComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object Loopback
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object Loopback
      //!
      ~LoopbackComponentImpl(void);

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

      U8 spiWriteBuffer[4];
      U8 spiReadBuffer[4];
      Fw::Buffer writeBuffer;
      Fw::Buffer readBuffer;

    };

} // end namespace Arduino

#endif
