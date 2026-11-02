
#ifndef __DRIVER_TIMER_H
#define __DRIVER_TIMER_H

#define get_timer_ticker()    Bt_M0_Cnt32Get(TIM1)


#ifdef      DRIVER_TIMER_C
    #define DRIVER_TIMER_C

#else
    #define DRIVER_TIMER_C  extern
		
#endif

void Init_ClockSys(void);
	
void Init_timer0(void);	
void Init_timer1(void);
void Init_timer2(void);	

void green_pwm_output(unsigned short duty);	
void green_set_duty(unsigned short duty);	
	
void Timer1_enable(void);
unsigned int Timer1_disable(void);	
void debug_send_string(char *str);	
	

#endif
