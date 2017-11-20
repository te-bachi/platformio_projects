/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <Arduino.h>

/******************************************************************************
 * STARTUP
 *****************************************************************************/

#define PHYSIOTRAIN_COUNTDOWN           3

/******************************************************************************
 * Kinematik
 *****************************************************************************/

//#define KINEMATIK_UPPER_ARM_LENGTH      280.0f         // in Millimeter [mm]
//#define KINEMATIK_LOWER_ARM_LENGTH      280.0f         // in Millimeter [mm]

#define KINEMATIK_UPPER_ARM_LENGTH      2.8f         // in Millimeter [mm]
#define KINEMATIK_LOWER_ARM_LENGTH      2.8f         // in Millimeter [mm]

/******************************************************************************
 * Serial Port Config
 *****************************************************************************/

#define SERIAL_BAUD_RATE                115200      // Serial port baud rate


/******************************************************************************
 * IMU
 *****************************************************************************/

#define IMU_SELECT_INTERNAL             0
#define IMU_SELECT_EXTERNAL             1


/******************************************************************************
 * I2C
 *****************************************************************************/

#define I2C_ADDRESS_I2C_MULTIPLEXER     0x70
#define I2C_ADDRESS_GPIO_EXPANDER       0x3E
#define I2C_ADDRESS_RTC                 0x68
#define I2C_ADDRESS_VIBRA               0x5A
#define I2C_ADDRESS_RAZOR_SLAVE         0x1F

#define I2C_MULTIPLEXER_GPIO_EXPANDER   2
#define I2C_MULTIPLEXER_RTC             3
#define I2C_MULTIPLEXER_VIBRA           4
#define I2C_MULTIPLEXER_RAZOR_SLAVE     5

/******************************************************************************
 * GPIO RAZOR
 *****************************************************************************/

// Input
#define IO_IN_ACCU_MEASURE              A1          // A1,7 (im Schema)

/******************************************************************************
 * GPIO EXPANDER
 *****************************************************************************/

// Input
#define IO_IN_SWITCH_RECORD             0
#define IO_IN_PUSHBUTTON_START_STOP     1
#define IO_IN_ROTARYSWITCH_TEACH        2
#define IO_IN_ROTARYSWITCH_EXERCISE     3
#define IO_IN_ROTARYSWITCH_EVALUATE     4

// Output
#define IO_OUT_ACCU_INDICATION_LOW      14          // LED links
#define IO_OUT_ACCU_INDICATION_HIGH     15          // LED rechts
#define IO_OUT_VIBRA_PWM                9           // Auf dem IO Breakoutboard
#define IO_OUT_VIBRA_ENABLE             8           // Auf dem IO Breakoutboard

/******************************************************************************
 * TIME AND DATE
 *****************************************************************************/

#define TIME_DEBOUNCING_DELAY_MS        30          // in milliserconds


#endif
