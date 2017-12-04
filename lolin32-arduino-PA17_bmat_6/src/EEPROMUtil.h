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

#define EEPROM_SIZE 64

class EEPROMUtil {
    static uint32_t readUInt32(int address);
    static void writeUInt32(int address, uint32_t value);
};

#endif
