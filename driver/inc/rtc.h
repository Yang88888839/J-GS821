/**
 ******************************************************************************
 * @file  rtc.h
 * @brief This file contains all the functions prototypes of the RTC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-04-23       MADS            First version
 @endverbatim
 ******************************************************************************
 * Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#ifndef __RTC_H__
#define __RTC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_RTC RTC模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Types RTC全局类型定义
 * @{
 */

/**
 * @brief  RTC周期中断的时间间隔
 * @note   RTC_CR0  PRDS
 */
typedef enum
{
    RtcNone = 0u, /*!< 无周期中断 */
    Rtc05S  = 1u, /*!< 0.5S中断 */
    Rtc1S   = 2u, /*!< 1秒 */
    Rtc1Min = 3u, /*!< 1分钟 */
    Rtc1H   = 4u, /*!< 1小时 */
    Rtc1Day = 5u, /*!< 1天 */
    Rtc1Mon = 6u  /*!< 1月 */
} en_rtc_prds_t;

/**
 * @brief  12h制或24h制方式选择
 * @note   RTC_CR0  AMPM
 */
typedef enum
{
    RtcAmpm12H = 0u, /*!< 12小时制 */
    RtcAmpm24H = 1u  /*!< 24小时制 */
} en_rtc_ampm_t;

/**
 * @brief  普通精度与高精度1Hz输出
 * @note   RTC_CR0  HZ1SEL
 */
typedef enum
{
    RtcHz1selGeneralPricision = 0u, /*!< 普通精度1Hz输出 */
    RtcHz1selHighPricision    = 1u  /*!< 高精度1Hz输出 */
} en_rtc_hz1sel_t;

/**
 * @brief  周期中断选择
 * @note   RTC_CR0  PRDSEL
 */
typedef enum
{
    RtcPrds = 0u, /*!< 使用PRDS所设定的周期中断事件间隔 */
    RtcPrdx = 1u  /*!< 使用PRDX所设定的周期中断事件间隔 */
} en_rtc_prdsel_t;

/**
 * @brief  RTC的时钟选择
 * @note   RTC_CR1  CKSEL
 */
typedef enum
{
    RtcClkXtl     = 0u, /*!< 外部低速时钟XTL  32.768k */
    RtcClkRcl     = 2u, /*!< 内部低速时钟RCL  32k */
    RtcClkXth128  = 4u, /*!< 外部晶振4M       XTH/128 */
    RtcClkXth256  = 5u, /*!< 外部晶振8M       XTH/256 */
    RtcClkXth512  = 6u, /*!< 外部晶振16M      XTH/512 */
    RtcClkXth1024 = 7u  /*!< 外部晶振32M      XTH/1024 */
} en_rtc_cksel_t;

/**
 * @brief  时钟误差补偿使能或禁止
 * @note   RTC_COMPEN  EN
 */
typedef enum
{
    RtcCompenDisable = 0u,
    RtcCompenEnable  = 1u
} en_rtc_compen_t;

/**
 * @brief  时钟误差补偿精度
 * @note   RTC_COMPEN  CSTEPS
 */
typedef enum
{
    RtcCompenAcc096 = 0u,
    RtcCompenAcc006 = 1u
} en_rtc_compen_acc_t;

/**
 * @brief  闹钟通道
 */
typedef enum
{
    RtcAlarmA = 0, /*!< 闹钟A */
    RtcAlarmB = 1, /*!< 闹钟B */
}en_rtc_alarmch_t;


/**
 * @brief  唤醒定时器时钟选择
 */
typedef enum
{
    RtcWuckRTC_Div2 = 0,    /*!< RTC/2 */
    RtcWuckRTC_Div4 = 1,    /*!< RTC/4 */
    RtcWuckRTC_Div8 = 2,    /*!< RTC/8 */
    RtcWuckRTC_Div16 = 3,   /*!< RTC/16 */
    RtcWuckRTC_SecDiv1 = 4, /*!< RTC_Sec/1 */
    RtcWuckRTC_SecDiv2 = 5, /*!< RTC_Sec/2 */
    RtcWuckRTC_SecDiv4 = 6, /*!< RTC_Sec/4 */
    RtcWuckRTC_SecDiv8 = 7, /*!< RTC_Sec/8 */
}en_rtc_wucksel_t;

/**
 * @brief  时间戳边沿选择
 */
