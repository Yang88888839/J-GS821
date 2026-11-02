
#ifndef __DRIVER_RTC_H
#define __DRIVER_RTC_H

#include "rtc.h"

typedef struct tag_rtc_hex
{
	unsigned short year ;
	unsigned char  month ;
	unsigned char  day ;
	unsigned char  hour ;
	unsigned char  min ;
	unsigned char  sec ;
}rtc_hex_t ;	

#ifdef      DRIVER_RTC_C
    #define DRIVER_RTC_C

#else
    #define DRIVER_RTC_C  extern
		
#endif

void Init_rtc(void);
void Rtc_set(stc_rtc_time_t *tm);		
unsigned char Rtc_read(stc_rtc_time_t *tm);
void Rtc_time_printf(void);

unsigned int system_second_read(void);	
struct tm system_second_convert(unsigned int *sec);

#endif
