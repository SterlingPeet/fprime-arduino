// ======================================================================
// \title  LedBlinkerImpl.cpp
// \author Sterling Peet
// \brief  cpp file for LedBlinker component implementation class
// ======================================================================


#include <ATmega/examples/AssertDemonstrator/LedBlinker/LedBlinker.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  LedBlinkerComponentImpl ::
#if FW_OBJECT_NAMES == 1
    LedBlinkerComponentImpl(
        const char *const compName
    ) :
      LedBlinkerComponentBase(compName),
#else
    LedBlinkerComponentBase(void),
#endif
    m_state(false)
  {}

  LedBlinkerComponentImpl ::
    ~LedBlinkerComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void LedBlinkerComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    blink();
    m_state = !m_state;
    FW_ASSERT(m_state);
  }

} // end namespace Arduino
