/**
 ******************************************************************************
 * @file   wwdt.h
 *
 * @brief This file contains all the functions prototypes of the WWDT driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-04-23       MADS            First version
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

#ifndef __WWDT_H__
#define __WWDT_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_WWDT WWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup WWDT_Global_Types WWDT全局类型定义
 * @{
 */

/**
 * @brief  wwdt计数时钟配置
 */
typedef enum
{
    WwdtPclkDiv4096    = 0u << 11u,
    WwdtPclkDiv8192    = 1u << 11u,
    WwdtPclkDiv16384   = 2u << 11u,
    WwdtPclkDiv32768   = 3u << 11u,
    WwdtPclkDiv65536   = 4u << 11u,
    WwdtPclkDiv131072  = 5u << 11u,
    WwdtPclkDiv262144  = 6u << 11u,
    WwdtPclkDiv524288  = 7u << 11u,
} en_wwdt_prs_t;

/**
 * @brief  预溢出中断使能控制
 */
typedef enum
{
    WwdtPreIntEnable    = 1u << 9u, /*!< 使能预溢出中断 */
    WwdtPreIntDisable   = 0u,      /*!< 禁止预溢出中断 */
} en_wwdt_pre_over_int_t;


/**
 * @brief  wwdt初始化配置
 */
typedef struct
{
    en_wwdt_prs_t enPrescaler;   /*!< 看门狗计数时钟(PCLK)的分频 WWDT_PCLK_Prescaler */
    uint32_t u32Window;      /*!< 看门狗窗口值配置,取值范围必须为：[0x40u ~ 0x7Fu] */
    uint32_t u32Counter;     /*!< 看门狗计数值配置,取值范围必须为：[0x40u ~ 0x7Fu] */
    /*!< u32Window < u32Counter时, WWDT工作于窗口看门狗模式 */
    /*!< u32Window ≥ u32Counter时, WWDT工作于独立看门狗模式 */
    en_wwdt_pre_over_int_t enPreOverInt;  /*!< 预溢出中断控制 WWDT_Pre_Over_Int */
} stc_wwdt_init_t;


/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup WWDT_Global_Functions WWDT全局函数定义
 * @{
 */

/* WWDT 初始化配置 */
en_result_t WWDT_Init(stc_wwdt_init_t *pstcWwdtInit);

/* WWDT 启动 */
void WWDT_Start(void);

/* 喂狗处理 */
void WWDT_Feed(uint32_t u32Cnt);

/* 获取当前计数值 */
uint32_t WWDT_GetCnt(void);

/* WWDT 溢出标志获取 */
boolean_t WWDT_GetPreOverFlag(void);

/* WWDT 溢出标志清除 */
void WWDT_ClearPreOverFlag(void);

/* 运行状态获取 */
boolean_t WWDT_GetRunFlag(void);
/* 执行WWDT复位 */
void WWDT_Reset(void);

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

#endif /* __WDT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/



