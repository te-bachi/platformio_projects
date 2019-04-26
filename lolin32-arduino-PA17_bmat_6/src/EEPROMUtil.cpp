/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 28.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#include "EEPROMUtil.h"

#include <EEPROM.h>

using namespace PA17_bmat_6;

uint32_t
EEPROMUtil::readUInt32(int address)
{
    return 0;
}

void
EEPROMUtil::writeUInt32(int address, uint32_t value)
{

}

void
EEPROMUtil::writeDuration(DurationType duration)
{

}

DurationType
EEPROMUtil::readDuration()
{
    return 0;
}

void
EEPROMUtil::writeTemperature(TemperatureType temperature)
{

}

TemperatureType
EEPROMUtil::readTemperature()
{
    return 0;
}

void
EEPROMUtil::writeConfig(EEPROMConfig config)
{
    EEPROM.put(0, config);
    EEPROM.commit();
}

EEPROMConfig
EEPROMUtil::readConfig()
{
    EEPROMConfig config;
    EEPROM.get(0, config);
    return config;
}
