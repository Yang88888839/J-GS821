/**
 ******************************************************************************
 * @file   uart.h
 *
 * @brief This file contains all the functions prototypes of the USART driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-10-30       MADS            First version
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


#ifndef __UART_H__
#define __UART_H__

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
 * @addtogroup DDL_UART USART模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup UART_Global_Types USART全局类型定义
 * @{
 */
 
/**
 * @brief  usart 波特率设置模式选择类型定义
 */
typedef enum
{
    UsartBrrUART = 0u, /*!< UART模式 */
    UsartBrrSYNC = 1u, /*!< 同步串口模式 */
    UsartBrrSC   = 2u, /*!< 智能卡模式 */
    UsartBrrIR   = 3u, /*!< 红外模式 */
    UsartBrrLIN  = 4u, /*!< LIN模式 */
} en_usart_brr_mode_t;

/**
 * @brief  usart 采样分频配置(CR1.OVER8 同步串口模式和智能卡模式需设置为0, 红外模式无效)类型定义
 */
typedef enum
{
    UsartMskOver16 = 0u,     /*!< 16倍采样 */
    UsartMskOver8  = 0x80u,  /*!< 8倍采样 */
} en_usart_over_sample_t;

/**
 * @brief  usart 采样次数配置(仅限同步串口模式和智能卡模式)类型定义
 */
typedef enum
{
    UsartSyncSampleCnt = 4u,   /*!< 同步串口模式采样次数4 */
    UsartIrSampleCnt   = 16u,  /*!< 红外模式采样次数16 */
} en_usart_sample_cnt_t;

/**
 * @brief  ussart 智能卡模式 1位数据传输期间的基本时钟数(CR3.BCN)类型定义
 */
typedef enum
{
    UsartMskScBitClk16   = 16u,  /*!< 1位数据传输期间的基本时钟数16 */
    UsartMskScBitClk32   = 32u,  /*!< 1位数据传输期间的基本时钟数32 */
    UsartMskScBitClk64   = 64u,  /*!< 1位数据传输期间的基本时钟数64 */
    UsartMskScBitClk128  = 128u, /*!< 1位数据传输期间的基本时钟数128 */
    UsartMskScBitClk186  = 186u, /*!< 1位数据传输期间的基本时钟数186 */
    UsartMskScBitClk256  = 256u, /*!< 1位数据传输期间的基本时钟数256 */
    UsartMskScBitClk372  = 372u, /*!< 1位数据传输期间的基本时钟数372 */
    UsartMskScBitClk512  = 512u, /*!< 1位数据传输期间的基本时钟数512 */
} en_usart_sc_bcn_t;
 
/**
 * @brief  usart 收发端口符合使能/禁止配置(CR1.COMB异步串口模式时)类型定义
 */
typedef enum
{
    UsartMskTxRxSeparate = 0u,      /*!< TxD和RxD分开使用 */
    UsartMskTxRxCombine  = 0x1000u, /*!< 异步串口模式时, TxD和RxD合并用TxD端口 */
} en_usart_uart_comb_t;

/**
 * @brief  usart RxD起始位检测方式配置(CR1.SBS异步串口模式时)类型定义
 */
typedef enum
{
    UsartMskStartRxEdge   = 0u,     /*!< 接收数据RxD引脚边沿信号作为起始位(USART_CR2.RXINV=0为下降沿，USART_CR2.RXINV=1为上升沿)*/
    UsartMskStartRxLevel  = 0x800u, /*!< 接收数据RxD引脚电平信号作为起始位(USART_CR2.RXINV=0为低电平，USART_CR2.RXINV=1为高电平) */
} en_usart_uart_start_t;

/**
 * @brief  usart MSB/LSB方式选择(CR1.SBS)类型定义
 */
typedef enum
{
    UsartMskLSBFirst  = 0u,    /*!< LSB优先方式*/
    UsartMskMSBFirst  = 0x40u, /*!< MSB优先方式 */
} en_usart_bit_order_t;

/**
 * @brief  usart 异步串口模的时钟控制配置(CR2.CLKC)类型定义
 */
