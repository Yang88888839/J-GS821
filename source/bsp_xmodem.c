
#define   BSP_XMODEM_C

#include "bt.h"
#include "lpm.h"
#include "gpio.h"
#include "driver_flash.h"
#include "driver_gpio.h"
#include "driver_lpuart.h"

#include "stdio.h"
#include "main.h"
#include "bsp_log.h"
#include "bsp_key.h"
#include "bsp_gas.h"
#include "bsp_part.h"
#include "bsp_valve.h"
#include "bsp_queue.h"
#include "bsp_eeprom.h"
#include "bsp_module.h"
#include "bsp_string.h"
#include "bsp_xmodem.h"
/*---------------------------------includes---------------------------------*/
#include "FreeRTOS.h"
#include "app_work_4.h"
#include "task.h"
/*--------------------------------------------------------------------------*/
#define ota_send(a)       lpuart_senddata(M0P_LPUART1,a)
#define ota_re_done       lpuart1.done
#define ota_re_length     lpuart1.length
#define ota_re_buf        lpuart1.buf
/*--------------------------------------------------------------------------*/
#define XM_SOH            0x01
#define XM_EOT            0x04
#define XM_EOF            0x1A
#define XM_ACK            0x06
#define XM_NAK            0x15
#define XM_CAN            0x18
#define XM_CRC            'C'
/*--------------------------------------------------------------------------*/
#define XMODEM_ACK         1
#define XMODEM_NAK        -1
#define XMODEM_EOT        -2
#define XMODEM_EOF        -3

#define  flash_ota_start  0x00010000             
#define  flash_ota_over   0x0001d000 
/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return: 
-----------------------------------------------------------------------------*/
void Flash_ota_erase(void)
{
	unsigned int i ;
	for(i=flash_ota_start;i<flash_ota_over;i+=512) 
	{
		Flash_Erase(i);
	}	
}

/*---------------------------------------------------------------------------
 * @brief 
 * @output
 * @return
---------------------------------------------------------------------------*/
void Flash_ota_write(unsigned char *in_data,unsigned int total)
{
	unsigned int addr ;
	addr = flash_ota_start + (total*128) ;
	Flash_Write(addr,&array_temp.buf_32b[0],32);
}

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned short crc16_xmodem(unsigned char *data,unsigned int len)
{
	unsigned int i ;
	unsigned short crc = 0x0000;
    for (i = 0; i < len; i++) 
	{
        crc ^= (unsigned short)((unsigned short)data[i] << 8);
        for (int j = 0; j < 8; j++)
		{
            crc = (crc & 0x8000) ? (unsigned short)((crc << 1) ^ 0x1021)
                                 : (unsigned short)(crc << 1);
		}	
    }
    return crc;
}
	
/*---------------------------------------------------------------------------
 * @brief 
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned char xmodem_write_dispose(unsigned char *buf,unsigned char in_seq)	
{
	unsigned short crc_result,crc_input;
	unsigned char i,j;
    if((buf[1]+buf[2])!=0xff)//反码不正确
	{
		ota_send(XM_NAK);
		return 0;
	}	 
	if(buf[1]==in_seq)//编号一致
	{
		crc_result = crc16_xmodem(&buf[3],128);
		crc_input = (unsigned short)(buf[131]<<8) | buf[132] ;
		if(crc_result==crc_input)
		{
			for(i=0,j=3;i<128;i++,j++)
			{
				array_temp.buf_8b[i]=buf[j];
			}
			ota_send(XM_ACK);
            return 1 ;			
		}
	}
    ota_send(XM_NAK);
	return 0 ;
}	

/*---------------------------------------------------------------------------
 * @brief XMODEM 接收主函数
 * @output
 * @return
---------------------------------------------------------------------------*/
void xmodem_receive(void)
{
	unsigned short packet_total=0;
	unsigned short timer ;
	unsigned char seq=1 ;
	ota_re_done=0;
	ota_re_length=0;
	for(timer=100;timer>0;timer--)
	{
        if((timer%20)==0)
        {
			ota_send(XM_CRC);
		}
        if(ota_re_done)
        {
			timer=300;
			break;
		}
        vTaskDelay(10);		
	}	
    if(timer==0)
	{
		return ;
	}
    while(timer--)
	{
        if((timer==100)||(timer==200))
        {
			ota_send(XM_NAK);
		}
        if(ota_re_done)
        {
			switch(ota_re_buf[0])
			{
				case XM_SOH://数据传输
					 if(xmodem_write_dispose(&ota_re_buf[0],seq)==1)
					 {
						 timer=300;
						 Flash_ota_write(&ota_re_buf[3],packet_total);
						 packet_total++;
                         seq++;						 
					 }					 
				     break;
				case XM_EOT://传输结束			
				case XM_EOF://文件结束		
				case XM_CAN://取消
					 ota_send(XM_ACK);
				     goto ota_over;
                default:    //未知命令
					 ota_send(XM_NAK);
                     break;					
			}	
			ota_re_length=0;
			ota_re_done=0;
		}
		if(packet_total>=415)//超出OTA升级空间
		{
			break;
		}	
        vTaskDelay(10);	
        f_task4_run=1;		
	}
	ota_over:	
    ota_send(XM_CAN);
    ota_send(XM_CAN);
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
signed char ota_file_check(void)
{
	int j=4;
	Byte_int_t ota_head ;
	Byte_int_t ota_flag ;
	Byte_int_t ota_len ;
	Byte_int_t ota_crc ;
	Byte_int_t ota_ver ;
	unsigned short crc_count;
	unsigned int   old_version;
	
	for(int i=0;i<4;i++)
	{
		j--;
		ota_head.bytes[i]= ota_read_head(j);
		ota_flag.bytes[i]= ota_read_flag(j);
		ota_len.bytes[i] = ota_read_len(j);
		ota_crc.bytes[i] = ota_read_crc(j);
		ota_ver.bytes[i] = ota_read_ver(j);
	}
	old_version=convert_stringTOhex(APP_VERSION);
	myprintf("ota_head=%08x ",ota_head.value);
	myprintf("ota_len=%08x " ,ota_len.value);
	myprintf("ota_crc=%08x " ,ota_crc.value);
    myprintf("ota_ver=%08x " ,ota_ver.value);
	if(ota_head.value!=0x55aa9966)
	{
		return ota_error_head ;
	}
	if(ota_len.value>53200)//固件超出APP范围
	{
		return ota_error_length ;
	}		
	if(ota_flag.value!=0xffffffff)
	{
		return ota_error_flag ;
	}	
	if(ota_ver.value==old_version)//升级版本与当前版本相同
	{
		ota_flag.value=0;
		Flash_Write(ota_addr_flag,&ota_flag.value,1);
		return ota_error_version_same ;
	}
	crc_count=crc16_xmodem((unsigned char*)ota_addr_firmware,ota_len.value);	
	myprintf("firmware_crc=%08x ",crc_count);
    if(ota_crc.value==crc_count)//CRC正确	
	{
		return ota_normal ;
	}
    else
    {
		return ota_error_crc16 ;
	}		
}





