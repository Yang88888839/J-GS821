/**
 ******************************************************************************
 * @file   adc.h
 *
 * @brief This file contains all the functions prototypes of the ADC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-04-23       MDAS            First version
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

#ifndef __ADC_H__
#define __ADC_H__


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_ADC ADC模块驱动库
 * @{
 */
/******************************************************************************
 * Global definitions
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Macros ADC全局宏定义
 * @{
 */

/**
 * @defgroup ADC_Scan_Channel ADC scan channel enable
 * @{
 */
#define ADC_SCAN_CH0_EN     (0x1u)           /*!< SCAN模式使用ADC CH0 */
#define ADC_SCAN_CH1_EN     (0x1u<<1)        /*!< SCAN模式使用ADC CH1 */
#define ADC_SCAN_CH2_EN     (0x1u<<2)        /*!< SCAN模式使用ADC CH2 */
#define ADC_SCAN_CH3_EN     (0x1u<<3)        /*!< SCAN模式使用ADC CH3 */
#define ADC_SCAN_CH4_EN     (0x1u<<4)        /*!< SCAN模式使用ADC CH4 */
#define ADC_SCAN_CH5_EN     (0x1u<<5)        /*!< SCAN模式使用ADC CH5 */
#define ADC_SCAN_CH6_EN     (0x1u<<6)        /*!< SCAN模式使用ADC CH6 */
#define ADC_SCAN_CH7_EN     (0x1u<<7)        /*!< SCAN模式使用ADC CH7 */
/**
 * @}
 */

/**
 * @}
 */
/******************************************************************************
 ** Global type definitions
 *****************************************************************************/
/**
 * @defgroup ADC_Global_Types ADC全局类型定义
 * @{
 */

/**
 * @brief  ADC转换模式
 */
typedef enum
{
    AdcSglMode  = 0u,           /*!< 单输入通道单次转换模式 */
    AdcScanMode = 1u,           /*!< 多输入通道SQR/JQR扫描转换模式*/
} en_adc_mode_t;

/**
 * @brief  ADC时钟分频选择
 */
typedef enum
{
    AdcMskClkDiv1  = 0u << 2,      /*!< PCLK */
    AdcMskClkDiv2  = 1u << 2,      /*!< 1/2 PCLK */
    AdcMskClkDiv4  = 2u << 2,      /*!< 1/4 PCLK */
    AdcMskClkDiv8  = 3u << 2,      /*!< 1/8 PCLK */
} en_adc_clk_div_t;

/**
 * @brief  ADC参考电压
 */
typedef enum
{
    AdcMskRefVolSelInBgr1p5 = 0u << 9,      /*!< 内部参考电压1.5V(SPS<=200kHz) */
    AdcMskRefVolSelInBgr2p5 = 1u << 9,      /*!< 内部参考电压2.5V(avdd>3V,SPS<=200kHz) */
    AdcMskRefVolSelExtern1  = 2u << 9,      /*!< 外部输入(max avdd)   PB01 */
    AdcMskRefVolSelAVDD     = 3u << 9,      /*!< AVDD */
} en_adc_ref_vol_sel_t;

/**
 * @brief  ADC转换通道选择
 */
typedef enum
{
    AdcExInputCH0    =  0u,        /*!< 使用PA00 */
    AdcExInputCH1    =  1u,        /*!< 使用PA01 */
    AdcExInputCH2    =  2u,        /*!< 使用PA02 */
    AdcExInputCH3    =  3u,        /*!< 使用PA03 */
    AdcExInputCH4    =  4u,        /*!< 使用PA04 */
    AdcExInputCH5    =  5u,        /*!< 使用PA05 */
    AdcExInputCH6    =  6u,        /*!< 使用PA06 */
    AdcExInputCH7    =  7u,        /*!< 使用PA07 */
    AdcExInputCH8    =  8u,        /*!< 使用PB00 */
    AdcExInputCH9    =  9u,        /*!< 使用PB01 */
    AdcExInputCH10   =  10u,       /*!< 使用PC00 */
    AdcExInputCH11   =  11u,       /*!< 使用PC01 */
    AdcExInputCH12   =  12u,       /*!< 使用PC02 */
    AdcExInputCH13   =  13u,       /*!< 使用PC03 */
    AdcExInputCH14   =  14u,       /*!< 使用PC04 */
    AdcExInputCH15   =  15u,       /*!< 使用PC05 */
    
    AdcAiTsInput     =  16u,       /*!< 使用内置温度传感器BGR_TS(必须使用输入增益) */
    AdcAVccdiv3Input =  17u,       /*!< 使用1/3 AVCC(必须使用输入增益) */
    AdcVref1_2Input  =  18u,       /*!<使用内部基准1.2V(必须使用输入增益)*/
} en_adc_samp_ch_sel_t;

