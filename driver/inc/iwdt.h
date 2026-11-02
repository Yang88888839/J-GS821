/**
 ******************************************************************************
 * @file   wdt.h
 *
 * @brief This file contains all the functions prototypes of the IWDT driver
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

#ifndef __WDT_H__
#define __WDT_H__

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
 * @addtogroup DDL_IWDT IWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup _Global_Types IWDT全局类型定义
 * @{
 */

/**
 * @brief  IWDT 溢出后复位或中断配置数据类型定义
 */
typedef enum
{
    IwdtResetEn    = 0,          /*!< 复位使能 */
    IwdtIntEn      = 1u << 5u,   /*!< 中断使能 */
} en_iwdt_func_t;

/**
 * @brief  IWDT 中断配置数据类型定义
 */
typedef enum
{
    IwdtIrqDisable    = 0,        /*!< 中断禁止 */
    IwdtIrqEnanble    = 1u << 4u, /*!< 中断使能 */
} en_iwdt_Irq_t;

/**
 * @brief  IWDT 低功耗运行配置数据类型定义
 */
typedef enum
{
    IwdtDeepsleepRun    = 0,        /*!< 低功耗模式下运行 */
    IwdtDeepsleepStop   = 1u << 6u, /*!< 低功耗模式下停止 */
} en_iwdt_lpm_t;

/**
 * @brief  IWDT 时钟分频配置数据类型定义
 */
typedef enum
{
    IwdtClkDiv4    = 0,   /*!< IWDT 计数时钟4分频 */
    IwdtClkDiv8    = 1,   /*!< IWDT 计数时钟8分频 */
    IwdtClkDiv16   = 2,   /*!< IWDT 计数时钟16分频 */
    IwdtClkDiv32   = 3,   /*!< IWDT 计数时钟32分频 */
    IwdtClkDiv64   = 4,   /*!< IWDT 计数时钟64分频 */
    IwdtClkDiv128  = 5,   /*!< IWDT 计数时钟128分频 */
    IwdtClkDiv256  = 6,   /*!< IWDT 计数时钟256分频 */
    IwdtClkDiv512  = 7,   /*!< IWDT 计数时钟512分频 */
} en_iwdt_clk_div_t;

/**
 * @brief  IWDT 状态标志数据类型定义
 */
typedef enum
{
    IwdtFlagPrs    = 1u << 0u,   /*!< IWDT CR寄存器更新标志*/
    IwdtFlagArr    = 1u << 1u,   /*!< IWDT ARR寄存器更新标志 */
    IwdtFlagWinr   = 1u << 2u,   /*!< IWDT WINR寄存器更新标志 */
    IwdtFlagOv     = 1u << 3u,   /*!< IWDT 溢出标志 */
    IwdtFlagRun    = 1u << 4u,   /*!< IWDT 运行标志 */
} en_iwdt_flag_t;



/**
 * @brief  IWDT 初始化结构体定义
 */
typedef struct
{
    en_iwdt_func_t     enAction;      /*!< 看门狗休眠模式及溢出后动作配置 @ref IWDT_Action */
    en_iwdt_clk_div_t  enPrescaler;   /*!< 看门狗计数时钟(RC10K)的分频 @ref IWDT_RC32K_Prescaler */
    uint32_t           u32Window;     /*!< 看门狗窗口值配置,取值范围必须为：[0u ~ 0xFFFu] */
    uint32_t           u32ArrCounter; /*!< 看门狗重载计数值配置,取值范围必须为：[0u ~ 0xFFFu] */
                                      /*!< u32Window < u32ArrCounter时, IWDT工作于窗口看门狗模式 */
                                      /*!< u32Window ≥ u32ArrCounter时, IWDT工作于独立看门狗模式 */
    en_iwdt_Irq_t      enIrqCfg;
    en_iwdt_lpm_t      enLpmCfg;
} stc_iwdt_init_t;

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
 * @addtogroup WDT_Global_Functions IWDT全局函数定义
 * @{
 */

/* IWDT 初始化 */
en_result_t IWDT_Init(stc_iwdt_init_t *pstcCfg);

/* IWDT 启动函数 */
void IWDT_Start(void);
/* IWDT 停止函数 */
void IWDT_Stop(void);
/* IWDT 喂狗处理 */
void IWDT_Feed(void);
/* IWDT 低功耗Deepsleep运行配置 */
void IWDT_LpmCfg( boolean_t bVal);
/* IWDT 中断使能/禁止 */
void IWDT_IrqCfg( boolean_t bVal);
/* IWDT 中断标志清除 */
void IWDT_IrqClr(void);
/* IWDT 溢出时间设置 */
void IWDT_WriteWdtLoad(uint8_t u8LoadValue);
/* IWDT 中断状态获取 */
boolean_t IWDT_GetIrqStatus(void);
/* IWDT 运行状态获取 */
boolean_t IWDT_ReadwdtStatus(void);

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
