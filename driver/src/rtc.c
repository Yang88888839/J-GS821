/**
 *******************************************************************************
 * @file  rtc.c
 * @brief This file provides firmware functions to manage the RTC.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-04-23       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "rtc.h"
#include "math.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_RTC RTC模块驱动库
 * @brief RTC Driver Library RTC模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RTC_Local_Macros RTC局部宏定义
 * @{
 */
/**
 * @defgroup RTC_WPR_Value RTC WPR Value definition RTC WPR保护序列
 * @{
 */
#define RTC_UNLOCK_VALUE1       (0xCAU) /*!< 写入序列0xCA,0x53解锁 */
#define RTC_UNLOCK_VALUE2       (0x53U) /*!< 写入序列0xCA,0x53解锁 */
#define RTC_LOCK_VALUE          (0xFFU) /*!< 写入其他序列锁定寄存器写，除了WPR与ICR */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup RTC_Local_Variables RTC局部变量定义
 * @{
 */
const uint8_t Leap_Month_Base[]    = {3, 6, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2};
const uint8_t NonLeap_Month_Base[] = {4, 0, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2};
/**
 * @brief  平年每个月最后一天日期表 BCD格式.
 */
const uint8_t Cnst_Month_Tbl[12]   = {0x31, 0x28, 0x31, 0x30, 0x31, 0x30, 0x31, 0x31, 0x30, 0x31, 0x30, 0x31};
/**
 * @}
 */

/**
 * @defgroup RTC_Local_Functions RTC局部函数定义
 * @{
 */
/**
 * @brief  BCD格式检查.
 * @param  [in] u8data: BCD带检查数
 * @param  [in] u8limit_min: BCD最小值
 * @param  [in] u8limit_min: BCD最大值
 * @retval en_result_t:
 *           - Ok: BCD格式正确
 *           - Error: BCD格式错误
 */
static en_result_t Rtc_CheckBCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max)
{
    if (((u8data & 0x0FU) > 0x09U) || ((u8data & 0xF0U) > 0x90U)
    ||(u8data > u8limit_max) || (u8data < u8limit_min))
    {
        return Error;
    }
    return Ok;
}


/**
 * @brief  闰年判断.
 * @param  [in] u8year: 2000年后的年份的十位和个位0~99 
 * @retval boolean_t:
 *           - TRUE: 是闰年
 *           - FALSE: 不是闰年
 */
static boolean_t Rtc_IsLeapYear(uint8_t u8year)
{
    uint16_t u16year;
    u16year = 2000U + u8year;
    if(((u16year%4U == 0U) && (u16year%100U != 0U)) || (u16year%400U == 0U))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
* @}
*/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Functions RTC全局函数定义
 * @{
 */

/**
 * @defgroup RTC_Global_Functions RTC全局函数定义
 * @{
 */
/**
 * @brief  RTC写保护寄存器解锁.
 * @retval None.
 */
void Rtc_Unlock(void)
{
    M0P_RTC->WPR = RTC_UNLOCK_VALUE1;
    M0P_RTC->WPR = RTC_UNLOCK_VALUE2;
}

/**
 * @brief  RTC写保护寄存器锁定.
 * @retval None.
 */
void RtcC_Lock(void)
{
    M0P_RTC->WPR = RTC_UNLOCK_VALUE1;
    M0P_RTC->WPR = RTC_LOCK_VALUE;
}

/**
 * @brief  RTC计数器的使能或停止
 * @param  [in] NewState TRUE:使能, FALSE:禁止 @ref boolean_t
 * @retval None
 */
void Rtc_Cmd(boolean_t NewState)
{
    M0P_RTC->CR0_f.START = NewState;
}

/**
 * @brief  RTC计数器启动等待函数，如启动RTC计数器后立即进入低功耗模式，
 *         进入低功耗模式之前需执行此函数，以确保RTC已启动完成
 * @retval None
 */
void Rtc_StartWait(void)
{
    M0P_RTC->CR1_f.WAIT = 1;
    while (M0P_RTC->CR1_f.WAITF != 1) /* 等待直到WAITF=1 */
    {
        ;
    }
    M0P_RTC->CR1_f.WAIT = 0;
    while (M0P_RTC->CR1_f.WAITF != 0) /* 等待直到WAITF=0 */
    {
        ;
    }
}

/**
 * @brief  RTC的1Hz输出的使能或停止
 * @param  [in] pricision 普通精度与高精度1Hz输出选择 @ref en_rtc_hz1sel_t
 * @param  [in] NewState TRUE:使能, FALSE:禁止 @ref boolean_t
 * @retval None
 */
void Rtc_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState)
{
    M0P_RTC->CR0_f.HZ1SEL = pricision; /* 设置普通精度或者高精度1Hz输出 */
    M0P_RTC->CR0_f.HZ1OE  = NewState; /* 设置1Hz输出使能或禁止 */
}

