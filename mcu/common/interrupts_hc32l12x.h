/**
 *******************************************************************************
 * @file  interrupts_hc32l12x.h
 * @brief Header file for INTERRUPTS functions
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

#ifndef __INTERRUPTS_HC32L12X_H__
#define __INTERRUPTS_HC32L12X_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
#define DDL_IRQ_LEVEL_DEFAULT                   3u

/**
 * @brief 打开interrupt_hc32xxx.c中的中断回调函数，用户如果需要实现中断服务函数，
 *        可在源码文件中定义该文件中用"__WEAK"声明的同名中断服务函数即可。
 */
#define INT_CALLBACK_ON                                  1u  //<<(默认值)

/**
 * @brief 关闭interrupt_hc32xxx.c中的中断回调函数，此时用户可在该文件中自行定义中断服务函数的实现。
 */
#define INT_CALLBACK_OFF                                 0u

/**
 * @brief Global type definitions
 */
#define INT_CALLBACK_PORTA                       INT_CALLBACK_ON
#define INT_CALLBACK_PORTB                       INT_CALLBACK_ON
#define INT_CALLBACK_PORTC                       INT_CALLBACK_ON
#define INT_CALLBACK_PORTD                       INT_CALLBACK_ON
#define INT_CALLBACK_DMAC                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM3                        INT_CALLBACK_ON
#define INT_CALLBACK_USART0                       INT_CALLBACK_ON
#define INT_CALLBACK_USART1                       INT_CALLBACK_ON
#define INT_CALLBACK_LPUART0                     INT_CALLBACK_ON
#define INT_CALLBACK_LPUART1                     INT_CALLBACK_ON
#define INT_CALLBACK_SPI0                        INT_CALLBACK_ON
#define INT_CALLBACK_SPI1                        INT_CALLBACK_ON
#define INT_CALLBACK_I2C0                        INT_CALLBACK_ON
#define INT_CALLBACK_I2C1                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM0                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM1                        INT_CALLBACK_ON
#define INT_CALLBACK_TIM2                        INT_CALLBACK_ON
#define INT_CALLBACK_LPTIM0                      INT_CALLBACK_ON
#define INT_CALLBACK_LPTIM1                      INT_CALLBACK_ON
#define INT_CALLBACK_HSI2C                       INT_CALLBACK_ON
#define INT_CALLBACK_LPUART2                     INT_CALLBACK_ON
#define INT_CALLBACK_WWDT                        INT_CALLBACK_ON
#define INT_CALLBACK_IWDT                        INT_CALLBACK_ON
#define INT_CALLBACK_RTC                         INT_CALLBACK_ON
#define INT_CALLBACK_ADC                         INT_CALLBACK_ON
#define INT_CALLBACK_VC0                         INT_CALLBACK_ON
#define INT_CALLBACK_VC1                         INT_CALLBACK_ON
#define INT_CALLBACK_LVD                         INT_CALLBACK_ON
#define INT_CALLBACK_LCD                         INT_CALLBACK_ON
#define INT_CALLBACK_FLASH                       INT_CALLBACK_ON
#define INT_CALLBACK_RAM                         INT_CALLBACK_ON
#define INT_CALLBACK_CTRIM                       INT_CALLBACK_ON
#define INT_CALLBACK_CLKDET                      INT_CALLBACK_ON
 
/**
 * @brief 中断优先级数据类型定义
 */
typedef enum en_irq_level
{
    IrqLevel0  = 0u,   /*!< 优先级0*/
    IrqLevel1  = 1u,   /*!< 优先级1*/
    IrqLevel2  = 2u,   /*!< 优先级2*/
    IrqLevel3  = 3u,   /*!< 优先级3*/
} en_irq_level_t; 


/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @brief 系统中断使能开关
 */
extern void EnableNvic(IRQn_Type enIrq, en_irq_level_t enLevel, boolean_t bEn);


#ifdef __cplusplus
}
#endif


#endif /* __INTERRUPTS_HC32L12X_H__ */

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
