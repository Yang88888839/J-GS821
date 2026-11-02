#define   BSP_PART_C

#include "stdio.h"
#include "sysctrl.h"

#include "main.h"
#include "bsp_part.h"
#include "bsp_eeprom.h"
#include "bsp_queue.h"

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void delay_10us(unsigned short us)
{	
	unsigned int i ;
	while(us)
	{
		for(i=29;i>0;i--)
		{
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();			
		}
		us--;		
	}
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void delay_ms(unsigned short ms)
{
	unsigned int i ;
	while(ms)
	{
		for(i=3020;i>0;i--)
		{
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();			
		}
		ms--;
	}
}

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned char convert_bcdTOhex(unsigned char bcd)
{
	return (((bcd>>4)*10) + (bcd&0xf));
}

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned char convert_hexTObcd(unsigned char hex)
{
	return (((hex/10)<<4) | (hex%10));
}

#define POLY 0xa001
/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned short int create_crc(unsigned char *buf,unsigned char lenth) 
{ 
    int i,j; 
    unsigned short int crc; 
    for(i=0,crc=0xffff;i<lenth;i++) 
    { 
        crc ^= buf[i]; 
        for(j=0;j<8;j++) 
        { 
            if(crc & 0x01) crc = (crc >> 1) ^ POLY; 
            else crc >>= 1; 
        } 
    } 
    return crc; 
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void average_init(TagAverage_t *pa)
{
	pa->sum=0;
	pa->minimum=0xffff;
	pa->maximum=0x0000;
	pa->number=0;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void average_input(TagAverage_t *pa,unsigned short in_value)
{
	pa->number++;
	pa->sum+=in_value ;
	if(pa->minimum>in_value)
	{
		pa->minimum=in_value;
	}
	if(pa->maximum<in_value)
	{
		pa->maximum=in_value;
	}		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned short average_count(TagAverage_t *pa,unsigned short number)
{
	if(pa->sum>pa->minimum)
	{
		pa->sum-=pa->minimum;
		number--;
	}
	if(pa->sum>pa->maximum)
	{
		pa->sum-=pa->maximum;
		number--;
	}	
    return (pa->sum/number);	
}

	