typedef enum
{
    UsartMskUartInnerClkNoOutput    = 0u,     /*!< UART模式: 内部生成的时钟，不输出到CK管脚 */
    UsartMskUartInnerClkWithOutput  = 0x100u, /*!< UART模式: 内部生成的时钟，输出到CK管脚 */
    UsartMskSyncInnerClkWithOutput  = 0x100u, /*!< 同步串口模式: 内部生成的时钟，输出到CK管脚 */
    UsartMskSyncExtClk              = 0x300u, /*!< 同步串口模式: 外部输入时钟，频率和波特率相同 */
    UsartMskScInnerClkNoOutput      = 0u,     /*!< 智能卡模式: 内部生成的时钟，不输出到CK管脚 */
    UsartMskScInnerClkWithOutput    = 0x100u, /*!< 智能卡模式: 内部生成的时钟，输出到CK管脚 */
} en_usart_clk_ctrl_t;

/**
 * @brief  usart Tx/Rx引脚互换控制配置(CR2.SWAP)类型定义
 */
typedef enum
{
    UsartMskTxRxSwapDisable = 0u,    /*!< TxD/RxD引脚功能不互换 */
    UsartMskTxRxSwapEnable  = 0x80u, /*!< TxD/RxD引脚功能互换 */
} en_usart_port_swap_t;

/**
 * @brief  usart Tx/Rx信号反相控制配置(CR2.TXINV&RXINV)类型定义
 */
typedef enum
{
    UsartMskTxRxInvDisable = 0u,    /*!< TxD/RxD信号不反相 */
    UsartMskRxInvEnable    = 0x10u, /*!< RxD输入信号反相 */
    UsartMskTxInvEnable    = 0x20u, /*!< TxD输出信号反相 */
    UsartMskTxRxInvEnable  = 0x30u, /*!< TxD输出、RxD输入信号都反相 */
} en_usart_txrx_inv_t;

/**
 * @brief  usart 硬件流控功能配置(CR2.CTSEN&RTSEN)类型定义
 */
typedef enum
{
    UsartMskHwFlowDisable      = 0u,   /*!< 硬件流控CTS和RTS功能禁止 */
    UsartMskHwFlowRtsEnable    = 0x4u, /*!< 硬件流控RTS功能使能 */
    UsartMskHwFlowCtsEnable    = 0x8u, /*!< 硬件流控CTS功能使能 */
    UsartMskHwFlowCtsRtsEnable = 0xCu, /*!< 硬件流控CTS和RTS功能使能 */
} en_usart_hw_flow_t;

/**
 * @brief  usart DMA 传输功能配置(CR2.TXDMAEN&RXDMAEN)类型定义
 */
typedef enum
{
    UsartMskDmaDisable    = 0u,   /*!< Tx和RxDMA传输禁止 */
    UsartMskDmaRxEnable   = 0x1u, /*!< RxD DMA传输使能 */
    UsartMskDmaTxEnable   = 0x2u, /*!< TxD DMA传输使能 */
    UsartMskDmaTxRxEnable = 0x3u, /*!< TxD&RxD DMA传输使能*/
} en_usart_dma_t;

/**
 * @brief  usart 多处理器通信 静默模式（CR1.SLME)配置类型定义
 */
typedef enum
{
    UsartMskUartMulNormal   = 0u,      /*!< 正常模式 */
    UsartMskUartMulSilent   = 0x4000u, /*!< 静默模式 */
} en_usart_uart_silent_t;

/**
 * @brief  usart 多处理器通信 使能(CR1.MPE)配置类型定义
 */
typedef enum
{
    UsartMskUartMulProDisable  = 0u,      /*!< 多处理器通信功能无效 */
    UsartMskUartMulProEnable   = 0x2000u, /*!< 多处理器通信功能有效 */
} en_usart_uart_multi_t;

/**
 * @brief  usart 多处理器通信ID位配置(TDR.MPID)类型定义
 */
typedef enum
{
    UsartMskUartMulData  = 0u,     /*!< 发送数据 */
    UsartMskUartMulID    = 0x200u, /*!< 发送ID */
} en_usart_uart_multi_id_t;


/**
 * @brief  usart 通道采样分频配置(CR1.CHLEN 同步串口模式和智能卡模式需设置为0, 红外模式无效)类型定义
 */
typedef enum
{
    UsartMskFrame8Bit  = 0u,     /*!< 帧长度8bit */
    UsartMskFrame9Bit  = 0x10u,  /*!< 帧长度9bit */
} en_usart_length_t;

