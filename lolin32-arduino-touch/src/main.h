
#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"

extern QueueHandle_t qTempCurrent;

void taskTempCurrentGet(void *parameter);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*MAIN_H*/

