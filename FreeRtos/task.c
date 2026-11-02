
#include "gpio.h"
#include "iwdt.h"

#include "driver_rtc.h"
#include "driver_adc.h"
#include "driver_gpio.h"
#include "driver_iwdt.h"
#include "driver_uart.h"
#include "driver_timer.h"
#include "driver_lptim.h"
#include "driver_flash.h"
#include "driver_lpuart.h"
#include "driver_pwm.h"

#include "stdio.h"

#include "main.h"
#include "bsp_key.h"
#include "bsp_gas.h"
#include "bsp_log.h"
#include "bsp_part.h"
#include "bsp_valve.h"
#include "bsp_queue.h"
#include "bsp_eeprom.h"
#include "bsp_factory.h"
#include "bsp_sound_led.h"

#include "bsp_protocol_fct.h"
#include "bsp_temperature.h"
#include "bsp_string.h"
#include "bsp_module.h"


#include "FreeRTOS.h"
#include "task.h"

/* 当前正在运行的任务的任务控制块指针，默认初始化为NULL */
TCB_t * volatile pxCurrentTCB = NULL;
List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

static List_t xDelayedTaskList1;
static List_t xDelayedTaskList2;
static List_t xSuspendedTaskList;
static List_t * volatile pxDelayedTaskList;
static List_t * volatile pxOverflowDelayedTaskList;
static volatile UBaseType_t uxTopReadyPriority = tskIDLE_PRIORITY;

#define IdleTaskStackSize  128
StackType_t IdleTaskStack[IdleTaskStackSize]  __attribute__((aligned(4)));
TCB_t IdleTaskTCB;
/*------------------------------------------------------------------------------------
Function:  函数声明
------------------------------------------------------------------------------------*/
void prvInitialiseTaskLists( void );                                 
static void prvAddNewTaskToReadyList( TCB_t *pxNewTCB );
                                  
void vTaskSwitchContext( void ); 
static void prvResetNextTaskUnblockTime( void );  
static void prvAddCurrentTaskToDelayedList( TickType_t xTicksToWait ); 

