/**
 *******************************************************************************
 * @file  uart.c
 * @brief This file provides - functions to manage the USART.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-10-30       MADS            First version
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
#include "usart.h"
/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_USART USART模块驱动库
 * @brief USART Driver Library USART模块驱动库
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
 * @defgroup USART_Global_Functions USART全局函数定义
 * @{
 */

/**
 * @brief  USART通信中断使能函数设置.
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] enIrqSel: 发送or接收中断使能  @ref en_uart_irq_sel_t
 * @retval en_result_t:
 *         - Ok: 设置成功
 */
en_result_t Usart_EnableIrq(M0P_USART_TypeDef *USARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(USARTx->IER)), enIrqSel, TRUE);

    return Ok;
}

/**
 * @brief  USART通信中断禁止函数设置.
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] enIrqSel: 发送or接收中断使能  @ref en_uart_irq_sel_t
 * @retval en_result_t:
 *         - Ok: 设置成功
 */
en_result_t Usart_DisableIrq(M0P_USART_TypeDef *USARTx, en_uart_irq_sel_t enIrqSel)
{
    SetBit((uint32_t)(&(USARTx->IER)), enIrqSel, FALSE);

    return Ok;
}

/**
 * @brief  USART获取中断使能位
 * @param  [in] USARTx: USARTx 通道                       @ref M0P_USART_TypeDef
 * @retval uint32_t: 状态值
 */
boolean_t Usart_GetIrqEn(M0P_USART_TypeDef *USARTx, en_uart_irq_sel_t enIrqSel)
{
    boolean_t bStatus = FALSE;

    bStatus =  GetBit((uint32_t)(&(USARTx->IER)), enIrqSel);
    
    return bStatus;
}

/**
 * @brief  USART总状态获取
 * @param  [in] USARTx: USARTx 通道                       @ref M0P_USART_TypeDef
 * @retval uint32_t: 状态值
 */
uint32_t Usart_GetIsr(M0P_USART_TypeDef *USARTx)
{
    return (USARTx->SR);
}


/**
 * @brief  USART单事件状态获取
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] enStatus: 获取哪个状态  @ref en_uart_status_t
 * @retval boolean_t: 状态值
 */
boolean_t Usart_GetStatus(M0P_USART_TypeDef *USARTx, en_uart_status_t enStatus)
{
    boolean_t bStatus = FALSE;

    bStatus =  GetBit((uint32_t)(&(USARTx->SR)), enStatus);

    return bStatus;
}

/**
 * @brief  USART总标志位寄存器清除
 * @param  [in] USARTx: USARTx 通道                       @ref M0P_USART_TypeDef
 * @retval en_result_t:
 *           - Ok:清除成功
 */
en_result_t Usart_ClrIsr(M0P_USART_TypeDef *USARTx)
{
    USARTx->ICR = 0u;
    return Ok;
}

/**
 * @brief  USART单时间标志位清除
 * @param  [in] USARTx: USARTx 通道                       @ref M0P_USART_TypeDef
 * @param  [in] enStatus: 清除哪个状态                  @ref en_uart_status_t
 * @retval en_result_t:
 *           - Ok:清除成功
 */
en_result_t Usart_ClrStatus(M0P_USART_TypeDef *USARTx, en_uart_status_t enStatus)
{
    SetBit((uint32_t)(&(USARTx->ICR)), enStatus, FALSE);

    return Ok;
}

/**
 * @brief  USART 收发功能配置函数
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] enTransferMode: 收发TxRx功能枚举定义
 * @retval en_result_t:
 *            - Ok:配置成功
 */
en_result_t Usart_TxRxCmd(M0P_USART_TypeDef *USARTx, en_usart_transfer_t enTransferMode)
{
    CLEAR_BIT(USARTx->CR1, USART_CR1_RE|USART_CR1_TE);
    /* Tx/Rx 使能 */
    MODIFY_REG(USARTx->CR1, USART_CR1_RE|USART_CR1_TE, enTransferMode);
    
    return Ok;
}

/**
 * @brief  USART DMA传输功能配置函数
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] enDma: DMA 功能枚举定义
 * @retval en_result_t:
 *            - Ok:配置成功
 */
en_result_t Usart_DmaCmd(M0P_USART_TypeDef *USARTx, en_usart_dma_t enDma)
{
    /* Tx/Rx DMA硬件握手信号使能 */
    MODIFY_REG(USARTx->CR2, USART_CR2_RXDMAEN|USART_CR2_TXDMAEN, enDma);
    
    return Ok;
}

