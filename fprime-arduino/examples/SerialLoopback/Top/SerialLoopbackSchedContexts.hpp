// ======================================================================
// \title  SerialLoopbackSchedContexts.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example Serial Loopback Demonstration deployment to show Serial functionality and hookup.
// ======================================================================


#ifndef SERIALLOOPBACK_TOP_SERIALLOOPBACKSCHEDCONTEXTS_HPP_
#define SERIALLOOPBACK_TOP_SERIALLOOPBACKSCHEDCONTEXTS_HPP_

namespace SerialLoopback {
    // A list of contexts for the rate groups
    enum {
        // CONTEXT_SERIALLOOPBACK_1Hz = 10, // 1 Hz cycle
        CONTEXT_SERIALLOOPBACK_10Hz = 11 // 10 Hz cycle
    };
}  // end SerialLoopback

#endif /* SERIALLOOPBACK_TOP_SERIALLOOPBACKSCHEDCONTEXTS_HPP_ */