/**
 * @brief  设置周期中断的类型(PRDSEL)及其所选类型的时间(PRDS或PRDX)
 * @param  [in] pstCyc 根据结构体的定义设置PRDSEL、PRDS与PRDX @ref stc_rtc_cyccfg_t
 * @retval en_result_t
 *         - Ok: No error
 *         - ErrorInvalidParameter: Provided parameter is not valid
 */
en_result_t Rtc_SetCyc(stc_rtc_cyccfg_t *pstcCyc)
{
    en_result_t enRet     = Ok;
    
    M0P_RTC->CR0_f.PRDSEL = pstcCyc->rtcPrdsel;
    
    if (pstcCyc->rtcPrdsel == RtcPrds)
    {
        M0P_RTC->CR0_f.PRDS = pstcCyc->rtcPrds;
    }
    else if (pstcCyc->rtcPrdsel == RtcPrdx)
    {
        if (pstcCyc->rtcPrdx >= 64)
        {
            return ErrorInvalidParameter;
        }
        M0P_RTC->CR0_f.PRDX = pstcCyc->rtcPrdx;
    }
    else
    {
        ;
    }
    
    return enRet;
}


/**
 * @brief  RTC闹钟的使能或停止
 * @param  [in] NewState TRUE:使能, FALSE:禁止 @ref boolean_t
 * @retval None
 */
void Rtc_AlarmEnCmd(en_rtc_alarmch_t enAlarmX, boolean_t NewState)
{
    if(RtcAlarmA == enAlarmX)
    {
        M0P_RTC->CR2_f.ALMAE = NewState;
    }
    else if(RtcAlarmB == enAlarmX)
    {
        M0P_RTC->CR2_f.ALMBE = NewState;
    }
    else
    {
        ;
    }
}


/**
 * @brief  RTC闹钟中断时间获取.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @param  [in] pstcAlarmTime: 存放闹钟时间寄存器数据：秒 分 时 周 秒屏蔽 分屏蔽 时屏蔽 @ref stc_rtc_alarmtime_t
 * @retval None.
 */
