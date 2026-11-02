/**
 *******************************************************************************
 * @file  timer3.c
 * @brief This file provides firmware functions to manage the TIMER3.
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
#include "timer3.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_TIMER3 TIMER3模块驱动库
 * @brief TIMER3 Driver Library TIMER3模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup TIMER3_Global_Functions TIMER3全局函数定义
 * @{
 */

/**
 * @brief  Timer3 中断标志获取(模式0/1/23)
 * @param  [in] enTim3Irq 中断类型 @ref en_tim3_irq_type_t
 * @retval boolean_t
 *         - TRUE: 发生中断
 *         - FALSE: 没有发生中断
 */
boolean_t Tim3_GetIntFlag(en_tim3_irq_type_t enTim3Irq)
{
    boolean_t bRetVal = FALSE;
    uint32_t  u32Val;

    u32Val  = M0P_TIM3_MODE23->IFR;
    bRetVal = (u32Val >> enTim3Irq) & 0x1;

    return bRetVal;
}

/**
 * @brief  Timer3 中断标志清除(模式0/1/23)
 * @param  [in] enTim3Irq 中断类型 @ref en_tim3_irq_type_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_ClearIntFlag(en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->ICLR = ~(1u << enTim3Irq);

    return enResult;
}

/**
 * @brief  Timer3 中断所有标志清除(模式23)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_ClearAllIntFlag(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->ICLR = 0;

    return enResult;
}

/**
 * @brief  Timer3 中断使能(模式0)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_Mode0_EnableIrq(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->M0CR_f.UIE = TRUE;

    return enResult;
}

/**
 * @brief  Timer3 中断禁止(模式0)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_Mode0_DisableIrq(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->M0CR_f.UIE = FALSE;

    return enResult;
}

/**
 * @brief  Timer3 中断使能(模式1)
 * @param  [in] enTim3Irq 中断类型 @ref en_tim3_irq_type_t
 *         @arg Tim3UevIrq 溢出/事件更新中断
 *         @arg Tim3CA0Irq CH0A捕获/比较中断(仅模式1/23存在)
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_Mode1_EnableIrq(en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;

    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            M0P_TIM3_MODE1->M1CR_f.UIE = TRUE;
            break;
        case Tim3CA0Irq:
            M0P_TIM3_MODE1->CR0_f.CIEA = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 * @brief  Timer3 中断禁止(模式1)
 * @param  [in] enTim3Irq 中断类型 @ref en_tim3_irq_type_t
 *         @arg Tim3UevIrq 溢出/事件更新中断
 *         @arg Tim3CA0Irq CH0A捕获/比较中断(仅模式1/23存在)
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_Mode1_DisableIrq(en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;

    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            M0P_TIM3_MODE1->M1CR_f.UIE = FALSE;
            break;
        case Tim3CA0Irq:
            M0P_TIM3_MODE1->CR0_f.CIEA = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 * @brief  Timer3 中断使能(模式23)
 * @param  [in] enTim3Irq 中断类型 @ref en_tim3_irq_type_t
 *         @arg Tim3UevIrq 溢出/事件更新中断
 *         @arg Tim3CA0Irq CH0A捕获/比较中断(仅模式1/23存在)
 *         @arg Tim3CB0Irq CH0B捕获/比较中断(仅模式23存在)
 *         @arg Tim3CA1Irq CH1A捕获/比较中断(仅模式23存在)
 *         @arg Tim3CB1Irq CH1B捕获/比较中断(仅模式23存在)
 *         @arg Tim3CA2Irq CH2A捕获/比较中断(仅模式23存在)
 *         @arg Tim3CB2Irq CH2B捕获/比较中断(仅模式23存在)
 *         @arg Tim3BkIrq 刹车中断(仅模式23存在）
 *         @arg Tim3TrigIrq 触发中断(仅模式23存在）
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_Mode23_EnableIrq(en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;

    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            M0P_TIM3_MODE23->M23CR_f.UIE = TRUE;
            break;
        case Tim3CA0Irq:
            M0P_TIM3_MODE23->CRCH0_f.CIEA = TRUE;
            break;
        case Tim3CB0Irq:
            M0P_TIM3_MODE23->CRCH0_f.CIEB = TRUE;
            break;
        case Tim3CA1Irq:
            M0P_TIM3_MODE23->CRCH1_f.CIEA = TRUE;
            break;
        case Tim3CB1Irq:
            M0P_TIM3_MODE23->CRCH1_f.CIEB = TRUE;
            break;
        case Tim3CA2Irq:
            M0P_TIM3_MODE23->CRCH2_f.CIEA = TRUE;
            break;
        case Tim3CB2Irq:
            M0P_TIM3_MODE23->CRCH2_f.CIEB = TRUE;
            break;
        case Tim3BkIrq:
            M0P_TIM3_MODE23->M23CR_f.BIE = TRUE;
            break;
        case Tim3TrigIrq:
            M0P_TIM3_MODE23->M23CR_f.TIE = TRUE;
            break;
        case Tim3OVIrq:
            M0P_TIM3_MODE23->M23CR_f.OVE = TRUE;
            break;
        case Tim3UNDIrq:
            M0P_TIM3_MODE23->M23CR_f.UNDE = TRUE;
            break;
        case Tim3CA3Irq:
            M0P_TIM3_MODE23->CRCH3A_f.CIE = TRUE;
            break;
        case Tim3CB3Irq:
            M0P_TIM3_MODE23->CRCH3B_f.CIE = TRUE;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 * @brief  Timer3 中断禁止(模式23)
 * @param  [in] enTim3Irq 中断类型 @ref en_tim3_irq_type_t
 *         @arg Tim3UevIrq 溢出/事件更新中断
 *         @arg Tim3CA0Irq CH0A捕获/比较中断(仅模式1/23存在)
 *         @arg Tim3CB0Irq CH0B捕获/比较中断(仅模式23存在)
 *         @arg Tim3CA1Irq CH1A捕获/比较中断(仅模式23存在)
 *         @arg Tim3CB1Irq CH1B捕获/比较中断(仅模式23存在)
 *         @arg Tim3CA2Irq CH2A捕获/比较中断(仅模式23存在)
 *         @arg Tim3CB2Irq CH2B捕获/比较中断(仅模式23存在)
 *         @arg Tim3BkIrq 刹车中断(仅模式23存在）
 *         @arg Tim3TrigIrq 触发中断(仅模式23存在）
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_Mode23_DisableIrq(en_tim3_irq_type_t enTim3Irq)
{
    en_result_t enResult = Ok;

    switch (enTim3Irq)
    {
        case Tim3UevIrq:
            M0P_TIM3_MODE23->M23CR_f.UIE = FALSE;
            break;
        case Tim3CA0Irq:
            M0P_TIM3_MODE23->CRCH0_f.CIEA = FALSE;
            break;
        case Tim3CB0Irq:
            M0P_TIM3_MODE23->CRCH0_f.CIEB = FALSE;
            break;
        case Tim3CA1Irq:
            M0P_TIM3_MODE23->CRCH1_f.CIEA = FALSE;
            break;
        case Tim3CB1Irq:
            M0P_TIM3_MODE23->CRCH1_f.CIEB = FALSE;
            break;
        case Tim3CA2Irq:
            M0P_TIM3_MODE23->CRCH2_f.CIEA = FALSE;
            break;
        case Tim3CB2Irq:
            M0P_TIM3_MODE23->CRCH2_f.CIEB = FALSE;
            break;
        case Tim3BkIrq:
            M0P_TIM3_MODE23->M23CR_f.BIE = FALSE;
            break;
        case Tim3TrigIrq:
            M0P_TIM3_MODE23->M23CR_f.TIE = FALSE;
            break;
        case Tim3OVIrq:
            M0P_TIM3_MODE23->M23CR_f.OVE = FALSE;
            break;
        case Tim3UNDIrq:
            M0P_TIM3_MODE23->M23CR_f.UNDE = FALSE;
            break;
        case Tim3CA3Irq:
            M0P_TIM3_MODE23->CRCH3A_f.CIE = FALSE;
            break;
        case Tim3CB3Irq:
            M0P_TIM3_MODE23->CRCH3B_f.CIE = FALSE;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 * @brief  Timer3 初始化配置(模式0)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_mode0_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_Mode0_Init(stc_tim3_mode0_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->M0CR_f.MODE  = pstcCfg->enWorkMode;
    M0P_TIM3_MODE0->M0CR_f.GATEP = pstcCfg->enGateP;
    M0P_TIM3_MODE0->M0CR_f.GATE  = pstcCfg->bEnGate;
    M0P_TIM3_MODE0->M0CR_f.PRS   = pstcCfg->enPRS;
    M0P_TIM3_MODE0->M0CR_f.TOGEN = pstcCfg->bEnTog;
    M0P_TIM3_MODE0->M0CR_f.CT    = pstcCfg->enCT;
    M0P_TIM3_MODE0->M0CR_f.MD    = pstcCfg->enCntMode;

    return enResult;
}

/**
 * @brief  Timer3 启动运行(模式0)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M0_Run(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->M0CR_f.CTEN = TRUE;

    return enResult;
}

/**
 * @brief  Timer3 停止运行(模式0)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M0_Stop(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->M0CR_f.CTEN = FALSE;

    return enResult;
}

/**
 * @brief  Timer3 端口输出使能/禁止设定(模式0)
 * @param  [in] bEnOutput 翻转输出设定 TRUE:使能, FALSE:禁止 @ref boolean_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M0_Enable_Output(boolean_t bEnOutput)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->DTR_f.MOE = bEnOutput;

    return enResult;
}

/**
 * @brief  Timer3 翻转使能/禁止（低电平）设定(模式0)
 * @param  [in] bEnTOG 翻转输出设定 TRUE:使能, FALSE:禁止 @ref boolean_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M0_EnTOG(boolean_t bEnTOG)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->M0CR_f.TOGEN = bEnTOG;

    return enResult;
}

/**
 * @brief  Timer3 16位计数器初值设置(模式0)
 * @param  [in] u16Data CNT 16位初值
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M0_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->CNT_f.CNT = u16Data;

    return enResult;
}

/**
 * @brief  Timer3 16位计数值获取(模式0)
 * @retval 16位计数值
 */
