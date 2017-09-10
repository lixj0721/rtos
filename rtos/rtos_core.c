#include "os_core.h"

TASK_PRIO OSPrioCur, OSPrioHighRdy, OSPrioRdyTable;
TASK_TCB   *OSHighRdyTCB;
TASK_TCB   *OSTCBPrioCur;
TASK_TCB   OSTaskTCBTable[OS_USER_TASK_MAX+1];
uint32_t   OSNesting;
uint32_t   OSTaskSWCnt;

#define  OS_ENTER_CRITICAL()   {cpu_sr = OS_CPU_SR_Save();}
#define  OS_EXIT_CRITICAL()    {OS_CPU_SR_Restore(cpu_sr);}

#define Task_Sw() OSCtxSw()

void OSInit()
{
	
}

void OSStart()
{

}

void OSGetHighRdy()
{
	uint32_t tempi;
	for(tempi=0;tempi<OS_TASK_LOWEST_PRIO;tempi++)
	{
		if((OSPrioRdyTable>>tempi)&0x01!=0)
			OSPrioHighRdy = tempi;
	}
}

void  OS_Sched (void)
{
	OS_CPU_SR  cpu_sr = 0u;

	OS_ENTER_CRITICAL()
	if(OSNesting==0)
	{
		OSGetHighRdy();
		if(OSPrioHighRdy != OSPrioCur)
		{
			OSTaskSWCnt++;
			OSHighRdyTCB->osTaskSwCnt++;
			Task_Sw();
		}
	}
	OS_EXIT_CRITICAL();
}

void OSTaskCreate(void * pTask, uinnt8_t * pTaskStack, uint32_t taskPrio)
{
	
}

void OSTimeDelay(uint32_t dlyTime)
{
    OS_CPU_SR  cpu_sr = 0u;
	if(OSNesting>0)
		return;
	
	if(dlyTime>0)
	{
		OS_ENTER_CRITICAL();
		OSTCBPrioCur->osTaskDlyTime = dlyTime;
		OS_EXIT_CRITICAL();
		OS_Sched();
	}
}