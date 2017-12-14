/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 12.12.2017
 *
 * https://github.com/te-bachi/XXX
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>
#include <Arduino.h>

#include "Dimmer.h"

namespace PA17_bmat_6 {

    class Display;

    class Menu {

        private:

        protected:
            Display*            m_display;

        public:
                                Menu(Display* display);
            virtual             ~Menu() {};

            virtual void        setup() = 0;
            virtual void        loop() = 0;
            virtual void        modeHandler() = 0;
            virtual void        selectHandler() = 0;
    };

    class LogoMenu : public Menu {

        private:

        public:
                                LogoMenu(Display* display) : Menu(display) {};
            virtual             ~LogoMenu() {};

            virtual void        setup();
            virtual void        loop();
            virtual void        modeHandler();
            virtual void        selectHandler();
    };

    class TreatmentMenu : public Menu {

        private:
            bool                m_start;                /*< treatment started? */
            bool                m_tempReached;          /*< target temperature reached? */
            uint32_t            m_duration;             /*< copy from parameters when start treatment */
            double              m_targetTemp;           /*< copy from parameters when start treatment (convert to double) */
            uint32_t            m_startTime;            /*< set start time when current temperature reaches target  */
            uint32_t            m_lastTime;             /*< last time the */
            String              m_thermopileTempStr;    /*< current temperature as string to present to display */
            Dimmer::Value       m_currentDimmerValue;   /*< current dimmer value */

        public:
                                TreatmentMenu(Display* display) : Menu(display) {};
            virtual             ~TreatmentMenu() {};

            virtual void        setup();
            virtual void        loop();
            virtual void        modeHandler();
            virtual void        selectHandler();
    };

    class SettingsMenu : public Menu {

        private:
            enum Submenu {
                NONE = 0,
                PARAMETERS,
                WIFI,
                ACCESS,
            };

            static const char      *RIGHT_SUBMENU[];
            static const char      *TITLE[];
            static const Submenu    NEXT[];
            Submenu                 m_submenu;

        public:
                                SettingsMenu(Display* display) : Menu(display) {};
            virtual             ~SettingsMenu() {};

            virtual void        setup();
            virtual void        loop();
            virtual void        modeHandler();
            virtual void        selectHandler();
    };

    class Display {

        friend class Menu;
        friend class LogoMenu;
        friend class TreatmentMenu;
        friend class SettingsMenu;

        public:
            static const int DISPLAY_YELLOW_WIDTH;
            static const int DISPLAY_YELLOW_HEIGHT;

        private:
            Menu*           m_current;

            LogoMenu        m_logo;
            TreatmentMenu   m_treatment;
            SettingsMenu    m_settings;

        public:

                        Display();
            virtual     ~Display();

            void        begin();
            void        setCurrentMenu(Menu *current);
            Menu*       getCurrentMenu();
    };
};

#endif