/**
 * @brief  usart 奇偶校验配置(CR1.PCE&PS)类型定义
 */
typedef enum
{
    UsartMskFParityNone  = 0u,    /*!< 无校验 */
    UsartMskFParityEven  = 0x8u,  /*!< 偶校验 */
    UsartMskFParityOdd   = 0xCu,  /*!< 奇校验 */
} en_usart_parity_t;

/**
 * @brief  ussart stop长度选择(CR1.STOP)类型定义
 */
typedef enum
{
    UsartMskStop1bit   = 0x00u, /*!< 1位停止位 */
    UsartMskStop2bit   = 0x20u, /*!< 2位停止位 */
} en_usart_stop_t;

/**
 * @brief  usart 接收/发送使能选择(CR1.TE&RE)类型定义
 */
typedef enum
{
    UsartMskTxRxDisable = 0x0u, /*!< 接收 发送都禁止 */
    UsartMskRxEnable    = 0x1u, /*!< 接收使能 */
    UsartMskTxEnable    = 0x2u, /*!< 发送使能 */
    UsartMskTxRxEnable  = 0x3u, /*!< 接收 发送都使能 */
} en_usart_transfer_t;

/**
 * @brief  usart 异步串口/同步串口选择(CR2.SYNC)类型定义
 */
typedef enum
{
    UsartMskUartMode  = 0x0u,  /*!< 异步串口 */
    UsartMskSyncMode  = 0x40u, /*!< 同步串口 */
} en_usart_sync_t;

/**
 * @brief  ussart 红外模式 红外载波选择(CR3.IRCW)类型定义
 */
typedef enum
{
    UsartMskIrMode3_16  = 0x0u,    /*!< 3/16模式 */
    UsartMskIrMode38K   = 0x4000u, /*!< 38K载波模式 */
} en_usart_ir_cw_t;

/**
 * @brief  ussart 红外模式 38K 调制方式(CR3.IRMOD)类型定义
 */
typedef enum
{
    UsartMskIr38kMode0  = 0x0u,    /*!< 数据0时输出38K载波 */
    UsartMskIr38kMode1  = 0x8000u, /*!< 数据1时输出38K载波 */
} en_usart_ir_mode_t;

/**
 * @brief  ussart 智能卡模式 输出边沿整形(CR3.SMCPU)类型定义
 */
typedef enum
{
    UsartMskSc0PclkHighLevel  = 0x000u, /*!< 开漏时输出无边沿整形 */
    UsartMskSc1PclkHighLevel  = 0x100u, /*!< 开漏时强输出1个PCLK周期COMS高电平 */
    UsartMskSc2PclkHighLevel  = 0x200u, /*!< 开漏时强输出2个PCLK周期COMS高电平 */
    UsartMskSc4PclkHighLevel  = 0x300u, /*!< 开漏时强输出4个PCLK周期COMS高电平 */
} en_usart_sc_smcpu_t;

/**
 * @brief  ussart 多功能定时器功能(CR1.TOE)类型定义
 */
typedef enum
{
    UsartToStop      = 0x0u,  /*!< 停止多功能定时器 */
    UsartToGtim      = 0x1u,  /*!< 通用定时器功能 */
    UsartToRxTim     = 0x2u,  /*!< 接收定时功能 */
    UsartToFrameTim  = 0x3u,  /*!< 数据帧间定时(超时)功能 */
    UsartToLinBreak  = 0x4u,  /*!< LIN模式下,间隔段计数使能 */
    UsartToAutoBrr   = 0x5u,  /*!< LIN模式或UART模式下, 波特率自动检测使能 */
} en_usart_to_mode_t;

/**
 * @brief  ussart 波特率生成预分频(BRR.PSC)类型定义
 */
typedef enum
{
    UsartPclkDiv1   = 0x0u, /*!< PCLK */
    UsartPclkDiv4   = 0x1u, /*!< PCLK/4 */
    UsartPclkDiv16  = 0x2u, /*!< PCLK/16 */
    UsartPclkDiv64  = 0x3u, /*!< PCLK/64 */
} en_usart_clk_div_t;

/**
 * @brief  ussart 波特率自动检测功能(CR3.ABRE)类型定义
 */
