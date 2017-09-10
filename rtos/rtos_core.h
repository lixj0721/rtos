#ifndef __OS_CORE_H__
#define __OS_CORE_H__

#define uint32_t unsigned int

#define TASK_STACK_LENGTH  uint32_t
#define TASK_PRIO          uint32_t
#define TASK_STACK         uint32_t
#define OS_CPU_SR          uint32_t

#define  OS_USER_TASK_MAX 4
#define OS_TASK_LOWEST_PRIO (OS_USER_TASK_MAX+1)

//#define OS_TASK_LOWEST_PRIO  32

typedef struct
{
	TASK_STACK * pTaskStack;
	uint32_t     osTaskDlyTime;
	uint32_t     osTaskSwCnt;
}TASK_TCB;

void OSInit();
void OSStart();
void OSTimeDelay(uint32_t dlyTime);
void OSTaskCreate(void * pTask, uinnt8_t * pTaskStack, uint32_t taskPrio);

#endif  //__OS_CORE_H__