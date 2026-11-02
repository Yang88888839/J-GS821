#ifndef INC_TASK_H
#define INC_TASK_H

#include "list.h"

#define tskIDLE_PRIORITY			       ( ( UBaseType_t ) 0U )
#define taskYIELD()					       portYIELD()

#define taskENTER_CRITICAL()		       portENTER_CRITICAL()
#define taskENTER_CRITICAL_FROM_ISR()      portSET_INTERRUPT_MASK_FROM_ISR()

#define taskEXIT_CRITICAL()			       portEXIT_CRITICAL()
#define taskEXIT_CRITICAL_FROM_ISR( x )    portCLEAR_INTERRUPT_MASK_FROM_ISR( x )

typedef void  * TaskHandle_t;

static volatile TickType_t xNextTaskUnblockTime		= ( TickType_t ) 0U;
static volatile BaseType_t xNumOfOverflows 			= ( BaseType_t ) 0;
static volatile TickType_t xTickCount 				= ( TickType_t ) 0U;


void xTaskCreateStatic(	TaskFunction_t pxTaskCode,           /* ������� */
	                    const char * const pcName,           /* �������ƣ��ַ�����ʽ */
						const uint32_t ulStackDepth,         /* ����ջ��С����λΪ�� */
						void * const pvParameters,           /* �����β� */	
						UBaseType_t uxPriority,              /* �������ȼ�����ֵԽ�����ȼ�Խ�� */
						StackType_t * const puxStackBuffer,  /* ����ջ��ʼ��ַ */
						TCB_t * const pxTaskBuffer );        /* ������ƿ� */
 
void xTask_init(void);						
void prvInitialiseTaskLists( void );                                
void vTaskStartScheduler( void );
void vTaskSwitchContext( void );
void vTaskDelay( const TickType_t xTicksToDelay );
void xTaskIncrementTick( void );
void vTaskSuspend( TCB_t * xTaskToSuspend );
void vTaskResume( TCB_t * xTaskToResume );						
//void vTaskResume( TaskHandle_t xTaskToResume );

                                
#endif /* INC_TASK_H */ 
