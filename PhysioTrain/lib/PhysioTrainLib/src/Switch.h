/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 13.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "SparkFunSX1509.h"

class Switch {
    private:
        SX1509         *_ioExpander;
        int             _pin;
        int             _prev;              // timestamp
        bool            _pos;               // switch position
        bool            _togglePos;         // buffered value to be returned
        bool            _toggleValue;       // buffered value to be returned
        bool            _incrementePos;     // buffered value to be returned
        int             _incrementValue;    // buffered increment value to be returned

    public:
                        Switch();
        virtual         ~Switch();

        void            begin(SX1509 *ioExpander, int pin);
        bool            getPosition();
        bool            getToggleValue();
        int             getIncrementValue();
        void            resetIncrementValue();

    private:
};

#endif

