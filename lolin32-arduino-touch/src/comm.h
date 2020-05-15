#ifndef COMM_H
#define COMM_H

#ifdef __cplusplus
extern "C" {
#endif

void comm_power_on();
void comm_power_off();
float comm_temp_current_get();
void comm_temp_target_set(int temp);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*COMM_H*/