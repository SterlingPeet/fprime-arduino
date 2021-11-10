// ======================================================================
// \title  PrmBlinkComponent.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support Parameter Usage LED Blink Demonstration deployment.
// ======================================================================


#include <ATmega/examples/ParameterBlink/PrmBlink/PrmBlinkComponent.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace ParamBlinkDemo {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  PrmBlinkComponent ::
#if FW_OBJECT_NAMES == 1
    PrmBlinkComponent(
        const char *const compName
    ) :
      PrmBlinkComponentBase(compName),
#else
    PrmBlinkComponent(void) :
#endif
    m_state(false),
    m_paramsLoaded(false),
    m_blinks(0),
    m_blinkDecimCtr(0)
  {}

  void PrmBlinkComponent ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    PrmBlinkComponentBase::init(instance);
  }

  void PrmBlinkComponent ::
    blink()
  {
    this->gpio_out(0, m_state);
  }

  PrmBlinkComponent ::
    ~PrmBlinkComponent(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void PrmBlinkComponent ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    Fw::ParamValid valid;

    m_blinkDecimCtr++;
    if(m_blinkDecimCtr >= this->paramGet_blinkDecimate(valid))
    {
      blink();
      m_state = !m_state;
      m_blinkDecimCtr = 0;

      if(m_state)
      {
        m_blinks++;
        tlmWrite_numBlinks(m_blinks);
      }
    }
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void PrmBlinkComponent ::
    downlinkParams_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    Fw::ParamValid valid;
    U8 val1 = this->paramGet_blinkDecimate(valid);
    this->tlmWrite_blinkDecimate(val1);
    I16 val2 = this->paramGet_parameter1(valid);
    this->tlmWrite_parameter1(val2);
    U32 val3 = this->paramGet_parameter2(valid);
    this->tlmWrite_parameter2(val3);
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void PrmBlinkComponent ::
    parameterUpdated(
        FwPrmIdType id
    )
  {
    this->log_ACTIVITY_LO_PrmBlinkParameterUpdated(id);
    Fw::ParamValid valid;
    switch(id) {
      case PARAMID_BLINKDECIMATE: {
        U8 val = this->paramGet_blinkDecimate(valid);
        this->tlmWrite_blinkDecimate(val);
        break;
      }
      case PARAMID_PARAMETER1: {
        I16 val = this->paramGet_parameter1(valid);
        this->tlmWrite_parameter1(val);
        break;
      }
      case PARAMID_PARAMETER2: {
        U32 val = this->paramGet_parameter2(valid);
        this->tlmWrite_parameter2(val);
        break;
      }
      default:
        FW_ASSERT(0,id);
        break;
    }
  }

} // end namespace ParamBlinkDemo