/**
 * @brief  USART多主机模式配置.
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] pstcMultiCfg: 多主机模式结构            @ref stc_uart_multimode_t
 * @retval en_result_t:
 *         - Ok: 配置成功
 *         - ErrorInvalidParameter: 配置失败
 */
en_result_t Usart_SetMultiMode(M0P_USART_TypeDef *USARTx, stc_uart_multimode_t *pstcMultiCfg)
{
    uint32_t u32TempCR1;
    
    if (NULL != pstcMultiCfg)
    {
        u32TempCR1 = USARTx->CR1 & 0x00000003u;
        
        USARTx->CR1 &= 0xFFFFFFFCu;
        
        USARTx->ADDR = pstcMultiCfg->u8SlaveAddr;
        USARTx->ADDMR = pstcMultiCfg->u8SlaveAddrMsk;        
        USARTx->CR1 |= u32TempCR1 | (uint32_t)pstcMultiCfg->enMultiProSilentMode | (uint32_t)pstcMultiCfg->enMultiProEn;
    }
    else
    {
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 * @brief  USART多机模式从机地址配置函数
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] u8Addr: 地址
 * @retval en_result_t:
 *            - Ok:配置成功
 */
en_result_t Usart_SetSaddr(M0P_USART_TypeDef *USARTx, uint8_t u8Addr, uint8_t u8SlaveAddrMsk)
{
    USARTx->ADDR = u8Addr;
    USARTx->ADDMR = u8SlaveAddrMsk;

    return Ok;
}

/**
 * @brief  USART单线半双工模式使能.
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @retval None
 */
void Usart_HdModeEnable(M0P_USART_TypeDef *USARTx)
{
    USARTx->CR1 &= 0xFFFFFFFCu;
    USARTx->CR1_f.COMB = TRUE;
    USARTx->CR1_f.RE = TRUE;
}

/**
 * @brief  USART单线半双工模式关闭.
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @retval None
 */
void Usart_HdModeDisable(M0P_USART_TypeDef *USARTx)
{
    USARTx->CR1 &= 0xFFFFFFFCu;
    USARTx->CR1_f.COMB = FALSE;
}


/**
 * @brief  USART发送数据函数,查询方式调用此函数，中断方式发送不适用
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] u16Data: 发送数据
 * @notes 如不是多处理器通信,u16Data的bit9须始终保持为0!!!
 * @retval en_result_t:
 *           - Ok:发送成功
 */
en_result_t Usart_SendDataPoll(M0P_USART_TypeDef *USARTx, uint16_t u16Data)
{
    while (FALSE == Usart_GetStatus(USARTx, UsartTxE))
    {}

    USARTx->TDR = u16Data;

    return Ok;
}

/**
 * @brief  USART发送数据函数,查询方式调用此函数，中断方式发送不适用
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] u16Data: 发送数据
 * @param  [in] u32TimeOut: 最大发送等待时间
 * @notes 如不是多处理器通信,u16Data的bit9须始终保持为0!!!
 * @retval en_result_t:
 *           - Ok:发送成功
 *           - ErrorTimeout:发送超时
 */
en_result_t Usart_SendDataPollTimeOut(M0P_USART_TypeDef *USARTx, uint16_t u16Data, uint32_t u32TimeOut)
{
    uint32_t u32Cnt;

    u32Cnt = u32TimeOut;
    while (FALSE == Usart_GetStatus(USARTx, UsartTxE))
    {
        if (0u == u32Cnt--)
        {
            return ErrorTimeout;
        }
    }

    USARTx->TDR = u16Data;
    
    u32Cnt = u32TimeOut;
    while (FALSE == Usart_GetStatus(USARTx, UsartTC))
    {
        if (0u == u32Cnt--)
        {
            return ErrorTimeout;
        }
    }
    Usart_ClrStatus(USARTx, UsartTC);

    return Ok;
}

/**
 * @brief  USART发送数据函数,中断方式调用此函数
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @param  [in] u16Data: 发送数据
 * @notes 如不是多处理器通信,u16Data的bit9须始终保持为0!!!
 * @retval en_result_t:
 *           - Ok:发送成功
 */
en_result_t Usart_SendDataIt(M0P_USART_TypeDef *USARTx, uint16_t u16Data)
{
    USARTx->TDR = u16Data;

    return Ok;
}

/**
 * @brief  USART接收数据函数
 * @param  [in] USARTx: USARTx 通道  @ref M0P_USART_TypeDef
 * @retval uint16_t: 接收数据
 */
uint16_t Usart_ReceiveData(M0P_USART_TypeDef *USARTx)
{
    return (uint16_t)(USARTx->RDR);
}


/**
 * @brief  USART 自动波特率检测函数
 * @param  [in] USARTx:            USART类型定义              @ref M0P_USART_TypeDef
 * @param  [in] u32PSC:            PSC分频选择                @ref USART_Baud_Rate_Pre_Clock_Div
 * @retval None
 * @note   须根据目标波特率和当前PCLK设置合适的PSC分频值，以避免波特率检测溢出；须避开波特率检测范围的边缘值
 */
void Usart_ABR_Detect(M0P_USART_TypeDef* USARTx, en_usart_clk_div_t enPSC)
{
    /* 设置PSC值 */
    USARTx->BRR_f.PSC = enPSC;

    /* 自动波特率检测使能 */
    USARTx->CR3_f.ABRE = TRUE;
    
    /* 使用TOE功能为波特率自动检测 */
    USARTx->CR1_f.TOE = UsartToStop; /* 停止TOE */
    
    USARTx->CR1_f.TOE = UsartToAutoBrr;
}

/**
 * @brief  USART 根据自动波特率检测值设置波特率函数
 * @param  [in] USARTx:  USART类型定义  @ref M0P_USART_TypeDef
 * @retval None
 */
void Usart_Detect_ABR_Set(M0P_USART_TypeDef* USARTx, uint32_t u32Pclk)
{
    uint32_t u32CalBaudRate;
    uint32_t u32BDRValue;
    uint32_t u32TXRXEnSta;

    /* 自动波特率检测除能 */
    CLEAR_BIT(USARTx->CR3, 0x4u);

    /* 计算检测的波特率 */
    u32BDRValue    = USARTx->BDR + 1u;
    u32CalBaudRate = Sysctrl_GetPClkFreq() / (1u << (USARTx->BRR_f.PSC * 2u)) / u32BDRValue;

    /* 目标波特率设置 */
    u32TXRXEnSta = READ_BIT(USARTx->CR1, UsartMskTxRxEnable); /* 读取TX、RX使能状态 */
    if (0u == u32TXRXEnSta)  /* TX、RX未使能 */
    {
        u32CalBaudRate = Usart_BaudRateCal(USARTx, UsartBrrUART, u32CalBaudRate, u32Pclk, USARTx->CR1 & UsartMskOver8);
    }
    else /* TX、RX任一使能 */
    {
        CLEAR_BIT(USARTx->CR1, (uint32_t)UsartMskTxRxEnable);
        u32CalBaudRate = Usart_BaudRateCal(USARTx, UsartBrrUART, u32CalBaudRate, u32Pclk, USARTx->CR1 & UsartMskOver8);
        SET_BIT(USARTx->CR1, u32TXRXEnSta);
    }
}


/**
 * @brief  USART 波特率初始化函数
 * @param  [in] USARTx:             USART类型定义      @ref M0P_USART_TypeDef
 * @param  [in] u32BaudRateSetMode: 波特率设置模式选择 @ref USART_BAUD_RATE_SET_MODE
 * @param  [in] u32BaudRate:        UART波特率
 * @param  [in] u32PCLK:            PCLK时钟
 * @param  [in] u32SampMode:        采样次数选择       @ref USART_SAMPLE_BITS_SET （时钟同步模式、红外通信模式）
 *                                                     @ref USART_Over_Sampling   （UART模式、LIN模式）
 *                                                     @ref USART_SC_BCN_SET      （智能卡接口模式）
 * @retval uint32_t：               计算的波特率
 *         - 0：                    配置失败
 *         - 非0：                  计算的波特率
 */
uint32_t Usart_BaudRateCal(M0P_USART_TypeDef* USARTx, en_usart_brr_mode_t enBaudRateSetMode, uint32_t u32BaudRate, uint32_t u32PCLK, uint32_t u32SampMode)
{
    uint64_t u64PCLK, u64BaudRate, u64Temp, u64TempCal, u64MinOffset;
    uint32_t u32Sample         = 0u;   /* Sampel value */
    uint64_t u64TempDIVI[4]    = {0u}; /* DIVI */
    uint64_t u64TempDIVF[4]    = {0u}; /* DIVF */
    uint64_t u64CalBaudRate[4] = {0u}; /* Calculated Baud Rate */
    uint32_t u32TempIdx        = 0u;   /* Index for u32TempDIVI & u32TempDIVF */
    uint32_t u32BaudRateIdx    = 0u;   /* Index for Baud Rate */

    u64PCLK     = (uint64_t)u32PCLK;
    u64BaudRate = (uint64_t)u32BaudRate;

    if (0u != u64BaudRate)
    {
        switch (enBaudRateSetMode)
        {
            case UsartBrrUART:
            case UsartBrrLIN:
                /* BPS = (PCLK×(128+DIVF))/(4^psc×8×(2-OVER8)×(DIVI+1)×256) */
                if (UsartMskOver16 == u32SampMode)
                {
                    u32Sample = 2u * 8u; /* (2-OVER8) = 2 */
                }
                else
                {
                    u32Sample = 1u * 8u; /* (2-OVER8) = 1 */
                }
                break;
            case UsartBrrSYNC:
            case UsartBrrIR:
                /* CLKSYNC BPS = (PCLK×(128+DIVF))/(4^psc×4×(DIVI+1)×256) */
                /* IR      BPS = (PCLK×(128+DIVF))/(4^psc×16×(DIVI+1)×256) */
                u32Sample = u32SampMode;
                break;
            case UsartBrrSC:
                /* BPS = (PCLK×(128+DIVF))/(4^psc×2×BCN×(DIVI+1)×256) */
                u32Sample = 2u * u32SampMode;
                break;
            default:
                break;
        }

        if (u32Sample == 0u)
        {
            /* Invalid setting*/
            return 0u;
        }

        u64Temp = u64PCLK / (u64BaudRate * u32Sample); /* = PCLK / (BPS * 采样计数 */
        if (0u == u64Temp)
        {
            /* Invalid setting*/
            return 0u;
        }
        for (u32TempIdx = 0u; u32TempIdx < 4u; u32TempIdx++)
        {
            /* Cal DIVI */
            u64TempDIVI[u32TempIdx] = u64Temp >> (2u * u32TempIdx); /* = / 4^psc */
            if (256u < u64TempDIVI[u32TempIdx])                     /* DIVI <= 256 */
            {
                u64TempDIVI[u32TempIdx] = 0u;
            }
            if (0u != u64TempDIVI[u32TempIdx])
            {
                /* Cal DIVF */
                u64TempCal = u32Sample * u64TempDIVI[u32TempIdx];
                u64TempDIVF[u32TempIdx] =
                    ((((u64BaudRate * u64TempCal * 256u) << (2u * u32TempIdx)) * 10u / u64PCLK) + 5u) / 10u - 128u; /* with round up */
                if (127u < u64TempDIVF[u32TempIdx])
                {
                    /* Calcualte baud rate: DIVF is disabled */
                    u64CalBaudRate[u32TempIdx] = u64PCLK / (u64TempCal << (2u * u32TempIdx));
                }
                else
                {
                    /* Calcualte baud rate: DIVF is enabled */
                    u64CalBaudRate[u32TempIdx] = u64PCLK * (128u + u64TempDIVF[u32TempIdx]) / (u64TempCal << (2u * u32TempIdx)) / 256u;
                }
            }
        }

        /* Out of range check */
        for (u32TempIdx = 0u; u32TempIdx < 4u; u32TempIdx++)
        {
            if (u64TempDIVI[u32TempIdx] != 0u)
            {
                break;
            }
            if (u32TempIdx == 3u)
            {
                /* Invalid setting*/
                return 0u;
            }
        }

        /* Find best fit baud rate */
        u64MinOffset = 0xFFFFFFFFu;
        for (u32TempIdx = 0u; u32TempIdx < 4u; u32TempIdx++)
        {
            if (0u != u64TempDIVI[u32TempIdx])
            {
                u64Temp = (u64CalBaudRate[u32TempIdx] > u32BaudRate) ? (u64CalBaudRate[u32TempIdx] - u32BaudRate) :
                                                                       (u32BaudRate - u64CalBaudRate[u32TempIdx]);
                if (u64Temp < u64MinOffset)
                {
                    u64MinOffset   = u64Temp;
                    u32BaudRateIdx = u32TempIdx;
                }
            }
        }

        if (enBaudRateSetMode == UsartBrrSYNC)
        {
            /* 时钟同步最高波特率 >= PCLK/8 */
            if ((0u == u32BaudRateIdx) && (1u == u64TempDIVI[0u]))
            {
                /* Invalid setting*/
                return 0u;
            }
        }

        /* Set BRR register */
        if (128u <= u64TempDIVF[u32BaudRateIdx])
        {
            WRITE_REG(USARTx->BRR, (u32BaudRateIdx << 16u) | ((u64TempDIVI[u32BaudRateIdx] - 1u) << 8u));
        }
        else
        {
            WRITE_REG(USARTx->BRR, (u32BaudRateIdx << 16u) | ((u64TempDIVI[u32BaudRateIdx] - 1u) << 8u) | u64TempDIVF[u32BaudRateIdx] | 0x80u);
        }

        /* Feedback best fit baud rate */
        return (uint32_t)u64CalBaudRate[u32BaudRateIdx];
    }
    else
    {
        /* Invalid setting*/
        return 0u;
    }
}

/**
 * @brief  USART初始化函数
 * @param  [in] USARTx: USARTx 通道       @ref M0P_USART_TypeDef
 * @param  [in] pstcCfg: 初始化结构体     @ref stc_usart_uart_init_t
 * @retval en_result_t:
 *           - Ok:配置成功
 *           - Error:配置失败
 *           - ErrorInvalidParameter:参数不合理
 */
en_result_t Usart_Uart_Init(M0P_USART_TypeDef *USARTx, stc_usart_uart_init_t *pstcUartCfg)
{
    en_result_t  enRet = Ok;
    uint32_t     u32CalBaudRate = 0u;

    if (NULL == pstcUartCfg)
    {
        return ErrorInvalidParameter;
    }
    
    /* 复位 */
    if (M0P_USART0 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART0 = 0u;
        M0P_RESET->PERI_RESET0_f.USART0 = 1u;
    }
    else if (M0P_USART1 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART1 = 0u;
        M0P_RESET->PERI_RESET0_f.USART1 = 1u;
    }
    else {}

    /* 设置波特率 */
    u32CalBaudRate = Usart_BaudRateCal(USARTx, UsartBrrUART, pstcUartCfg->u32BaudRate, pstcUartCfg->u32Pclk, pstcUartCfg->enSampleMode);
        
    if(0u == u32CalBaudRate)
    {
        enRet =  ErrorInvalidParameter;
    }

    /* CR2设置 */
    WRITE_REG(USARTx->CR2, (uint32_t)pstcUartCfg->stcAdvFeature.enClockCtrl | (uint32_t)pstcUartCfg->stcAdvFeature.enTxRxSwap | (uint32_t)UsartMskUartMode
                               | (uint32_t)pstcUartCfg->stcAdvFeature.enTxRxPinLevelInvert | (uint32_t)pstcUartCfg->stcAdvFeature.enHWFlowCtrl
                               | (uint32_t)pstcUartCfg->stcAdvFeature.enDMATxRxTransfer);
    
    /* CR1设置 */
    WRITE_REG(USARTx->CR1, (uint32_t)pstcUartCfg->stcAdvFeature.enTxRxCombine | (uint32_t)pstcUartCfg->stcAdvFeature.enStartBitDetectMode
                               | (uint32_t)pstcUartCfg->enSampleMode | (uint32_t)pstcUartCfg->stcAdvFeature.enMSBFirst | (uint32_t)pstcUartCfg->enStopBit
                               | (uint32_t)pstcUartCfg->enFrameLength | pstcUartCfg->enParity);
    
    /* ICR 清零 */
    CLEAR_REG(USARTx->ICR);

    /* Tx/Rx 使能 */
    MODIFY_REG(USARTx->CR1, USART_CR1_RE|USART_CR1_TE, pstcUartCfg->enTransMode);

    return enRet;
}

/**
 * @brief  USART 同步串口初始化函数
 * @param  [in] USARTx:          USART类型定义      @ref M0P_USART_TypeDef
 * @param  [in] pstcClkSyncInit: UART初始化结构体   @ref stc_usart_uart_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t Usart_ClkSync_Init(M0P_USART_TypeDef* USARTx, stc_usart_clksync_init_t* pstcClkSyncInit)
{
    uint32_t u32CalBaudRate = 0u;
    /* 复位 */
    if (M0P_USART0 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART0 = 0u;
        M0P_RESET->PERI_RESET0_f.USART0 = 1u;
    }
    else if (M0P_USART1 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART1 = 0u;
        M0P_RESET->PERI_RESET0_f.USART1 = 1u;
    }
    else {}

    /* 内部波特率生成器生成的时钟 */
    if (UsartMskSyncInnerClkWithOutput == pstcClkSyncInit->stcAdvFeature.enClockCtrl)
    {
        /* 设置波特率 */
        u32CalBaudRate =
            Usart_BaudRateCal(USARTx, UsartBrrSYNC, pstcClkSyncInit->u32BaudRate, pstcClkSyncInit->u32Pclk, UsartSyncSampleCnt);
        if(0u == u32CalBaudRate)
        {
            return ErrorInvalidParameter;
        }
    }
    /* CR2设置 */
    WRITE_REG(USARTx->CR2, (uint32_t)pstcClkSyncInit->stcAdvFeature.enClockCtrl | (uint32_t)pstcClkSyncInit->stcAdvFeature.enTxRxSwap | (uint32_t)UsartMskSyncMode
                               | (uint32_t)pstcClkSyncInit->stcAdvFeature.enTxRxPinLevelInvert | (uint32_t)pstcClkSyncInit->stcAdvFeature.enHWFlowCtrl
                               | (uint32_t)pstcClkSyncInit->stcAdvFeature.enDMATxRxTransfer);
    
    /* CR1设置 */
    WRITE_REG(USARTx->CR1, (uint32_t)UsartMskTxRxSeparate | (uint32_t)UsartMskStartRxEdge | (uint32_t)UsartMskOver16 | (uint32_t)pstcClkSyncInit->stcAdvFeature.enMSBFirst
                               | (uint32_t)UsartMskStop1bit | (uint32_t)UsartMskFrame8Bit | (uint32_t)UsartMskFParityNone);

    /* ICR 清零 */
    CLEAR_REG(USARTx->ICR);

    /* Tx/Rx 使能 */
    MODIFY_REG(USARTx->CR1, USART_CR1_RE|USART_CR1_TE, pstcClkSyncInit->enTransMode);
    return u32CalBaudRate;
}

