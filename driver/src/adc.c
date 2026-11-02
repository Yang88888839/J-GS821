/**
 *******************************************************************************
 * @file  adc.c
 * @brief This file provides - functions to manage the ADC.
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
#include "adc.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_ADC ADC模块驱动库
 * @brief ADC Driver Library ADC模块驱动库
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
 * @defgroup ADC_Global_Functions ADC全局函数定义
 * @{
 */

/**
 * @brief  获取ADC中断状态.
 * @param  [in] enAdcIrq: ADC中断类型 @ref en_adc_irq_type_t
 * @retval boolean_t:
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq)
{
    return (M0P_ADC->IFR & enAdcIrq)? TRUE : FALSE;
}

/**
 * @brief  清除ADC中断标志.
 * @param  [in] enAdcIrq: ADC中断类型 @ref en_adc_irq_type_t
 * @retval None.
 */
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq)
{
    M0P_ADC->ICR &= ~(uint32_t)enAdcIrq;
}

/**
 * @brief  ADC中断使能.
 * @retval None.
 */
void Adc_EnableIrq(void)
{
    M0P_ADC->CR0_f.IE = 1u;
}

/**
 * @brief  ADC中断禁止.
 * @retval None.
 */
void Adc_DisableIrq(void)
{
    M0P_ADC->CR0_f.IE = 0u;
}

/**
 * @brief  ADC初始化.
 * @param  [in] pstcAdcCfg: ADC配置指针 @ref stc_adc_cfg_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_Init(stc_adc_cfg_t *pstcAdcCfg)
{
    if (NULL == pstcAdcCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR0 = 0x1u;    /* ADC 使能 */
    delay10us(2);

    M0P_ADC->CR0 |= (uint32_t)pstcAdcCfg->enAdcClkDiv       |
                    (uint32_t)pstcAdcCfg->enAdcRefVolSel    |
                    (uint32_t)pstcAdcCfg->enAdcSampCycleSel;

    M0P_ADC->CR1_f.MODE  = pstcAdcCfg->enAdcMode;

    return Ok;
}



/**
 * @brief  ADC单次转换或者SQR扫描转换外部中断触发源配置.
 * @param  [in] enAdcTrigSel: 触发源选择 @ref en_adc_trig_sel_t
 * @param  [in] bValue:
 *                      -TRUE: 使能
 *                      -FALSE: 关闭
 * @retval None.
 */
void Adc_SglExtTrigCfg(en_adc_trig0_sel_t enAdcTrigSel)
{
    M0P_ADC->EXTTRIGGER0 = enAdcTrigSel;
}


/**
 * @brief  ADC SQR扫描转换外部中断触发源配置.
 * @param  [in] enAdcTrigSel: 触发源选择 @ref en_adc_trig_sel_t
 * @param  [in] bValue:
 *                      -TRUE: 使能
 *                      -FALSE: 关闭
 * @retval None.
 */
void Adc_SqrExtTrigCfg(en_adc_trig0_sel_t enAdcTrigSel)
{
    M0P_ADC->EXTTRIGGER0 = enAdcTrigSel;
}


/**
 * @brief  ADC JQR扫描转换外部中断触发源配置.
 * @param  [in] enAdcTrigSel: 触发源选择 @ref en_adc_trig_sel_t
 * @param  [in] bValue:
 *                      -TRUE: 使能
 *                      -FALSE: 关闭
 * @retval None.
 */
void Adc_JqrExtTrigCfg(en_adc_trig1_sel_t enAdcTrigSel)
{
    M0P_ADC->EXTTRIGGER1 = enAdcTrigSel;
}


/**
 * @brief  ADC单次转换开始
 * @retval None.
 */
void Adc_SGL_Start(void)
{
    M0P_ADC->SGLSTART = 1u;
}

/**
 * @brief  ADC 单次转换停止
 * @retval None.
 */
