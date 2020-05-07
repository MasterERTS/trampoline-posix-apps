#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "tpl_os.h"
#include "tpl_posixvp_irq_gen.h"

volatile bool revert = false;
volatile bool active = true;
volatile int i = 0;

int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

ISR (when_a)
{
    if (revert) {
        i = 2;
    } else {
        i = 0;
    }
    
    if (!active) {
        SetRelAlarm(chasePeriod, 50, 50);
        active = true;
    }
}

ISR (when_b)
{
    if (active) 
    {
        CancelAlarm(chasePeriod);
        active = false;
    } else {
        revert = !revert;
        active = true;
        SetRelAlarm(chasePeriod, 50, 50);
    }
}

TASK (chase)
{
    if (!revert && active) {
        if (i == 0) {
            reset_leds(BLUE);
            set_leds(RED);
            i++;
        } else if (i == 1) {
            reset_leds(RED);
            set_leds(GREEN);
            i++;
        } else if (i == 2) {
            reset_leds(GREEN);
            set_leds(BLUE);
            i = 0;
        }
    } else if (revert && active) {
        if (i == 2) {
            reset_leds(RED);
            set_leds(BLUE);
            i--;
        } else if (i == 1) {
            reset_leds(BLUE);
            set_leds(GREEN);
            i--;
        } else if (i == 0) {
            reset_leds(GREEN);
            set_leds(RED);
            i = 2;
        }
    }
    
    
}