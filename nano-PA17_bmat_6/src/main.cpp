/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

#include <Arduino.h>
#include <Wire.h>
#include "Shell.h"
#include "TimerOne.h"
#include "Leishman.h"

void blinkLED(void);
void receiveEvent(int numBytes);
void timerIsr();
void zcdIsr();

//Shell               shell;

volatile uint32_t   i;
volatile int        ledState = LOW;
volatile bool       zcdEnabled = false;
volatile bool       timerOverflow = false;
volatile bool       timerShow = false;

const byte          zcdPin = 2;
const byte          switchPin = 5;
const byte          ledPin = LED_BUILTIN;

void
setup()
{
    i = 0;

    /*** INPUT/OUTPUT *********************************************************/
    pinMode(switchPin, OUTPUT);
    digitalWrite(switchPin, LOW);
    attachInterrupt(digitalPinToInterrupt(zcdPin), zcdIsr, RISING);

    /*** TIMER 1 **************************************************************/
    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerIsr);
    //Timer1.stop();

    /*** SHELL ****************************************************************/
    //shell.setPrompt("> ");
    //shell.begin(Serial, 5);

    /*** CONSOLE **************************************************************/
    Leishman::begin();

    /*** I2C ******************************************************************/
    //Wire.begin(8);
    //Wire.onReceive(receiveEvent);

    Serial.println("Done!");
}

void
loop()
{
    uint32_t k;
    bool     t = false;
    //cli.check();

    static int a = LOW;
    a = (a == LOW ? HIGH : LOW);

    digitalWrite(switchPin, a);

    /*
    noInterrupts();
    if (timerShow) {
        ledState = (ledState == LOW ? HIGH : LOW);
        digitalWrite(ledPin, ledState);
        timerShow       = false;
        t               = true;
        k               = i;
    }
    interrupts();

    if (t) {
        String s = "i = " + String(k);
        Serial.println(s);
    }
    */

    /*
    noInterrupts();
    if (timerShow) {
        k         = i;
    }
    interrupts();
    Serial.println(k);
    delay(1000);
    */

    /*
    noInterrupts();
    if (timerShow) {
        timerShow = false;
        k         = i;
        t         = true;
    }
    interrupts();
    if (t) {
        Serial.println(k);
    }
    */

    //shell.loop();
}

void
timerIsr(void)
{
    static uint8_t  intTrigger = 0;
    static uint16_t showTrigger = 0;
    /*
    timerOverflow = true;
    timerShow     = true;
    Timer1.stop();
    Serial.println("!");
    */
    if (intTrigger >= 10) {
        intTrigger = 0;
        attachInterrupt(digitalPinToInterrupt(zcdPin), zcdIsr, RISING);
    }
    if (showTrigger >= 1000) {
        showTrigger = 0;
        timerShow = true;
    }


    //ledState = (ledState == LOW ? HIGH : LOW);
    //digitalWrite(ledPin, ledState);
    intTrigger++;
    showTrigger++;
}

void
zcdIsr() {
    /*
    if (!zcdEnabled) {
        zcdEnabled = true;
    }
    */

    /*
    if (timerOverflow) {
        timerOverflow = false;
        Timer1.start();
    }
    */

    //Serial.println("!");
    detachInterrupt(digitalPinToInterrupt(zcdPin));
    i++;

}


void
receiveEvent(int numBytes) {
    Serial.print("I2C (bytes=");
    Serial.print(numBytes);
    Serial.print(") ");
    while (1 < Wire.available()) {
        char c = Wire.read();
        Serial.print(c);
    }
    byte x = Wire.read();
    Serial.println(x);
}