void Adc_SGL_Stop(void)
{
    M0P_ADC->SGLSTART = 0u;
}


/**
 * @brief  ADC单次转换一直转换开始
 * @retval None.
 */
void Adc_SGL_Always_Start(void)
{
    M0P_ADC->ALLSTART = 1u;
}


/**
 * @brief  ADC单次转换一直转换停止
 * @retval None.
 */
void Adc_SGL_Always_Stop(void)
{
    M0P_ADC->ALLSTART = 0u;
}


/**
 * @brief  ADC SQR扫描转换开始
 * @retval None.
 */
void Adc_SQR_Start(void)
{
    M0P_ADC->SQRSTART = 1u;
}


/**
 * @brief  ADC SQR扫描转换停止
 * @retval None.
 */
void Adc_SQR_Stop(void)
{
    M0P_ADC->SQRSTART = 0u;
}


/**
 * @brief  ADC JQR扫描转换开始
 * @retval None.
 */
void Adc_JQR_Start(void)
{
    M0P_ADC->JQRSTART = 1u;
}


/**
 * @brief  ADC JQR扫描转换停止
 * @retval None.
 */
void Adc_JQR_Stop(void)
{
    M0P_ADC->JQRSTART = 0u;
}


/**
 * @brief  ADC使能
 * @retval None.
 */
void Adc_Enable(void)
{
    M0P_ADC->CR0_f.EN = 1u;
}


/**
 * @brief  ADC除能
 * @retval None.
 */
void Adc_Disable(void)
{
    M0P_ADC->CR0_f.EN = 0u;
}


/**
 * @brief  配置SQR扫描转换模式.
 * @param  [in] pstcAdcSqrCfg: SQR扫描转换模式配置指针 @ref stc_adc_sqr_cfg_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t *pstcAdcSqrCfg)
{
    if ((NULL == pstcAdcSqrCfg) || (pstcAdcSqrCfg->u8SqrCnt > 6u))
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.RACCCLR = 0; //ADC转换结果累加寄存器（ADC_ResultAcc）清零
    M0P_ADC->CR1_f.RACCEN  = pstcAdcSqrCfg->enResultAcc;
    M0P_ADC->CR1_f.DMASQR  = pstcAdcSqrCfg->bSqrDmaTrig;

    M0P_ADC->SQR1_f.CNT  = pstcAdcSqrCfg->u8SqrCnt - 1u;

    return Ok;
}


/**
 * @brief  配置JQR扫描转换模式.
 * @param  [in] pstcAdcJqrCfg: JQR扫描转换模式配置指针 @ref stc_adc_jqr_cfg_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t *pstcAdcJqrCfg)
{
    if ((NULL == pstcAdcJqrCfg) || (pstcAdcJqrCfg->u8JqrCnt > 4u))
    {
        return ErrorInvalidParameter;
    }

    M0P_ADC->CR1_f.DMAJQR  = pstcAdcJqrCfg->bJqrDmaTrig;

    M0P_ADC->JQR_f.CNT  = pstcAdcJqrCfg->u8JqrCnt - 1u;

    return Ok;
}


/**
 * @brief  配置单次转换通道.
 * @param  [in] enstcAdcSampCh: 转换通道 @ref en_adc_samp_ch_sel_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 */
en_result_t Adc_CfgSglChannel(en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    M0P_ADC->CR0_f.SGLMUX = enstcAdcSampCh;

    return Ok;
}


