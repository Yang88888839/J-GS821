
#ifndef __DRIVER_PWM_H
#define __DRIVER_PWM_H

#define FRQ_300K  0
#define FRQ_335K  0
#define FRQ_350K  1


#if   FRQ_300K
      #define PWM_BASE_FRQ  1000    //2.98K 
#elif FRQ_335K
      #define PWM_BASE_FRQ  1166    //3.50K
#elif FRQ_350K
      #define PWM_BASE_FRQ  915   //3.35K 
#endif

typedef struct Tag_frequency
{
	unsigned short cycle ;
	unsigned short duty ;
}Tag_frequency_t ;	


#ifdef      DRIVER_PWM_C
    #define DRIVER_PWM_C

#else
    #define DRIVER_PWM_C  extern
		
#endif


void Init_pwm(void);
void pwm_enable(void);
void pwm_disable(void);	
void frequency_set(unsigned short cycle,unsigned short duty);
void frequency_duty_set(unsigned char volume);



#endif
