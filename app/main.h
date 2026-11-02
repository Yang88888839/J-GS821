
#ifndef __MAIN_H
#define __MAIN_H

/////////////////////////////////////////////////////////////////////////
#define  GAS_TEST                 0             //(正常需设置为0)
#define  FLASH_PRINT              1             //(正常需设置为0)
#define  PRINTF_ON                1
/////////////////////////////////////////////////////////////////////////
#define  DEBUG                    1             //(0=打印关闭;1=打印开启) 

#if (DEBUG==0)
	#define   C_aging_time         240           //老化时间240分钟
	#define   C_calibrat_wait_8min 120           //等待时间8分钟
	
	#define   C_time_preheat       30            //上电预热时间15秒
	#define   C_time_heart         43200         //心跳12小时
	#define   C_time_mute_alarm    240           //静音4分钟
	#define   C_time_mute_fault    86400         //静音24小时
	#define   C_time_life_over     173448000     //寿命终止5.5年
    #define   C_alarm_smulate()
#else
	#define   C_aging_time         3            //老化时间1分
	#define   C_calibrat_wait_8min 12           //等待时间8分钟
	
    #define   C_time_preheat       30           //上电预热时间15秒
	#define   C_time_heart         12000        //10分钟
	#define   C_time_mute_alarm    240          //静音4分钟
	#define   C_time_mute_fault    300          //静音5分钟
	#define   C_time_life_over     3000000	    //寿命终止10分钟
    #define   C_alarm_smulate()    if(f_system_preheat==0){\
		                                                   f_alarm_gas = 1;\
		                                                   alarm_sensor_init();\
	                                                       message_enqueue(&upload_message,msg_status_alarm);}
#endif

#define device_hardware    0x11 
#define device_software    0x11
#define device_protocol    0x16
#define APP_VERSION        "0002"

#if (PRINTF_ON == 1 && DEBUG == 1)
    #define     myprintf(fmt,...)    printf((fmt),##__VA_ARGS__)
#else
    #define     myprintf(...)
#endif

typedef union 
{
    unsigned char byte;
    struct
    {
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    }bytes;
}u8bit_flag;

typedef union
{
	unsigned char bytes[4];
	unsigned int  value;
}Byte_int_t;	

typedef union Tag_data_conv
{
	unsigned char buf_8b[128];
	unsigned int buf_32b[32];
}data_conv_t;	

typedef struct Tag_Device
{
	unsigned int   ticker ;
	unsigned int   heart_count ;
	
	unsigned int   alarm_timer ;
	unsigned short alarm_mute_wait ;

	signed char  temperature;

}TagDevice_t;

#define   f_timer_10ms              sys_time.bytes.bit0
#define   f_timer_sec               sys_time.bytes.bit1

#define   f_fault_gas               status_fault.bytes.bit0
#define   f_fault_valve             status_fault.bytes.bit1
#define   f_fault_lifeover          status_fault.bytes.bit2   //寿命到期标志

#define   f_alarm_gas               status_alarm.bytes.bit0
#define   f_alarm_test              status_alarm.bytes.bit1
#define   f_alarm_remote            status_alarm.bytes.bit2

#define   f_system_preheat          status_general.bytes.bit0
#define   f_fault_mute              status_general.bytes.bit1
#define   f_alarm_mute              status_general.bytes.bit2
#define   f_status_ac               status_general.bytes.bit3
#define   f_alarm_high              status_general.bytes.bit4
#define   f_alarm_mute_disable      status_general.bytes.bit5
#define   f_run_fct                 status_general.bytes.bit6
#define   f_run_factory             status_general.bytes.bit7

#define   f_task1_run               task_run.bytes.bit0
#define   f_task2_run               task_run.bytes.bit1
#define   f_task3_run               task_run.bytes.bit2
#define   f_task4_run               task_run.bytes.bit3

#ifdef      MAIN_C
    #define MAIN_C

#else
    #define MAIN_C  extern
		
#endif
	
MAIN_C data_conv_t       array_temp __attribute__ ((aligned(4)));	
	
MAIN_C  u8bit_flag       task_run ;	

MAIN_C  u8bit_flag       sys_time ;
MAIN_C  u8bit_flag       status_fault ; 		
MAIN_C  u8bit_flag       status_alarm ; 
MAIN_C  u8bit_flag       status_general ; 	
	
MAIN_C	TagDevice_t      device;
	
void task_start_init(void);

#endif
