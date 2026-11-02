/**
 *******************************************************************************
 * @file  ctrim.c
 * @brief This file provides firmware functions to manage the CTRIM.
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
#include "ctrim.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CTRIM CTRIM模块驱动库
 * @brief CTRIM Driver Library CTRIM模块驱动库
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
 * @defgroup CTRIM_Global_Functions CTRIM全局函数定义
 * @{
 */

/**
 * @brief  CTRIM 时钟校准初始化配置
 * @param  [in] pstcInitCfg: Trim时钟校准结构体     @ref stc_ctrim_cali_init_t
 * @retval en_result_t
 *         - Ok                    OK
 *         - ErrorInvalidParameter Invalid parameter
 */
en_result_t CTRIM_CaliInit(stc_ctrim_cali_init_t *pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);

    if ((pstcInitCfg->enMode == 2u) || (pstcInitCfg->enRefClockDiv == 0u))
    {
        return ErrorInvalidParameter;
    }
    
    M0P_CTRIM->CR0_f.STEP = pstcInitCfg->enInitialStep;
    M0P_CTRIM->CR0_f.ETRFLT = pstcInitCfg->enEtrFilter;
    M0P_CTRIM->CR0_f.SRC = pstcInitCfg->enAccurateClock;
    
    M0P_CTRIM->CR1_f.MD = pstcInitCfg->enMode;
    M0P_CTRIM->CR1_f.AUTO = pstcInitCfg->enAutoTrim;
    M0P_CTRIM->CR1_f.PRS = pstcInitCfg->enRefClockDiv;
    M0P_CTRIM->CR1_f.OST = pstcInitCfg->enOneShot;

    M0P_CTRIM->ARR = pstcInitCfg->u16ReloadVal;

    M0P_CTRIM->FLIM = pstcInitCfg->u16CountErrorLimit;

    return Ok;
}

/**
 * @brief  CTRIM 时钟功能初始化配置
 * @param  [in] pstcInitCfg: Trim时钟初始化结构体     @ref stc_ctrim_timer_init_t
 * @retval en_result_t
 *         - Ok                    OK
 *         - ErrorInvalidParameter Invalid parameter
 */
en_result_t CTRIM_TimerInit(stc_ctrim_timer_init_t *pstcInitCfg)
{
    ASSERT(NULL != pstcInitCfg);

    if (pstcInitCfg->enClockDiv == 0u)
    {
        return ErrorInvalidParameter;
    }
    
    M0P_CTRIM->CR0_f.ETRFLT = pstcInitCfg->enEtrFilter;
    M0P_CTRIM->CR0_f.SRC = pstcInitCfg->enClock;
    
    M0P_CTRIM->CR1_f.PRS = pstcInitCfg->enClockDiv;
    M0P_CTRIM->CR1_f.MD = CtrimModeTimer;

    M0P_CTRIM->ARR = pstcInitCfg->u16ReloadVal;

    return Ok;
}

/**
 * @brief  CTRIM 获取误差计数器计数值
 * @retval uint32_t：        计数器计数值
 */
uint32_t CTRIM_GetCounter(void)
{
    return (uint32_t)(M0P_CTRIM->CNT);
}

/**
 * @brief  CTRIM 设定自动装载寄存器的值
 * @param  [in] u32AutoReload: 重载值 取值范围 0x0 ~ 0xFFFF
 * @retval None
 */
void CTRIM_SetAutoReload(uint32_t u32AutoReload)
{
    M0P_CTRIM->ARR = u32AutoReload;
}

/**
 * @brief  CTRIM 获取自动装载寄存器的值
 * @retval uint32_t：          自动装载寄存器的值
 */
uint32_t CTRIM_GetAutoReload(void)
{
    return (uint32_t)(M0P_CTRIM->ARR);
}

/**
 * @brief  CTRIM RCH/RCL TRIM初始步进量配置，必须在CTRIM模块未使能时才可以配置
 * @param  [in] enTrimStep:   初始步进量
 * @retval None
 */
void CTRIM_SetInitialStep(en_ctrim_step_t enTrimStep)
{
    M0P_CTRIM->CR0_f.STEP = enTrimStep;
}

/**
 * @brief  CTRIM 外部管脚输入时钟滤波配置，必须在CTRIM模块未使能时才可以配置
 * @param  [in] enExClockFilter:  外部输入时钟滤波配置
 * @retval None
 */
void CTRIM_SetEtrClockFilter(en_ctrim_etrflt_t enExClockFilter)
{
    M0P_CTRIM->CR0_f.ETRFLT = enExClockFilter;
}

/**
 * @brief  CTRIM 精确时钟源选择，必须在CTRIM模块未使能时才可以配置
 * @param  [in] enClockSource:    时钟源选择
 * @retval None
 */
void CTRIM_SetAccurateClock(en_ctrim_src_t enClockSource)
{
    M0P_CTRIM->CR0_f.SRC = enClockSource;
}

/**
 * @brief  CTRIM 工作模式配置
 * @param  [in] enMode:       工作模式选择
 * @retval None
 */
void CTRIM_SetMode(en_ctrim_md_t enMode)
{
    M0P_CTRIM->CR1_f.MD  = enMode;
}

