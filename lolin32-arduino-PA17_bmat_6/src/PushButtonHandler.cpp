/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 04.12.2017
 *
 * https://github.com/te-bachi/XXX
 */

#include "PushButtonHandler.h"
#include "Display.h"
#include "Parameters.h"

#include <Arduino.h>


void
PA17_bmat_6::modeHandler(int pin, PushButtonEvent event)
{
    /*
    Serial.print("modeHandler pin=");
    Serial.print(pin);
    Serial.print(" event=");
    Serial.println((int) event);
    */
    if (event == PUSH_BUTTON_RELEASE) {
        display.getCurrentMenu()->modeHandler();
    }
}

void
PA17_bmat_6::selectHandler(int pin, PushButtonEvent event)
{
    /*
    Serial.print("selectHandler pin=");
    Serial.print(pin);
    Serial.print(" event=");
    Serial.println((int) event);
    */
    if (event == PUSH_BUTTON_RELEASE) {
        display.getCurrentMenu()->selectHandler();
    }
}
