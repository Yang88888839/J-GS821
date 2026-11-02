/**
 ******************************************************************************
 * @file   lcd.h
 *
 * @brief This file contains all the functions prototypes of the LCD driver
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

#ifndef __LCD_H__
#define __LCD_H__
/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_LCD LCD模块驱动库
 * @{
 */
/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

/******************************************************************************
 ** Global type definitions
 *****************************************************************************/
/**
 * @defgroup LCD_Global_Types LCD全局类型定义
 * @{
 */

/**
 * @brief  LCD bias电压源选择(CR0.BSEL)
 */
typedef enum
{
    LcdInResHighPower   = 6,    /*!< 内部电阻分压，大功耗模式 */
    LcdInResLowPower    = 4,    /*!< 内部电阻分压，小功耗模式 */
    LcdInResMidPower    = 2,    /*!< 内部电阻分压，中功耗模式 */
    LcdExtCap           = 1,    /*!< 电容分压模式，需要外部电路配合 */
    LcdExtRes           = 0,    /*!< 外部电阻模式，需要外部电路配合 */
} en_lcd_biassrc_t;

/**
 * @brief  LCD duty选择(CR0.DUTY)
 */
typedef enum
{
    LcdStatic = 0u,        /*!< 静态显示 */
    LcdDuty2  = 1u,        /*!< 1/2duty */
    LcdDuty3  = 2u,        /*!< 1/3duty */
    LcdDuty4  = 3u,        /*!< 1/4duty */
    LcdDuty6  = 5u,        /*!< 1/6duty */
    LcdDuty8  = 7u,        /*!< 1/8duty */
} en_lcd_duty_t;

/**
 * @brief  LCD bias配置位(CR0.BIAS)
 */
typedef enum
{
    LcdBias2 = 0u,        /*!< 1/2 BIAS */    
    LcdBias3 = 1u,        /*!< 1/3 BIAS */
    LcdBias4 = 2u,        /*!< 1/4 BIAS */
} en_lcd_bias_t;

/**
 * @brief  LCD 电压泵时钟频率选择(CR0.CPCLLK)
 */
typedef enum
{
    LcdCpFinClkDiv16  = 0u,        /*!< 电压泵时钟频率 FinClk/16 */
    LcdCpFinClkDiv8   = 1u,        /*!< 电压泵时钟频率 FinClk/8 */
    LcdCpFinClkDiv4   = 2u,        /*!< 电压泵时钟频率 FinClk/4 */
    LcdCpFinClkDiv2   = 3u         /*!< 电压泵时钟频率 FinClk/2 */
} en_lcd_cpclk_t;


/**
 * @brief  LCD 使能控制(CR0.EN)
 */
typedef enum
{
    LcdEnable   = 1u,   /*!< LCD使能 */
    LcdDisable  = 0u    /*!< LCD禁止 */
} en_lcd_en_t;

/**
* @brief  LCD 死区时间配置(CR1.DEAD)
 */
typedef enum
{
    LcdDeadTimeOff    = 0u,  /*!< 无死区时间 */
    LcdDeadTime1Cycle = 1u,  /*!< 1相周期死区时间 */
    LcdDeadTime2Cycle = 2u,  /*!< 2相周期死区时间 */
    LcdDeadTime3Cycle = 3u,  /*!< 3相周期死区时间 */
    LcdDeadTime4Cycle = 4u,  /*!< 4相周期死区时间 */
    LcdDeadTime5Cycle = 5u,  /*!< 5相周期死区时间 */
    LcdDeadTime6Cycle = 6u,  /*!< 6相周期死区时间 */
    LcdDeadTime7Cycle = 7u,  /*!< 7相周期死区时间 */
} en_lcd_dead_time_t;

/**
 * @brief  LCD 时钟PSC预分频器配置(CR1.PSC)
 */
typedef enum
{
    LcdInClkPsc2    = 0u,  /*!< SLCD时钟预分配 Finclk/2 */
    LcdInClkPsc4    = 1u,  /*!< SLCD时钟预分配 Finclk/4 */
    LcdInClkPsc8    = 2u,  /*!< SLCD时钟预分配 Finclk/8 */
    LcdInClkPsc16   = 3u,  /*!< SLCD时钟预分配 Finclk/16 */
    LcdInClkPsc32   = 4u,  /*!< SLCD时钟预分配 Finclk/32 */
} en_lcd_psc_t;

/**
 * @brief  LCD 时钟DIV分频器配置(CR1.DIV)
 */
typedef enum
{
    LcdClkDiv16   = 0u,  /*!< FpscClk 16分频 */
    LcdClkDiv17   = 1u,  /*!< FpscClk 17分频 */
    LcdClkDiv18   = 2u,  /*!< FpscClk 18分频 */
    LcdClkDiv19   = 3u,  /*!< FpscClk 19分频 */
    LcdClkDiv20   = 4u,  /*!< FpscClk 20分频 */
    LcdClkDiv21   = 5u,  /*!< FpscClk 21分频 */
    LcdClkDiv22   = 6u,  /*!< FpscClk 22分频 */
    LcdClkDiv23   = 7u,  /*!< FpscClk 23分频 */
    LcdClkDiv24   = 8u,  /*!< FpscClk 24分频 */
    LcdClkDiv25   = 9u,  /*!< FpscClk 25分频 */
    LcdClkDiv26   = 10u, /*!< FpscClk 26分频 */
    LcdClkDiv27   = 11u, /*!< FpscClk 27分频 */
    LcdClkDiv28   = 12u, /*!< FpscClk 28分频 */
    LcdClkDiv29   = 13u, /*!< FpscClk 29分频 */
    LcdClkDiv30   = 14u, /*!< FpscClk 30分频 */
    LcdClkDiv31   = 15u, /*!< FpscClk 31分频 */
} en_lcd_div_t;

