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
    ActivateTask(task1);
    for(int i = 0 ; i < 6 ; i++) {
        EventMaskType received = 0x0;
        printf("==Server Task==\r\n");
        printf("Server Waiting for Event //EV_SERVER//\r\n");
        WaitEvent(ev_server);
        GetEvent(server, &received);
        ClearEvent(received);
        if (received & ev_server) {
            printf("==Server== received //EV_SERVER//, Activating ==Task 1==\r\n");
            ActivateTask(task1);
        }
    }
    TerminateTask();
}

TASK(task1)
{
    printf("==Task 1==\r\n");
    printf("Set Event //EV_SERVER//\r\n");
    SetEvent(server, ev_server);
    TerminateTask();
}