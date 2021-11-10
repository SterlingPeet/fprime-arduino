// ======================================================================
// \title  ATmegaReadInternalAdcSchedContexts.hpp
// \author Kaushik Manchikanti <kmanchikanti6@gatech.edu>
// \brief  Example deployment to show how to read from the ATmega's internal adc
// ======================================================================


#ifndef ATMEGAREADINTERNALADC_TOP_ATMEGAREADINTERNALADCSCHEDCONTEXTS_HPP_
#define ATMEGAREADINTERNALADC_TOP_ATMEGAREADINTERNALADCSCHEDCONTEXTS_HPP_

namespace ATmegaReadInternalAdc {
    // A list of contexts for the rate groups
    enum {
        // CONTEXT_ATMEGAREADINTERNALADC_1Hz = 10, // 1 Hz cycle
        CONTEXT_ATMEGAREADINTERNALADC_10Hz = 11 // 10 Hz cycle
    };
}  // end ATmegaReadInternalAdc

#endif /* ATMEGAREADINTERNALADC_TOP_ATMEGAREADINTERNALADCSCHEDCONTEXTS_HPP_ */
