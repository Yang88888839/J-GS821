/**
 *******************************************************************************
 * @file  spi.c
 * @brief This file provides - functions to manage the SPI.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "spi.h"


/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SPI SPI模块驱动库
 * @brief SPI Driver Library SPI模块驱动库
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
 * @defgroup SPI_Global_Functions SPI全局函数定义
 * @{
 */

/**
 * @brief  SPI 状态获取.
 * @param  [in] SPIx: SPIx 通道              @ref M0P_SPI_TypeDef
 * @param  [in] enStatus: SPI状态位          @ref en_spi_status_t
 * @retval boolean_t:
 *         - TRUE: SPI状态位置起
 *         - FALSE: SPI状态位未置起
 */
boolean_t Spi_GetStatus(M0P_SPI_TypeDef *SPIx, en_spi_status_t enStatus)
{
    if (SPIx->SR & (uint32_t)enStatus)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

/**
 * @brief  SPI 中断清除.
 * @param  [in] SPIx: SPIx 通道              @ref M0P_SPI_TypeDef
 * @param  [in] enStatus: SPI状态位          @ref en_spi_status_t
 * @retval en_result_t:
 *         - Ok: SPI中断清除成功
 */
en_result_t Spi_ClearStatus(M0P_SPI_TypeDef *SPIx, en_spi_status_t enStatus)
{
    SPIx->ICR &= ~(uint32_t)enStatus;

    return Ok;
}

/**
 * @brief  SPI 所有标志清除.
 * @param  [in] SPIx: SPIx 通道              @ref M0P_SPI_TypeDef
 * @retval en_result_t:
 *         - Ok: SPI中断清除成功
 */
en_result_t Spi_ClearStatusAll(M0P_SPI_TypeDef *SPIx)
{
    SPIx->ICR = (uint32_t)0u;

    return Ok;
}

/**
 * @brief  SPI 中断使能函数.
 * @param  [in] SPIx: SPIx 通道              @ref M0P_SPI_TypeDef
 * @param  [in] enIt: SPI中断                @ref en_spi_it_t
 * @retval en_result_t:
 *         - Ok: SPI中断使能成功
 */
en_result_t Spi_IrqEnable(M0P_SPI_TypeDef *SPIx, en_spi_it_t enIt)
{
    SPIx->CR1 |= (uint32_t)enIt;

    return Ok;
}


/**
 * @brief  SPI 中断禁止函数.
 * @param  [in] SPIx: SPIx 通道              @ref M0P_SPI_TypeDef
 * @param  [in] enIt: SPI中断                @ref en_spi_it_t
 * @retval en_result_t:
 *         - Ok: SPI中断禁止成功
 */
en_result_t Spi_IrqDisable(M0P_SPI_TypeDef *SPIx, en_spi_it_t enIt)
{
    SPIx->CR1 &= ~(uint32_t)enIt;

    return Ok;
}


/**
 * @brief  SPI 总体初始化函数.
 * @param  [in] SPIx: SPIx 通道                 @ref M0P_SPI_TypeDef
 * @param  [in] pstcSpiCfg: 初始化结构体        @ref stc_spi_cfg_t
 * @retval en_result_t:
 *         - Ok: SPI功能初始化成功
 */
en_result_t Spi_Init(M0P_SPI_TypeDef *SPIx, stc_spi_cfg_t *pstcSpiCfg)
{
    ASSERT(NULL != pstcSpiCfg);

    SPIx->CR0 = 0x00000000u;
    SPIx->CR1 = 0u;

    SPIx->CR0 = (uint32_t)pstcSpiCfg->enSpiMode |
                (uint32_t)pstcSpiCfg->enPclkDiv |
                (uint32_t)pstcSpiCfg->enCPOL    |
                (uint32_t)pstcSpiCfg->enCPHA    |
                (uint32_t)pstcSpiCfg->enBitOrder|
                (uint32_t)pstcSpiCfg->enDataWidth|
                (uint32_t)pstcSpiCfg->enNssMode|
                (uint32_t)pstcSpiCfg->enTransferDirection|
                (uint32_t)pstcSpiCfg->enSampleDelay;
    
    SPIx->CR1 = (uint32_t)pstcSpiCfg->enDMAReq;

    return Ok;
}

/**
 * @brief  开启SPI模块.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval None
 */
void Spi_Enable(M0P_SPI_TypeDef *SPIx)
{
    SPIx->CR0_f.EN = 1u;
}


/**
 * @brief  禁止SPI模块.
 * @param  [in] SPIx: SPI结构体 @ref SPI_TypeDef
 * @retval None
 */
void Spi_Disable(M0P_SPI_TypeDef *SPIx)
{
    SPIx->CR0_f.EN = 0u;
}

/**
 * @brief  SPI 配置主发送的电平.
 * @param  [in] SPIx: SPIx 通道              @ref M0P_SPI_TypeDef
 * @param  [in] bFlag: 高低电平              @ref boolean_t
 * @retval None
 * @note   SPI模块作为主机 配置NSS片选输出(到从机)，只有当SSM=1，即硬件控制输出(外部IO管脚NSS输出)时有效.
 */
void Spi_SetCS(M0P_SPI_TypeDef *SPIx, boolean_t bFlag)
{
    SPIx->SSI = bFlag;
}

/**
 * @brief  SPI模块作为从机时，配置NSS片选使能或禁止，只有当SSM=1，即软件控制(非外部IO管脚输入)时有效.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] enNSSCfg: NSS选择 @ref en_spi_ssi_t
 * @retval None
 */
void Spi_SlaveNSSConfig(M0P_SPI_TypeDef *SPIx, en_spi_ssi_t enNSSCfg)
{
    SPIx->SSI = enNSSCfg;
}

/**
 * @brief  设定SPI 半双工通信方式选择.
 * @param  [in] SPIx: SPI结构体变量 @ref SPI_TypeDef
 * @param  [in] enHalfDirection: 半双工通信方式选择 @ref en_spi_half_t
 * @retval None
 */
void Spi_SetHalfDuplexDirection(M0P_SPI_TypeDef *SPIx, en_spi_half_t enHalfDirection)
{
    SPIx->HDOE = enHalfDirection;
}


/**
 * @brief  SPI 发送一字节函数.
 * @param  [in] SPIx: SPIx 通道                       @ref M0P_SPI_TypeDef
 * @param  [in] u8Data: 发送一字节数据
 * @retval en_result_t:
 *         - Ok: 发送一字节成功
 */
en_result_t Spi_SendData(M0P_SPI_TypeDef *SPIx, uint8_t u8Data)
{
    while (FALSE == SPIx->SR_f.TXE) {;}
    SPIx->DR = u8Data;

    return Ok;
}

/**
 * @brief  SPI 写和读一字节函数.
 * @param  [in] SPIx: SPIx 通道                       @ref M0P_SPI_TypeDef
 * @param  [in] u8Data: 发送一字节数据
 * @retval uint8_t: 接收一字节数据
 */
uint8_t Spi_RWByte(M0P_SPI_TypeDef *SPIx, uint8_t u8Data)
{
    while (FALSE == SPIx->SR_f.TXE) {;}
    SPIx->DR = u8Data;
    while (FALSE == SPIx->SR_f.RXNE) {;}
    return SPIx->DR;
}

/**
 * @brief  SPI 从机预准备第一字节数据.
 * @param  [in] SPIx: SPIx 通道                       @ref M0P_SPI_TypeDef
 * @param  [in] u8Data: 预准备第一字节数据
 * @retval None
 */
void Spi_Slave_DummyWriteData(M0P_SPI_TypeDef *SPIx, uint8_t u8Data)
{
    while (FALSE == SPIx->SR_f.TXE) {;}
    SPIx->DR = u8Data;
}


/**
 * @brief  SPI 连续发送多字节函数.
 * @param  [in] SPIx: SPIx 通道                       @ref M0P_SPI_TypeDef
 * @param  [in] pu8Buf: 发送数据指针
 * @param  [in] u32Len: 发送数据长度
 * @retval en_result_t:
 *         - Ok: 发送多字节成功
 */
en_result_t Spi_SendBuf(M0P_SPI_TypeDef *SPIx, uint8_t *pu8Buf, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    volatile uint8_t  u8data = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        while (FALSE == SPIx->SR_f.TXE) {;}
        SPIx->DR = pu8Buf[u32Index];
        while (FALSE == SPIx->SR_f.RXNE) {;}
        u8data = SPIx->DR;
    }

    while (FALSE == SPIx->SR_f.TXE) {;}
    while (TRUE == SPIx->SR_f.BUSY) {;}

    return Ok;
}


/**
 * @brief  SPI 接收一字节函数.
 * @param  [in] SPIx: SPIx 通道                       @ref M0P_SPI_TypeDef
 * @retval uint8_t:接收一字节
 */
uint8_t Spi_ReceiveData(M0P_SPI_TypeDef *SPIx)
{
    return SPIx->DR;
}

/**
 * @brief  SPI 连续接收多字节函数.
 * @param  [in] SPIx: SPIx 通道                       @ref M0P_SPI_TypeDef
 * @param  [in] pu8Buf: 接收数据指针
 * @param  [in] u32Len: 接收数据长度
 * @retval en_result_t:
 *         - Ok: 接收多字节成功
 */
en_result_t Spi_ReceiveBuf(M0P_SPI_TypeDef *SPIx, uint8_t *pu8Buf, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        while (FALSE == SPIx->SR_f.TXE) {;}
        SPIx->DR = 0x00;
        while (FALSE == SPIx->SR_f.RXNE) {;}
        pu8Buf[u32Index] = SPIx->DR;
    }

    while (TRUE == SPIx->SR_f.BUSY) {;}

    return Ok;
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

