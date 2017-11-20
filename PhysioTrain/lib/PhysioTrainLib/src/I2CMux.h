/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 09.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __I2C_MUX_H__
#define __I2C_MUX_H__

class I2CMux {
    private:
                        I2CMux();
        virtual         ~I2CMux();

    public:

        static void     select(int channel);
        static void     selectGpioExpander();
        static void     selectRtc();
        static void     selectVibra();
        static void     selectRazorSlave();
};

#endif

