#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "tpl_os.h"
#include "tpl_posixvp_irq_gen.h"

volatile bool a_pressable = true;

int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

ISR (when_a)
{
    if (a_pressable == true) {
        printf("Pressed A\r\n");
        SetRelAlarm(clockFour, 400, 0);
        SetRelAlarm(clockFive, 500, 0);
        a_pressable = false;
    }
}

ISR (when_b)
{
    TickType val;
    if (a_pressable == false && GetAlarm(clockFour, &val) == 0) 
    {
        printf("Pressed B\r\n");
        GetAlarm(clockFour, &val);
        printf("Time since pressed A : %ld\r\n", 400 - val);
        CancelAlarm(clockFour);
    }
}

TASK (server)
{
    printf("=== Starting... ===\r\n");
}

TASK (task1)
{
    printf("Error : You didn't press 'b' before 4 seconds\r\n");
    CancelAlarm(clockFour);
}

TASK (task2)
{
    printf("You can press 'a' again.\r\n");
    a_pressable = true;
    CancelAlarm(clockFive);
}
