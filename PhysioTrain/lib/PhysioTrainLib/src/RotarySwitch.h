/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 13.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __ROTARY_SWITCH_H__
#define __ROTARY_SWITCH_H__

#include "SparkFunSX1509.h"
#include "Mode.h"

class RotarySwitch {
    private:
        SX1509         *_ioExpander;
        int             _pin1;
        int             _pin2;
        int             _pin3;
        int             _prev;  // timestamp
        Mode            _value; // buffered value to be returned

    public:
                        RotarySwitch();
        virtual         ~RotarySwitch();

        void            begin(SX1509 *ioExpander, int pin1, int pin2, int pin3);
        Mode            getValue();

};

#endif

