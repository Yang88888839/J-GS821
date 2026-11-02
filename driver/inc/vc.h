/**
 ******************************************************************************
 * @file   vc.h
 *
 * @brief This file contains all the functions prototypes of the VC driver
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

#ifndef __VC_H__
#define __VC_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
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
 * @addtogroup DDL_VC VC模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup VC_Global_Types VC全局类型定义
 * @{
 */


/**
 * @brief  VC迟滞 VCx_CR0.HYS(x=0、1)
 */
typedef enum
{
    VcDelayoff  = 0u,    /*!<   迟滞关闭 */
    VcDelay10mv = 1u,    /*!<   迟滞10mv */
    VcDelay20mv = 2u,    /*!<   迟滞20mv */
    VcDelay30mv = 3u    /*!<   迟滞30mv */
} en_vc_cmp_delay_t;

/**
 * @brief  VC偏置电流 VCx_CR0.BIAS(x=0、1、2)
 */
typedef enum
{
    VcBias300na  = 0u,    /*!< 偏置电流300nA */
    VcBias1200na = 1u,    /*!< 偏置电流1.2uA */
    VcBias10ua   = 2u,    /*!< 偏置电流10uA */
    VcBias20ua   = 3u    /*!< 偏置电流20uA */
} en_vc_bias_current_t;


/**
 * @brief  VC输出滤波时间  VCx_CR  debounce_time(x=0、1、2)
 */
typedef enum
{
    VcFilterMskNone      = 0x0u,    /*!< 无滤波 */
    VcFilterMsk2Cycle    = 0x1u,    /*!< 滤波时间 2 周期 */
    VcFilterMsk4Cycle    = 0x2u,    /*!< 滤波时间 4 周期 */
    VcFilterMsk8Cycle    = 0x3u,    /*!< 滤波时间 8 周期 */
    VcFilterMsk16Cycle   = 0x4u,    /*!< 滤波时间 16 周期 */
    VcFilterMsk32Cycle   = 0x5u,    /*!< 滤波时间 32 周期 */
    VcFilterMsk64Cycle   = 0x6u,    /*!< 滤波时间 64 周期 */
    VcFilterMsk128Cycle  = 0x7u,    /*!< 滤波时间 128 周期 */
    VcFilterMsk256Cycle  = 0x8u,    /*!< 滤波时间 256 周期 */
    VcFilterMsk512Cycle  = 0x9u,    /*!< 滤波时间 512 周期 */
    VcFilterMsk1024Cycle = 0xAu,    /*!< 滤波时间 1024 周期 */
    VcFilterMsk2048Cycle = 0xBu,    /*!< 滤波时间 2048 周期 */
    VcFilterMsk4096Cycle = 0xCu     /*!< 滤波时间 4096 周期 */
} en_vc_resp_filter_t;

/**
 * @brief   VC滤波模式选择
 */
typedef enum
{
    VcFltModeMskNormal    = 0u,    /*!< 普通滤波模式 */
    VcFltModeMskFltPeak   = 0x1u,  /*!< 滤峰模式 */
    VcFltModeMskFltValley = 0x2u,  /*!< 滤谷模式 */
    VcFltModeMskFltGlitch = 0x3u   /*!< 滤刺模式 */
} en_vc_flt_mode_t;

/**
 * @brief   VC滤波时钟选择
 */
typedef enum
{
    VcFltClkMskRc256k = 0u,   /*!< 滤波时钟RC256K */
    VcFltClkMskPclk   = 0x1u  /*!< 滤波时钟PCLK */
} en_vc_flt_clk_t;

/**
 * @brief  VC P端输入
 */
typedef enum
{
    VcInPCh0 = 0u,      /*!< VC0输入通道0  PA01;    VC1输入通道0  PA01   */
    VcInPCh1 = 1u,      /*!< VC0输入通道1  PA03;    VC1输入通道1  PA03   */
    VcInPCh2 = 2u,      /*!< VC0输入通道2  PA06;    VC1输入通道2  PA06   */
    VcInPCh3 = 3u,      /*!< VC0输入通道3  PA07;    VC1输入通道3  PA07   */
    VcInPCh4 = 4u,      /*!< VC0输入通道4  PB04;    VC1输入通道4  PB04   */
    VcInPCh5 = 5u,      /*!< VC0输入通道5  PB05;    VC1输入通道5  PB05   */
    VcInPCh6 = 6u,      /*!< VC0输入通道6  PB06;    VC1输入通道6  PB06   */
    VcInPCh7 = 7u,      /*!< VC0输入通道7  PB07;    VC1输入通道7  PB07   */
} en_vc_input_p_src_t;

