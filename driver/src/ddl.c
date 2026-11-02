/**
 *******************************************************************************
 * @file  ddl.c
 * @brief This file provides - functions to manage the DDL.
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

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_DDL DDL模块驱动库
 * @brief DDL Common Functions共通API
 * @{
 */

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/
/**
 * @defgroup DDL_Local_Macros DDL局部宏定义
 * @{
 */
#ifndef __DEBUG
    #define __DEBUG
    //#define __CC_ARM
#endif
/**
 * @}
 */
/******************************************************************************/
/* Global variable definitions (declared in header file with 'extern')        */
/******************************************************************************/

/******************************************************************************/
/* Local type definitions ('typedef')                                         */
/******************************************************************************/

/******************************************************************************/
/* Local variable definitions ('static')                                      */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Function implementation - global ('extern') and local ('static')           */
/******************************************************************************/


/**
 * @defgroup DDL_Global_Functions DDL全局函数定义
 * @{
 */

/**
 * @brief  log2 数学函数
 * @param  [in] u32Val: 32位无符号输入值
 * @retval uint32_t: 32位无符号结果
 */
uint32_t Log2(uint32_t u32Val)
{
    uint32_t u32V1 = 0;

    if (0u == u32Val)
    {
        return 0;
    }

    while (u32Val > 1u)
    {
        u32V1++;
        u32Val /= 2;
    }

    return u32V1;
}


/**
 * @brief  ddl memory 清零函数
 * @param  [in] pu8Address: 起始地址
 * @param  [in] u32Count: 清零长度，以字节为单位
 * @retval None
 */
void ddl_memclr(void *pu8Address, uint32_t u32Count)
{
    uint8_t *pu8Addr = (uint8_t *)pu8Address;

    if (NULL == pu8Addr)
    {
        return;
    }

    while (u32Count--)
    {
        *pu8Addr++ = 0;
    }
}

/**
 * @brief   1ms 延时函数
 * @param   [in]  u32Cnt: 延时时长，单位1ms
 * @retval  None
 */
void delay1ms(uint32_t u32Cnt)
{
    uint32_t ValNow, CNT = 0;
    uint32_t end = (u32Cnt * (SystemCoreClock / 1000));

    uint32_t StaVal = SysTick->VAL;
    while (1)
    {
        ValNow = SysTick->VAL;

        if (ValNow != StaVal)
        {
            if (ValNow < StaVal)
            {
                CNT += StaVal - ValNow;
            }
            else
            {
                CNT += SysTick->LOAD - ValNow + StaVal;
            }
            StaVal = ValNow;
            if (CNT >= end)
            {
                break;
            }
        }
    }
}


/**
 * @brief   100us 延时函数
 * @param   [in]  u32Cnt: 延时时长，单位100us
 * @retval  None
 */
void delay100us(uint32_t u32Cnt)
{
    uint32_t ValNow, CNT = 0;
    uint32_t end = (u32Cnt * (SystemCoreClock / 10000));

    uint32_t StaVal = SysTick->VAL;
    while (1)
    {
        ValNow = SysTick->VAL;

        if (ValNow != StaVal)
        {
            if (ValNow < StaVal)
            {
                CNT += StaVal - ValNow;
            }
            else
            {
                CNT += SysTick->LOAD - ValNow + StaVal;
            }

            StaVal = ValNow;

            if (CNT >= end)
            {
                break;
            }
        }
    }
}

/**
 * @brief   10us 延时函数
 * @param   [in]  u32Cnt: 延时时长，单位10us
 * @retval  None
 */
void delay10us(uint32_t u32Cnt)
{
    uint32_t ValNow, CNT = 0;

    uint32_t StaVal = SysTick->VAL;
    while (1)
    {
        ValNow = SysTick->VAL;

        if (ValNow != StaVal)
        {
            if (ValNow < StaVal)
            {
                CNT += StaVal - ValNow;
            }
            else
            {
                CNT += SysTick->LOAD - ValNow + StaVal;
            }

            StaVal = ValNow;

            if (CNT >= (u32Cnt * (SystemCoreClock / 100000)))
            {
                break;
            }
        }
    }
}

/**
 * @brief   设置bit位
 * @param   [in]  addr: 地址
 * @param   [in]  offset: 偏移位数
 * @param   [in]  bFlag: 清零或者置位
 * @retval  None
 */
void SetBit(uint32_t addr, uint32_t offset, boolean_t bFlag)
{
    if (TRUE == bFlag)
    {
        *((volatile uint32_t *)(addr)) |= ((1UL) << (offset));
    }
    else
    {
        *((volatile uint32_t *)(addr)) &= (~(1UL << (offset)));
    }


}


/**
 * @brief   获取bit位
 * @param   [in]  addr: 地址
 * @param   [in]  offset: 偏移位数
 * @retval  boolean_t
 */
boolean_t GetBit(uint32_t addr, uint32_t offset)
{
    return ((((*((volatile uint32_t *)(addr))) >> (offset)) & 1u) > 0) ? TRUE : FALSE;
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

