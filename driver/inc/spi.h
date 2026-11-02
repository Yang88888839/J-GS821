/**
 ******************************************************************************
 * @file   spi.h
 *
 * @brief This file contains all the functions prototypes of the SPI driver
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

#ifndef __SPI_H__
#define __SPI_H__

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
 * @addtogroup DDL_SPI SPI模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Types SPI全局类型定义
 * @{
 */


/**
 * @brief  SPI 功能使能设置
 */
typedef enum
{
    SpiMskEnable  = 0x4u, /*!< SPI模块使能 */
    SpiMskDisable = 0u,   /*!< SPI模块禁止 */
} en_spi_en_t;

/**
 * @brief  SPI 模式配置
 */
typedef enum
{
    SpiMskSlave  = 0x00u,  /*!< 从机 */
    SpiMskMaster = 0x40u,  /*!< 主机 */
} en_spi_mode_t;

/**
 * @brief  SPI 时钟极性设置
 */
typedef enum
{
    SpiMskcpollow  = 0x00u, /*!< 极性为低 */
    SpiMskcpolhigh = 0x20u, /*!< 极性为高 */
} en_spi_cpol_t;

/**
 * @brief  SPI 时钟相位设置
 */
typedef enum
{
    SpiMskCphafirst  = 0x00u, /*!< 第一边沿采样(前边沿采样/后边沿移位) */
    SpiMskCphasecond = 0x10u, /*!< 第二边沿采样(前边沿移位/后边沿采样) */
} en_spi_cpha_t;

/**
 * @brief  SPI 时钟分频配置
 */
typedef enum
{
    SpiClkMskDiv2   = 0x00u, /*!< PCLK 2分频 */
    SpiClkMskDiv4   = 0x02u, /*!< PCLK 4分频 */
    SpiClkMskDiv8   = 0x04u, /*!< PCLK 8分频 */
    SpiClkMskDiv16  = 0x06u, /*!< PCLK 16分频 */
    SpiClkMskDiv32  = 0x08u, /*!< PCLK 32分频 */
    SpiClkMskDiv64  = 0x0Au, /*!< PCLK 64分频 */
    SpiClkMskDiv128 = 0x0Cu, /*!< PCLK 128分频 */
} en_spi_clk_div_t;

/**
 * @brief  SPI 数据帧高低位顺序选择
 */
typedef enum
{
    SpiMskMsbFirst = 0x0u,  /*!< 最高有效位MSB收发在前 */
    SpiMskLsbFirst = 0x80u, /*!< 最低有效位LSB收发在前 */
} en_spi_bit_t;

/**
 * @brief  SPI 每帧数据宽度选择
 */
typedef enum
{
    SpiMskWidth4Bit  = 0x300u, /*!< 帧数据宽度:4bit */
    SpiMskWidth5Bit  = 0x400u, /*!< 帧数据宽度:5bit */
    SpiMskWidth6Bit  = 0x500u, /*!< 帧数据宽度:6bit */
    SpiMskWidth7Bit  = 0x600u, /*!< 帧数据宽度:7bit */
    SpiMskWidth8Bit  = 0x700u, /*!< 帧数据宽度:8bit */
    SpiMskWidth9Bit  = 0x800u, /*!< 帧数据宽度:9bit */
    SpiMskWidth10Bit = 0x900u, /*!< 帧数据宽度:10bit */
    SpiMskWidth11Bit = 0xA00u, /*!< 帧数据宽度:11bit */
    SpiMskWidth12Bit = 0xB00u, /*!< 帧数据宽度:12bit */
    SpiMskWidth13Bit = 0xC00u, /*!< 帧数据宽度:13bit */
    SpiMskWidth14Bit = 0xD00u, /*!< 帧数据宽度:14bit */
    SpiMskWidth15Bit = 0xE00u, /*!< 帧数据宽度:15bit */
    SpiMskWidth16Bit = 0xF00u, /*!< 帧数据宽度:16bit */
} en_spi_width_t;

/**
 * @brief  SPI从机选择配置
 */
typedef enum
{
    SpiMskNssByIo  = 0u,      /*!< 主机模式/从机模式: NSS管脚决定从机选择输入值 */
    SpiMskNssBySsi = 0x1000u, /*!< 主机模式:SSI决定从机选择输出值; 从机模式:SSI决定从机选择输入值 */
} en_spi_nss_mode_t;

/**
 * @brief  SPI 内部从机选择
 */
typedef enum
{
    SpiSsiNssEnable  = 0u, /*!< 片选使能(主机:输出低电平;从机:被选中) */
    SpiSsiNssDisable = 1u, /*!< 片选禁止(主机:输出高电平;从机:不被选中) */
} en_spi_ssi_t;

/**
 * @brief  SPI 通讯方式选择
 */
typedef enum
{
    SpiMskFullDuplex  = 0u, /*!< 全双工 */
    SpiMskSimplexTx   = 0x2000u, /*!< 单工只发 */
    SpiMskSimplexRx   = 0x4000u, /*!< 单工只收 */
    SpiMskHalfDuplex  = 0x6000u, /*!< 单线半双工 */
} en_spi_dir_t;

/**
 * @brief  SPI 半双工传输方向选择
 */
typedef enum
{
    SpiHalfDuplexRx   = 0u, /*!< 单工只收 */
    SpiHalfDuplexTx   = 1u, /*!< 单工只发 */
} en_spi_half_t;

/**
* @brief  SPI 主机模式延后采样配置
 */
typedef enum
{
    SpiMskSampleNormal   = 0u,      /*!< 正常采样 */
    SpiMskSampleDelay    = 0x8000u, /*!< 延后半个SCK周期采样 */
} en_spi_sample_t;


