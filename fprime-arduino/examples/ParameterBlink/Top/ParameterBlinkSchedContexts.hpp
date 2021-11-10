// ======================================================================
// \title  ParameterBlinkSchedContexts.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example deployment for illustrating how to use the EEPROM based parameter storage component to adjust the timing of a blinking LED.
// ======================================================================


#ifndef PARAMETERBLINK_TOP_PARAMETERBLINKSCHEDCONTEXTS_HPP_
#define PARAMETERBLINK_TOP_PARAMETERBLINKSCHEDCONTEXTS_HPP_

namespace ParameterBlink {
    // A list of contexts for the rate groups
    enum {
        // CONTEXT_PARAMETERBLINK_1Hz = 10, // 1 Hz cycle
        CONTEXT_PARAMETERBLINK_10Hz = 11 // 10 Hz cycle
    };
}  // end ParameterBlink

#endif /* PARAMETERBLINK_TOP_PARAMETERBLINKSCHEDCONTEXTS_HPP_ */
