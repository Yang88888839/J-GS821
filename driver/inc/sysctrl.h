/**
 ******************************************************************************
 * @file   sysctrl.h
 *
 * @brief This file contains all the functions prototypes of the SYSCTRL driver
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

#ifndef __SYSCTRL_H__
#define __SYSCTRL_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_SYSCTRL SYSCTRL模块驱动库
 * @{
 */

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
* @defgroup SYSCTRL_Global_Types SYSCTRL全局类型定义
* @{
*/

/**
 * @brief 系统时钟输入源类型定义
 * @note
 */
typedef enum
{
    SysctrlClkRCH   = 0u,  /*!< 内部高速RCH时钟 */
    SysctrlClkXTH   = 1u,  /*!< 外部高速时钟 */
    SysctrlClkRCL   = 2u,  /*!< 内部低速时钟 */
    SysctrlClkXTL   = 3u,  /*!< 外部低速时钟 */
} en_sysctrl_clk_source_t;

/**
 * @brief 系统时钟输入源类型定义
 * @note
 */
typedef enum
{
    SysctrlExtXth   = 0u,  /*!< 外部输入高速时钟信号 */
    SysctrlExtXtl   = 1u,  /*!< 外部输入低速时钟信号 */
} en_sysctrl_extclk_t;


/**
 * @brief RCH频率值枚举类型定义
 */
typedef enum
{
    SysctrlRchFreq4MHz    = 0x00u,  /*!< 4MHz */
    SysctrlRchFreq6MHz    = 0x01u,  /*!< 6MHz */
    SysctrlRchFreq32MHz   = 0x02u,  /*!< 32MHz */
    SysctrlRchFreq48MHz   = 0x03u,  /*!< 48MHz */
} en_sysctrl_rch_freq_t;

/**
 * @brief XTAL驱动能力类型定义
 */
typedef enum
{
    SysctrlXtalDriver0 = 0u,  /*!< 最弱驱动能力 */
    SysctrlXtalDriver1 = 1u,  /*!< 较弱驱动能力 */
    SysctrlXtalDriver2 = 2u,  /*!< 较强驱动能力 */
    SysctrlXtalDriver3 = 3u,  /*!< 最强驱动能力 */
} en_sysctrl_xtal_driver_t;


/**
 * @brief XTH频率值范围选择类型定义
 */
typedef enum
{
    SysctrlXthFreq8MHz     = 0u,  /*!< 8MHz */
    SysctrlXthFreq8_16MHz  = 1u,  /*!< 8~16MHz */
    SysctrlXthFreq16_24MHz = 2u,  /*!< 16~24MHz */
    SysctrlXthFreq24_32MHz = 3u,  /*!< 24~32MHz */
} en_sysctrl_xth_freq_t;

/**
 * @brief XTH时钟稳定周期数类型定义
 */
typedef enum
{
    SysctrlXthStableCycle8192    = 0u,  /*!< 8192 个周期数 */
    SysctrlXthStableCycle32768   = 1u,  /*!< 32768 个周期数 */
    SysctrlXthStableCycle131072  = 2u,  /*!< 131072 个周期数 */
    SysctrlXthStableCycle2621144 = 3u,  /*!< 262144 个周期数 */
} en_sysctrl_xth_cycle_t;

/**
 * @brief RCL频率值枚举类型定义
 */
typedef enum
{
    SysctrlRclFreqHpm32768    = 0u,  /*!< 32.768KHz HPM */
    SysctrlRclFreqHpm38400    = 1u,  /*!< 38.4KHz HPM */
    SysctrlRclFreqLpm32768    = 7u,  /*!< 32.768KHz LPM */
    SysctrlRclFreqLpm38400    = 8u,  /*!< 38.4KHz LPM */
} en_sysctrl_rcl_freq_t;


/**
 * @brief XTL时钟稳定周期数类型定义
 */
typedef enum
{
    SysctrlXtlStableCycle4096   = 0u,  /*!< 4096 个周期数 */
    SysctrlXtlStableCycle8192   = 1u,  /*!< 8192 个周期数 */
    SysctrlXtlStableCycle16384  = 2u,  /*!< 16384 个周期数 */
    SysctrlXtlStableCycle32768  = 3u,  /*!< 32768 个周期数 */
} en_sysctrl_xtl_cycle_t;

/**
 * @brief XTL晶体振幅枚举类型定义
 */
typedef enum
{
    SysctrlXtlAmp0 = 0u,  /*!< 最小振幅 */
    SysctrlXtlAmp1 = 1u,  /*!< 正常振幅 */
    SysctrlXtlAmp2 = 2u,  /*!< 较大振幅 */
    SysctrlXtlAmp3 = 3u,  /*!< 最大振幅 */
} en_sysctrl_xtl_amp_t;


/**
 * @brief HCLK时钟分频系数类型定义
 */
typedef enum
{
    SysctrlHclkDiv1   = 0u,  /*!< SystemClk */
    SysctrlHclkDiv2   = 1u,  /*!< SystemClk/2 */
    SysctrlHclkDiv4   = 2u,  /*!< SystemClk/4 */
    SysctrlHclkDiv8   = 3u,  /*!< SystemClk/8 */
    SysctrlHclkDiv16  = 4u,  /*!< SystemClk/16 */
    SysctrlHclkDiv32  = 5u,  /*!< SystemClk/32 */
    SysctrlHclkDiv64  = 6u,  /*!< SystemClk/64 */
    SysctrlHclkDiv128 = 7u,  /*!< SystemClk/128 */
} en_sysctrl_hclk_div_t;

/**
 * @brief PCLK分频系数
 */
typedef enum
{
    SysctrlPclkDiv1 = 0u,                /*!< HCLK */
    SysctrlPclkDiv2 = 1u,                /*!< HCLK/2 */
    SysctrlPclkDiv4 = 2u,                /*!< HCLK/4 */
    SysctrlPclkDiv8 = 3u,                /*!< HCLK/8 */
} en_sysctrl_pclk_div_t;

/**
 * @brief 系统控制模块其他功能数据类型定义
 */
typedef enum
{
    SysctrlEXTHEn           = 1u,  /*!< 使能外部高速时钟从输入引脚输入 */
    SysctrlEXTLEn           = 2u,  /*!< 使能外部低速速时钟从输入引脚输入 */
    SysctrlXTLAlwaysOnEn    = 3u,  /*!< 使能后XTL_EN只可置位 */
    SysctrlClkFaultEn       = 5u,  /*!< 使能时钟错误检测功能 */
    SysctrlCMLockUpEn       = 6u,  /*!< 使能后CPU执行无效指令会复位MCU */
    SysctrlSpiPortCtrl      = 7u,  /*!< SPI端口控制:TRUE:GPIO控制; FALSE:SPI控制*/
    SysctrlSWDUseIOEn       = 8u,  /*!< SWD端口设为IO功能:TRUE:GPIO端口; FALSE:SWD端口 */
} en_sysctrl_func_t;

/**
 * @brief 外设时钟门控开关类型枚举
 */
typedef enum
{
    SysctrlPeripheralUsart0     = 0u,   /*!< 串口0 */
    SysctrlPeripheralUsart1     = 1u,   /*!< 串口1 */
    SysctrlPeripheralLpUart0    = 2u,   /*!< 低功耗串口0 */
    SysctrlPeripheralLpUart1    = 3u,   /*!< 低功耗串口1 */
    SysctrlPeripheralI2c0       = 4u,   /*!< I2C0 */
    SysctrlPeripheralI2c1       = 5u,   /*!< I2C1 */
    SysctrlPeripheralSpi0       = 6u,   /*!< SPI0 */
    SysctrlPeripheralSpi1       = 7u,   /*!< SPI1 */
    SysctrlPeripheralBaseTim    = 8u,   /*!< 定时器TIM0/1/2 */
    SysctrlPeripheralLpTim0     = 9u,   /*!< 低功耗定时器0 */
    SysctrlPeripheralTim3       = 11u,  /*!< 定时器3 */
    SysctrlPeripheralIwdt       = 15u,  /*!< 独立看门狗 */
    SysctrlPeripheralAdcBgr     = 16u,  /*!< ADC&BGR */
    SysctrlPeripheralVcLvd      = 17u,  /*!< VC和LVD */
    SysctrlPeripheralTrng       = 18u,  /*!< TRNG */
    SysctrlPeripheralRtc        = 20u,  /*!< RTC */
    SysctrlPeripheralLcd        = 22u,  /*!< LCD */
    SysctrlPeripheralCrc        = 26u,  /*!< CRC */
    SysctrlPeripheralAes        = 27u,  /*!< AES */
    SysctrlPeripheralGpio       = 28u,  /*!< GPIO */
    SysctrlPeripheralDma        = 29u,  /*!< DMA */
    SysctrlPeripheralHsi2c      = 30u,  /*!< HSI2C */
    SysctrlPeripheralFlash      = 31u,  /*!< Flash */
    SysctrlPeripheralCtrim      = 34u,  /*!< 时钟校准 */
    SysctrlPeripheralLpTim1     = 36u,  /*!< 低功耗定时器1 */
    SysctrlPeripheralLpuart2    = 40u,  /*!< LPUART2 */
    SysctrlPeripheralWwdt       = 42u,  /*!< WWDT */
} en_sysctrl_peripheral_gate_t;

/**
 * @brief XTL晶体晶体失效检测间隔选择枚举类型定义
 */
typedef enum
{
    SysctrlXtlFaultDetTime2ms = 0u,  /*!< 2ms检测时间间隔 */
    SysctrlXtlFaultDetTime8ms = 1u,  /*!< 8ms检测时间间隔 */
} en_sysctrl_xtl_det_time_t;


/**
 * @brief 时钟初始化配置结构体定义
 */
typedef struct
{
    en_sysctrl_clk_source_t  enClkSrc;   /*!< 时钟源选择 */
    en_sysctrl_hclk_div_t    enHClkDiv;  /*!< HCLK分频系数 */
    en_sysctrl_pclk_div_t    enPClkDiv;  /*!< PCLK分频系数 */
} stc_sysctrl_clk_cfg_t;


/**
 * @brief XTH 失效检测配置结构体定义
 */
typedef struct
{
    boolean_t           bFaultDetectEn;       /*!< XTH 停振检测使能 */
    boolean_t           bFaultDetectIntEn;    /*!< XTH 停振检测中断使能 */
} stc_sysctrl_xth_det_cfg_t;

/**
 * @brief XTL 失效检测配置结构体定义
 */
typedef struct
{
    boolean_t                   bFaultDetectEn;       /*!< XTL 停振检测使能 */
    boolean_t                   bFaultDetectIntEn;    /*!< XTL 停振检测中断使能 */
    en_sysctrl_xtl_det_time_t   enFaultDetTime;       /*!< XTL 停振检测间隔时间 */
} stc_sysctrl_xtl_det_cfg_t;


/**
 * @}
 */

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup SYSCTRL_Global_Functions SYSCTRL全局函数定义
 * @{
 */
/* 系统时钟初始化API:用于上电后，系统工作之前对主频及外设时钟进行初始化；
  - 注意1:使用该初始化函数前需要根据系统，必须优先设置目标内部时钟源RCH或RCL的TRIM值或外部时高速钟源XTH的频率范围；
  - 注意2:XTH、XTL的频率范围设定，驱动能力设置需要根据外部晶振决定，用户需根据实际情况修改此函数内的默认值；
  - 注意3:本驱动默认宏定义：SYSTEM_XTH=8MHz,SYSTEM_XTL=32768Hz,如使用其它外部晶振，必须修改这两个宏定义的值。
  - 注意4:本函数默认配置RCL功耗模式为低功耗模式
  - 注意5:如果选择的时钟源频率超过24MHz，需要在调用此函数前合理设置FLASH读等待周期*/
en_result_t Sysctrl_ClkInit(stc_sysctrl_clk_cfg_t *pstcCfg);

/* 系统时钟去初始化API:恢复为上电默认状态->PCLK=HCLK=SystemClk=RCH4MHz */
en_result_t Sysctrl_ClkDeInit(void);

/* 系统时钟模块的基本功能设置
   注意：调用此函数使能时钟之前，必须先设置目标时钟的相关参数，
   如RCH的TRIM值，RCH_CR寄存器参数，PLL的参数或外部时钟源的频率（振幅）范围、驱动能力和稳定时间等*/
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag);
/* 外部输入时钟信号功能设置
   注意：调用此函数使能时钟之前，必须先设置目标时钟的稳定时间参数*/
en_result_t Sysctrl_Ext_Enable(en_sysctrl_extclk_t enSource, boolean_t bFlag);

/* 外部晶振驱动能力配置 */
en_result_t Sysctrl_XTHDriverCfg(en_sysctrl_xtal_driver_t enDriver);
en_result_t Sysctrl_XTLDriverCfg(en_sysctrl_xtl_amp_t enAmp, en_sysctrl_xtal_driver_t enDriver);

/* 时钟稳定周期设置 */
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle);
en_result_t Sysctrl_SetXTLStableTime(en_sysctrl_xtl_cycle_t enCycle);

