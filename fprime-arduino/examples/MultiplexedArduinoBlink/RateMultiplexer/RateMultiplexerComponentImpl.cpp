// ======================================================================
// \title  RateMultiplexerComponentImpl.cpp
// \author Aaron McDaniel <amcdaniel39@gatech.edu>
// \brief  cpp file for RateMultiplexer component implementation class
// ======================================================================


#include <ATmega/examples/MultiplexedArduinoBlink/RateMultiplexer/RateMultiplexerComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  RateMultiplexerComponentImpl ::
#if FW_OBJECT_NAMES == 1
    RateMultiplexerComponentImpl(
        const char *const compName
    ) :
      RateMultiplexerComponentBase(compName)
#else
    RateMultiplexerComponentImpl(void)
#endif
  {

  }

  void RateMultiplexerComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    RateMultiplexerComponentBase::init(instance);
  }

  RateMultiplexerComponentImpl ::
    ~RateMultiplexerComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void RateMultiplexerComponentImpl ::
    Input10Hz_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // 10 Hz input should trigger outputs for the 10Hz components
    if(LedBlinkComponentGroup.getInputRate() == Hz10){
      this->OutputLedBlinker_out(portNum, context);      
    }
  }

  void RateMultiplexerComponentImpl ::
    ChangeRatePort_handler(
        const NATIVE_INT_TYPE portNum,
        RateGroup InputRate,
        Component TargetComponent
    )
  {
    // this should update the target component to belong to the InputRate group instead
    switch(TargetComponent.getTargetComponent()){
      case LedBlinker:
        LedBlinkComponentGroup = InputRate;
        break;
    }
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void RateMultiplexerComponentImpl ::
    change_rate_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        Component TargetComponent_comm,
        RateGroup TargetRateGroup_comm
    )
  {
    // this should update the target component to belong to the InputRate group instead
    switch(TargetComponent_comm.getTargetComponent()){
      case LedBlinker:
        LedBlinkComponentGroup = TargetRateGroup_comm;
        break;
    }
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

} // end namespace Arduino
