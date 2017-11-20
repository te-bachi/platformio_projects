/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 13.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include <Arduino.h>
#include "PushButton.h"
#include "I2CMux.h"
#include "config.h"

PushButton::PushButton()
: _ioExpander(NULL), _prev(0), _value(false)
{

}

PushButton::~PushButton()
{

}

void
PushButton::begin(SX1509 *ioExpander, int pin)
{
    _ioExpander = ioExpander;
    _pin        = pin;

    I2CMux::selectGpioExpander();
    _ioExpander->pinMode(_pin, INPUT);
    _value = _ioExpander->digitalRead(_pin);
}


bool
PushButton::getValue()
{
    int     curr = millis();
    int     prev = _prev;

    if (prev == 0 || (curr - prev) > TIME_DEBOUNCING_DELAY_MS) {
        I2CMux::selectGpioExpander();
        _value = _ioExpander->digitalRead(_pin);
    }

    return _value;
}
