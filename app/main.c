
#define MAIN_C
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:  
-----------------------------------------------------------------------------*/
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
#include "app_work_1.h"
#include "app_work_2.h"
#include "app_work_3.h"
#include "app_work_4.h"
#include "task.h"
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:  
-----------------------------------------------------------------------------*/
void calibration_fixed_value(void)
{
	eep.cal.byte.flag_init=0x5a ;
	Flash_factory_write(EEP_ADDR_CAL,&eep.cal.buffer[0],16);
}	


/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
int32_t main(void)
{
	Init_ClockSys();
	Init_gpio();
	Init_lptim0();
	Init_timer0();
	Init_timer1();
	Init_timer2();
    Init_usart0();
	Init_usart1();
	Init_Adc();
	Init_rtc();
	Init_pwm();
	Init_lpusart1();
	initializeQueue(&upload_message);
	initializeQueue(&event_message);
	initializeQueue(&get_message);
	initializeQueue(&set_message);
	Init_gpio_interrupt();
	Flash_read_params();
	Flash_factory_check();
	Flash_factory_params();
    Flash_lifeover_judge();	
	myprintf("start\r\n");
	Init_iwdt();
	//-----------------------------------------------------
    xTask_init();
    Creat_work_1();
    Creat_work_2();
    Creat_work_3();
    Creat_work_4();	
    portDISABLE_INTERRUPTS(); /* 在启动调度器前，关闭中断 */ 
    /* 启动调度器 */
    if( xPortStartScheduler() != pdFALSE )
    {
        /* 调度器启动成功，则不会返回，即不会来到这里 */
    }									  
    for(;;)
	{
		/* 系统启动成功不会到达这里 */
		printf("run...\r\n");
		delay_ms(1000);
	}	
}



/******************************************************************************
 * EOF (not truncated)

 ******************************************************************************/


