
#define BSP_LOG_C

#include "stdio.h"
#include "rtc.h"
#include "time.h"
#include "main.h"
#include "driver_rtc.h"
#include "driver_uart.h"
#include "driver_flash.h"
#include "driver_lpuart.h"

#include "bsp_log.h"
#include "bsp_part.h"
#include "bsp_eeprom.h"
#include "bsp_sound_led.h"

#define log_send(a)       uart_senddata(M0P_USART0,a)
#define log_re_done       uart0.done
#define log_re_length     uart0.length
#define log_re_buf        uart0.buf
#define log_re            uart0


#define  flash_log_read(i)   (*(volatile unsigned int *)(0x00000000+i))

typedef union tag_logbuf
{
	unsigned int buf[2] ;
	struct 
	{
		unsigned short int head ;
		unsigned short int year ;
		unsigned char month ;
		unsigned char day ;
		unsigned char hour ;
		unsigned char min ;
	}byte ;
}taglogbuf ;	
	
unsigned char log_buffer[20] ;	
unsigned char log_control_c1 ;
unsigned char log_control_c2 ;

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned int log_blank_find(tagLogAddr addr)
{
	unsigned int i ;
	
	for(i=addr.start;i<addr.over;i+=4)
	{
		if(flash_log_read(i)==0xffffffff)
		{
			return i ;
		}	
	}
    return 0 ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void log_write(tagLogAddr addr)
{	
	unsigned int i,j,*p ;
    unsigned int addr_write,sec ;
	//--------------------------------------------------------------------
	addr_write=log_blank_find(addr);
	sec = system_second_read();
    //--------------------------------------------------------------------
	if(addr_write>0)
	{
        Flash_Write(addr_write,&sec,1);		
	}
    else
    {
		p= &flash_buffer_public[0] ;
		for(i=addr.start;i<addr.over;i+=4,p++)        
		{
			*p = flash_log_read(i);
		}
		for(i=addr.start;i<addr.over;i+=512)          
		{
			Flash_Erase(i);
		}
		for(i=addr.start,j=1;i<addr.over-4;i+=4,j++)  
		{
			Flash_Write(i ,&flash_buffer_public[j],1);
		}
		Flash_Write(addr.over-4,&sec,1);
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return: 
-----------------------------------------------------------------------------*/
void log_erase_all(void)
{
	unsigned int i ;
	for(i=flash_alarm_enter_start;i<flash_life_over;i+=512) 
	{
		Flash_Erase(i);
	}	
}	

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned int log_find(tagLogAddr addr)
{
	unsigned int  i,j=0 ;
		
	for(i=addr.start;i<addr.over;i+=4)
	{		
		if(flash_log_read(i)==0xffffffff)
		{
			break;
		}	
		j++;
	}
    return j ;		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void log_packet_total(void)
{
	unsigned char i ;

	log_buffer[0 ]= 0xaa ;
	log_buffer[1 ]= 0 ;  //非数据记录  
    log_buffer[2 ]= 0 ;  //功能码
    log_buffer[3 ]= 12;	 //数据长度
	log_buffer[4 ]= log_find(FlashAlarm_enter);
	log_buffer[5 ]= log_find(FlashAlarm_exit);
	log_buffer[6 ]= log_find(FlashFault_enter);
	log_buffer[7 ]= log_find(FlashFault_clear);
	log_buffer[8 ]= log_find(FlashPower_down);
	log_buffer[9 ]= log_find(FlashPower_on);
	log_buffer[10]= log_find(FlashLife);
	log_buffer[11]= log_find(FlashMute);
	log_buffer[12]= log_find(FlashCheck);
	log_buffer[13]= log_find(FlashValve_on);
	log_buffer[14]= log_find(FlashValve_feedback);	
	log_buffer[15]= 0 ;   //其它记录总数
	log_buffer[16]= 0 ;   //校验
	log_buffer[17]= 0x55 ;//结束
	for(i=0;i<16;i++)
	{
		log_buffer[16]+=log_buffer[i] ;
	}
    for(i=0;i<18;i++)
	{
		log_send(log_buffer[i]);
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned int log_message_find(tagLogAddr addr,unsigned char number)
{
	unsigned int  temp ;
	unsigned int  log_sec=0 ;
	
	if(addr.start==flash_life_start)
	{
	    temp = addr.start ;  
	}	
	else
	{		
		temp = addr.start +(number*4);
	}	
	if(temp<addr.over)
	{
		log_sec = flash_log_read(temp);
		if(log_sec==0xffffffff)
		{
			log_sec=0;
		}	
	}
	return log_sec ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void log_packet_message(tagLogAddr addr_in,unsigned char number)
{  
	unsigned int  i,log_sec ;	
	struct tm timer;
	
	if(number==0)
	{
		return ;
	}
    number--;	
	log_sec = log_message_find(addr_in,number);	
    #if DEBUG
	myprintf("LOG_ADD=0x%08x\r\n",log_sec);	
    #endif
	if(log_sec>0)
	{
		timer          = system_second_convert(&log_sec);
		log_buffer[5 ] = timer.tm_year>>8 ;    //year
		log_buffer[6 ] = timer.tm_year&0xff ;  //year
		log_buffer[7 ] = timer.tm_mon ;        //month
		log_buffer[8 ] = timer.tm_mday ;       //day
		log_buffer[9 ] = timer.tm_hour ;        //hour
		log_buffer[10] = timer.tm_min ;        //minute		
	}
    else
    {
		log_buffer[5 ] =0 ;
		log_buffer[6 ] =0 ;	
		log_buffer[7 ] =0 ;
		log_buffer[8 ] =0 ;	
		log_buffer[9 ] =0 ;
		log_buffer[10] =0 ;			
	}
	log_buffer[0 ]= 0xaa ;
	log_buffer[1 ]= log_control_c1 ;
    log_buffer[2 ]= log_control_c2 ;
    log_buffer[3 ]= 7 ;
	log_buffer[4 ]= log_control_c1 ;
	log_buffer[11]= 0 ;
	log_buffer[12]= 0x55 ;
	for(i=0;i<11;i++)
	{
		log_buffer[11]+=log_buffer[i] ;
	}
    for(i=0;i<13;i++)
	{
		log_send(log_buffer[i]);
	}	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void log_packet_date(void)
{
	unsigned char i ;
	unsigned short int year ;
    stc_rtc_time_t tm ;	
	
	if(Rtc_read(&tm)!=0)
	{
		return ;
	}
    tm.u8Year  = convert_bcdTOhex(tm.u8Year);
    tm.u8Month = convert_bcdTOhex(tm.u8Month);	
	tm.u8Day   = convert_bcdTOhex(tm.u8Day);
	tm.u8Hour  = convert_bcdTOhex(tm.u8Hour);
	tm.u8Minute= convert_bcdTOhex(tm.u8Minute);
	year = 2000+tm.u8Year ;
	
	log_buffer[0 ]= 0xaa ;
	log_buffer[1 ]= 0x00 ;
    log_buffer[2 ]= log_control_c2 ;
    log_buffer[3 ]= 6 ;
	log_buffer[4 ]= year>>8 ;	
	log_buffer[5 ]= year&0xff;
	log_buffer[6 ]= tm.u8Month;
	log_buffer[7 ]= tm.u8Day;
	log_buffer[8 ]= tm.u8Hour;
	log_buffer[9 ]= tm.u8Minute;
	log_buffer[10]= 0 ;
	log_buffer[11]= 0x55 ;
	for(i=0;i<10;i++)
	{
		log_buffer[10]+=log_buffer[i] ;
	}
    for(i=0;i<12;i++)
	{
		log_send(log_buffer[i]);
	}		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return: 
-----------------------------------------------------------------------------*/
unsigned char log_packet_check(tagusart *ua)
{
	unsigned char i,sum=0;
		
	if((ua->buf[0]!=0xaa)||(ua->buf[ua->length-1]!=0x55))
	{
		return 0 ;
	}	
	for(i=0;i<ua->length-2;i++)
	{
		sum += ua->buf[i] ;		
	}
	if(ua->buf[ua->length-2]==sum)
	{
		return 1 ;
	}
    else
    {
		return 0 ;
	}		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return: 
-----------------------------------------------------------------------------*/
void rtc_calibration_dispose(void)
{
	stc_rtc_time_t rtc_time ;	
	unsigned char temp[8] ;

	if(0x54==log_re_buf[3])
	{
		Rtc_read(&rtc_time); 
		temp[0] = log_re_buf[4 ];
		temp[1] = log_re_buf[5 ];
		temp[2] = log_re_buf[6 ];
		temp[3] = log_re_buf[7 ];
		temp[4] = log_re_buf[8 ];
		temp[5] = log_re_buf[9 ];
		temp[6] = log_re_buf[10];
        	
		if((rtc_time.u8Minute    ==temp[1])&& 
		   (rtc_time.u8Hour      ==temp[2])&&
	       (rtc_time.u8DayOfWeek ==temp[3])&&
		   (rtc_time.u8Day       ==temp[4])&&
		   (rtc_time.u8Month     ==temp[5])&& 
		   (rtc_time.u8Year      ==temp[6]))
		{		 
			if((rtc_time.u8Second<(temp[0]+2))&&
			   (rtc_time.u8Second>(temp[0]-2)))
			{
				eep.sys.byte.rtc_init=0x55;
				Flash_write_smart();
				return ;
			}	
		}
		rtc_time.u8Second    = temp[0];
		rtc_time.u8Minute    = temp[1];
		rtc_time.u8Hour      = temp[2];
		rtc_time.u8DayOfWeek = temp[3];
		rtc_time.u8Day       = temp[4];	 
		rtc_time.u8Month     = temp[5];
		rtc_time.u8Year      = temp[6];	
		Rtc_set(&rtc_time);
        Flash_set_rtc_flag();		
     }	 
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void log_receive_dispose(void)
{
	if(log_re_done==0)
	{
		return ;
	}
	myprintf("log_rec=");
	for(char i=0;i<log_re_length;i++)
	{
		myprintf("%02x",log_re_buf[i]);
	}
	if(log_packet_check(&log_re)==0)
	{
		log_re_done=0;
		log_re_length=0 ;
		return ;
	}	
    log_control_c1= log_re_buf[1];
	log_control_c2= log_re_buf[2];
	myprintf("log_in...\r\n");
	switch(log_control_c2)
	{
		case  0x00  :
			        if(log_control_c1==0)
					{
						log_packet_total();
					} 	 
		            break;
		case  0x01  :	 
		            log_packet_message(FlashAlarm_enter,log_control_c1);
		            break;
		case  0x02  :	 
		            log_packet_message(FlashAlarm_exit,log_control_c1);
		            break;
		case  0x03  :	 
		            log_packet_message(FlashFault_enter,log_control_c1);
		            break;
		case  0x04  :	 
		            log_packet_message(FlashFault_clear,log_control_c1);
		            break;
		case  0x05  :	 
			        log_packet_message(FlashPower_down,log_control_c1);
		            break;
		case  0x06  :	 
			        log_packet_message(FlashPower_on,log_control_c1);
		            break;	
		case  0x07  :	 
			        log_packet_message(FlashLife,log_control_c1);
		            break;
		case  0x08  :	 
		            if(log_control_c1==0)
					{						 
		               log_packet_date();
					}	
		            break;
		case  0x09  ://报警消音	 
			        log_packet_message(FlashMute,log_control_c1);
		            break;					
		case  0x0A  ://自检	 
			        log_packet_message(FlashCheck,log_control_c1);
		            break;					
		case  0x0B  ://阀门启动	 
			        log_packet_message(FlashValve_on,log_control_c1);
		            break;
		case  0x0C  ://关阀	 
			        log_packet_message(FlashValve_feedback,log_control_c1);
		            break;		
        case  0x53  :
                    if(log_control_c1==0)
                    {
					    rtc_calibration_dispose();
					}						
        default     :
                    break;			
	}	
	log_re_done=0;
	log_re_length=0 ;
}
	
/*----------------------------------------------------------------------
Function:
----------------------------------------------------------------------*/
void rtc_calibration_send(void)
{
	unsigned char i ;

	log_buffer[0 ]= 0xaa ;
	log_buffer[1 ]= 0x53 ;
    log_buffer[2 ]= 0x49 ;
    log_buffer[3 ]= 0x54 ;
	log_buffer[4 ]= 0x45 ;
	log_buffer[5 ]= 0x52 ;	
	log_buffer[6 ]= 0x57 ;
	log_buffer[7 ]= 0x45 ;
	log_buffer[8 ]= 0x4c ;
	log_buffer[9 ]= 0x4c ;
	log_buffer[10]= 0x65 ;
	log_buffer[11]= 0x55 ;

    for(i=0;i<12;i++)
	{
		log_send(log_buffer[i]);
	}	 
}

/*----------------------------------------------------------------------
Function:
----------------------------------------------------------------------*/
void log_test(void)
{
	#if FLASH_PRINT
	unsigned int i,j,m ;
	
	myprintf("flash-test...\r\n");
	for(i=0;i<1024;i+=64)
	{   	
		for(j=0;j<64;j+=4)
		{
		    m = flash_log_read(FlashMute.start+i+j);
			myprintf("%08x",m);			
		}
        myprintf("\r\n");                		
	}
	#endif
}


