void Rtc_GetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime)
{
    uint32_t u32RegAddr;
    uint8_t u8Hour;

    if(RtcAlarmA == enAlarmX)
    {
        u32RegAddr = (uint32_t)&M0P_RTC->ALMA;
    }
    else
    {
        u32RegAddr = (uint32_t)&M0P_RTC->ALMB;
    }

    pstcAlarmTime->u8AlarmSec    = (uint8_t)(((*(uint32_t*)u32RegAddr) & 0x7Fu) >> 0u);
    pstcAlarmTime->u8AlarmMinute = (uint8_t)(((*(uint32_t*)u32RegAddr) & 0x7F00u) >> 8u);
    u8Hour   = (uint8_t)(((*(uint32_t*)u32RegAddr) & 0x3F0000u) >> 16u);
    pstcAlarmTime->u8AlarmDayOfWeek   = (uint8_t)(((*(uint32_t*)u32RegAddr) & 0x7F000000u) >> 24u);
    pstcAlarmTime->bAlarmMskH = ((*(uint32_t*)u32RegAddr) & 0x800000u)? TRUE: FALSE;
    pstcAlarmTime->bAlarmMskM = ((*(uint32_t*)u32RegAddr) & 0x8000u)? TRUE: FALSE;
    pstcAlarmTime->bAlarmMskS = ((*(uint32_t*)u32RegAddr) & 0x80u)? TRUE: FALSE;

    if(RtcAmpm24H == M0P_RTC->CR0_f.AMPM)
    {
        pstcAlarmTime->u8AlarmHour = u8Hour;
    }
    else
    {
        pstcAlarmTime->u8AlarmHour = u8Hour & 0x1fU;
        pstcAlarmTime->u8AmPm = (u8Hour & 0x20U)? 1U : 0U;
    }
}

/**
 * @brief  RTC闹钟设置.
 * @param  [in] enAlarmX: 闹钟选择闹钟A或者闹钟B @ref en_rtc_alarmch_t
 * @param  [in] pstcAlarmTime: 存放闹钟时间寄存器数据：秒 分 时 周 秒屏蔽 分屏蔽 时屏蔽 @ref stc_rtc_alarmtime_t
 * @retval en_result_t:
 *         - Ok: 设置完成.
 *         - ErrorInvalidParameter: 设置失败，时间BCD格式不符合.
 */
en_result_t Rtc_SetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime)
{
    en_result_t enRet = Ok;
    uint32_t u32RegValue;
    uint32_t u32Hour;
  
    if(Ok != Rtc_CheckBCD_Format(pstcAlarmTime->u8AlarmSec, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != Rtc_CheckBCD_Format(pstcAlarmTime->u8AlarmMinute, 0x00U, 0x59U))
    {
        return ErrorInvalidParameter;
    }

    if(RtcAmpm24H == M0P_RTC->CR0_f.AMPM)
    {
        enRet = Rtc_CheckBCD_Format(pstcAlarmTime->u8AlarmHour, 0x00U, 0x23U); /* 24H */
        u32Hour = pstcAlarmTime->u8AlarmHour;
    }
    else
    {
        enRet = Rtc_CheckBCD_Format(pstcAlarmTime->u8AlarmHour&(~0x20U), 0x01U, 0x12U); /* 12H */
        u32Hour = pstcAlarmTime->u8AmPm? (pstcAlarmTime->u8AlarmHour | 0x20U): pstcAlarmTime->u8AlarmHour;
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }


    u32RegValue = (((uint32_t)pstcAlarmTime->u8AlarmSec << 0u) | \
                    ((uint32_t)pstcAlarmTime->u8AlarmMinute << 8u) | \
                    ((uint32_t)u32Hour << 16u) | \
                    ((uint32_t)pstcAlarmTime->u8AlarmDayOfWeek << 24u) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskS << 7u) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskM << 15u) | \
                    ((uint32_t)pstcAlarmTime->bAlarmMskH << 23u));

    if(RtcAlarmA == enAlarmX)
    {
        M0P_RTC->CR2 &= (~0x200u);      /* 闹钟禁止以后再设置闹钟时间 */
        M0P_RTC->ALMA = u32RegValue;
        M0P_RTC->CR2 |= 0x200u;
    }
    else
    {
        M0P_RTC->CR2 &= (~0x400u);      /* 闹钟禁止以后再设置闹钟时间 */
        M0P_RTC->ALMB = u32RegValue;
        M0P_RTC->CR2 |= 0x400u;
    }

    return Ok;
}



/**
 * @brief  RTC唤醒定时器使能/禁止.
 * @param [in]  bCmd
 *              - TRUE:唤醒定时器功能使能
 *              - FALSE:唤醒定时器功能使能
 * @retval None.
 */
