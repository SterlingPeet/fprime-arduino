#ifndef __ARD_COMPONENTS_HEADER__
#define __ARD_COMPONENTS_HEADER__

#define COMM_SERIAL

void constructArduinoArchitecture(void);
void exitTasks(void);
void constructApp();

#include <Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>

#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

#include <ATmega/examples/AssertDemonstrator/LedBlinker/LedBlinker.hpp>
#include <ATmega/HardwareRateDriver/HardwareRateDriver.hpp>
#include <ATmega/AssertReset/AssertResetComponent.hpp>

//Core components. Gotta run them all
extern Drv::ATmegaGpioDriverComponentImpl ledGpio;
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
extern Svc::ActiveRateGroupImpl rateGroup10HzComp;
extern Arduino::LedBlinkerComponentImpl ledBlinker;
extern Arduino::HardwareRateDriver hardwareRateDriver;
extern ATmega::AssertResetComponent assertResetter;
// #ifdef COMM_SERIAL
//   extern Arduino::SerialDriverComponentImpl comm;
// #endif
#endif