/*------------------------------------------------------------------------------------
Function: 
------------------------------------------------------------------------------------*/
void Idle_Entry(void *p_arg)	
{	
	for(;;)
    {
		/* 就绪任务链表节点数 */
		if(( &( pxReadyTasksLists[ tskIDLE_PRIORITY ]))->uxNumberOfItems >0 )
		{		
			taskYIELD();
		}	
    }
}
/*--------------------------------------------------------------------------------------------------
Function: 
--------------------------------------------------------------------------------------------------*/
void xTask_init(void)
{
    xNextTaskUnblockTime = portMAX_DELAY;
    xTickCount = ( TickType_t ) 0U;	
	
	prvInitialiseTaskLists();
    //创建空闲任务 	
	xTaskCreateStatic( (TaskFunction_t)Idle_Entry,     /* 任务入口 */
	                   (char *)"Idle",                 /* 任务名称，字符串形式 */
					   (uint32_t)IdleTaskStackSize ,   /* 任务栈大小，单位为字 */
					   (void *) NULL,                  /* 任务形参 */	
					   (UBaseType_t) tskIDLE_PRIORITY, /* 任务优先级，数值越大，优先级越高 */
					   (StackType_t *)IdleTaskStack,   /* 任务栈起始地址 */
					   (TCB_t *)&IdleTaskTCB );        /* 任务控制块 */										 								 
}	                               
/*--------------------------------------------------------------------------------------------------
Function: 
--------------------------------------------------------------------------------------------------*/
void xTaskCreateStatic(	TaskFunction_t pxTaskCode,           /* 任务入口 */
	                    const char * const pcName,           /* 任务名称，字符串形式 */
					    const uint32_t ulStackDepth,         /* 任务栈大小，单位为字 */
						void * const pvParameters,           /* 任务形参 */	
                        UBaseType_t uxPriority,              /* 任务优先级，数值越大，优先级越高 */
					    StackType_t * const puxStackBuffer,  /* 任务栈起始地址 */
					    TCB_t * const pxTaskBuffer )         /* 任务控制块 */
{
	TCB_t *pxNewTCB;	
    StackType_t *pxTopOfStack;
		
	pxNewTCB = ( TCB_t * ) pxTaskBuffer;                     //赋值任务块
	pxNewTCB->pxStack = ( StackType_t * ) puxStackBuffer;    //任务块加入任务栈起始地址

	/* 创建新的任务 */
	/* 获取栈顶地址 */
	pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1 );   
	/* 向下做8字节对齐 */
	pxTopOfStack = ( StackType_t * ) ( ( ( uint32_t ) pxTopOfStack ) & ( ~( ( uint32_t ) 0x0007 ) ) );	  		
	
	pxNewTCB->xStateListItem.pvContainer = NULL;             //链表前一个节点
	pxNewTCB->xStateListItem.pvOwner = pxNewTCB ;            //任务控制块
	
	/* 初�?�化优先�? */
	if( uxPriority >= ( UBaseType_t ) configMAX_PRIORITIES )
	{
		uxPriority = ( UBaseType_t ) configMAX_PRIORITIES - ( UBaseType_t ) 1U;
	}
	/* 任务优先级 */
	pxNewTCB->uxPriority = uxPriority;                      
	/* 初始化任务栈 ，返回任务栈位置 */                                       
	pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, pxTaskCode); 
	/* 将任务添加到就绪列表 */
	prvAddNewTaskToReadyList( pxNewTCB );
}
/*--------------------------------------------------------------------------------------------------
Function: 
--------------------------------------------------------------------------------------------------*/
static void prvAddNewTaskToReadyList( TCB_t *pxNewTCB )
{	
    uint32_t ulPreviousMask;
	/* 关中断 */
    ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();	

	/* 如果pxCurrentTCB为空，则将pxCurrentTCB指向新创建的任务 */
	if( pxCurrentTCB == NULL )
	{
		pxCurrentTCB = pxNewTCB;
	}
	/* 如果pxCurrentTCB不为空，则根据任务的优先级将pxCurrentTCB指向最高优先级任务的TCB */
	else 
	{
		if( pxCurrentTCB->uxPriority <= pxNewTCB->uxPriority )  
		{
			pxCurrentTCB = pxNewTCB;
		}
	}

	uxTopReadyPriority |= 1UL<< ( ( pxNewTCB )->uxPriority );											    
	/* 将节点插入到链表的尾部 */
	vListInsertEnd( &( pxReadyTasksLists[ ( pxNewTCB )->uxPriority ]) ,&( ( pxNewTCB )->xStateListItem ));		
    /* 开中断 */
	portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );		
	
}
/*--------------------------------------------------------------------------------------------------
Function: 初�?�化任务相关的列�?
--------------------------------------------------------------------------------------------------*/
void prvInitialiseTaskLists( void )
{
    UBaseType_t uxPriority;
    
    /* 初始化就绪列表 */
    for( uxPriority = ( UBaseType_t ) 0U; uxPriority < ( UBaseType_t ) configMAX_PRIORITIES ; uxPriority++ )
	{
		/* 链表初始化 */
		vListInitialise( &( pxReadyTasksLists[ uxPriority ] ) );
	}
    
    vListInitialise( &xDelayedTaskList1 );
	vListInitialise( &xDelayedTaskList2 );
	vListInitialise( &xSuspendedTaskList );
    
    pxDelayedTaskList = &xDelayedTaskList1;
	pxOverflowDelayedTaskList = &xDelayedTaskList2;
}
/*--------------------------------------------------------------------------------------------------
Function: 任务切换，即寻找优先级最高的就绪任务 
--------------------------------------------------------------------------------------------------*/
void vTaskSwitchContext( void )
{
	/* 获取优先级最高的就绪任务的TCB，然后更新到pxCurrentTCB */
    List_t * pxConstList ;	
	UBaseType_t uxTopPriority;
																						
	/* 寻找包含就绪任务的最高优先级的队列,从位图中查找就绪任务 */								                        
	portGET_HIGHEST_PRIORITY( uxTopPriority, uxTopReadyPriority );	

	/* 节点索引指向链表第一个节点调整节点索引指针，指向下一个节点，
    如果当前链表有N个节点，当第N次调用该函数时，pxInedex则指向第N个节点 */
	pxConstList = &( pxReadyTasksLists[ uxTopPriority ] ) ;
	( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;							
	/* 当前链表为空 */                                                                       
	if( ( void * ) ( pxConstList )->pxIndex == ( void * ) &( ( pxConstList )->xListEnd ) )	
	{																						
		( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;						
	}																						
	/* 获取节点的OWNER，即TCB */
    /* 获取优先级最高的就绪任务的TCB，然后更新到pxCurrentTCB */         	
	( pxCurrentTCB ) = ( pxConstList )->pxIndex->pvOwner;											
}
/*--------------------------------------------------------------------------------------------------
Function: 
--------------------------------------------------------------------------------------------------*/
void vTaskDelay( const TickType_t xTicksToDelay )
{
    TCB_t *pxTCB = NULL;
    
    /* 获取当前任务的TCB */
    pxTCB = pxCurrentTCB;
    
    /* 设置延时时间 */
    pxTCB->xTicksToDelay = xTicksToDelay;
    
    /* 将任务插入到延时列表 */
    prvAddCurrentTaskToDelayedList( xTicksToDelay );
    
    /* 任务切换 */
    taskYIELD();
}
/*--------------------------------------------------------------------------------------------------
Function: 
--------------------------------------------------------------------------------------------------*/
void xTaskIncrementTick( void )
{
	TCB_t * pxTCB;
	List_t *pxTemp;
	TickType_t xItemValue;

	const TickType_t xConstTickCount = xTickCount + 1;
	xTickCount = xConstTickCount;

	/* 如果xConstTickCount溢出，则切换延时列表 */
	if( xConstTickCount == ( TickType_t ) 0U )
	{
		//taskSWITCH_DELAYED_LISTS();
		pxTemp = pxDelayedTaskList;
		pxDelayedTaskList = pxOverflowDelayedTaskList;
		pxOverflowDelayedTaskList = pxTemp;
		xNumOfOverflows++;
		prvResetNextTaskUnblockTime();		
	}

	/* 最近的延时任务延时到期 */
	if( xConstTickCount >= xNextTaskUnblockTime )
	{
		for( ;; )
		{
			if( pxDelayedTaskList->uxNumberOfItems == 0 )
			{   /* 延时列表为空，设置xNextTaskUnblockTime为可能的最大值 */
				xNextTaskUnblockTime = portMAX_DELAY; 
				break;
			}
			else 
			{   /* 延时列表不为空 */
				pxTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxDelayedTaskList );
				//xItemValue = listGET_LIST_ITEM_VALUE( &( pxTCB->xStateListItem ) );
                xItemValue = ( &( pxTCB->xStateListItem ))->xItemValue ;
				/* 直到将延时列表中所有延时到期的任务移除才跳出for循环 */
                if( xConstTickCount < xItemValue )
				{
					xNextTaskUnblockTime = xItemValue;
					break;
				}
				/* 将任务从延时列表移除，消除等待状态 */
				( void ) uxListRemove( &( pxTCB->xStateListItem ) );

				/* 将解除等待的任务添加到就绪列表 */
	            uxTopReadyPriority |= 1UL<< ( ( pxTCB )->uxPriority );											    
                /* 将节点插入到链表的尾部 */
                vListInsertEnd( &( pxReadyTasksLists[ ( pxTCB )->uxPriority ]) ,&( ( pxTCB )->xStateListItem ));					
			}
		}
	}
    /* 任务切换 */
    //portYIELD();
}
/*--------------------------------------------------------------------------------------------------
Function: 
--------------------------------------------------------------------------------------------------*/
static void prvAddCurrentTaskToDelayedList( TickType_t xTicksToWait )
{
    TickType_t xTimeToWake;
    
    /* 获取系统时基计数器xTickCount的值 */
    const TickType_t xConstTickCount = xTickCount;

    /* 将任务从就绪列表中移除 */
	if( uxListRemove( &( pxCurrentTCB->xStateListItem ) ) == ( UBaseType_t ) 0 )
	{
		/* 将任务在优先级位图中对应的位清除 */
        portRESET_READY_PRIORITY( pxCurrentTCB->uxPriority, uxTopReadyPriority );
	}

    /* 计算延时到期时，系统时基计数器xTickCount的值是多少 */
    xTimeToWake = xConstTickCount + xTicksToWait;

    /* 将延时到期的值设置为节点的排序值 */
    //listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xStateListItem ), xTimeToWake );
	pxCurrentTCB->xStateListItem.xItemValue = xTimeToWake ;

    /* 溢出 */
    if( xTimeToWake < xConstTickCount )
    {
        vListInsert( pxOverflowDelayedTaskList, &( pxCurrentTCB->xStateListItem ) );
    }
    else /* 没有溢出 */
    {
        vListInsert( pxDelayedTaskList, &( pxCurrentTCB->xStateListItem ) );
        /* 更新下一个任务解锁时刻变量xNextTaskUnblockTime的值 */
        if( xTimeToWake < xNextTaskUnblockTime )
        {
            xNextTaskUnblockTime = xTimeToWake;
        }
    }	
}

/*--------------------------------------------------------------------------------------------------
Function: 延时任务为空，计数值设置为最大，延时不为空，计数值赋值
--------------------------------------------------------------------------------------------------*/
static void prvResetNextTaskUnblockTime( void )
{
    TCB_t *pxTCB;
	
	if((pxDelayedTaskList ->uxNumberOfItems ) == 0)           //=0，没有延时任务，>0有延时任务
	//if( listLIST_IS_EMPTY( pxDelayedTaskList ) != pdFALSE )
	{
		/* The new current delayed list is empty.  Set xNextTaskUnblockTime to
		the maximum possible value so it is	extremely unlikely that the
		if( xTickCount >= xNextTaskUnblockTime ) test will pass until
		there is an item in the delayed list. */
		xNextTaskUnblockTime = portMAX_DELAY;
	}
	else
	{
		/* The new current delayed list is not empty, get the value of
		the item at the head of the delayed list.  This is the time at
		which the task at the head of the delayed list should be removed
		from the Blocked state. */
		( pxTCB ) = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxDelayedTaskList );
		xNextTaskUnblockTime = pxTCB ->xStateListItem.xItemValue ;
		//xNextTaskUnblockTime = listGET_LIST_ITEM_VALUE( &( ( pxTCB )->xStateListItem ) );
	}
}

