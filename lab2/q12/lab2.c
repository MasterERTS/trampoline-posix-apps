#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "tpl_os.h"
#include "tpl_posixvp_irq_gen.h"

int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

ISR (when_a)
{
    ActivateTask(task1);
}

ISR (when_b) 
{
    // Here we supposedly don't need to terminate t1 because we shutdown
    printf("Emergency Stop\r\n");
    CancelAlarm(halfSec);
    ShutdownOS(OSDEFAULTAPPMODE);
}

TASK (task1)
{
    static bool active = true;

    if (active) {
        printf("Waking up...\r\n");
        SetRelAlarm(halfSec, 50, 50);
    } else {
        printf("Sleeping...\r\n");
        CancelAlarm(halfSec);
    }
    active = !active;
}

TASK (task2)
{
    static bool set = true;

    if (set) {
        set_leds(GREEN);
    } else {
        reset_leds(GREEN);
    }
    set = !set;
}