/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 20.11.2017
 *
 * https://github.com/te-bachi/XXX
 */

#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <stdint.h>

#include <Arduino.h>
#include <WiFi.h>

#include "MLX90614.h"
#include "Display.h"

using namespace PA17_bmat_6;

#define NANO_I2C_ADDRESS    0x08

typedef uint32_t            DurationType;
typedef uint32_t            TemperatureType;
typedef uint8_t             IntensityType;

extern DurationType         duration;
extern TemperatureType      temperature;
extern IntensityType        intensityDebug;

extern Display              display;
extern MLX90614             thermopile;

extern const char *         ssid;
extern const char *         password;

extern IPAddress            myIP;

#endif
