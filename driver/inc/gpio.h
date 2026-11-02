/**
 ******************************************************************************
 * @file   gpio.h
 *
 * @brief GPIO  This file contains all the functions prototypes of the GPIO driver
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

#ifndef __GPIO_H__
#define __GPIO_H__

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
 * @addtogroup DDL_GPIO GPIO模块驱动库
 * @{
 */


/*******************************************************************************
* Global type definitions ('typedef')
******************************************************************************/
/**
 * @defgroup GPIO_Global_Types GPIO 全局类型定义
 * @{
 */

/**
 * @brief GPIO PORT类型定义
 */
typedef enum
{
    GpioPortA = 0x00u,                 /*!< GPIO PORT A */
    GpioPortB = 0x40u,                 /*!< GPIO PORT B */
    GpioPortC = 0x80u,                 /*!< GPIO PORT C */
    GpioPortD = 0xc0u,                 /*!< GPIO PORT D */
} en_gpio_port_t;

/**
 * @brief GPIO PIN类型定义
 */
typedef enum
{
    GpioPin0  = 0u,                 /*!< GPIO PIN0 */
    GpioPin1  = 1u,                 /*!< GPIO PIN1 */
    GpioPin2  = 2u,                 /*!< GPIO PIN2 */
    GpioPin3  = 3u,                 /*!< GPIO PIN3 */
    GpioPin4  = 4u,                 /*!< GPIO PIN4 */
    GpioPin5  = 5u,                 /*!< GPIO PIN5 */
    GpioPin6  = 6u,                 /*!< GPIO PIN6 */
    GpioPin7  = 7u,                 /*!< GPIO PIN7 */
    GpioPin8  = 8u,                 /*!< GPIO PIN8 */
    GpioPin9  = 9u,                 /*!< GPIO PIN9 */
    GpioPin10 = 10u,                /*!< GPIO PIN10 */
    GpioPin11 = 11u,                /*!< GPIO PIN11 */
    GpioPin12 = 12u,                /*!< GPIO PIN12 */
    GpioPin13 = 13u,                /*!< GPIO PIN13 */
    GpioPin14 = 14u,                /*!< GPIO PIN14 */
    GpioPin15 = 15u,                /*!< GPIO PIN15 */
} en_gpio_pin_t;

/**
 * @brief GPIO 端口复用功能(AF-Alternate function)类型定义
 * @note  具体功能及含义请参考用户手册GPIO复用表或下表
 */
typedef enum
{
    GpioAf0  = 0u,      /*!< GPIO功能 */
    GpioAf1  = 1u,      /*!< GPIO AF1:复用功能1 */
    GpioAf2  = 2u,      /*!< GPIO AF2:复用功能2 */
    GpioAf3  = 3u,      /*!< GPIO AF3:复用功能3 */
    GpioAf4  = 4u,      /*!< GPIO AF4:复用功能4 */
    GpioAf5  = 5u,      /*!< GPIO AF5:复用功能5 */
    GpioAf6  = 6u,      /*!< GPIO AF6:复用功能6 */
    GpioAf7  = 7u,      /*!< GPIO AF7:复用功能7 */
} en_gpio_af_t;

///*||======||=============||=============||=============||=============||=============||=============||=============||*///
///*||PSEL  ||   GpioAf1   ||   GpioAf2   ||   GpioAf3   ||   GpioAf4   ||   GpioAf5   ||   GpioAf6   ||   GpioAf7   ||*///
///*||======||=============||=============||=============||=============||=============||=============||=============||*///
///*||PA00  ||USART1_CTS   ||LPUART1_TXD  ||TIM0_ETR     ||VC0_OUT      ||TIM1_CHA     ||TIM3_ETR     ||TIM0_CHA     ||*///
///*||PA01  ||USART1_RTS   ||LPUART1_RXD  ||TIM0_CHB     ||TIM1_ETR     ||TIM1_CHB     ||HCLK_OUT     ||SPI1_MOSI    ||*///
///*||PA02  ||USART1_TXD   ||TIM0_CHA     ||VC1_OUT      ||TIM1_CHA     ||TIM2_CHA     ||PCLK_OUT     ||SPI1_MISO    ||*///
///*||PA03  ||USART1_RXD   ||TIM0_GATE    ||TIM1_CHB     ||TIM2_CHB     ||SPI1_CS      ||TIM3_CH1A    ||             ||*///
///*||PA04  ||SPI0_CS      ||USART1_TXD   ||LPUART1_RTS  ||TIM2_ETR     ||             ||LVD_OUT      ||TIM3_CH2B    ||*///
///*||PA05  ||SPI0_SCK     ||TIM0_ETR     ||LPUART1_CTS  ||TIM0_CHA     ||USART1_RTS   ||XTL_OUT      ||XTH_OUT      ||*///
///*||PA06  ||SPI0_MISO    ||LPTIM0_TOG   ||TIM3_BK      ||TIM1_CHA     ||VC0_OUT      ||TIM3_GATE    ||LPUART0_CTS  ||*///
///*||PA07  ||SPI0_MOSI    ||LPTIM0_TOGN  ||HCLK_OUT     ||TIM3_CH0B    ||TIM2_CHA     ||VC1_OUT      ||LPUART0_RXD  ||*///
///*||PA08  ||USART0_TXD   ||TIM3_CH0A    ||CTRIM_ETRTOG ||LPTIM1_ETR   ||TIM1_GATE    ||             ||TIM3_BK      ||*///
///*||PA09  ||USART0_TXD   ||TIM3_CH1A    ||TIM0_BK      ||I2C0_SCL     ||LPUART0_TXD  ||HCLK_OUT     ||TIM3_CH0A    ||*///
///*||PA10  ||USART0_RXD   ||TIM3_CH2A    ||TIM2_BK      ||I2C0_SDA     ||TIM2_GATE    ||PCLK_OUT     ||TIM0_CHB     ||*///
///*||PA11  ||USART0_CTS   ||TIM3_GATE    ||I2C1_SCL     ||HSI2C_SCL    ||VC0_OUT      ||SPI0_MISO    ||CTRIM_ETRTOG ||*///
///*||PA12  ||USART0_RTS   ||TIM3_ETR     ||I2C1_SDA     ||HSI2C_SDA    ||VC1_OUT      ||SPI0_MOSI    ||             ||*///
///*||PA13  ||IR_OUT       ||USART0_RXD   ||LVD_OUT      ||TIM3_ETR     ||RTC_1HZ      ||I2C1_SDA     ||USART1_SCK   ||*///
///*||PA14  ||USART1_TXD   ||USART0_TXD   ||TIM3_CH2A    ||LVD_OUT      ||RCH_OUT      ||RCL_OUT      ||I2C1_SCL     ||*///
///*||PA15  ||SPI0_CS      ||USART1_RXD   ||LPUART1_RTS  ||TIM0_ETR     ||TIM0_CHA     ||TIM3_CH1A    ||USART0_SCK   ||*///
///*||PB00  ||             ||TIM3_CH1B    ||LPUART0_TXD  ||LPTIM1_TOG   ||RCH_OUT      ||RCL_OUT      ||             ||*///
///*||PB01  ||             ||PCLK_OUT     ||TIM3_CH2B    ||             ||LPUART0_RTS  ||LPTIM1_ETR   ||TCLK_OUT　   ||*///
///*||PB02  ||LPTIM0_TOG   ||             ||LPUART1_TXD  ||             ||TIM1_BK      ||TIM0_BK      ||TIM2_BK      ||*///
///*||PB03  ||SPI0_SCK     ||TIM0_CHB     ||TIM1_GATE    ||TIM3_CH0A    ||LPTIM0_GATE  ||XTL_OUT      ||XTH_OUT      ||*///
///*||PB04  ||SPI0_MISO    ||             ||TIM2_BK      ||USART0_CTS   ||TIM2_GATE    ||TIM3_CH0B    ||LPTIM0_ETR   ||*///
///*||PB05  ||SPI0_MOSI    ||HSI2C_SCL    ||TIM1_BK      ||             ||LPTIM0_GATE  ||             ||USART0_RTS   ||*///
///*||PB06  ||I2C0_SCL     ||USART0_TXD   ||TIM1_CHB     ||TIM0_CHA     ||LPTIM0_ETR   ||TIM3_CH0A    ||LPTIM0_TOG   ||*///
///*||PB07  ||I2C0_SDA     ||USART0_RXD   ||TIM2_CHB     ||LPUART1_CTS  ||TIM0_CHB     ||LPTIM0_TOGN  ||             ||*///
///*||PB08  ||I2C0_SCL     ||TIM1_CHA     ||USART1_SCK   ||TIM2_CHA     ||TIM0_GATE    ||TIM3_CH2A    ||USART0_TXD   ||*///
///*||PB09  ||I2C0_SDA     ||IR_OUT       ||SPI1_CS      ||TIM2_CHA     ||HSI2C_SDA    ||TIM2_CHB     ||USART0_RXD   ||*///
///*||PB10  ||I2C1_SCL     ||SPI1_SCK     ||TIM1_CHA     ||LPUART0_TXD  ||TIM3_CH1A    ||LPUART1_RTS  ||USART1_RTS   ||*///
///*||PB11  ||I2C1_SDA     ||TIM1_CHB     ||LPUART0_RXD  ||TIM2_GATE    ||             ||LPUART1_CTS  ||USART1_CTS   ||*///
///*||PB12  ||SPI1_CS      ||TIM3_BK      ||LPUART0_TXD  ||TIM0_BK      ||USART0_SCK   ||LPUART0_RTS  ||             ||*///
///*||PB13  ||SPI1_SCK     ||I2C1_SCL     ||TIM3_CH0B    ||LPUART0_CTS  ||TIM1_CHA     ||TIM1_GATE    ||             ||*///
///*||PB14  ||SPI1_MISO    ||I2C1_SDA     ||TIM3_CH1B    ||TIM0_CHA     ||RTC_1HZ      ||LPUART0_RTS  ||TIM1_BK      ||*///
///*||PB15  ||SPI1_MOSI    ||TIM3_CH2B    ||TIM0_CHB     ||TIM0_GATE    ||             ||             ||LPUART1_RXD  ||*///
///*||PC00  ||LPTIM0_GATE  ||             ||USART1_CTS   ||HSI2C_SCL    ||             ||             ||             ||*///
///*||PC01  ||LPTIM0_TOG   ||             ||USART1_RTS   ||HSI2C_SDA    ||             ||             ||             ||*///
///*||PC02  ||SPI1_MISO    ||LPTIM0_TOGN  ||             ||             ||             ||             ||             ||*///
///*||PC03  ||SPI1_MOSI    ||LPTIM0_ETR   ||LPTIM0_TOGN  ||             ||             ||             ||             ||*///
///*||PC04  ||LPUART0_TXD  ||TIM2_ETR     ||IR_OUT       ||             ||             ||             ||             ||*///
///*||PC05  ||LPUART0_RXD  ||             ||             ||             ||             ||             ||             ||*///
///*||PC06  ||             ||             ||TIM2_CHA     ||LPTIM1_GATE  ||             ||LPUART2_RXD  ||             ||*///
///*||PC07  ||             ||             ||TIM2_CHB     ||LPTIM1_ETR   ||             ||LPUART2_TXD  ||             ||*///
///*||PC08  ||             ||             ||TIM2_ETR     ||LPTIM1_TOG   ||             ||LPUART2_CTS  ||             ||*///
///*||PC09  ||             ||             ||TIM1_ETR     ||LPTIM1_TOGN  ||             ||LPUART2_RTS  ||             ||*///
///*||PC10  ||LPUART1_TXD  ||LPUART0_TXD  ||             ||             ||             ||             ||             ||*///
///*||PC11  ||LPUART1_RXD  ||LPUART0_RXD  ||             ||             ||             ||             ||             ||*///
///*||PC12  ||LPUART0_TXD  ||LPUART1_TXD  ||             ||             ||             ||             ||             ||*///
///*||PC13  ||RTC_TAMP     ||RTC_1HZ      ||TIM3_CH1B    ||             ||             ||             ||             ||*///
///*||PC14  ||             ||USART0_SCK   ||             ||LPTIM1_TOGN  ||             ||             ||             ||*///
///*||PC15  ||             ||USART1_SCK   ||             ||LPTIM1_GATE  ||             ||             ||             ||*///
///*||PD00  ||I2C0_SDA     ||CTRIM_ETRTOG ||USART1_TXD   ||             ||             ||LPUART2_RXD  ||             ||*///
///*||PD01  ||I2C0_SCL     ||             ||USART1_RXD   ||             ||             ||LPUART2_TXD  ||             ||*///
///*||PD02  ||             ||LPUART0_RTS  ||TIM1_ETR     ||HSI2C_SCL    ||             ||             ||             ||*///
///*||PD03  ||             ||             ||             ||             ||             ||             ||             ||*///
///*||PD04  ||             ||             ||LPTIM1_TOGN  ||             ||             ||             ||             ||*///
///*||PD05  ||USART0_SCK   ||             ||LPTIM1_TOG   ||HSI2C_SDA    ||             ||             ||             ||*///
///*||PD06  ||I2C1_SCL     ||LPUART1_CTS  ||USART0_CTS   ||LPTIM1_GATE  ||             ||LPUART2_CTS  ||             ||*///
///*||PD07  ||I2C1_SDA     ||LPUART1_RTS  ||USART0_RTS   ||LPTIM1_TOGN  ||             ||LPUART2_RTS  ||             ||*///
///*||======||=============||=============||=============||=============||=============||=============||=============||*///


