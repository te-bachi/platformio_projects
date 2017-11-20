/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 13.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include <Arduino.h>
#include "Switch.h"
#include "I2CMux.h"
#include "config.h"

Switch::Switch()
: _ioExpander(NULL), _prev(0), _pos(false), _toggleValue(false)
{

}

Switch::~Switch()
{

}

void
Switch::begin(SX1509 *ioExpander, int pin)
{
    _ioExpander = ioExpander;
    _pin        = pin;

    I2CMux::selectGpioExpander();
    _ioExpander->pinMode(_pin, INPUT);
    _toggleValue = _ioExpander->digitalRead(_pin);
}

bool
Switch::getPosition()
{
    int     curr = millis();
    int     prev = _prev;

    if (prev == 0 || (curr - prev) > TIME_DEBOUNCING_DELAY_MS) {
        I2CMux::selectGpioExpander();
        _pos = _ioExpander->digitalRead(_pin);
    }

    return _pos;
}


bool
Switch::getToggleValue()
{
    bool    pos = getPosition();

    /* switch is pressed */
    if (pos == HIGH && _togglePos == LOW) {
        _togglePos = HIGH;

        /* invert value */
        _toggleValue = !_toggleValue;

    /* */
    } else if (pos == LOW) {
        _togglePos = LOW;
    }

    return _toggleValue;
}

int
Switch::getIncrementValue()
{
    bool    pos = getPosition();

    /* switch is pressed */
    if (pos == HIGH && _incrementePos == LOW) {
        _incrementePos = HIGH;

        /* increment */
        _incrementValue++;

    /* */
    } else if (pos == LOW) {
        _incrementePos = LOW;
    }

    return _incrementValue;
}

void
Switch::resetIncrementValue()
{
    _incrementValue = 0;
}
