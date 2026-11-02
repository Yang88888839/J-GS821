/**
 *******************************************************************************
 * @file  reset.c
 * @brief This file provides - functions to manage the RESET.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "reset.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_RESET RESET模块驱动库
 * @brief Reset Driver Library RESET模块驱动库
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/


/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup RESET_Global_Functions RESET全局函数定义
 * @{
 */

/**
 * @brief 获取复位源类型.
 * @param [out]  enRstFlg  @ref en_reset_flag_t
 * @retval  TRUE or FALSE
 */
boolean_t Reset_GetFlag(en_reset_flag_t enRstFlg)
{
    if (M0P_RESET->RESET_FLAG & (uint32_t)enRstFlg)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief 清除复位源类型.
 * @param [in]  enRstFlg  @ref en_reset_flag_t
 * @retval  None
 */
void Reset_ClearFlag(en_reset_flag_t enRstFlg)
{
    M0P_RESET->RESET_FLAG &= ~(uint32_t)enRstFlg;
}

/**
 * @brief 清除所有复位源类型.
 * @retval  None
 */
void Reset_ClearFlagAll(void)
{
    M0P_RESET->RESET_FLAG = 0;
}

/**
 * @brief 所有模块进行一次复位.
 * @retval  None
 */
void Reset_RstPeripheralAll(void)
{
    M0P_RESET->PERI_RESET0 = 0u;
    M0P_RESET->PERI_RESET0 = 0xFFFFFFFFu;
    M0P_RESET->PERI_RESET1 = 0u;
    M0P_RESET->PERI_RESET1 = 0xFFFFFFFFu;
}

/**
 * @brief 对外设源0模块进行一次复位.
 * @param [in]  enPeri  @ref en_reset_peripheral0_t
 * @retval  None
 */
void Reset_RstPeripheral0(en_reset_peripheral0_t enPeri)
{
    M0P_RESET->PERI_RESET0 &= ~(uint32_t)enPeri;
    M0P_RESET->PERI_RESET0 |= (uint32_t)enPeri;
}

/**
 * @brief 对外设源1模块进行一次复位.
 * @param [in]  enPeri  @ref en_reset_peripheral1_t
 * @retval  None
 */
void Reset_RstPeripheral1(en_reset_peripheral1_t enPeri)
{
    M0P_RESET->PERI_RESET1 &= ~(uint32_t)enPeri;
    M0P_RESET->PERI_RESET1 |= (uint32_t)enPeri;
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

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


