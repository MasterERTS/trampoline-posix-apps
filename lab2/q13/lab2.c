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
    static bool active = true;
    if (active) {
        SetEvent(server, wakeup);
        printf("Set Event |WAKEUP|\r\n");
    } else {
        SetEvent(server, sleeping);
        printf("Set Event |SLEEP|\r\n");
    }
    active = !active;
}

ISR (when_b) 
{
    SetEvent(server, terminate);
    printf("Set Event |TERMINATE|\r\n");
    ActivateTask(server);
}

TASK (server)
{
    printf("== Server ==\r\n");
    static bool state = false;
    EventMaskType received = 0x0;
    WaitEvent(wakeup | sleeping | terminate);
    GetEvent(server, &received);
    ClearEvent(received);
    if ((received & wakeup) && (state == false))
    {
        // Wake Up
        state = true;
        printf("wake up\r\n");
        SetRelAlarm(halfSec, 50, 50);
    }
    if ((received & sleeping) && (state == true))
    {
        // Sleep
        state = false;
        printf("sleep\r\n");
        CancelAlarm(halfSec);
    }
    if (received & terminate)
    {
        // Terminate
        state = false;
        printf("shutdown\r\n");
        CancelAlarm(halfSec);
        ShutdownOS(OSDEFAULTAPPMODE);
    }
    TerminateTask();
}

TASK (task1)
{
    static bool set = true;

    if (set) {
        set_leds(GREEN);
    } else {
        reset_leds(GREEN);
    }
    set = !set;
}
