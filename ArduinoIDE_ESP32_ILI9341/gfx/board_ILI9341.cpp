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
 
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "board_ILI9341.h"

#define SPI_DEFAULT_FREQ	40000000
#define USE_FAST_PINIO

// SPI Macros
#ifdef USE_FAST_PINIO
volatile uint32_t *csport, *dcport;
uint32_t cspinmask, dcpinmask;
#endif

#ifdef USE_FAST_PINIO
#define SPI_DC_HIGH()	*dcport |=  dcpinmask
#define SPI_DC_LOW()	*dcport &= ~dcpinmask
#define SPI_CS_HIGH()	*csport |= cspinmask
#define SPI_CS_LOW()	*csport &= ~cspinmask
#else
#define SPI_DC_HIGH()	digitalWrite(GDISP_PIN_DC, HIGH)
#define SPI_DC_LOW()	digitalWrite(GDISP_PIN_DC, LOW)
#define SPI_CS_HIGH()	digitalWrite(GDISP_PIN_CS, HIGH)
#define SPI_CS_LOW()	digitalWrite(GDISP_PIN_CS, LOW)
#endif

#ifdef SPI_HAS_TRANSACTION
	#define HSPI_BEGIN_TRANSACTION()	SPI.beginTransaction(SPISettings(SPI_DEFAULT_FREQ, MSBFIRST, SPI_MODE0))
	#define HSPI_END_TRANSACTION()		SPI.endTransaction()
#else
	#define HSPI_BEGIN_TRANSACTION()	SPI.setFrequency(SPI_DEFAULT_FREQ); SPI.setBitOrder(MSBFIRST); SPI.setDataMode(SPI_MODE0)
	#define HSPI_END_TRANSACTION()
#endif


// Board exported functions
void ILI9341_init_board(void) {
#ifdef USE_FAST_PINIO
	csport		= portOutputRegister(digitalPinToPort(GDISP_PIN_CS));
	cspinmask	= digitalPinToBitMask(GDISP_PIN_CS);
	dcport		= portOutputRegister(digitalPinToPort(GDISP_PIN_DC));
	dcpinmask	= digitalPinToBitMask(GDISP_PIN_DC);
#endif
	pinMode(GDISP_PIN_DC, OUTPUT);
	digitalWrite(GDISP_PIN_DC, LOW);
	pinMode(GDISP_PIN_CS, OUTPUT);
	digitalWrite(GDISP_PIN_CS, HIGH);
	
	SPI.begin();
	
#ifdef GDISP_PIN_RST
	pinMode(GDISP_PIN_RST, OUTPUT);
	digitalWrite(GDISP_PIN_RST, HIGH);
	delay(100);
	digitalWrite(GDISP_PIN_RST, LOW);
	delay(100);
	digitalWrite(GDISP_PIN_RST, HIGH);
	delay(200);
#endif
}

void ILI9341_post_init_board() {

}

void ILI9341_setpin_reset(int state) {
	(void) state;
	// Ignore this, since we do a proper reset in "ILI9341_init_board".
	// Reason: The hard coded hardware reset in "gdisp_lld_ILI9341.c gdisp_lld_init" seems not work with all ILI9341 based displays.
}

void ILI9341_acquirebus(void) {
	HSPI_BEGIN_TRANSACTION();
	SPI_CS_LOW();
}

void ILI9341_releasebus(void) {
	SPI_CS_HIGH();
	HSPI_END_TRANSACTION();
}

void ILI9341_write_index(uint8_t index) {
	SPI_DC_LOW();
	SPI.write(index);
	SPI_DC_HIGH();
}

void ILI9341_write_data(uint8_t data) {
	SPI.write(data);
}

void ILI9341_set_backlight(uint8_t percent) {
	(void) percent;
}

void ILI9341_setreadmode(void) {
	
}

void ILI9341_setwritemode(void) {

}

uint8_t ILI9341_read_data(void) {
	return SPI.transfer(0);
}