/**
* @brief  SPI DMA传输配置
 */
typedef enum
{
    SpiMskDmaDisable     = 0u,     /*!< SPI触发DMA禁止 */
    SpiMskDmaRxEnable    = 0x100u, /*!< SPI接收 DMA传输 */
    SpiMskDmaTxEnable    = 0x200u, /*!< SPI发送 DMA传输 */
    SpiMskDmaTxRxEnable  = 0x300u, /*!< SPI接收发送 DMA传输 */
} en_spi_dma_t;

/**
 * @brief  SPI 状态
 */
typedef enum
{
    SpiStaSslvl   = 0x200u,/*!< 从机选择输入的(电平)状态,仅当CR0.SSM=0时 */
    SpiStaBusy    = 0x100u,/*!< SPI总线忙状态 */
    SpiStaMdf     = 0x80u, /*!< 主机模式错误状态(主机模式下从机选择输入为低) */
    SpiStaSserr   = 0x40u, /*!< 从机模式下的从机选择错误状态 */
    SpiStaOvf     = 0x20u, /*!< 接收缓冲上溢错误状态 */
    SpiStaUdf     = 0x10u, /*!< 从机模式下的发送缓冲下溢错误状态 */
    SpiStaSsr     = 0x08u, /*!< 从机选择输入上升沿状态 */
    SpiStaSsf     = 0x04u, /*!< 从机选择输入下降沿状态 */
    SpiStaRxne    = 0x02u, /*!< 接受缓冲器非空状态 */
    SpiStaTxe     = 0x01u, /*!< 发送缓冲器器空状态*/
} en_spi_status_t;

/**
 * @brief  SPI 中断使能&标志
 */
typedef enum
{
    SpiMskMdf     = 0x80u, /*!< 主机模式错误中断/标志(主机模式下从机选择输入为低) */
    SpiMskSserr   = 0x40u, /*!< 从机模式下的从机选择错误中断/标志 */
    SpiMskOvf     = 0x20u, /*!< 接收缓冲上溢错误中断/标志 */
    SpiMskUdf     = 0x10u, /*!< 从机模式下的发送缓冲下溢错误中断/标志 */
    SpiMskSsr     = 0x08u, /*!< 从机选择输入上升沿中断/标志 */
    SpiMskSsf     = 0x04u, /*!< 从机选择输入下降沿中断/标志 */
    SpiMskRxne    = 0x02u, /*!< 接受缓冲器非空中断/标志 */
    SpiMskTxe     = 0x01u, /*!< 发送缓冲器器空中断/标志*/
} en_spi_it_t;


/**
 * @brief  SPI 总体配置结构体
 */
typedef struct
{
    en_spi_clk_div_t  enPclkDiv;     /*!< 波特率分频 */ 
    en_spi_cpha_t     enCPHA;        /*!< 时钟相位选择 */  
    en_spi_cpol_t     enCPOL;        /*!< 时钟极性选择 */   
    en_spi_mode_t     enSpiMode;     /*!< 主从模式选择 */
    en_spi_bit_t      enBitOrder;    /*!< 数据传输高低位顺序选择 */
    en_spi_width_t    enDataWidth;   /*!< 每帧的数据宽度 */
    en_spi_nss_mode_t enNssMode;     /*!< 配置NSS片选信号是硬件控制还是软件控制 */  
    en_spi_dir_t      enTransferDirection;  /*!< 通信方式选择 */
    en_spi_sample_t   enSampleDelay; /*!< 主机模式延后采样 */ 
    en_spi_dma_t      enDMAReq;      /*!< DMA传输配置 */
}stc_spi_cfg_t;

/**
 * @}
 */


/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup SPI_Global_Functions SPI全局函数定义
 * @{
 */

boolean_t Spi_GetStatus(M0P_SPI_TypeDef *SPIx, en_spi_status_t enStatus);
en_result_t Spi_ClearStatus(M0P_SPI_TypeDef *SPIx,en_spi_status_t enStatus);
en_result_t Spi_ClearStatusAll(M0P_SPI_TypeDef *SPIx);
en_result_t Spi_IrqEnable(M0P_SPI_TypeDef *SPIx, en_spi_it_t enIt);
en_result_t Spi_IrqDisable(M0P_SPI_TypeDef *SPIx, en_spi_it_t enIt);
en_result_t Spi_Init(M0P_SPI_TypeDef *SPIx, stc_spi_cfg_t *pstcSpiCfg);
void Spi_Enable(M0P_SPI_TypeDef *SPIx);
void Spi_Disable(M0P_SPI_TypeDef *SPIx);
void Spi_SetCS(M0P_SPI_TypeDef *SPIx, boolean_t bFlag);
void Spi_SlaveNSSConfig(M0P_SPI_TypeDef *SPIx, en_spi_ssi_t enNSSCfg);
uint8_t Spi_RWByte(M0P_SPI_TypeDef *SPIx, uint8_t u8Data);
en_result_t Spi_SendData(M0P_SPI_TypeDef *SPIx, uint8_t u8Data);
void Spi_Slave_DummyWriteData(M0P_SPI_TypeDef *SPIx, uint8_t u8Data);
en_result_t Spi_SendBuf(M0P_SPI_TypeDef *SPIx, uint8_t *pu8Buf, uint32_t u32Len);
uint8_t Spi_ReceiveData(M0P_SPI_TypeDef *SPIx);
en_result_t Spi_ReceiveBuf(M0P_SPI_TypeDef *SPIx, uint8_t *pu8Buf, uint32_t u32Len);


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

#endif /* __SPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

