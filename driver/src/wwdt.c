/**
 *******************************************************************************
 * @file  wdt.c
 * @brief This file provides firmware functions to manage the WWDT.
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
#include "wwdt.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_WWDT WWDT模块驱动库
 * @brief WWDT Driver Library WWDT模块驱动库
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
* @defgroup WWDT_Global_Functions WWDT全局函数定义
* @{
*/

/**
 * @brief  WDT初始化函数
 * @param [in] pstcWwdtInit @ref stc_wwdt_init_t
 * @retval Ok
*/
en_result_t WWDT_Init(stc_wwdt_init_t *pstcWwdtInit)
{
    M0P_WWDT->CR1 =  (uint32_t)pstcWwdtInit->enPrescaler  | \
                     (uint32_t)pstcWwdtInit->enPreOverInt | \
                     pstcWwdtInit->u32Window;

    M0P_WWDT->CR0 =  pstcWwdtInit->u32Counter;

    return Ok;
}

/**
 * @brief  WWDT启动运行函数
 * @retval None
*/
void WWDT_Start(void)
{
    M0P_WWDT->CR0_f.EN = 0x01u;
}

/**
 * @brief  WWDT 喂狗
 * @param [in] u32Cnt: 计数值
 * @retval None
*/
void WWDT_Feed(uint32_t u32Cnt)
{
    M0P_WWDT->CR0_f.WCNT = u32Cnt;
}

/**
 * @brief  WWDT预溢出标志清除
 * @retval None
*/
void WWDT_ClearPreOverFlag(void)
{
    M0P_WWDT->SR = 0u;
}

/**
 * @brief  WWDT预溢出标志获取
 * @retval boolean_t: TRUE or FALSE
*/
boolean_t WWDT_GetPreOverFlag(void)
{
    return ((0x01U == M0P_WWDT->SR_f.POV) ? TRUE : FALSE);
}

/**
 * @brief  WWDT 获取当前运行状态
 * @retval boolean_t: TRUE or FALSE
*/
boolean_t WWDT_GetRunFlag(void)
{
    return ((0x01U == M0P_WWDT->CR0_f.EN) ? TRUE : FALSE);
}

/**
 * @brief  WWDT 获取当前计数值
 * @retval uint32_t: 32位计数值
*/
uint32_t WWDT_GetCnt(void)
{

    uint32_t u32Count;

    u32Count = M0P_WWDT->CR0_f.WCNT;

    return u32Count;
}

/**
* @brief  WWDT 直接复位
* @retval None
*/
void WWDT_Reset(void)
{
    M0P_WWDT->CR0 = 0u;
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
