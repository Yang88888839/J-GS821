
#ifndef  BSP_PART_H
#define  BSP_PART_H

typedef struct tag_average
{
	unsigned short int sum  ;
	unsigned short int minimum;
	unsigned short int maximum;
    unsigned short int number ;	
}TagAverage_t ;	


#ifdef      BSP_PART_C
    #define BSP_PART_C
#else
    #define BSP_PART_C extern 
#endif

BSP_PART_C   void delay_ms(unsigned short ms);
BSP_PART_C   void delay_10us(unsigned short us);
	
BSP_PART_C   unsigned char convert_bcdTOhex(unsigned char bcd);	
BSP_PART_C   unsigned char convert_hexTObcd(unsigned char hex);

unsigned short int create_crc(unsigned char *buf,unsigned char lenth);	
void average_init(TagAverage_t *pa);	
void average_input(TagAverage_t *pa,unsigned short in_value);
unsigned short average_count(TagAverage_t *pa,unsigned short number);	

	
#endif
