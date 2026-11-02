
#ifndef __DRIVER_LPUART_H
#define __DRIVER_LPUART_H

#include "lpuart.h"

typedef struct tag_lpusart
{
	unsigned char  buf[512] ;
	unsigned short length;
	unsigned char timer ;
	unsigned char done;
}taglpusart;


#ifdef      DRIVER_LPUART_C
    #define DRIVER_LPUART_C   
#else
    #define DRIVER_LPUART_C   extern		
#endif 

DRIVER_LPUART_C  taglpusart    lpuart1;

void Init_lpusart1(void);
void lpuart1_receive_timer(void);	
void lpuart_senddata(M0P_LPUART_TypeDef *LPUARTx, uint16_t u16Data);	
   

#endif
