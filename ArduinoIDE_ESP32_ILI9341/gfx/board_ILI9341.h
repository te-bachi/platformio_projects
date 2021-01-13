/*
 * Board file for ESP32 on Arduino IDE 
 *
 * Developed an tested with DOIT ESP32 DEVKIT 1.0 and Arduino IDE 1.8.5
 *
 * The board file is partly based on SPI macros taken from the Adafruit ILI9341 library, see
 * https://github.com/adafruit/Adafruit_ILI9341
 *
 * Adafruit library "Adafruit_ILI9341" written by Limor Fried for Adafruit Industries (BSD license).
 * 
 * Adafruit invests time and resources providing this open source code, please support
 * Adafruit and open-source hardware by purchasing products from Adafruit!
 *
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

/*===========================================================================*/
/* Board pin settings (by default using hardware SPI).
/*===========================================================================*/
#define GDISP_PIN_CS		SS		// mandatory: chip select pin CS/SS pin display 1(here: using hardware defaults as set by the Arduino IDE)
#define GDISP_PIN_DC		15		// mandatory: data-or-command pin	
#define GDISP_PIN_RST		2		// optional: reset pin (for some displays also mandatory, see https://forum.arduino.cc/index.php?topic=473378.0 )


/*===========================================================================*/
/* Board exported functions.
/*===========================================================================*/
#define init_board(g)				ILI9341_init_board()
#define post_init_board(g)			ILI9341_post_init_board()
#define setpin_reset(g, state)		ILI9341_setpin_reset(state)
#define acquire_bus(g)				ILI9341_acquirebus()
#define release_bus(g)				ILI9341_releasebus()
#define write_index(g, index)		ILI9341_write_index(index)
#define write_data(g, data)			ILI9341_write_data(data)
#define set_backlight(g, percent)	ILI9341_set_backlight(percent)
#define setreadmode(g)				ILI9341_setreadmode()
#define setwritemode(g)				ILI9341_setwritemode()
#define read_data(g)				ILI9341_read_data()

#ifdef __cplusplus
extern "C" {
#endif

void ILI9341_init_board(void);
void ILI9341_post_init_board(void);
void ILI9341_setpin_reset(int state);
void ILI9341_acquirebus(void);
void ILI9341_releasebus(void);
void ILI9341_write_index(uint8_t index);
void ILI9341_write_data(uint8_t data);
void ILI9341_set_backlight(uint8_t percent);
void ILI9341_setreadmode(void);
void ILI9341_setwritemode(void);
uint8_t ILI9341_read_data(void);


#ifdef __cplusplus
}
#endif

#endif /* _GDISP_LLD_BOARD_H */
