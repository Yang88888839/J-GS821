/**
 *******************************************************************************
 * @file  lpuart.c
 * @brief This file provides - functions to manage the lpuart.
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
#include "lpuart.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_LPUART LPUART模块驱动库
 * @brief LPUART Driver Library LPUART模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup LPUART_Global_Functions LPUART全局函数定义
 * @{
 */

/**
 * @brief  LPUART通信中断使能函数设置.
 * @param  [in] LPUARTx: LPUARTx 通道                 @ref M0P_LPUART_TypeDef
 * @param  [in] enIrqSel: 发送or接收中断使能          @ref en_lpuart_irq_sel_t
 * @retval en_result_t:
 *         - OK: 配置成功
 */
en_result_t LPUart_EnableIrq(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), enIrqSel, TRUE);
    return Ok;
}

/**
 * @brief  LPUART通信中断禁止函数设置.
 * @param  [in] LPUARTx: LPUARTx 通道                 @ref M0P_LPUART_TypeDef
 * @param  [in] enIrqSel: 发送or接收中断使能          @ref en_lpuart_irq_sel_t
 * @retval en_result_t:
 *         - OK: 配置成功
 */
en_result_t LPUart_DisableIrq(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), enIrqSel, FALSE);
    return Ok;
}

/**
 * @brief  lpuart通信时钟源选择.
 * @param  [in] LPUARTx: LPUARTx 通道                 @ref M0P_LPUART_TypeDef
 * @param  [in] enSclk: 时钟源选项                    @ref en_lpuart_sclksel_t
 * @retval en_result_t:
 *         - OK: 配置成功
 */
en_result_t LPUart_SelSclk(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_sclksel_t enSclk)
{
    ASSERT(IS_VALID_CLK(enSclk));
    LPUARTx->SCON_f.SCLKSEL = enSclk;
    return Ok;
}


/**
 * @brief  LPUART多机模式配置.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] pstcMultiCfg: 多机模式结构                     @ref stc_lpuart_multimode_t
 * @retval en_result_t:
 *         - OK: 配置成功
 *         - ErrorInvalidParameter: 配置失败
 */
en_result_t LPUart_SetMultiMode(M0P_LPUART_TypeDef *LPUARTx, stc_lpuart_multimode_t *pstcMultiCfg)
{
    if (NULL != pstcMultiCfg)
    {
        LPUARTx->SCON_f.ADRDET = TRUE;
        LPUARTx->SADDR = pstcMultiCfg->u8SlaveAddr;
        LPUARTx->SADEN = pstcMultiCfg->u8SaddEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 * @brief  LPUART单线半双工模式关闭.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @retval None
 */
void LPUart_HdModeDisable(M0P_LPUART_TypeDef *LPUARTx)
{
    LPUARTx->SCON_f.HDSEL = FALSE;
}

/**
 * @brief  LPUART多机模式从机地址配置函数.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] u8Addr: 地址
 * @retval en_result_t:
 *         - OK: 配置成功
 */
en_result_t LPUart_SetSaddr(M0P_LPUART_TypeDef *LPUARTx, uint8_t u8Addr)
{
    LPUARTx->SADDR = u8Addr;
    return Ok;
}


/**
 * @brief  LPUART发送或接收等功能使能设置.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] enFunc: 功能                                   @ref en_lpuart_func_t
 * @retval en_result_t:
 *         - OK: 设置成功
 */
en_result_t LPUart_EnableFunc(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), enFunc, TRUE);
    return Ok;
}

/**
 * @brief  LPUART发送或接收等功能禁止设置.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] enFunc: 功能                                   @ref en_lpuart_func_t
 * @retval en_result_t:
 *         - OK: 设置成功
 */
en_result_t LPUart_DisableFunc(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_func_t enFunc)
{
    SetBit((uint32_t)(&(LPUARTx->SCON)), enFunc, FALSE);
    return Ok;
}

/**
 * @brief  LPUART总状态获取.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @retval None
 */
uint8_t LPUart_GetIsr(M0P_LPUART_TypeDef *LPUARTx)
{
    return (LPUARTx->ISR);
}