/**
 * @brief GPIO输入输出配置数据类型定义
 */
typedef enum
{
    GpioDirOut = 0u,                /*!< GPIO 输出 */
    GpioDirIn  = 1u,                /*!< GPIO 输入 */
} en_gpio_dir_t;

/**
 * @brief GPIO端口上拉配置数据类型定义
 */
typedef enum
{
    GpioPuDisable = 0u,                /*!< GPIO无上拉 */
    GpioPuEnable  = 1u,                /*!< GPIO上拉 */
} en_gpio_pu_t;

/**
 * @brief GPIO端口下拉配置数据类型定义
 */
typedef enum
{
    GpioPdDisable = 0u,                /*!< GPIO无下拉 */
    GpioPdEnable  = 1u,                /*!< GPIO下拉 */
} en_gpio_pd_t;

/**
 * @brief GPIO端口输出驱动能力配置数据类型定义
 */
typedef enum
{
    GpioDrvH = 0u,                  /*!< GPIO高驱动能力 */
    GpioDrvL = 1u,                  /*!< GPIO低驱动能力 */
} en_gpio_drv_t;

/**
 * @brief GPIO端口开漏输出控制数据类型定义
 */
typedef enum
{
    GpioOdDisable = 0u,             /*!< GPIO开漏输出关闭 */
    GpioOdEnable  = 1u,             /*!< GPIO开漏输出使能 */
} en_gpio_od_t;

/**
 * @brief GPIO端口输入/输出值寄存器总线控制模式选择
 */
typedef enum
{
    GpioFastIO = 0u,             /*!< FAST IO 总线控制模式 */
    GpioAHB  = 1u,               /*!< AHB 总线控制模式 */
} en_gpio_ctrl_mode_t;

/**
 * @brief GPIO中断触发方式类型定义
 */
typedef enum
{
    GpioIrqHigh     = 0u,           /*!< GPIO高电平触发 */
    GpioIrqLow      = 1u,           /*!< GPIO低电平触发 */
    GpioIrqRising   = 2u,           /*!< GPIO上升沿触发 */
    GpioIrqFalling  = 3u,           /*!< GPIO下降沿触发 */
} en_gpio_irqtype_t;


/**
 * @brief GPIO 辅助功能（SF-Secondary Function）HCLK输出门控类型定义
 */
typedef enum
{
    GpioSfHclkOutDisable = 0u,       /*!< HCLK输出门控关闭 */
    GpioSfHclkOutEnable  = 1u,       /*!< HCLK输出门控使能 */
} en_gpio_sf_hclkout_g_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）HCLK输出分频选择类型定义
 **/
typedef enum
{
    GpioSfHclkOutDiv1 = 0u,         /*!< HCLK */
    GpioSfHclkOutDiv2 = 1u,         /*!< HCLK/2 */
    GpioSfHclkOutDiv4 = 2u,         /*!< HCLK/4 */
    GpioSfHclkOutDiv8 = 3u,         /*!< HCLK/8 */
} en_gpio_sf_hclkout_div_t;
/**
 * @brief GPIO 辅助功能（SF-Secondary Function）PCLK输出门控类型定义
 **/
typedef enum
{
    GpioSfPclkOutDisable = 0u,       /*!< PCLK输出门控关闭 */
    GpioSfPclkOutEnable  = 1u,       /*!< PCLK输出门控使能 */
} en_gpio_sf_pclkout_g_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）PCLK输出分频选择类型定义
 */
typedef enum
{
    GpioSfPclkOutDiv1 = 0u,         /*!< PCLK */
    GpioSfPclkOutDiv2 = 1u,         /*!< PCLK/2 */
    GpioSfPclkOutDiv4 = 2u,         /*!< PCLK/4 */
    GpioSfPclkOutDiv8 = 3u,         /*!< PCLK/8 */
} en_gpio_sf_pclkout_div_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）IR输出极性选择类型定义
 */
