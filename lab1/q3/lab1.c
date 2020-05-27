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
    status = ChainTask(task2);
    ActivateTask(task3);
}

TASK(task2)
{
    printf("== Task 2 ==\r\n");
    printf("%d\r\n", status);
    TerminateTask();
}

TASK(task3)
{
    printf("== Task 3 ==\r\n");
    TerminateTask();
}