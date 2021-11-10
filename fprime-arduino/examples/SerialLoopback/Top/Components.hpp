#ifndef __SERIALLOOPBACK_COMPONENTS_HEADER__
#define __SERIALLOOPBACK_COMPONENTS_HEADER__

void constructSerialLoopbackArchitecture(void);
void exitTasks(void);
void constructApp();

#include <Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>

#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

#include <ATmega/HardwareRateDriver/HardwareRateDriver.hpp>
#include <ATmega/examples/SerialLoopback/LoopbackBlinker/LoopbackBlinkerComponent.hpp>
#include <Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>

// Core components
extern Drv::ATmegaGpioDriverComponentImpl ledGpio;
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
// extern Svc::ActiveRateGroupImpl rateGroup1HzComp;
extern Svc::ActiveRateGroupImpl rateGroup10HzComp;
extern Arduino::HardwareRateDriver hardwareRateDriver;
extern example::LoopbackBlinkerComponent loopbackBlinker;
extern Drv::ATmegaSerialDriverComponentImpl comm;

#endif  // end __SERIALLOOPBACK_COMPONENTS_HEADER__