/**
 * @brief  VC N端输入
 */
typedef enum
{
    VcInNCh0    = 0u,    /*!< VC0输入通道0  PA00;    VC1输入通道0 PA02 */
    VcInNCh1    = 1u,    /*!< VC0输入通道1  PA04;    VC1输入通道1 PA04 */
    VcInNCh2    = 2u,    /*!< VC0输入通道2  PA05;    VC1输入通道2 PA05 */
    VcInNCh3    = 3u,    /*!< VC0输入通道3  PB01;    VC1输入通道3 PB03 */
    VcInNCh4    = 4u,    /*!< VC0输入通道4  Vcore;   VC1输入通道4 Vcore */
    ResDivOut   = 5u,    /*!< VC0输入通道5  电阻分压;VC1输入通道5 电阻分压 */
    AiTs        = 6u,    /*!< VC0输入通道6  Ts;      VC1输入通道6 Ts */
    VcInNCh7    = 7u,    /*!< VC0输入通道7  PA04;    VC1输入通道7 PA04 */
} en_vc_input_n_src_t;

/**
 * @brief  VC中断触发方式
 */
typedef enum
{
    VcIrqNone = 0u,    /*!< 无中断 */
    VcIrqFall = 0x1000u,    /*!< 下降沿触发 */
    VcIrqRise = 0x2000u,    /*!< 上升沿触发 */
    VcIrqHigh = 0x4000u,    /*!< 高电平触发 */
} en_vc_irq_sel_t;

/**
 * @brief  VC状态
 */
typedef enum
{
    Vc_Intf    = 0u,    /*!< VCx中断标志 */
    Vc_Filter  = 1u,    /*!< VCx Filter 后的状态 */
} en_vc_ifr_t;

/**
 * @brief  VC输出配置 VCx_CR2(x=0、1)
 * @note  
 */
typedef enum
{
    VcOutDisable   = 0u,
    VcOutInvOutput = 0x1u,    /*!< 使能结果输出反向 */
    VcOutTIM0RCLR  = 0x2u,    /*!< 结果输出到TIM0 REFCLR使能控制 */
    VcOutTIM1RCLR  = 0x4u,    /*!< 结果输出到TIM1 REFCLR使能控制 */
    VcOutTIM2RCLR  = 0x8u,    /*!< 结果输出到TIM2 REFCLR使能控制 */
    VcOutTIM3RCLR  = 0x10u,   /*!< 结果输出到TIM3 REFCLR使能控制 */
    VcOutTIMBK     = 0x20u,   /*!< 结果输出到Timer0,1,2,3刹车控制 */
} en_vc_output_cfg_t;

/**
 * @brief  VC 窗口配置 VCx_CR2(x=0、1)
 * @note  
 */
typedef enum
{
    VcWindNone        = 0x0u,   /*!< 无空白窗口 */
    VcWindTim0Ocrefb  = 0x1u,   /*!< 空白窗口为TIM0 OCREFB信号  */
    VcWindTim3Ocref0b = 0x2u,   /*!< 空白窗口为TIM3 OCREF0B信号  */
    VcWindTim3Ocref1b = 0x4u,   /*!< 空白窗口为TIM3 OCREF1B信号  */
    VcWindTim3Ocref2b = 0x8u,   /*!< 空白窗口为TIM3 OCREF2B信号  */
} en_vc_window_cfg_t;

/**
 * @brief  VC DIV参考电压Vref选择 VC_CR   VC_REF2P5_SEL
 */
typedef enum
{
    VcDivVrefAvcc = 0u,             /*!< AVCC */
    VcDivVrefAdc  = 1u,             /*!< ADC_CR0 SREF选择参考电压 */
} en_vc_div_vref_t;

/**
 * @brief  VC DIV电阻分压配置
 */
typedef struct
{
    boolean_t           bDivEn;       /*!< VC_CR: VC_DIV_EN */
    uint8_t             u8DivVal;     /*!< VC_CR: VC_DIV 范围：0-63 */
    en_vc_div_vref_t    enDivVref;    /*!< VC_CR: VC_REF2P5_SEL @ref en_vc_div_vref_t */
} stc_vc_div_cfg_t;


