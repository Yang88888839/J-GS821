
#ifndef __DRIVER_UART_H
#define __DRIVER_UART_H

#include "usart.h"

#define   UART_LEN_MAX   500
#define   UART_FUN_FCT   1
#define   UART_FUN_LOG   2  


typedef struct tag_usart
{
	unsigned char  buf[UART_LEN_MAX+1] ;
	unsigned short length;
	unsigned char  timer ;
	unsigned char  done;
}tagusart;


#ifdef      DRIVER_UART_C
    #define DRIVER_UART_C   
#else
    #define DRIVER_UART_C   extern		
#endif 


DRIVER_UART_C  tagusart    uart0;
DRIVER_UART_C  tagusart    uart1;	

void uart0_receive_timer(void);
void Init_usart0(void);
void Init_usart0_fun(unsigned char fun);	
void uart_send_array(M0P_USART_TypeDef *USARTx,unsigned char *buf,unsigned char len);	
	
void uart1_receive_timer(void);
void Init_usart1(void);	

void uart_senddata(M0P_USART_TypeDef *USARTx, uint16_t u16Data);	
void uart_send_string(M0P_USART_TypeDef *USARTx, char *str);
#endif
