/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 14.12.2017
 *
 * https://github.com/te-bachi/XXX
 */

#include "Dimmer.h"


using namespace PA17_bmat_6;

Dimmer::Dimmer(TwoWire& twoWire, int address) :
m_twoWire(twoWire), m_address(address)
{
    //
}

void
Dimmer::setStep(Step step)
{
    m_twoWire.beginTransmission(m_address);
    m_twoWire.write(step);
    m_twoWire.endTransmission();
}
