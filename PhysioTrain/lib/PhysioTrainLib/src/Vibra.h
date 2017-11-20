/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 16.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __VIBRA_H__
#define __VIBRA_H__

#include "SparkFunSX1509.h"
#include "Sparkfun_DRV2605L.h"

class Vibra {
    public:
        const static int    VIBRA_STOP      = 120;
        const static int    VIBRA_MOVE_SLOW = 180;
        const static int    VIBRA_MOVE_FAST = 240;
    private:
        SX1509             *_ioExpander;
        SFE_HMD_DRV2605L    _vibra;
        int                 _pwmPin;
        int                 _enablePin;
        bool                _enabled;
        int                 _prev;          // timestamp in milliseconds
        int                 _duration;      // duration in milliserconds

    public:
                        Vibra();
        virtual         ~Vibra();

        void            begin(SX1509 *ioExpander, int pwmPin, int enablePin);
        bool            isEnabled();
        void            start();
        void            start(int duration);
        void            stop();
        void            tryStop();

};

#endif

