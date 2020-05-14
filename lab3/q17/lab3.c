#include <stdio.h>
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
	while(1)
	{
		GetResource(Res_Val);
		if (val < 100) 
		{
			val++;
		}
		else if (val >= 100) 
		{
			val--;
		}
		ReleaseResource(Res_Val);
	}
    TerminateTask();
}

TASK(periodicTask)
{
	activationCount++;
	GetResource(Res_Val);
	if ((activationCount % 2) == 0) 
	{
		val--;
	} else {
		val++;
	}
	ReleaseResource(Res_Val);
	TerminateTask();
}

TASK(displayTask)
{
	printf("%d\r\n", val);
	TerminateTask();
}