/* 系统时钟源切换并更新系统时钟；
   - 注意1：调用此函数前，必须确保新的系统时钟源的相关参数已经初始化，并且新时钟源已经使能且稳定运行
   - 注意2：时钟切换前后，必须根据目标频率值设置Flash读等待周期，可配置插入周期为0、1、2
   - 注意3：当HCLK大于24MHz时，FLASH等待周期插入必须至少为1,否则程序运行可能产生未知错误 */
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource);

/* 时钟源频率设定：根据系统情况，单独设置不同时钟源的频率值;
   时钟频率设置前，必须根据目标频率值设置Flash读等待周期，可配置插入周期为0、1、2，
   其中XTL的时钟由外部晶振决定，无需设置。*/
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq);
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq);
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq);

/* 时钟分频设置:根据系统情况，单独设置HCLK、PCLK的分配值 */
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv);
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv);

/* 时钟频率获取：根据系统需要，获取当前HCLK及PCLK的频率值 
 * @note 注意:本驱动默认宏定义：SYSTEM_XTH=8MHz,SYSTEM_XTL=32768Hz,如使用其它外部晶振，必须修改这两个宏定义的值
 * @note 注意:如果手动修改或者调用CLKTRIM/CTRIM修改RCH/RCH/RCL时钟的TRIM值，此函数可能不会返回正确的HCLK频率值*/
