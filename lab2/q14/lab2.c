#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "tpl_os.h"
#include "tpl_posixvp_irq_gen.h"

bool a_pressable = true;

int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

ISR (when_a)
{
    printf("Pressed A\r\n");
    if (a_pressable == true) {
        SetRelAlarm(clockFour, 400, 400);
        SetRelAlarm(clockFive, 500, 500);
        a_pressable = false;
    }
}

ISR (when_b)
{
    if (a_pressable == false) 
    {
        printf("Pressed B\r\n");
        long unsigned int* ptr;
        GetAlarm(clockFour, ptr);
        CancelAlarm(clockFour);
        printf("%ld", *ptr);
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
