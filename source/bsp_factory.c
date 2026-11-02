#define   BSP_FACTORY_C

#include "gpio.h"
#include "stdio.h"
#include "driver_gpio.h"
#include "driver_pwm.h"

#include "main.h"
#include "bsp_log.h"
#include "bsp_gas.h"
#include "bsp_key.h"
#include "bsp_part.h"
#include "bsp_eeprom.h"
#include "bsp_module.h"
#include "bsp_sound_led.h"
/*---------------------------------includes---------------------------------*/
#include "FreeRTOS.h"
#include "app_work_5.h"
#include "task.h"

enum 
{
	em_factory_start=0,
	em_factory_display,
    em_factory_rtc,	
	em_factory_module,
	em_factory_show_fault,
	em_factory_exit,
};

enum
{
	em_fault_null=0,
	em_fault_other=1,
	em_fault_power,
	em_fault_module,
	em_fault_temperature,
	em_fault_sensor_co,
	em_fault_sensor_0PPM,
	em_fault_sensor_55PPM,
	em_fault_temperature_diff,
	em_fault_sensor_gas,
	em_fault_sensor_smoke,	
};	

unsigned char  factory_steps=0;

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void factory_status_show(void)
{
	switch(eep.sys.byte.factory_status)
	{
		case em_fault_other://
			 voice_open_set(SOUND_CLASS_55DB,5,0,1);
			 led_open_set(colour_red,5,45,1);			 
			 break;
		case em_fault_module://
			 voice_open_set(SOUND_CLASS_55DB,5,0,1);
			 led_open_set(colour_red,5,45,3);				
			 break;
		case em_fault_sensor_gas://
			 voice_open_set(SOUND_CLASS_55DB,5,45,2);
			 led_open_set(colour_red,5,45,1);			
			 break;
		default:
			 break;		
	}	
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void factory_start(void)
{
	if((eep.sys.byte.factory_status>0)&&(eep.sys.byte.factory_status<16))
	{
		factory_steps = em_factory_show_fault;
	}
    else
    {
		factory_steps = em_factory_display;
	}		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void factory_check_display(void)
{
	for(int i=0;i<20;i++)
	{	
		switch(i&0x03)
		{
			case 0 :
			     led_open_set(colour_red,90,10,1);
			     break;
			case 1 :
				 led_open_set(colour_green,90,10,1);
                 break;	
			case 2 :
				 led_open_set(colour_yellow,90,10,1);
                 break;	
            default:
				 led_open_set(colour_blue,90,10,1);
                 break;				
		}	
		led_open_set(colour_valve,90,10,1);
		led_open_set(colour_lifeover,90,10,1);
        voice_open_set(SOUND_CLASS_55DB,10,0,1);		
		for(int j=0;j<100;j++)
		{		
			if(key.value==KEY_PRESS_DOWN)
			{
				factory_steps = em_factory_rtc;
				key.value=0;
				return ;				
			}
            vTaskDelay(10);			
		}	
	}
    factory_steps = em_factory_rtc;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void factory_check_rtc(void)
{
	int timer=0;
	while(1)
	{
		if((timer%100)==0)
		{
			rtc_calibration_send();
		}
        if((timer%400)==0)
        {
			led_open_set(colour_yellow,100,0,1);
			led_open_set(colour_lifeover,100,0,1);
			led_open_set(colour_valve,100,0,1);
		}
		if(eep.sys.byte.rtc_init==0x55)
		{
			factory_steps = em_factory_module;
			break ;
		}
        vTaskDelay(10);
        f_task2_run=1;
        timer++;		
	}	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void factory_check_module(void)
{
	if(f_fault_gas==1)
	{
		eep.sys.byte.factory_status=em_fault_sensor_gas;
		factory_steps = em_factory_show_fault;
		Flash_write_smart();				
	}
	else if(module_param.reply_result==0)
	{
		eep.sys.byte.factory_status=em_fault_module;
		factory_steps = em_factory_show_fault;
		Flash_write_smart();				
	}	
	else
	{ 
		factory_steps = em_factory_exit;
	}	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void factory_show_fault(void)
{
    unsigned int timer=0;
	key.value=0;
	while(1)
	{
		if(key.value==KEY_PRESS_DOWN)//清除故障
		{
			eep.sys.byte.factory_status=em_fault_null;
			factory_steps = em_factory_start ;
			Flash_write_smart();
            break;			
		}
		if(key.value==KEY_PRESS_LONG)//显示故障
		{
			factory_status_show();
		}
		if((timer%200)==0)//任务提示
		{
			led_open_set(colour_red,10,0,1);
		}
        vTaskDelay(10);
        f_task2_run=1;
        timer++;	
	}	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void factory_exit(void)
{
	factory_steps = em_factory_exit;
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void (*FactoryFunc[])(void) =
{
    factory_start,
    factory_check_display,	
	factory_check_rtc,
	factory_check_module,
	factory_show_fault,
	factory_exit,
};

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void factory_handler(void)
{
    if(eep.sys.byte.rtc_init==0x55)
	{
		return ;
	}
	f_run_factory=1;
	factory_steps = em_factory_start;
	while(1)
	{
		FactoryFunc[factory_steps]();
		if(factory_steps==em_factory_exit)
		{
			break;
		}	
		vTaskDelay(10);
		f_task2_run=1;
	}
    f_run_factory=0;	
}