/**
 * @brief  VC 空白窗口功能配置
 */
typedef struct
{
    boolean_t               bBlanken;           /*!< 空白窗口使能 */
    en_vc_window_cfg_t      enBlankSel;         /*!< 空白窗口信号选择 */
} stc_vc_blank_cfg_t;

/**
 * @brief  VC 滤波功能配置
 */
typedef struct
{
    en_vc_flt_mode_t        enFltMode;          /*!< 滤波模式选择 */
    en_vc_flt_clk_t         enFltClk;           /*!< 滤波时钟源选择 */
    en_vc_resp_filter_t     enVcFilterTime;     /*!< 输出滤波时间 */
} stc_vc_flt_cfg_t;

/**
 * @brief  VC通道配置
 */
typedef struct
{
    en_vc_cmp_delay_t       enVcCmpDly;         /*!< VC迟滞 */
    en_vc_bias_current_t    enVcBiasCurrent;    /*!< VC功耗选择 */
    en_vc_flt_mode_t        enFltMode;          /*!< 滤波模式选择 */
    en_vc_flt_clk_t         enFltClk;           /*!< 滤波时钟源选择 */
    en_vc_resp_filter_t     enVcFilterTime;     /*!< 输出滤波时间 */
    en_vc_input_p_src_t     enVcInPin_P;        /*!< P端输入 */
    en_vc_input_n_src_t     enVcInPin_N;        /*!< N端输入  */
    uint32_t                u32VcOutCfg;         /*!< 输出配置 @ref en_vc_output_cfg_t  */
    boolean_t               bBlanken;           /*!< 空白窗口使能 */
    en_vc_window_cfg_t      enBlankSel;         /*!< 空白窗口信号选择 */
} stc_vc_channel_cfg_t;
/**
 * @}
 */
/******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup VC_Global_Macros VC Global Macros
 * @{
 */
 
/**
 * @defgroup VC_VC0_TRIM VC0 Trim Value
 * @{
 */
#define VC_VC0_TRIM_POSITIVE             (*((volatile uint8_t*) (0x00101BC0ul)));
#define VC_VC0_TRIM_NEGATIVE             (*((volatile uint8_t*) (0x00101BC1ul)));
/**
 * @}
 */

/**
 * @defgroup VC_VC1_TRIM VC1 Trim Value
 * @{
 */
#define VC_VC1_TRIM_POSITIVE             (*((volatile uint8_t*) (0x00101BC2ul)));
#define VC_VC1_TRIM_NEGATIVE             (*((volatile uint8_t*) (0x00101BC3ul)));
/**
 * @}
 */
 
/**
 * @}
 */
 
/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup VC_Global_Functions VC全局函数定义
 * @{
 */
void Vc_CfgItType(M0P_VC_TypeDef *VCx, en_vc_irq_sel_t ItType);
void Vc_ClrItType(M0P_VC_TypeDef *VCx, en_vc_irq_sel_t ItType);
void  Vc_ItCfg(M0P_VC_TypeDef *VCx, boolean_t NewStatus);
boolean_t Vc_GetItStatus(M0P_VC_TypeDef *VCx, en_vc_ifr_t Result);
void Vc_ClearItStatus(M0P_VC_TypeDef *VCx);
en_result_t Vc_DivInit(M0P_VC_TypeDef *VCx, stc_vc_div_cfg_t *pstcDacCfg);
en_result_t Vc_Fltcfg(M0P_VC_TypeDef *VCx, stc_vc_flt_cfg_t *pstcFltCfg);
en_result_t Vc_Blankcfg(M0P_VC_TypeDef *VCx, stc_vc_blank_cfg_t *pstcFltCfg);
en_result_t Vc_Outputcfg(M0P_VC_TypeDef *VCx, uint32_t u32VcOutCfg);
en_result_t Vc_Init(M0P_VC_TypeDef *VCx, stc_vc_channel_cfg_t *pstcChannelCfg);
void Vc_Cmd(M0P_VC_TypeDef *VCx, boolean_t NewStatus);
void Vc_Vc0TrimCfg(uint8_t u8Vc0Trim);
void Vc_Vc1TrimCfg(uint8_t u8Vc1Trim);
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

#endif /* __VC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

