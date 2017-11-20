/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 16.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "Vibra.h"
#include "I2CMux.h"
#include "config.h"

Vibra::Vibra()
: _enabled(false), _duration(0), _prev(0)
{

}

Vibra::~Vibra()
{

}

void
Vibra::begin(SX1509 *ioExpander, int pwmPin, int enablePin)
{
    _ioExpander = ioExpander;
    _pwmPin     = pwmPin;
    _enablePin  = enablePin;
    _enabled    = false;
    _prev       = 0;
    _duration   = 0;

    I2CMux::selectGpioExpander();
    _ioExpander->pinMode(_enablePin, OUTPUT);
    _ioExpander->pinMode(_pwmPin,    ANALOG_OUTPUT);

    //invertiert! 3.3V - 0, 0V - 255 //Value == 120 -> keine bewegung
    _ioExpander->digitalWrite(_enablePin, LOW);
    _ioExpander->analogWrite(_pwmPin, Vibra::VIBRA_STOP);

    I2CMux::selectVibra();
    _vibra.begin();
    _vibra.Mode(0x03);          // PWM INPUT
    _vibra.MotorSelect(0x0A);
    _vibra.Library(7);          //change to 6 for LRA motors

}

bool
Vibra::isEnabled()
{
    return _enabled;
}

void
Vibra::start()
{
    start(-1);
}

void
Vibra::start(int duration)
{
    _enabled    = true;
    _prev       = millis();
    _duration   = duration;

    I2CMux::selectGpioExpander();
    _ioExpander->digitalWrite(_enablePin, HIGH);
    _ioExpander->analogWrite(_pwmPin, Vibra::VIBRA_MOVE_FAST);
}

void
Vibra::stop()
{
    _enabled    = false;

    I2CMux::selectGpioExpander();
    _ioExpander->digitalWrite(_enablePin, LOW);
    _ioExpander->analogWrite(_pwmPin, Vibra::VIBRA_STOP);
}

void
Vibra::tryStop()
{
    if (_enabled) {
        int curr = millis();
        int prev = _prev;

        if (_duration != -1 && (curr - prev) > _duration) {
            stop();
        }
    }
}
