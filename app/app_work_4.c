
#define   APP_WORK_4_C


#include "driver_gpio.h"

#include "iwdt.h"
#include "stdio.h"
#include "main.h"
#include "bsp_log.h"
#include "bsp_key.h"
#include "bsp_part.h"
#include "bsp_module.h"
#include "bsp_eeprom.h"
#include "bsp_xmodem.h"
#include "bsp_queue.h"
#include "bsp_sound_led.h"
/*---------------------------------includes---------------------------------*/
#include "FreeRTOS.h"
#include "app_work_4.h"
#include "task.h"
/*----------------------------------------------------------------------------
功能：任务1
----------------------------------------------------------------------------*/
#define TASK4_STACK_SIZE                    256
StackType_t Task4Stack[TASK4_STACK_SIZE]    __attribute__((aligned(4)));
TCB_t Task4TCB;	

#define  str_test  "str_test"
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Task4_Entry( void *p_arg )
{
	vTaskDelay(2000);
	module_param.reply_result=0;
	module_param.reply_result=message_packet_pid();
	module_param.reply_result=message_packet_config();
	module_param.reply_result=message_packet_version();
	message_packet_debug();
	//ota_file_check();
	while(1)
	{		   
		module_message_dispose();
		//-----------------------------------
        f_task4_run=1;		
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void Creat_work_4(void)
{	
	/* 创建任务 */
    xTaskCreateStatic(  (TaskFunction_t)Task4_Entry,   /* 任务入口 */
	                    (char *)"Task4",               /* 任务名称，字符串形式 */
					    (uint32_t)TASK4_STACK_SIZE ,   /* 任务栈大小，单位为字 */
                        (void *) NULL,                 /* 任务形参 */						
					    (UBaseType_t) 2,               /* 任务优先级，数值越大，优先级越高 */
					    (StackType_t *)Task4Stack,     /* 任务栈起始地址 */
					    (TCB_t *)&Task4TCB );          /* 任务控制块 */

}