void Rtc_WakeupTimerEnCmd(boolean_t bCmd)
{
    M0P_RTC->CR2_f.WUTE = bCmd;
}


/**
 * @brief  RTC唤醒定时器时钟选择.
 * @retval None.
 */
void Rtc_WakeupTimerClkSel(en_rtc_wucksel_t enWucksel)
{
    uint32_t u32RegValue;

    u32RegValue = M0P_RTC->CR2 & (~0x7u);
    M0P_RTC->CR2 = u32RegValue | (uint32_t)enWucksel;
}


/**
 * @brief  RTC唤醒定时器设置周期值.
 * @param  [in] u16Arr: RTC唤醒定时器周期值
 * @retval None.
 */
void Rtc_WakeupTimerSetArr(uint16_t u16Arr)
{
    M0P_RTC->WUTR = (uint32_t)u16Arr;
}

/**
 * @brief  RTC唤醒定时器获取周期值.
 * @retval uint16_t: RTC唤醒定时器周期值
 */
uint16_t Rtc_WakeupTimerGetArr(void)
{
    return (uint16_t)M0P_RTC->WUTR;
}


/**
 * @brief  RTC时间戳使能/禁止.
 * @param [in]  bCmd
 *              - TRUE:时间戳功能使能
 *              - FALSE:时间戳功能使能
 * @retval None.
 */
void Rtc_TimestampEnCmd(boolean_t bCmd)
{
    M0P_RTC->CR2_f.TSE = bCmd;
}


/**
 * @brief  RTC时间戳边沿选择.
 * @param  [in] enEdge: RTC时间戳边沿选择 @ref en_rtc_tsedge_t
 * @retval None.
 */
void Rtc_TimestampEdgeSel(en_rtc_tsedge_t enEdge)
{
    M0P_RTC->CR2_f.TSEDG = enEdge;
}

/**
 * @brief  RTC时间戳时间读取.
 * @param  [in] pstcTs: RTC时间戳读取指针 @ref stc_rtc_ts_t
 * @retval None.
 */
void Rtc_TimestampGet(stc_rtc_ts_t *pstcTs)
{
    uint8_t u8Hour;

    pstcTs->u8Second = (uint8_t)((M0P_RTC->TSTR & 0x7Fu) >> 0u);
    pstcTs->u8Minute = (uint8_t)((M0P_RTC->TSTR & 0x7F00) >> 8u);
    u8Hour = (uint8_t)((M0P_RTC->TSTR & 0x3F0000u) >> 16u);
    pstcTs->u8DayOfWeek = (uint8_t)((M0P_RTC->TSDR & 0xE000) >> 13u);
    pstcTs->u8Day = (uint8_t)((M0P_RTC->TSDR & 0x3Fu) >> 0u);
    pstcTs->u8Month = (uint8_t)((M0P_RTC->TSDR & 0x1F00u) >> 8u);

    if(RtcAmpm24H == M0P_RTC->CR0_f.AMPM)
    {
        pstcTs->u8Hour = u8Hour;
    }
    else
    {
        pstcTs->u8Hour = u8Hour & 0x1fU;
        pstcTs->u8AmPm = (u8Hour & 0x20U)? 1U : 0U;
    }
}



/**
 * @brief  RTC读取中断标志.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t Rtc_GetIrqFlag(en_rtc_irq_t enIrqFlag)
{
    return (M0P_RTC->IFR & (uint32_t)enIrqFlag)? TRUE: FALSE;
}


/**
 * @brief  RTC清除中断标志.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void Rtc_ClearIrqFlag(en_rtc_irq_t enIrqFlag)
{
    M0P_RTC->ICR = ~((uint32_t)enIrqFlag);
}

/**
 * @brief  RTC读取中断使能状态.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval boolean_t:
 *           - TRUE: 中断使能
 *           - FALSE: 中断未使能
 */
