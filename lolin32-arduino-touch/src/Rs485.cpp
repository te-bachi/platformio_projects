
#include "Rs485.h"

#include "soc/uart_reg.h"
#include "soc/uart_struct.h"

//#define UART_MUTEX_LOCK()    do {} while (xSemaphoreTake(_uart->lock, portMAX_DELAY) != pdPASS)
//#define UART_MUTEX_UNLOCK()  xSemaphoreGive(_uart->lock)

Rs485::Rs485(int uart_nr) : HardwareSerial(uart_nr)
{
    //
}

int
Rs485::printRegStatus()
{
    int ret;
    if(_uart == NULL) {
        return -1;
    }
    /*
    UART_MUTEX_LOCK();
    ret = _uart->dev->status;
    UART_MUTEX_UNLOCK();
    */

    return ret;
}
