#ifndef __PARAMETERBLINK_COMPONENTS_HEADER__
#define __PARAMETERBLINK_COMPONENTS_HEADER__

void constructParameterBlinkArchitecture(void);
void exitTasks(void);
void constructApp();

#include <ATmega/AssertReset/AssertResetComponent.hpp>
#include <Svc/CmdDispatcher/CommandDispatcherImpl.hpp>
#include <Svc/TlmChan/TlmChanImpl.hpp>
#include <Svc/ActiveLogger/ActiveLoggerImpl.hpp>
#include <ATmega/EePrmDb/EePrmDbComponentImpl.hpp>
#include <Svc/GroundInterface/GroundInterface.hpp>
#include <Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>
#include <Svc/LinuxTime/LinuxTimeImpl.hpp>

#include <Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>

#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

#include <ATmega/HardwareRateDriver/HardwareRateDriver.hpp>
#include <ATmega/examples/ParameterBlink/PrmBlink/PrmBlinkComponent.hpp>

// Core components
extern ATmega::AssertResetComponent assertResetter;
extern Svc::CommandDispatcherImpl cmdDisp;
extern Svc::TlmChanImpl chanTlm;
extern Svc::ActiveLoggerImpl eventLogger;
extern ATmega::EePrmDbComponentImpl eePrmDb;
extern Svc::GroundInterfaceComponentImpl groundIf;
extern Drv::ATmegaSerialDriverComponentImpl uartDriver;
extern Svc::LinuxTimeImpl linuxTime;

extern Drv::ATmegaGpioDriverComponentImpl ledGpio;
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
// extern Svc::ActiveRateGroupImpl rateGroup1HzComp;
extern Svc::ActiveRateGroupImpl rateGroup10HzComp;
extern Arduino::HardwareRateDriver hardwareRateDriver;
extern ParamBlinkDemo::PrmBlinkComponent paramBlink;

#endif  // end __PARAMETERBLINK_COMPONENTS_HEADER__
