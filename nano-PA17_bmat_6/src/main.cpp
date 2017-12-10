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
/* everything in microseconds: 0 . 000 001 */
/* wave zero-crossing every:   0 . 010 000 */

volatile uint16_t   timerIncrement;
volatile uint16_t   timerThresholdBulb;
volatile uint16_t   timerThresholdWave;
volatile uint16_t   timerCount;

volatile int        ledState = LOW;
volatile bool       zcdEnabled = false;

volatile bool       triggerZcd;
volatile bool       enableZcd;

volatile bool       timerOverflow = false;
volatile bool       timerShow = false;


const byte          zcdPin = 2;
const byte          switchPin = 5;
const byte          ledPin = LED_BUILTIN;

void
setup()
{
    i                  = 0;

    timerIncrement     = 500;
    timerThresholdBulb = 2500;
    timerThresholdWave = 9500;
    timerCount         = 0;
    triggerZcd         = false;
    enableZcd          = true;

    /*** INPUT/OUTPUT *********************************************************/
    pinMode(switchPin, OUTPUT);
    digitalWrite(switchPin, HIGH);

    pinMode(zcdPin, INPUT);
    //attachInterrupt(digitalPinToInterrupt(zcdPin), zcdIsr, CHANGE);

    /*** TIMER 1 **************************************************************/

    //Timer1.initialize(timerIncrement);
    //Timer1.attachInterrupt(timerIsr);
    //Timer1.stop();

    /*** SHELL ****************************************************************/
    //shell.setPrompt("> ");
    //shell.begin(Serial, 5);

    /*** CONSOLE **************************************************************/
    Serial.begin(115400);
    //Leishman::begin();

    /*** I2C ******************************************************************/
    Wire.begin(8);
    Wire.onReceive(receiveEvent);

    Serial.println("Done!");
}

/******************************************************************************/

void
loop_a()
{
    static int a = LOW;
    a = (a == LOW ? HIGH : LOW);

    digitalWrite(switchPin, a);
}

void
timerIsr_a(void)
{
}



/******************************************************************************/


void
loop_b()
{
    uint32_t k;

    digitalWrite(switchPin, HIGH);

    noInterrupts();
    k = i;
    interrupts();

    Serial.println(k);
    delay(1000);
}


void
timerIsr_b(void)
{

}

void
zcdIsr_b()
{
    i++;
}

/******************************************************************************/

void
loop_c()
{

    //uint32_t k;
    //bool     t = false;
    //cli.check();

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
timerIsr_c(void)
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
zcdIsr_c()
{
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
    //detachInterrupt(digitalPinToInterrupt(zcdPin));
}

/******************************************************************************/

void
loop_d()
{
    uint32_t k;

    noInterrupts();
    k = i;
    interrupts();

    Serial.println(k);
    delay(1000);
}


inline void
timerIsr_d(void)
{

    /* Timer count (per ISR) greater than threshold (stop bulb) */
    if (timerCount >= timerThresholdBulb) {
        /* Stop Bulb */
        digitalWrite(switchPin, HIGH);

    }

    if (timerCount >= timerThresholdWave) {
        attachInterrupt(digitalPinToInterrupt(zcdPin), zcdIsr, CHANGE);
    }

    timerCount += timerIncrement;
}

inline void
zcdIsr_d()
{
    detachInterrupt(digitalPinToInterrupt(zcdPin));

    /* Start Bulb */
    digitalWrite(switchPin, LOW);

    /* Reset timer count */
    timerCount = 0;
    //Timer1.restart();


    i++;
}

/******************************************************************************/

void
loop_e()
{
    uint32_t k;

    noInterrupts();
    k = i;
    interrupts();

    Serial.println(k);
    delay(1000);
}


inline void
timerIsr_e(void)
{

    /* Timer count (per ISR) greater than threshold (stop bulb) */
    if (timerCount >= timerThresholdBulb) {
        /* Stop Bulb */
        digitalWrite(switchPin, HIGH);

    }

    if (timerCount >= timerThresholdWave) {
        enableZcd = true;
    }

    timerCount += timerIncrement;
}

inline void
zcdIsr_e()
{
    if (enableZcd) {
        enableZcd = false;

        /* Start Bulb */
        digitalWrite(switchPin, LOW);

        /* Reset timer count */
        timerCount = 0;


        i++;
    }
}

/******************************************************************************/

void
loop_f()
{
    static int      _zcdOld         = LOW;
    static bool     _zcdEnable      = true;
    static bool     _triggerChange  = false;
    static uint16_t _timerCount     = 0;
    static uint16_t _microsOld      = 0;

    int             zcd = digitalRead(zcdPin);
    uint16_t        diff;

    /* If rising edge or falling edge trigger */
    if ((zcd == HIGH && _zcdOld == LOW) || (zcd == LOW && _zcdOld == HIGH)) {
        if (_zcdEnable) {
            _zcdEnable     = false;
            _triggerChange = true;

            /* Start bulb */
            digitalWrite(switchPin, LOW);

            /* restar timer */
            _timerCount = 0;
        } else {
            _triggerChange = false;
        }

    /* Level trigger */
    } else {
        _triggerChange = false;
    }

    /* If not edge trigger */
    if (!_triggerChange) {
        diff         = micros() - _microsOld;
        _microsOld   = micros();
        _timerCount += diff;

        if (!_zcdEnable) {
            if (_timerCount >= timerThresholdBulb) {
                /* Stop bulb */
                digitalWrite(switchPin, HIGH);
            }

            if (_timerCount >= timerThresholdWave) {
                _zcdEnable = true;

                /* Start bulb */
                digitalWrite(switchPin, LOW);
            }
        }
    }

    _zcdOld     = zcd;
}


inline void
timerIsr_f(void)
{
    /* NOT USED */
}

inline void
zcdIsr_f()
{
    /* NOT USED */
}

/******************************************************************************/


void
loop()
{
    loop_f();
}

void
timerIsr(void)
{
    timerIsr_f();
}

void
zcdIsr() {
    zcdIsr_f();
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