/**
 * @brief  LCD 电压输出驱动使能(CR0.VODEN)
 */
typedef enum
{
    LcdVolDrvDisable = 0u,  /*!< LCD 电压输出驱动禁止 */
    LcdVolDrvEnable  = 1u,  /*!< LCD 电压输出驱动使能 */
} en_lcd_voden_t;

/**
 * @brief  LCD 电阻强驱脉冲控制(CR1.DRVRES)
 */
typedef enum
{
    LcdDrvResOff       = 0u,  /*!< 关闭 */
    LcdDrvRes1FinClk   = 1u,  /*!< 1个FInClk周期 */
    LcdDrvRes2FinClk   = 2u,  /*!< 2个FInClk周期 */
    LcdDrvRes4FinClk   = 3u,  /*!< 4个FInClk周期 */
    LcdDrvRes8FinClk   = 4u,  /*!< 8个FInClk周期 */
    LcdDrvRes16FinClk  = 5u,  /*!< 16个FInClk周期 */
    LcdDrvRes32FinClk  = 6u,  /*!< 32个FInClk周期 */
    LcdDrvResAllON     = 7u,  /*!< 保持常开 */
} en_lcd_drvres_t;

/**
 * @brief  LCD 显示模式(CR1.MODE)
 */
typedef enum
{
    LcdMode0 = 0,       /*!< 模式0 */
    LcdMode1 = 1,       /*!< 模式1 */
} en_lcd_dispmode_t;

/**
 * @brief  LCD 时钟源选择(CR1.CLKSRC)
 */
typedef enum
{
    LcdRCL = 0,     /*!< 内部RCL */    
    LcdXTL = 1,     /*!< 外部XTL */
} en_lcd_clk_t;

/**
 * @brief  LCD CR1寄存器的使能位、标志位
 */
typedef enum
{
    LcdBlinkEn   = 6u,  /*!< LCD闪屏配置位 */
    LcdIe        = 9u,  /*!< LCD 中断使能位 */
    LcdDmaEn     = 10u, /*!< LCD DMA硬件触发使能位 */
} en_lcd_cr1_t;


/**
 * @brief  LCD 显示SEG COM端口寄存器的配置
 */
typedef struct
{
    uint32_t u32Seg0_31;            /*!< SEG0-31配置 */
    union
    {
        uint32_t seg32_39_com0_7;
        struct
        {
            uint32_t Seg32_35     : 4;
            uint32_t Seg36Com7    : 1;
            uint32_t Seg37Com6    : 1;
            uint32_t Seg38Com5    : 1;
            uint32_t Seg39Com4    : 1;
            uint32_t Reserve      : 12;
            uint32_t Mux          : 1;
            uint32_t Com0_3       : 4;
        } segcom_bit;
    } stc_seg32_39_com0_7_t;        /*!< SEG32-39 和 COM0-7配置 */
} stc_lcd_segcom_t;

/**
 * @brief  LCD 端口配置参数
 */
typedef struct
{
    en_lcd_duty_t LcdDuty;          /*!< 占空比 */
    en_lcd_biassrc_t LcdBiasSrc;    /*!< 时钟源 */
    uint8_t u8MaxSeg;               /*!< 最大SEG口 */
} stc_lcd_segcompara_t;

/**
 * @brief  LCD 初始化配置结构
 */
typedef struct
{
    uint8_t             LcdContrast;    /*!< 对比度设置 范围0~15,0对比度最大，15对比度最小 */
    en_lcd_biassrc_t    LcdBiasSrc;     /*!< 偏置源选择 */
    en_lcd_duty_t       LcdDuty;        /*!< duty配置选择 */
    en_lcd_bias_t       LcdBias;        /*!< 偏压选择 */
    en_lcd_cpclk_t      LcdCpClk;       /*!< 电压泵时钟频率选择 */
    en_lcd_dispmode_t   LcdMode;        /*!< 显示模式选择 */
    en_lcd_clk_t        LcdClkSrc;      /*!< 时钟源选择 */
    en_lcd_voden_t      LcdVolDrv;      /*!< 电压驱动输出控制 */
    en_lcd_drvres_t     LcdDrvRes;      /*!< 电阻强驱脉冲控制 */
    en_lcd_dead_time_t  LcdDeadTime;    /*!< 死区时间选择 */
    en_lcd_psc_t        LcdPscSel;      /*!< 预分频PSC配置 */
    en_lcd_div_t        LcdDivSel;      /*!< 时钟分频DIV配置 */
    en_lcd_en_t         LcdEn;          /*!< LCD使能 */
} stc_lcd_cfg_t;

/**
 * @}
 */

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup LCD_Global_Functions LCD全局函数定义
 * @{
 */

boolean_t Lcd_GetItStatus(void);
void Lcd_ClearItPendingBit(void);
en_result_t Lcd_GetSegCom(stc_lcd_segcompara_t *pstcSegComPara, stc_lcd_segcom_t *pstcSegCom);
void Lcd_SetSegCom(stc_lcd_segcom_t *pstcSegCom);
void Lcd_Init(stc_lcd_cfg_t *pstcLcdCfg);
void Lcd_FullDisp(void);
void Lcd_ClearDisp(void);
en_result_t Lcd_WriteRam(uint8_t u8Row, uint32_t u32Data);
en_result_t Lcd_BlinkCfg(uint8_t u8BlinkCnt, boolean_t bBlinkEn);
en_result_t Lcd_FuncSet(en_lcd_cr1_t enCtrl, boolean_t bEn);

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

#endif /* __LCD_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


