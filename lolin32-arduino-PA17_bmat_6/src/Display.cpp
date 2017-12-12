/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 12.12.2017
 *
 * https://github.com/te-bachi/XXX
 */

#include "Display.h"
#include "Parameters.h"

#include <Arduino.h>

#include "SSD1306.h"

#include "logo.xbm"

using namespace PA17_bmat_6;

SSD1306 oled(0x3C /* I2C address */, 21 /* SDA */, 22 /* SCL */);

/*
display.setFont(ArialMT_Plain_10);

display.clear();
display.setTextAlignment(TEXT_ALIGN_LEFT);
display.setFont(ArialMT_Plain_10);
display.drawString(0, 0, "Hello world");
display.setFont(ArialMT_Plain_16);
display.drawString(0, 10, "Hello world");
display.setFont(ArialMT_Plain_24);
display.drawString(0, 26, "Hello world");
display.display();




double temp = thermopile.readObjectTempC();
String tempStr = String(temp);

//Serial.println("Loop");
display.clear();
for (int i = 0, k = 2; i < 16; i++, k++) {
    display.drawLine(0, i, 2*k, i);
}

//display.drawProgressBar(0, 0, uint16_t width, uint16_t height, uint8_t progress);

/*
std::ostringstream os;
os << "hello " << 12 << "world!";
display.setFont(ArialMT_Plain_16);
display.drawString(0, 10, String(os.str().c_str()));
*/

/*
display.setFont(ArialMT_Plain_24);
display.drawString(0, 26, tempStr);
display.display();

//Serial.println(tempStr);
*/

/*******************************************************************************
 * Menu
 */

Menu::Menu(Display* display) :
m_display(display)
{
    //
}

/*******************************************************************************
 * LogoMenu
 */

void
LogoMenu::setup()
{
    oled.clear();

    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    oled.setFont(ArialMT_Plain_10);
    oled.drawString(64, 0, "Press ANY key");

    oled.drawXbm(0, Display::DISPLAY_YELLOW_HEIGHT + 1, logo_width, logo_height, logo_bits);

    oled.display();
}

void
LogoMenu::loop()
{
    delay(100);
}

void
LogoMenu::modeHandler()
{
    /*
    oled.clear();

    oled.setTextAlignment(TEXT_ALIGN_LEFT);
    oled.setFont(ArialMT_Plain_10);
    oled.drawString(0, Display::DISPLAY_YELLOW_HEIGHT + 1, "mode");

    oled.display();
    */
    m_display->setCurrentMenu(&(m_display->m_treatment));
}

void
LogoMenu::selectHandler()
{
    /*
    oled.clear();

    oled.setTextAlignment(TEXT_ALIGN_LEFT);
    oled.setFont(ArialMT_Plain_10);
    oled.drawString(0, Display::DISPLAY_YELLOW_HEIGHT + 1, "select");

    oled.display();
    */
    m_display->setCurrentMenu(&(m_display->m_treatment));
}


/*******************************************************************************
 * TreatmentMenu
 */

void
TreatmentMenu::setup()
{
    m_start = false;
}

void
TreatmentMenu::loop()
{
    oled.clear();

    oled.setFont(ArialMT_Plain_10);
    if (!m_start) {
        oled.setTextAlignment(TEXT_ALIGN_LEFT);
        oled.drawString(0, 0, "Settings");

        oled.setTextAlignment(TEXT_ALIGN_RIGHT);
        oled.drawString(128, 0, "Start");
    } else {
        oled.setTextAlignment(TEXT_ALIGN_RIGHT);
        oled.drawString(128, 0, "Stop");
    }
    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    oled.drawString(64, Display::DISPLAY_YELLOW_HEIGHT + 1, "Treatment");

    if (m_start) {
        uint32_t currentTime  = millis();
        uint32_t diffTime     = (currentTime - m_startTime) / 1000;
        uint32_t stopwatch    = duration - diffTime;
        String   stopwatchStr = String(stopwatch);

        oled.setFont(ArialMT_Plain_16);
        oled.setTextAlignment(TEXT_ALIGN_CENTER);
        oled.drawString(64, 40, stopwatchStr);
    }

    oled.display();

    delay(100);
}

void
TreatmentMenu::modeHandler()
{
    m_display->setCurrentMenu(&(m_display->m_settings));
}

void
TreatmentMenu::selectHandler()
{
    if (!m_start) {
        m_start     = true;
        m_startTime = millis();
    } else {
        m_start     = false;
    }

}


/*******************************************************************************
 * SettingsMenu
 */

void
SettingsMenu::setup()
{
    oled.clear();

    oled.setFont(ArialMT_Plain_10);
    oled.setTextAlignment(TEXT_ALIGN_LEFT);
    oled.drawString(0, 0, "Treatment");

    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    oled.drawString(64, Display::DISPLAY_YELLOW_HEIGHT + 1, "Settings");

    oled.display();
}

void
SettingsMenu::loop()
{

}

void
SettingsMenu::modeHandler()
{
    m_display->setCurrentMenu(&(m_display->m_treatment));
}

void
SettingsMenu::selectHandler()
{

}

/*******************************************************************************
 * DISPLAY
 */

const int Display::DISPLAY_YELLOW_WIDTH   = DISPLAY_WIDTH;
const int Display::DISPLAY_YELLOW_HEIGHT  = 16;

Display::Display() :
m_current(&m_logo), m_logo(this), m_treatment(this), m_settings(this)
{
    //
}

Display::~Display()
{

}

void
Display::begin()
{
    oled.init();
    oled.flipScreenVertically();

    m_current->setup();
}

void
Display::setCurrentMenu(Menu *current)
{
    m_current = current;
    current->setup();
}

Menu*
Display::getCurrentMenu()
{
    return m_current;
}
