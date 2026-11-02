/**
 *******************************************************************************
 * @file  ram.c
 * @brief This file provides - functions to manage the RAM.
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
#include "ram.h"
/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_RAM RAM子模块驱动库
 * @brief RAM Driver Library RAM子模块驱动库
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
 * @defgroup RAM_Global_Functions RAM全局函数定义
 * @{
 */

/**
 * @brief  Ram奇偶校验出错地址获取.
 * @retval uint32_t: 出错地址
 */
uint32_t Ram_ErrAddrGet(void)
{
    return M0P_RAM->ERRADDR;
}


/**
 * @brief  Ram中断标志获取.
 * @retval boolean_t: 中标标志
 *           - TRUE: 中断位置起
 *           - FALSE: 中断位未置起
 */
boolean_t Ram_GetIntFlag(void)
{
    if (M0P_RAM->IFR & 0x1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


/**
 * @brief  Ram中断标志清除.
 * @retval None
 */
void Ram_ClearIntFlag(void)
{
    M0P_RAM->ICLR = 0u;
}

/**
 * @brief  Ram中断使能.
 * @retval None
 */
void Ram_EnableIrq(void)
{
    M0P_RAM->CR |= 0x2u;
}


/**
 * @brief  ram中断禁止.
 * @retval None
 */
void Ram_DisableIrq(void)
{
    M0P_RAM->CR &= 0x1;
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
 *****************************************************************************/