boolean_t Rtc_GetIrqEn(en_rtc_irq_t enIrqFlag)
{
    return (M0P_RTC->IER & (uint32_t)enIrqFlag)? TRUE: FALSE;
}


/**
 * @brief  RTC使能中断.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void Rtc_EnableIrq(en_rtc_irq_t enIrqFlag)
{
    M0P_RTC->IER |= (uint32_t)enIrqFlag;
}


/**
 * @brief  RTC禁用中断.
 * @param  [in] u32IqrFlag: RTC中断标记 @ref RTC_IRQ_Flag
 * @retval None.
 */
void Rtc_DisableIrq(en_rtc_irq_t enIrqFlag)
{
    M0P_RTC->IER &= ~((uint32_t)enIrqFlag);
}


/**
 * @brief  计算RTC误差补偿寄存器的值.
 * @param  [in] s16CompUnit: 补偿单位，取值范围 -275 ~ +213，1个单位为(1/32768)*10^6 /32 = 0.96ppm
 * @param  [out] pu16CompValue: 计算结果
 * @retval en_result_t:
 *           - Ok: 计算成功
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t Rtc_CalcCompValue(float32_t f32CompUint, en_rtc_compen_acc_t enAccSel, uint16_t *pu16CompValue)
{
    uint16_t u16Res;
    float32_t f32Temp = f32CompUint;
    
    /* 根据 enAccSel 选择补偿精度 */
    if (RtcCompenAcc096 == enAccSel)
    {
        if ((f32CompUint < -274.66) || (f32CompUint > 212.67))
        {
            return ErrorInvalidParameter;
        }

        if (f32CompUint > -31.47125)
        {
            f32Temp = 32 + (f32Temp / 0.9536743f);
            f32Temp = roundf(f32Temp);   /* 四舍五入 */
            u16Res  = (uint16_t)f32Temp; /* 仅保留低9位 */
            u16Res &= 0x1FFu;
        }
        else
        {
            f32Temp = 512 + ((f32Temp + 32 * 0.9536743f) / 0.9536743f);
            f32Temp = roundf(f32Temp);   /* 四舍五入 */
            u16Res  = (uint16_t)f32Temp; /* 仅保留低9位 */
            u16Res &= 0x1FFu;
        }
    }

    else if (RtcCompenAcc006 == enAccSel)
    {
        if ((f32CompUint < -274.66) || (f32CompUint > 213.57))
        {
            return ErrorInvalidParameter;
        }

        if (f32CompUint > -30.51758)
        {
            f32Temp = 512 + (f32Temp / 0.0596046f);
            f32Temp = roundf(f32Temp);   /* 四舍五入 */
            u16Res  = (uint16_t)f32Temp; /* 仅保留低13位 */
            u16Res &= 0x1FFFu;
        }
        else
        {
            f32Temp = 8192 + ((f32Temp + 512 * 0.0596046f) / 0.0596046f);
            f32Temp = roundf(f32Temp);   /* 四舍五入 */
            u16Res  = (uint16_t)f32Temp; /* 仅保留低13位 */
            u16Res &= 0x1FFFu;
        }
    }

    else
    {
        return ErrorInvalidParameter;
    }

    *pu16CompValue = u16Res;

    return Ok;
}

/**
 * @brief  配置RTC的误差补偿寄存器
 * @param  [in] CompVlue 数值的范围为：0 ~ 0x1FF
 * @param  [in] NewStatus TRUE 或 FALSE @ref en_rtc_compen_t
 * @retval en_result_t
 *         - Ok: No error
 *         - ErrorInvalidParameter: Provided parameter is not valid
 */
