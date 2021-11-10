// ======================================================================
// \title  LedBlinkerImpl.cpp
// \author lestarch
// \brief  cpp file for LedBlinker component implementation class
// ======================================================================


#include <ATmega/examples/ArduinoBlinkBasic/LedBlinker/LedBlinker.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <stdio.h>

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
