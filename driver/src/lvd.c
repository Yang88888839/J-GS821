/**
 *******************************************************************************
 * @file  lvd.c
 * @brief This file provides - functions to manage the LVD.
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
#include "lvd.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LVD LVD模块驱动库
 * @brief LVD Driver Library LVD模块驱动库
 * @{
 */

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
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
 * @defgroup LVD_Global_Functions LVD全局函数定义
 * @{
 */

/**
 * @brief  使能LVD中断.
 * @retval None.
 */
void Lvd_EnableIrq(void)
{
    M0P_LVD->CR_f.IE = TRUE;
}

/**
 * @brief  禁用LVD中断.
 * @retval None.
 */
void Lvd_DisableIrq(void)
{
    M0P_LVD->CR_f.IE = FALSE;
}

/**
 * @brief  LVD初始化.
 * @param  [in] pstcCfg: LVD配置指针 @ref stc_lvd_cfg_t
 * @retval None.
 */
void Lvd_Init(stc_lvd_cfg_t *pstcCfg)
{
    M0P_LVD->CR = 0;

    M0P_LVD->CR = (uint32_t)pstcCfg->enAct        |
                  (uint32_t)pstcCfg->enFltMode    |
                  (uint32_t)pstcCfg->enFilterTime |
                  (uint32_t)pstcCfg->enInputSrc   |
                  (uint32_t)pstcCfg->enIrqType    |
                  (uint32_t)pstcCfg->enThreshold;
}

/**
 * @brief  使能LVD.
 * @retval None.
 */
void Lvd_Enable(void)
{
    M0P_LVD->CR_f.LVDEN = 1u;
}

/**
 * @brief  禁用LVD.
 * @retval None.
 */
void Lvd_Disable(void)
{
    M0P_LVD->CR_f.LVDEN = 0u;
}

/**
 * @brief  获取LVD中断标志.
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t Lvd_GetIrqStat(void)
{
    return M0P_LVD->IFR_f.INTF;

}

/**
 * @brief  清除LVD中断标志.
 * @retval None.
 */
void Lvd_ClearIrq(void)
{
    M0P_LVD->IFR_f.INTF = 0u;
}

/**
 * @brief  获取LVD Filter结果.
 * @retval boolean_t:
 *           - TRUE: LVD Filter结果为1
 *           - FALSE: LVD Filter结果为0
 */
boolean_t Lvd_GetFilterResult(void)
{
    return (boolean_t)M0P_LVD->IFR_f.FILTER;
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

