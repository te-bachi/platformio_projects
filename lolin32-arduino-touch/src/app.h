#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void app_create(lv_obj_t *parent);
void app_temp_current_set(float temp);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*APP_H*/