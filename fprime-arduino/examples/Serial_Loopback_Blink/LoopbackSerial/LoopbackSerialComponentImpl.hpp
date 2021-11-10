// ======================================================================
// \title  LoopbackSerialComponentImpl.hpp
// \author vagrant
// \brief  hpp file for LoopbackSerial component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef LoopbackSerial_HPP
#define LoopbackSerial_HPP

#include "ATmega/examples/Serial_Loopback_Blink/LoopbackSerial/LoopbackSerialComponentAc.hpp"

namespace Arduino {

  class LoopbackSerialComponentImpl :
    public LoopbackSerialComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object LoopbackSerial
      //!
      LoopbackSerialComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object LoopbackSerial
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object LoopbackSerial
      //!
      ~LoopbackSerialComponentImpl(void);

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

      U8 writeBufferData[4];
      Fw::Buffer writeBuffer;
      U8 readBufferData[4];
      Fw::Buffer readBuffer;

    };

} // end namespace Arduino

#endif
