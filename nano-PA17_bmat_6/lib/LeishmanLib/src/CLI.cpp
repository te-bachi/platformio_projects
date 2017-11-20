/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

#include "config.h"
#include "CLI.h"

CLI::CLI()
{
    //
}

CLI::~CLI()
{
    //
}

bool
CLI::begin()
{
    _menuMain.begin(this);
    //menuMain = &_menuMain;

    _menuFile.begin(this);
    //menuFile = &_menuFile;

    _menuRun.begin(this);
    //menuRun = &_menuRun;

    _menuCurrent = &_menuMain;

    return true;
}

void
CLI::check()
{
    // Checks for new serial input:
    if (Serial.available()) {
        // If new input is available on serial port
        _menuCurrent->parse(Serial.read());
    }
}

void
CLI::updateCurrentMenu(Menu *menuCurrent)
{
    _menuCurrent = menuCurrent;
}

Menu*
CLI::getCurrentMenu()
{
    return _menuCurrent;
}
