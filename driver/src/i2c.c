/**
 *******************************************************************************
 * @file  i2c.c
 * @brief This file provides firmware functions to manage the I2C.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-11-29       MADS            First version
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
#include "i2c.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_I2C I2C模块驱动库
 * @brief I2C Driver Library I2C模块驱动库
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')         *
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
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
 * @defgroup I2C_Global_Functions I2C全局函数定义
 * @{
 */
 
/**
 * @brief  I2C设置波特率配置寄存器
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @param  [in] u8Brr:             波特率配置值
 * @retval en_result_t:            波特率设置状态
 *         - Error:        配置失败
 *         - Ok:           配置成功
 */
en_result_t I2C_SetBaud(M0P_I2C_TypeDef *I2Cx, uint8_t u8Brr)
{
    en_result_t enRet = Error;

    I2Cx->TM = u8Brr;

    enRet = Ok;
    return enRet;
}

/**
 * @brief  I2C功能开启函数
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @param  [in] enFunc:            功能参数                  @ref en_i2c_func_t
 * @retval en_result_t:            功能开启状态
 *         - Error:        设置失败
 *         - Ok:           设置成功
 */
en_result_t I2C_SetFunc(M0P_I2C_TypeDef *I2Cx, en_i2c_func_t enFunc)
{
    en_result_t enRet = Error;

    SetBit((uint32_t)&I2Cx->CR, enFunc, TRUE);

    enRet = Ok;
    return enRet;
}


/**
 * @brief  I2C功能禁止函数
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @param  [in] enFunc:            功能参数                  @ref en_i2c_func_t
 * @retval en_result_t:            功能清除状态
 *         - Error:        禁止失败
 *         - Ok:           禁止成功
 */
en_result_t I2C_ClearFunc(M0P_I2C_TypeDef *I2Cx, en_i2c_func_t enFunc)
{
    en_result_t enRet = Error;

    SetBit((uint32_t)&I2Cx->CR, enFunc, FALSE);

    enRet = Ok;
    return enRet;
}

/**
 * @brief  I2C获取中断标记函数
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @retval boolean_t:              中断状态
 *         - FALSE:       未发生中断
 *         - TRUE:        发生中断
 */
boolean_t I2C_GetIrq(M0P_I2C_TypeDef *I2Cx)
{
    if (I2Cx->CR & 0x8)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


/**
 * @brief  I2C清除中断标记函数
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @retval en_result_t:            中断清除状态
 *         - Error:       清除失败
 *         - Ok:          清除成功
 */
en_result_t I2C_ClearIrq(M0P_I2C_TypeDef *I2Cx)
{
    en_result_t enRet = Error;

    I2Cx->CR &= ~0x8u;

    enRet = Ok;
    return enRet;
}


/**
 * @brief  I2C获取相关状态
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @retval uint8_t:                I2C状态码
 */
uint8_t I2C_GetState(M0P_I2C_TypeDef *I2Cx)
{
    uint8_t u8State = 0;

    u8State = I2Cx->STAT;

    return u8State;
}


/**
 * @brief  I2C字节数据写函数
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @param  [in] u8Data:            写入字节
 * @retval en_result_t:            写字节状态
 *         - Error:       写入失败
 *         - Ok:          写入成功
 */
en_result_t I2C_WriteByte(M0P_I2C_TypeDef *I2Cx, uint8_t u8Data)
{
    en_result_t enRet = Error;

    I2Cx->DATA = u8Data;

    enRet = Ok;
    return enRet;
}


/**
 * @brief  I2C字节数据读函数
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @retval u8Data:                 读取字节
 */
uint8_t I2C_ReadByte(M0P_I2C_TypeDef *I2Cx)
{
    uint8_t u8Data = 0;

    u8Data = I2Cx->DATA;

    return u8Data;
}


/**
 * @brief  I2C从机地址匹配状态读取函数
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @retval uint8_t:                I2C从机地址匹配状态
 */
uint8_t I2C_GetAddMatchState(M0P_I2C_TypeDef *I2Cx)
{
    uint8_t u8State = 0;

    u8State = I2Cx->MATCH;

    return u8State;
}


/**
 * @brief  I2C模块初始化
 * @param  [in] I2Cx:              I2C类型定义               @ref M0P_I2C_TypeDef
 * @param  [in] pstcI2CCfg:        I2C初始化配置结构体       @ref stc_i2c_cfg_t
 * @retval en_result_t:            初始化状态
 *         - Error:       初始化失败
 *         - Ok:          初始化成功
 */
en_result_t I2C_Init(M0P_I2C_TypeDef *I2Cx, stc_i2c_cfg_t *pstcI2CCfg)
{
    en_result_t enRet = Error;
    uint8_t     u8Tm;

    if (M0P_I2C0 == I2Cx)
    {
        M0P_RESET->PERI_RESET0 &= ~(uint32_t)0x10u;
        M0P_RESET->PERI_RESET0 |= (uint32_t)0x10u;
    }
    else
    {
        M0P_RESET->PERI_RESET0 &= ~(uint32_t)0x20u;
        M0P_RESET->PERI_RESET0 |= (uint32_t)0x20u;
    }

    I2Cx->CR = 0;
    I2Cx->CR = pstcI2CCfg->enMode;

    if ((pstcI2CCfg->u32Baud << 4) > pstcI2CCfg->u32Pclk)
    {
        return Error;
    }

    if (I2cMasterMode == pstcI2CCfg->enMode)
    {
        I2Cx->TMRUN = TRUE;

        u8Tm = ((pstcI2CCfg->u32Pclk / pstcI2CCfg->u32Baud) >> 3) - 1;  /* Fsck = Fpclk/8*(Tm+1) */
        if (9 > u8Tm)
        {
            I2C_SetFunc(I2Cx, I2cHlm_En);
        }
        enRet = I2C_SetBaud(I2Cx, u8Tm);
    }
    else
    {
        I2Cx->TMRUN = FALSE;
        pstcI2CCfg->u8SlaveAddr0 = (uint8_t)(((uint32_t)pstcI2CCfg->u8SlaveAddr0 << 1u) | (pstcI2CCfg->bGc));
        I2Cx->ADDR0 = pstcI2CCfg->u8SlaveAddr0;
        I2Cx->ADDR1 = (uint8_t)((uint32_t)pstcI2CCfg->u8SlaveAddr1 << 1u);
        I2Cx->ADDR2 = (uint8_t)((uint32_t)pstcI2CCfg->u8SlaveAddr2 << 1u);
    }

    return enRet;
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
