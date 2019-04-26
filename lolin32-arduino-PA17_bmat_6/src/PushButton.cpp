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
m_pin(pin), m_handlerType(HANDLER_CLASS), m_handler(defaultHandler),
m_handlerFunc(nullptr), m_lastEvent(PUSH_BUTTON_RELEASE)
{
        pinMode(pin, INPUT);
}

PushButton::PushButton(int pin, PushButtonHandler& handler) :
m_pin(pin), m_handlerType(HANDLER_CLASS), m_handler(handler),
m_handlerFunc(nullptr), m_lastEvent(PUSH_BUTTON_RELEASE)
{
    pinMode(pin, INPUT);
}

PushButton::PushButton(int pin, PushButtonHandlerFunc handler) :
m_pin(pin), m_handlerType(HANDLER_FUNC), m_handler(defaultHandler),
m_handlerFunc(handler), m_lastEvent(PUSH_BUTTON_RELEASE)
{
    pinMode(pin, INPUT);
}

PushButton::~PushButton()
{
    //
}

int
PushButton::getPin()
{
    return m_pin;
}

PushButtonEvent
PushButton::getLastEvent()
{
    return m_lastEvent;
}

PushButtonTask::PushButtonTask(uint8_t debouncingDelay) :
Task("PushButtonTask", 16*1024), m_running(false), m_debouncingDelay(debouncingDelay)
{

}

PushButtonTask::~PushButtonTask()
{

}

void
PushButtonTask::start()
{
    Task::start(nullptr);
}

void
PushButtonTask::run(void* data)
{
    int             pin;
    int             value;
    PushButtonEvent event = PUSH_BUTTON_NONE;

    //Serial.println("PushButtonTask::run");
    m_running = true;
    while (true) {
        //for(std::vector<PushButton*>::iterator it = m_pushButtons.begin(); it != m_pushButtons.end(); ++it) {
        for (auto const& pushButton: m_pushButtons) {
            pin   = pushButton->getPin();
            value = digitalRead(pin);

            if (value == LOW)  event = PUSH_BUTTON_RELEASE;
            if (value == HIGH) event = PUSH_BUTTON_PRESS;

            if (pushButton->getLastEvent() != event) {
                pushButton->m_handlerFunc(pin, event);
                pushButton->m_lastEvent = event;
            }
        }
        delay(m_debouncingDelay);
    }
}


/**
 * @param
 * @return TRUE when add to list, FALSE when there was an error resp. the task is already running
 */
bool
PushButtonTask::addPushButton(PushButton* pushButton)
{
    if (!m_running) {
        m_pushButtons.push_back(pushButton);
        return true;
    }

    return false;
}