/**
 * @brief  USART LIN初始化函数
 * @param  [in] USARTx:        USART类型定义    @ref M0P_USART_TypeDef
 * @param  [in] pstcLinInit:   LIN初始化结构体  @ref stc_usart_lin_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t Usart_Lin_Init(M0P_USART_TypeDef* USARTx, stc_usart_lin_init_t* pstcLinInit)
{
    uint32_t u32CalBaudRate = 0u;
    /* 复位 */
    if (M0P_USART0 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART0 = 0u;
        M0P_RESET->PERI_RESET0_f.USART0 = 1u;
    }
    else if (M0P_USART1 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART1 = 0u;
        M0P_RESET->PERI_RESET0_f.USART1 = 1u;
    }
    else {}

    /* 设置波特率 */
    u32CalBaudRate = Usart_BaudRateCal(USARTx, UsartBrrLIN, pstcLinInit->u32BaudRate, pstcLinInit->u32Pclk, pstcLinInit->enSampleMode);
    if(0u == u32CalBaudRate)
    {
        return ErrorInvalidParameter;
    }
    
    /* CR2设置 */
    WRITE_REG(USARTx->CR2, (uint32_t)pstcLinInit->stcAdvFeature.enTxRxSwap | (uint32_t)UsartMskUartMode | (uint32_t)pstcLinInit->stcAdvFeature.enTxRxPinLevelInvert
                               | (uint32_t)pstcLinInit->stcAdvFeature.enDMATxRxTransfer);
    /* CR1设置 */
    WRITE_REG(USARTx->CR1,
        (uint32_t)pstcLinInit->enSampleMode | (uint32_t)pstcLinInit->stcAdvFeature.enMSBFirst | (uint32_t)UsartMskFParityNone | (uint32_t)UsartMskStop1bit | (uint32_t)UsartMskTxRxSeparate);

    /* ICR 清零 */
    CLEAR_REG(USARTx->ICR);

    return u32CalBaudRate;
}