/*--------------------------------------------------------------------------------------------------
Function: 任务挂起
--------------------------------------------------------------------------------------------------*/
void vTaskSuspend( TCB_t *xTaskToSuspend )
{
    TCB_t *pxTCB;
    void *pvStateList;
    uint32_t ulPreviousMask;
    BaseType_t xTaskIsCurrent;

    if( xTaskToSuspend == NULL )
    {
        return;
    }
    pxTCB = xTaskToSuspend;
    //关总中断
	ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
    pvStateList = pxTCB->xStateListItem.pvContainer;
    //已加入挂机任务列表
    if(( pvStateList == NULL )||( pvStateList == ( void * ) &xSuspendedTaskList ))
    {
        portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
        return;
    }
	//是否为当前任务
    xTaskIsCurrent = ( pxTCB == pxCurrentTCB ) ? pdTRUE : pdFALSE;
    ( void ) uxListRemove( &( pxTCB->xStateListItem ) );
    //查询就绪任务列表
    if( pvStateList == ( void * ) &( pxReadyTasksLists[ pxTCB->uxPriority ] ) )
    {
        if( pxReadyTasksLists[ pxTCB->uxPriority ].uxNumberOfItems == 0U )
        {
            portRESET_READY_PRIORITY( pxTCB->uxPriority, uxTopReadyPriority );
        }
    }
    //查询延时任务列表
	else if( pvStateList == ( void * ) pxDelayedTaskList )
    {
        prvResetNextTaskUnblockTime();
    }
	//加入挂机任务列表
    vListInsertEnd(&xSuspendedTaskList, &( pxTCB->xStateListItem ));
	//开总中断
    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
    //任务切换
    if( xTaskIsCurrent != pdFALSE )
    {
        taskYIELD();
    }
}

