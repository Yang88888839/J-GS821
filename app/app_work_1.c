
#define   APP_WORK_1_C


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
#include "app_work_1.h"
#include "task.h"
/*----------------------------------------------------------------------------
功能：任务1
----------------------------------------------------------------------------*/
#define TASK1_STACK_SIZE                    256
StackType_t Task1Stack[TASK1_STACK_SIZE]    __attribute__((aligned(4)));  
TCB_t Task1TCB;	
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Task1_Entry( void *p_arg )
{
	while(1)
	{		
        //-------------------------------串口接收
		uart0_receive_timer();
	    uart1_receive_timer();
        lpuart1_receive_timer();	
		//-------------------------------
		key_scan();
		led_working();
		voice_working();
		valve_working();
		//-------------------------------
		power_supply_check();
        gas_sensor_analysis();   
		//-------------------------------
		if((f_run_factory==0)&&(f_run_fct==0))
		{
			log_receive_dispose();
			ir38k_dispose();
			key_dispose();		
		}
		else
		{
			if(f_run_fct==1)
				fct_test_receive();	
            if(f_run_factory==1)
				log_receive_dispose();
		}				
		//-------------------------------
		vTaskDelay(10);
        f_task1_run=1;
		//-------------------------------
		if((task_run.byte&0x0f)==0x0f)
		{
			task_run.byte=0;
			IWDT_Feed();
		}		
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Creat_work_1(void)
{	
	/* 创建任务 */
    xTaskCreateStatic(  (TaskFunction_t)Task1_Entry,   /* 任务入口 */
	                    (char *)"Task1",               /* 任务名称，字符串形式 */
					    (uint32_t)TASK1_STACK_SIZE ,   /* 任务栈大小，单位为字 */
                        (void *) NULL,                 /* 任务形参 */						
					    (UBaseType_t) 2,               /* 任务优先级，数值越大，优先级越高 */
					    (StackType_t *)Task1Stack,     /* 任务栈起始地址 */
					    (TCB_t *)&Task1TCB );          /* 任务控制块 */

}


