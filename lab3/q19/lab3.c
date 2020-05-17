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
	static bool initizalized;
	if (!initizalized) {
		printf("start background task\r\n");
		initizalized = true;
	}
	static bool state = true;
	if (val < 0 && state == false) state = true;
	if (val > 50 && state == true) state = false;

	if (state) val++;
	if (!state) val--;
	ChainTask(bgTask);
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
	//printf("I was here\r\n");
	TerminateTask();
}

TASK(displayTask)
{
	printf("%d\r\n", val);
	TerminateTask();
}
