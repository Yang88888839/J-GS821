/**
 *******************************************************************************
 * @file  trng.c
 * @brief This file provides - functions to manage the TRNG.
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
#include "trng.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_TRNG TRNG模块驱动库
 * @brief TRNG Driver Library TRNG模块驱动库
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
 * @defgroup TRNG_Global_Functions TRNG全局函数定义
 * @{
 */

/**
 * @brief  随机数初始化(上电第一次生成随机数)
 * @retval boolean_t
 *         - Ok: No error
 */
en_result_t Trng_Init(void)
{
    /* 生成64bits随机数(上电第一次) */
    M0P_TRNG->CR_f.TRNGCIR_EN = 1;
    /* 模式配置0 */
    M0P_TRNG->MODE_f.LOAD    = 1;
    M0P_TRNG->MODE_f.FDBK    = 1;
    M0P_TRNG->MODE_f.CNT     = 6;
    /* 生成随机数0 */
    M0P_TRNG->CR_f.TRNG_RUN  = 1;
    while (M0P_TRNG->CR_f.TRNG_RUN)
    {
        ;
    }

    /* 模式配置1 */
    M0P_TRNG->MODE_f.LOAD    = 0;
    M0P_TRNG->MODE_f.FDBK    = 0;
    M0P_TRNG->MODE_f.CNT     = 4;
    /* 生成随机数1 */
    M0P_TRNG->CR_f.TRNG_RUN  = 1;
    while (M0P_TRNG->CR_f.TRNG_RUN)
    {
        ;
    }

    /* 关闭随机源电路，节省功耗 */
    M0P_TRNG->CR_f.TRNGCIR_EN = 0;

    return Ok;
}

/**
 * @brief  生成随机数(非上电第一次生成随机数)
 * @retval en_result_t
 *         - Ok: No error
 */
en_result_t Trng_Generate(void)
{
    /* 生成64bits随机数(非上电第一次生成) */
    M0P_TRNG->CR_f.TRNGCIR_EN = 1;

    /* 模式配置0 */
    M0P_TRNG->MODE_f.LOAD    = 0;
    M0P_TRNG->MODE_f.FDBK    = 1;
    M0P_TRNG->MODE_f.CNT     = 6;
    /* 生成随机数0 */
    M0P_TRNG->CR_f.TRNG_RUN  = 1;
    while (M0P_TRNG->CR_f.TRNG_RUN)
    {
        ;
    }

    /* 模式配置1 */
    M0P_TRNG->MODE_f.FDBK    = 0;
    M0P_TRNG->MODE_f.CNT     = 4;
    M0P_TRNG->MODE_f.CNT     = 4;
    /* 生成随机数1 */
    M0P_TRNG->CR_f.TRNG_RUN  = 1;
    while (M0P_TRNG->CR_f.TRNG_RUN)
    {
        ;
    }

    /* 关闭随机源电路，节省功耗 */
    M0P_TRNG->CR_f.TRNGCIR_EN = 0;

    return Ok;
}

/**
 * @brief  随机数获取
 * @retval 低32位随机数
 */
uint32_t Trng_GetData0(void)
{
    return M0P_TRNG->DATA0;
}

/**
 * @brief  随机数获取
 * @retval 高32位随机数
 */
uint32_t Trng_GetData1(void)
{
    return M0P_TRNG->DATA1;
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
