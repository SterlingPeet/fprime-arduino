#include <ATmega/examples/I2C_ADXL345_Blink/Top/Components.hpp>
#ifdef ARDUINO
    #include <Os/Arduino/StreamLog.hpp>
    #include <Arduino.h>
#else
    #include <examples/ArduinoGpsTracker/SerialDriver/SerialDriver.hpp>
#endif

#define STARTUP_DELAY_MS 2000

/**
 * Main function.
 */
int main(int argc, char* argv[]) {

    // Set up the XMEM interface
    XMCRB=0; // need all 64K. no pins released
    XMCRA=1<<SRE; // enable xmem, no wait states

    // set up the bank selector pins (address lines A16..A18)
    // these are on pins 38,42,43 (PD7,PL7,PL6)
    DDRD|=_BV(PD7);
    DDRL|=(_BV(PL6)|_BV(PL7));

    // set the bank selector pins (address lines A16..A18)
    // to zero only, we aren't doing fancy mem page swapping right now
    PORTD|=_BV(PD7);
    PORTL|=(_BV(PL6)|_BV(PL7));

    init();
    // initVariant();  // Seems to cause main() duplicate to show up...

    // Set power pins for the ADXL345
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(16, OUTPUT);
    digitalWrite(14, LOW);
    digitalWrite(15, HIGH);
    digitalWrite(16, HIGH);
#ifdef ARDUINO
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
#ifndef ARDUINO
    while (1) {}
#endif
    return 0;
}
