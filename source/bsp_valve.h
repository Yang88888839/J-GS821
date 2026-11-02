#ifndef  APP_VALVE_H
#define  APP_VALVE_H

typedef enum
{
	va_action=0,
	va_check ,
	va_max ,
}valve_number ;

typedef enum
{
	em_valve_uncalibrated =0x00, //未校准
	em_valve_open =0x01,         //开阀
	em_valve_close =0x02,        //关阀
	em_valve_open_fault =0x03,   //开路故障
	em_valve_short_fault =0x04,  //短路故障
	em_valve_offline_fault =0x05,//离线故障
	em_valve_other_fault =0x06,  //其它故障
	em_valve_close_fault =0x07,  //关闭故障
	em_valve_unknown ,           //未知
}em_valve_status;

#define  VALVE_STUDY_MIN       50
#define  VALVE_STUDY_MAX       1000

#define  VALVE_PULSE_RANGE_OPEN      4000
#define  VALVE_PULSE_RANGE_CLOSE     100

#ifdef      APP_VALVE_C
    #define APP_VALVE_C
#else
    #define APP_VALVE_C extern 
#endif

typedef struct tag_control
{
	unsigned char  delay ;
	unsigned char  close ;
    unsigned char  start ;
}control_t ;	

typedef struct tag_valve
{
	control_t      control[va_max] ;
	unsigned short study_timer ;
	unsigned char  status ;
    unsigned char  Null ;	
}tagvalve;	


APP_VALVE_C   tagvalve  valve ;

void valve_working(void);
void valve_open_set(unsigned char name,unsigned char delay,unsigned char close);
void valve_clear_set(void);
void valve_check_task(void);

#endif
