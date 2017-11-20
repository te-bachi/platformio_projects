/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 13.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include <Arduino.h>
#include "RotarySwitch.h"
#include "I2CMux.h"
#include "config.h"

RotarySwitch::RotarySwitch()
: _ioExpander(NULL), _pin1(0), _pin2(0), _pin3(0), _prev(0), _value(Mode::NONE)
{

}

RotarySwitch::~RotarySwitch()
{

}

void
RotarySwitch::begin(SX1509 *ioExpander, int pin1, int pin2, int pin3)
{
    _ioExpander = ioExpander;
    _pin1       = pin1;
    _pin2       = pin2;
    _pin3       = pin3;

    I2CMux::selectGpioExpander();
    _ioExpander->pinMode(_pin1, INPUT);
    _ioExpander->pinMode(_pin2, INPUT);
    _ioExpander->pinMode(_pin3, INPUT);
}


Mode
RotarySwitch::getValue()
{
    int     curr = millis();
    int     prev = _prev;
    int     value1;
    int     value2;
    int     value3;

    if (prev == 0 || (curr - prev) > TIME_DEBOUNCING_DELAY_MS) {
        I2CMux::selectGpioExpander();

        /* TEACH */
        value1 = _ioExpander->digitalRead(_pin1);
        if (value1 == HIGH) {
            _value = Mode::TEACH;
            return _value;
        }

        /* EXERCISE */
        value2 = _ioExpander->digitalRead(_pin2);
        if (value2 == HIGH) {
            _value = Mode::EXERCISE;
            return _value;
        }

        /* EVALUATE */
        value3 = _ioExpander->digitalRead(_pin3);
        if (value3 == HIGH) {
            _value = Mode::EVALUATE;
        }

        _value = Mode::EVALUATE;
    }

    return _value;
}
