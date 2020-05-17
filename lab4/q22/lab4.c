#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "tpl_os.h"
#include "tpl_posixvp_irq_gen.h"

DeclareMessage(from_send);
DeclareMessage(for_receive_auto);
DeclareMessage(for_receive_event);


int main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK (send) 
{
    static unsigned int data;
    data = rand() % 100; // Note that using this method throws the uniformity of rand()
    SendMessage(from_send, &data);
    SetEvent(t_event, new_value);
    TerminateTask();
}

TASK (t_event)
{
    static unsigned int data;
    static unsigned int sum;
    static unsigned int data_array[10];
    static unsigned int index = 0;
    static unsigned int n_elems = 0;

    EventMaskType received = 0x0;
    WaitEvent(new_value);
    GetEvent(t_event, &received);
    ClearEvent(received);

    if (received & new_value)
    {
        // Event is ok, receive message
        ReceiveMessage(for_receive_event, &data);

        // Store the data to record the last 10 values
        data_array[index] = data;
        if (n_elems < 10) ++n_elems;

        // Compute sum of the last 10 or less recorded data
        sum = 0;
        for (int i = 0; i < 10; ++i) {
            sum += data_array[i];
        }

        float average = sum/n_elems;

        // The index is to emulate a FIFO (bumping the first in, then go to the n+1)
        index++;
        if (index > 9) index = 0;
        printf("Average over last 10 values == %2.f\r\n", average);
    }
    TerminateTask();
}

TASK (receive)
{
    static unsigned int data;
    ReceiveMessage(for_receive_auto, &data);
    printf("New value == %d\r\n", data);
    TerminateTask();
}
