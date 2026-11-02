/**
 ******************************************************************************
 * @file   lpuart.h
 *
 * @brief This file contains all the functions prototypes of the LPUART driver
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

#ifndef __LPUART_H__
#define __LPUART_H__
/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"


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
 * @addtogroup DDL_LPUART LPUART模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup LPUART_Global_Types LPUART全局类型定义
 * @{
 */

/**
 * @brief  lpuart 的sclk时钟源选择
 */
typedef enum
{
    LPUartMskPclk   = 0u << 11, /*!<  pclk */
    LPUartMskXtl    = 2u << 11, /*!<  外部低速晶振 */
    LPUartMskRcl    = 3u << 11, /*!<  内部低速晶振 */
} en_lpuart_sclksel_t;


/**
 * @brief  lpuart多机模式地址帧/数据帧或者奇偶校验
 */
typedef enum
{
    LPUartDataOrAddr = 0u,   /*!<  多机模式时，通过读写SBUF[8]决定帧为数据帧或地址帧 */
    LPUartEven       = 0x4u, /*!<  非多机模式偶校验 */
    LPUartOdd        = 0x8u, /*!<  非多机模式奇校验 */
} en_lpuart_mmdorck_t;


/**
 * @brief  lpuart多机模式及从机地址和地址掩码配置
 */

typedef struct
{
    uint8_t     u8SlaveAddr;  /*!<  从机地址 */
    uint8_t     u8SaddEn;     /*!<  从机地址掩码 */
} stc_lpuart_multimode_t;


/**
 * @brief  lpuart 四种工作模式选择
 */
typedef enum
{
    LPUartMskMode0 = 0x00u, /*!<  模式0 */
    LPUartMskMode1 = 0x40u, /*!<  模式1 */
    LPUartMskMode2 = 0x80u, /*!<  模式2 */
    LPUartMskMode3 = 0xc0u, /*!<  模式3 */
} en_lpuart_mode_t;

/**
 * @brief  lpuart stop长度选择
 */
typedef enum
{
    LPUart1bit   = 0x0000u,  /*!<  1位停止位 */
    LPUart1_5bit = 0x4000u,  /*!<  1.5位停止位 */
    LPUart2bit   = 0x8000u,  /*!<  2位停止位 */
} en_lpuart_stop_t;

/**
 * @brief  lpuart 功能使能
 */
typedef enum
{
    LPUartRenFunc    = 4u,    /*!<  0-TX; 1-非mode0模式代表RX&TX ,mode0模式代表RX */
    LPUartDmaRxFunc  = 16u,   /*!<  DMA接收功能 */
    LPUartDmaTxFunc  = 17u,   /*!<  DMA发送功能 */
    LPUartRtsFunc    = 18u,   /*!<  硬件流RTS功能 */
    LPUartCtsFunc    = 19u,   /*!<  硬件流CTS功能 */
    LPUartHdFunc     = 22u,   /*!<  单线半双工功能 */
} en_lpuart_func_t;

/**
 * @brief  lpuart中断使能控制
 */
typedef enum
{
    LPUartRxIrq  = 0u,    /*!<  接收中断使能 */
    LPUartTxIrq  = 1u,    /*!<  发送中断使能 */
    LPUartTxEIrq = 8u,    /*!<  TX空中断使能 */
    LPUartPEIrq  = 13u,   /*!<  奇偶校验中断使能 */
    LPUartCtsIrq = 20u,   /*!<  CTS信号翻转中断使能 */
    LPUartFEIrq  = 21u,   /*!<  帧错误中断使能 */
} en_lpuart_irq_sel_t;


/**
 * @brief  lpuart状态标志位
 */
typedef enum
{
    LPUartRC    = 0u,  /*!<  接收数据完成标记 */
    LPUartTC    = 1u,  /*!<  发送数据完成标记 */
    LPUartFE    = 2u,  /*!<  帧错误标记 */
    LPUartTxe   = 3u,  /*!<  TXbuff空标记 */
    LPUartPE    = 4u,  /*!<  奇偶校验错误标记 */
    LPUartCtsIf = 5u,  /*!<  CTS中断标记 */
    LPUartCts   = 6u,  /*!<  CTS信号标记 */
} en_lpuart_status_t;



/**
 * @brief  lpuart 通道采样分频配置
 */
typedef enum
{
    LPUartMsk16Or32Div = 0u,        /*!<  模式0无效，模式1/3为16分频，模式2为32分频 */
    LPUartMsk8Or16Div  = 0x200u,    /*!<  模式0无效，模式1/3为8分频，模式2为16分频 */
    LPUartMsk4Or8Div   = 0x400u,    /*!<  模式0无效，模式1/3为4分频，模式2为8分频 */
} en_lpuart_clkdiv_t;

