/**
 *******************************************************************************
 * @file  wdt.c
 * @brief This file provides firmware functions to manage the IWDT.
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
#include "iwdt.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_IWDT IWDT模块驱动库
 * @brief IWDT Driver Library IWDT模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup IWDT_Local_Macros IWDT局部宏定义
 * @{
 */
/**
 * @defgroup IWDT_Key_Value_Define IWDT键值设置
 * @{
 */
#define IWDT_KEY_LOCK_RELEASE     (0x5555U) /*!< 解除写保护 */
#define IWDT_KEY_START_VALUE      (0xCCCCU) /*!< 启动IWDT计数器 */
#define IWDT_KEY_RELOAD_VALUE     (0xAAAAU) /*!< 重载IWDT计数器 */
#define IWDT_KEY_STOP_BYPASS_1234 (0x1234U) /*!< 依次写入0x1234和0x5678停止IWDT */
#define IWDT_KEY_STOP_BYPASS_5678 (0x5678U) /*!< 依次写入0x1234和0x5678停止IWDT */
/**
 * @}
 */

/**
 * @}
 */
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
 * @defgroup WDT_Global_Functions IWDT全局函数定义
 * @{
 */


/**
 * @brief  IWDT初始化函数
 * @param [in] enFunc @ref en_wdt_func_t
 * @param [in] enTime @ref en_wdt_time_t
 * @retval en_result_t
 *         - Ok: No error
*/
en_result_t IWDT_Init(stc_iwdt_init_t *pstcCfg)
{
    en_result_t enRet = Ok;
    
    M0P_IWDT->KR = IWDT_KEY_START_VALUE;
    M0P_IWDT->KR = IWDT_KEY_LOCK_RELEASE;
    
    while(READ_BIT(M0P_IWDT->SR, 0x7u))
    {
        ;
    }
    
    MODIFY_REG(M0P_IWDT->CR, 0x77u, (uint32_t)pstcCfg->enLpmCfg | (uint32_t)pstcCfg->enAction | (uint32_t)pstcCfg->enIrqCfg | (uint32_t)pstcCfg->enPrescaler);
    while(1u == M0P_IWDT->SR_f.CRF)
    {
        ;
    }
    
    M0P_IWDT->ARR = pstcCfg->u32ArrCounter;
    while(1u == M0P_IWDT->SR_f.ARRF)
    {
        ;
    }
    
    M0P_IWDT->WINR = pstcCfg->u32Window;
    while(1u == M0P_IWDT->SR_f.WINRF)
    {
        ;
    }
    
    M0P_IWDT->KR = IWDT_KEY_RELOAD_VALUE;
    while(0u == M0P_IWDT->SR_f.RUN)
    {
        ;
    }
    
    return enRet;
}
/**
 * @brief  IWDT启动函数
 * @retval None
*/
void IWDT_Start(void)
{
    M0P_IWDT->KR = IWDT_KEY_START_VALUE;
}

/**
 * @brief  IWDT 停止运行
 *
 * @retval None
 */
void IWDT_Stop(void)
{
    M0P_IWDT->KR = IWDT_KEY_STOP_BYPASS_1234;
    M0P_IWDT->KR = IWDT_KEY_STOP_BYPASS_5678;
}


/**
 * @brief  IWDT喂狗
 * @retval None
 */
void IWDT_Feed(void)
{
    M0P_IWDT->KR = IWDT_KEY_RELOAD_VALUE;
}

/**
 * @brief  IWDT低功耗Deepsleep下运行配置
 * @retval None
*/
void IWDT_LpmCfg( boolean_t bVal)
{
    M0P_IWDT->KR = IWDT_KEY_LOCK_RELEASE;
    M0P_IWDT->CR_f.PAUSE = bVal;
    while(1u == M0P_IWDT->SR_f.CRF)
    {
        ;
    }
    M0P_IWDT->KR = IWDT_KEY_RELOAD_VALUE;
}

/**
 * @brief  IWDT中断标志清除
 * @retval None
*/
void IWDT_IrqClr(void)
{
    M0P_IWDT->SR_f.OV = 0u;
}

/**
 * @brief  IWDT中断使能/禁止
 * @retval None
*/
void IWDT_IrqCfg( boolean_t bVal)
{
    M0P_IWDT->KR = IWDT_KEY_LOCK_RELEASE;
    M0P_IWDT->CR_f.IE = bVal;
    while(1u == M0P_IWDT->SR_f.CRF)
    {
        ;
    }
    M0P_IWDT->KR = IWDT_KEY_RELOAD_VALUE;
}


/**
 * @brief  IWDT读取当前运行状态
 * @retval boolean_t: 状态值
*/
boolean_t IWDT_ReadwdtStatus(void)
{
    if (1u == M0P_IWDT->SR_f.RUN)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief IWDT 中断状态标记获取
 * @retval boolean_t: 中断状态
*/
boolean_t IWDT_GetIrqStatus(void)
{
    if (1u == M0P_IWDT->SR_f.OV)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
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