/**
 * @brief  ADC采样周期选择
 */
typedef enum
{
    AdcMskSampCycle2Clk   =  0u << 17,      /*!< 2个采样时钟 */
    AdcMskSampCycle3Clk   =  1u << 17,      /*!< 3个采样时钟 */
    AdcMskSampCycle4Clk   =  2u << 17,      /*!< 4个采样时钟 */
    AdcMskSampCycle6Clk   =  3u << 17,      /*!< 6个采样时钟 */
    AdcMskSampCycle8Clk   =  4u << 17,      /*!< 8个采样时钟 */
    AdcMskSampCycle10Clk  =  5u << 17,      /*!< 10个采样时钟 */
    AdcMskSampCycle12Clk  =  6u << 17,      /*!< 12个采样时钟 */
    AdcMskSampCycle16Clk  =  7u << 17,      /*!< 16个采样时钟 */
    AdcMskSampCycle20Clk  =  8u << 17,      /*!< 20个采样时钟 */
    AdcMskSampCycle28Clk  =  9u << 17,      /*!< 28个采样时钟 */
    AdcMskSampCycle36Clk  =  10u << 17,     /*!< 36个采样时钟 */
    AdcMskSampCycle48Clk  =  11u << 17,     /*!< 48个采样时钟 */
    AdcMskSampCycle64Clk  =  12u << 17,     /*!< 64个采样时钟 */
    AdcMskSampCycle72Clk  =  13u << 17,     /*!< 72个采样时钟 */
    AdcMskSampCycle96Clk  =  14u << 17,     /*!< 96个采样时钟 */
    AdcMskSampCycle127Clk =  15u << 17,     /*!< 127个采样时钟 */
} en_adc_samp_cycle_sel_t;

/**
 * @brief  ADC电流功耗选择
 */
typedef enum
{
    AdcMskLowPowerCS  = 0u,        /*!< 低消耗电流和速度 */
    AdcMskHighPowerCS = 3u << 12,  /*!< 高消耗电流和速度 */
} en_adc_lp_cs_t;

/**
 * @brief  ADC模块单次或SQR扫描采样外部触发源选择
 */
typedef enum
{
    AdcTrig0NoneTrig   =  0u,    /*!< 无触发 */
    AdcTrig0TIM0Tradc  =  1u,    /*!< 选择Timer0Tradc中断源,自动触发ADC采样 */
    AdcTrig0TIM1Tradc  =  2u,    /*!< 选择Timer1Tradc中断源,自动触发ADC采样 */
    AdcTrig0TIM2Tradc  =  3u,    /*!< 选择Timer2Tradc中断源,自动触发ADC采样 */
    AdcTrig0TIM3Tradc  =  4u,    /*!< 选择Timer3Tradc中断源,自动触发ADC采样 */
    AdcTrig0LPTIM0     =  5u,    /*!< 选择lptimer0中断源,自动触发ADC采样 */
    AdcTrig0USART0     =  6u,    /*!< 选择uart0中断源，自动触发ADC采样 */
    AdcTrig0LPUART0    =  7u,    /*!< 选择lpuart0中断源，自动触发ADC采样 */
    AdcTrig0VC0        =  8u,    /*!< 选择VC0中断源，自动触发ADC采样 */
    AdcTrig0RTC        =  9u,    /*!< 选择RTC中断源，自动触发ADC采样 */
    AdcTrig0SPI0       =  10u,   /*!< 选择SPI0中断源，自动触发ADC采样 */
    AdcTrig0PA03       =  11u,   /*!< 选择PA03中断源，自动触发ADC采样 */
    AdcTrig0PB03       =  12u,   /*!< 选择PB03中断源，自动触发ADC采样 */
    AdcTrig0PC03       =  13u,   /*!< 选择PC03中断源，自动触发ADC采样 */
    AdcTrig0PD03       =  14u,   /*!< 选择PD03中断源，自动触发ADC采样 */
    AdcTrig0PA11       =  15u,   /*!< 选择PA11中断源，自动触发ADC采样 */
} en_adc_trig0_sel_t;


/**
 * @brief  ADC模块触发源选择
 */
