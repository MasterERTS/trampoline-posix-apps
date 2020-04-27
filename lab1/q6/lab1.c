#include <stdio.h>
#include "tpl_os.h"

StatusType status;

FUNC(int, OS_APPL_CODE) main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK(task1)
{
	printf("== Task 1 ==\r\n");
    ActivateTask(task2);
    ActivateTask(task3);
    printf("== Task 1 ==\r\n");
    printf("Set Event //EV2//\r\n");
    SetEvent(task2, ev2);
    printf("== Task 1 ==\r\n");
    printf("Set Event //EV3//\r\n");
    SetEvent(task3, ev3);
}

TASK(task2)
{
    printf("== Task 2 ==\r\n");
    EventMaskType received = 0x0;
    printf("Waiting for Event //EV2//\r\n");
    WaitEvent(ev2);
    printf("== Task 2 ==\r\n");
    GetEvent(task2, &received);
    printf("Received Event //EV2//\r\n");
    ClearEvent(received);
    TerminateTask();
}

TASK(task3)
{
    printf("== Task 3 ==\r\n");
    EventMaskType received = 0x0;
    printf("Waiting for Event //EV3//\r\n");
    WaitEvent(ev3);
    printf("== Task 3 ==\r\n");
    GetEvent(task3, &received);
    printf("Received Event //EV3//\r\n");
    ClearEvent(received);
    TerminateTask();
}