#ifndef Rs485_h
#define Rs485_h

#include <inttypes.h>

#include "HardwareSerial.h"
#include "esp32-hal.h"

class Rs485 : public HardwareSerial
{
    public:
        Rs485(int uart_nr);

        int printRegStatus();
};

#endif
