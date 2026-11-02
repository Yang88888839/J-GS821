
#define BSP_SOUND_LED_C

#include "main.h"
#include "gpio.h"
#include "driver_gpio.h"
#include "driver_timer.h"
#include "driver_pwm.h"

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
#include "app_work_2.h"
#include "task.h" 


unsigned short green_weak=950;
/*------------------------------------------------------------------------
 * @brief
 * @input:	open  -> 亮灯时间 单位（10ms）; 
 *			close -> 灭灯时间 单位（10ms）; 
 *			cyc   -> 亮灯次数       
 * @return
------------------------------------------------------------------------*/
void led_open_set(led_colour name,unsigned char open,unsigned char close, unsigned char cyc)
{	
	led[name].cyc = cyc ;
	led[name].open = open ;
	led[name].close = close ;
	led[name].open_bk = open ;
	led[name].close_bk = close ;	
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void led_output(unsigned char name,unsigned char sta)
{
	switch(name)		
	{
		case colour_green_weak:
			 //sta==1 ? PW_green_weak_open() : PW_green_weak_close() ;
		     sta==1 ? green_set_duty(green_weak) : PW_green_weak_close() ;
		     break;
		case colour_yellow:
			 if(sta==1)
			 {
				 PW_yellow_open();
			 }
             else
             {
				 PW_yellow_close();
			 }				 
			 break;
		case colour_green:
			 sta==1 ? PW_green_open() : PW_green_close() ;
			 break;
        case colour_blue:
			 sta==1 ? PW_blue_open() : PW_blue_close() ;
		     break;
		case colour_red:
			 sta==1 ? PW_red_open() : PW_red_close() ;
			 break;
        case colour_lifeover:
			 sta==1 ? PW_lifeover_open() : PW_lifeover_close() ;
			 break;
        case colour_valve :
             sta==1 ? PW_led_valve_open() : PW_led_valve_close() ;			
        default :
			 break;			
	}	
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void led_clr_set(led_colour name)
{
	led[name].cyc = 0 ;
	led[name].open = 0 ;
	led[name].close = 0 ;
	led[name].open_bk = 0 ;
	led[name].close_bk = 0 ;
    led_output(name,0);	
}

/*------------------------------------------------------------------------
 * @brief	LED扫描(在10ms扫描里最后调用最优)
 * @input
 * @return
------------------------------------------------------------------------*/
void led_working(void)
{		
	for(int i=0;i<colour_max;i++)
	{
		if(led[i].cyc>0)
		{	
			if(led[i].open>0)
			{
                led[i].open--;
				led_output(i,1);   //open led
			}
            else
            {
				if(led[i].close>0)
				{
					led[i].close -- ;	
				}
				else
				{
					led[i].cyc -- ;
					led[i].open = led[i].open_bk ;
					led[i].close = led[i].close_bk ;				
				}
                led_output(i,0);  //close led				
			}				
		}	
	}	
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void voice_open_set(unsigned char volume,unsigned char open,unsigned char close ,unsigned char cyc)
{	
	voice.cyc = cyc ;
	voice.open = open ;
	voice.close = close ;
	voice.open_bk = open ;
	voice.close_bk = close ;
    frequency_duty_set(volume);
    voice.volume=volume ;	
}

/*------------------------------------------------------------------------
 * @brief 故障提示音间隔5秒
 * @input
 * @return
------------------------------------------------------------------------*/
void voice_fault_set(unsigned char name)
{	
	static unsigned int timer=0;
	if(f_fault_mute==1)
	{	
		return ;
	}	
	if((++timer)<500)
	{
		return ; 
	}
	timer=0;
	switch(name)
	{
		case INDICATE_FAULT_SENSOR:
			 voice_open_set(SOUND_CLASS_55DB,10,20,2);
		     break;
		case INDICATE_FAULT_LIFEOVER:
			 voice_open_set(SOUND_CLASS_55DB,10,20,1);		 
		     break;
		case INDICATE_FAULT_VALVE:
			 voice_open_set(SOUND_CLASS_55DB,10,20,2);		
		     break;
	    default:
             break;				 
	}
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void buzzer_short(unsigned short ms)
{
	frequency_duty_set(SOUND_CLASS_55DB);
	pwm_enable();
    delay_ms(ms);
	pwm_disable();
}

/*------------------------------------------------------------------------
 * @brief  
 * @input
 * @return
------------------------------------------------------------------------*/
void voice_working(void)
{
	static _Bool f_sound_run=0;
	unsigned short temp ;
	if(voice.cyc>0)
	{
        if(voice.open>0)
        {
        	if(f_sound_run==0)
        	{		
				f_sound_run=1;
        		pwm_enable();
        	}
			if(voice.volume>6) //50%占空比+变频
			{
				temp = PWM_BASE_FRQ - (50-voice.open) ;
				frequency_set(temp,temp>>1); 
			}	
        	voice.open--;
        }
        else
        {
        	if(voice.close>0)
        	{
        		voice.close--;
        	}
        	else
        	{       		
    			voice.cyc--;
    			if(voice.cyc>0)
    			{
	    			voice.open = voice.open_bk;
	    			voice.close = voice.close_bk;
    			}        		
        	}
    		if(f_sound_run==1)
    		{
    			f_sound_run=0;
    			pwm_disable();
    		}        	
        }		
	}
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void voice_alarm_control(void)
{
	for(int i=0;i<4;i++)
	{
		if(f_alarm_gas==0)
		{
			return;
		}
        if(i<3)
        {
			if(voice.DBlow<8)
			{
				voice.DBlow++;
			}
			if(f_alarm_mute==0)
			{
				voice_open_set(voice.DBlow,30,40,1);			
			}			
		}			
		led_open_set(colour_red,75,0,1);
		vTaskDelay(700);			
	}			
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void display_PowerOn(void)
{	
	PW_red_open();
	PW_lifeover_open();
	PW_led_valve_open();
	buzzer_short(500);
	PW_lifeover_close();	
	PW_led_valve_close();	
}

/*------------------------------------------------------------------------
* @brief  小声报警提示音
 * @input
 * @return
------------------------------------------------------------------------*/
void voice_test_control(void)
{  
    for(int i=0;i<colour_max;i++)
    {
		led_clr_set((led_colour)i);
	}
	PW_lifeover_open();
	PW_led_valve_open();	
    PW_red_open();vTaskDelay(500);PW_red_close();	
	PW_yellow_open();vTaskDelay(500);PW_yellow_close();
	PW_green_open();vTaskDelay(500);PW_green_close();
	PW_blue_open();vTaskDelay(500);PW_blue_close();
	PW_lifeover_close();
	PW_led_valve_close();		
	PW_green_open();
	for(int i=0;i<11;i++)
	{
		if((i&0x03)!=0x03)
		{
			voice.DBlow++;
			voice_open_set(voice.DBlow,30,40,1);			
		}
		vTaskDelay(700);	
		if(f_alarm_test==0)
		{	
			voice_open_set(SOUND_CLASS_55DB,10,0,1);		    
			break;
		}
        if(f_alarm_gas)
        {
			return;
		}			
	}
	valve_open_set(va_action,200,100);  //电磁阀关闭
	valve.study_timer=500;              //电磁阀学习
	f_alarm_test=0;	
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void display_preheat(void)
{
	static unsigned char flag=0;
	
	flag++;
	switch(flag)
	{
		case 1 :
			 led_open_set(colour_red,50,0,1);
			 break;
		case 2 :
			 led_open_set(colour_yellow,50,0,1);
			 break;		
		default:
             led_open_set(colour_green,50,0,1);
			 flag=0;
			 break;		
	}
}

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void led_slow_light(led_colour name)
{
	static unsigned char timer=0;
	
	if((++timer)>70)
	{
		led_open_set(name,30,40,1);
		timer=0;
	}	
}	

/*------------------------------------------------------------------------
 * @brief
 * @input
 * @return
------------------------------------------------------------------------*/
void display_handler(void)
{				
	if(f_fault_lifeover)//寿命终止
	{
		voice_fault_set(INDICATE_FAULT_LIFEOVER);	
		led_open_set(colour_lifeover,10,0,1);
		led_open_set(colour_yellow,10,0,1);
        return;		
	}	 
	if(f_fault_gas==1)//传感器故障指示
    {		
		voice_fault_set(INDICATE_FAULT_SENSOR);
        led_open_set(colour_yellow,20,0,1);
		return ;
	}
	if(f_alarm_gas)//气体报警指示
	{
		voice_alarm_control();
		return;
	}
	if(f_alarm_test)//测试报警指示
	{
		voice_test_control();
		return;
	}		
	if(f_fault_valve==1)//电磁阀声音指示
	{
		voice_fault_set(INDICATE_FAULT_VALVE);	
	}
	if(module_param.join_timer>0)
	{		
		//连接中
		if((module_param.net==em_net_offline)||(module_param.net==em_net_local))
		{
            led_slow_light(colour_blue);			
			return ;
		}
		//未入网
        if(module_param.net==em_net_uap)
		{
            led_slow_light(colour_yellow);
			return ;			
		}		
    }
	if(module_param.net==em_net_updating)//固件升级中
	{
		led_slow_light(colour_blue);
		return ;		
	}
	led_open_set(colour_green_weak,10,0,1);		
}

/*-----------------------------------------------------------------------------
 * @brief: 报警静音退出
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void alarm_mute_exit(void)
{
	static unsigned short alarm_mute_timer=0;
	if(status_alarm.byte==0)
	{
		if(f_alarm_mute)
		{
			message_enqueue(&upload_message,msg_sensor_alarm_mute);	
			f_alarm_mute=0;
		}	
		alarm_mute_timer=0;
	}
	else
	{	
		if(f_alarm_mute==1)
		{
			if((++alarm_mute_timer)>C_time_mute_alarm)
			{
				message_enqueue(&upload_message,msg_sensor_alarm_mute);	
				f_alarm_mute=0;
			}	
		}		
	}
	if(device.alarm_mute_wait>0)
	{
		device.alarm_mute_wait--;
	}	
}	

/*-----------------------------------------------------------------------------
 * @brief: 故障静音退出
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void fault_mute_exit(void)
{
	static unsigned short alarm_mute_timer=0;
	if(status_fault.byte==0)
	{
		if(f_fault_mute==1)
		{
			message_enqueue(&upload_message,msg_sensor_fault_mute);	
			f_fault_mute=0;		
		}	
		alarm_mute_timer=0;
	}
    else
    {		
		if(f_fault_mute)
		{
			if((++alarm_mute_timer)>C_time_mute_fault)
			{
				message_enqueue(&upload_message,msg_sensor_fault_mute);
				alarm_mute_timer=0;
				f_fault_mute=0;
			}				
		}
    }
    if(f_fault_mute==0)
    {
		alarm_mute_timer=0;
	}		
}













