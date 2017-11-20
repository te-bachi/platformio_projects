/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 22.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "I2CMux.h"
#include "Led.h"

Led::Led()
: _ioExpander(NULL), _pin(0), _value(false)
{

}

Led::~Led()
{

}

void
Led::begin(SX1509 *ioExpander, int pin)
{
    _ioExpander = ioExpander;
    _pin        = pin;

    I2CMux::selectGpioExpander();
    _ioExpander->pinMode(_pin, OUTPUT);
    _ioExpander->digitalWrite(_pin, _value);
}

void
Led::setValue(bool value)
{
    _value = value;

    I2CMux::selectGpioExpander();
    _ioExpander->digitalWrite(_pin, _value);
}

void
Led::toggle()
{
    _value = !_value;

    I2CMux::selectGpioExpander();
    _ioExpander->digitalWrite(_pin, _value);
}

void
Led::blink(int low, int high)
{
    I2CMux::selectGpioExpander();
    _ioExpander->blink(_pin, low, high);
}
