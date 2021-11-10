#ifndef __ATMEGAREADINTERNALADC_COMPONENTS_HEADER__
#define __ATMEGAREADINTERNALADC_COMPONENTS_HEADER__

void constructATmegaReadInternalAdcArchitecture(void);
void exitTasks(void);
void constructApp();

#include <Drv/ATmegaInternalAdcDriver/ATmegaInternalAdcDriverComponentImpl.hpp>

#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

#include <ATmega/HardwareRateDriver/HardwareRateDriver.hpp>
#include <ATmega/examples/ATmegaReadInternalAdc/ReadingDisplay/ReadingDisplayComponentImpl.hpp>

// Core components
extern Drv::ATmegaInternalAdcDriverComponentImpl internalAdc;
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
// extern Svc::ActiveRateGroupImpl rateGroup1HzComp;
extern Svc::ActiveRateGroupImpl rateGroup10HzComp;
extern Arduino::HardwareRateDriver hardwareRateDriver;
extern Arduino::ReadingDisplayComponentImpl ReadingDisplay;

#endif  // end __ATMEGAREADINTERNALADC_COMPONENTS_HEADER__
