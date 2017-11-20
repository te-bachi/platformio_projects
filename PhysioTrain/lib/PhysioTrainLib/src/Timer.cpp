/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 13.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#if 0

#include "Timer.h"
#include "avdweb_SAMDtimer.h"

void ISR_timer4_LED2(struct tc_module *const module_inst);

static int time = 0;

SAMDtimer timer4_2Hz = SAMDtimer(4, ISR_timer4_LED2, 1e5);

Timer::Timer()
{
}

Timer::~Timer()
{

}

void
Timer::begin()
{

}

int
Timer::getTime()
{
    int value;

    cpu_irq_enter_critical();
    value = time;
    cpu_irq_leave_critical();

    return value;
}

void
ISR_timer4_LED2(struct tc_module *const module_inst)
{
    time += 100;
}

#endif
