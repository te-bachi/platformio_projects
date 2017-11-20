/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __CLI_H__
#define __CLI_H__

class CLI;

#include "Menu.h"

class CLI {
    
    public:
        Menu*       current;
        
        MenuMain    main;
        MenuFile    file;
        MenuRun     run;
        
    public:
                    
                    CLI();
        virtual     ~CLI();

        bool        begin();
        void        update();
};

#endif