uint16_t Tim3_M0_Cnt16Get(void)
{
    uint16_t u16CntData = 0;

    u16CntData = M0P_TIM3_MODE0->CNT_f.CNT;

    return u16CntData;
}

/**
 * @brief  Timer3 重载值设置(模式0)
 * @param  [in] u16Data 16位重载值
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M0_ARRSet(uint16_t u16Data)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->ARR_f.ARR = u16Data;

    return enResult;
}

/**
 * @brief  Timer3 32位计数器初值设置(模式0)
 * @param  [in] u32Data 32位初值
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M0_Cnt32Set(uint32_t u32Data)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE0->CNT32_f.CNT32 = u32Data;

    return enResult;
}

/**
 * @brief  Timer3 32位计数值获取(模式0)
 * @retval 32位计数值
 */
uint32_t Tim3_M0_Cnt32Get(void)
{
    uint32_t u32CntData = 0;

    u32CntData = M0P_TIM3_MODE0->CNT32_f.CNT32;

    return u32CntData;
}

/**
 * @brief  Timer3 初始化配置(模式1)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_mode1_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_Mode1_Init(stc_tim3_mode1_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE1->M1CR_f.MODE    = pstcCfg->enWorkMode;
    M0P_TIM3_MODE1->M1CR_f.PRS     = pstcCfg->enPRS;
    M0P_TIM3_MODE1->M1CR_f.CT      = pstcCfg->enCT;
    M0P_TIM3_MODE1->M1CR_f.ONESHOT = pstcCfg->enOneShot;

    return enResult;
}

/**
 * @brief  Timer3 PWC 输入配置(模式1)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_pwc_input_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M1_Input_Cfg(stc_tim3_pwc_input_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE1->MSCR_f.TS    = pstcCfg->enTsSel;
    M0P_TIM3_MODE1->MSCR_f.IA0S  = pstcCfg->enIA0Sel;
    M0P_TIM3_MODE1->MSCR_f.IB0S  = pstcCfg->enIB0Sel;
    M0P_TIM3_MODE1->FLTR_f.ETP   = pstcCfg->enETRPhase;
    M0P_TIM3_MODE1->FLTR_f.FLTET = pstcCfg->enFltETR;
    M0P_TIM3_MODE1->FLTR_f.FLTA0 = pstcCfg->enFltIA0;
    M0P_TIM3_MODE1->FLTR_f.FLTB0 = pstcCfg->enFltIB0;
    if (pstcCfg->enTsSel == Tim3Ts6IAFP)
    {
        M0P_TIM3_MODE1->CR0_f.CSA = 1; /* CHA设置为捕获模式 */
    }
    else if (pstcCfg->enTsSel == Tim3Ts7IBFP)
    {
        M0P_TIM3_MODE1->CR0_f.CSB = 1; /* CHB设置为捕获模式 */
    }
    else {}

    return enResult;
}

