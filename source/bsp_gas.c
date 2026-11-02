
#define  BSP_GAS_C

#define   GAS_fault_voltage_min   150
#define   GAS_fault_voltage_mac   3000
#define   GAS_fault_difference    100

#define   GAS_00LEL_minimum       150
#define   GAS_00LEL_maximum       1100

#define   GAS_10LEL_up_minimum    100
#define   GAS_10LEL_up_maximum    500

#define   GAS_10LEL_down_value    50

#define   GAS_alarm_level_5lel    5
#define   GAS_alarm_level_8lel    8
#define   GAS_alarm_level_9lel    9
#define   GAS_alarm_level_10lel   10
#define   GAS_alarm_level_25lel   25

#define   channel_gas             ADC_Channel_5

#include "gpio.h"

#include "driver_rtc.h"
#include "driver_adc.h"
#include "driver_gpio.h"
#include "driver_uart.h"
#include "driver_timer.h"
#include "driver_flash.h"

#include "stdio.h"

#include "main.h"
#include "bsp_log.h"
#include "bsp_key.h"
#include "bsp_gas.h"
#include "bsp_part.h"
#include "bsp_valve.h"
#include "bsp_queue.h"
#include "bsp_eeprom.h"
#include "bsp_string.h"
#include "bsp_sound_led.h"

#define sensor_send(a)       uart_senddata(M0P_USART1,a)
#define sensor_re_done       uart1.done
#define sensor_re_length     uart1.length
#define sensor_re_buf        uart1.buf

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void gas_judge_fault(void)
{	                                   
	if(gas.sensor_online>0)
	{
		gas.sensor_online--;
	}	
	else
	{
		gas.value_fault=SENSOR_FAULT_OFF_LINE;
	}	
	if(f_fault_gas==0)
	{
		if(gas.value_fault>0)
		{
			if((++gas.fault_enter)>5)//进入故障判断
			{
				f_fault_gas =1 ;				
				log_write(FlashFault_enter);
				message_enqueue(&upload_message,msg_sensor_fault);
			}
	    }
		else
		{
			gas.fault_enter=0;
		}	
		gas.fault_exit =0 ;	
	}
    else
	{
		if(gas.value_fault==0)
		{	
			if((++gas.fault_exit)>5)//退出故障判断
			{
				f_fault_gas =0 ;			
				log_write(FlashFault_clear);
				message_enqueue(&upload_message,msg_sensor_fault);
			}
	    }
        else
        {
			gas.fault_exit=0;
		}			
        gas.fault_enter =0 ;		
	}		
}


/********************************************************************
 * @brief 计算输入数据的校验和。
 *
 * 该函数接收一个字符指针作为输入，计算前17个字节的异或校验和，并将结果转换为十进制格式。
 *
 * @param data 输入的字符指针，指向要计算校验和的数据。
 * @return 计算得到的校验和，以十进制格式表示。
 *********************************************************************/
