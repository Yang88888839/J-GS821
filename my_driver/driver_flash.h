
#ifndef __DRIVER_FLASH_H
#define __DRIVER_FLASH_H

#ifdef      DRIVER_FLASH_C
    #define DRIVER_FLASH_C

#else
    #define DRIVER_FLASH_C  extern
		
#endif
unsigned char Flash_Erase(unsigned int addr);	
unsigned char Flash_Write(unsigned int addr,unsigned int *datum,unsigned int len);	

#endif
