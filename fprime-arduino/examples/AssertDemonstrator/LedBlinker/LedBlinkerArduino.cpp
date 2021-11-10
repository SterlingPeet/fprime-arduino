// ======================================================================
// \title  LedBlinkerImpl.cpp
// \author Sterling Peet
// \brief  cpp file for LedBlinker component implementation class
// ======================================================================


#include <ATmega/examples/AssertDemonstrator/LedBlinker/LedBlinker.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <Arduino.h>
namespace Arduino {

  void LedBlinkerComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    LedBlinkerComponentBase::init(instance);
  }

  void LedBlinkerComponentImpl ::
    blink()
  {
      this->gpio_out(0, m_state);
  }
} // end namespace Arduino
