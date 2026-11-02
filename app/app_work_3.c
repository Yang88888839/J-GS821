
#define   APP_WORK_3_C

#include "driver_adc.h"
#include "driver_pwm.h"
#include "driver_gpio.h"

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
#include "bsp_sound_led.h"
#include "bsp_queue.h"
/*---------------------------------includes---------------------------------*/
#include "FreeRTOS.h"
#include "app_work_3.h"
#include "task.h"
/*----------------------------------------------------------------------------
功能：任务1
----------------------------------------------------------------------------*/
#define TASK3_STACK_SIZE                    256
StackType_t Task3Stack[TASK3_STACK_SIZE]    __attribute__((aligned(4)));
TCB_t Task3TCB;	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void module_timer(void)
{
	//入网指示
	if(module_param.join_timer>0)
	{
		module_param.join_timer--;
	}
	//工厂模式退出
    if(module_param.factory_exit>0)
    {
		if((--module_param.factory_exit)==0)
		{
			message_enqueue(&set_message,msg_set_reboot);
		}	
	}		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void device_heart_timer(void)
{
    if(device.heart_count==0)
    {
		Flash_write_smart();
        device.heart_count=C_time_heart;
		message_enqueue(&upload_message,msg_status_normal);
	}
    else
    {
		device.heart_count--;
	}		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Task3_Entry( void *p_arg )
{ 
	for(int i=0;i<15;i++)
	{
		valve_check_task();
		vTaskDelay(1000);
		f_task3_run=1;
	}
	while(1)
	{		
		alarm_mute_exit();
		fault_mute_exit();		    
		valve_check_task();
		gas_sensor_alarm();
		gas_sensor_alarm_again();
		gas_sensor_lel_upload();
		Flash_lifeover_judge();
		device_heart_timer();
		module_timer();	
		//-------------------------------
		vTaskDelay(1000); 
        f_task3_run=1;		
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Creat_work_3(void)
{	
	/* 创建任务 */
    xTaskCreateStatic(  (TaskFunction_t)Task3_Entry,   /* 任务入口 */
	                    (char *)"Task3",               /* 任务名称，字符串形式 */
					    (uint32_t)TASK3_STACK_SIZE ,   /* 任务栈大小，单位为字 */
                        (void *) NULL,                 /* 任务形参 */						
					    (UBaseType_t) 2,               /* 任务优先级，数值越大，优先级越高 */
					    (StackType_t *)Task3Stack,     /* 任务栈起始地址 */
					    (TCB_t *)&Task3TCB );          /* 任务控制块 */

}


