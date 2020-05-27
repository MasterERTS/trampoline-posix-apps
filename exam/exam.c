#include <stdio.h>
#include <stdbool.h>
#include "tpl_os.h"
#include <stdlib.h>


volatile int val = 0;
volatile int activationCount = 0;

FUNC(int, OS_APPL_CODE) main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK(t_event_a_or_b)
{
	printf("start background task\r\n");
	unsigned int i = 0;
	while(1)
	{
		EventMaskType received = 0x0;
		WaitEvent(ev_a | ev_b);
		GetEvent(t_event_a_or_b, &received);
		ClearEvent(received);
		if ((received & ev_a) || (received & ev_b))
		{
			i++;
			printf("%d\r\n", i);
			if (i > 9) ShutdownOS(OSDEFAULTAPPMODE);
		}
	}
    TerminateTask();
}

TASK(t_periodic_40ms)
{
	// Let us assume rand() % 255 is uint8_t critical_40ms() [ rand % 255 always on 8 bits (0-255 range) ]
	unsigned int x = rand() % 255;
	if (x < 50) SetEvent(t_event_a_or_b, ev_b);
	TerminateTask();
}

TASK(t_periodic_60ms)
{
	// Let us assume rand() % 255 is uint8_t critical_60ms() [ rand % 255 always on 8 bits (0-255 range) ]
	unsigned int x = rand() % 255;
	if (x > 200) SetEvent(t_event_a_or_b, ev_a);
	TerminateTask();
}
