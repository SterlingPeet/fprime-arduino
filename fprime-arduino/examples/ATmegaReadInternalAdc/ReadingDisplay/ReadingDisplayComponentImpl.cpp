// ======================================================================
// \title  ReadingDisplayComponentImpl.cpp
// \author Kaushik Manchikanti <kmanchikanti6@gatech.edu>
// \brief  Example component to display the readings from the internal adc channels to the Serial Monitor
// ======================================================================


#include <ATmega/examples/ATmegaReadInternalAdc/ReadingDisplay/ReadingDisplayComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#ifdef ARDUINO
#include <Arduino.h>
#endif
#ifndef SERIAL_PORT
  #define SERIAL_PORT Serial
#endif

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ReadingDisplayComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ReadingDisplayComponentImpl(
        const char *const compName
    ) :
      ReadingDisplayComponentBase(compName),
#else
    ReadingDisplayComponentImpl(void) :
#endif
    m_channels(8)
  {}

  void ReadingDisplayComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ReadingDisplayComponentBase::init(instance);
  }

  ReadingDisplayComponentImpl ::
    ~ReadingDisplayComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ReadingDisplayComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
#ifdef ARDUINO
    SERIAL_PORT.println();
#endif
    for (int i = 0; i < m_channels; i++) {
      // retrieve the adc counts from each channel and convert them to a voltage
      getAdc_out(i,this->m_counts);
      this->m_voltage = this->m_reference_voltage * static_cast<F32>(this->m_counts) / this->m_maxCounts;

      // display the converted voltages on the Serial Monitor 
#ifdef ARDUINO
      SERIAL_PORT.print("Channel ");
      SERIAL_PORT.print(i);
      SERIAL_PORT.print(": ");
      SERIAL_PORT.print(this->m_voltage,3);
      SERIAL_PORT.print(" V\t");
#endif

      // indicate which channels are being read on the ATmega
      if (isConnected_led_OutputPort(i)) {
        led_out(i,1);
      }
    }
  }

} // end namespace Arduino
