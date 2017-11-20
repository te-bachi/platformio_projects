/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 22.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __LED_H__
#define __LED_H__

#include "SparkFunSX1509.h"

class Led {
    private:
        SX1509         *_ioExpander;
        int             _pin;
        bool            _value;

    public:
                        Led();
        virtual         ~Led();

        void            begin(SX1509 *ioExpander, int pin);
        void            setValue(bool value);
        void            toggle();
        void            blink(int low, int high);

    private:
};

#endif

