/**
 ******************************************************************************
 * @file   ram.h
 *
 * @brief This file contains all the functions prototypes of the RAM driver
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

#ifndef __RAM_H__
#define __RAM_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
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
 * @addtogroup DDL_RAM RAM子模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @addtogroup RAM_Global_Functions RAM全局函数定义
 * @{
 */

/* 中断相关函数 */
/* 中断使能/禁止 */
void Ram_EnableIrq(void);
void Ram_DisableIrq(void);

/* 中断标志获取 */
boolean_t Ram_GetIntFlag(void);

/* 中断标志清除 */
void Ram_ClearIntFlag(void);

/* 奇偶校验出错地址获取 */
uint32_t Ram_ErrAddrGet(void);

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

#endif /* __RAM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
