/*******************************************************************************
 * lolin32-arduino-PA17_bmat_6 (c) 2017
 * Andreas Bachmann
 * 04.12.2017
 *
 * https://github.com/te-bachi/XXX
 */

#ifndef __PUSH_BUTTON_HANDLER_H__
#define __PUSH_BUTTON_HANDLER_H__

#include "PushButton.h"

namespace PA17_bmat_6 {
    void modeHandler(int pin, PushButtonEvent event);
    void selectHandler(int pin, PushButtonEvent event);
};

#endif