unsigned char calculate_checksum(unsigned char*data,unsigned char len)
{
    // 定义要处理的数据字节数为17
    uint8_t data_count = len-4;
    uint8_t checksum = 0;
   
    while (data_count--)
    {
        // 对当前字节进行异或操作，更新校验和
        checksum ^= *data;
        data++;
    }
    // 将校验和转换为十进制格式，先右移4位取高4位乘以10，再加上低4位
    checksum =(checksum>>4)*10+(checksum%16);
    return checksum;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void gas_sensor_convert(char *buf)
{
	char symbol=0;	
	char str_lel[16];	
	char str_fault[16];
	char str_check[16];
	char str_temperature[16];
	
	string_get_params(buf,' ',&str_lel[0]);
	gas.result_value_lel=convert_stringTOfloat(&str_lel[0]);
	while(*buf!='\0')
	{
		if((*buf)==32)//空格符	
		{
			buf++;
			symbol++;
			switch(symbol)
			{
				case 1:
					 string_get_params(buf,' ',&str_temperature[0]);
				     gas.result_temperature=convert_stringTOfloat(&str_temperature[0]);
					 break;
				case 5:
					 string_get_params(buf,' ',&str_fault[0]);
				     gas.result_fault = convert_stringTObcd(&str_fault[0]);
					 break;
				case 6:
					 string_get_params(buf,' ',&str_check[0]);
				     gas.result_check = convert_stringTObcd(&str_check[0]);
					 break;
				default:
					 break;					
			}			
		}
		buf++;
	}
//    myprintf("lel=%f->fault=%d\r\n",gas.result_value_lel,gas.result_fault);
//    myprintf("temperature=%f\r\n",gas.result_temperature);
//    myprintf("fault=%d\r\n",gas.result_fault);
//    myprintf("sum=%d\r\n",gas.result_check);	
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:  A+000.00 +32.7 0669.80 +22.1 B+003.0 00 18
-----------------------------------------------------------------------------*/
void gas_sensor_analysis(void)
{	
	char *rec_point;
	unsigned char result;

	if(sensor_re_done==0)
	{
		return ;
	}	
	result = calculate_checksum(&sensor_re_buf[0],sensor_re_length);
	if(string_place((char*)&sensor_re_buf[0],"A",(char**)&rec_point)==1)
	{
		gas_sensor_convert(rec_point);
		if(result==gas.result_check)
		{
			if(f_fault_lifeover)
			{
				gas.value_lel =0;
				gas.value_fault =0;
			}	
			else
			{								
				gas.value_lel = gas.result_value_lel*22.7;
				gas.value_fault = gas.result_fault ;
            }
			gas.value_temperature = gas.result_temperature ;
			gas.sensor_online = 3 ;
		}			    
	}
    sensor_re_done=0;
	sensor_re_length=0;	
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void gas_alarm_input(void)
{
	f_alarm_gas =1 ;
	gas.alarm_exit=0 ;
	gas.alarm_enter=0 ;
	alarm_sensor_init();
	f_alarm_mute_disable=0 ;
	device.alarm_mute_wait=60;
	log_write(FlashAlarm_enter);   
	message_enqueue(&upload_message,msg_status_alarm);
}	
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void gas_alarm_exit(void)
{
	f_alarm_gas=0 ;	
    f_alarm_high=0 ;
	gas.alarm_exit =0 ;
    f_alarm_mute_disable=0 ;	
	
	log_write(FlashAlarm_exit);
    message_enqueue(&upload_message,msg_status_alarm);
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void gas_sensor_alarm(void)
{	   
	if(f_fault_lifeover)
	    return ;
	//----------------------------------------------
	gas_judge_fault();//传感器故障检查
	gas_status_output();
	//----------------------------------------------	
    if((f_fault_gas)||(gas.fault_enter>0))
	{
		f_alarm_gas =0 ;
		return ;
	}
	//----------------------------------------------
	if(gas.value_lel<GAS_alarm_level_9lel)
	{
		if(f_alarm_gas==1)
		{
			if((++gas.alarm_exit)>6)
			{
				gas_alarm_exit();
			}	
		}	
	}
	else
	{	
		gas.alarm_exit =0;
	}	
    //----------------------------------------------
	if(gas.value_lel>=GAS_alarm_level_10lel)  
	{
		if(f_alarm_gas==0)
		{
			if((++gas.alarm_enter)>16)
			{
				gas_alarm_input();
			}	
		}		
	}
    else
    {
		gas.alarm_enter=0;
	}		
    //----------------------------------------------
	if(gas.value_lel>GAS_alarm_level_25lel)
	{
		if(gas.alarm_25lel_enter<10)
		{
			gas.alarm_25lel_enter++;
		}	
		if((gas.alarm_25lel_enter==5)&&(f_alarm_high==0))
		{
            f_alarm_high=1;
			message_enqueue(&event_message,msg_event_high_lel);
		}			
	}
    else
    {
		gas.alarm_25lel_enter=0;
	}		
}



/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void gas_sensor_alarm_again(void)
{
	if(f_alarm_gas==1)
	{
		if(device.alarm_timer<86400)
		{
			device.alarm_timer++;
		}
		if(device.alarm_timer<9)
		{
			if((device.alarm_timer&0x01)==0x01)
			{
				message_enqueue(&upload_message,msg_sensor_alarm_timer);
			}	
		}
        else
        {
			if((device.alarm_timer%10)==0)
			{
				message_enqueue(&upload_message,msg_sensor_alarm_timer);
			}			
		}				
	}
    else
    {
		device.alarm_timer=0;
	}		
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void gas_sensor_lel_upload(void)
{
	static unsigned char interval_timer=0;
	
	if(interval_timer>0)
	{
		interval_timer--;
		return ;
	}	
	if(gas.value_lel>2)
	{
		if(gas.value_lel!=gas.value_lel_bk)
		{
			message_enqueue(&upload_message,msg_sensor_gas_lel);
			gas.value_lel_bk = gas.value_lel;
			interval_timer=60;
		}	
	}	
	else
	{
		if(gas.value_lel_bk!=0)
		{
			message_enqueue(&upload_message,msg_sensor_gas_lel);
			gas.value_lel_bk=0;
			interval_timer=60;
		}	
	}		
}	

extern unsigned int valve_pulse_printf;
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void gas_status_output(void)
{					
	static unsigned char timer=0;
	
	if((++timer)>9)
	{
		printf("\nGAS_LEL=%d  fault=%d  ",gas.value_lel,
		                                  gas.value_fault);
		printf("General=0x%02x Fault=0x%02x Alarm=0x%02x  ",status_general.byte,
															status_fault.byte,
															status_alarm.byte);
		printf("valve pulse width=%d  Temperature=%.2f\r\n",valve_pulse_printf,
		                                                    gas.value_temperature);
		Rtc_time_printf();
		timer=0;
	}	
}
