/*--------------------------------------------------------------------------------------------------
Function: 任务恢复
--------------------------------------------------------------------------------------------------*/
void vTaskResume( TCB_t *xTaskToResume )
{
    TCB_t *pxTCB;
    uint32_t ulPreviousMask;
    BaseType_t xYieldRequired = pdFALSE;

    if( xTaskToResume == NULL )
    {
        return;
    }
    pxTCB = xTaskToResume;
	//关总中断
    ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
    //是否已挂起
    if( pxTCB->xStateListItem.pvContainer == ( void * ) &xSuspendedTaskList )
    {
        //移除任务
		( void ) uxListRemove( &( pxTCB->xStateListItem ) );
        uxTopReadyPriority |= 1UL << pxTCB->uxPriority;
        vListInsertEnd( &( pxReadyTasksLists[ pxTCB->uxPriority ] ),&( pxTCB->xStateListItem ) );

        if(( pxCurrentTCB == NULL )||( pxTCB->uxPriority >= pxCurrentTCB->uxPriority ))
        {
            xYieldRequired = pdTRUE;
        }
    }
    //开总中断
	portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
    if( xYieldRequired != pdFALSE )
    {
        taskYIELD();
    }
}


























#if 0
/*--------------------------------------------------------------------------------------------------
Function: 任务挂起
--------------------------------------------------------------------------------------------------*/
void vTaskSuspend( TCB_t *xTaskToSuspend )
{
	TCB_t *pxTCB;
	void *pvStateList;
	uint32_t ulPreviousMask;
	BaseType_t xTaskIsCurrent;

	/* NULL 表示挂起当前运�?�任务�? */
	pxTCB = ( xTaskToSuspend == NULL ) ? pxCurrentTCB : xTaskToSuspend;
	if( pxTCB == NULL )
	{
		return;
	}

	ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
	pvStateList = pxTCB->xStateListItem.pvContainer;

	/* 已挂起的任务不重复�?�理；无效或�?加入状态链表的任务也不移除�? */
	if( ( pvStateList == ( void * ) &xSuspendedTaskList ) ||
		( pvStateList == NULL ) )
	{
		portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
		return;
	}

	xTaskIsCurrent = ( pxTCB == pxCurrentTCB ) ? pdTRUE : pdFALSE;
	( void ) uxListRemove( &( pxTCB->xStateListItem ) );

	if( pvStateList == ( void * ) &( pxReadyTasksLists[ pxTCB->uxPriority ] ) )
	{
		if( pxReadyTasksLists[ pxTCB->uxPriority ].uxNumberOfItems == 0U )
		{
			portRESET_READY_PRIORITY( pxTCB->uxPriority, uxTopReadyPriority );
		}
	}
	else if( pvStateList == ( void * ) pxDelayedTaskList )
	{
		prvResetNextTaskUnblockTime();
	}

	vListInsertEnd( &xSuspendedTaskList, &( pxTCB->xStateListItem ) );
	portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );

	/* 当前任务已不再就�?，必须立即调度其他任务�? */
	if( xTaskIsCurrent != pdFALSE )
	{
		taskYIELD();
	}
}

