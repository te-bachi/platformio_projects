/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

#include <Arduino.h>
#include <Wire.h>

#define NANO_I2C_ADDRESS    0x08

void receiveEvent(int numBytes);
void edge(uint16_t *count);

typedef enum {
    DIMMER_OFF,
    DIMMER_DIMM,
    DIMMER_FULL
} DimmerType;

/*******************************************************************************
 *  50 Hz = 0.02 s (full period)
 * 100 Hz = 0.01 s (half period)
 * everything in microseconds: 0 . 000 001 s
 * wave zero-crossing every:   0 . 010 000 s
 */

const int16_t       period                  = 20000;    /* 50 Hz => 20'000 us */
const int16_t       timerThresholdZcdEdge   = 9000;     /* 9000 us, threshold to enable ZCD edge triggering */
const int16_t       timerThresholdFactor    = 1000;     /* 1000 us, factor to calculate timerThresholdBulb */
const int16_t       timerThresholdDivisor   = 100;      /* (SIGNED!!) */


const uint16_t      risingOffset            = 1000;     /* rising offset 1000 us */
const uint16_t      fallingOffset           = 680;      /* falling offset 680 us */

const uint16_t      risingThreshold         = period - risingOffset;
const uint16_t      fallingThreshold        = period - fallingOffset;

int16_t             timerThresholdBulbFinal;            /* threshold to switch off bulb (final, SIGNED!!)*/
int16_t             timerThresholdBulbCurrent;          /* threshold to switch off bulb (current, SIGNED!!) */
int16_t             timerIncrement;                     /* increment timer to final value (SIGNED!!) */
int16_t             timerOffCount;                      /* from 0 to threshold bulb (SIGNED!!) */
uint16_t            timerOnRisingCount;                 /* from 0 to (period - risingOffset) */
uint16_t            timerOnFallingCount;                /* from 0 to (period - fallingOffset) */

uint32_t            microsOld;                          /* old micros() value */

/* Switch on/off light */
DimmerType          dimmer;
bool                lightOn;

int                 zcdOld;
bool                zcdEnable;
bool                triggerChange;

/* Pin definition */
const byte          zcdPin      = 2;
const byte          switchPin   = 5;
const byte          ledPin      = LED_BUILTIN;

void
setup()
{
    /* timer variables in microseconds */
    timerThresholdBulbFinal     = 0;
    timerThresholdBulbCurrent   = 0;

    timerOffCount               = 0;
    microsOld                   = 0;

    dimmer                      = DIMMER_OFF;
    lightOn                     = false;

    zcdOld                      = LOW;
    zcdEnable                   = true;
    triggerChange               = false;

    /*** INPUT/OUTPUT *********************************************************/
    pinMode(switchPin, OUTPUT);
    digitalWrite(switchPin, HIGH);

    pinMode(zcdPin, INPUT);

    /*** CONSOLE **************************************************************/
    //Serial.begin(115200);

    /*** I2C ******************************************************************/
    Wire.begin(NANO_I2C_ADDRESS);
    Wire.onReceive(receiveEvent);

    //Serial.println("Done!");
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

    if (timerThresholdBulbCurrent == timerThresholdBulbFinal && dimmer == DIMMER_OFF) {
        /* Stop bulb */
        digitalWrite(switchPin, HIGH);

    } else if (timerThresholdBulbCurrent == timerThresholdBulbFinal && dimmer == DIMMER_FULL) {
        /* Start bulb */
        digitalWrite(switchPin, LOW);

    } else {
        /* ZCD: rising edge */
        if (zcd == HIGH && zcdOld == LOW) {
            edge(&timerOnRisingCount);

        /* ZCD: falling edge */
        } else if (zcd == LOW && zcdOld == HIGH) {
            edge(&timerOnFallingCount);

        /* ZCD: level trigger */
        } else {
            triggerChange = false;
        }

        /* If not edge trigger */
        if (!triggerChange) {
            microsNew               = micros();
            diff                    = microsNew - microsOld;
            microsOld               = microsNew;
            timerOffCount          += diff;
            timerOnRisingCount     += diff;
            timerOnFallingCount    += diff;

            /* Switch on, if... */
            if (!lightOn && (timerOnRisingCount >= risingThreshold || timerOnFallingCount >= fallingThreshold)) {
                lightOn = true;

                if (timerOnRisingCount >= risingThreshold) {
                    timerOnRisingCount = 0;
                } else if (timerOnFallingCount >= fallingThreshold) {
                    timerOnFallingCount = 0;
                }

                /* Switch: Start bulb */
                digitalWrite(switchPin, LOW);

                /* Reset */
                timerOffCount = 0;
            }

            /* Switch off, if... */
            if (lightOn && (timerOffCount >= timerThresholdBulbCurrent)) {
                lightOn = false;

                /* Switch: Stop bulb */
                digitalWrite(switchPin, HIGH);

                /* Transition */
                if (abs(timerIncrement) < abs(timerThresholdBulbFinal - timerThresholdBulbCurrent)) {
                    /* increment can be negative! */
                    timerThresholdBulbCurrent += timerIncrement;
                } else {
                    /* set to final */
                    timerThresholdBulbCurrent = timerThresholdBulbFinal;
                }
            }

            /* Enable ZCD trigger */
            if (timerOffCount >= timerThresholdZcdEdge) {
                zcdEnable = true;
            }
        }
    }

    zcdOld     = zcd;
}

void
edge(uint16_t *count)
{
    if (zcdEnable) {
        zcdEnable     = false;
        triggerChange = true;

        /* restar timer */
        *count = 0;
    } else {
        triggerChange = false;
    }
}

void
receiveEvent(int numBytes) {
    byte step = Wire.read();

    switch (step) {
        case 0:
            dimmer                  = DIMMER_OFF;
            break;

        case 1: /* 1 x 1000 = 1000 us */
        case 2: /* 2 x 1000 = 2000 us */
        case 3: /* 3 x 1000 = 3000 us */
        case 4: /* 4 x 1000 = 4000 us */
        case 5: /* 5 x 1000 = 5000 us */
        case 6: /* 6 x 1000 = 6000 us */
        case 7: /* 7 x 1000 = 7000 us */
        case 8: /* 8 x 1000 = 8000 us */
        case 9: /* 9 x 1000 = 9000 us */
            dimmer                  = DIMMER_DIMM;
            break;

        case 10: /* 10 x 1000 = 10'000 us = 0.01 s (zero-crossing length)*/
        default:
            dimmer                  = DIMMER_FULL;
            break;

    }

    timerThresholdBulbFinal = step * timerThresholdFactor;
    timerIncrement          = (timerThresholdBulbFinal - timerThresholdBulbCurrent) / timerThresholdDivisor;
}
