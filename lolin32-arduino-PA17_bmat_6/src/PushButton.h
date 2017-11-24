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
        PUSH_BUTTON_PRESSED,
        PUSH_BUTTON_RELEASED
    };

    class PushButtonHandler {
        public:
            virtual void    handle(int pin, PushButtonEvent event) = 0;

    };

    class PushButton {
        private:
            PushButtonHandler&  m_handler;
            int                 m_pin;
            int                 m_prev;  // timestamp
            bool                m_value; // buffered value to be returned


        public:
                            PushButton(int pin);
                            PushButton(PushButtonHandler& handler, int pin);
            virtual         ~PushButton();

            bool            getValue();

    };

    class PushButtonTask : Task {
        private:
            std::vector<PushButton *>   m_pushButtons;

        public:
                                        PushButtonTask(int pin);
            virtual                     ~PushButtonTask();

       	    void                        run(void* data);
            void                        addPushButton(PushButton *pushButton);
    };
};

#endif
