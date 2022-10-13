#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <Arduino/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Os/IntervalTimer.hpp>
#include <FprimeArduino.hpp>

namespace Arduino {
IntervalTimer s_itimer;

void HardwareRateDriver::start() {
    bool ok = s_itimer.begin(HardwareRateDriver::s_timerISR, m_interval * 1000);
    if (isConnected_error_OutputPort(0)) {
        error_out(0, ok ? Fw::Logic::HIGH : Fw::Logic::LOW);
    }
}

void HardwareRateDriver::stop() {
    s_itimer.end();
}

void HardwareRateDriver::s_timerISR() {
    s_timer(s_driver);
}

};