typedef enum
{
    UsartMskBrrAutoDetDisable  = 0x0u, /*!< 波特率自动检测停止 */
    UsartMskBrrAutoDetEnable   = 0x4u, /*!< 波特率自动检测使能 */
} en_usart_brr_det_t;


/**
 * @brief  uart 状态/中断标志&清除 类型定义
 */
typedef enum
{
    UsartTxE  = 0u,  /*!< TXbuff空 标志 */
    UsartTC   = 1u,  /*!< 发送数据完成 标志 */
    UsartRC   = 2u,  /*!< 接收数据完成 标志 */
    UsartPE   = 3u,  /*!< 奇偶校验错误 标志 */
    UsartFE   = 4u,  /*!< 帧错误 标志 */
    UsartOR   = 5u,  /*!< 上溢错误 标志 */
    UsartTO   = 6u,  /*!< 定时器匹配或溢出 标志 */
    UsartMPB  = 8u,  /*!< 多处理器通信标志: 0: 接收数据为数据; 1:接收数据为ID*/
    UsartAM   = 9u,  /*!< 多处理器通信地址匹配 标志 */
    UsartCtsV = 10u, /*!< CTS管脚当前电平 */
    UsartCts  = 11u, /*!< CTS信号翻转 标志 */
    UsartABR  = 12u, /*!< 自动波特率检测 标志 */
    UsartLBD  = 13u, /*!< (LIN模式)同步间隔段检测 标志 */
    UsartDWK  = 14u, /*!< (UART/IR/LIN模式)RxD唤醒 标志 */
} en_uart_status_t;

/**
 * @brief  uart 中断使能/清除类型定义
 */
typedef enum
{
    UsartTxEIrq = 0u,  /*!< TXbuff空中断 */
    UsartTxIrq  = 1u,  /*!< 发送数据完成中断 */
    UsartRxIrq  = 2u,  /*!< 接收数据完成中断 */
    UsartPEIrq  = 3u,  /*!< 奇偶校验错误中断 */
    UsartFEIrq  = 4u,  /*!< 帧错误中断 */
    UsartORIrq  = 5u,  /*!< 上溢错误中断 */
    UsartTOIrq  = 6u,  /*!< 定时器匹配或溢出中断 */
    UsartAMIrq  = 9u,  /*!< 多处理器通信地址匹配中断 */
    UsartCtsIrq = 11u, /*!< CTS信号翻转中断 */
    UsartABRIrq = 12u, /*!< 自动波特率检测中断 */
    UsartLBDIrq = 13u, /*!< (LIN模式)同步间隔段检测中断 */
    UsartDWKIrq = 14u, /*!< (UART/IR/LIN模式)RxD边沿中断 */
} en_uart_irq_sel_t;




/**
 * @brief  USART 高级功能初始化配置
 */
typedef struct
{
    en_usart_uart_comb_t   enTxRxCombine;        /*!< 收发端口复合使能位  */
    en_usart_uart_start_t  enStartBitDetectMode; /*!< 接收起始位检测模式  */
    en_usart_bit_order_t   enMSBFirst;           /*!< MSB/LSB方式选择     */
    en_usart_clk_ctrl_t    enClockCtrl;          /*!< 时钟控制位          */
    en_usart_port_swap_t   enTxRxSwap;           /*!< TX/RX引脚互换控制位 */
    en_usart_txrx_inv_t    enTxRxPinLevelInvert; /*!< 输出信号反向控制位  */
    en_usart_hw_flow_t     enHWFlowCtrl;         /*!< 硬件流控            */
    en_usart_dma_t         enDMATxRxTransfer;    /*!< DMA传输控制         */
} stc_usart_adv_feature_init_t;

/**
 * @brief  USART 多处理机初始化配置
 */
typedef struct
{
    /* Multi Processor Enable Type */
    en_usart_uart_multi_t    enMultiProEn; /*!< UART多处理器功能使能控制 */
    /* Slaver Type */
    en_usart_uart_silent_t   enMultiProSilentMode; /*!< UART多处理静默模式 */
    uint8_t  u8SlaveAddr;           /*!< 从机地址      取值范围0 ~ 127 */
    uint8_t  u8SlaveAddrMsk;        /*!< 从机地址掩码  取值范围0 ~ 127 */
} stc_uart_multimode_t;


/**
 * @brief  USART UART初始化
 */
