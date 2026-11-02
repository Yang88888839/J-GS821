
#ifndef __DRIVER_ADC_H
#define __DRIVER_ADC_H




#ifdef      DRIVER_ADC_C
    #define DRIVER_ADC_C

#else
    #define DRIVER_ADC_C  extern
		
#endif

void Init_Adc(void);
unsigned short get_sensor_voltage(void);
unsigned short get_vcc_voltage(void);
signed char get_temperature(void);	



#endif
