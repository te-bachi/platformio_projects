/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "Menu.h"
#include "CLI.h"


/*******************************************************************************
 * Menu
 ******************************************************************************/

Menu::Menu()
: _cli(NULL)
{
    //
}

Menu::Menu(CLI* cli)
: _cli(cli)
{
    //
}

Menu::~Menu()
{
    //
}

bool
Menu::begin(CLI* cli)
{
    _cli = cli;
    return true;
}

void
Menu::listItems()
{
    Serial.println("Menu");
}

void
Menu::parse(char c)
{
    //
}

 /*******************************************************************************
 * MenuMain
 ******************************************************************************/

MenuMain::MenuMain()
{
    //
}

MenuMain::MenuMain(CLI* cli)
{
    _cli = cli;
}

MenuMain::~MenuMain()
{
    //
}

bool
MenuMain::begin(CLI* cli)
{
    _cli = cli;
    return true;
}

void
MenuMain::listItems()
{
    Serial.println("=== MAIN ===");
    Serial.println(" [F] File ");
    Serial.println(" [R] Run ");
}

void
MenuMain::parse(char c)
{
    switch (c) {
        case MenuMain::MENU_FILE:
            _cli->current = &(_cli->file);
            break;
            
        case MenuMain::MENU_RUN:
            _cli->current = &(_cli->run);
            break;

        default:
            return;
    }
    _cli->current->listItems();
}

 /*******************************************************************************
 * MenuFile
 ******************************************************************************/

MenuFile::MenuFile()
{
    //
}

MenuFile::MenuFile(CLI* cli)
{
    _cli = cli;
}

MenuFile::~MenuFile()
{
    //
}

bool
MenuFile::begin(CLI* cli)
{
    _cli = cli;
    return true;
}

void
MenuFile::listItems()
{
    Serial.println("=== FILE ===");
    Serial.println(" [M] Main Menu ");
    Serial.println(" [N] Next File ");
}

void
MenuFile::parse(char c)
{
    switch (c) {
        case MenuFile::MENU_NEXT:
            break;
            
        case MenuFile::MENU_MAIN:
            _cli->current = &(_cli->main);
            break;

        default:
            return;
    }
    _cli->current->listItems();
}

 /*******************************************************************************
 * MenuRun
 ******************************************************************************/

MenuRun::MenuRun()
{
    //
}

MenuRun::MenuRun(CLI* cli)
{
    _cli = cli;
}

MenuRun::~MenuRun()
{
    //
}

bool
MenuRun::begin(CLI* cli)
{
    _cli = cli;
    return true;
}

void
MenuRun::listItems()
{
    Serial.println("=== RUN ===");
    Serial.println(" [M] Main Menu ");
    Serial.println(" [S] Start/Stop Capture ");
}

void
MenuRun::parse(char c)
{
    switch (c) {
        case MenuRun::MENU_START_STOP:
            if (!_start) {
                Serial.println(" Start motion");
                _start = true;
            } else {
                Serial.println(" Stop motion");
                _start = false;
            }
            break;
            
        case MenuRun::MENU_MAIN:
            _cli->current = &(_cli->main);
            break;

        default:
            return;
    }
    _cli->current->listItems();
}