typedef enum
{
    RtcTSRising = 0,  /*!< 上升沿 */
    RtcTSFalling = 1, /*!< 下降沿 */
}en_rtc_tsedge_t;

/**
 * @brief  RTC中断(标志)类型定义
 * @note   RTC_IER_IFR_ICR  AMPM
 */
typedef enum
{
    RtcIrqAlmA  = 0x01u, /*!< 闹钟A中断 */
    RtcIrqAlmB  = 0x02u, /*!< 闹钟B中断 */
    RtcIrqWu    = 0x04u, /*!< 定时中断 */
    RtcIrqTs    = 0x08u, /*!< 时间戳中断 */
    RtcIrqTsOv  = 0x10u, /*!< 时间戳溢出标志（无中断） */
    RtcIrqPrd   = 0x40u, /*!< 周期中断 */
    RtcIrqAll   = 0x5Fu  /*!< 所有中断 */    
} en_rtc_irq_t;

/**
 * @brief  配置PRD中断使能及其周期类型
 */
typedef struct
{
    en_rtc_prdsel_t rtcPrdsel;  /*!< 时钟周期选择  @ref en_rtc_prdsel_t */
    uint8_t         rtcPrdx;    /*!< 0~63,设置产生周期中断的时间间隔，(rtcPrdx + 1)*0.5s */
    en_rtc_prds_t   rtcPrds;    /*!< rtc周期中断的时间间隔  @ref en_rtc_prds_t */
} stc_rtc_cyccfg_t;

/**
 * @brief  闹钟源配置
 */
typedef struct
{
    uint8_t  u8AlarmSec;    /*!< 闹钟秒钟 BCD码 */
    uint8_t  u8AlarmMinute; /*!< 闹钟分钟 BCD码 */
    uint8_t  u8AlarmHour;   /*!< 闹钟小时 BCD码 */
    uint8_t  u8AmPm;        /*!< 仅12小时制时需要，0：AM 1:PM */
    uint8_t  u8AlarmDayOfWeek;   /*!< 闹钟星期选择 @ref RTC_AlarmDayOfWeek_Sel */
    boolean_t bAlarmMskH; /*!< 闹钟小时屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与时位无关 */
    boolean_t bAlarmMskM; /*!< 闹钟分屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与分位无关 */
    boolean_t bAlarmMskS; /*!< 闹钟秒屏蔽位，0：时位匹配才会产生闹钟 1：闹钟与秒位无关 */
} stc_rtc_alarmtime_t;

/**
 * @brief  rtc时钟时间戳结构
 */
typedef struct
{
    uint8_t  u8Second;      /*!< 时间：秒 BCD码 */
    uint8_t  u8Minute;      /*!< 时间：分 BCD码 */
    uint8_t  u8Hour;        /*!< 时间：时 BCD码 */
    uint8_t  u8DayOfWeek;   /*!< 时间：周 BCD码 */
    uint8_t  u8Day;         /*!< 时间：日 BCD码 */    
    uint8_t  u8Month;       /*!< 时间：月 BCD码 */
    uint8_t  u8AmPm;        /*!< 仅12小时制时需要，0：AM 1:PM */
} stc_rtc_ts_t;

/**
 * @brief  RTC时钟年、月、日、时、分、秒读写结构
 * @note   RTC_CR0
 */
typedef struct
{
    uint8_t u8Second;    /*!< 时间：秒 */
    uint8_t u8Minute;    /*!< 时间：分 */
    uint8_t u8Hour;      /*!< 时间：时 */
    uint8_t u8DayOfWeek; /*!< 时间：周 */
    uint8_t u8Day;       /*!< 时间：日 */
    uint8_t u8Month;     /*!< 时间：月 */
    uint8_t u8Year;      /*!< 时间：年 */
    uint8_t  u8AmPm;     /*!< 仅12小时制时需要，0：AM 1:PM */
} stc_rtc_time_t;

/**
 * @brief  RTC初始化结构体
 */
