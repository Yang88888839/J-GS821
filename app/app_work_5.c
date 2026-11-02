
#define   APP_WORK_5_C

#include "driver_rtc.h"
#include "driver_adc.h"
#include "driver_gpio.h"
#include "driver_iwdt.h"
#include "driver_uart.h"
#include "driver_timer.h"
#include "driver_flash.h"
#include "driver_lpuart.h"

#include "iwdt.h"
#include "stdio.h"
#include "main.h"
#include "bsp_log.h"
#include "bsp_key.h"
#include "bsp_gas.h"
#include "bsp_part.h"
#include "bsp_valve.h"
#include "bsp_eeprom.h"
#include "bsp_sound_led.h"
#include "bsp_protocol_fct.h"
/*---------------------------------includes---------------------------------*/
#include "FreeRTOS.h"
#include "app_work_5.h"
#include "task.h"
/*----------------------------------------------------------------------------
功能：任务1
----------------------------------------------------------------------------*/
#define TASK5_STACK_SIZE                    256
StackType_t Task5Stack[TASK5_STACK_SIZE]    __attribute__((aligned(4)));   
TCB_t Task5TCB;	
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Task5_Entry( void *p_arg )
{
	while(1)
	{					
		//---------------------历史数据
		
		//-------------------------------
		vTaskDelay(1000); 
		f_task5_run=1;				
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Creat_work_5(void)
{	
	/* 创建任务 */
    xTaskCreateStatic(  (TaskFunction_t)Task5_Entry,   /* 任务入口 */
	                    (char *)"Task5",               /* 任务名称，字符串形式 */
					    (uint32_t)TASK5_STACK_SIZE ,   /* 任务栈大小，单位为字 */
                        (void *) NULL,                 /* 任务形参 */						
					    (UBaseType_t) 2,               /* 任务优先级，数值越大，优先级越高 */
					    (StackType_t *)Task5Stack,     /* 任务栈起始地址 */
					    (TCB_t *)&Task5TCB );          /* 任务控制块 */

}


