#include <ATmega/examples/ATmegaReadInternalAdc/Top/Components.hpp>
#ifdef ARDUINO
    #include <Os/Arduino/StreamLog.hpp>
    #include <Arduino.h>
    #include <Os/AVR/XMem.hpp>
#endif

#define STARTUP_DELAY_MS 2000

/**
 * Main function.
 */
int main(int argc, char* argv[]) {
#ifdef ARDUINO
    init();
    // initVariant();  // Seems to cause main() duplicate to show up...

    Serial.begin(115200);
    Os::setArduinoStreamLogHandler(&Serial);
    Serial.println("Started!");

    delay(2000);

#endif
    constructApp();
    return 0;
}