/**
 * @brief  CTRIM 参考时钟预分频配置,M0P_CTRIM->CR1.PRS不能配置为0值，否则CTRIM不能正常工作
 * @param  [in] enRefClockDiv: 参考时钟预分频配置
 * @retval None
 */
void CTRIM_SetRefClockDiv(en_ctrim_prs_t enRefClockDiv)
{
    M0P_CTRIM->CR1_f.PRS = enRefClockDiv;
}

/**
 * @brief  CTRIM 校准模式配置
 * @param  [in] enOneShotMode: 校准模式配置
 * @retval None
 */
void CTRIM_SetOneShot(en_ctrim_ost_t enOneShotMode)
{
    M0P_CTRIM->CR1_f.OST = enOneShotMode;
}

/**
 * @brief  CTRIM 获取误差计数器计数方向
 * @retval uint32_t: 误差计数器计数方向
 *         - 0u  递增计数，RCH输出频率高于目标频率，或RCL输出频率低于目标频率
 *         - 1u  递减计数，RCH输出频率低于目标频率，或RCL输出频率高于目标频率
 */
uint32_t CTRIM_GetARRCoutDir(void)
{
    return (uint32_t)(M0P_CTRIM->ISR_f.DIR);
}

/**
 * @brief  CTRIM 获取TrimCode值，及trim结束后的trim校准值
 * @retval uint16_t: TrimCode值
 */
uint16_t CTRIM_GetTrimCode(void)
{
    return (uint16_t)(M0P_CTRIM->TVAL);
}

/**
 * @brief  CTRIM 获取计数误差捕获值，校准结束时，误差计数器里面的值
 * @retval uint16_t: 计数误差捕获值
 */
uint16_t CTRIM_GetCountErrorCapture(void)
{
    return (uint16_t)(M0P_CTRIM->FCAP);
}

/**
 * @brief  CTRIM 设置误差允许值， 一个周期计数结束，误差计数器里的值小于当前设定值，则认为校验成功

 * @param  [in] u16ErrLimit:     误差上限值 取值范围 0x0 ~ 0xFFF
 * @retval None
 */
void CTRIM_SetCountErrorLimit(uint16_t u16ErrLimit)
{
    M0P_CTRIM->FLIM_f.FLIM = u16ErrLimit;
}

/**
 * @brief  CTRIM 获取误差允许值， 一个周期计数结束，误差计数器里的值小于当前设定值，则认为校验成功
 * @retval uint16_t：  误差上限值
 */
uint16_t CTRIM_GetCountErrorLimit(void)
{
    return (uint16_t)(M0P_CTRIM->FLIM);
}

/**
 * @brief  CTRIM 开启模块
 * @retval None
 */
void CTRIM_Enable(void)
{
    M0P_CTRIM->CR1_f.EN = 1u;
}

/**
 * @brief  CTRIM 禁止模块
 * @retval None
 */
void CTRIM_Disable(void)
{
    M0P_CTRIM->CR1_f.EN = 0u;
}

/**
 * @brief  CTRIM 检查模块是否已开启
 * @retval boolean_t: 
 *         - TRUE： 已开启
 *         - FALSE：未开启
 */
boolean_t CTRIM_IsEnable(void)
{
    return (M0P_CTRIM->CR1_f.EN == 1u) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 中断使能

 * @param  [in] enIT:  中断类型定义
 * @retval None
 */
void CTRIM_EnableIT(en_ctrim_flag_it_t enIT)
{
    SET_BIT(M0P_CTRIM->IER, enIT);
}

/**
 * @brief  CTRIM 中断禁止

 * @param  [in] enIT:  中断类型定义
 * @retval None
 */
void CTRIM_DisableIT(en_ctrim_flag_it_t enIT)
{
    CLEAR_BIT(M0P_CTRIM->IER, (uint32_t)enIT);
}

/**
 * @brief  CTRIM 检查中断是否开启

 * @param  [in] enIT:  中断类型定义
 * @retval boolean_t: 
 *         - TRUE： 已使能中断产生标志
 *         - FALSE：未使能中断
 */
boolean_t CTRIM_IsEnableIT(en_ctrim_flag_it_t enIT)
{
    return (READ_BIT(M0P_CTRIM->IER, enIT) == enIT) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 获取中断标志

 * @param  [in] enITFlag:  中断标记
 * @retval boolean_t: 
 *         - TRUE： 中断产生标志
 *         - FALSE：未产生中断
 */
boolean_t CTRIM_IsActiveFlag(en_ctrim_flag_it_t enITFlag)
{
    return (READ_BIT(M0P_CTRIM->ISR, enITFlag) == enITFlag) ? TRUE : FALSE;
}

/**
 * @brief  CTRIM 清除中断标志

 * @param  [in] enITFlag: 中断标记
 * @retval None
 */
void CTRIM_ClearFlag(en_ctrim_flag_it_t enITFlag)
{
    CLEAR_BIT(M0P_CTRIM->ICR, (uint32_t)enITFlag);
}

/**
 * @brief  CTRIM 清除所有标志

 * @retval None
 */
void CTRIM_ClearFlag_ALL(void)
{
    M0P_CTRIM->ICR = 0u;
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