/**
 * @brief  lpuart XTL为32768时的波特率设定
 */
typedef enum
{
    LPUartBselSetByFormula     = 0u,    /*!<  时钟源不是XTL32K，正常波特率由公式生成 */
    LPUartBselXtl32kSetTo9600  = 1u,    /*!<  时钟源是XTL32K，由调制生成9600波特率 */
    LPUartBselXtl32kSetTo4800  = 2u,    /*!<  时钟源是XTL32K，由调制生成4800波特率 */
} en_lpuart_xtl_bsel_t;

/**
 * @brief  lpuart 通道Mode1和Mode3波特率计算参数
 */
typedef struct
{
    en_lpuart_sclksel_t  enSclkSel;      /*!<  传输时钟源选择 */
    en_lpuart_clkdiv_t   enSclkDiv;      /*!<  采样分频选择 */
    uint32_t             u32Sclk;        /*!<  sclk */
    uint32_t             u32Baud;        /*!<  波特率 */
} stc_lpuart_baud_t;

/**
 * @brief  lpuart 总体配置
 */
typedef struct
{
    en_lpuart_mode_t       enRunMode;      /*!<  四种模式配置 */
    en_lpuart_mmdorck_t    enMmdorCk;      /*!<  校验模式 */
    en_lpuart_stop_t       enStopBit;      /*!<  停止位长度 */
    boolean_t              bHalfDuplex;    /*!<  单线半双工模式 */
    stc_lpuart_baud_t      stcBaud;        /*!<  Mode1/3波特率配置 */
} stc_lpuart_cfg_t;


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
 * @addtogroup LPUART_Global_Functions LPUART全局函数定义
 * @{
 */

/* 总初始化处理 */
en_result_t LPUart_Init(M0P_LPUART_TypeDef *LPUARTx, stc_lpuart_cfg_t *pstcCfg);

/* LPUART 单线模式禁止 */
void LPUart_HdModeDisable(M0P_LPUART_TypeDef *LPUARTx);

/* 中断相关设置函数使能和禁止 */
en_result_t LPUart_EnableIrq(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_irq_sel_t enIrqSel);
en_result_t LPUart_DisableIrq(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_irq_sel_t enIrqSel);

/* 特殊功能使能和禁止 */
en_result_t LPUart_EnableFunc(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_func_t enFunc);
en_result_t LPUart_DisableFunc(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_func_t enFunc);

/* 状态位获取函数 */
boolean_t LPUart_GetStatus(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_status_t enStatus);
/* 状态位的清除 */
en_result_t LPUart_ClrStatus(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_status_t enStatus);
/* 整个状态寄存器获取 */
uint8_t LPUart_GetIsr(M0P_LPUART_TypeDef *LPUARTx);
/* 整个状态寄存器清除 */
en_result_t LPUart_ClrIsr(M0P_LPUART_TypeDef *LPUARTx);

/* 数据查询方式的发送 */
en_result_t LPUart_SendData(M0P_LPUART_TypeDef *LPUARTx, uint8_t u8Data);
en_result_t LPUart_SendDataTimeOut(M0P_LPUART_TypeDef *LPUARTx, uint8_t u8Data, uint32_t u32TimeOut);
/* 数据中断方式的发送 */
en_result_t LPUart_SendDataIt(M0P_LPUART_TypeDef *LPUARTx, uint8_t u8Data);
/* 多主机模式查询方式的发送 */
en_result_t LPUart_MultiModeSendData(M0P_LPUART_TypeDef *LPUARTx, uint16_t u16Data, uint32_t u32Timeout);
/* 多主机模式中断方式的发送 */
en_result_t LPUart_MultiModeSendDataIt(M0P_LPUART_TypeDef *LPUARTx, uint16_t u16Data);
/* 数据接收 */
uint8_t LPUart_ReceiveData(M0P_LPUART_TypeDef *LPUARTx);

/* 数据寄存器bit8位获取 */
boolean_t LPUart_GetRb8(M0P_LPUART_TypeDef *LPUARTx);

/* LPUARTx通道号，enClk 时钟源选项 */
en_result_t LPUart_SelSclk(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_sclksel_t enSclk);

/* LPUART通道多主机模式配置 */
en_result_t LPUart_SetMultiMode(M0P_LPUART_TypeDef *LPUARTx, stc_lpuart_multimode_t *pstcMultiCfg);

/* LPUART通道多主机模式从机地址配置函数 */
en_result_t LPUart_SetSaddr(M0P_LPUART_TypeDef *LPUARTx, uint8_t u8Addr);

/* LPUART XTL波特率产生寄存器 */
en_result_t LPUart_Xtl_Bsel_Set(M0P_LPUART_TypeDef *LPUARTx, en_lpuart_xtl_bsel_t enBselSet);


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

#endif /* __LPUART_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



