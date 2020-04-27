#include <stdio.h>
#include "tpl_os.h"

StatusType status;

FUNC(int, OS_APPL_CODE) main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK(server)
{
    while(1) {
        EventMaskType received = 0x0;
        printf("==Server Task==\r\n");
        ActivateTask(task1);
        printf("Server Waiting for Event //EV_SERVER//\r\n");
        WaitEvent(ev_server_t1 | ev_server_t2 | ev_server_t3);
        GetEvent(server, &received);
        ClearEvent(received);
        if (received & ev_server_t1) {
            printf("==Server== received //EV_SERVER_T1//, Activating ==Task 1==\r\n");
            ActivateTask(task1);
        } else if (received & ev_server_t2) {
            printf("==Server== received //EV_SERVER_T2//, Activating ==Task 2==\r\n");
            ActivateTask(task2);
        } else if (received & ev_server_t3) {
            printf("==Server== received //EV_SERVER_T3//, Activating ==Task 3==\r\n");
            ActivateTask(task3);
        }
    }
    printf("Exiting server..");
    TerminateTask();
}

TASK(task1)
{
    printf("==Task 1==\r\n");
    printf("Set Event //EV_SERVER_T1//\r\n");
    SetEvent(server, ev_server_t1);
    TerminateTask();
}

TASK(task2)
{
    printf("==Task 2==\r\n");
    printf("Set Event //EV_SERVER_T2//\r\n");
    SetEvent(server, ev_server_t2);
    TerminateTask();
}

TASK(task3)
{
    printf("==Task 3==\r\n");
    printf("Set Event //EV_SERVER_T3//\r\n");
    SetEvent(server, ev_server_t3);
    TerminateTask();
}