uint32_t Sysctrl_GetHClkFreq(void);
uint32_t Sysctrl_GetPClkFreq(void);

/* 外设门控开关/状态获取：用于控制外设模块的使能，使用该模块的功能之前，必须使能该模块的门控时钟；*/
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag);
boolean_t   Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral);

/* 系统功能配置：用于设置其他系统相关特殊功能；*/
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag);

/* 系统功能配置：设定Deepsleep唤醒后系统时钟来源；*/
en_result_t Sysctrl_SetWakeupByRch(boolean_t bFlag);

/* 系统功能配置：设置XTH停振检测功能 */
en_result_t Sysctrl_XthFaultDetectCfg(stc_sysctrl_xth_det_cfg_t *pstcCfg);
/* 获得XTH 失效检测中断状态 */
boolean_t Sysctrl_GetXthFaultStatus(void);
/* 清除XTH 失效检测中断状态 */
void Sysctrl_ClrXthFaultStatus(void);
/* 系统功能配置：设置XTL停振检测功能*/
en_result_t Sysctrl_XtlFaultDetectCfg(stc_sysctrl_xtl_det_cfg_t *pstcCfg);
/* 获得XTL 失效检测中断状态 */
boolean_t Sysctrl_GetXtlFaultStatus(void);
/* 清除XTL 失效检测中断状态 */
void Sysctrl_ClrXtlFaultStatus(void);
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
#endif

#endif /* __SYSCTRL_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


