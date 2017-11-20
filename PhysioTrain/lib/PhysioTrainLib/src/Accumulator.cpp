/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 22.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "Arduino.h"
#include "Accumulator.h"
#include "I2CMux.h"

#include <inttypes.h>

#define maxWertAkkuMessung        1010

Accumulator::Accumulator()
{

}

Accumulator::~Accumulator()
{

}

void
Accumulator::begin(int pin, Led *ledLeft, Led *ledRight)
{
    _pin        = pin;
    _ledLeft    = ledLeft;
    _ledRight   = ledRight;
}

/**
 * U = Umessung *4.3 / 3.3
 * Umax = 4.2V
 * Umin = 3V
 * 100% = 4.2V
 * 90% = 4.08V  Stufe 4
 * 70% = 3.84V   Stufe 3
 * 50% = 3.6V   Stufe 2
 * 35% = 3.42V  Stufe 1
 * 20% = 3.24V  Stufe 0
 * 0% = 3V
 * 2^10 = 1024 - 3.3V
 */
void
Accumulator::checkLevel()
{

    uint8_t zustand = 0;
    uint8_t akkuMessung = analogRead(_pin);

    //check if AkkuMessung im Bereich
    //Messung * SkalierungMesswert * Widerstandsteiler
    float Uakku = akkuMessung * (3.3 / maxWertAkkuMessung) * (4.3 / 3.3) + 3.0;

    if      (Uakku > 3.99)   zustand = 4;
    else if (Uakku > 3.84)   zustand = 3;
    else if (Uakku > 3.60)   zustand = 2;
    else if (Uakku > 3.42)   zustand = 1;
    else if (Uakku > 3.24)   zustand = 0;

    switch (zustand) {
        case 4:     _ledLeft->setValue(HIGH);   _ledRight->setValue(HIGH);      break;
        case 3:     _ledLeft->setValue(HIGH);   _ledRight->blink(400, 400);     break;
        case 2:     _ledLeft->setValue(HIGH);   _ledRight->setValue(LOW);       break;
        case 1:     _ledLeft->blink(400, 400);  _ledRight->setValue(LOW);       break;
        case 0:
        default:    _ledLeft->setValue(LOW);    _ledRight->setValue(LOW);       break;
    }

    /*
    SerialUSB.print("akkuMessung=");
    SerialUSB.print(akkuMessung);
    SerialUSB.print(" Uakku=");
    SerialUSB.print(Uakku);
    SerialUSB.print(" zustand=");
    SerialUSB.println(zustand);
    */
}
