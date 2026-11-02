/**
 *******************************************************************************
 * @file  lcd.c
 * @brief This file provides - functions to manage the LCD.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-04-23       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "lcd.h"


/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LCD LCD模块驱动库
 * @brief LCD Driver Library LCD模块驱动库
 * @{
 */

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
/**
 * @defgroup LCD_Global_Functions LCD全局函数定义
 * @{
 */

/**
 * @brief  获取LCD中断标志位INTF.
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t Lcd_GetItStatus(void)
{
    return (M0P_LCD->SR & 0x01u) ? TRUE : FALSE;
}

/**
 * @brief  清除LCD中断标志INTF.
 * @retval None.
 */
void Lcd_ClearItPendingBit(void)
{
    M0P_LCD->INTCLR_f.INTF = 0u;
}

/**
 * @brief  根据LCD显示模式获取端口配置.
 * @param  [in] pstcSegComPara: 显示模式 @ref stc_lcd_segcompara_t
 * @param  [out] pstcSegCom: 获取端口参数 @ref stc_lcd_segcom_t
 * @retval en_result_t:
 *           - Ok: 成功
 *           - Error: 失败
 *           - ErrorInvalidParameter: 参数错误
 */
en_result_t Lcd_GetSegCom(stc_lcd_segcompara_t *pstcSegComPara, stc_lcd_segcom_t *pstcSegCom)
{
    en_result_t enRet = Error;
    pstcSegCom->stc_seg32_39_com0_7_t.seg32_39_com0_7 = 0xffffffffu;
    pstcSegCom->u32Seg0_31                            = 0xffffffffu;
    if (pstcSegComPara->u8MaxSeg > 39u)
    {
        return ErrorInvalidParameter;
    }
    switch (pstcSegComPara->LcdBiasSrc)
    {
        case LcdInResHighPower:
        case LcdInResLowPower:
        case LcdInResMidPower:
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Mux = 1u;
            break;
        case LcdExtCap:
        case LcdExtRes:
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Mux = 0u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg32_35 = 0u;
            break;
        default:
            return ErrorInvalidParameter;
    }
    switch (pstcSegComPara->LcdDuty)
    {
        case LcdStatic:
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Com0_3 = (~1u) & 0x0fu;
            break;
        case LcdDuty2:
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Com0_3 = (~3u) & 0x0fu;
            break;
        case LcdDuty3:
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Com0_3 = (~7u) & 0x0fu;
            break;
        case LcdDuty4:
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Com0_3 = (~15u) & 0x0fu;
            break;
        case LcdDuty6:
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Com0_3 = 0u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg39Com4 = 0u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg38Com5 = 0u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg37Com6 = 1u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg36Com7 = 1u;
            break;
        case LcdDuty8:
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Com0_3 = 0u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg39Com4 = 0u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg38Com5 = 0u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg37Com6 = 0u;
            pstcSegCom->stc_seg32_39_com0_7_t.segcom_bit.Seg36Com7 = 0u;
            break;
        default:
            return ErrorInvalidParameter;
    }
    enRet = Ok;
    return enRet;
}

/**
 * @brief  LCD COMSEG端口配置，使用该函数之前需要先使能相应的Seg.
 * @param  [in] pstcSegCom: 端口配置结构体 @ref stc_lcd_segcom_t
 * @retval None.
 */
void Lcd_SetSegCom(stc_lcd_segcom_t *pstcSegCom)
{
    M0P_LCD->POEN0 = pstcSegCom->u32Seg0_31;
    M0P_LCD->POEN1 = pstcSegCom->stc_seg32_39_com0_7_t.seg32_39_com0_7;
}

/**
 * @brief  LCD模块初始化函数.
 * @param  [in] pstcLcdCfg: 配置初始化结构体 @ref stc_lcd_cfg_t
 * @retval None.
 */