/**
 * @brief  LPUART单个状态获取.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] enStatus: 获取哪个状态                         @ref en_lpuart_status_t
 * @retval boolean_t:
 *         - TRUE: 配置成功
 *         - FALSE: 配置失败
 */
boolean_t LPUart_GetStatus(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_status_t enStatus)
{
    boolean_t bStatus = FALSE;

    bStatus =  GetBit((uint32_t)(&(LPUARTx->ISR)), enStatus);

    return bStatus;
}

/**
 * @brief  LPUART状态全部清除.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @retval boolean_t:
 *         - OK: 清除成功
 */
en_result_t LPUart_ClrIsr(M0P_LPUART_TypeDef *LPUARTx)
{
    LPUARTx->ICR = 0u;
    return Ok;
}

/**
 * @brief  LPUART单个状态清除.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] enStatus: 清除哪个状态                         @ref en_lpuart_status_t
 * @retval en_result_t:
 *         - OK: 清除成功
 */
en_result_t LPUart_ClrStatus(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_status_t enStatus)
{
    SetBit((uint32_t)(&(LPUARTx->ICR)), enStatus, FALSE);

    return Ok;
}

/**
 * @brief  LPUART发送数据函数,查询方式调用此函数，中断方式发送不适用.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] u8Data: 发送数据
 * @retval en_result_t:
 *         - OK: 发送成功
 */
en_result_t LPUart_SendData(M0P_LPUART_TypeDef *LPUARTx, uint8_t u8Data)
{
    while (FALSE == LPUart_GetStatus(LPUARTx, LPUartTxe))
    {}
    LPUARTx->SBUF_f.DATA = u8Data;

    return Ok;
}


/**
 * @brief  LPUART发送数据函数,查询方式调用此函数，中断方式发送不适用.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] u8Data: 发送数据
 * @param  [in] u32TimeOut: 最长发送时间
 * @retval en_result_t:
 *         - OK: 发送成功
 *         - ErrorTimeout: 发送超时
 */
en_result_t LPUart_SendDataTimeOut(M0P_LPUART_TypeDef *LPUARTx, uint8_t u8Data, uint32_t u32TimeOut)
{
    uint32_t u32Cnt = 0;

    while (FALSE == LPUart_GetStatus(LPUARTx, LPUartTxe))
    {
        if (u32Cnt > u32TimeOut)
        {
            return ErrorTimeout;
        }
        u32Cnt++;
    }
    
    LPUARTx->SBUF_f.DATA = u8Data;
    
    u32Cnt = 0u;
    while (FALSE == LPUart_GetStatus(LPUARTx, LPUartTC))
    {
        if (u32Cnt > u32TimeOut)
        {
            return ErrorTimeout;
        }
        u32Cnt++;
    }
    LPUart_ClrStatus(LPUARTx, LPUartTC);
    return Ok;
}

/**
 * @brief  LPUART发送数据函数,中断方式调用此函数.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] u8Data: 发送数据
 * @retval en_result_t:
 *         - OK: 发送成功
 */
en_result_t LPUart_SendDataIt(M0P_LPUART_TypeDef *LPUARTx, uint8_t u8Data)
{
    LPUARTx->SBUF_f.DATA = u8Data;
    return Ok;
}

/**
 * @brief  LPUART多机模式查询发送，中断方式发送不适用.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] u16Data: 发送数据
 * @param  [in] u32Timeout: 最长发送时间
 * @retval en_result_t:
 *         - OK: 发送成功
 *         - ErrorTimeout: 发送超时
 */
en_result_t LPUart_MultiModeSendData(M0P_LPUART_TypeDef *LPUARTx, uint16_t u16Data, uint32_t u32Timeout)
{
    uint32_t u32TimeCnt = 0u;

    while (FALSE == LPUart_GetStatus(LPUARTx, LPUartTxe))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /* 等待超时 */
            return ErrorTimeout;
        }
    }

    LPUARTx->SBUF  = (uint32_t)u16Data;

    u32TimeCnt = 0u;
    while (FALSE == LPUart_GetStatus(LPUARTx, LPUartTC))
    {
        u32TimeCnt++;
        if (u32Timeout <= u32TimeCnt)
        {
            /* 等待超时 */
            return ErrorTimeout;
        }
    }

    LPUart_ClrStatus(LPUARTx, LPUartTC);

    return Ok;
}

