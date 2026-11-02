
#ifndef  BSP_FACTORY_H
#define  BSP_FACTORY_H




#ifdef      BSP_FACTORY_C
    #define BSP_FACTORY_C
#else
    #define BSP_FACTORY_C extern 
#endif

void factory_handler(void);	
	
	
#endif
