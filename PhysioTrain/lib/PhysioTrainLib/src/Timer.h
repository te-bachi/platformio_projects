/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 13.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdint.h>

class Timer {
    private:

    public:
                        Timer();
        virtual         ~Timer();

        void            begin();
        int             getTime();

};

#endif

