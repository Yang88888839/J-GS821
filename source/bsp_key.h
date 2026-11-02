#ifndef  BSP_KEY_H
#define  BSP_KEY_H

typedef struct tag_key
{
	unsigned char  time_release ;  //按键松开计时器
	unsigned short time_press ;    //按键按下计时器
	unsigned char  value;
    unsigned char  save ;    
}tagkey;

typedef struct tag_pulse 
{
	unsigned int  start ;
	unsigned int  finish ;
	unsigned int  width ;
	unsigned int  status ;
	unsigned int  number ;
}pulse_t ;	

#define  KEY_PRESS_ONE          1
#define  KEY_PRESS_TWO          2
#define  KEY_PRESS_THREE        3
#define  KEY_PRESS_FIVE         5
#define  KEY_PRESS_SEVEN        7
#define  KEY_PRESS_TEN          10

#define  KEY_PRESS_DOWN         0XB0
#define  KEY_PRESS_LONG         0XA0
#define  KEY_PRESS_LONG_3SEC    0XC0

///////////防拆//////////////////
#define  TAMPER_STATUS_HANGUP   0       //正常安装
#define  TAMPER_STATUS_UNLOAD   1       //被拆卸




#ifdef          BSP_KEY_C
      #define   BSP_KEY_C 
     
#else       
      #define   BSP_KEY_C  extern      
#endif 

BSP_KEY_C  tagkey   key;
	  
BSP_KEY_C  volatile pulse_t  ir38k_pulse;
BSP_KEY_C  volatile pulse_t  valve_pulse;	  

void key_scan(void);
void key_dispose(void);
void ir38k_dispose(void);
void system_test_start(void);	  
void power_supply_check(void);	
unsigned char system_fault_mute(void);
unsigned char system_fault_mute_cancel(void);	  
unsigned char system_alarm_mute(void);	  

#endif