/**
 * @brief  USART IR初始化函数
 * @param  [in] USARTx:        USART类型定义      @ref M0P_USART_TypeDef
 * @param  [in] pstcIRInit:    IR初始化结构体   @ref stc_usart_ir_init_t
 * @retval uint32_t:           设置的实际波特率
 */
uint32_t Usart_Ir_Init(M0P_USART_TypeDef* USARTx, stc_usart_ir_init_t* pstcIRInit)
{
    uint32_t u32CalBaudRate = 0u;
    /* 复位 */
    if (M0P_USART0 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART0 = 0u;
        M0P_RESET->PERI_RESET0_f.USART0 = 1u;
    }
    else if (M0P_USART1 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART1 = 0u;
        M0P_RESET->PERI_RESET0_f.USART1 = 1u;
    }
    else {}
        

    /* 设置波特率 */
    u32CalBaudRate = Usart_BaudRateCal(USARTx, UsartBrrIR, pstcIRInit->u32BaudRate, pstcIRInit->u32Pclk, UsartIrSampleCnt);
    if(0u == u32CalBaudRate)
    {
        return ErrorInvalidParameter;
    }
        
    /* 设置38K高低电平维持时间 */
    USARTx->IR_f.DCNTH = pstcIRInit->u32HighLevelTime38K;
    USARTx->IR_f.DCNTL = pstcIRInit->u32LowLevelTime38K;
        
    /* CR3设置 */
    WRITE_REG(USARTx->CR3, (uint32_t)pstcIRInit->enIRMode | (uint32_t)pstcIRInit->enIRMod38K);
    /* CR2设置 */
    WRITE_REG(USARTx->CR2, (uint32_t)pstcIRInit->stcAdvFeature.enTxRxSwap | (uint32_t)UsartMskUartMode | (uint32_t)pstcIRInit->stcAdvFeature.enTxRxPinLevelInvert
                               | (uint32_t)pstcIRInit->stcAdvFeature.enDMATxRxTransfer);
    /* CR1设置 */
    WRITE_REG(USARTx->CR1, (uint32_t)UsartMskTxRxSeparate | (uint32_t)UsartMskStartRxEdge | (uint32_t)UsartMskOver16 | (uint32_t)pstcIRInit->stcAdvFeature.enMSBFirst
                               | (uint32_t)UsartMskStop1bit | (uint32_t)pstcIRInit->enFrameLength | (uint32_t)pstcIRInit->enParity);

    /* ICR 清零 */
    CLEAR_REG(USARTx->ICR);

    /* Tx/Rx 使能 */
    MODIFY_REG(USARTx->CR1, USART_CR1_RE|USART_CR1_TE, pstcIRInit->enTransMode);
    return u32CalBaudRate;
}

