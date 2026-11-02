
#ifndef __DRIVER_LPTIM_H
#define __DRIVER_LPTIM_H



#ifdef      DRIVER_LPTIM_C
    #define DRIVER_LPTIM_C

#else
    #define DRIVER_LPTIM_C  extern
		
#endif

void Init_lptim0(void);
void debug_send_string(char *str);

#endif
