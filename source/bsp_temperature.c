
#define  DRIVER_TEMPERATURE_C

#include "main.h"

#include "bsp_gas.h"
#include "bsp_part.h"
#include "bsp_module.h"
#include "bsp_temperature.h"

#include "driver_rtc.h"
#include "driver_adc.h"
//#include "driver_log.h"
#include "driver_gpio.h"
//#include "driver_usart.h"
#include "driver_timer.h"
#include "driver_flash.h"

#define channel_ntc   ADC_Channel_8

typedef struct tag_temp_list
{
	unsigned short int voltage ;
    signed char value ;
}tagtemp_list ;

const tagtemp_list temp_list[92]=
{
	{2765,-11},  
    {2751,-10},
	{2739,-9 },
	{2726,-8 },
	{2713,-7 },
	{2699,-6 },
	{2684,-5 },
	{2668,-4 },
	{2653,-3 },
	{2636,-2 },
	{2620,-1 },
	{2603, 0 },
	{2586, 1 },
	{2568, 2 },
	{2549, 3 },
	{2530, 4 },	
	{2510, 5 },
	{2489, 6 },
	{2468, 7 },
	{2445, 8 },
	{2422, 9 },
	{2398, 10},
	{2377, 11},	
	{2354, 13},
	{2329, 14},
	{2303, 15},
	{2276, 16},	
	{2249, 17},
	{2221, 18},	
	{2166, 19},
	{2138, 20},	
	{2110, 21},
	{2083, 22},	
	{2055, 23},
	{2027, 24},	
	{2000, 25},
	{1975, 26},	
	{1942, 27},	
	{1911, 28},	
	{1879, 29},	
	{1845, 30},	
	{1814, 31},
	{1783, 32},	
	{1752, 33},	
	{1720, 34},	
	{1688, 35},
	{1656, 36},	
	{1623, 37},	
	{1591, 38},	
	{1559, 39},
	{1527, 40},	
	{1495, 41},	
	{1465, 42},	
	{1435, 43},	
	{1406, 44},	
	{1378, 45},	
	{1346, 46},	
	{1314, 47},	
	{1283, 48},	
	{1254, 49},	
	{1225, 50},	
	{1197, 51},	
	{1169, 52},	
	{1142, 53},
	{1116, 54},	
	{1090, 55},	
	{1064, 56},	
	{1038, 57},	
	{1011, 58},	
	{ 985, 59},	
	{ 958, 60},	
	{ 932, 61},
	{ 907, 62},	
	{ 883, 63},	
	{ 860, 64},	
	{ 837, 65},
	{ 815, 66},	
	{ 794, 67},		
	{ 773, 68},	
	{ 752, 69},
	{ 732, 70},	
	{ 712, 71},
	{ 693, 72},	
	{ 673, 73},	
	{ 654, 74},	
	{ 635, 75},
	{ 617, 76},	
	{ 601, 77},		
	{ 584, 78},	
	{ 569, 79},
	{ 553, 80},	
	{ 538, 81},	
};	

/*---------------------------------------------------------------------------------------
Function:
---------------------------------------------------------------------------------------*/
signed char temperature_read(void)
{
	unsigned char i ;
	unsigned short int value_minimum = 0xffff ;
	unsigned short int value_maximum = 0x0000 ;
	unsigned short int value_sum =0 ;
	unsigned short int value_adc ;
	
	for(i=0;i<6;i++)
	{
		value_adc = GetVoltage(channel_ntc);
		
		if(value_adc < value_minimum)
		{
			value_minimum = value_adc ;
		}
        if(value_adc > value_maximum)
        {
			value_maximum = value_adc ;
		}
        value_sum += value_adc ;		
	}
	value_sum -= value_minimum ;
	value_sum -= value_maximum ;	
	temperature.voltage = value_sum>>2 ;

	if(temperature.voltage>=temp_list[41].voltage)
	{
		temperature.value = temp_list[0].value ;		
		for(i=41;i>0;i--)
		{
			if(temperature.voltage<=temp_list[i].voltage)
			{
				temperature.value = temp_list[i].value-18 ;
				break;
			}		
		}
	}	
	else
	{
		temperature.value = temp_list[91].value ;
		for(i=41;i<91;i++)
		{
			if(temperature.voltage>=temp_list[i].voltage)
			{
				temperature.value = temp_list[i].value-18 ;
				break;
			}
			
		}		
	}
	return temperature.value ;	
}

/*---------------------------------------------------------------------------------------
Function: 10MS运行一次
---------------------------------------------------------------------------------------*/
void temperature_judge_fault(void)
{
	if((temperature.voltage<200)||(temperature.voltage>2955))    
    {
		if(0==b_fault_temperature)
		{
			if((++temperature.fault_enter)>3)
			{
				b_fault_temperature=1 ;
				//b_upload =1 ; 
				//log_write(FlashFault_enter);
			}	
		}
        temperature.fault_exit=0 ;		
	}
    else
	{
		if(1==b_fault_temperature)
		{
			if((++temperature.fault_exit)>3)
			{
				b_fault_temperature =0 ;
				//b_upload =1 ;
				//log_write(FlashFault_clear);
			}	
		}
        temperature.fault_enter=0;		
	}		
}









































///*---------------------------------------------------------------------------------------
//Function:
//---------------------------------------------------------------------------------------*/
//void temperature_alarm_check(void)
//{
//	static unsigned char fast_counter=0;
//		
//	if((b_fault_temperature)||(b_fault_system))
//	{
//		temperature.value =25 ;
//		return ;
//	}	
//	if(temperature.fault_enter>0)
//	{
//		temperature.value =25 ;
//		return ;
//	}	
//	//--------------------------------------------------------fast check
//	if(temperature.value>63)
//	{
//		if(0==b_ntc_alarm_fast)
//		{
//			b_ntc_alarm_fast=1 ;
//			b_upload=1;
//		}   
//	}
//    else
//    {
//		if(1==b_ntc_alarm_fast)
//		{	
//			if((++fast_counter)>5)
//			{
//				b_ntc_alarm_fast=0;
//				b_upload=1 ;
//			}
//	    }
//        else
//        {
//			fast_counter=0;		
//		}			
//	}		
//	//--------------------------------------------------------alarm_check
//    if(temperature.value>65)
//	{
//		if(0==b_alarm_temperature)
//		{
//			if((++temperature.alarm_enter)>5)
//			{
//				b_alarm_temperature =1 ;
//				b_ntc_alarm_fast =0 ;
//				b_upload=1;
//				log_write(FlashAlarm_enter);
//			}	
//		}
//        temperature.alarm_exit =0 ;		
//	}	
//    else
//    {
//		if(1==b_alarm_temperature)
//		{
//			if((++temperature.alarm_exit)>5)
//			{
//				b_alarm_temperature =0 ;			
//                b_upload=1;
//				log_write(FlashAlarm_exit);
//			}	
//		}
//        temperature.alarm_enter =0 ;		
//	}		
//}
