/*--------------------------------------------------------------------------------------------------
Function: 任务恢复
--------------------------------------------------------------------------------------------------*/
void vTaskResume( TCB_t *xTaskToResume )
{
	TCB_t *pxTCB;
	uint32_t ulPreviousMask;
	BaseType_t xYieldRequired = pdFALSE;

	if( xTaskToResume == NULL )
	{
		return;
	}

	pxTCB = xTaskToResume;
	ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();

	/* 仅恢复明�?处于挂起链表�?的任务�? */
	if( pxTCB->xStateListItem.pvContainer == ( void * ) &xSuspendedTaskList )
	{
		( void ) uxListRemove( &( pxTCB->xStateListItem ) );
		uxTopReadyPriority |= 1UL << pxTCB->uxPriority;
		vListInsertEnd( &( pxReadyTasksLists[ pxTCB->uxPriority ] ),
		                &( pxTCB->xStateListItem ) );

		if( ( pxCurrentTCB == NULL ) ||
			( pxTCB->uxPriority >= pxCurrentTCB->uxPriority ) )
		{
			xYieldRequired = pdTRUE;
		}
	}

	portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );

	if( xYieldRequired != pdFALSE )
	{
		taskYIELD();
	}
}

#endif





























//extern TCB_t Task1TCB;
//extern TCB_t Task2TCB;
//extern TCB_t IdleTaskTCB;
//void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
//                                    StackType_t **ppxIdleTaskStackBuffer, 
//                                    uint32_t *pulIdleTaskStackSize );
//void vTaskStartScheduler( void )
//{
///*======================================创建空闲任务start==============================================*/     
//    TCB_t *pxIdleTaskTCBBuffer = NULL;
//    StackType_t *pxIdleTaskStackBuffer = NULL;
//    uint32_t ulIdleTaskStackSize;
//    
//    /* 获取空闲任务的内存：任务栈和任务TCB */
//    vApplicationGetIdleTaskMemory( &pxIdleTaskTCBBuffer, 
//                                   &pxIdleTaskStackBuffer, 
//                                   &ulIdleTaskStackSize );    
//    
//    xIdleTaskHandle = xIdleTaskHandle ;
//	xIdleTaskHandle = xTaskCreateStatic( (TaskFunction_t)prvIdleTask,              /* 任务入口 */
//					                     (char *)"IDLE",                           /* 任务名称，字符串形式 */
//					                     (uint32_t)ulIdleTaskStackSize ,           /* 任务栈大小，单位为字 */
//					                     (void *) NULL,                            /* 任务形参 */
//                                         (UBaseType_t) tskIDLE_PRIORITY,           /* 任务优先级，数值越大，优先级越�? */
//					                     (StackType_t *)pxIdleTaskStackBuffer,     /* 任务栈起始地址 */
//					                     (TCB_t *)pxIdleTaskTCBBuffer );           /* 任务控制�? */										 								 
///*======================================创建空闲任务end================================================*/ 
//    xNextTaskUnblockTime = portMAX_DELAY;
//    xTickCount = ( TickType_t ) 0U;

//    /* �?动调度器 */
//    if( xPortStartScheduler() != pdFALSE )
//    {
//        /* 调度器启动成功，则不会返回，即不会来到这�? */
//    }
//}
///*------------------------------------------------------------------------------------
//Function: 
//------------------------------------------------------------------------------------*/
//static portTASK_FUNCTION( prvIdleTask, pvParameters )
//{
//	TCB_t *pxTCB = NULL;
//    BaseType_t i = 0;
//	
//    for(;;)
//    {
//		for(i=0; i<configMAX_PRIORITIES; i++)
//		{
//			pxTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( ( &pxReadyTasksLists[i] ) );
//			
//			if( pxTCB->xTicksToDelay ==0 )     //延时时间到，任务就绪
//			{
//		        portYIELD();				   //任务切换
//			}
//		}	
//    }
//}


