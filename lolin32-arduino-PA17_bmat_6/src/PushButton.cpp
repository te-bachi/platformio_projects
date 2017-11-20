/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 20.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#include "PushButton.h"

class PushButtonHandlerDefault : public PushButtonHandler {
    public:
        PushButtonHandlerDefault()
        {

        }

        virtual ~PushButtonHandlerDefault()
        {

        }

        bool handle()
        {
            return true;
        }
};

static PushButtonHandlerDefault defaultHandler;

PushButton::PushButton(int pin) :
m_handler(defaultHandler), m_pin(pin)
{

}

PushButton::PushButton(PushButtonHandler& handler, int pin) :
m_handler(handler), m_pin(pin)
{

}

PushButton::~PushButton()
{

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