typedef struct
{
    /* UART Base Type */
    uint32_t            u32BaudRate;   /*!< UART 通信波特率配置(bps) */
    uint32_t            u32Pclk;       /*!< UART 通信当前PCLK时钟频率 */
    en_usart_over_sample_t   enSampleMode;  /*!< UART 采样模式设定16倍/8倍采样 */
    en_usart_length_t   enFrameLength; /*!< 数据帧长度8/9bits */
    en_usart_parity_t   enParity;      /*!< 奇偶校验选择 */
    en_usart_stop_t     enStopBit;     /*!< 停止位长度 */
    en_usart_transfer_t enTransMode;   /*!< 数据传输方式 */

    /* UART Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 */
} stc_usart_uart_init_t;

/**
 * @brief  USART 同步串口初始化
 */
typedef struct
{
    /* Clock Sync Base Type */
    uint32_t            u32BaudRate;  /*!< 通信波特率配置(bps) */
    uint32_t            u32Pclk;      /*!< 通信当前PCLK时钟频率 */
    en_usart_transfer_t enTransMode; /*!< 数据传输方式 */

    /* Clock Sync Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 */
} stc_usart_clksync_init_t;

/**
 * @brief  USART 红外模式初始化配置
 */
typedef struct
{
    /* IR Base Type */
    uint32_t            u32BaudRate;   /*!< 通信波特率配置(bps) */
    uint32_t            u32Pclk;       /*!< 通信当前PCLK时钟频率 */
    en_usart_length_t   enFrameLength; /*!< 数据帧长度8/9bits */
    en_usart_parity_t   enParity;     /*!< 奇偶校验选择 */
    en_usart_transfer_t enTransMode;   /*!< 数据传输方式 */
    en_usart_ir_cw_t    enIRMode;      /*!< 红外模式 */
    en_usart_ir_mode_t  enIRMod38K;    /*!< 38K调制方式 */
    uint32_t      u32HighLevelTime38K; /*!< 38K载波高电平维持时间(μs) */
    uint32_t      u32LowLevelTime38K;  /*!< 38K载波低电平维持时间(μs) */

    /* IR Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 */
} stc_usart_ir_init_t;

/**
 * @brief  LIN LIN模式初始化配置
 */
typedef struct
{
    /* LIN Base Type */
    uint32_t          u32BaudRate;  /*!< LIN 通信波特率配置(bps) */
    uint32_t          u32Pclk;      /*!< LIN 通信当前PCLK时钟频率 */
    en_usart_over_sample_t enSampleMode; /*!< UART 采样模式设定16倍/8倍采样 */

    /* UART Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 */
} stc_usart_lin_init_t;

/**
 * @brief  SC 智能卡模式初始化配置
 */
