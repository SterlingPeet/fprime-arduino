#include <ATmega/examples/ArduinoBlinkBasic/Top/Components.hpp>
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
    delay(STARTUP_DELAY_MS);
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
