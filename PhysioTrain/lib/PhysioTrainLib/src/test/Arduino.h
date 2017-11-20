
#ifndef ARDUINO

#include <stdint.h>

extern "C" {

    #define byte char
    #define LOW 0
    #define HIGH 1
    #define INPUT_PULLUP 1
    static inline void pinMode( uint32_t ulPin, uint32_t ulMode )
    {

    }

}

#endif
