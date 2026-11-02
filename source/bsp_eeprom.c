
#define  BSP_EEPROM_C

#include "stdio.h"
#include "rtc.h"
#include "time.h"
#include "main.h"
#include "driver_rtc.h"
#include "driver_uart.h"
#include "driver_flash.h"
#include "driver_lptim.h"

#include "bsp_log.h"
#include "bsp_gas.h"
#include "bsp_part.h"
#include "bsp_string.h"
#include "bsp_eeprom.h"
#include "bsp_module.h"
//---------------------------------------------------------------
#define  EEPROM_ADDRESS_BASE    0x0001F000

#define  eeprom_page_one        0       
#define  eeprom_page_two        1
#define  eeprom_page_cal        2
#define  eep_read(i)            (*(volatile unsigned int *)(EEPROM_ADDRESS_BASE+i))
#define  eep_Erase(i)	        Flash_Erase(EEPROM_ADDRESS_BASE+(i*0x200))
#define  eep_write(a,b,c)       Flash_Write(EEPROM_ADDRESS_BASE+a,b,c)

#define  flash_error            0
#define  flash_normal           1 

unsigned int datum_zero =0;
/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned char Flash_read_find(void)
{
	unsigned int i =0 ;
	unsigned int heard,erase ;
	
	for(i=0;i<1024;i+=64)
	{
		heard = eep_read(0);
		erase = eep_read(i+4);
		if((heard==0x55555555)&&(erase==0xffffffff))
		{
		    eep.addr_read = i ;      
			eep.addr_write = i+64 ;       
			if(eep.addr_write>=1024)
			{
				eep.addr_write=0;
			}
			return 1;
		}	
	}
	eep.addr_read=1024-64;
	eep.addr_write=0;                 
	eep_Erase(0);
	eep_Erase(1);
	return 0 ;		
}	
/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned char Flash_blank_find(void)
{
	unsigned short int i ;
	unsigned char j ;
		
	for(i=0;i<1024;i+=64)
	{
		for(j=0;j<64;j+=4)
		{
			if(eep_read(eep.addr_write+j)!=0xffffffff)
			{
				eep_write(eep.addr_write+4,&datum_zero,1);
				break;
			}
			if(j>=60)
			{
				return 1 ;
			}
		}
		eep.addr_write +=64 ;
		if(eep.addr_write>=1024)
		{
			eep.addr_write=0;
		}	
	}
	eep.addr_read=1024-64;
	eep.addr_write=0;                      
	eep_Erase(0);
	return 0 ;		
}	
/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_erase_judge(void)
{
	if((eep.addr_write>0x100)&&(eep.addr_write<0x180))
	{
		if(eep_read(0x280)!=0xffffffff)
		{
			eep_Erase(1);
		}
	}	
	if((eep.addr_write>0x300)&&(eep.addr_write<0x380))
	{
		if(eep_read(0x100)!=0xffffffff)
		{	
		    eep_Erase(0);
		}	
	}		
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned int Flash_sum_create(unsigned int *buf,unsigned short length)
{
	unsigned short i,j ;
	unsigned int sum=0;
	
	j = length-1 ;
	for(i=0;i<j;i++)
	{
		sum += buf[i];
	}
	return sum ;
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned char Flash_sum_check(unsigned int *buf,unsigned short length)
{
	unsigned short i,j ;
	unsigned int sum=0;
	
	j = length-1;
	for(i=0;i<j;i++)
	{
		sum += buf[i];
	}
	if(sum==buf[j])
	{
		return 1 ;
	}	
	else
	{
		return 0;
	}	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_write_smart(void)
{
    unsigned char i,result;
	
	for(i=0;i<8;i++)
	{
		Flash_read_find();
		Flash_blank_find();
		eep.sys.byte.heard = 0x55555555 ;
		eep.sys.byte.erase = 0xffffffff ;
		eep.sys.buffer[15]=Flash_sum_create(&eep.sys.buffer[0],16);
		result=eep_write(eep.addr_write,&eep.sys.buffer[0],16);
		eep_write(eep.addr_read+4,&datum_zero,1);
		Flash_erase_judge();	
		#if FLASH_PRINT
		myprintf("r_add=0x%04x\r\n",eep.addr_read);
		myprintf("w_add=0x%04x\r\n",eep.addr_write);
		#endif			
		if(flash_normal==result)
		{
			break;
		}	
	}
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_lifeover_judge(void)
{
	if(eep.sys.byte.life_ticker>C_time_life_over)
	{	
		if(f_fault_lifeover==0)
		{
			if(log_message_find(FlashLife,0)==0)
			{
				log_write(FlashLife);
			}	
			f_fault_lifeover=1;	
		}	
	}
	else
	{
		f_fault_lifeover =0 ;
	}
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_read_params(void)
{
	unsigned char i ;
	
	if(Flash_read_find()==0)
	{ 	
		myprintf("param null...\r\n"); 
		eep.sys.byte.rtc_init=255 ;
		eep.sys.byte.life_ticker= 0 ;
		eep.sys.byte.valve_width= 0xffffffff;
		Flash_write_smart();		
	}
    else
    {
		for(i=0;i<16;i++)
		{
			eep.sys.buffer[i] = eep_read(eep.addr_read+(i*4)) ;
		}
		if(Flash_sum_check(&eep.sys.buffer[0],16)==1)
		{
			myprintf("r_normal...\r\n");
		}	
		else
		{
			eep.sys.byte.valve_width= 0xffffffff;
			eep.sys.byte.life_ticker= 0  ;
			Flash_write_smart();
			myprintf("r_error...\r\n");					
		}		
	}
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_factory_write(unsigned short addr,unsigned int *datum,unsigned char len)
{
	unsigned char i ;
	unsigned char int_addr ;

	int_addr = addr>>2;
	for(i=0;i<64;i++)
	{
		eep_one.buf_int[i] = eep_read(EEP_ADDR_FACTORY+(i*4));
	}
	for(i=0;i<len;i++)
	{
		eep_one.buf_int[int_addr+i] = datum[i];
	}
	eep_one.buf_int[63] = Flash_sum_create(&eep_one.buf_int[0],64);
	eep_Erase(eeprom_page_cal);
	eep_write(EEP_ADDR_FACTORY,&eep_one.buf_int[0],64);
	eep_write(EEP_ADDR_FACTORY_BK,&eep_one.buf_int[0],64);
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_factory_read(unsigned short addr,unsigned int *datum,unsigned char len)
{
	unsigned char i ;

	for(i=0;i<len;i++)
	{
		datum[i] = eep_read(EEP_ADDR_FACTORY+addr+(i*4));
	}	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_factory_params(void)
{
	Flash_factory_read(EEP_ADDR_CAL,&eep.cal.buffer[0],16);
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_get_uuid(void)
{
	unsigned char buf[10];
	Byte_int_t temp1,temp2;
	memcpy((void *)(buf), (unsigned char *)0x00101E8C,10);
	
	for(int i=0;i<4;i++)
	{
		temp1.bytes[i] = buf[i];
		temp2.bytes[i] = buf[i+4];
	}
	temp1.value += temp2.value;
	temp1.value += buf[8] ;
	temp1.value += buf[9] ;
	for(int i=0;i<4;i++)
	{
		eep.cal.byte.serial.sn[i]=temp1.bytes[i];
	}
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_set_rtc_flag(void)
{
	if(eep.sys.byte.rtc_init!=0x55)
	{
		eep.sys.byte.rtc_init=0x55;
		Flash_write_smart();				
	}		
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned char Flash_factory_check(void)
{
	unsigned char i,result=0 ;	

	for(i=0;i<64;i++)
	{
		eep_one.buf_int[i] = eep_read(EEP_ADDR_FACTORY+(i*4));
		eep_two.buf_int[i] = eep_read(EEP_ADDR_FACTORY_BK+(i*4));
	}
	if(Flash_sum_check(&eep_one.buf_int[0],64)==1)
	{ 
		result|=0x01;
	}	
	if(Flash_sum_check(&eep_two.buf_int[0],64)==1)
	{ 
		result|=0x02;
	}	
    if(result==3)
	{
		myprintf("cal_normal...\r\n");
		return 1;
	}
    if(result==1)
	{
		eep_Erase(eeprom_page_cal);
		eep_write(EEP_ADDR_FACTORY,&eep_one.buf_int[0],64);
		eep_write(EEP_ADDR_FACTORY_BK,&eep_one.buf_int[0],64);
        return 0 ;		
	}	
    if(result==2)
    {
		eep_Erase(eeprom_page_cal);
		eep_write(EEP_ADDR_FACTORY,&eep_two.buf_int[0],64);
		eep_write(EEP_ADDR_FACTORY_BK,&eep_two.buf_int[0],64);
        return 0 ;		
	}		
	myprintf("cal_error...\r\n");
    return 3 ;	
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void eeprom_test(void)
{
	#if FLASH_PRINT
	unsigned int i,j,m ;
	
	myprintf("flash-test...\r\n");
	for(i=0;i<2048;i+=64)
	{   	
		for(j=0;j<64;j+=4)
		{
		    m = eep_read(i+j);
			myprintf("%08x",m);			
		}
        myprintf("\r\n");                		
	}
	#endif
}














