/**
 ******************************************************************************
 * @file   ddl.h
 *
 * @brief This file contains all the functions prototypes of the DDL driver
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

#ifndef __DDL_H__
#define __DDL_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"
#include "board_stkhc32l12x.h"
#include "hc32l12x.h"
#include "system_hc32l12x.h"
#include "sysctrl.h"
#include "interrupts_hc32l12x.h"
/* C binding of definitions if building with C++ compiler                     */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_DDL DDL模块驱动库
 * @{
 */

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
/**
 * @defgroup DDL_Global_Macros DDL全局宏定义
 * @{
 */

#define DDL_ZERO_STRUCT(x)          ddl_memclr((uint8_t*)&(x), (uint32_t)(sizeof(x)))   /*!< 结构体清零 */


#define DEC2BCD(x)                  ((((x)/10)<<4) + ((x)%10))      /*!< 十进制转BCD */
#define BCD2DEC(x)                  ((((x)>>4)*10) + ((x)&0x0F))    /*!< BCD转十进制 */


#define SET_BIT(REG, BIT)     ((REG) |= (BIT))      /*!< 寄存器位置位 */

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))     /*!< 寄存器位清零 */

#define READ_BIT(REG, BIT)    ((REG) & (BIT))       /*!< 寄存器位读取 */

#define CLEAR_REG(REG)        ((REG) = (0x0))       /*!< 寄存器清零 */

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))       /*!< 寄存器写入 */

#define READ_REG(REG)         ((REG))               /*!< 寄存器读取 */

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK))) /*!< 寄存器修改 */

/**
 * @brief Global Device Series List
 */
#define DDL_DEVICE_SERIES_HC32L12X       (0u)


/**
 * @defgroup Compiler_Macros Compiler Macros
 * @{
 */
#ifndef __UNUSED
#define __UNUSED                        __attribute__((unused))
#endif /* __UNUSED */

#ifndef __USED
#define __USED                        __attribute__((used))
#endif /* __USED */

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#ifndef __WEAKDEF
#define __WEAKDEF                   __attribute__((weak))
#endif /* __WEAKDEF */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN               __attribute__((aligned(4)))
#endif /* __ALIGN_BEGIN */
#ifndef __NOINLINE
#define __NOINLINE                  __attribute__((noinline))
#endif /* __NOINLINE */
/* RAM functions are defined using the toolchain options.
Functions that are executed in RAM should reside in a separate source module.
Using the 'Options for File' dialog you can simply change the 'Code / Const'
area of a module to a memory space in physical RAM. */
#ifndef __RAM_FUNC
#define __RAM_FUNC                  __attribute__((section("ramfunc")))
#endif /* __RAM_FUNC */
#ifndef __NO_INIT
#define __NO_INIT                   __attribute__((section(".bss.noinit")))
#endif /* __NO_INIT */
#ifndef __NO_OPTIMIZE
#define __NO_OPTIMIZE               __attribute__((optnone))
#endif /* __NO_OPTIMIZE */
#elif defined (__GNUC__) && !defined (__CC_ARM) /*!< GNU Compiler */
#ifndef __WEAKDEF
#define __WEAKDEF                   __attribute__((weak))
#endif /* __WEAKDEF */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN               __attribute__((aligned (4)))
#endif /* __ALIGN_BEGIN */
#ifndef __NOINLINE
#define __NOINLINE                  __attribute__((noinline))
#endif /* __NOINLINE */
#ifndef __RAM_FUNC
#define __RAM_FUNC                  __attribute__((long_call, section(".ramfunc")))
/* Usage: __RAM_FUNC void foo(void) */
#endif /* __RAM_FUNC */
#ifndef __NO_INIT
#define __NO_INIT                   __attribute__((section(".noinit")))
#endif /* __NO_INIT */
#ifndef __NO_OPTIMIZE
#define __NO_OPTIMIZE               __attribute__((optimize("O0")))
#endif /* __NO_OPTIMIZE */
#elif defined (__ICCARM__)              /*!< IAR Compiler */
#ifndef __WEAKDEF
#define __WEAKDEF                   __weak
#endif /* __WEAKDEF */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN               _Pragma("data_alignment=4")
#endif /* __ALIGN_BEGIN */
#ifndef __NOINLINE
#define __NOINLINE                  _Pragma("optimize = no_inline")
#endif /* __NOINLINE */
#ifndef __RAM_FUNC
#define __RAM_FUNC                  __ramfunc
#endif /* __RAM_FUNC */
#ifndef __NO_INIT
#define __NO_INIT                   __no_init
#endif /* __NO_INIT */
#ifndef __NO_OPTIMIZE
#define __NO_OPTIMIZE               _Pragma("optimize=none")
#endif /* __NO_OPTIMIZE */
#elif defined (__CC_ARM)                /*!< ARM Compiler */
#ifndef __WEAKDEF
#define __WEAKDEF                   __attribute__((weak))
#endif /* __WEAKDEF */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN               __align(4)
#endif /* __ALIGN_BEGIN */
#ifndef __NOINLINE
#define __NOINLINE                  __attribute__((noinline))
#endif /* __NOINLINE */
#ifndef __NO_INIT
#define __NO_INIT                   __attribute__((section(".bss.noinit"), zero_init))
#endif /* __NO_INIT */
#ifndef __NO_OPTIMIZE
#define __NO_OPTIMIZE
#endif /* __NO_OPTIMIZE */
/* RAM functions are defined using the toolchain options.
Functions that are executed in RAM should reside in a separate source module.
Using the 'Options for File' dialog you can simply change the 'Code / Const'
area of a module to a memory space in physical RAM. */
#ifndef __RAM_FUNC
#define __RAM_FUNC                  __attribute__((section("ramfunc")))
#endif /* __RAM_FUNC */
/* Suppress warning message: extended constant initializer used */
#pragma diag_suppress 1296
#else
#error  "unsupported compiler!!"
#endif

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************/
/* User Device Setting Include file                                           */
/******************************************************************************/
#include "ddl_device.h"  // MUST be included here!

/******************************************************************************/
/* Global type definitions ('typedef')                                        */
/******************************************************************************/
/**
 * @defgroup DDL_Global_Types DDL全局类型定义
 * @{
 */
/**
 * @brief Level
 * @note Specifies levels
 */
typedef enum
{
    DdlLow      = 0u,  /*!< Low level  '0' */
    DdlHigh     = 1u   /*!< High level '1' */
} en_level_t;

/**
 * @brief Generic Flag Code
 * @note Specifies flags
 */
typedef enum
{
    DdlClr = 0u,       /*!< Flag clr '0' */
    DdlSet = 1u        /*!< Flag set '1' */
} en_stat_flag_t, en_irq_flag_t;
/**
 * @}
 */
/******************************************************************************/
/* Global variable declarations ('extern', definition in C source)            */
/******************************************************************************/

/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
/**
 * @addtogroup DDL_Global_Functions DDL全局函数定义
 * @{
 */
void ddl_memclr(void *pu8Address, uint32_t u32Count);
uint32_t Log2(uint32_t u32Val);

void delay1ms(uint32_t u32Cnt);
void delay100us(uint32_t u32Cnt);
void delay10us(uint32_t u32Cnt);

void SetBit(uint32_t addr, uint32_t offset, boolean_t bFlag);
boolean_t GetBit(uint32_t addr, uint32_t offset);

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

#endif /* __DDL_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/

