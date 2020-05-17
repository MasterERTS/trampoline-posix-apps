#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "tpl_os.h"
#include "tpl_posixvp_irq_gen.h"

DeclareMessage(from_t1);
DeclareMessage(from_t2);
DeclareMessage(for_receive1);
DeclareMessage(for_receive2);


int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK (task1)
{
    static unsigned int cnt = 0;
    ++cnt;
    SendMessage(from_t1, &cnt);
    TerminateTask();
}

TASK (task2) 
{
    static unsigned int cnt = 0;
    ++cnt;
    SendMessage(from_t2, &cnt);
    TerminateTask();
}

TASK (receive)
{
    static unsigned int rec1, rec2;
    static int ok1, ok2;
    ok1 = ReceiveMessage(for_receive1, &rec1);
    ok2 = ReceiveMessage(for_receive2, &rec2);

    if (ok1 == 0) printf("Task 1 activated %u times.\r\n", rec1);
    else if (ok2 == 0) printf("Task 2 activated %u times.\r\n", rec2);
    TerminateTask();
}
