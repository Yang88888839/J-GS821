
#define   APP_WORK_2_C


#include "driver_pwm.h"
#include "driver_gpio.h"
#include "driver_uart.h"
#include "driver_timer.h"

#include "iwdt.h"
#include "stdio.h"
#include "main.h"
#include "bsp_log.h"
#include "bsp_key.h"
#include "bsp_gas.h"
#include "bsp_part.h"
#include "bsp_valve.h"
#include "bsp_eeprom.h"
#include "bsp_module.h"
#include "bsp_factory.h"
#include "bsp_sound_led.h"
#include "bsp_protocol_fct.h"
/*---------------------------------includes---------------------------------*/
#include "FreeRTOS.h"
#include "app_work_2.h"
#include "task.h"
/*----------------------------------------------------------------------------
功能：任务1
----------------------------------------------------------------------------*/
#define TASK2_STACK_SIZE                    256
StackType_t Task2Stack[TASK2_STACK_SIZE]    __attribute__((aligned(4)));   
TCB_t Task2TCB;	
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Task2_Entry( void *p_arg )
{
	module_param.join_timer=1800;
	//-----------------------------------FCT测试
	fct_send_handler();
	//-----------------------------------工厂自检
	//factory_handler();
	//-----------------------------------上电指示
    led_open_set(colour_valve,50,0,1);
	led_open_set(colour_lifeover,50,0,1);
	voice_open_set(SOUND_CLASS_45DB,50,0,1);	
	//-----------------------------------预热开始
	f_system_preheat=1;
	for(int i=0;i<C_time_preheat;i++)
	{
		display_preheat();
        vTaskDelay(500);
        f_task2_run=1;		
	}
    //-----------------------------------预热结束	
	f_system_preheat=0;
    voice_open_set(SOUND_CLASS_55DB,50,0,1);	
	while(1)
	{					
		//-------------------------------
		display_handler();
		//-------------------------------
		f_run_factory=0;
        f_run_fct=0;			
		//-------------------------------
		vTaskDelay(10); 
		f_task2_run=1;
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Creat_work_2(void)
{	
	/* 创建任务 */
    xTaskCreateStatic(  (TaskFunction_t)Task2_Entry,   /* 任务入口 */
	                    (char *)"Task2",               /* 任务名称，字符串形式 */
					    (uint32_t)TASK2_STACK_SIZE ,   /* 任务栈大小，单位为字 */
                        (void *) NULL,                 /* 任务形参 */						
					    (UBaseType_t) 2,               /* 任务优先级，数值越大，优先级越高 */
					    (StackType_t *)Task2Stack,     /* 任务栈起始地址 */
					    (TCB_t *)&Task2TCB );          /* 任务控制块 */

}


