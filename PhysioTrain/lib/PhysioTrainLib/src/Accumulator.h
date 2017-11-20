/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 22.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __ACCUMULATOR_H__
#define __ACCUMULATOR_H__

#include "Led.h"

class Accumulator {
    private:
        int             _pin;
        Led             *_ledLeft;
        Led             *_ledRight;

    public:
                        Accumulator();
        virtual         ~Accumulator();

        void            begin(int pin, Led *ledLeft, Led *ledRight);
        void            checkLevel();

    private:
};

#endif

