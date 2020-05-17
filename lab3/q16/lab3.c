#include <stdio.h>
#include <stdbool.h>
#include "tpl_os.h"

volatile int val = 0;
volatile int activationCount = 0;

FUNC(int, OS_APPL_CODE) main(void)
{
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

TASK(bgTask)
{
	printf("start background task\r\n");
	static bool state = true;
	while(1)
	{
		if (val < 0 && state == false) state = true;
		if (val > 50 && state == true) state = false;

		if (state) val++;
		if (!state) val--;
	
	}
    TerminateTask();
}

TASK(periodicTask)
{
	activationCount++;
	if ((activationCount % 2) == 0) 
	{
		val--;
	} else {
		val++;
	}
	printf("I was here\r\n");
	TerminateTask();
}

TASK(displayTask)
{
	printf("%d\r\n", val);
	TerminateTask();
}
