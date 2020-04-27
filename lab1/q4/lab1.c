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
	printf("Hello world\r\n");
    ActivateTask(task3);
    status = ChainTask(task2);
    if (status != 0) printf("ChainTask(task2) failed. Status of ChainTask : %d\r\n", status);
}

TASK(task2)
{
    printf("== Task 2 ==\r\n");
    printf("ChainTask(task2) succeeded. State of ChainTask : %d\r\n", status);
    TerminateTask();
}

TASK(task3)
{
    printf("== Task 3 ==\r\n");
    TerminateTask();
}