en_result_t Rtc_CompCfg(uint16_t u16CompValue, en_rtc_compen_acc_t enAccSel, en_rtc_compen_t NewStatus)
{
    if (RtcCompenAcc096 == enAccSel)
    {
        if (u16CompValue > 0x1FFu)
        {
            return ErrorInvalidParameter;
        }
        else
        {
            M0P_RTC->COMPEN_f.CR = u16CompValue;
            M0P_RTC->COMPEN_f.EN = NewStatus;
        }
    }
    else if (RtcCompenAcc006 == enAccSel)
    {
        if (u16CompValue > 0x1FFFu)
        {
            return ErrorInvalidParameter;
        }
        else
        {
            M0P_RTC->COMPEN_f.CR = u16CompValue;
            M0P_RTC->COMPEN_f.EN = NewStatus;
        }
    }
    else
    {
        return ErrorInvalidParameter;
    }
    
    return Ok;
}


/**
 * @brief  RTC根据年获取二月的天数
 * @param  [in] u8year 年份
 * @retval 2月天数 28天或29天
 */
uint8_t Get_Month2_Day(uint8_t u8year)
{
    uint8_t u8day = 0;

    u8day = 28;
    if (Rtc_IsLeapYear(u8year) == 1)
    {
        u8day++;
    }
    return u8day;
}

/**
 * @brief  RTC获取时间函数
 * @param  [in] time 用于存放读取自时间寄存器的时间数据，格式为BCD码格式 @ref stc_rtc_time_t
 * @retval en_result_t
 *         - Ok: No error
 *         - ErrorTimeout: Time Out error occurred
 */
en_result_t Rtc_ReadDateTime(stc_rtc_time_t *pstcDateTime)
{
    uint32_t u32TimeOut;
    
    ASSERT(NULL != pstcTimeDate);
    
    if (1u == M0P_RTC->CR0_f.START)
    {
        M0P_RTC->CR1_f.WAIT = 1u;
        u32TimeOut = 1000u;
        while(FALSE == M0P_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
		}
    }
    
    pstcDateTime->u8Second = M0P_RTC->SEC;
    pstcDateTime->u8Minute = M0P_RTC->MIN;
    if (1u == M0P_RTC->CR0_f.AMPM)
    {
        pstcDateTime->u8Hour = M0P_RTC->HOUR;
    }
    else
    {
        pstcDateTime->u8Hour = M0P_RTC->HOUR & 0x1fu;
        pstcDateTime->u8AmPm = ((M0P_RTC->HOUR & 0x20u)? 1u : 0u);
    }
    
    pstcDateTime->u8Day       = M0P_RTC->DAY;
    pstcDateTime->u8DayOfWeek = M0P_RTC->WEEK;
    pstcDateTime->u8Month     = M0P_RTC->MON;
    pstcDateTime->u8Year      = M0P_RTC->YEAR;

    M0P_RTC->CR1_f.WAIT = 0u;
    if(1u == M0P_RTC->CR0_f.START)
    {
        u32TimeOut = 1000u;
        while(TRUE == M0P_RTC->CR1_f.WAITF)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
    }

    return Ok;
}

/**
 * @brief  向RTC时间寄存器写入时间
 * @param  [in] time 存放时间的结构体，各个时间均为BCD码格式 @ref stc_rtc_time_t
 * @retval en_result_t
 *         - Ok: No error
 *         - ErrorTimeout: Time Out error occurred
 */
