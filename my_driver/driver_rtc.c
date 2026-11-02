
#define DRIVER_RTC_C

#include "bt.h"
#include "rtc.h"
#include "time.h"
#include "main.h"

#include "driver_rtc.h"

#include "bsp_part.h"
#include "bsp_eeprom.h"

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Rtc_IRQHandler(void)
{
	if (Rtc_GetIrqFlag(RtcIrqPrd) == TRUE)
    {
        Rtc_ClearIrqFlag(RtcIrqPrd); /* 清除中断标志位 */
    }
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_rtc(void)
{
    /* 使能外部XTL时钟作为RTC时钟 */
    Sysctrl_SetXTLStableTime(SysctrlXtlStableCycle16384); /*延时周期*/
    Sysctrl_XTLDriverCfg(SysctrlXtlAmp2, SysctrlXtalDriver2);
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, TRUE);	
    Sysctrl_SetPeripheralGate(SysctrlPeripheralRtc, TRUE); /* RTC模块时钟打开 */	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Rtc_set(stc_rtc_time_t *tm)
{
	stc_rtc_initstruct_t RtcInitStruct;
	stc_rtc_time_t       stcDateTime;
	
	Rtc_Unlock();
    DDL_ZERO_STRUCT(RtcInitStruct);     /* 初始值清零 */
    RtcInitStruct.enAmpm = RtcAmpm24H;  /* 24小时制 */
    RtcInitStruct.enClksrc = RtcClkXtl; /* 外部低速时钟 */
    Rtc_Init(&RtcInitStruct);

	DDL_ZERO_STRUCT(stcDateTime);               /* 初始值清零 */
    stcDateTime.u8Second    = tm->u8Second;     /* 配置RTC时间 */
    stcDateTime.u8Minute    = tm->u8Minute;
    stcDateTime.u8Hour      = tm->u8Hour;
    stcDateTime.u8Day       = tm->u8Day;
    stcDateTime.u8Month     = tm->u8Month;
    stcDateTime.u8Year      = tm->u8Year;	
	Rtc_SetTime(&stcDateTime);                        /* 设置RTC时钟值 */
	
	Rtc_CompCfg(0u, RtcCompenAcc096, RtcCompenEnable);/* 使能时钟误差补偿,补偿值0u  根据实际情况进行补偿 */
	Rtc_Cmd(TRUE);                                    /* 使能RTC开始计数 */
	RtcC_Lock();	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned char Rtc_read(stc_rtc_time_t *tm)
{
	unsigned char re ;
	Rtc_Unlock();
	re=Rtc_ReadDateTime(tm); /* 获取RTC时钟值 */
	RtcC_Lock();
	return re ;	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Rtc_time_printf(void)
{
    stc_rtc_time_t dev_time ;
	Rtc_read(&dev_time);
	printf("Date=%02x-%02x-%02x  ",dev_time.u8Year,dev_time.u8Month,dev_time.u8Day);
	printf("Time=%02x:%02x:%02x\r",dev_time.u8Hour,dev_time.u8Minute,dev_time.u8Second);	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned int system_second_read(void)
{
    unsigned int sec ;
	struct tm conv_time;
    stc_rtc_time_t dev_time ;
	
	Rtc_read(&dev_time);
	conv_time.tm_year  = convert_bcdTOhex(dev_time.u8Year);
	conv_time.tm_mon   = convert_bcdTOhex(dev_time.u8Month);
	conv_time.tm_mday  = convert_bcdTOhex(dev_time.u8Day);
	conv_time.tm_hour  = convert_bcdTOhex(dev_time.u8Hour);
	conv_time.tm_min   = convert_bcdTOhex(dev_time.u8Minute);
    conv_time.tm_sec   = convert_bcdTOhex(dev_time.u8Second);
    conv_time.tm_year  = conv_time.tm_year+2000-1900;
	conv_time.tm_mon -- ;
	
	sec = mktime(&conv_time);
	return sec ;
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
struct tm system_second_convert(unsigned int *sec)
{
	struct tm conv_t ;
	
	conv_t = *localtime(sec);
	conv_t.tm_year += 1900 ;
	conv_t.tm_mon ++ ;
	return conv_t ;
}	