/**
 * @brief  Timer3 PWC测量边沿起始结束选择(模式1)
 * @param  [in] enEdgeSel PWC测量起始终止电平 @ref en_tim3_m1cr_Edge_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M1_PWC_Edge_Sel(en_tim3_m1cr_Edge_t enEdgeSel)
{
    en_result_t enResult = Ok;

    switch (enEdgeSel)
    {
        case 0:                                /* 上升沿到上升沿(周期) */
            M0P_TIM3_MODE1->M1CR_f.EDG1ST = 0; /* 上升沿 */
            M0P_TIM3_MODE1->M1CR_f.EDG2ND = 0; /* 上升沿 */
            break;
        case 1:                                /* 下降沿到上升沿(低电平) */
            M0P_TIM3_MODE1->M1CR_f.EDG1ST = 1; /* 下降沿 */
            M0P_TIM3_MODE1->M1CR_f.EDG2ND = 0; /* 上升沿 */
            break;
        case 2:                                /* 上升沿到下降沿(高电平) */
            M0P_TIM3_MODE1->M1CR_f.EDG1ST = 0; /* 上升沿 */
            M0P_TIM3_MODE1->M1CR_f.EDG2ND = 1; /* 下降沿 */
            break;
        case 3:                                /* 下降沿到下降沿(周期) */
            M0P_TIM3_MODE1->M1CR_f.EDG1ST = 1; /* 下降沿 */
            M0P_TIM3_MODE1->M1CR_f.EDG2ND = 1; /* 下降沿 */
            break;
        default:
            break;
    }

    return enResult;
}

