
#define DRIVER_FLASH_C

#include "bt.h"
#include "flash.h"
#include "stdio.h"
#include "main.h"

/*-------------------------------------------------------------
//报警记录(标准要求200条)
#define   flash_alarm_enter_start  0x800d000     //256条512*2
#define   flash_alarm_enter_over   0x800d3ff     
//报警退出记录(标准要求200条)
#define   flash_alarm_exit_start   0x800d400     //256条512*2
#define   flash_alarm_exit_over    0x800d7ff     
//传感器故障记录(标准要求100条)
#define   flash_fault_enter_start  0x800d800     //128条512*1
#define   flash_fault_enter_over   0x800d9ff    
//传感器故障恢复记录(标准要求100条)
#define   flash_fault_clear_start  0x800da00     //128条512*1
#define   flash_fault_clear_over   0x800dbff
//设备掉电记录(标准要求50条)
#define   flash_power_down_start   0x800de00     //64条512*1 
#define   flash_power_down_over    0x800deff     
//设备上电记录(标准要求50条)
#define   flash_power_on_start     0x800df00     //64条 
#define   flash_power_on_over      0x800dfff
//设备消音记录(标准要求20条)
#define   flash_power_on_start     0x800e000     //64条512*1 
#define   flash_power_on_over      0x800e0ff
//设备自检记录(标准要求20条)
#define   flash_power_on_start     0x800e100     //64*4 
#define   flash_power_on_over      0x800e1ff
//电磁阀启动记录(标准要求20条)
#define   flash_power_on_start     0x800e200     //64条512*1  
#define   flash_power_on_over      0x800e2ff
//电磁阀反馈记录(标准要求20条)
#define   flash_power_on_start     0x800e300     //64*4 
#define   flash_power_on_over      0x800e3ff
//寿命终止记录
#define   flash_life_start         0x800e400     //64条512*1  
#define   flash_life_over          0x800e4ff
-------------------------------------------------------------*/


#define  Flash_Read(i)             (*(volatile unsigned int *)(i))
	
typedef struct tag_unlock
{
	unsigned char flag ;
	unsigned int area ;
}TagUnlock_t ;	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
TagUnlock_t Flash_unlock_area(unsigned int addr)
{
	unsigned char i ;
	TagUnlock_t out ;
	
	addr = addr&0x1FE00;
	i = addr/2048;
	if(i>31)
	{
		out.flag=1;
		i -=32 ;
	}
    else
    {
		out.flag=0;
		out.area=i;		
	}
	out.area = (1<<i);
    return out ;	
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned char Flash_Erase(unsigned int addr)
{
	TagUnlock_t fl;	
	fl = Flash_unlock_area(addr); 
	//FLASH初始化（编程时间,休眠模式配置）
	Flash_Init(1, TRUE);
	//FLASH FLASH 解锁只读模式，可以擦写
	Flash_FuncSet(FlashReadOnlyEn,FALSE);
	//FLASH 扇区解锁
	if(fl.flag==0)
	{
		Flash_LockSet(FlashLock0, fl.area);
	}
    else
    {
		Flash_LockSet(FlashLock1, fl.area);
	}
	//FLASH目标扇区擦除
	Flash_OpModeConfig(FlashSectorEraseMode);
	Flash_SectorErase(addr&0x1FE00);
    //对扇区加锁
    Flash_LockAll();	
    return 1 ;	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned char Flash_Write(unsigned int addr,unsigned int *datum,unsigned int len)
{	
	TagUnlock_t fl;
    unsigned int i,addr_bk=addr;	
	
	fl = Flash_unlock_area(addr);
	//FLASH初始化（编程时间,休眠模式配置）
	Flash_Init(1, TRUE);
	//FLASH FLASH 解锁只读模式，可以擦写
	Flash_FuncSet(FlashReadOnlyEn,FALSE);
	//FLASH 扇区解锁
	if(fl.flag==0)
	{
		Flash_LockSet(FlashLock0, fl.area);
	}
    else
    {
		Flash_LockSet(FlashLock1, fl.area);
	}
    //FLASH 字节写、校验 
    Flash_OpModeConfig(FlashWriteMode);
    Flash_Write32(addr, datum, len);
    //对扇区加锁
    Flash_LockAll();
    //只读模式使能  
	Flash_OpModeConfig(FlashReadMode);
	//FLASH 只读模式，不可以擦写
	Flash_FuncSet(FlashReadOnlyEn,TRUE);
	for(i=0;i<len;i++)
	{
		if(Flash_Read(addr_bk)!=datum[i])
		{
			return 0 ;
		}
        addr_bk += 4 ;		
	}	
	return 1 ;
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Flash_test(void)
{
    static unsigned char test=0;
	unsigned int fl_addr = 0x1F800u ;
	
	test +=0x11;
	for(int i=0;i<16;i++)
	{
		array_temp.buf_32b[i] = test ;
	}
	Flash_Erase(fl_addr);
	Flash_Write(fl_addr,&array_temp.buf_32b[0],16);
	for(int i=0;i<16;i++)
	{
		array_temp.buf_32b[i] = Flash_Read(fl_addr+i*4) ;
	}
	for(int i=0;i<16;i++)
	{
		printf("0x%08x ",array_temp.buf_32b[i]);
	}
}	