void Lcd_Init(stc_lcd_cfg_t *pstcLcdCfg)
{
    M0P_LCD->CR0_f.CONTRAST = (pstcLcdCfg->LcdContrast > 0xfu) ? 0xfu : pstcLcdCfg->LcdContrast;
    M0P_LCD->CR0_f.BSEL     = pstcLcdCfg->LcdBiasSrc;
    M0P_LCD->CR0_f.DUTY     = pstcLcdCfg->LcdDuty;
    M0P_LCD->CR0_f.BIAS     = pstcLcdCfg->LcdBias;
    M0P_LCD->CR0_f.CPCLK    = pstcLcdCfg->LcdCpClk;
    M0P_LCD->CR1_f.MODE     = pstcLcdCfg->LcdMode;
    M0P_LCD->CR1_f.CLKSRC   = pstcLcdCfg->LcdClkSrc;
    M0P_LCD->CR0_f.VODEN    = pstcLcdCfg->LcdVolDrv;
    M0P_LCD->CR1_f.DRVRES   = pstcLcdCfg->LcdDrvRes;
    M0P_LCD->CR1_f.DEAD     = pstcLcdCfg->LcdDeadTime;
    M0P_LCD->CR1_f.PSC      = pstcLcdCfg->LcdPscSel;
    M0P_LCD->CR1_f.DIV      = pstcLcdCfg->LcdDivSel;
    M0P_LCD->CR0_f.EN       = pstcLcdCfg->LcdEn;
}

/**
 * @brief  LCD全显.
 * @retval None.
 */
void Lcd_FullDisp(void)
{
    uint8_t tmp;
    volatile uint32_t *ram = NULL;
    ram = &M0P_LCD->RAM0;
    for (tmp = 0u; tmp < 16u; tmp++)
    {
        *ram = 0xffffffffu;
        ram++;
    }
}

/**
 * @brief  LCD清屏.
 * @retval None.
 */
void Lcd_ClearDisp(void)
{
    uint8_t tmp;
    volatile uint32_t *ram = NULL;
    ram = &M0P_LCD->RAM0;
    for (tmp = 0u; tmp < 16u; tmp++)
    {
        *ram = 0u;
        ram++;
    }
}

/**
 * @brief  LCD RAM 0-f寄存器设置函数.
 * @param  [in] u8Row: 行
 * @param  [in] u32Data: 数据 每个位为0时对应的SEG COM交叉点不亮；每个位为1时对应的SEG COM交叉点亮；
 * @retval en_result_t:
 *           - Ok: 成功
 *           - ErrorInvalidParameter: 失败，参数错误
 */
en_result_t Lcd_WriteRam(uint8_t u8Row, uint32_t u32Data)
{
    en_result_t  enRet = Ok;
    volatile uint32_t *ram = NULL;
    ram = (volatile uint32_t *)&M0P_LCD->RAM0;

    if (u8Row > 15u)
    {
        return ErrorInvalidParameter;
    }

    ram += u8Row;
    *ram = u32Data;
    
    return  enRet;
}

/**
 * @brief  LCD 闪烁配置
 * @retval en_result_t:
 *           - Ok: 成功
 *           - ErrorInvalidParameter: 失败，参数错误
 */
en_result_t Lcd_BlinkCfg(uint8_t u8BlinkCnt, boolean_t bBlinkEn)
{
    en_result_t  enRet = Ok;
    
    if(u8BlinkCnt > 0x3Fu)
    {
        return ErrorInvalidParameter;
    }
    
    M0P_LCD->CR1_f.BLINKCNT = u8BlinkCnt;
    M0P_LCD->CR1_f.BLINKEN = bBlinkEn;
    
    return  enRet;
}

/**
 * @brief  LCD 功能配置
 *           - Ok: 成功
 *           - others: 失败
 */
en_result_t Lcd_FuncSet(en_lcd_cr1_t enCtrl, boolean_t bEn)
{
    en_result_t  enRet = Ok;
    
    SetBit((uint32_t)&M0P_LCD->CR1, enCtrl, bEn);
    
    return  enRet;
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