/**
 * @brief  Timer3 启动运行(模式1)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M1_Run(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE1->M1CR_f.CTEN = TRUE;

    return enResult;
}

/**
 * @brief  Timer3 停止运行(模式1)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M1_Stop(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE1->M1CR_f.CTEN = FALSE;

    return enResult;
}

/**
 * @brief  Timer3 16位计数器初值设置(模式1)
 * @param  [in] u16Data 16位初值
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M1_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE1->CNT_f.CNT = u16Data;

    return enResult;
}

/**
 * @brief  Timer3 16位计数值获取(模式1)
 * @retval 16位计数值
 */
uint16_t Tim3_M1_Cnt16Get(void)
{
    uint16_t u16CntData = 0;

    u16CntData = M0P_TIM3_MODE1->CNT_f.CNT;

    return u16CntData;
}

/**
 * @brief  Timer3 脉冲宽度测量结果数值获取(模式1)
 * @retval 16位脉冲宽度测量结果
 */
uint16_t Tim3_M1_PWC_CapValueGet(void)
{
    uint16_t u16CapData = 0;

    u16CapData = M0P_TIM3_MODE1->CCR0A_f.CCR0A;

    return u16CapData;
}
/**
 * @brief  Timer3 初始化配置(模式23)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_mode23_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_Mode23_Init(stc_tim3_mode23_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.MODE = pstcCfg->enWorkMode;

    M0P_TIM3_MODE23->M23CR_f.PRS     = pstcCfg->enPRS;
    M0P_TIM3_MODE23->M23CR_f.CT      = pstcCfg->enCT;
    M0P_TIM3_MODE23->M23CR_f.COMP    = pstcCfg->enPWMTypeSel;
    M0P_TIM3_MODE23->M23CR_f.PWM2S   = pstcCfg->enPWM2sSel;
    M0P_TIM3_MODE23->M23CR_f.ONESHOT = pstcCfg->bOneShot;
    M0P_TIM3_MODE23->M23CR_f.URS     = pstcCfg->bURSSel;
    M0P_TIM3_MODE23->M23CR_f.DIR     = pstcCfg->enCntDir;

    return enResult;
}

/**
 * @brief  Timer3 PWM输出使能(模式23)
 * @param  [in] bEnOutput PWM输出设定 TRUE:使能，FALSE:禁止 @ref boolean_t
 * @param  [in] bEnAutoOutput PWM自动输出设定 TRUE:使能，FALSE:禁止 @ref boolean_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_EnPWM_Output(boolean_t bEnOutput, boolean_t bEnAutoOutput)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->DTR_f.MOE = bEnOutput;
    M0P_TIM3_MODE23->DTR_f.AOE = bEnAutoOutput;

    return enResult;
}

/**
 * @brief  Timer3 启动运行(模式23)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_Run(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.CTEN = TRUE;

    return enResult;
}

/**
 * @brief  Timer3 停止运行(模式23)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_Stop(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.CTEN = FALSE;

    return enResult;
}

/**
 * @brief  Timer3 重载值设置(模式23)
 * @param  [in] u16Data 16位重载值 @ref uint16_t
 * @param  [in] bArrBufEn ARR重载缓存设定 TRUE:使能，FALSE:禁止 @ref boolean_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_ARRSet(uint16_t u16Data, boolean_t bArrBufEn)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->ARR_f.ARR      = u16Data;
    M0P_TIM3_MODE23->M23CR_f.BUFPEN = bArrBufEn;

    return enResult;
}

/**
 * @brief  Timer3 16位计数器初值设置(模式23)
 * @param  [in] u16Data 16位初值
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_Cnt16Set(uint16_t u16Data)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->CNT_f.CNT = u16Data;

    return enResult;
}

/**
 * @brief  Timer3 16位计数值获取(模式23)
 * @retval 16位计数值
 */
