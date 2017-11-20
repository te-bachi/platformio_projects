
#ifndef ARDUINO

#include "Wire.h"

TwoWire::TwoWire()
{
}

void TwoWire::begin(void) {
}

void TwoWire::begin(uint8_t address) {
}

void TwoWire::setClock(uint32_t baudrate) {
}

void TwoWire::end() {
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit)
{
    return 0;
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity)
{
    return 0;
}

void TwoWire::beginTransmission(uint8_t address)
{

}

uint8_t TwoWire::endTransmission(bool stopBit)
{
    return 0;
}

uint8_t TwoWire::endTransmission()
{
    return 0;
}

size_t TwoWire::write(uint8_t ucData)
{
    return 0;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
    return 0;
}

int TwoWire::available(void)
{
    return 0;
}

int TwoWire::read(void)
{
    return 0;
}

int TwoWire::peek(void)
{
    return 0;
}

void TwoWire::flush(void)
{
}

void TwoWire::onReceive(void(*function)(int))
{
}

void TwoWire::onRequest(void(*function)(void))
{
}

void TwoWire::onService(void)
{
}

TwoWire Wire;

#endif

