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

const uint16_t      period                  = 20000;    /* 50 Hz => 20'000 us */
const uint16_t      timerThresholdZcdEdge   = 9000;     /* 9000 us, threshold to enable ZCD edge triggering */
const uint16_t      timerIncrement          = 50;       /*   50 us, increment timer to final value */
const uint16_t      timerThresholdFactor    = 1250;     /* 1250 us, factor to calculate timerThresholdBulb */

const uint16_t      risingOffset            = 1000;     /* rising offset 1000 us */
const uint16_t      fallingOffset           = 680;      /* falling offset 680 us */

const uint16_t      risingThreshold         = period - risingOffset;
const uint16_t      fallingThreshold        = period - fallingOffset;

uint16_t            timerThresholdBulb;                 /* threshold to switch off bulb*/
uint16_t            timerOnRisingCount;                 /* from 0 to (period - risingOffset) */
uint16_t            timerOnFallingCount;                /* from 0 to (period - fallingOffset) */
uint16_t            timerOffCount;                      /* from 0 to threshold bulb */

uint32_t            microsOld;                          /* old micros() value */

/* Switch on/off light */
DimmerType          dimmer;

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
    timerThresholdBulb      = 0;
    timerOffCount           = 0;
    microsOld               = 0;

    dimmer                  = DIMMER_OFF;

    zcdOld                  = LOW;
    zcdEnable               = true;
    triggerChange           = false;

    /*** INPUT/OUTPUT *********************************************************/
    pinMode(switchPin, OUTPUT);
    digitalWrite(switchPin, HIGH);

    pinMode(zcdPin, INPUT);

    /*** CONSOLE **************************************************************/
    Serial.begin(115400);

    /*** I2C ******************************************************************/
    Wire.begin(NANO_I2C_ADDRESS);
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

    if (dimmer == DIMMER_OFF) {
        /* Stop bulb */
        digitalWrite(switchPin, HIGH);

    } else if (dimmer == DIMMER_FULL) {
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
            if (timerOnRisingCount >= risingThreshold || timerOnFallingCount >= fallingThreshold) {
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
            if (timerOffCount >= timerThresholdBulb) {

                /* Switch: Stop bulb */
                digitalWrite(switchPin, HIGH);
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
    byte factor = Wire.read();
    Serial.print("Dimmer ");
    Serial.println(factor);

    switch (factor) {
        case 0:
            dimmer              = DIMMER_OFF;
            break;

        case 1: /* 1 x 1250 = 1250 us */
        case 2: /* 2 x 1250 = 2500 us */
        case 3: /* 3 x 1250 = 3750 us */
        case 4: /* 4 x 1250 = 5000 us */
        case 5: /* 5 x 1250 = 6250 us */
        case 6: /* 6 x 1250 = 7500 us */
        case 7: /* 7 x 1250 = 8750 us */
            dimmer              = DIMMER_DIMM;
            timerThresholdBulb  = factor * timerThresholdFactor;
            break;

        case 8: /* 8 x 1250 = 10'000 us = 0.01 s (zero-crossing length)*/
        default:
            dimmer              = DIMMER_FULL;
            break;

    }
}