uint16_t Tim3_M23_Cnt16Get(void)
{
    uint16_t u16CntData = 0;

    u16CntData = M0P_TIM3_MODE23->CNT_f.CNT;

    return u16CntData;
}

/**
 * @brief  Timer3 比较捕获寄存器CCRxA/CCRxB设置(模式23)
 * @param  [in] enCCRSel CCRxA/CCRxB设定 @ref en_tim3_m23_ccrx_t
 * @param  [in] u16Data CCRxA/CCRxB 16位初始值
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_M23_CCR_Set(en_tim3_m23_ccrx_t enCCRSel, uint16_t u16Data)
{
    en_result_t enResult = Ok;

    uint32_t u32BaseAddress;

    u32BaseAddress = (uint32_t)(&M0P_TIM3_MODE23->CCR0A) + (uint32_t)enCCRSel;

    *(volatile uint32_t *)u32BaseAddress = u16Data;

    return enResult;
}

/**
 * @brief  Timer3 比较捕获寄存器CCRxA/CCRxB读取(模式23)
 * @param  [in] enCCRSel CCRxA/CCRxB设定 @ref en_tim3_m23_ccrx_t
 * @retval 16位CCRxA/CCRxB捕获值
 */
uint16_t Tim3_M23_CCR_Get(en_tim3_m23_ccrx_t enCCRSel)
{
    uint32_t u32BaseAddress;

    u32BaseAddress = (uint32_t)(&M0P_TIM3_MODE23->CCR0A) + (uint32_t)enCCRSel;


    return *(volatile uint16_t *)u32BaseAddress;
}

/**
 * @brief  Timer3 PWM互补输出模式下，GATE功能选择(模式23)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_gate_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_GateFuncSel(stc_tim3_m23_gate_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.CSG = pstcCfg->enGateFuncSel;
    M0P_TIM3_MODE23->M23CR_f.CRG = pstcCfg->bGateRiseCap;
    M0P_TIM3_MODE23->M23CR_f.CFG = pstcCfg->bGateFallCap;

    return enResult;
}

/**
 * @brief  Timer3 主从模式配置(模式23)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_master_slave_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_MasterSlave_Set(stc_tim3_m23_master_slave_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->MSCR_f.MSM = pstcCfg->enMasterSlaveSel;
    M0P_TIM3_MODE23->MSCR_f.MMS = pstcCfg->enMasterSrc;
    M0P_TIM3_MODE23->MSCR_f.SMS = pstcCfg->enSlaveModeSel;
    M0P_TIM3_MODE23->MSCR_f.TS  = pstcCfg->enTsSel;

    return enResult;
}

/**
 * @brief  Timer3 CHxA/CHxB比较通道控制(模式23)
 * @param  [in] enTim3Chx Timer3通道(Tim3CH0, Tim3CH1, Tim3CH2) @ref en_tim3_channel_t
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_compare_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_M23_PortOutput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_compare_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    switch (enTim3Chx)
    {
        case Tim3CH0:
            M0P_TIM3_MODE23->CRCH0_f.CSA        = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMA0_FLTA0 = pstcCfg->enCHxACmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPA0       = pstcCfg->enCHxAPolarity;
            M0P_TIM3_MODE23->CRCH0_f.BUFEA      = pstcCfg->bCHxACmpBufEn;
            M0P_TIM3_MODE23->M23CR_f.CIS        = pstcCfg->enCHxACmpIntSel;

            M0P_TIM3_MODE23->CRCH0_f.CSB        = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMB0_FLTB0 = pstcCfg->enCHxBCmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPB0       = pstcCfg->enCHxBPolarity;
            M0P_TIM3_MODE23->CRCH0_f.BUFEB      = pstcCfg->bCHxBCmpBufEn;
            M0P_TIM3_MODE23->CRCH0_f.CISB       = pstcCfg->enCHxBCmpIntSel;
            break;
        case Tim3CH1:
            M0P_TIM3_MODE23->CRCH1_f.CSA        = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMA1_FLTA1 = pstcCfg->enCHxACmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPA1       = pstcCfg->enCHxAPolarity;
            M0P_TIM3_MODE23->CRCH1_f.BUFEA      = pstcCfg->bCHxACmpBufEn;
            M0P_TIM3_MODE23->M23CR_f.CIS        = pstcCfg->enCHxACmpIntSel;

            M0P_TIM3_MODE23->CRCH1_f.CSB        = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMB1_FLTB1 = pstcCfg->enCHxBCmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPB1       = pstcCfg->enCHxBPolarity;
            M0P_TIM3_MODE23->CRCH1_f.BUFEB      = pstcCfg->bCHxBCmpBufEn;
            M0P_TIM3_MODE23->CRCH1_f.CISB       = pstcCfg->enCHxBCmpIntSel;
            break;
        case Tim3CH2:
            M0P_TIM3_MODE23->CRCH2_f.CSA        = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMA2_FLTA2 = pstcCfg->enCHxACmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPA2       = pstcCfg->enCHxAPolarity;
            M0P_TIM3_MODE23->CRCH2_f.BUFEA      = pstcCfg->bCHxACmpBufEn;
            M0P_TIM3_MODE23->M23CR_f.CIS        = pstcCfg->enCHxACmpIntSel;

            M0P_TIM3_MODE23->CRCH2_f.CSB        = 0;
            M0P_TIM3_MODE23->FLTR_f.OCMB2_FLTB2 = pstcCfg->enCHxBCmpCtrl;
            M0P_TIM3_MODE23->FLTR_f.CCPB2       = pstcCfg->enCHxBPolarity;
            M0P_TIM3_MODE23->CRCH2_f.BUFEB      = pstcCfg->bCHxBCmpBufEn;
            M0P_TIM3_MODE23->CRCH2_f.CISB       = pstcCfg->enCHxBCmpIntSel;
            break;
        default:
            enResult = Error;
            break;
    }

    return enResult;
}

/**
 * @brief  Timer3 CH3A/CH3B比较通道配置(模式23)
 * @param [in] enTim3Chx:  Timer3 CH3通道(Tim3CH3A, Tim3CH3B) @ref en_tim3_ch3_t
 * @param [in] pstcCfg:    配置结构体指针 @ref stc_tim3_m23_ch3_cfg_t
 *
 * @retval en_result_t:
 *           - Ok: 设定成功
 *           - 其他: 设定失败
 */
