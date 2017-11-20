/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 13.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __PUSH_BUTTON_H__
#define __PUSH_BUTTON_H__

#include "SparkFunSX1509.h"

class PushButton {
    private:
        SX1509         *_ioExpander;
        int             _pin;
        int             _prev;  // timestamp
        bool            _value; // buffered value to be returned

    public:
                        PushButton();
        virtual         ~PushButton();

        void            begin(SX1509 *ioExpander, int pin);
        bool            getValue();

};

#endif

