#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

#include "FreeRTOSConfig.h"
#include "portmacro.h"
#include "list.h"

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode);
BaseType_t   xPortStartScheduler( void );

typedef struct tskTaskControlBlock
{
	volatile StackType_t    *pxTopOfStack;    /* 栈顶 */

	ListItem_t			    xStateListItem;   /* 任务节点 */
    
    StackType_t             *pxStack;         /* 任务栈起始地址 */

    TickType_t              xTicksToDelay;    /* 任务延时 */
	
    UBaseType_t			    uxPriority;       /* 任务优先级 */
}tskTCB;
typedef tskTCB TCB_t;

















#endif /* INC_FREERTOS_H */
