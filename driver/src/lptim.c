/**
 *******************************************************************************
 * @file  lptim.c
 * @brief This file provides firmware functions to manage the LPTIM.
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
#include "lptim.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LPTIM LPTIM模块驱动库
 * @brief LPTIM Driver Library LPTIM模块驱动库
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
 * @defgroup LPTIM_Global_Functions LPTIM全局函数定义
 * @{
 */

/**
 * @brief  定时器LPTIMx中断使能控制
 * @param  [in] Lptimx LPTIM0 或LPTIM1 @ref M0P_LPTIMER_TypeDef
 * @param  [in] NewStatus TRUE:使能, FALSE:禁止 @ref boolean_t
 * @retval None
 */
void Lptim_ConfIt(M0P_LPTIMER_TypeDef *Lptimx, boolean_t NewStatus)
{
    Lptimx->CR_f.IE = NewStatus;
}

/**
 * @brief  定时器LPTIMx的启动/停止控制
 * @param  [in] Lptimx LPTIM0 或LPTIM1 @ref M0P_LPTIMER_TypeDef*
 * @param  [in] NewStatus TRUE:启动, FALSE:停止 @ref boolean_t
 * @retval None
 */
en_result_t Lptim_Cmd(M0P_LPTIMER_TypeDef *Lptimx, boolean_t NewStatus)
{
    uint16_t u16TimeOut;
    
    if(NewStatus == FALSE)
    {
        Lptimx->CR_f.TR = FALSE;
    }
    else
    {
        u16TimeOut = 1000u;
        while (1u == Lptimx->CR_f.SYNCCOUNTRST) 
        {
            if (0u == u16TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        
        Lptimx->CR_f.TR = TRUE;
    }
    
    return Ok;
}

/**
 * @brief  定时器LPTIMx的中断标志位获取
 * @param  [in] Lptimx LPTIM0 或LPTIM1 @ref M0P_LPTIMER_TypeDef*
 * @retval boolean_t
 *         - TRUE: 发生中断
 *         - FALSE: 没有发生中断
 */
boolean_t Lptim_GetItStatus(M0P_LPTIMER_TypeDef *Lptimx)
{
    return GetBit((uint32_t)(&(Lptimx->IFR)), 0);
}

/**
 * @brief  定时器LPTIMx的中断标志位清除
 * @param  [in] Lptimx LPTIM0 或LPTIM1 @ref M0P_LPTIMER_TypeDef
 * @retval None
 */
void Lptim_ClrItStatus(M0P_LPTIMER_TypeDef *Lptimx)
{
    Lptimx->ICLR_f.OV = 0u;
}

/**
 * @brief  定时器LPTIMx的重载值设置
 * @param  [in] Lptimx LPTIM0 或LPTIM1 @ref M0P_LPTIMER_TypeDef*
 * @param  [in] u16Arr Arr重载值
 * @retval en_result_t
 *         - Ok: No error
 *         - ErrorTimeout: Time Out error occurred
 */
en_result_t Lptim_SetArr(M0P_LPTIMER_TypeDef *Lptimx, uint16_t u16Arr)
{
    uint16_t u16TimeOut;
    
    u16TimeOut = 1000u;
    while (0u == Lptimx->CR_f.WT_FLAG) 
    {
        if (0u == u16TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    Lptimx->ARR = u16Arr;
    
    return Ok;
}

/**
 * @brief  定时器LPTIMx的比较值设置
 * @param  [in] Lptimx LPTIM0 或LPTIM1 @ref M0P_LPTIMER_TypeDef*
 * @param  [in] u16Arr Arr重载值
 * @retval en_result_t
 *         - Ok: No error
 *         - ErrorTimeout: Time Out error occurred
 */
en_result_t Lptim_SetCmp(M0P_LPTIMER_TypeDef *Lptimx, uint16_t u16Cmp)
{
    uint16_t u16TimeOut;
    
    u16TimeOut = 1000u;
    while (0u == Lptimx->CR_f.WT_FLAG) 
    {
        if (0u == u16TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    Lptimx->CMP = u16Cmp;
    
    return Ok;
}

/**
 * @brief  定时器LPTIMx的计数器同步复位
 * @param  [in] Lptimx LPTIM0 或LPTIM1 @ref M0P_LPTIMER_TypeDef*
 * @retval en_result_t
 *         - Ok: No error
 *         - ErrorTimeout: Time Out error occurred
 */
en_result_t Lptim_SyncCntRst(M0P_LPTIMER_TypeDef *Lptimx)
{
    uint16_t u16TimeOut;
    
    Lptimx->CR_f.SYNCCOUNTRST = 1u;
    
    u16TimeOut = 1000u;
    while (1u == Lptimx->CR_f.SYNCCOUNTRST) 
    {
        if (0u == u16TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    return Ok;
}

/**
 * @brief  定时器LPTIMx的初始化配置
 * @param  [in] Lptimx LPTIM0 或LPTIM1 @ref M0P_LPTIMER_TypeDef
 * @param  [in] InitStruct 初始化LPTIMx的结构体 @ref stc_lptim_cfg_t
 * @retval en_result_t
 *         - Ok: No error
 *         - ErrorTimeout: Time Out error occurred
 */
en_result_t Lptim_Init(M0P_LPTIMER_TypeDef *Lptimx, stc_lptim_cfg_t *InitStruct)
{
    uint16_t u16TimeOut;
    
    Lptimx->CR_f.PRS     = InitStruct->enPrs;
    Lptimx->CR_f.TCK_SEL = InitStruct->enTcksel;
    Lptimx->CR_f.GATE_P  = InitStruct->enGatep;
    Lptimx->CR_f.GATE    = InitStruct->enGate;
    Lptimx->CR_f.TOG_EN  = InitStruct->enTogen;
    Lptimx->CR_f.CT      = InitStruct->enCt;
    Lptimx->CR_f.MD      = InitStruct->enMd;
    
    u16TimeOut = 1000u;
    while (0u == Lptimx->CR_f.WT_FLAG) 
    {
        if (0u == u16TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    Lptimx->ARR_f.ARR = InitStruct->u16Arr;
    Lptimx->CMP_f.CMP = InitStruct->u16Cmp;
    
    return Ok;
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
