/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 20.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#include "PushButton.h"

#include <Arduino.h>
#include <sstream>

using namespace PA17_bmat_6;

class PushButtonHandlerDefault : public PushButtonHandler {
    public:
        PushButtonHandlerDefault()
        {

        }

        virtual ~PushButtonHandlerDefault()
        {

        }

        void handle(int pin, PushButtonEvent event)
        {
            std::ostringstream buffer;
            buffer << "PushButtonHandlerDefault: pin=" << pin;
            buffer << " event=" << event << "\n";
            Serial.println(buffer.str().c_str());
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
    /*
    int     curr = millis();
    int     prev = _prev;

    if (prev == 0 || (curr - prev) > TIME_DEBOUNCING_DELAY_MS) {
        I2CMux::selectGpioExpander();
        _value = _ioExpander->digitalRead(_pin);
    }

    return _value;
    */
}