typedef enum
{
    GpioSfIrP = 0u,                  /*!< IR正向输出 */
    GpioSfIrN = 1u,                  /*!< IR反向输出 */
} en_gpio_sf_irpol_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）HSI2C IO有效电平类型定义
 */
typedef enum
{
    GpioHsi2cLevelNormal = 0u,       /*!< HSI2C IO正常有效电平 */
    GpioHsi2cLevelLow    = 1u,       /*!< HSI2C IO低有效电平 */
} en_gpio_sf_hsi2c_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）TCLK 输出信号源类型定义
 */
typedef enum
{
    GpioTclkRch  = 0u,             /*!< TCLK时钟源选择RCH */
    GpioTclkRcl    = 1u,             /*!< TCLK时钟源选择RCL */
    GpioTclkXth    = 2u,             /*!< TCLK时钟源选择XTH */
    GpioTclkXtl    = 3u,             /*!< TCLK时钟源选择XTL */
} en_gpio_sf_tlcksel_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）TCLK 输出分频类型定义
 */
typedef enum
{
    GpioTclkDiv1    = 0u,             /*!< TCLK输出1分频 */
    GpioTclkDiv2    = 1u,             /*!< TCLK输出2分频 */
    GpioTclkDiv4    = 2u,             /*!< TCLK输出4分频 */
    GpioTclkDiv8    = 3u,             /*!< TCLK输出8分频 */
} en_gpio_sf_tlckdiv_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器互联功能选择类型定义
 * @note  具体功能及含义请参考用户手册GPIO辅助寄存器描述
 */
typedef enum
{
    GpioSf0 = 0u,       /*!< SF0:PX_SEL的配置功能 */
    GpioSf1 = 1u,       /*!< SF1:辅助功能1 */
    GpioSf2 = 2u,       /*!< SF2:辅助功能2 */
    GpioSf3 = 3u,       /*!< SF3:辅助功能3 */
    GpioSf4 = 4u,       /*!< SF4:辅助功能4 */
    GpioSf5 = 5u,       /*!< SF5:辅助功能5 */
    GpioSf6 = 6u,       /*!< SF6:辅助功能6 */
    GpioSf7 = 7u,       /*!< SF7:辅助功能7 */
} en_gpio_sf_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器门控类型选择数据类型定义
 **/
typedef enum
{
    GpioSfTim0G   = 0u,         /*!< Tim0定时器GATE输入选择 */
    GpioSfTim1G   = 3u,         /*!< Tim1定时器GATE输入选择 */
    GpioSfTim2G   = 6u,         /*!< Tim2定时器GATE输入选择 */
    GpioSfTim3G   = 9u,         /*!< Tim3定时器GATE输入选择 */
    GpioSfLpTim0G = 12u,        /*!< LPTim0定时器GATE输入选择 */
    GpioSfLpTim1G = 38u,        /*!< LPTim1定时器GATE输入选择 */
} en_gpio_sf_tim_g_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器ETR类型选择数据类型定义
 */
typedef enum
{
    GpioSfTim0E   = 0u,         /*!< Tim0定时器ETR输入选择 */
    GpioSfTim1E   = 3u,         /*!< Tim1定时器ETR输入选择 */
    GpioSfTim2E   = 6u,         /*!< Tim2定时器ETR输入选择 */
    GpioSfTim3E   = 9u,         /*!< Tim3定时器ETR输入选择 */
    GpioSfLpTim0E = 12u,        /*!< LPTim0定时器ETR输入选择 */
    GpioSfLpTim1E = 41u,        /*!< LPTim1定时器ETR输入选择 */
} en_gpio_sf_tim_e_t;

/**
 * @brief GPIO 辅助功能（SF-Secondary Function）定时器捕获输入类型选择数据类型定义
 */
typedef enum
{
    GpioSfTim0CA = 0u,          /*!< Tim0定时器CHA输入选择 */
    GpioSfTim1CA = 3u,          /*!< Tim1定时器CHA输入选择 */
    GpioSfTim2CA = 6u,          /*!< Tim2定时器CHA输入选择 */
    GpioSfTim3CA = 9u,          /*!< Tim3定时器CH0A输入选择 */
    GpioSfTim3CB = 12u,         /*!< Tim3定时器CH0B输入选择 */
} en_gpio_sf_tim_c_t;

/**
 * @brief GPIO 滤波时钟源选择类型定义
 */
typedef enum
{
    GpioFltSelHclk   = 0u,      /*!< GPIO 滤波时钟选择HCLK */
    GpioFltSelRc256k = 1u,      /*!< GPIO 滤波时钟选择RC256K */
} en_gpio_flt_clk_sel_t;

/**
 * @brief GPIO 滤波时钟分频选择类型定义
 */
typedef enum
{
    GpioFltFclkDiv1  = 0u,      /*!< GPIO 滤波时钟分频FCLK */
    GpioFltFclkDiv4  = 1u,      /*!< GPIO 滤波时钟分频FCLK/4 */
    GpioFltFclkDiv16 = 2u,      /*!< GPIO 滤波时钟分频FCLK/16 */
    GpioFltFclkDiv64 = 3u,      /*!< GPIO 滤波时钟分频FCLK/64 */
} en_gpio_flt_clk_div_t;

/**
 * @brief GPIO 端口配置结构体定义
 */
typedef struct
{
    boolean_t           bOutputVal;      /*!< 默认端口输出电平 */
    en_gpio_dir_t       enDir;           /*!< 端口方向配置 */
    en_gpio_drv_t       enDrv;           /*!< 端口驱动能力配置 */
    en_gpio_pu_t        enPu;            /*!< 端口上拉配置 */
    en_gpio_pd_t        enPd;            /*!< 端口下拉配置 */
    en_gpio_od_t        enOD;            /*!< 端口开漏输出配置 */
    en_gpio_ctrl_mode_t enCtrlMode;      /*!< 端口输入/输出值寄存器总线控制模式配置 */
} stc_gpio_cfg_t;

/**
 * @brief GPIO 端口滤波配置结构体定义
 */
typedef struct
{
    boolean_t              bPa00FltEn;      /*!< PA00端口滤波使能 */
    boolean_t              bPa08FltEn;      /*!< PA08端口滤波使能 */
    boolean_t              bPb00FltEn;      /*!< PB00端口滤波使能 */
    boolean_t              bPb08FltEn;      /*!< PB08端口滤波使能 */
    en_gpio_flt_clk_sel_t  enFltCLkSel;     /*!< 滤波时钟源选择 */
    en_gpio_flt_clk_div_t  enFltCLkDiv;     /*!< 滤波时钟分频选择 */
} stc_gpio_flt_cfg_t;

/**
 * @}
 */

/*******************************************************************************
 * Global definitions——(GPIO 复用功能宏定义)
 ******************************************************************************/
/**
* @defgroup GPIO_Global_Macros GPIO全局宏定义
* @{
*/
/**
 * @defgroup GPIO_AF1_Macros GPIO复用功能AF1宏定义
 * @{
 */
