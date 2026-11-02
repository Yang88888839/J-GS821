/**
 ******************************************************************************
 * @file   reset.h
 *
 * @brief This file contains all the functions prototypes of the RESET driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-04-23       MDAS            First version
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

#ifndef __RESET_H__
#define __RESET_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_RESET RESET模块驱动库
 * @{
 */

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/*******************************************************************************
 * Global definitions
 ******************************************************************************/
/**
* @defgroup RESET_Global_Types RESET全局类型定义
* @{
*/

/**
 * @brief 外设源0复位控制类型定义
 * @note
 */
typedef enum
{
    ResetMskUsart0     = 1u << 0u,     ///< 串口0
    ResetMskUsart1     = 1u << 1u,     ///< 串口1
    ResetMskLpUart0    = 1u << 2u,     ///< 低功耗串口0
    ResetMskLpUart1    = 1u << 3u,     ///< 低功耗串口1
    ResetMskI2c0       = 1u << 4u,     ///< I2C0
    ResetMskI2c1       = 1u << 5u,     ///< I2C1
    ResetMskSpi0       = 1u << 6u,     ///< SPI0
    ResetMskSpi1       = 1u << 7u,     ///< SPI1
    ResetMskTim012     = 1u << 8u,     ///< 定时器TIM0/1/2
    ResetMskLpTim0     = 1u << 9u,     ///< 低功耗定时器0
    ResetMskTim3       = 1u << 11u,    ///< 定时器3
    ResetMskAdcBgr     = 1u << 16u,    ///< ADC&BGR
    ResetMskVcLvd      = 1u << 17u,    ///< VC和LVD
    ResetMskRng        = 1u << 18u,    ///< TRNG
    ResetMskRtc        = 1u << 20u,    ///< RTC
    ResetMskLcd        = 1u << 22u,    ///< LCD
    ResetMskCrc        = 1u << 26u,    ///< CRC
    ResetMskAes        = 1u << 27u,    ///< AES
    ResetMskGpio       = 1u << 28u,    ///< GPIO
    ResetMskDma        = 1u << 29u,    ///< DMA
    ResetMskHsi2c      = 1u << 30u,    ///< HSI2C
} en_reset_peripheral0_t;

/**
 * @brief 外设源1复位控制类型定义
 * @note
 */
typedef enum
{
    ResetMskCtrim      = 1u << 2u,    ///< 时钟校准
    ResetMskLpTim1     = 1u << 4u,    ///< 低功耗定时器1
    ResetMskLpUart2    = 1u << 8u,    ///< LPUART2
    ResetMskWwdt       = 1u << 10u,   ///< WWDT
} en_reset_peripheral1_t;

/**
 * @brief 复位源（标识）显示
 * @note
 */
typedef enum
{
    ResetFlagMskPor5V     = 1u << 0u,       ///< 5V启动复位
    ResetFlagMskPor1_5V   = 1u << 1u,       ///< 1.5V启动复位
    ResetFlagMskLvd       = 1u << 2u,       ///< 低电压检测复位
    ResetFlagMskIwdt      = 1u << 3u,       ///< 看门狗复位
    ResetFlagMskLockup    = 1u << 5u,       ///< 系统异常复位
    ResetFlagMskSysreq    = 1u << 6u,       ///< 软件复位
    ResetFlagMskRstb      = 1u << 7u,       ///< RESET脚 复位
    ResetFlagMskWwdt      = 1u << 8u,       ///< 窗口看门狗复位

} en_reset_flag_t;

/**
 * @}
 */


/*******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup RESET_Global_Functions RESET全局函数定义
 * @{
 */
///< 获得复位源状态
boolean_t Reset_GetFlag(en_reset_flag_t enRstFlg);
///< 清除复位源状态
void Reset_ClearFlag(en_reset_flag_t enRstFlg);
void Reset_ClearFlagAll(void);

///< 外设模块复位
void Reset_RstPeripheralAll(void);
void Reset_RstPeripheral0(en_reset_peripheral0_t enPeri);
void Reset_RstPeripheral1(en_reset_peripheral1_t enPeri);

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
#endif


#endif /* __RESET_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


