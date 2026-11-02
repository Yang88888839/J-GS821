/**
 *******************************************************************************
 * @file  vc.c
 * @brief This file provides - functions to manage the VC.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-04-23       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "vc.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_VC VC模块驱动库
 * @brief VC Driver Library VC模块驱动库
 * @{
 */

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/


/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup VC_Global_Functions VC全局函数定义
 * @{
 */

/**
 * @brief  配置VC中断触发方式.
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] ItType: 中断触发方式 @ref en_vc_irq_sel_t
 * @retval None.
 */
void Vc_CfgItType(M0P_VC_TypeDef *VCx, en_vc_irq_sel_t ItType)
{
    VCx->CR1 |= (uint32_t)ItType;
}

/**
 * @brief  清除VC中断触发方式.
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] ItType: 中断触发方式 @ref en_vc_irq_sel_t
 * @retval None.
 */
void Vc_ClrItType(M0P_VC_TypeDef *VCx, en_vc_irq_sel_t ItType)
{
    VCx->CR1 &= ~(uint32_t)ItType;
}


/**
 * @brief  VC 中断使能与禁止
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] NewStatus:
 *                      - TRUE: 使能中断
 *                      - FALSE: 禁用中断
 * @retval None.
 */
void  Vc_ItCfg(M0P_VC_TypeDef *VCx, boolean_t NewStatus)
{
    VCx->CR1_f.IE = NewStatus;
}


/**
 * @brief  VC 比较结果获取，包含中断标志位和滤波结果
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] Result: 所要读取的结果 @ref en_vc_ifr_t
 * @retval boolean_t:
 *          - TRUE: 中断标志置位，或者滤波结果为1
 *          - FALSE: 中断标志未置位，或者滤波结果为0
 */
boolean_t Vc_GetItStatus(M0P_VC_TypeDef *VCx, en_vc_ifr_t Result)
{
    return GetBit((uint32_t)(&(VCx->IFR)), Result);
}


/**
 * @brief  VC 清除中断标志位
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @retval None.
 */
void Vc_ClearItStatus(M0P_VC_TypeDef *VCx)
{
    VCx->IFR_f.INTF = 0u;
}


/**
 * @brief  VC 配置内部电阻分压相关的内容  VC_CR0.REF、VC_CR0.DIVEN、VC_CR0.DIV
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] pstcDacCfg: VC 内部电阻分压配置结构体 @ref stc_vc_div_cfg_t
 * @retval en_result_t:
 *          - Ok: 配置正确
 *          - ErrorInvalidParameter: 参数错误
 */
en_result_t Vc_DivInit(M0P_VC_TypeDef *VCx, stc_vc_div_cfg_t *pstcDacCfg)
{
    if (NULL == pstcDacCfg)
    {
        return ErrorInvalidParameter;
    }

    VCx->CR0_f.DIV_EN = pstcDacCfg->bDivEn;
    VCx->CR0_f.REF   = pstcDacCfg->enDivVref;

    if (pstcDacCfg->u8DivVal < 0x40u)
    {
        VCx->CR0_f.DIV = pstcDacCfg->u8DivVal;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 * @brief  VC 配置滤波功能相关的内容  VC_CR1.FLTMODE、VC_CR1.FLTCLK、VC_CR1.FLTTIME
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] pstcFltCfg: VC 滤波配置结构体 @ref stc_vc_flt_cfg_t
 * @retval en_result_t:
 *          - Ok: 配置正确
 *          - ErrorInvalidParameter: 参数错误
 */
en_result_t Vc_Fltcfg(M0P_VC_TypeDef *VCx, stc_vc_flt_cfg_t *pstcFltCfg)
{
    if (NULL == pstcFltCfg)
    {
        return ErrorInvalidParameter;
    }

    VCx->CR1_f.FLTMODE = pstcFltCfg->enFltMode;
    VCx->CR1_f.FLTCLK  = pstcFltCfg->enFltClk;
    VCx->CR1_f.FLTTIME = pstcFltCfg->enVcFilterTime;
    
    return Ok;
}

/**
 * @brief  VC 配置空白窗口功能相关的内容  VC_CR2.WINDOW、VC_CR2.BLANK
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] pstcFltCfg: VC 空白窗口配置结构体 @ref stc_vc_blank_cfg_t
 * @retval en_result_t:
 *          - Ok: 配置正确
 *          - ErrorInvalidParameter: 参数错误
 */
en_result_t Vc_Blankcfg(M0P_VC_TypeDef *VCx, stc_vc_blank_cfg_t *pstcFltCfg)
{
    if (NULL == pstcFltCfg)
    {
        return ErrorInvalidParameter;
    }

    VCx->CR2_f.WINDOW = pstcFltCfg->bBlanken;
    VCx->CR2_f.BLANK  = pstcFltCfg->enBlankSel;
    
    return Ok;
}

/**
 * @brief  VC 输出功能相关的内容
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] u32VcOutCfg: VC 输出配置参数 @ref en_vc_output_cfg_t
 * @retval en_result_t:
 *          - Ok: 配置正确
 *          - ErrorInvalidParameter: 参数错误
 */
en_result_t Vc_Outputcfg(M0P_VC_TypeDef *VCx, uint32_t u32VcOutCfg)
{
    VCx->CR2 |= u32VcOutCfg;
    
    return Ok;
}


/**
 * @brief  VC 通道初始化
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] pstcChannelCfg: VC通道配置结构体指针 @ref stc_vc_channel_cfg_t
 * @retval None.
 */
en_result_t Vc_Init(M0P_VC_TypeDef *VCx, stc_vc_channel_cfg_t *pstcChannelCfg)
{
    if (NULL == pstcChannelCfg)
    {
        return ErrorInvalidParameter;
    }
    
    VCx->CR2 = 0u;
    VCx->CR0_f.HYS = pstcChannelCfg->enVcCmpDly;
    VCx->CR0_f.BIAS = pstcChannelCfg->enVcBiasCurrent;
    VCx->CR1_f.FLTMODE = pstcChannelCfg->enFltMode;
    VCx->CR1_f.FLTCLK = pstcChannelCfg->enFltClk;
    VCx->CR1_f.FLTTIME = pstcChannelCfg->enVcFilterTime;
    VCx->CR1_f.PSEL = pstcChannelCfg->enVcInPin_P;
    VCx->CR1_f.NSEL = pstcChannelCfg->enVcInPin_N;
    VCx->CR2 |= pstcChannelCfg->u32VcOutCfg;
    VCx->CR2_f.WINDOW = pstcChannelCfg->bBlanken;
    VCx->CR2_f.BLANK = pstcChannelCfg->enBlankSel;
    
    return Ok;
}


/**
 * @brief  VC 通道使能/禁止
 * @param  [in] VCx: VC通道（M0P_VC0/M0P_VC1)
 * @param  [in] enChannel: VC通道号 @ref en_vc_channel_t
 * @param  [in] NewStatus:
 *                  - TRUE: 通道使能
 *                  - FALSE: 通道禁用
 * @retval None.
 */
void Vc_Cmd(M0P_VC_TypeDef *VCx, boolean_t NewStatus)
{
    VCx->CR1_f.EN = NewStatus;
}

/**
 * @brief  VC0 TRIM配置
 * @param  [in] u8Vc0Trim: VC0 Trim值 用户可以加载默认TRIIM值 @ref VC_VC0_TRIM, 也可以自行调整加载值
 * @retval None.
 */
void Vc_Vc0TrimCfg(uint8_t u8Vc0Trim)
{
    M0P_VCTRIM->VCTRIM_f.TRIM0 = u8Vc0Trim;
}

/**
 * @brief  VC1 TRIM配置
 * @param  [in] u8Vc1Trim: VC1 Trim值 用户可以加载默认TRIIM值 @ref VC_VC1_TRIM, 也可以自行调整加载值
 * @retval None.
 */
void Vc_Vc1TrimCfg(uint8_t u8Vc1Trim)
{
    M0P_VCTRIM->VCTRIM_f.TRIM1 = u8Vc1Trim;
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