#define PA00_USART1_CTS   (GpioPortA<<16u|GpioPin0 <<8u|GpioAf1)
#define PA01_USART1_RTS   (GpioPortA<<16u|GpioPin1 <<8u|GpioAf1)
#define PA02_USART1_TXD   (GpioPortA<<16u|GpioPin2 <<8u|GpioAf1)
#define PA03_USART1_RXD   (GpioPortA<<16u|GpioPin3 <<8u|GpioAf1)
#define PA04_SPI0_CS      (GpioPortA<<16u|GpioPin4 <<8u|GpioAf1)
#define PA05_SPI0_SCK     (GpioPortA<<16u|GpioPin5 <<8u|GpioAf1)
#define PA06_SPI0_MISO    (GpioPortA<<16u|GpioPin6 <<8u|GpioAf1)
#define PA07_SPI0_MOSI    (GpioPortA<<16u|GpioPin7 <<8u|GpioAf1)
#define PA08_USART0_TXD   (GpioPortA<<16u|GpioPin8 <<8u|GpioAf1)
#define PA09_USART0_TXD   (GpioPortA<<16u|GpioPin9 <<8u|GpioAf1)
#define PA10_USART0_RXD   (GpioPortA<<16u|GpioPin10<<8u|GpioAf1)
#define PA11_USART0_CTS   (GpioPortA<<16u|GpioPin11<<8u|GpioAf1)
#define PA12_USART0_RTS   (GpioPortA<<16u|GpioPin12<<8u|GpioAf1)
#define PA13_IR_OUT       (GpioPortA<<16u|GpioPin13<<8u|GpioAf1)
#define PA14_USART1_TXD   (GpioPortA<<16u|GpioPin14<<8u|GpioAf1)
#define PA15_SPI0_CS      (GpioPortA<<16u|GpioPin15<<8u|GpioAf1)
#define PB00_1x           (GpioPortB<<16u|GpioPin0 <<8u|GpioAf1)
#define PB01_1x           (GpioPortB<<16u|GpioPin1 <<8u|GpioAf1)
#define PB02_LPTIM0_TOG   (GpioPortB<<16u|GpioPin2 <<8u|GpioAf1)
#define PB03_SPI0_SCK     (GpioPortB<<16u|GpioPin3 <<8u|GpioAf1)
#define PB04_SPI0_MISO    (GpioPortB<<16u|GpioPin4 <<8u|GpioAf1)
#define PB05_SPI0_MOSI    (GpioPortB<<16u|GpioPin5 <<8u|GpioAf1)
#define PB06_I2C0_SCL     (GpioPortB<<16u|GpioPin6 <<8u|GpioAf1)
#define PB07_I2C0_SDA     (GpioPortB<<16u|GpioPin7 <<8u|GpioAf1)
#define PB08_I2C0_SCL     (GpioPortB<<16u|GpioPin8 <<8u|GpioAf1)
#define PB09_I2C0_SDA     (GpioPortB<<16u|GpioPin9 <<8u|GpioAf1)
#define PB10_I2C1_SCL     (GpioPortB<<16u|GpioPin10<<8u|GpioAf1)
#define PB11_I2C1_SDA     (GpioPortB<<16u|GpioPin11<<8u|GpioAf1)
#define PB12_SPI1_CS      (GpioPortB<<16u|GpioPin12<<8u|GpioAf1)
#define PB13_SPI1_SCK     (GpioPortB<<16u|GpioPin13<<8u|GpioAf1)
#define PB14_SPI1_MISO    (GpioPortB<<16u|GpioPin14<<8u|GpioAf1)
#define PB15_SPI1_MOSI    (GpioPortB<<16u|GpioPin15<<8u|GpioAf1)
#define PC00_LPTIM0_GATE  (GpioPortC<<16u|GpioPin0 <<8u|GpioAf1)
#define PC01_LPTIM0_TOG   (GpioPortC<<16u|GpioPin1 <<8u|GpioAf1)
#define PC02_SPI1_MISO    (GpioPortC<<16u|GpioPin2 <<8u|GpioAf1)
#define PC03_SPI1_MOSI    (GpioPortC<<16u|GpioPin3 <<8u|GpioAf1)
#define PC04_LPUART0_TXD  (GpioPortC<<16u|GpioPin4 <<8u|GpioAf1)
#define PC05_LPUART0_RXD  (GpioPortC<<16u|GpioPin5 <<8u|GpioAf1)
#define PC06_1x           (GpioPortC<<16u|GpioPin6 <<8u|GpioAf1)
#define PC07_1x           (GpioPortC<<16u|GpioPin7 <<8u|GpioAf1)
#define PC08_1x           (GpioPortC<<16u|GpioPin8 <<8u|GpioAf1)
#define PC09_1x           (GpioPortC<<16u|GpioPin9 <<8u|GpioAf1)
#define PC10_LPUART1_TXD  (GpioPortC<<16u|GpioPin10<<8u|GpioAf1)
#define PC11_LPUART1_RXD  (GpioPortC<<16u|GpioPin11<<8u|GpioAf1)
#define PC12_LPUART0_TXD  (GpioPortC<<16u|GpioPin12<<8u|GpioAf1)
#define PC13_RTC_TAMP     (GpioPortC<<16u|GpioPin13<<8u|GpioAf1)
#define PC14_1x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf1)
#define PC15_1x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf1)
#define PD00_I2C0_SDA     (GpioPortD<<16u|GpioPin0 <<8u|GpioAf1)
#define PD01_I2C0_SCL     (GpioPortD<<16u|GpioPin1 <<8u|GpioAf1)
#define PD02_1x           (GpioPortD<<16u|GpioPin2 <<8u|GpioAf1)
#define PD03_1x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf1)
#define PD04_1x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf1)
#define PD05_USART0_SCK   (GpioPortD<<16u|GpioPin5 <<8u|GpioAf1)
#define PD06_I2C1_SCL     (GpioPortD<<16u|GpioPin6 <<8u|GpioAf1)
#define PD07_I2C1_SDA     (GpioPortD<<16u|GpioPin7 <<8u|GpioAf1)
/**
 * @}
 */

/**
 * @defgroup GPIO_AF2_Macros GPIO复用功能AF2宏定义
 * @{
 */
#define PA00_LPUART1_TXD  (GpioPortA<<16u|GpioPin0 <<8u|GpioAf2)
#define PA01_LPUART1_RXD  (GpioPortA<<16u|GpioPin1 <<8u|GpioAf2)
#define PA02_TIM0_CHA     (GpioPortA<<16u|GpioPin2 <<8u|GpioAf2)
#define PA03_TIM0_GATE    (GpioPortA<<16u|GpioPin3 <<8u|GpioAf2)
#define PA04_USART1_TXD   (GpioPortA<<16u|GpioPin4 <<8u|GpioAf2)
#define PA05_TIM0_ETR     (GpioPortA<<16u|GpioPin5 <<8u|GpioAf2)
#define PA06_LPTIM0_TOG   (GpioPortA<<16u|GpioPin6 <<8u|GpioAf2)
#define PA07_LPTIM0_TOGN  (GpioPortA<<16u|GpioPin7 <<8u|GpioAf2)
#define PA08_TIM3_CH0A    (GpioPortA<<16u|GpioPin8 <<8u|GpioAf2)
#define PA09_TIM3_CH1A    (GpioPortA<<16u|GpioPin9 <<8u|GpioAf2)
#define PA10_TIM3_CH2A    (GpioPortA<<16u|GpioPin10<<8u|GpioAf2)
#define PA11_TIM3_GATE    (GpioPortA<<16u|GpioPin11<<8u|GpioAf2)
#define PA12_TIM3_ETR     (GpioPortA<<16u|GpioPin12<<8u|GpioAf2)
#define PA13_USART0_RXD   (GpioPortA<<16u|GpioPin13<<8u|GpioAf2)
#define PA14_USART0_TXD   (GpioPortA<<16u|GpioPin14<<8u|GpioAf2)
#define PA15_USART1_RXD   (GpioPortA<<16u|GpioPin15<<8u|GpioAf2)
#define PB00_TIM3_CH1B    (GpioPortB<<16u|GpioPin0 <<8u|GpioAf2)
#define PB01_PCLK_OUT     (GpioPortB<<16u|GpioPin1 <<8u|GpioAf2)
#define PB02_2x           (GpioPortB<<16u|GpioPin2 <<8u|GpioAf2)
#define PB03_TIM0_CHB     (GpioPortB<<16u|GpioPin3 <<8u|GpioAf2)
#define PB04_2x           (GpioPortB<<16u|GpioPin4 <<8u|GpioAf2)
#define PB05_HSI2C_SCL    (GpioPortB<<16u|GpioPin5 <<8u|GpioAf2)
#define PB06_USART0_TXD   (GpioPortB<<16u|GpioPin6 <<8u|GpioAf2)
#define PB07_USART0_RXD   (GpioPortB<<16u|GpioPin7 <<8u|GpioAf2)
#define PB08_TIM1_CHA     (GpioPortB<<16u|GpioPin8 <<8u|GpioAf2)
#define PB09_IR_OUT       (GpioPortB<<16u|GpioPin9 <<8u|GpioAf2)
#define PB10_SPI1_SCK     (GpioPortB<<16u|GpioPin10<<8u|GpioAf2)
#define PB11_TIM1_CHB     (GpioPortB<<16u|GpioPin11<<8u|GpioAf2)
#define PB12_TIM3_BK      (GpioPortB<<16u|GpioPin12<<8u|GpioAf2)
#define PB13_I2C1_SCL     (GpioPortB<<16u|GpioPin13<<8u|GpioAf2)
#define PB14_I2C1_SDA     (GpioPortB<<16u|GpioPin14<<8u|GpioAf2)
#define PB15_TIM3_CH2B    (GpioPortB<<16u|GpioPin15<<8u|GpioAf2)
#define PC00_2x           (GpioPortC<<16u|GpioPin0 <<8u|GpioAf2)
#define PC01_2x           (GpioPortC<<16u|GpioPin1 <<8u|GpioAf2)
#define PC02_LPTIM0_TOGN  (GpioPortC<<16u|GpioPin2 <<8u|GpioAf2)
#define PC03_LPTIM0_ETR   (GpioPortC<<16u|GpioPin3 <<8u|GpioAf2)
#define PC04_TIM2_ETR     (GpioPortC<<16u|GpioPin4 <<8u|GpioAf2)
#define PC05_2x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf2)
#define PC06_2x           (GpioPortC<<16u|GpioPin6 <<8u|GpioAf2)
#define PC07_2x           (GpioPortC<<16u|GpioPin7 <<8u|GpioAf2)
#define PC08_2x           (GpioPortC<<16u|GpioPin8 <<8u|GpioAf2)
#define PC09_2x           (GpioPortC<<16u|GpioPin9 <<8u|GpioAf2)
#define PC10_LPUART0_TXD  (GpioPortC<<16u|GpioPin10<<8u|GpioAf2)
#define PC11_LPUART0_RXD  (GpioPortC<<16u|GpioPin11<<8u|GpioAf2)
#define PC12_LPUART1_TXD  (GpioPortC<<16u|GpioPin12<<8u|GpioAf2)
#define PC13_RTC_1HZ      (GpioPortC<<16u|GpioPin13<<8u|GpioAf2)
#define PC14_USART0_SCK   (GpioPortC<<16u|GpioPin14<<8u|GpioAf2)
#define PC15_USART1_SCK   (GpioPortC<<16u|GpioPin15<<8u|GpioAf2)
#define PD00_CTRIM_ETRTOG (GpioPortD<<16u|GpioPin0 <<8u|GpioAf2)
#define PD01_2x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf2)
#define PD02_LPUART0_RTS  (GpioPortD<<16u|GpioPin2 <<8u|GpioAf2)
#define PD03_2x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf2)
#define PD04_2x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf2)
#define PD05_2x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf2)
#define PD06_LPUART1_CTS  (GpioPortD<<16u|GpioPin6 <<8u|GpioAf2)
#define PD07_LPUART1_RTS  (GpioPortD<<16u|GpioPin7 <<8u|GpioAf2)
/**
 * @}
 */