/**
 * @brief  USART IR功能开启/关闭控制
 * @param  [in] USARTx:      USART类型定义  @ref M0P_USART_TypeDef
 * @param  [in] bIrCmd: TRUE:使能; FALSE:关闭
 * @retval None
 */
void Usart_Ir_Enable_Cmd(M0P_USART_TypeDef* USARTx, boolean_t bIrCmd)
{
    USARTx->CR3_f.IREN = bIrCmd;
}

/**
 * @brief  USART SmartCard初始化函数
 * @param  [in] USARTx:             USART类型定义    @ref M0P_USART_TypeDef
 * @param  [in] pstcSmartCardInit:  智能卡初始化结构体  @ref stc_usart_smart_card_init_t
 * @retval uint32_t:                设置的实际波特率
 */
uint32_t Usart_Sc_Init(M0P_USART_TypeDef* USARTx, stc_usart_smart_card_init_t* pstcSmartCardInit)
{
    uint32_t u32CalBaudRate = 0u;
    uint32_t u32Parity;
    uint32_t u32Cr3Val;

    /* 复位 */
    if (M0P_USART0 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART0 = 0u;
        M0P_RESET->PERI_RESET0_f.USART0 = 1u;
    }
    else if (M0P_USART1 == USARTx)
    {
        M0P_RESET->PERI_RESET0_f.USART1 = 0u;
        M0P_RESET->PERI_RESET0_f.USART1 = 1u;
    }
    else {}

    /* 设置时钟源波特率，智能卡模式固定16倍采样，采样计数为2*bcn */
    u32CalBaudRate =
        Usart_BaudRateCal(USARTx, UsartBrrSC, pstcSmartCardInit->u32DataBaudRate, pstcSmartCardInit->u32Pclk, pstcSmartCardInit->enFiBCN);
        if(0u == u32CalBaudRate)
        {
            return ErrorInvalidParameter;
        }
        
    /* CR2设置 */
    WRITE_REG(USARTx->CR2, (uint32_t)pstcSmartCardInit->stcAdvFeature.enTxRxSwap | (uint32_t)pstcSmartCardInit->stcAdvFeature.enClockCtrl
                               | (uint32_t)pstcSmartCardInit->stcAdvFeature.enTxRxPinLevelInvert | (uint32_t)pstcSmartCardInit->stcAdvFeature.enDMATxRxTransfer);
    /* CR1设置 */
    u32Parity = (UsartMskFParityEven == pstcSmartCardInit->enParity) ? UsartMskFParityEven : UsartMskFParityOdd;
    WRITE_REG(USARTx->CR1, (uint32_t)pstcSmartCardInit->stcAdvFeature.enMSBFirst | (uint32_t)UsartMskStop1bit | (uint32_t)UsartMskTxRxSeparate | u32Parity);

    /* CR3设置 */
    switch (pstcSmartCardInit->enFiBCN)
    {
        case UsartMskScBitClk16:
            u32Cr3Val = (0ul << USART_CR3_BCN_Pos) | ((uint32_t)pstcSmartCardInit->enIOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case UsartMskScBitClk32:
            u32Cr3Val = (1ul << USART_CR3_BCN_Pos) | ((uint32_t)pstcSmartCardInit->enIOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case UsartMskScBitClk64:
            u32Cr3Val = (2ul << USART_CR3_BCN_Pos) | ((uint32_t)pstcSmartCardInit->enIOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case UsartMskScBitClk128:
            u32Cr3Val = (3ul << USART_CR3_BCN_Pos) | ((uint32_t)pstcSmartCardInit->enIOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case UsartMskScBitClk186:
            u32Cr3Val = (4ul << USART_CR3_BCN_Pos) | ((uint32_t)pstcSmartCardInit->enIOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case UsartMskScBitClk256:
            u32Cr3Val = (5ul << USART_CR3_BCN_Pos) | ((uint32_t)pstcSmartCardInit->enIOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case UsartMskScBitClk372:
            u32Cr3Val = (6ul << USART_CR3_BCN_Pos) | ((uint32_t)pstcSmartCardInit->enIOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        case UsartMskScBitClk512:
            u32Cr3Val = (7ul << USART_CR3_BCN_Pos) | ((uint32_t)pstcSmartCardInit->enIOPUTime << USART_CR3_SMCPU_Pos) | USART_CR3_SCEN;
            break;

        default:
            break;
    }

    WRITE_REG(USARTx->CR3, u32Cr3Val);
    /* ICR 清零 */
    CLEAR_REG(USARTx->ICR);

    return u32CalBaudRate;
}

/**
 * @brief  USART SmartCard时钟输出使能/禁止
 * @param  [in] USARTx: USART类型定义    @ref M0P_USART_TypeDef
 * @param  [in] bEn: 输出时钟使能(输出使能：TRUE，输出禁止：FALSE)
 * @retval uint32_t:                设置的实际波特率
 */
void Usart_Sc_CLK_Enable(M0P_USART_TypeDef* USARTx, boolean_t bEn)
{
    USARTx->CR2_f.CLKC = bEn;
}

/**
 * @brief  USART 智能卡中断发送
 * @param  [in] USARTx:      USART类型定义      @ref M0P_USART_TypeDef
 * @param  [in] pu8Data:     待发送数据地址
 * @retval None
 */
void Usart_Sc_TransmitINT(M0P_USART_TypeDef* USARTx, uint8_t* pu8Data)
{
    uint32_t i = 0u;
    
    MODIFY_REG(USARTx->CR1, USART_CR1_RE|USART_CR1_TE, UsartMskTxEnable);
    
    while((!READ_BIT(USARTx->CR1, USART_CR1_TE)) && (i++ < 10000u))
    {}
        
    WRITE_REG(USARTx->TDR, *pu8Data);
}

/**
 * @brief  USART 智能卡中断接收
 * @param  [in] USARTx:      USART类型定义      @ref M0P_USART_TypeDef
 * @retval None
 */
void Usart_Sc_ReceiveINT(M0P_USART_TypeDef* USARTx)
{
    uint32_t i = 0u;
    
    MODIFY_REG(USARTx->CR1, USART_CR1_RE|USART_CR1_TE, UsartMskRxEnable);
    
    while((!READ_BIT(USARTx->CR1, USART_CR1_RE)) && (i++ < 10000u)){}
}

/**
 * @brief  USART 多功能定时器配置
 * @param  [in] USARTx:  USART类型定义  @ref M0P_USART_TypeDef
 * @param  [in] enToMode:  多功能定时器工作模式枚举定义
 * @param  [in] u32ToData: 多功能定时器计数目标值设置
 * @retval None
 */
void Usart_To_Cfg(M0P_USART_TypeDef* USARTx,en_usart_to_mode_t enToMode, uint32_t u32Totime)
{    
    USARTx->TOR = u32Totime;
    USARTx->CR1_f.TOE = enToMode;
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
