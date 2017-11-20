/*******************************************************************************
 * nano-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 11.11.2017
 *
 * https://github.com/te-bachi/nano-PA17_bmat_6
 */

#ifndef __CLI_H__
#define __CLI_H__

class CLI;

#include "Menu.h"

class CLI {

    public:
        Menu* const      menuMain = &_menuMain;
        Menu* const      menuFile = &_menuFile;
        Menu* const      menuRun  = &_menuFile;

    private:
        Menu*       _menuCurrent;

        MenuMain    _menuMain;
        MenuFile    _menuFile;
        MenuRun     _menuRun;

    public:

                    CLI();
        virtual     ~CLI();

        bool        begin();
        void        check();
        void        updateCurrentMenu(Menu *menuCurrent);
        Menu*       getCurrentMenu();
};

#endif