/**
 * @defgroup GPIO_AF3_Macros GPIO复用功能AF3宏定义
 * @{
 */
#define PA00_TIM0_ETR     (GpioPortA<<16u|GpioPin0 <<8u|GpioAf3)
#define PA01_TIM0_CHB     (GpioPortA<<16u|GpioPin1 <<8u|GpioAf3)
#define PA02_VC1_OUT      (GpioPortA<<16u|GpioPin2 <<8u|GpioAf3)
#define PA03_TIM1_CHB     (GpioPortA<<16u|GpioPin3 <<8u|GpioAf3)
#define PA04_LPUART1_RTS  (GpioPortA<<16u|GpioPin4 <<8u|GpioAf3)
#define PA05_LPUART1_CTS  (GpioPortA<<16u|GpioPin5 <<8u|GpioAf3)
#define PA06_TIM3_BK      (GpioPortA<<16u|GpioPin6 <<8u|GpioAf3)
#define PA07_HCLK_OUT     (GpioPortA<<16u|GpioPin7 <<8u|GpioAf3)
#define PA08_CTRIM_ETRTOG (GpioPortA<<16u|GpioPin8 <<8u|GpioAf3)
#define PA09_TIM0_BK      (GpioPortA<<16u|GpioPin9 <<8u|GpioAf3)
#define PA10_TIM2_BK      (GpioPortA<<16u|GpioPin10<<8u|GpioAf3)
#define PA11_I2C1_SCL     (GpioPortA<<16u|GpioPin11<<8u|GpioAf3)
#define PA12_I2C1_SDA     (GpioPortA<<16u|GpioPin12<<8u|GpioAf3)
#define PA13_LVD_OUT      (GpioPortA<<16u|GpioPin13<<8u|GpioAf3)
#define PA14_TIM3_CH2A    (GpioPortA<<16u|GpioPin14<<8u|GpioAf3)
#define PA15_LPUART1_RTS  (GpioPortA<<16u|GpioPin15<<8u|GpioAf3)
#define PB00_LPUART0_TXD  (GpioPortB<<16u|GpioPin0 <<8u|GpioAf3)
#define PB01_TIM3_CH2B    (GpioPortB<<16u|GpioPin1 <<8u|GpioAf3)
#define PB02_LPUART1_TXD  (GpioPortB<<16u|GpioPin2 <<8u|GpioAf3)
#define PB03_TIM1_GATE    (GpioPortB<<16u|GpioPin3 <<8u|GpioAf3)
#define PB04_TIM2_BK      (GpioPortB<<16u|GpioPin4 <<8u|GpioAf3)
#define PB05_TIM1_BK      (GpioPortB<<16u|GpioPin5 <<8u|GpioAf3)
#define PB06_TIM1_CHB     (GpioPortB<<16u|GpioPin6 <<8u|GpioAf3)
#define PB07_TIM2_CHB     (GpioPortB<<16u|GpioPin7 <<8u|GpioAf3)
#define PB08_USART1_SCK   (GpioPortB<<16u|GpioPin8 <<8u|GpioAf3)
#define PB09_SPI1_CS      (GpioPortB<<16u|GpioPin9 <<8u|GpioAf3)
#define PB10_TIM1_CHA     (GpioPortB<<16u|GpioPin10<<8u|GpioAf3)
#define PB11_LPUART0_RXD  (GpioPortB<<16u|GpioPin11<<8u|GpioAf3)
#define PB12_LPUART0_TXD  (GpioPortB<<16u|GpioPin12<<8u|GpioAf3)
#define PB13_TIM3_CH0B    (GpioPortB<<16u|GpioPin13<<8u|GpioAf3)
#define PB14_TIM3_CH1B    (GpioPortB<<16u|GpioPin14<<8u|GpioAf3)
#define PB15_TIM0_CHB     (GpioPortB<<16u|GpioPin15<<8u|GpioAf3)
#define PC00_USART1_CTS   (GpioPortC<<16u|GpioPin0 <<8u|GpioAf3)
#define PC01_USART1_RTS   (GpioPortC<<16u|GpioPin1 <<8u|GpioAf3)
#define PC02_3x           (GpioPortC<<16u|GpioPin2 <<8u|GpioAf3)
#define PC03_LPTIM0_TOGN  (GpioPortC<<16u|GpioPin3 <<8u|GpioAf3)
#define PC04_IR_OUT       (GpioPortC<<16u|GpioPin4 <<8u|GpioAf3)
#define PC05_3x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf3)
#define PC06_TIM2_CHA     (GpioPortC<<16u|GpioPin6 <<8u|GpioAf3)
#define PC07_TIM2_CHB     (GpioPortC<<16u|GpioPin7 <<8u|GpioAf3)
#define PC08_TIM2_ETR     (GpioPortC<<16u|GpioPin8 <<8u|GpioAf3)
#define PC09_TIM1_ETR     (GpioPortC<<16u|GpioPin9 <<8u|GpioAf3)
#define PC10_3x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf3)
#define PC11_3x           (GpioPortC<<16u|GpioPin11<<8u|GpioAf3)
#define PC12_3x           (GpioPortC<<16u|GpioPin12<<8u|GpioAf3)
#define PC13_TIM3_CH1B    (GpioPortC<<16u|GpioPin13<<8u|GpioAf3)
#define PC14_3x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf3)
#define PC15_3x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf3)
#define PD00_USART1_TXD   (GpioPortD<<16u|GpioPin0 <<8u|GpioAf3)
#define PD01_USART1_RXD   (GpioPortD<<16u|GpioPin1 <<8u|GpioAf3)
#define PD02_TIM1_ETR     (GpioPortD<<16u|GpioPin2 <<8u|GpioAf3)
#define PD03_3x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf3)
#define PD04_LPTIM1_TOGN  (GpioPortD<<16u|GpioPin4 <<8u|GpioAf3)
#define PD05_LPTIM1_TOG   (GpioPortD<<16u|GpioPin5 <<8u|GpioAf3)
#define PD06_USART0_CTS   (GpioPortD<<16u|GpioPin6 <<8u|GpioAf3)
#define PD07_USART0_RTS   (GpioPortD<<16u|GpioPin7 <<8u|GpioAf3)
/**
 * @}
 */

/**
 * @defgroup GPIO_AF4_Macros GPIO复用功能AF4宏定义
 * @{
 */
