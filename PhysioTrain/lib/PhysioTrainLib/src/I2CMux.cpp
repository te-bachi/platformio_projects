/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 09.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "I2CMux.h"

#include <Wire.h>

extern TwoWire muxWire;

I2CMux::I2CMux()
{

}

I2CMux::~I2CMux()
{

}

void
I2CMux::select(int channel)
{
    muxWire.beginTransmission(I2C_ADDRESS_I2C_MULTIPLEXER);
    muxWire.write(1 << channel);
    muxWire.endTransmission();
}

void
I2CMux::selectGpioExpander()
{
    select(I2C_MULTIPLEXER_GPIO_EXPANDER);
}

void
I2CMux::selectRtc()
{
    select(I2C_MULTIPLEXER_RTC);
}

void
I2CMux::selectVibra()
{
    select(I2C_MULTIPLEXER_VIBRA);
}

void
I2CMux::selectRazorSlave()
{
    select(I2C_MULTIPLEXER_RAZOR_SLAVE);
}