typedef enum
{
    AdcTrig1NoneTrig   =  0u,    /*!< 无触发 */
    AdcTrig1TIM0Trgo   =  1u,    /*!< 选择timer0中断源，自动触发ADC采样 */
    AdcTrig1TIM1Trgo   =  2u,    /*!< 选择timer1中断源，自动触发ADC采样 */
    AdcTrig1TIM2Trgo   =  3u,    /*!< 选择timer2中断源，自动触发ADC采样 */
    AdcTrig1TIM3Cmp3a  =  4u,    /*!< 选择timer3中断源，自动触发ADC采样 */
    AdcTrig1LPTIM1     =  5u,    /*!< 选择lptimer1中断源,自动触发ADC采样 */
    AdcTrig1USART1     =  6u,    /*!< 选择uart1中断源，自动触发ADC采样 */
    AdcTrig1LPUART1    =  7u,    /*!< 选择lpuart1中断源，自动触发ADC采样 */
    AdcTrig1VC1        =  8u,    /*!< 选择VC1中断源，自动触发ADC采样 */
    AdcTrig1DMA        =  9u,    /*!< 选择DMA中断源，自动触发ADC采样 */
    AdcTrig1SPI1       =  10u,   /*!< 选择SPI1中断源，自动触发ADC采样 */
    AdcTrig1PA07       =  11u,   /*!< 选择PA07中断源，自动触发ADC采样 */
    AdcTrig1PB07       =  12u,   /*!< 选择PB07中断源，自动触发ADC采样 */
    AdcTrig1PC07       =  13u,   /*!< 选择PC07中断源，自动触发ADC采样 */
    AdcTrig1PD07       =  14u,   /*!< 选择PD07中断源，自动触发ADC采样 */
    AdcTrig1PA15       =  15u,   /*!< 选择PA15中断源，自动触发ADC采样 */
} en_adc_trig1_sel_t;

/**
 * @brief  ADC外部触发源寄存器选择
 */
typedef enum
{
    AdcExtTrig0     =  0u,         /*!< 单次及SQR扫描转换 外部触发源选择寄存器 */
    AdcExtTrig1     =  1u,         /*!< JQR扫描转换 外部触发源选择寄存器 */
} en_adc_ext_trig_sel_t;

/**
 * @brief  ADC SQR转换通道
 */
typedef enum
{
    AdcSQRCH0MUX     =  0u,         /*!< SQR扫描模式转换通道0 */
    AdcSQRCH1MUX     =  1u,         /*!< SQR扫描模式转换通道1 */
    AdcSQRCH2MUX     =  2u,         /*!< SQR扫描模式转换通道2 */
    AdcSQRCH3MUX     =  3u,         /*!< SQR扫描模式转换通道3 */
    AdcSQRCH4MUX     =  4u,         /*!< SQR扫描模式转换通道4 */
    AdcSQRCH5MUX     =  5u,         /*!< SQR扫描模式转换通道5 */
} en_adc_sqr_chmux_t;

/**
 * @brief  ADC JQR转换通道
 */
typedef enum
{
    AdcJQRCH0MUX     =  0u,         /*!< 转换通道0 */
    AdcJQRCH1MUX     =  1u,         /*!< 转换通道1 */
    AdcJQRCH2MUX     =  2u,         /*!< 转换通道2 */
    AdcJQRCH3MUX     =  3u,         /*!< 转换通道3 */
} en_adc_jqr_chmux_t;


/**
 * @brief  ADC转换结果自动累加功能
 */
typedef enum
{
    AdcResultAccEnable  = 1u,   /*!< 使能ADC转换结果自动累加 */
    AdcResultAccDisable = 0u,   /*!< 禁止ADC转换结果自动累加 */
} en_adc_result_acc_t;

/**
 * @brief  ADC中断类型定义
 */
typedef enum
{
    AdcMskIrqJqr =  0x20u,     /*!< ADC JQR扫描转换完成 */
    AdcMskIrqSqr =  0x10u,     /*!< ADC SQR扫描转换完成 */
    AdcMskIrqReg =  0x8u,      /*!< ADC转换结果比较区间内 */
    AdcMskIrqHt  =  0x4u,      /*!< ADC转换结果高于HT */
    AdcMskIrqLt  =  0x2u,      /*!< ADC转换结果低于LT */
    AdcMskIrqSgl =  0x1u,      /*!< ADC单次转换完成 */
} en_adc_irq_type_t;


/**
 * @brief  ADC初始化配置结构体
 */