en_result_t Tim3_M23_Ch3_Cfg(en_tim3_ch3_t enTim3Chx, stc_tim3_m23_ch3_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    if (Tim3CH3A == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH3A_f.CIS = pstcCfg->enCH3CmpIntSel;
        M0P_TIM3_MODE23->CRCH3A_f.BUF = pstcCfg->bCH3CompValBuffEn;
        M0P_TIM3_MODE23->CRCH3A_f.CDE = pstcCfg->bCH3ComTrigDMAEn;
        M0P_TIM3_MODE23->CRCH3A_f.CM3AE = pstcCfg->bCH3TrigAdcEn;
        M0P_TIM3_MODE23->CRCH3A_f.C3AEN = pstcCfg->bCH3CompEn;
    }
    else
    {
        M0P_TIM3_MODE23->CRCH3B_f.CIS = pstcCfg->enCH3CmpIntSel;
        M0P_TIM3_MODE23->CRCH3B_f.BUF = pstcCfg->bCH3CompValBuffEn;
        M0P_TIM3_MODE23->CRCH3B_f.CDE = pstcCfg->bCH3ComTrigDMAEn;
        M0P_TIM3_MODE23->CRCH3B_f.CM3BE = pstcCfg->bCH3TrigAdcEn;
        M0P_TIM3_MODE23->CRCH3B_f.C3BEN = pstcCfg->bCH3CompEn;
    }

    return enResult;
}