typedef struct
{
    en_rtc_ampm_t         enAmpm;      /*!< 小时的时制 */
    en_rtc_cksel_t        enClksrc;    /*!< 实时时钟的时钟源 */
} stc_rtc_initstruct_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Macros RTC全局宏定义
 * @{
 */
/**
 * @defgroup RTC_AlarmDayOfWeek_Sel  RTC闹钟周内选择
 * @{
 */
#define RTC_ALMWEEK_SUNDAY          (0x01U) /*!< 周日 */
#define RTC_ALMWEEK_MONDAY          (0x02U) /*!< 周一 */
#define RTC_ALMWEEK_TUESDAY         (0x04U) /*!< 周二 */
#define RTC_ALMWEEK_WEDNESDAY       (0x08U) /*!< 周三 */
#define RTC_ALMWEEK_THURSDAY        (0x10U) /*!< 周四 */
#define RTC_ALMWEEK_FRIDAY          (0x20U) /*!< 周无 */
#define RTC_ALMWEEK_SATURDAY        (0x40U) /*!< 周六 */
#define RTC_ALMWEEK_ALL             (0x7FU) /*!< 一周全选 */
/**
 * @}
 */
 
/**
 * @}
 */
 
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup RTC_Global_Functions RTC全局函数定义
 * @{
 */
/* RTC写保护寄存器解锁 */
void Rtc_Unlock(void);
/* RTC写保护寄存器锁定 */
void RtcC_Lock(void);
/* RTC计数器的使能或停止 */
void Rtc_Cmd(boolean_t NewState);
/* RTC计数器启动等待函数 */
void Rtc_StartWait(void);
/* RTC的1Hz输出的使能或停止 */
void Rtc_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState);
/* 设置周期中断的类型(PRDSEL)及其所选类型的时间(PRDS或PRDX) */
en_result_t Rtc_SetCyc(stc_rtc_cyccfg_t *pstcCyc);
/* RTC闹钟的使能或停止 */
void Rtc_AlarmEnCmd(en_rtc_alarmch_t enAlarmX, boolean_t NewState);
/* RTC闹钟中断时间获取 */
void Rtc_GetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime);
/* RTC闹钟设置 */
en_result_t Rtc_SetAlarmTime(en_rtc_alarmch_t enAlarmX, stc_rtc_alarmtime_t* pstcAlarmTime);
/* RTC唤醒定时器使能/禁止 */
void Rtc_WakeupTimerEnCmd(boolean_t bCmd);
/* RTC唤醒定时器时钟选择 */
void Rtc_WakeupTimerClkSel(en_rtc_wucksel_t enWucksel);
/* RTC唤醒定时器设置周期值 */
void Rtc_WakeupTimerSetArr(uint16_t u16Arr);
/* RTC唤醒定时器获取周期值 */
uint16_t Rtc_WakeupTimerGetArr(void);
/* RTC时间戳使能/禁止 */
void Rtc_TimestampEnCmd(boolean_t bCmd);
/* RTC时间戳边沿选择 */
void Rtc_TimestampEdgeSel(en_rtc_tsedge_t enEdge);
/* RTC时间戳时间读取 */
void Rtc_TimestampGet(stc_rtc_ts_t *pstcTs);
/* RTC读取中断标志 */
boolean_t Rtc_GetIrqFlag(en_rtc_irq_t enIrqFlag);
/* RTC清除中断标志 */
void Rtc_ClearIrqFlag(en_rtc_irq_t enIrqFlag);
/* RTC读取中断使能状态 */
boolean_t Rtc_GetIrqEn(en_rtc_irq_t enIrqFlag);
/* RTC使能中断 */
void Rtc_EnableIrq(en_rtc_irq_t enIrqFlag);
/* RTC禁用中断 */
void Rtc_DisableIrq(en_rtc_irq_t enIrqFlag);
/* 计算RTC误差补偿寄存器的值 */
en_result_t Rtc_CalcCompValue(float32_t f32CompUint, en_rtc_compen_acc_t enAccSel, uint16_t *pu16CompValue);
/* 配置RTC的误差补偿寄存器 */
en_result_t Rtc_CompCfg(uint16_t u16CompValue, en_rtc_compen_acc_t enAccSel, en_rtc_compen_t NewStatus);
/* RTC根据年获取二月的天数 */
uint8_t Get_Month2_Day(uint8_t u8year);
/* RTC获取时间函数 */
en_result_t Rtc_ReadDateTime(stc_rtc_time_t *pstcDateTime);
/* 向RTC时间寄存器写入时间 */
en_result_t Rtc_SetTime(stc_rtc_time_t *pstcDateTime);
/* 读取RTC当前的时间格式 12小时制或者24小时制 */
en_rtc_ampm_t RTC_GetAmpmFormat(void);
/* 初始化RTC */
void Rtc_Init(stc_rtc_initstruct_t *Rtc_InitStruct);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
