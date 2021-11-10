#include <ATmega/examples/ParameterBlink/Top/Components.hpp>
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

    Serial1.begin(115200);
    Os::setArduinoStreamLogHandler(&Serial1);
    Serial1.println("Started!");

    delay(2000);
    // Two quick flashes for viz indication
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(600);
#endif
    constructApp();
    return 0;
}