/**
 * @brief  Timer3 CHxA/CHxB输入控制(模式23)
 * @param  [in] enTim3Chx Timer3通道(Tim3CH0, Tim3CH1, Tim3CH2) @ref en_tim3_channel_t
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_input_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_M23_PortInput_Cfg(en_tim3_channel_t enTim3Chx, stc_tim3_m23_input_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    switch (enTim3Chx)
    {
        case Tim3CH0:
            M0P_TIM3_MODE23->CRCH0_f.CSA          = 1;
            M0P_TIM3_MODE23->CRCH0_f.CFA_CRA_BKSA = pstcCfg->enCHxACapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMA0_FLTA0   = pstcCfg->enCHxAInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPA0         = pstcCfg->enCHxAPolarity;

            M0P_TIM3_MODE23->CRCH0_f.CSB          = 1;
            M0P_TIM3_MODE23->CRCH0_f.CFB_CRB_BKSB = pstcCfg->enCHxBCapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMB0_FLTB0   = pstcCfg->enCHxBInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPB0         = pstcCfg->enCHxBPolarity;
            break;
        case Tim3CH1:
            M0P_TIM3_MODE23->CRCH1_f.CSA          = 1;
            M0P_TIM3_MODE23->CRCH1_f.CFA_CRA_BKSA = pstcCfg->enCHxACapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMA1_FLTA1   = pstcCfg->enCHxAInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPA1         = pstcCfg->enCHxAPolarity;

            M0P_TIM3_MODE23->CRCH1_f.CSB          = 1;
            M0P_TIM3_MODE23->CRCH1_f.CFB_CRB_BKSB = pstcCfg->enCHxBCapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMB1_FLTB1   = pstcCfg->enCHxBInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPB1         = pstcCfg->enCHxBPolarity;
            break;
        case Tim3CH2:
            M0P_TIM3_MODE23->CRCH2_f.CSA          = 1;
            M0P_TIM3_MODE23->CRCH2_f.CFA_CRA_BKSA = pstcCfg->enCHxACapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMA2_FLTA2   = pstcCfg->enCHxAInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPA2         = pstcCfg->enCHxAPolarity;

            M0P_TIM3_MODE23->CRCH2_f.CSB          = 1;
            M0P_TIM3_MODE23->CRCH2_f.CFB_CRB_BKSB = pstcCfg->enCHxBCapSel;
            M0P_TIM3_MODE23->FLTR_f.OCMB2_FLTB2   = pstcCfg->enCHxBInFlt;
            M0P_TIM3_MODE23->FLTR_f.CCPB2         = pstcCfg->enCHxBPolarity;
            break;
        default:
            enResult = Error;
            break;
    }
    return enResult;
}

/**
 * @brief  Timer3 ERT输入控制(模式23)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_etr_input_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_ETRInput_Cfg(stc_tim3_m23_etr_input_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->FLTR_f.ETP   = pstcCfg->enETRPolarity;
    M0P_TIM3_MODE23->FLTR_f.FLTET = pstcCfg->enETRFlt;

    return enResult;
}

/**
 * @brief  Timer3 刹车BK输入控制(模式23)
 * @param  [in] pstcBkCfg 初始化配置结构体指针 @ref stc_tim3_m23_bk_input_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_BrakeInput_Cfg(stc_tim3_m23_bk_input_cfg_t *pstcBkCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->DTR_f.BKE            = pstcBkCfg->bEnBrake;
    M0P_TIM3_MODE23->DTR_f.VCE            = pstcBkCfg->bEnVCBrake;
    M0P_TIM3_MODE23->DTR_f.SAFEEN         = pstcBkCfg->bEnSafetyBk;
    M0P_TIM3_MODE23->DTR_f.BKSEL          = pstcBkCfg->bEnBKSync;
    M0P_TIM3_MODE23->CRCH0_f.CFA_CRA_BKSA = pstcBkCfg->enBkCH0AStat;
    M0P_TIM3_MODE23->CRCH0_f.CFB_CRB_BKSB = pstcBkCfg->enBkCH0BStat;
    M0P_TIM3_MODE23->CRCH1_f.CFA_CRA_BKSA = pstcBkCfg->enBkCH1AStat;
    M0P_TIM3_MODE23->CRCH1_f.CFB_CRB_BKSB = pstcBkCfg->enBkCH1BStat;
    M0P_TIM3_MODE23->CRCH2_f.CFA_CRA_BKSA = pstcBkCfg->enBkCH2AStat;
    M0P_TIM3_MODE23->CRCH2_f.CFB_CRB_BKSB = pstcBkCfg->enBkCH2BStat;
    M0P_TIM3_MODE23->FLTR_f.BKP           = pstcBkCfg->enBrakePolarity;
    M0P_TIM3_MODE23->FLTR_f.FLTBK         = pstcBkCfg->enBrakeFlt;

    return enResult;
}

/**
 * @brief  Base Timer3 触发ADC控制(模式23)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_adc_trig_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_TrigADC_Cfg(stc_tim3_m23_adc_trig_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->ADTR_f.ADTE  = pstcCfg->bEnTrigADC;
    M0P_TIM3_MODE23->ADTR_f.UEVE  = pstcCfg->bEnUevTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMA0E = pstcCfg->bEnCH0ACmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMB0E = pstcCfg->bEnCH0BCmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMA1E = pstcCfg->bEnCH1ACmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMB1E = pstcCfg->bEnCH1BCmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMA2E = pstcCfg->bEnCH2ACmpTrigADC;
    M0P_TIM3_MODE23->ADTR_f.CMB2E = pstcCfg->bEnCH2BCmpTrigADC;
    M0P_TIM3_MODE23->CRCH3A_f.CM3AE = pstcCfg->bEnCH3ACmpTrigADC;
    M0P_TIM3_MODE23->CRCH3B_f.CM3BE = pstcCfg->bEnCH3BCmpTrigADC;
    
    return enResult;
}

/**
 * @brief  Timer3 死区功能(模式23)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_dt_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_DT_Cfg(stc_tim3_m23_dt_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->DTR_f.DTEN = pstcCfg->bEnDeadTime;
    M0P_TIM3_MODE23->DTR_f.DTR  = pstcCfg->u8DeadTimeValue;

    return enResult;
}

/**
 * @brief  Timer3 重复周期设置(模式23)
 * @param  [in] u8ValidPeriod 重复周期值
 * @param  [in] bOVMaskEn 上溢屏蔽使能/禁止
 * @param  [in] bUDMaskEn 下溢屏蔽使能/禁止
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_SetValidPeriod(uint8_t u8ValidPeriod, boolean_t bOVMaskEn, boolean_t bUDMaskEn)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->RCR_f.RCR = u8ValidPeriod;
    M0P_TIM3_MODE23->RCR_f.OV = bOVMaskEn;
    M0P_TIM3_MODE23->RCR_f.UND = bUDMaskEn;

    return enResult;
}

/**
 * @brief  Timer3 OCREF清除功能(模式23)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_OCREF_Clr_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_OCRefClr(stc_tim3_m23_OCREF_Clr_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.OCCS = pstcCfg->enOCRefClrSrcSel;
    M0P_TIM3_MODE23->M23CR_f.OCCE = pstcCfg->bVCClrEn;

    return enResult;
}

/**
 * @brief  Timer3 使能DMA传输(模式23)
 * @param  [in] pstcCfg 初始化配置结构体指针 @ref stc_tim3_m23_trig_dma_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_EnDMA(stc_tim3_m23_trig_dma_cfg_t *pstcCfg)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.UDE  = pstcCfg->bUevTrigDMA;
    M0P_TIM3_MODE23->M23CR_f.TDE  = pstcCfg->bTITrigDMA;
    M0P_TIM3_MODE23->CRCH0_f.CDEA = pstcCfg->bCmpA0TrigDMA;
    M0P_TIM3_MODE23->CRCH0_f.CDEB = pstcCfg->bCmpB0TrigDMA;
    M0P_TIM3_MODE23->CRCH1_f.CDEA = pstcCfg->bCmpA1TrigDMA;
    M0P_TIM3_MODE23->CRCH1_f.CDEB = pstcCfg->bCmpB1TrigDMA;
    M0P_TIM3_MODE23->CRCH2_f.CDEA = pstcCfg->bCmpA2TrigDMA;
    M0P_TIM3_MODE23->CRCH2_f.CDEB = pstcCfg->bCmpB2TrigDMA;
    M0P_TIM3_MODE23->CRCH3A_f.CDE = pstcCfg->bCmpA3TrigDMA;
    M0P_TIM3_MODE23->CRCH3B_f.CDE = pstcCfg->bCmpB3TrigDMA;
    M0P_TIM3_MODE23->MSCR_f.CCDS  = pstcCfg->enCmpUevTrigDMA;

    return enResult;
}

/**
 * @brief  Timer3 捕获比较A软件触发(模式23)
 * @param  [in] enTim3Chx Timer3通道(Tim3CH0, Tim3CH1, Tim3CH2) @ref en_tim3_channel_t
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_M23_EnSwTrigCapCmpA(en_tim3_channel_t enTim3Chx)
{
    en_result_t enResult = Ok;
    if (Tim3CH0 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH0_f.CCGA = TRUE;
    }
    else if (Tim3CH1 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH1_f.CCGA = TRUE;
    }
    else if (Tim3CH2 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH2_f.CCGA = TRUE;
    }
    else
    {
        enResult = Error;
    }
    return enResult;
}

/**
 * @brief  Timer3 捕获比较B软件触发(模式23)
 * @param  [in] enTim3Chx Timer3通道(Tim3CH0, Tim3CH1, Tim3CH2) @ref en_tim3_channel_t
 * @retval en_result_t
 *         - Ok: No error
 *         - Error: Non-specific error code
 */
en_result_t Tim3_M23_EnSwTrigCapCmpB(en_tim3_channel_t enTim3Chx)
{
    en_result_t enResult = Ok;
    if (Tim3CH0 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH0_f.CCGB = TRUE;
    }
    else if (Tim3CH1 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH1_f.CCGB = TRUE;
    }
    else if (Tim3CH2 == enTim3Chx)
    {
        M0P_TIM3_MODE23->CRCH2_f.CCGB = TRUE;
    }
    else
    {
        enResult = Error;
    }
    return enResult;
}

/**
 * @brief  Timer3 软件更新使能(模式23)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_EnSwUev(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.UG = TRUE;

    return enResult;
}

/**
 * @brief  Timer3 软件触发使能(模式23)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_EnSwTrig(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.TG = TRUE;

    return enResult;
}

/**
 * @brief  Timer3 软件刹车使能(模式23)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Tim3_M23_EnSwBk(void)
{
    en_result_t enResult = Ok;

    M0P_TIM3_MODE23->M23CR_f.BG = TRUE;

    return enResult;
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
