
#ifndef BSP_EEPROM_H
#define BSP_EEPROM_H

#define EEP_ADDR_CAL        0     
#define EEP_ADDR_URL        64   
#define EEP_ADDR_USERID     128   
#define EEP_ADDR_PASSWORD   160   

#define EEP_ADDR_SUM        63    

#define EEP_ADDR_FACTORY    0x400
#define EEP_ADDR_FACTORY_BK 0x500

#define MODULE_UPLOAD_URL      "10427645.non-nb.ctwing.cn"
#define MODULE_UPLOAD_USERID   "17262945"
#define MODULE_UPLOAD_PASSWORD "ri48W2-CMuqkINtmfMoWmvwQ1ICbxO6QHdfA-xfsK5Q"

typedef struct tag_product_date
{
	unsigned char year_h ;
	unsigned char year_l ;
	unsigned char month ;
	unsigned char day ;
}product_date_t;

typedef struct tag_product_serial
{
	unsigned char sn[4] ;
}product_serial_t;

typedef union tag_sys
{
	unsigned int buffer[16];
	struct
	{
		unsigned int heard ;
		unsigned int erase ;
		
		unsigned char null_1 ;
		unsigned char null_2 ;
		unsigned char rtc_init ;
		unsigned char factory_status;
		
		unsigned int  life_ticker ;
		unsigned int  valve_width ;
	}byte;
}tagsys_t;

typedef union tag_cal
{
	unsigned int buffer[16];
	struct
	{
		unsigned char flag_init ;		
		unsigned char null_1 ;
		unsigned char null_2 ;
        unsigned char null_3 ;
		product_serial_t serial ;
        product_date_t date ;	
	}byte;
}tagcal_t;

typedef struct tag_eep
{
	unsigned int addr_read ;
	unsigned int addr_write ;
    tagcal_t     cal ;
	tagsys_t     sys ;
}tageep;

typedef union tag_eep_save
{
	unsigned char buf_char[256];
	unsigned int buf_int[64];
}eep_save_t ;	

#ifdef      BSP_EEPROM_C
    #define BSP_EEPROM_C
#else
    #define BSP_EEPROM_C  extern 
#endif
	
BSP_EEPROM_C  tageep      eep     __attribute__ ((aligned(4)));		
BSP_EEPROM_C  eep_save_t  eep_one __attribute__ ((aligned(4)));
BSP_EEPROM_C  eep_save_t  eep_two __attribute__ ((aligned(4)));	
	
void Flash_write_smart(void);
void Flash_read_params(void);
void Flash_lifeover_judge(void);	
	
void Flash_factory_write(unsigned short addr,unsigned int *datum,unsigned char len);
void Flash_factory_read(unsigned short addr,unsigned int *datum,unsigned char len);
void Flash_factory_params(void);
unsigned char Flash_factory_check(void);
void Flash_get_uuid(void);
void Flash_set_rtc_flag(void);	
	
void eeprom_test(void);	

#endif












