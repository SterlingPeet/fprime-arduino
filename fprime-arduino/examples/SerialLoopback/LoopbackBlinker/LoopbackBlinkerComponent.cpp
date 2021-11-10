// ======================================================================
// \title  LoopbackBlinkerComponent.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support Serial Loopback Demo deployment.
// ======================================================================


#include <ATmega/examples/SerialLoopback/LoopbackBlinker/LoopbackBlinkerComponent.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace example {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  LoopbackBlinkerComponent ::
#if FW_OBJECT_NAMES == 1
    LoopbackBlinkerComponent(
        const char *const compName
    ) :
      LoopbackBlinkerComponentBase(compName),
#else
    LoopbackBlinkerComponent(void) :
#endif
    m_state(false)
  {}

  void LoopbackBlinkerComponent ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    LoopbackBlinkerComponentBase::init(instance);
    m_staticBuf.setdata((U64)&m_data);
    m_staticBuf.setsize(8);
    m_loopBuf.setdata((U64)&m_loop);
  }

  void LoopbackBlinkerComponent ::
    blink()
  {
    this->gpio_out(0, m_state);
  }

  LoopbackBlinkerComponent ::
    ~LoopbackBlinkerComponent(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void LoopbackBlinkerComponent ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    blink();
    m_state = !m_state;
    if(m_state)
    {
      this->serialSend_out(0, m_staticBuf);
    }
    this->m_loopBuf.setsize(64);
    this->serialRecv_out(0, m_loopBuf);
    if(this->m_loopBuf.getsize() > 0)
    {
      this->serialSend_out(0, m_loopBuf);
    }
  }

} // end namespace example