/**
 * @brief  LPUART多机模式中断发送.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] u16Data: 发送数据
 * @retval en_result_t:
 *         - OK: 发送成功
 */
en_result_t LPUart_MultiModeSendDataIt(M0P_LPUART_TypeDef *LPUARTx, uint16_t u16Data)
{
    while (FALSE == LPUart_GetStatus(LPUARTx, LPUartTxe)) {;}
    LPUARTx->SBUF  = (uint32_t)u16Data;
    return Ok;
}


/**
 * @brief  LPUART接收数据函数.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @retval uint8_t: 接收数据
 */
uint8_t LPUart_ReceiveData(M0P_LPUART_TypeDef *LPUARTx)
{
    return (LPUARTx->SBUF_f.DATA);
}

/**
 * @brief  获取RB8数值.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @retval boolean_t: RB8
 */
boolean_t LPUart_GetRb8(M0P_LPUART_TypeDef *LPUARTx)
{
    return (LPUARTx->SBUF_f.DATA8);
}

/**
 * @brief  LPUART初始化函数.
 * @param  [in] LPUARTx: LPUARTx 通道                          @ref M0P_LPUART_TypeDef
 * @param  [in] pstcCfg: 初始化结构体                          @ref stc_lpuart_cfg_t
 * @retval en_result_t:
 *         - OK: 配置成功
 *         - ErrorInvalidParameter: 参数不合理
 */
en_result_t LPUart_Init(M0P_LPUART_TypeDef *LPUARTx, stc_lpuart_cfg_t *pstcCfg)
{
    en_result_t enRet = Error;
    const uint32_t u32Over[3] = {0x4, 0x3, 0x2};
    uint16_t u16OverShift;
    float32_t f32Scnt = 0;

    if (NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }

    LPUARTx->SCON = 0;
    
    LPUARTx->SCON |= (uint32_t)pstcCfg->stcBaud.enSclkSel;
    
    if(pstcCfg->bHalfDuplex == TRUE)
    {
        LPUARTx->SCON_f.HDSEL = TRUE;
        delay1ms(1u);
    }
    
    LPUARTx->SCON |= (uint32_t)pstcCfg->enStopBit          |
                    (uint32_t)pstcCfg->enMmdorCk          |
                    (uint32_t)pstcCfg->stcBaud.enSclkDiv  |
                    (uint32_t)pstcCfg->enRunMode;

    if ((LPUartMskMode1 == pstcCfg->enRunMode) || (LPUartMskMode3 == pstcCfg->enRunMode))
    {
        u16OverShift = u32Over[pstcCfg->stcBaud.enSclkDiv / LPUartMsk8Or16Div];
        f32Scnt = (float32_t)(pstcCfg->stcBaud.u32Sclk) / (float32_t)(pstcCfg->stcBaud.u32Baud << u16OverShift);
        LPUARTx->SCNT = (uint16_t)(float32_t)(f32Scnt + 0.5f);
    }

    enRet = Ok;

    return enRet;
}

/**
 * @brief  LPUART XTL波特率产生寄存器
 * @note   当XTL时钟为32768时，调用此函数产生9600或者4800波特率
 * @param  [in] LPUARTx: LPUARTx 通道                            @ref M0P_LPUART_TypeDef
 * @param  [in] enBselSet: 波特率选择                            @ref en_lpuart_xtl_bsel_t
 * @retval en_result_t:
 *         - OK: 配置成功
 *         - Error: 配置成功
 */
en_result_t LPUart_Xtl_Bsel_Set(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_xtl_bsel_t enBselSet)
{
    en_result_t enRet = Ok;

    if (0x2u == LPUARTx->SCON_f.SCLKSEL)
    {
        if (enBselSet == LPUartBselXtl32kSetTo9600)
        {
            LPUARTx->BSEL = 0x2u;
            LPUARTx->MODU = 0x54Au;
        }
        else if (enBselSet == LPUartBselXtl32kSetTo4800)
        {
            LPUARTx->BSEL = 0x3u;
            LPUARTx->MODU = 0xEFBu;
        }
        else
        {
            enRet = Error;
        }
    }
    else
    {
        enRet = Error;
    }

    return enRet;
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
 *****************************************************************************/
