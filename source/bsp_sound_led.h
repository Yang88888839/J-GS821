#ifndef  BSP_SOUND_LED_H
#define  BSP_SOUND_LED_H

#define  alarm_test_init()     voice.DBlow=0
#define  alarm_sensor_init()   voice.DBlow=0

#define  SOUND_CLASS_45DB      1
#define  SOUND_CLASS_55DB      2
#define  SOUND_CLASS_70DB      3
#define  SOUND_CLASS_80DB      4
#define  SOUND_CLASS_85DB      5
#define  SOUND_CLASS_MAX       6

#define  INDICATE_FAULT_SENSOR      2
#define  INDICATE_FAULT_LIFEOVER    3
#define  INDICATE_FAULT_VALVE       4


typedef enum
{   
	colour_valve=0 ,
	colour_lifeover,	
 	colour_yellow ,
	colour_green ,
	colour_green_weak ,
	colour_blue ,
	colour_red ,
	colour_max ,
}led_colour;

#ifdef      BSP_SOUND_LED_C
    #define BSP_SOUND_LED_C
#else
    #define BSP_SOUND_LED_C extern 
#endif


typedef struct tag_voice
{
    unsigned char  volume ;   //可以用局部变量	
	unsigned char  DBlow; 
    unsigned char  cyc ;
    unsigned char  open ;
    unsigned char  close ;
    unsigned char  open_bk ;
    unsigned char  close_bk ;
    
}tagvoice;

typedef struct tag_led
{
	unsigned char cyc ;
	unsigned char open ;
	unsigned char close ;
	unsigned char open_bk ;
	unsigned char close_bk ;	
}tagled ;



BSP_SOUND_LED_C   tagled    led[colour_max] ;  
BSP_SOUND_LED_C   tagvoice  voice  ;

void led_open_set(led_colour name,unsigned char open,unsigned char close, unsigned char cyc);
void led_output(unsigned char name,unsigned char sta);
void led_working(void);
void voice_working(void);
void voice_open_set(unsigned char volume,unsigned char open,unsigned char close ,unsigned char cyc);
void buzzer_short(unsigned short ms);
void voice_DBlow_control(void);
void voice_alarm_control(void);
void display_PowerOn(void);
void display_handler(void);
void display_preheat(void);

void alarm_mute_exit(void);
void fault_mute_exit(void);

#endif