#define PA00_VC0_OUT      (GpioPortA<<16u|GpioPin0 <<8u|GpioAf4)
#define PA01_TIM1_ETR     (GpioPortA<<16u|GpioPin1 <<8u|GpioAf4)
#define PA02_TIM1_CHA     (GpioPortA<<16u|GpioPin2 <<8u|GpioAf4)
#define PA03_TIM2_CHB     (GpioPortA<<16u|GpioPin3 <<8u|GpioAf4)
#define PA04_TIM2_ETR     (GpioPortA<<16u|GpioPin4 <<8u|GpioAf4)
#define PA05_TIM0_CHA     (GpioPortA<<16u|GpioPin5 <<8u|GpioAf4)
#define PA06_TIM1_CHA     (GpioPortA<<16u|GpioPin6 <<8u|GpioAf4)
#define PA07_TIM3_CH0B    (GpioPortA<<16u|GpioPin7 <<8u|GpioAf4)
#define PA08_LPTIM1_ETR   (GpioPortA<<16u|GpioPin8 <<8u|GpioAf4)
#define PA09_I2C0_SCL     (GpioPortA<<16u|GpioPin9 <<8u|GpioAf4)
#define PA10_I2C0_SDA     (GpioPortA<<16u|GpioPin10<<8u|GpioAf4)
#define PA11_HSI2C_SCL    (GpioPortA<<16u|GpioPin11<<8u|GpioAf4)
#define PA12_HSI2C_SDA    (GpioPortA<<16u|GpioPin12<<8u|GpioAf4)
#define PA13_TIM3_ETR     (GpioPortA<<16u|GpioPin13<<8u|GpioAf4)
#define PA14_LVD_OUT      (GpioPortA<<16u|GpioPin14<<8u|GpioAf4)
#define PA15_TIM0_ETR     (GpioPortA<<16u|GpioPin15<<8u|GpioAf4)
#define PB00_LPTIM1_TOG   (GpioPortB<<16u|GpioPin0 <<8u|GpioAf4)
#define PB01_4x           (GpioPortB<<16u|GpioPin1 <<8u|GpioAf4)
#define PB02_4x           (GpioPortB<<16u|GpioPin2 <<8u|GpioAf4)
#define PB03_TIM3_CH0A    (GpioPortB<<16u|GpioPin3 <<8u|GpioAf4)
#define PB04_USART0_CTS   (GpioPortB<<16u|GpioPin4 <<8u|GpioAf4)
#define PB05_4x           (GpioPortB<<16u|GpioPin5 <<8u|GpioAf4)
#define PB06_TIM0_CHA     (GpioPortB<<16u|GpioPin6 <<8u|GpioAf4)
#define PB07_LPUART1_CTS  (GpioPortB<<16u|GpioPin7 <<8u|GpioAf4)
#define PB08_TIM2_CHA     (GpioPortB<<16u|GpioPin8 <<8u|GpioAf4)
#define PB09_TIM2_CHA     (GpioPortB<<16u|GpioPin9 <<8u|GpioAf4)
#define PB10_LPUART0_TXD  (GpioPortB<<16u|GpioPin10<<8u|GpioAf4)
#define PB11_TIM2_GATE    (GpioPortB<<16u|GpioPin11<<8u|GpioAf4)
#define PB12_TIM0_BK      (GpioPortB<<16u|GpioPin12<<8u|GpioAf4)
#define PB13_LPUART0_CTS  (GpioPortB<<16u|GpioPin13<<8u|GpioAf4)
#define PB14_TIM0_CHA     (GpioPortB<<16u|GpioPin14<<8u|GpioAf4)
#define PB15_TIM0_GATE    (GpioPortB<<16u|GpioPin15<<8u|GpioAf4)
#define PC00_HSI2C_SCL    (GpioPortC<<16u|GpioPin0 <<8u|GpioAf4)
#define PC01_HSI2C_SDA    (GpioPortC<<16u|GpioPin1 <<8u|GpioAf4)
#define PC02_4x           (GpioPortC<<16u|GpioPin2 <<8u|GpioAf4)
#define PC03_4x           (GpioPortC<<16u|GpioPin3 <<8u|GpioAf4)
#define PC04_4x           (GpioPortC<<16u|GpioPin4 <<8u|GpioAf4)
#define PC05_4x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf4)
#define PC06_LPTIM1_GATE  (GpioPortC<<16u|GpioPin6 <<8u|GpioAf4)
#define PC07_LPTIM1_ETR   (GpioPortC<<16u|GpioPin7 <<8u|GpioAf4)
#define PC08_LPTIM1_TOG   (GpioPortC<<16u|GpioPin8 <<8u|GpioAf4)
#define PC09_LPTIM1_TOGN  (GpioPortC<<16u|GpioPin9 <<8u|GpioAf4)
#define PC10_4x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf4)
#define PC11_4x           (GpioPortC<<16u|GpioPin11<<8u|GpioAf4)
#define PC12_4x           (GpioPortC<<16u|GpioPin12<<8u|GpioAf4)
#define PC13_4x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf4)
#define PC14_LPTIM1_TOGN  (GpioPortC<<16u|GpioPin14<<8u|GpioAf4)
#define PC15_LPTIM1_GATE  (GpioPortC<<16u|GpioPin15<<8u|GpioAf4)
#define PD00_4x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf4)
#define PD01_4x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf4)
#define PD02_HSI2C_SCL    (GpioPortD<<16u|GpioPin2 <<8u|GpioAf4)
#define PD03_4x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf4)
#define PD04_4x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf4)
#define PD05_HSI2C_SDA    (GpioPortD<<16u|GpioPin5 <<8u|GpioAf4)
#define PD06_LPTIM1_GATE  (GpioPortD<<16u|GpioPin6 <<8u|GpioAf4)
#define PD07_LPTIM1_TOGN  (GpioPortD<<16u|GpioPin7 <<8u|GpioAf4)
/**
 * @}
 */

/**
 * @defgroup GPIO_AF5_Macros GPIO复用功能AF5宏定义
 * @{
 */
#define PA00_TIM1_CHA     (GpioPortA<<16u|GpioPin0 <<8u|GpioAf5)
#define PA01_TIM1_CHB     (GpioPortA<<16u|GpioPin1 <<8u|GpioAf5)
#define PA02_TIM2_CHA     (GpioPortA<<16u|GpioPin2 <<8u|GpioAf5)
#define PA03_SPI1_CS      (GpioPortA<<16u|GpioPin3 <<8u|GpioAf5)
#define PA04_5x           (GpioPortA<<16u|GpioPin4 <<8u|GpioAf5)
#define PA05_USART1_RTS   (GpioPortA<<16u|GpioPin5 <<8u|GpioAf5)
#define PA06_VC0_OUT      (GpioPortA<<16u|GpioPin6 <<8u|GpioAf5)
#define PA07_TIM2_CHA     (GpioPortA<<16u|GpioPin7 <<8u|GpioAf5)
#define PA08_TIM1_GATE    (GpioPortA<<16u|GpioPin8 <<8u|GpioAf5)
#define PA09_LPUART0_TXD  (GpioPortA<<16u|GpioPin9 <<8u|GpioAf5)
#define PA10_TIM2_GATE    (GpioPortA<<16u|GpioPin10<<8u|GpioAf5)
#define PA11_VC0_OUT      (GpioPortA<<16u|GpioPin11<<8u|GpioAf5)
#define PA12_VC1_OUT      (GpioPortA<<16u|GpioPin12<<8u|GpioAf5)
#define PA13_RTC_1HZ      (GpioPortA<<16u|GpioPin13<<8u|GpioAf5)
#define PA14_RCH_OUT      (GpioPortA<<16u|GpioPin14<<8u|GpioAf5)
#define PA15_TIM0_CHA     (GpioPortA<<16u|GpioPin15<<8u|GpioAf5)
#define PB00_RCH_OUT      (GpioPortB<<16u|GpioPin0 <<8u|GpioAf5)
#define PB01_LPUART0_RTS  (GpioPortB<<16u|GpioPin1 <<8u|GpioAf5)
#define PB02_TIM1_BK      (GpioPortB<<16u|GpioPin2 <<8u|GpioAf5)
#define PB03_LPTIM0_GATE  (GpioPortB<<16u|GpioPin3 <<8u|GpioAf5)
#define PB04_TIM2_GATE    (GpioPortB<<16u|GpioPin4 <<8u|GpioAf5)
#define PB05_LPTIM0_GATE  (GpioPortB<<16u|GpioPin5 <<8u|GpioAf5)
#define PB06_LPTIM0_ETR   (GpioPortB<<16u|GpioPin6 <<8u|GpioAf5)
#define PB07_TIM0_CHB     (GpioPortB<<16u|GpioPin7 <<8u|GpioAf5)
#define PB08_TIM0_GATE    (GpioPortB<<16u|GpioPin8 <<8u|GpioAf5)
#define PB09_HSI2C_SDA    (GpioPortB<<16u|GpioPin9 <<8u|GpioAf5)
#define PB10_TIM3_CH1A    (GpioPortB<<16u|GpioPin10<<8u|GpioAf5)
#define PB11_5x           (GpioPortB<<16u|GpioPin11<<8u|GpioAf5)
#define PB12_USART0_SCK   (GpioPortB<<16u|GpioPin12<<8u|GpioAf5)
#define PB13_TIM1_CHA     (GpioPortB<<16u|GpioPin13<<8u|GpioAf5)
#define PB14_RTC_1HZ      (GpioPortB<<16u|GpioPin14<<8u|GpioAf5)
#define PB15_5x           (GpioPortB<<16u|GpioPin15<<8u|GpioAf5)
#define PC00_5x           (GpioPortC<<16u|GpioPin0 <<8u|GpioAf5)
#define PC01_5x           (GpioPortC<<16u|GpioPin1 <<8u|GpioAf5)
#define PC02_5x           (GpioPortC<<16u|GpioPin2 <<8u|GpioAf5)
#define PC03_5x           (GpioPortC<<16u|GpioPin3 <<8u|GpioAf5)
#define PC04_5x           (GpioPortC<<16u|GpioPin4 <<8u|GpioAf5)
#define PC05_5x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf5)
#define PC06_5x           (GpioPortC<<16u|GpioPin6 <<8u|GpioAf5)
#define PC07_5x           (GpioPortC<<16u|GpioPin7 <<8u|GpioAf5)
#define PC08_5x           (GpioPortC<<16u|GpioPin8 <<8u|GpioAf5)
#define PC09_5x           (GpioPortC<<16u|GpioPin9 <<8u|GpioAf5)
#define PC10_5x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf5)
#define PC11_5x           (GpioPortC<<16u|GpioPin11<<8u|GpioAf5)
#define PC12_5x           (GpioPortC<<16u|GpioPin12<<8u|GpioAf5)
#define PC13_5x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf5)
#define PC14_5x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf5)
#define PC15_5x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf5)
#define PD00_5x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf5)
#define PD01_5x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf5)
#define PD02_5x           (GpioPortD<<16u|GpioPin2 <<8u|GpioAf5)
#define PD03_5x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf5)
#define PD04_5x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf5)
#define PD05_5x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf5)
#define PD06_5x           (GpioPortD<<16u|GpioPin6 <<8u|GpioAf5)
#define PD07_5x           (GpioPortD<<16u|GpioPin7 <<8u|GpioAf5)
/**
 * @}
 */

