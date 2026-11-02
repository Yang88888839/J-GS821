#ifndef   DRIVER_TEMPERATURE_C
#define   DRIVER_TEMPERATURE_C


#ifdef        DRIVER_TEMPERATURE_C

	#define   DRIVER_TEMPERATURE_C
	//content

#else
	#define   DRIVER_TEMPERATURE_C  extern
	//content

#endif

DRIVER_TEMPERATURE_C    signed char temperature_read(void);
DRIVER_TEMPERATURE_C	void temperature_judge_fault(void);

#endif 	
	
	
	
	

