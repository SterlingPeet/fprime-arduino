#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <Arduino/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <FprimeArduino.hpp>

namespace Arduino {
IntervalTimer s_itimer;

void HardwareRateDriver::start() {
    bool ok = s_itimer.begin(HardwareRateDriver::s_timerISR, m_interval * 1000);
    if (!ok) {
        digitalWrite(13, HIGH);
    }
}

void HardwareRateDriver::stop() {
    s_itimer.end();
}

void HardwareRateDriver::s_timerISR() {
    s_timer(s_driver);
}

};