typedef struct
{
    en_adc_mode_t           enAdcMode;                  /*!< ADC转换模式 */
    en_adc_clk_div_t        enAdcClkDiv;                /*!< ADC时钟选择 */
    en_adc_samp_cycle_sel_t enAdcSampCycleSel;          /*!< ADC采样周期选择 */
    en_adc_ref_vol_sel_t    enAdcRefVolSel;             /*!< ADC参考电压选择 */
} stc_adc_cfg_t;


/**
 * @brief  ADC SQR扫描模式配置结构体
 */
typedef struct
{
    uint8_t                 u8SqrCnt;                   /*!< ADC SQR扫描转换次数 */
    en_adc_result_acc_t     enResultAcc;                /*!< ADC转换结果自动累加功能 */
    boolean_t               bSqrDmaTrig;                /*!< ADC SQR扫描转换完成DMA触发使能 */
} stc_adc_sqr_cfg_t;

/**
 * @brief  ADC JQR扫描模式配置结构体
 */
typedef struct
{
    uint8_t                 u8JqrCnt;                   /*!< ADC SQR扫描转换次数 */
    boolean_t               bJqrDmaTrig;                /*!< ADC JQR扫描转换完成DMA触发使能 */
} stc_adc_jqr_cfg_t;


/**
 * @brief  ADC比较功能配置结构体
 */
typedef struct
{
    boolean_t bAdcRegCmp ;                  /*!< ADC区间使能 */
    boolean_t bAdcHtCmp ;                   /*!< ADC上超出区间使能 */
    boolean_t bAdcLtCmp ;                   /*!< ADC下超出区间使能 */

    uint32_t u32AdcHighThd;                 /*!< ADC比较上阈值 */
    uint32_t u32AdcLowThd;                  /*!< ADC比较下阈值 */

    en_adc_samp_ch_sel_t    enSampChSel;    /*!< ADC采样通道选择 */

} stc_adc_threshold_cfg_t;

/**
 * @}
 */
/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup ADC_Global_Functions ADC全局函数定义
 * @{
 */
//ADC 初始化
en_result_t Adc_Init(stc_adc_cfg_t *pstcAdcCfg);

//ADC 中断使能
void Adc_EnableIrq(void);
//ADC 中断禁止
void Adc_DisableIrq(void);

//ADC 中断/采样完成状态获取
boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq);
//ADC 中断/采样完成状态清除
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq);

//ADC 使能
void Adc_Enable(void);
//ADC 禁止
void Adc_Disable(void);

//ADC SQR扫描模式配置
en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t *pstcAdcSqrCfg);
//ADC JQR扫描模式配置
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t *pstcAdcJqrCfg);

//ADC Sgl 单次转换模式通道选择配置
en_result_t Adc_CfgSglChannel(en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC SQR扫描转换模式通道选择配置
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC JQR扫描转换模式通道选择配置
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);

//ADC 单次转换外部触发源配置
void Adc_SglExtTrigCfg(en_adc_trig0_sel_t enAdcTrigSel);
//ADC SQR扫描转换外部触发源配置
void Adc_SqrExtTrigCfg(en_adc_trig0_sel_t enAdcTrigSel);
//ADC JQR扫描转换外部触发源配置
void Adc_JqrExtTrigCfg(en_adc_trig1_sel_t enAdcTrigSel);

//ADC 阈值比较功能配置
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t *pstcAdcThrCfg);

//ADC 单次转换模式启动
void Adc_SGL_Start(void);
//ADC 单次转换模式停止
void Adc_SGL_Stop(void);

//ADC 单次转换模式一直转换模式启动
void Adc_SGL_Always_Start(void);
//ADC 单次转换模式一直转换模式停止
void Adc_SGL_Always_Stop(void);

//ADC SQR扫描转换模式启动
void Adc_SQR_Start(void);
//ADC SQR扫描转换模式停止
void Adc_SQR_Stop(void);

//ADC JQR扫描转换模式启动
void Adc_JQR_Start(void);
//ADC JQR扫描转换模式停止
void Adc_JQR_Stop(void);

//获取单次转换采样值
uint32_t Adc_GetSglResult(void);
//获取SQR扫描采样值
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux);
//获取JQR扫描采样值
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux);

//获取累加采样值
uint32_t Adc_GetAccResult(void);
//clear ADC 累加寄存器结果清除
void Adc_ClrAccResult(void);

/* 内部温度传感器使能/关闭 */
void Bgr_TempSensorEnable(void);
void Bgr_TempSensorDisable(void);
/* BGR使能/关闭 */
void Bgr_BgrEnable(void);
void Bgr_BgrDisable(void);
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

#endif /* __ADC_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
