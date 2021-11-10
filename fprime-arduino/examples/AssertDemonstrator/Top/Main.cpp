#include <ATmega/examples/AssertDemonstrator/Top/Components.hpp>
#include <ATmega/AssertReset/AssertResetComponent.hpp>
#ifdef ARDUINO
    #include <Os/Arduino/StreamLog.hpp>
    #include <Arduino.h>
    #include <Os/AVR/XMem.hpp>
#endif

#define STARTUP_DELAY_MS 2000

// This variable ends up in SRAM, but does not get initialized
// so it retains its value between reset events
volatile U16 bootCount __attribute__ ((section(".noinit")));

/**
 * Main function.
 */
int main(int argc, char* argv[]) {
#ifdef ARDUINO
    init();
    // initVariant();  // Seems to cause main() duplicate to show up...

    Serial.begin(115200);
    Serial.println("\n\n\nAssert Demonstrator deployment, starting up.");
    Serial.print("MCUCSR (boot flag register): 0x");
    Serial.println(MCUCSR, HEX);
    // Could use if statements to list flags raised here

    if(MCUCSR != _BV(WDRF))
    {
        Serial.println("This was not a watchdog reset, safely ignore Assert Flag.");
        bootCount = 0;
        MCUCSR = 0;
    }
    Serial.print("Boot Count: ");
    Serial.println(bootCount);
    bootCount++;

    Serial.print("Previous Assert Flag: 0x");
    Serial.println(ATmega::assertFlag, HEX);
    if(ATmega::assertFlag == ATmega::assertFlagTrue)
    {
        Serial.println("Previous Assert Information:");
        Serial.print(" * Location: File ");
 #if FW_ASSERT_LEVEL == FW_FILEID_ASSERT
        Serial.print("Search Command: fprime-util hash-to-file 0x");
        Serial.println(ATmega::prevAssertFile, HEX);
#else
        Serial.println(ATmega::prevAssertFile);
#endif
        Serial.print(" * Line Number: ");
        Serial.println(ATmega::prevAssertLineNo);

        Serial.println("Resetting Assert Flag.");
        ATmega::assertFlag = 0;
    }

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
