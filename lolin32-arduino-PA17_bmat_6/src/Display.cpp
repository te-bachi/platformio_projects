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
#include <string>
#include <sstream>

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

    oled.drawXbm(0, Display::DISPLAY_YELLOW_HEIGHT, logo_width, logo_height, logo_bits);

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
    oled.drawString(64, Display::DISPLAY_YELLOW_HEIGHT, "Treatment");

    if (m_start) {
        uint32_t currentTime    = millis();                             /* in milliseconds */
        uint32_t diffTimeStart  = currentTime - m_startTime;            /* in milliseconds */
        uint32_t diffTimeLast   = currentTime - m_lastTime;             /* in milliseconds */
        uint32_t s              = duration - (diffTimeStart / 1000);    /* in seconds */
        uint32_t m              = int(s / 60);                          /* in minutes */

        s = s - (m * 60);

        if (s == 0 && m == 0) {
            m_start = false;
        }

        /* Convert number to string in format MM:SS */
        std::ostringstream buffer;
        if (s < 10) {
            buffer << std::to_string(m) << ":0" << std::to_string(s);
        } else {
            buffer << std::to_string(m) << ":" << std::to_string(s);
        }
        String stopwatchStr = String(buffer.str().c_str());

        oled.setFont(ArialMT_Plain_16);
        oled.setTextAlignment(TEXT_ALIGN_LEFT);
        oled.drawString(0, 40, stopwatchStr);

        /* Update */
        if (diffTimeLast > 500) {
            m_lastTime          = currentTime;
            m_thermopileTempStr = String(thermopile.readObjectTempC()) + "°";
        }
        oled.setFont(ArialMT_Plain_16);
        oled.setTextAlignment(TEXT_ALIGN_RIGHT);
        oled.drawString(128, 40, m_thermopileTempStr);
    }

    oled.display();

    delay(100);
}

void
TreatmentMenu::modeHandler()
{
    if (!m_start) {
        m_display->setCurrentMenu(&(m_display->m_settings));
    }
}

void
TreatmentMenu::selectHandler()
{
    if (!m_start) {
        m_start             = true;
        m_startTime         = millis();
        m_lastTime          = m_startTime;
        m_thermopileTempStr = String(thermopile.readObjectTempC()) + "°";
    } else {
        m_start             = false;
    }

}


/*******************************************************************************
 * SettingsMenu
 */

const char *SettingsMenu::RIGHT_SUBMENU[] = {
    [NONE]          = "Parameters",
    [PARAMETERS]    = "Wifi",
    [WIFI]          = "Access",
    [ACCESS]        = "Parameters",
};

const char *SettingsMenu::TITLE[] = {
    [NONE]          = "Settings",
    [PARAMETERS]    = "Parameters",
    [WIFI]          = "WiFi",
    [ACCESS]        = "Access",
};

void
SettingsMenu::setup()
{
    m_submenu = NONE;
}

void
SettingsMenu::loop()
{
    oled.clear();

    /* Left menu */
    oled.setFont(ArialMT_Plain_10);
    oled.setTextAlignment(TEXT_ALIGN_LEFT);
    oled.drawString(0, 0, "Treatment");

    /* Right menu */
    oled.setFont(ArialMT_Plain_10);
    oled.setTextAlignment(TEXT_ALIGN_RIGHT);
    oled.drawString(128, 0, RIGHT_SUBMENU[m_submenu]);

    /* Title */
    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    oled.drawString(64, Display::DISPLAY_YELLOW_HEIGHT, TITLE[m_submenu]);

    /* Content */
    oled.setFont(ArialMT_Plain_10);
    oled.setTextAlignment(TEXT_ALIGN_LEFT);
    if (m_submenu == NONE) {
        //
    } else if (m_submenu == PARAMETERS) {
        uint32_t s = duration;      /* in seconds */
        uint32_t m = int(s / 60);   /* in minutes */

        s = s - (m * 60);

        /* Convert number to string in format MM:SS */
        String d;
        if (s < 10) {
            d = String(m) + ":0" + String(s);
        } else {
            d = String(m) + ":" + String(s);
        }
        String t = String(temperature) + "°";
        oled.drawString( 0, 35, "Duration");
        oled.drawString(65, 35, d);
        oled.drawString( 0, 45, "Temperatur");
        oled.drawString(65, 45, t);
    } else if (m_submenu == WIFI) {
        oled.drawString( 0, 35, "SSID");
        oled.drawString(50, 35, String(ssid));
        oled.drawString( 0, 45, "Password");
        oled.drawString(50, 45, String(password));
    } else if (m_submenu == ACCESS) {
        oled.setTextAlignment(TEXT_ALIGN_CENTER);
        String url = String("http://") + myIP.toString() + "/";
        oled.drawString(64, 45, url);
    }

    oled.display();

    delay(100);
}

void
SettingsMenu::modeHandler()
{
    m_display->setCurrentMenu(&(m_display->m_treatment));
}

void
SettingsMenu::selectHandler()
{
    if (m_submenu == NONE) {
        m_submenu = PARAMETERS;
    } else if (m_submenu == PARAMETERS) {
        m_submenu = WIFI;
    } else if (m_submenu == WIFI) {
        m_submenu = ACCESS;
    } else if (m_submenu == ACCESS) {
        m_submenu = PARAMETERS;
    }
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
