/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

#include <Arduino.h>
#include <Wire.h>

void receiveEvent(int numBytes);

/*******************************************************************************
 *  50 Hz = 0.02 s (full period)
 * 100 Hz = 0.01 s (half period)
 * everything in microseconds: 0 . 000 001 s
 * wave zero-crossing every:   0 . 010 000 s
 */

uint16_t            timerIncrement;         /* increment timer to final value */
uint16_t            timerThresholdBulb;     /* */
uint16_t            timerThresholdWave;     /* threshold to enable ZCD triggering */
uint16_t            timerCount;             /* from 0 to threshold bulb */

uint32_t            microsOld;              /* old micros() value */

/* Switch on/off light */
bool                lightOff;
bool                lightFull;

int                 zcdOld         = LOW;
bool                zcdEnable      = true;
bool                triggerChange  = false;

/* Pin definition */
const byte          zcdPin      = 2;
const byte          switchPin   = 5;
const byte          ledPin      = LED_BUILTIN;

void
setup()
{
    timerIncrement      = 50;
    timerThresholdBulb  = 0;
    timerThresholdWave  = 9000;
    timerCount          = 0;
    microsOld           = 0;

    lightOff            = true;
    lightFull           = false;

    zcdOld              = LOW;
    zcdEnable           = true;
    triggerChange       = false;

    /*** INPUT/OUTPUT *********************************************************/
    pinMode(switchPin, OUTPUT);
    digitalWrite(switchPin, HIGH);

    pinMode(zcdPin, INPUT);

    /*** CONSOLE **************************************************************/
    Serial.begin(115400);

    /*** I2C ******************************************************************/
    Wire.begin(8);
    Wire.onReceive(receiveEvent);

    Serial.println("Done!");
}

/******************************************************************************
 * void digitalWrite(uint8_t, uint8_t);
 * int digitalRead(uint8_t);
 */

void
loop()
{
    int             zcd = digitalRead(zcdPin);
    uint32_t        microsNew;
    uint32_t        diff;

    if (lightOff) {
        /* Stop bulb */
        digitalWrite(switchPin, HIGH);

    } else if (lightFull) {
        /* Start bulb */
        digitalWrite(switchPin, LOW);

    } else {
        /* If rising edge or falling edge trigger */
        if ((zcd == HIGH && zcdOld == LOW) || (zcd == LOW && zcdOld == HIGH)) {
            if (zcdEnable) {
                zcdEnable     = false;
                triggerChange = true;

                /* Start bulb */
                digitalWrite(switchPin, LOW);

                /* restar timer */
                timerCount = 0;
            } else {
                triggerChange = false;
            }

        /* Level trigger */
        } else {
            triggerChange = false;
        }

        /* If not edge trigger */
        if (!triggerChange) {
            microsNew    = micros();
            diff         = microsNew - microsOld;
            microsOld   = microsNew;
            timerCount += diff;

            if (timerCount >= timerThresholdBulb) {
                /* Stop bulb */
                digitalWrite(switchPin, HIGH);
            }

            if (timerCount >= timerThresholdWave) {
                zcdEnable = true;

            }
        }
    }

    zcdOld     = zcd;
}

void
receiveEvent(int numBytes) {
    byte factor = Wire.read();
    switch (factor) {
        case 0:
            lightOff            = true;
            lightFull           = false;
            break;

        case 1: /* 1 x 1250 = 1250 us */
        case 2: /* 2 x 1250 = 2500 us */
        case 3: /* 3 x 1250 = 3750 us */
        case 4: /* 4 x 1250 = 5000 us */
        case 5: /* 5 x 1250 = 6250 us */
        case 6: /* 6 x 1250 = 7500 us */
        case 7: /* 7 x 1250 = 8750 us */
            lightOff            = false;
            lightFull           = false;
            timerThresholdBulb  = factor * 1250;
            break;

        case 8: /* 8 x 1250 = 10'000 us = 0.01 s (zero-crossing length)*/
        default:
            lightOff            = false;
            lightFull           = true;
            break;

    }
}
