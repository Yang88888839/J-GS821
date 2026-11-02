
#define   BSP_KEY_C

#include "bt.h"
#include "lpm.h"
#include "adc.h"
#include "gpio.h"
#include "driver_gpio.h"
#include "driver_timer.h"
#include "driver_pwm.h"

#include "stdio.h"
#include "main.h"
#include "bsp_log.h"
#include "bsp_key.h"
#include "bsp_gas.h"
#include "bsp_part.h"
#include "bsp_valve.h"
#include "bsp_queue.h"
#include "bsp_eeprom.h"
#include "bsp_module.h"
#include "bsp_sound_led.h"

/*---------------------------------includes---------------------------------*/
#include "FreeRTOS.h"
#include "app_work_4.h"
#include "app_work_5.h"
#include "task.h"

unsigned int valve_pulse_printf=0;
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned int difference_count(unsigned int start,unsigned int finish)
{
	unsigned int result ;
	if(finish>=start)
	{
		result = finish-start ;
	}
    else
    {
		result = (0xffffffff-start)+finish ;
	}
    return result ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void PortD_IRQHandler(void)
{
	//AC唤醒
	if (TRUE == Gpio_GetIrqStatus(AC_CHECK_PORT, AC_CHECK_PIN))
    {
        Gpio_ClearIrq(AC_CHECK_PORT, AC_CHECK_PIN);
    }
    //IR信号检测
	if (TRUE == Gpio_GetIrqStatus(IR_INPUT_PORT, IR_INPUT_PIN))
    {
        Gpio_ClearIrq(IR_INPUT_PORT, IR_INPUT_PIN);
		ir38k_pulse.number++;
		if(PR_ir38K()==0)
		{
			ir38k_pulse.start = get_timer_ticker();
		}
        if(PR_ir38K()==1)
        {
			ir38k_pulse.finish = get_timer_ticker();
			ir38k_pulse.width  = difference_count(ir38k_pulse.start,ir38k_pulse.finish);
			if((ir38k_pulse.width>2000)&&(ir38k_pulse.width<20000))
			{
		        ir38k_pulse.status =1;
			}	
		}			
    }	
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void PortA_IRQHandler(void)
{
	//阀门检测
    if (TRUE == Gpio_GetIrqStatus(VALVE_PULSE_PORT, VALVE_PULSE_PIN))
    {
		Gpio_ClearIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN);
		if(PR_valve_pulse()==0)
		{
			valve_pulse.start = get_timer_ticker();
		}
        if(PR_valve_pulse()==1)
		{
			valve_pulse.finish = get_timer_ticker();
			valve_pulse.width  = difference_count(valve_pulse.start,valve_pulse.finish);
			valve_pulse_printf = valve_pulse.width;
			valve_pulse.status = 1 ;		
		}		
	}		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void key_scan(void)
{
    if(PR_key()==0)
	{
		if(key.time_press < 6000)
		{
			key.time_press ++ ;
		}
		if(key.time_press==2)
		{
			if(status_alarm.byte==0)
			{	
			    buzzer_short(20);
			}	
		}	
        if(key.save==0)
		{
			if(key.time_press ==2)
			{
				key.value=KEY_PRESS_DOWN;
			}
			if(key.time_press ==300)
			{
				key.value=KEY_PRESS_LONG_3SEC;
				buzzer_short(50);
			}				
			if(key.time_press ==700)
			{
				key.value=KEY_PRESS_LONG;
				buzzer_short(50);
			}		
		}	
		key.time_release =50 ; //松开500ms秒
	}
	else
	{
		if(key.time_release > 0)
		{
			if((key.time_press >2) && (key.time_press <200))//连击计数
			{
				key.save ++ ;
			}	
            if(key.time_release == 1)
            {
                key.value = key.save;
                key.save =0 ;
            }
			key.time_release --;
		}
		key.time_press =0 ;
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char system_fault_mute(void)
{
	if(status_fault.byte==0)
	{
		return 0;
	}	 
	if(f_fault_mute==0)
	{
		f_fault_mute =1 ;
		log_write(FlashMute);
		message_enqueue(&upload_message,msg_sensor_fault_mute);
		return 1 ;
	}
    return 0 ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char system_fault_mute_cancel(void)
{
	if(status_fault.byte==0)
	{
		return 0;
	}
	if(f_fault_mute==1)
	{
		f_fault_mute =0 ;
		message_enqueue(&upload_message,msg_sensor_fault_mute);
		return 1 ;
	}
    return 0 ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char system_alarm_mute(void)
{	
	if((f_alarm_gas==0)||(device.alarm_mute_wait>0))
	{
		return 0;
	}
	if(f_alarm_mute_disable)
	{
		return 0;
	}	
	if(f_alarm_mute==0)
	{
	    f_alarm_mute =1 ;
		f_alarm_mute_disable=1;
        log_write(FlashMute);
		message_enqueue(&upload_message,msg_sensor_alarm_mute);
        return 1 ;		
	}
    return 0 ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void system_test_start(void)
{
	if(f_alarm_gas)
		return ;
	if(f_alarm_test==1)
	{
		f_alarm_test=0;	
	}	
	else
	{	
		log_write(FlashCheck);
		alarm_test_init();
		f_alarm_test=1;	
    }	
}	

extern unsigned short green_weak;
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void key_dispose(void)
{
    if(key.value==0)
    {
        return ;
    }
	myprintf("key=%d\r\n",key.value);
    switch(key.value)
    {
        case KEY_PRESS_DOWN :       //按下        
		     system_fault_mute();
		     system_alarm_mute();
		     green_weak = (green_weak>50) ? (green_weak-=50) : green_weak ;
		     myprintf("green_weak=%d\r\n",green_weak);
		     break;
		case KEY_PRESS_LONG_3SEC :
			 system_fault_mute_cancel();
		     break;
        case KEY_PRESS_LONG :       //长按7秒配网
			 message_enqueue(&set_message,msg_set_restore);
		     break;
        case KEY_PRESS_ONE :        //单击
		     break;
		case KEY_PRESS_TWO :        //双击
			 system_test_start();
			 break;
		case KEY_PRESS_THREE :      //三击				 
		     C_alarm_smulate();
		     break;		
		case KEY_PRESS_FIVE:        //五连击
			 valve_clear_set();
			 break;
        case KEY_PRESS_SEVEN :      //七连击,触发工厂模式
			 message_enqueue(&set_message,msg_set_factory);
		     module_param.factory_exit=30;
		     //eeprom_test();
             break;         			
        default:
            break;          
    }
    key.value=0;  
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void ir38k_dispose(void)
{
	static unsigned char timer=0;
	if((ir38k_pulse.status)||(ir38k_pulse.number>50))
	{
		myprintf("ir_pulse=%d\r\n",ir38k_pulse.width);
		ir38k_pulse.number=0;
		ir38k_pulse.status=0;
		system_fault_mute();
		system_alarm_mute();
	}
    if((++timer)>200)//2秒清零一次
    {
		ir38k_pulse.number=0;
		timer=0;
	}		
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void power_supply_check(void)
{	
	static unsigned char level_low=0;
	static unsigned char level_high=0;
		
	if(1==PR_sleep()) //掉电
	{
		level_high=0;
		if((++level_low)<10)
		{
			return ;
		}
		if(f_status_ac==1)
		{	
			if(f_fault_gas)
			{
				log_write(FlashFault_clear);	
			}			
			if(f_alarm_gas)
			{
				log_write(FlashAlarm_exit);
			}		
			f_status_ac=0;
	    }
		else
		{
			log_write(FlashPower_on);			
		}	
		message_packet_shutdown();		
		log_write(FlashPower_down);
        myprintf("AC_Off...\r");		
		Init_sleep();		
	}
	else//上电
	{
		level_low=0;
		if(0==f_status_ac)
		{	
			if((++level_high)<10)
			{
				return ;
			}			
			f_status_ac=1 ;
			log_write(FlashPower_on);
			myprintf("AC_ON...\r\n");		
	    }		
	}		
}


