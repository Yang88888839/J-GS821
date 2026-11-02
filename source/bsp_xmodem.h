#ifndef  BSP_XMODEM_H
#define  BSP_XMODEM_H

#define  ota_read_head(i)              (*(volatile unsigned char *)(0x00010000+i))
#define  ota_read_len(i)               (*(volatile unsigned char *)(0x00010004+i))
#define  ota_read_crc(i)               (*(volatile unsigned char *)(0x00010008+i))	
#define  ota_read_ver(i)               (*(volatile unsigned char *)(0x0001000c+i))
#define  ota_read_flag(i)	           (*(volatile unsigned char *)(0x00010010+i))	

//#define  ota_read_firmware(i)          (*(volatile unsigned char *)(0x00010040+i))
#define  ota_addr_flag                 0x00010010 
#define  ota_addr_firmware             0x00010040 
enum
{
	ota_normal=1,
	ota_error_version_same,
	ota_error_length,
	ota_error_crc16,	
	ota_error_flag,
    ota_error_head,	
};	

#ifdef          BSP_XMODEM_C
      #define   BSP_XMODEM_C 
     
#else       
      #define   BSP_XMODEM_C  extern      
#endif 

void Flash_ota_erase(void);	  
void xmodem_receive(void); 
signed char ota_file_check(void);
#endif