/**
 * @brief  配置SQR扫描转换通道.
 * @param  [in] enstcAdcSqrChMux: SQR扫描转换通道顺序 @ref en_adc_sqr_chmux_t
 * @param  [in] enstcAdcSampCh: 转换通道 @ref en_adc_samp_ch_sel_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    en_result_t enResult = Ok;
    
    M0P_ADC->SQR0 |= (uint32_t)enstcAdcSampCh << (uint8_t)enstcAdcSqrChMux * 5u;

    return enResult;
}


/**
 * @brief  配置JQR扫描转换通道.
 * @param  [in] enstcAdcJqrChMux: JQR扫描转换通道顺序 @ref en_adc_jqr_chmux_t
 * @param  [in] enstcAdcSampCh: 转换通道 @ref en_adc_samp_ch_sel_t
 * @retval en_result_t:
 *           - Ok: 配置成功
 *           - ErrorInvalidParameter: 无效参数
 */
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh)
{
    en_result_t enResult = Ok;
    
     M0P_ADC->JQR |= (uint32_t)enstcAdcSampCh << (uint8_t)enstcAdcJqrChMux * 5u;

    return enResult;
}

/**
 * @brief  获取采样值(单次采样结果）.
 * @retval uint32_t: 采样值
 */
uint32_t Adc_GetSglResult(void)
{
    return M0P_ADC->RESULT;
}

/**
 * @brief  获取SQR扫描采样值.
 * @param  [in] enstcAdcSqrChMux: SQR扫描通道序号 @ref en_adc_sqr_chmux_t
 * @retval uint32_t: 采样值
 */
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux)
{
    volatile uint32_t *BaseSqrResultAddress = &(M0P_ADC->SQRRESULT0);

    return *(BaseSqrResultAddress + ((uint32_t)enstcAdcSqrChMux));

}


/**
 * @brief  获取JQR扫描采样值.
 * @param  [in] enstcAdcJqrChMux: JQR扫描通道序号 @ref en_adc_jqr_chmux_t
 * @retval uint32_t: 采样值
 */
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux)
{
    volatile uint32_t *BaseJqrResultAddress = &(M0P_ADC->JQRRESULT0);

    return *(BaseJqrResultAddress + ((uint32_t)enstcAdcJqrChMux));

}


/**
 * @brief  获取累加采样值.
 * @retval uint32_t: 累加采样结果
 */
uint32_t Adc_GetAccResult(void)
{
    return M0P_ADC->RESULTACC;

}


/**
 * @brief  清零累加采样值.
 * @retval None.
 */
void Adc_ClrAccResult(void)
{
    M0P_ADC->CR1_f.RACCCLR = 0u;
}


/**
 * @brief  ADC比较使能(比较中断).
 * @param  [in] pstcAdcThrCfg: ADC比较配置 @ref stc_adc_threshold_cfg_t
 * @retval None.
 */
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t *pstcAdcThrCfg)
{
    M0P_ADC->HT = pstcAdcThrCfg->u32AdcHighThd;
    M0P_ADC->LT = pstcAdcThrCfg->u32AdcLowThd;

    M0P_ADC->CR1_f.THCH = pstcAdcThrCfg->enSampChSel;

    M0P_ADC->CR1_f.REGCMP = pstcAdcThrCfg->bAdcRegCmp;
    M0P_ADC->CR1_f.HTCMP  = pstcAdcThrCfg->bAdcHtCmp;
    M0P_ADC->CR1_f.LTCMP  = pstcAdcThrCfg->bAdcLtCmp;

}

/**
 * @brief  BGR 使能.
 * @retval None.
 */
void Bgr_BgrEnable(void)
{
    M0P_ADC->BGR |= 0x1u;

    delay10us(3u);
}

/**
 * @brief  BGR 禁止.
 * @retval None.
 */
void Bgr_BgrDisable(void)
{
    M0P_ADC->BGR &= 0x2u;
}

/**
 * @brief  BGR 温度传感器使能(需要先开启BGR).
 * @retval None.
 */
void Bgr_TempSensorEnable(void)
{
    M0P_ADC->BGR |= 0x2u;

    delay10us(3u);
}

/**
 * @brief  BGR 温度传感器禁止.
 * @retval None.
 */
void Bgr_TempSensorDisable(void)
{
    M0P_ADC->BGR &= 0x1u;
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