en_result_t Rtc_SetTime(stc_rtc_time_t *pstcDateTime)
{
    en_result_t enRet = Ok;
    uint16_t    u32TimeOut;
    uint8_t u8MonthIndex;
    
    if(Ok != Rtc_CheckBCD_Format(pstcDateTime->u8Second, 0x00u, 0x59u))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != Rtc_CheckBCD_Format(pstcDateTime->u8Minute, 0x00u, 0x59u))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != Rtc_CheckBCD_Format(pstcDateTime->u8Month, 0x01u, 0x12u))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != Rtc_CheckBCD_Format(pstcDateTime->u8Year, 0x00u, 0x99u))
    {
        return ErrorInvalidParameter;
    }
    if(Ok != Rtc_CheckBCD_Format(pstcDateTime->u8DayOfWeek, 0x00u, 0x06u))
    {
        return ErrorInvalidParameter;
    }
    u8MonthIndex = ((pstcDateTime->u8Month & 0x10u)? 10u: 0u) + (pstcDateTime->u8Month & 0x0fu) - 1u;
    if(pstcDateTime->u8Month == 0x02u)
    {
        if(Rtc_IsLeapYear(pstcDateTime->u8Year))
        {
            enRet = Rtc_CheckBCD_Format(pstcDateTime->u8Day, 0x01u, 0x29u); /*!< 闰年2月 */
        }
        else
        {
            enRet = Rtc_CheckBCD_Format(pstcDateTime->u8Day, 0x01u, 0x28u); /*!< 平年2月 */
        }
    }
    else
    {
        enRet = Rtc_CheckBCD_Format(pstcDateTime->u8Day, 0x01u, Cnst_Month_Tbl[u8MonthIndex]);
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }
    if(RtcAmpm24H == M0P_RTC->CR0_f.AMPM)
    {
        enRet = Rtc_CheckBCD_Format(pstcDateTime->u8Hour, 0x00u, 0x23u); /*!< 24H */
    }
    else
    {
        enRet = Rtc_CheckBCD_Format(pstcDateTime->u8Hour&(~0x20u), 0x01u, 0x12u); /*!< 12H */
    }
    if(Ok != enRet)
    {
        return ErrorInvalidParameter;
    }
    

    if (1u == M0P_RTC->CR0_f.START)
    {
        M0P_RTC->CR1_f.WAIT = 1u;
        u32TimeOut = 1000u;
        while(FALSE == M0P_RTC->CR1_f.WAITF)
        {
            if(0 == u32TimeOut--)
            {
                return ErrorTimeout;
            }
		}
    }
    
    M0P_RTC->SEC  = pstcDateTime->u8Second;
    M0P_RTC->MIN  = pstcDateTime->u8Minute;
    if(1u == M0P_RTC->CR0_f.AMPM)
    {
        M0P_RTC->HOUR  = pstcDateTime->u8Hour;
    }
    else
    {
        M0P_RTC->HOUR  = (uint32_t)pstcDateTime->u8Hour | ((uint32_t)pstcDateTime->u8AmPm<<5U);
    }
    M0P_RTC->DAY  = pstcDateTime->u8Day;
    M0P_RTC->MON  = pstcDateTime->u8Month;
    M0P_RTC->YEAR = pstcDateTime->u8Year;
    M0P_RTC->WEEK = pstcDateTime->u8DayOfWeek;

    M0P_RTC->CR1_f.WAIT = 0u;
    if (1u == M0P_RTC->CR0_f.START)
    {
        u32TimeOut = 1000u;
        while(TRUE == M0P_RTC->CR1_f.WAITF)
        {
            if(0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  读取RTC当前的时间格式 12小时制或者24小时制.
 * @retval en_rtc_ampm_t：  @ref en_rtc_ampm_t
 *           - RtcAmpm12H: 12小时制
 *           - RtcAmpm24H: 24小时制
 */
en_rtc_ampm_t RTC_GetAmpmFormat(void)
{
    return (M0P_RTC->CR0 & 0x8u)? RtcAmpm24H : RtcAmpm12H;
}

/**
 * @brief  初始化RTC
 * @param  [in] Rtc_InitStruct RTC初始化结构体 @ref stc_rtc_initstruct_t
 * @retval None
 */
void Rtc_Init(stc_rtc_initstruct_t *Rtc_InitStruct)
{
    M0P_RTC->CR0_f.START = FALSE;                /* 计数停止 */
    M0P_RTC->CR0_f.AMPM = Rtc_InitStruct->enAmpm;        /* 实时时钟小时的时制 */
    M0P_RTC->CR1_f.CKSEL = Rtc_InitStruct->enClksrc;     /* 实时时钟RTC的时钟源 */
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
