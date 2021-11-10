// ======================================================================
// \title  RateMultiplexerComponentImpl.hpp
// \author Aaron McDaniel <amcdaniel39@gatech.edu>
// \brief  hpp file for RateMultiplexer component implementation class
// ======================================================================

#ifndef RateMultiplexer_HPP
#define RateMultiplexer_HPP

#include "ATmega/examples/MultiplexedArduinoBlink/RateMultiplexer/RateMultiplexerComponentAc.hpp"

namespace Arduino {

  class RateMultiplexerComponentImpl :
    public RateMultiplexerComponentBase
  {

    public:
      RateGroup LedBlinkComponentGroup = RateGroup(Hz10);
      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object RateMultiplexer
      //!
      RateMultiplexerComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object RateMultiplexer
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object RateMultiplexer
      //!
      ~RateMultiplexerComponentImpl(void);

    PRIVATE:
      bool LedBlinkerGroupSet = false;
      RateGroup LedBlinkerGroup;
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for Input10Hz
      //!
      void Input10Hz_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Handler implementation for ChangeRatePort
      //!
      void ChangeRatePort_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          RateGroup InputRate, 
          Component TargetComponent 
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for change_rate command handler
      //! Command for changing rate subscription
      void change_rate_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Component TargetComponent_comm, /*!< Target Component Changing Rates*/
          RateGroup TargetRateGroup_comm /*!< Target Component Changing Rates*/
      );


    };

} // end namespace Arduino

#endif
