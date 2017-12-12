/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 28.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#ifndef __EEPROM_UTIL_H__
#define __EEPROM_UTIL_H__

#include <stddef.h>
#include <stdint.h>

#include "Parameters.h"

namespace PA17_bmat_6 {
    typedef struct {
        DurationType    duration;
        TemperatureType temperature;
    } EEPROMConfig;

    #define EEPROM_SIZE sizeof(EEPROMConfig)

    class EEPROMUtil {
        public:
            static uint32_t readUInt32(int address);
            static void writeUInt32(int address, uint32_t value);

            static void writeDuration(DurationType duration);
            static DurationType readDuration();

            static void writeTemperature(TemperatureType temperature);
            static TemperatureType readTemperature();

            static void writeConfig(EEPROMConfig config);
            static EEPROMConfig readConfig();
    };
};

#endif
