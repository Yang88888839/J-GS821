/**
 *******************************************************************************
 * @file  board_stkhc32l12x.h
 * @brief Header file for BSP functions
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

#ifndef __BOARD_STKHC32L12X_H__
#define __BOARD_STKHC32L12X_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "flash.h"
#include "gpio.h"
#include "sysctrl.h"
/******************************************************************************/
/* Global pre-processor symbols/macros ('define')                             */
/******************************************************************************/
/**
 * @defgroup BOARD_Global_Macros BOARD全局宏定义
 * @{
 */
/**
 * @brief  USER KEY
 */
#define STK_USER_PORT       GpioPortB
#define STK_USER_PIN        GpioPin9

#define STK_USER_READ()     (M0P_GPIO->PBIN_f.PB09)

/**
 * @brief  LED
 */
#define STK_LED_PORT        GpioPortD
#define STK_LED_PIN         GpioPin6

#define STK_LED_ON()        (M0P_GPIO->PDBSET_f.PD06 = 1)
#define STK_LED_OFF()       (M0P_GPIO->PDBCLR_f.PD06 = 1)

/**
 * @brief  XTH
 */
#define SYSTEM_XTH          (8*1000*1000u)     ///< 8MHz

#define STK_XTHI_PORT       GpioPortF
#define STK_XTHI_PIN        GpioPin0
#define STK_XTHO_PORT       GpioPortF
#define STK_XTHO_PIN        GpioPin1

/**
 * @brief  XTL
 */
#define SYSTEM_XTL          (32768u)            ///< 32768Hz
#define STK_XTLI_PORT       GpioPortC
#define STK_XTLI_PIN        GpioPin14
#define STK_XTLO_PORT       GpioPortC
#define STK_XTLO_PIN        GpioPin15

/**
 * @brief  LCD
 */
#define STK_LCD_COM0_PORT   GpioPortA
#define STK_LCD_COM0_PIN    GpioPin9
#define STK_LCD_COM1_PORT   GpioPortA
#define STK_LCD_COM1_PIN    GpioPin10
#define STK_LCD_COM2_PORT   GpioPortA
#define STK_LCD_COM2_PIN    GpioPin11
#define STK_LCD_COM3_PORT   GpioPortA
#define STK_LCD_COM3_PIN    GpioPin12
#define STK_LCD_SEG0_PORT   GpioPortC
#define STK_LCD_SEG0_PIN    GpioPin9
#define STK_LCD_SEG1_PORT   GpioPortC
#define STK_LCD_SEG1_PIN    GpioPin8
#define STK_LCD_SEG2_PORT   GpioPortC
#define STK_LCD_SEG2_PIN    GpioPin7
#define STK_LCD_SEG3_PORT   GpioPortC
#define STK_LCD_SEG3_PIN    GpioPin6
#define STK_LCD_SEG4_PORT   GpioPortD
#define STK_LCD_SEG4_PIN    GpioPin11
#define STK_LCD_SEG5_PORT   GpioPortD
#define STK_LCD_SEG5_PIN    GpioPin10
#define STK_LCD_SEG6_PORT   GpioPortD
#define STK_LCD_SEG6_PIN    GpioPin9
#define STK_LCD_SEG7_PORT   GpioPortD
#define STK_LCD_SEG7_PIN    GpioPin8

/**
 * @brief  I2C
 */
#define STK_I2C1_SCL_PORT    GpioPortA
#define STK_I2C1_SCL_PIN     GpioPin11
#define STK_I2C1_SDA_PORT    GpioPortA
#define STK_I2C1_SDA_PIN     GpioPin12

/**
 * @brief  HSI2C
 */
#define STK_HSI2C_SCL_PORT    GpioPortC
#define STK_HSI2C_SCL_PIN     GpioPin0
#define STK_HSI2C_SDA_PORT    GpioPortC
#define STK_HSI2C_SDA_PIN     GpioPin1

/**
 * @brief  SPI0
 */
#define STK_SPI0_CS_PORT      GpioPortA
#define STK_SPI0_CS_PIN       GpioPin4
#define STK_SPI0_SCK_PORT     GpioPortA
#define STK_SPI0_SCK_PIN      GpioPin5
#define STK_SPI0_MISO_PORT    GpioPortA
#define STK_SPI0_MISO_PIN     GpioPin6
#define STK_SPI0_MOSI_PORT    GpioPortA
#define STK_SPI0_MOSI_PIN     GpioPin7

/**
 * @brief  SPI1
 */
#define STK_SPI1_CS_PORT      GpioPortB
#define STK_SPI1_CS_PIN       GpioPin12
#define STK_SPI1_SCK_PORT     GpioPortB
#define STK_SPI1_SCK_PIN      GpioPin13
#define STK_SPI1_MISO_PORT    GpioPortB
#define STK_SPI1_MISO_PIN     GpioPin14
#define STK_SPI1_MOSI_PORT    GpioPortB
#define STK_SPI1_MOSI_PIN     GpioPin15



/**
 * @}
 */

/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/



#ifdef __cplusplus
}
#endif

#endif /* __BOARD_STKHC32L12X_H__ */
