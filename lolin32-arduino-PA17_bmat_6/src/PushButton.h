/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 20.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#ifndef __PUSH_BUTTON_H__
#define __PUSH_BUTTON_H__

#include <vector>

#include "Task.h"

namespace PA17_bmat_6 {

    enum PushButtonEvent {
        PUSH_BUTTON_NONE = 0,
        PUSH_BUTTON_PRESS,
        PUSH_BUTTON_RELEASE
    };

    typedef void (*PushButtonHandlerFunc)(int pin, PushButtonEvent event);

    class PushButtonHandler {
        public:
            virtual void    handle(int pin, PushButtonEvent event) = 0;

    };

    class PushButton {
        private:

            friend class PushButtonTask;

            enum PushButtonHandlerType {
                HANDLER_CLASS,
                HANDLER_FUNC
            };
            PushButtonHandlerType   m_handlerType;
            PushButtonHandler&      m_handler;
            PushButtonHandlerFunc   m_handlerFunc;
            int                     m_pin;
            PushButtonEvent         m_lastEvent;

        public:
                            PushButton(int pin);
                            PushButton(int pin, PushButtonHandler& handler);
                            PushButton(int pin, PushButtonHandlerFunc handler);
            virtual         ~PushButton();

            int             getPin();
            PushButtonEvent getLastEvent();

    };

    class PushButtonTask : Task {
        private:
            std::vector<PushButton*>    m_pushButtons;
            bool                        m_running;
            uint8_t                     m_debouncingDelay;

        public:
                                        PushButtonTask(uint8_t debouncingDelay);
            virtual                     ~PushButtonTask();

            void                        start();
            bool                        addPushButton(PushButton* pushButton);
            void                        run(void* data);
    };
};

#endif