typedef struct
{
    /* SC Base Type */
    uint32_t            u32DataBaudRate; /*!< IO上的数据传输波特率配置(bps) */
    uint32_t            u32Pclk;         /*!< 通信当前PCLK时钟频率 */
    en_usart_parity_t   enParity;        /*!< 奇偶校验选择，标准智能卡均采用偶校验 */
    en_usart_sc_bcn_t   enFiBCN;         /*!< 一位数据传输时的基本时钟数 */
    en_usart_sc_smcpu_t enIOPUTime;      /*!< 开漏时强输出CMOS高电平时间，单位:1/pclk */

    /* SC Advanced Feature Type */
    stc_usart_adv_feature_init_t stcAdvFeature; /*!< USART高级功能配置 */
} stc_usart_smart_card_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Macros USART全局宏定义
 * @{
 */
#define USART_CR1_RE        (0x1u)
#define USART_CR1_TE        (0x2u)
#define USART_CR2_RXDMAEN   (0x1u)
#define USART_CR2_TXDMAEN   (0x2u)

#define USART_CR3_BCN_Pos   (5u)
#define USART_CR3_SMCPU_Pos (8u)
#define USART_CR3_SCEN      (0x10u)


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
 * @addtogroup UART_Global_Functions USART全局函数定义
 * @{
 */


/* USART  UART初始化 */
en_result_t Usart_Uart_Init(M0P_USART_TypeDef *USARTx, stc_usart_uart_init_t *pstcUartCfg);

/* USART 自动波特率检测和检测后设置 */
void Usart_ABR_Detect(M0P_USART_TypeDef* USARTx, en_usart_clk_div_t enPSC);
void Usart_Detect_ABR_Set(M0P_USART_TypeDef* USARTx, uint32_t u32Pclk);
/* USART 波特率配置 */  
uint32_t Usart_BaudRateCal(M0P_USART_TypeDef* USARTx, en_usart_brr_mode_t enBaudRateSetMode, uint32_t u32BaudRate, uint32_t u32PCLK, uint32_t u32SampMode);

/* USART 单线模式使能/禁止 */
void Usart_HdModeEnable(M0P_USART_TypeDef *USARTx);
void Usart_HdModeDisable(M0P_USART_TypeDef *USARTx);

/* USART模块多机模式设置函数 */
en_result_t Usart_SetMultiMode(M0P_USART_TypeDef *USARTx, stc_uart_multimode_t *pstcMultiCfg);
en_result_t Usart_SetSaddr(M0P_USART_TypeDef *USARTx, uint8_t u8Addr, uint8_t u8SlaveAddrMsk);

/* 数据收发操作 */
/* 数据查询模式发送 */
en_result_t Usart_SendDataPoll(M0P_USART_TypeDef *USARTx, uint16_t u16Data);
en_result_t Usart_SendDataPollTimeOut(M0P_USART_TypeDef *USARTx, uint16_t u16Data, uint32_t u32TimeOut);
/* 数据中断模式发送 */
en_result_t Usart_SendDataIt(M0P_USART_TypeDef *USARTx, uint16_t u16Data);
uint16_t Usart_ReceiveData(M0P_USART_TypeDef *USARTx);

/* 中断相关设置函数 */
en_result_t Usart_EnableIrq(M0P_USART_TypeDef *USARTx, en_uart_irq_sel_t enIrqSel);
en_result_t Usart_DisableIrq(M0P_USART_TypeDef *USARTx, en_uart_irq_sel_t enIrqSel);
/* 状态位的获取和清除 */
boolean_t Usart_GetIrqEn(M0P_USART_TypeDef *USARTx, en_uart_irq_sel_t enIrqSel);
uint32_t Usart_GetIsr(M0P_USART_TypeDef *USARTx);
en_result_t Usart_ClrIsr(M0P_USART_TypeDef *USARTx);
boolean_t Usart_GetStatus(M0P_USART_TypeDef *USARTx, en_uart_status_t enStatus);
en_result_t Usart_ClrStatus(M0P_USART_TypeDef *USARTx, en_uart_status_t enStatus);

/* 功能使能和禁止 */
en_result_t Usart_TxRxCmd(M0P_USART_TypeDef *USARTx, en_usart_transfer_t enTransferMode);
en_result_t Usart_DmaCmd(M0P_USART_TypeDef *USARTx, en_usart_dma_t enDma);

/* 多功能定时器配置 */
void Usart_To_Cfg(M0P_USART_TypeDef* USARTx,en_usart_to_mode_t enToMode, uint32_t u32Totime);

/* USART  同步串口初始化 */
uint32_t Usart_ClkSync_Init(M0P_USART_TypeDef* USARTx, stc_usart_clksync_init_t* pstcClkSyncInit);
/* USART  LIN初始化 */
uint32_t Usart_Lin_Init(M0P_USART_TypeDef* USARTx, stc_usart_lin_init_t* pstcLinInit);
/* USART  IR初始化 */
uint32_t Usart_Ir_Init(M0P_USART_TypeDef* USARTx, stc_usart_ir_init_t* pstcIRInit);
/* USART  IR功能使能/关闭 */
void Usart_Ir_Enable_Cmd(M0P_USART_TypeDef* USARTx, boolean_t bIrCmd);
/* USART  SC初始化 */
uint32_t Usart_Sc_Init(M0P_USART_TypeDef* USARTx, stc_usart_smart_card_init_t* pstcSmartCardInit);
/* USART  SC时钟输出使能/禁止 */
void Usart_Sc_CLK_Enable(M0P_USART_TypeDef* USARTx, boolean_t bEn);
/* USART  SC智能卡中断发送 */
void Usart_Sc_TransmitINT(M0P_USART_TypeDef* USARTx, uint8_t* pu8Data);
/* USART  SC智能卡中断接收 */
void Usart_Sc_ReceiveINT(M0P_USART_TypeDef* USARTx);


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

#endif /* __UART_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