/**
 * @defgroup GPIO_AF6_Macros GPIO复用功能AF6宏定义
 * @{
 */
#define PA00_TIM3_ETR     (GpioPortA<<16u|GpioPin0 <<8u|GpioAf6)
#define PA01_HCLK_OUT     (GpioPortA<<16u|GpioPin1 <<8u|GpioAf6)
#define PA02_PCLK_OUT     (GpioPortA<<16u|GpioPin2 <<8u|GpioAf6)
#define PA03_TIM3_CH1A    (GpioPortA<<16u|GpioPin3 <<8u|GpioAf6)
#define PA04_LVD_OUT      (GpioPortA<<16u|GpioPin4 <<8u|GpioAf6)
#define PA05_XTL_OUT      (GpioPortA<<16u|GpioPin5 <<8u|GpioAf6)
#define PA06_TIM3_GATE    (GpioPortA<<16u|GpioPin6 <<8u|GpioAf6)
#define PA07_VC1_OUT      (GpioPortA<<16u|GpioPin7 <<8u|GpioAf6)
#define PA08_6x           (GpioPortA<<16u|GpioPin8 <<8u|GpioAf6)
#define PA09_HCLK_OUT     (GpioPortA<<16u|GpioPin9 <<8u|GpioAf6)
#define PA10_PCLK_OUT     (GpioPortA<<16u|GpioPin10<<8u|GpioAf6)
#define PA11_SPI0_MISO    (GpioPortA<<16u|GpioPin11<<8u|GpioAf6)
#define PA12_SPI0_MOSI    (GpioPortA<<16u|GpioPin12<<8u|GpioAf6)
#define PA13_I2C1_SDA     (GpioPortA<<16u|GpioPin13<<8u|GpioAf6)
#define PA14_RCL_OUT      (GpioPortA<<16u|GpioPin14<<8u|GpioAf6)
#define PA15_TIM3_CH1A    (GpioPortA<<16u|GpioPin15<<8u|GpioAf6)
#define PB00_RCL_OUT      (GpioPortB<<16u|GpioPin0 <<8u|GpioAf6)
#define PB01_LPTIM1_ETR   (GpioPortB<<16u|GpioPin1 <<8u|GpioAf6)
#define PB02_TIM0_BK      (GpioPortB<<16u|GpioPin2 <<8u|GpioAf6)
#define PB03_XTL_OUT      (GpioPortB<<16u|GpioPin3 <<8u|GpioAf6)
#define PB04_TIM3_CH0B    (GpioPortB<<16u|GpioPin4 <<8u|GpioAf6)
#define PB05_6x           (GpioPortB<<16u|GpioPin5 <<8u|GpioAf6)
#define PB06_TIM3_CH0A    (GpioPortB<<16u|GpioPin6 <<8u|GpioAf6)
#define PB07_LPTIM0_TOGN  (GpioPortB<<16u|GpioPin7 <<8u|GpioAf6)
#define PB08_TIM3_CH2A    (GpioPortB<<16u|GpioPin8 <<8u|GpioAf6)
#define PB09_TIM2_CHB     (GpioPortB<<16u|GpioPin9 <<8u|GpioAf6)
#define PB10_LPUART1_RTS  (GpioPortB<<16u|GpioPin10<<8u|GpioAf6)
#define PB11_LPUART1_CTS  (GpioPortB<<16u|GpioPin11<<8u|GpioAf6)
#define PB12_LPUART0_RTS  (GpioPortB<<16u|GpioPin12<<8u|GpioAf6)
#define PB13_TIM1_GATE    (GpioPortB<<16u|GpioPin13<<8u|GpioAf6)
#define PB14_LPUART0_RTS  (GpioPortB<<16u|GpioPin14<<8u|GpioAf6)
#define PB15_6x           (GpioPortB<<16u|GpioPin15<<8u|GpioAf6)
#define PC00_6x           (GpioPortC<<16u|GpioPin0 <<8u|GpioAf6)
#define PC01_6x           (GpioPortC<<16u|GpioPin1 <<8u|GpioAf6)
#define PC02_6x           (GpioPortC<<16u|GpioPin2 <<8u|GpioAf6)
#define PC03_6x           (GpioPortC<<16u|GpioPin3 <<8u|GpioAf6)
#define PC04_6x           (GpioPortC<<16u|GpioPin4 <<8u|GpioAf6)
#define PC05_6x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf6)
#define PC06_LPUART2_RXD  (GpioPortC<<16u|GpioPin6 <<8u|GpioAf6)
#define PC07_LPUART2_TXD  (GpioPortC<<16u|GpioPin7 <<8u|GpioAf6)
#define PC08_LPUART2_CTS  (GpioPortC<<16u|GpioPin8 <<8u|GpioAf6)
#define PC09_LPUART2_RTS  (GpioPortC<<16u|GpioPin9 <<8u|GpioAf6)
#define PC10_6x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf6)
#define PC11_6x           (GpioPortC<<16u|GpioPin11<<8u|GpioAf6)
#define PC12_6x           (GpioPortC<<16u|GpioPin12<<8u|GpioAf6)
#define PC13_6x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf6)
#define PC14_6x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf6)
#define PC15_6x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf6)
#define PD00_LPUART2_RXD  (GpioPortD<<16u|GpioPin0 <<8u|GpioAf6)
#define PD01_LPUART2_TXD  (GpioPortD<<16u|GpioPin1 <<8u|GpioAf6)
#define PD02_6x           (GpioPortD<<16u|GpioPin2 <<8u|GpioAf6)
#define PD03_6x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf6)
#define PD04_6x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf6)
#define PD05_6x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf6)
#define PD06_LPUART2_CTS  (GpioPortD<<16u|GpioPin6 <<8u|GpioAf6)
#define PD07_LPUART2_RTS  (GpioPortD<<16u|GpioPin7 <<8u|GpioAf6)
/**
 * @}
 */

/**
 * @defgroup GPIO_AF7_Macros GPIO复用功能AF7宏定义
 * @{
 */
