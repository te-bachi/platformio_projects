/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 14.12.2017
 *
 * https://github.com/te-bachi/XXX
 */

#ifndef __DIMMER_H__
#define __DIMMER_H__

#include <Arduino.h>
#include <Wire.h>

#define NANO_I2C_ADDRESS    0x08

namespace PA17_bmat_6 {

    class Dimmer {

        public:
            enum Step {
                OFF     = 0,
                FIRST   = 1,
                SECOND  = 2,
                THIRD   = 3,
                FOURTH  = 4,
                FIFTH   = 5,
                SIXTH   = 6,
                SEVENT  = 7,
                EIGTH   = 8,
                NINTH   = 9,
                FULL    = 10
            };

        private:
            TwoWire&            m_twoWire;
            int                 m_address;

        public:
                                Dimmer(TwoWire& twoWire, int address);
            virtual             ~Dimmer() {};

            void                setStep(Step step);
    };
};


#endif