#define PA00_TIM0_CHA     (GpioPortA<<16u|GpioPin0 <<8u|GpioAf7)
#define PA01_SPI1_MOSI    (GpioPortA<<16u|GpioPin1 <<8u|GpioAf7)
#define PA02_SPI1_MISO    (GpioPortA<<16u|GpioPin2 <<8u|GpioAf7)
#define PA03_7x           (GpioPortA<<16u|GpioPin3 <<8u|GpioAf7)
#define PA04_TIM3_CH2B    (GpioPortA<<16u|GpioPin4 <<8u|GpioAf7)
#define PA05_XTH_OUT      (GpioPortA<<16u|GpioPin5 <<8u|GpioAf7)
#define PA06_LPUART0_CTS  (GpioPortA<<16u|GpioPin6 <<8u|GpioAf7)
#define PA07_LPUART0_RXD  (GpioPortA<<16u|GpioPin7 <<8u|GpioAf7)
#define PA08_TIM3_BK      (GpioPortA<<16u|GpioPin8 <<8u|GpioAf7)
#define PA09_TIM3_CH0A    (GpioPortA<<16u|GpioPin9 <<8u|GpioAf7)
#define PA10_TIM0_CHB     (GpioPortA<<16u|GpioPin10<<8u|GpioAf7)
#define PA11_CTRIM_ETRTOG (GpioPortA<<16u|GpioPin11<<8u|GpioAf7)
#define PA12_7x           (GpioPortA<<16u|GpioPin12<<8u|GpioAf7)
#define PA13_USART1_SCK   (GpioPortA<<16u|GpioPin13<<8u|GpioAf7)
#define PA14_I2C1_SCL     (GpioPortA<<16u|GpioPin14<<8u|GpioAf7)
#define PA15_USART0_SCK   (GpioPortA<<16u|GpioPin15<<8u|GpioAf7)
#define PB00_7x           (GpioPortB<<16u|GpioPin0 <<8u|GpioAf7)
#define PB01_TCLK_OUT     (GpioPortB<<16u|GpioPin1 <<8u|GpioAf7)
#define PB02_TIM2_BK      (GpioPortB<<16u|GpioPin2 <<8u|GpioAf7)
#define PB03_XTH_OUT      (GpioPortB<<16u|GpioPin3 <<8u|GpioAf7)
#define PB04_LPTIM0_ETR   (GpioPortB<<16u|GpioPin4 <<8u|GpioAf7)
#define PB05_USART0_RTS   (GpioPortB<<16u|GpioPin5 <<8u|GpioAf7)
#define PB06_LPTIM0_TOG   (GpioPortB<<16u|GpioPin6 <<8u|GpioAf7)
#define PB07_7x           (GpioPortB<<16u|GpioPin7 <<8u|GpioAf7)
#define PB08_USART0_TXD   (GpioPortB<<16u|GpioPin8 <<8u|GpioAf7)
#define PB09_USART0_RXD   (GpioPortB<<16u|GpioPin9 <<8u|GpioAf7)
#define PB10_USART1_RTS   (GpioPortB<<16u|GpioPin10<<8u|GpioAf7)
#define PB11_USART1_CTS   (GpioPortB<<16u|GpioPin11<<8u|GpioAf7)
#define PB12_7x           (GpioPortB<<16u|GpioPin12<<8u|GpioAf7)
#define PB13_7x           (GpioPortB<<16u|GpioPin13<<8u|GpioAf7)
#define PB14_TIM1_BK      (GpioPortB<<16u|GpioPin14<<8u|GpioAf7)
#define PB15_LPUART1_RXD  (GpioPortB<<16u|GpioPin15<<8u|GpioAf7)
#define PC00_7x           (GpioPortC<<16u|GpioPin0 <<8u|GpioAf7)
#define PC01_7x           (GpioPortC<<16u|GpioPin1 <<8u|GpioAf7)
#define PC02_7x           (GpioPortC<<16u|GpioPin2 <<8u|GpioAf7)
#define PC03_7x           (GpioPortC<<16u|GpioPin3 <<8u|GpioAf7)
#define PC04_7x           (GpioPortC<<16u|GpioPin4 <<8u|GpioAf7)
#define PC05_7x           (GpioPortC<<16u|GpioPin5 <<8u|GpioAf7)
#define PC06_7x           (GpioPortC<<16u|GpioPin6 <<8u|GpioAf7)
#define PC07_7x           (GpioPortC<<16u|GpioPin7 <<8u|GpioAf7)
#define PC08_7x           (GpioPortC<<16u|GpioPin8 <<8u|GpioAf7)
#define PC09_7x           (GpioPortC<<16u|GpioPin9 <<8u|GpioAf7)
#define PC10_7x           (GpioPortC<<16u|GpioPin10<<8u|GpioAf7)
#define PC11_7x           (GpioPortC<<16u|GpioPin11<<8u|GpioAf7)
#define PC12_7x           (GpioPortC<<16u|GpioPin12<<8u|GpioAf7)
#define PC13_7x           (GpioPortC<<16u|GpioPin13<<8u|GpioAf7)
#define PC14_7x           (GpioPortC<<16u|GpioPin14<<8u|GpioAf7)
#define PC15_7x           (GpioPortC<<16u|GpioPin15<<8u|GpioAf7)
#define PD00_7x           (GpioPortD<<16u|GpioPin0 <<8u|GpioAf7)
#define PD01_7x           (GpioPortD<<16u|GpioPin1 <<8u|GpioAf7)
#define PD02_7x           (GpioPortD<<16u|GpioPin2 <<8u|GpioAf7)
#define PD03_7x           (GpioPortD<<16u|GpioPin3 <<8u|GpioAf7)
#define PD04_7x           (GpioPortD<<16u|GpioPin4 <<8u|GpioAf7)
#define PD05_7x           (GpioPortD<<16u|GpioPin5 <<8u|GpioAf7)
#define PD06_7x           (GpioPortD<<16u|GpioPin6 <<8u|GpioAf7)
#define PD07_7x           (GpioPortD<<16u|GpioPin7 <<8u|GpioAf7)
/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GPIO_Local_Types GPIO 局部类型定义
 * @{
 */
typedef uint32_t GpioPinMux;
/**
 * @}
 */
 
/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup GPIO_Global_Functions GPIO全局函数定义
 * @{
 */
/**
* @brief GPIO IO初始化
*/
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_cfg_t *pstcGpioCfg);
/**
 * @brief GPIO 获取端口输入电平
 */
boolean_t   Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
/**
 * @brief GPIO Port输入数据获取
 */
uint16_t Gpio_GetInputData(en_gpio_port_t enPort);
/**
 * @brief GPIO 端口输出电平配置
 */
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal);
/**
 * @brief GPIO 端口输出电平获取
 */
boolean_t   Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
/**
 * @brief GPIO PORT输出电平置位
 */
en_result_t Gpio_SetPort(en_gpio_port_t enPort, uint16_t u16ValMsk);
/**
 * @brief GPIO 端口输出电平置位
 */
en_result_t Gpio_SetIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
/**
 * @brief GPIO PORT输出电平清零
 */
en_result_t Gpio_ClrPort(en_gpio_port_t enPort, uint16_t u16ValMsk);
/**
 * @brief GPIO 端口输出电平清零
 */
en_result_t Gpio_ClrIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
/**
 * @brief GPIO 端口输出电平置位与清零设置
 */
en_result_t Gpio_SetClrPort(en_gpio_port_t enPort, uint32_t u32ValMsk);
/**
 * @brief GPIO 设置端口为模拟功能
 */
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin);
/**
 * @brief GPIO 设置端口为数字功能
 */
en_result_t Gpio_SetDigitalMode(en_gpio_port_t enPort, en_gpio_pin_t enPin);
/**
 * @brief GPIO 设置端口复用功能
 */
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf);
/**
 * @brief GPIO 设置端口复用功能
 */
void Gpio_SetAfMode_Lite(GpioPinMux PinMux);
/**
 * @brief GPIO 端口中断控制功能使能
 */
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
/**
 * @brief GPIO 端口中断控制功能关闭
 */
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
/**
 * @brief GPIO 中断状态获取
 */
boolean_t   Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin);
/**
 * @brief GPIO 中断标志清除
 */
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin);

/**
 * @brief GPIO IR输出极性配置
 */
en_result_t Gpio_SfIrPolCfg(en_gpio_sf_irpol_t enIrPolMode);

/**
 * @brief GPIO HCLK输出配置
 */
en_result_t Gpio_SfHClkOutputCfg(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv);
/**
 * @brief GPIO PCLK输出配置
 */
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv);
/**
 * @brief GPIO TCLK输出配置
 */
en_result_t Gpio_SfTclkOutputCfg(en_gpio_sf_tlcksel_t enSel, en_gpio_sf_tlckdiv_t enDiv);
/**
 * @brief GPIO Timer 门控输入配置
 */
en_result_t Gpio_SfTimGCfg(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf);
/**
 * @brief GPIO Timer ETR选择配置
 */
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf);
/**
 * @brief GPIO Timer 捕获输入配置
 */
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf);
/**
 * @brief GPIO HSI2C 端口有效电平选择
 */
en_result_t Gpio_Hsi2cLevelSel(en_gpio_sf_hsi2c_t enIoLevel);
/**
 * @brief GPIO 端口滤波配置
 */
en_result_t Gpio_FltCfg(stc_gpio_flt_cfg_t *pstcCfg);

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

#endif /* __GPIO_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
