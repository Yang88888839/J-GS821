/**
 *******************************************************************************
 * @file  hsi2c.h
 * @brief This file contains all the functions prototypes of the HSI2C driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2024, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef __HSI2C_H__
#define __HSI2C_H__

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
 * @addtogroup DDL_HSI2C HSI2C模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup HSI2C_Global_Types HSI2C全局类型定义
 * @{
 */

/**
 * @brief HSI2C通信方向
 */
typedef enum
{
    Hsi2cMasterWriteSlaveRead = 0x0u, /*!< 主机写从机读 */
    Hsi2cMasterReadSlaveWrite = 0x1u, /*!< 主机读从机写 */
} en_hsi2c_dir_t;

/**
 * @brief HSI2C主机中断/状态标志
 */
typedef enum
{
    Hsi2cMskMasterStaItTd  = 0x1u,   /*!< 主机发送完成 中断/标志 (注:该位不可通过MSCR清除) */
    Hsi2cMskMasterStaItRd  = 0x2u,   /*!< 主机接收完成 中断/标志 (注:该位不可通过MSCR清除) */
    Hsi2cMskMasterStaItEp  = 0x100u, /*!< 主机结束数据包 中断/标志 */
    Hsi2cMskMasterStaItSd  = 0x200u, /*!< 主机STOP已生成 中断/标志 */
    Hsi2cMskMasterStaItNd  = 0x400u, /*!< 主机检测到不期望NACK 中断/标志 */
    Hsi2cMskMasterStaItAl  = 0x800u, /*!< 主机仲裁丢失 中断/标志 */
    Hsi2cMskMasterStaItFe  = 0x1000u,/*!< 主机缓冲区错误 中断/标志 */
    Hsi2cMskMasterStaItPlt = 0x2000u,/*!< 主机引脚低超时 中断/标志 */
    Hsi2cMskMasterStaItDm  = 0x4000u,/*!< 主机数据匹配 中断/标志 */
    Hsi2cMskMasterStaMbf   = 0x1000000u, /*!< 主机忙标志  (注:该位不可通过MSCR清除)*/
    Hsi2cMskMasterStaBbf   = 0x2000000u, /*!< 总线忙标志  (注:该位不可通过MSCR清除)*/
    Hsi2cMskMasterItAll    = 0x7F03u,
    Hsi2cMskMasterFlagClrAll = 0x7F00u,
} en_hsi2c_mst_flag_it_t;

/**
 * @brief HSI2C从机中断/状态标志
 */
typedef enum
{
    Hsi2cMskSlaveStaItTd  = 0x1u,   /*!< 从机发送完成 中断/标志 (注:该位不可通过SSCR清除) */
    Hsi2cMskSlaveStaItRd  = 0x2u,   /*!< 从机接收完成 中断/标志 (注:该位不可通过SSCR清除) */
    Hsi2cMskSlaveStaItAv  = 0x4u,   /*!< 从机地址有效 中断/标志 (注:该位不可通过SSCR清除) */
    Hsi2cMskSlaveStaItTa  = 0x8u,   /*!< 从机发送ACK 中断/标志 (注:该位不可通过SSCR清除) */
    Hsi2cMskSlaveStaItRs  = 0x100u, /*!< 从机重复START 中断/标志 */
    Hsi2cMskSlaveStaItSd  = 0x200u, /*!< 从机STOP检出 中断/标志 */
    Hsi2cMskSlaveStaItBe  = 0x400u, /*!< 从机位错误 中断/标志 */
    Hsi2cMskSlaveStaItFe  = 0x800u, /*!< 从机缓冲区错误 中断/标志 */
    Hsi2cMskSlaveStaItAm0 = 0x1000u,/*!< 从机地址匹配0 中断/标志 (注:该位不可通过SSCR清除)*/
    Hsi2cMskSlaveStaItAm1 = 0x2000u,/*!< 从机地址匹配1 中断/标志 (注:该位不可通过SSCR清除)*/
    Hsi2cMskSlaveStaItGc  = 0x4000u,/*!< 从机广播标志 中断/标志 (注:该位不可通过SSCR清除)*/
    Hsi2cMskSlaveStaItSar = 0x8000u,/*!< 从机SMBus报警 中断/标志 (注:该位不可通过SSCR清除)*/
    Hsi2cMskSlaveStaSbf   = 0x1000000u, /*!< 从机忙标志 (注:该位不可通过SSCR清除)*/
    Hsi2cMskSlaveStaBbf   = 0x2000000u, /*!< 总线忙标志 (注:该位不可通过SSCR清除)*/
    Hsi2cMskSlaveItAll    = 0xFF0Fu,
    Hsi2cMskSlaveFlagClrAll = 0xF00u,
} en_hsi2c_slv_flag_it_t;

/**
 * @brief HSI2C 主机 匹配模式(MCFGR1.MATCFG)
 */
typedef enum
{
    Hsi2cMasterMatchDisable = 0x0u, /*!< 主机模式匹配禁止 */
    Hsi2cMasterMatchMode2   = 0x2u, /*!< 主机模式匹配模式2: 第一个数据字等于MDMR.MATCH0 或 MDMR.MATCH1 */
    Hsi2cMasterMatchMode3   = 0x3u, /*!< 主机模式匹配模式3: 任何数据字  等于MDMR.MATCH0 或 MDMR.MATCH1 */
    Hsi2cMasterMatchMode4   = 0x4u, /*!< 主机模式匹配模式4: 第一个数据字等于MDMR.MATCH0并且第二个数据字等于MDMR.MATCH1 */
    Hsi2cMasterMatchMode5   = 0x5u, /*!< 主机模式匹配模式5: 任何数据字  等于MDMR.MATCH0并且下一个数据字等于MDMR.MATCH1 */
    Hsi2cMasterMatchMode6   = 0x6u, /*!< 主机模式匹配模式6: (第一个数据字&MDMR.MATCH1)等于(MDMR.MATCH0&MDMR.MATCH1) */
    Hsi2cMasterMatchMode7   = 0x7u, /*!< 主机模式匹配模式6: (任何数据字&MDMR.MATCH1)  等于(MDMR.MATCH0&MDMR.MATCH1) */
} en_hsi2c_mst_match_t;


/**
 * @brief HSI2C 主机 接收数据处理方式(MCFGR1.RDMO)
 */
typedef enum
{
    Hsi2cMasterRxAnyStore       = 0x0u, /*!< 接收的数据存储在接收缓冲器中 */
    Hsi2cMasterRxMatchOnlyStore = 0x1u, /*!< 除非主机数据匹配标志置位(MSR.DMF)后存储数据,否则丢弃接收的数据 */
} en_hsi2c_mst_rxmatch_t;

/**
 * @brief HSI2C 主机从机 DMA使能配置(MDER/SDER)
 */
typedef enum
{
    Hsi2cDmaDisable       = 0x0u, /*!< DMA禁止 */
    Hsi2cTxDmaEnable      = 0x1u, /*!< 发送DMA使能 */
    Hsi2cRxDmaEnable      = 0x2u, /*!< 接收DMA使能 */
    Hsi2cTxRxDmaEnable    = 0x3u, /*!< 收发DMA使能 */
    Hsi2cAddDmaEnable     = 0x4u, /*!< 地址DMA使能，仅限从机 */
    Hsi2cTxRxAddDmaEnable = 0x7u, /*!< 地址和收发DMA使能，仅限从机 */
} en_hsi2c_dma_t;

/**
 * @brief HSI2C 主机 超时功能配置(MCFGR1.TIMECFG)
 */
typedef enum
{
    Hsi2cMasterTimeOutScl    = 0x0u, /*!< 如果SCL低电平持续时间超过配置的超时时间 MSR.PLT置位 */
    Hsi2cMasterTimeOutSclSda = 0x1u, /*!< 如果SCL或SDA低电平持续时间超过配置的超时时间 MSR.PLT置位 */
} en_hsi2c_mst_timeout_t;

/**
 * @brief HSI2C 主机 忽视NACK配置(MCFGR1.IGNACK)
 */
typedef enum
{
    Hsi2cMasterIgnoreNackDisable = 0x0u, /*!< 主机正常接收ACK/NACK */
    Hsi2cMasterIgnoreNackEnable  = 0x1u, /*!< 主机将接收的NACK视为ACK */
} en_hsi2c_mst_ignack_t;

/**
 * @brief HSI2C 主机 自动STOP配置(MCFGR1.AUTOSTOP)
 */
typedef enum
{
    Hsi2cMasterAutoStopDisable = 0x0u, /*!< 自动STOP生成禁用 */
    Hsi2cMasterAutoStopEnable  = 0x1u, /*!< 每当发送缓冲器为空且I2C主机忙时,自动生成STOP状态 */
} en_hsi2c_mst_autostop_t;


/**
 * @brief HSI2C 主机 SDA模拟滤波器配置(MCFGR2.FILTBPSDA)
 */
typedef enum
{
    Hsi2cMasterSdaFiltEnable  = 0x0u, /*!< SDA滤波器使能,SDA信号通过滤波器 */
    Hsi2cMasterSdaFiltDisable = 0x1u, /*!< SDA不通过滤波器 */
} en_hsi2c_mst_sdafilt_t;

/**
 * @brief HSI2C 主机 SCL模拟滤波器配置(MCFGR2.FILTBPSCL)
 */
typedef enum
{
    Hsi2cMasterSclFiltEnable  = 0x0u, /*!< SCL滤波器使能,SCL信号通过滤波器 */
    Hsi2cMasterSclFiltDisable = 0x1u, /*!< SCL不通过滤波器 */
} en_hsi2c_mst_sclfilt_t;

/**
 * @brief HSI2C 主机 调试使能选择(MCR.DBGEN)
 */
typedef enum
{
    Hsi2cMasterDebugDisable = 0x0u, /*!< 在调试模式中禁用主机 */
    Hsi2cMasterDebugEnable  = 0x1u, /*!< 在调试模式中启用主机 */
} en_hsi2c_mst_debug_t;



/**
 * @brief HSI2C 从机 地址模式选择(SCR1.ADDRMODE)
 */
typedef enum
{
    Hsi2cSlaveAddr0Bit7              = 0x00000u, /*!< 地址匹配0(7bit) */
    Hsi2cSlaveAddr0Bit10             = 0x10000u, /*!< 地址匹配0(10bit) */
    Hsi2cSlaveAddr0Bit7OrAddr1Bit7   = 0x20000u, /*!< 地址匹配0(7bit)或地址匹配1(7bit) */
    Hsi2cSlaveAddr0Bit10OrAddr1Bit10 = 0x30000u, /*!< 地址匹配0(10bit)或地址匹配1(10bit) */
    Hsi2cSlaveAddr0Bit7OrAddr1Bit10  = 0x40000u, /*!< 地址匹配0(7bit)或地址匹配1(10bit) */
    Hsi2cSlaveAddr0Bit10OrAddr1Bit7  = 0x50000u, /*!< 地址匹配0(10bit)或地址匹配1(7bit) */
    Hsi2cSlaveAddr0Bit7ToAddr1Bit7   = 0x60000u, /*!< 地址匹配0(7bit)到地址匹配1(7bit) */
    Hsi2cSlaveAddr0Bit10ToAddr1Bit10 = 0x70000u, /*!< 地址匹配0(10bit)到地址匹配1(10bit) */
} en_hsi2c_slv_addr_t;


/**
 * @brief HSI2C 从机 SCR1功能选择(SCR1.xxx)
 */
typedef enum
{
    Hsi2cSlaveMskAddrStallEn   = 0x1u, /*!< Address SCL时钟延展启用/暂停 */
    Hsi2cSlaveMskRxStallEn     = 0x2u, /*!< Rx SCL时钟延展启用/暂停 */
    Hsi2cSlaveMskTxStallEn     = 0x4u, /*!< Tx SCL时钟延展启用/暂停 */
    Hsi2cSlaveMskAckStallEn    = 0x8u, /*!< Ack SCL时钟延展启用/暂停 */
    Hsi2cSlaveMskGeneralCallEn = 0x100u, /*!< 广播地址启用/暂停 */
    Hsi2cSlaveMskSMBusAlertEn  = 0x200u, /*!< SMBus报警启用/暂停 */
    Hsi2cSlaveMskTxFlagCfg     = 0x400u, /*!< Tx发送标志配置:1:每当STDR为空时置位; 0：仅在发送过程中并且STDR为空时置位*/
    Hsi2cSlaveMskRxDataCfg     = 0x800u, /*!< 接收数据配置:1:在SSR.AVF置位时读取SRDR并清除该标志,当SSR.AVF清除时读取SRDR返回接收的数据并清除SSR.RDF
                                                         0: 读取SRDR返回接收的数据并清除SSR.RDF   */
    Hsi2cSlaveMskIgnoreNackEn  = 0x1000u, /*!< 忽视NACK使能/暂停(使能后, 当检测到NACK时从机不结束传输) */
    Hsi2cSlaveMskHSModeEn      = 0x2000u, /*!< 启用/禁用 HS模式主机代码的检测 */
} en_hsi2c_slv_scr1_t;


/**
 * @brief HSI2C 从机 SCR1功能选择(SCR2.FILTEN)
 */
typedef enum
{
    Hsi2cSlaveFiltDisable = 0x0u, /*!< 从机模式的数字滤波器和输出延时计数器禁用*/
    Hsi2cSlaveFiltEnable  = 0x1u, /*!< 从机模式的数字滤波器和输出延时计数器启用 */
} en_hsi2c_slv_filt_t;

/**
 * @brief HSI2C 从机 发送ACK配置(STAR.TXNACK)
 */
typedef enum
{
    Hsi2cSlaveTxAck   = 0x0u, /*!< 为每个接收字写入发送ACK*/
    Hsi2cSlaveTxNack  = 0x1u, /*!< 为每个接收字写入发送NACK */
} en_hsi2c_slv_star_t;

/**
 * @brief HSI2C通信状态
 */
typedef enum
{
    Hsi2cComBusy = 0x1u,
    Hsi2cComIdle = 0x0u,
} en_hsi2c_com_status_t;

/**
 * @brief HSI2C通信结果
 */
typedef enum
{
    Hsi2cComSuccess              = 0x0u, /* The operation is successful */
    Hsi2cComErrorNack            = 0x1u, /* The slave device sent a NACK in response to a byte */
    Hsi2cComErrorBitError        = 0x2u, /* Transferred bit was not seen on the bus */
    Hsi2cComErrorArbitrationLost = 0x3u, /* Arbitration lost error */
    Hsi2cComErrorPinLowTimeout   = 0x4u, /* SCL or SDA were held low longer than the timeout */
    Hsi2cComErrorBufError        = 0x5u, /* Buffer error */
    Hsi2cComErrorTimeout         = 0x6u, /* Timeout polling status flags */
    Hsi2cComErrorInvalidPara     = 0x7u, /* Invalid parameter */
} en_hsi2c_com_error_t;

/**
 * @brief HSI2C状态机定义
 */
typedef enum
{
    Hsi2cStatusStart     = 0x0u, /*!< HSI2C status machine: start/restart */
    Hsi2cStatusSubAddr   = 0x1u, /*!< HSI2C status machine: sub address */
    Hsi2cStatusTransData = 0x2u, /*!< HSI2C status machine: data transfer */
    Hsi2cStatusRxCmd     = 0x3u, /*!< HSI2C status machine: receive command */
    Hsi2cStatusStop      = 0x4u, /*!< HSI2C status machine: stop */
    Hsi2cStatusWaitEnd   = 0x5u, /*!< HSI2C status machine: wait for end */
    Hsi2cStatusRestart   = 0x6u, /*!< HSI2C status machine: reset */
} en_hsi2c_status_machine_t;



/**
 * @brief HSI2C主机配置寄存器MCFGR1结构体定义
 */
typedef struct
{
    /* MCFGR1 */
    en_hsi2c_mst_match_t     enMatchConfig;          /*!< Match configuration */
    en_hsi2c_mst_rxmatch_t   enReceiveDataMatchOnly; /*!< Receive data match only */
    en_hsi2c_mst_timeout_t   enTimeoutConfig;        /*!< Timeout config for pin low */
    en_hsi2c_mst_ignack_t    enIgnoreNack;           /*!< Whether to ignore ACK/NACK */
    en_hsi2c_mst_autostop_t  enAutoStop;             /*!< Whether to enable auto stop */
} stc_hsi2c_master_config1_t;

/**
 * @brief HSI2C主机配置寄存器MCFGR2结构体定义
 */
typedef struct
{
    /* MCFGR2 */
    en_hsi2c_mst_sdafilt_t  enSdaFilterEnable;       /*!< Analog filter SDA bypass */
    en_hsi2c_mst_sclfilt_t  enSclFilterEnable;       /*!< Analog filter SCL bypass */
    uint32_t                u32SdaGlitchFilterConfig; /*!< Configures the I2C master digital glitch filters for SDA input. Set to 0 to disable. 数据范围：0 ~ 0xF */
    uint32_t                u32SclGlitchFilterConfig; /*!< Configures the I2C master digital glitch filters for SCL input. Set to 0 to disable. 数据范围：0 ~ 0xF */
    uint32_t                u32BusIdleTimeout;        /*!< Configures the bus idle timeout period in clock cycles. Set to 0 to disable. 数据范围：0 ~ 0xFFF */
} stc_hsi2c_master_config2_t;

/**
 * @brief HSI2C主机配置寄存器MCFGR3结构体定义
 */
typedef struct
{
    /* MCFGR3 */
    uint32_t u32PinLowTimeout; /*!< Configures the pin low timeout flag in clock cycles. Set to 0 to disable. 数据范围：0 ~ 0xFFF */
} stc_hsi2c_master_config3_t;

/**
 * @brief HSI2C主机配置结构体定义
 */
typedef struct
{
    boolean_t                  bResetBeforeInit; /*!< Whether to reset hsi2c before configure it @ref boolean_t */
    en_hsi2c_mst_debug_t       enEnableDebug;   /*!< Enable transfers to continue when halted in debug mode */
    uint32_t                   u32BaudRateHz;    /*!< Desired baud rate in Hz */
    uint8_t                    u8SlaveAddr;      /*!< The 10-bit or 7-bit slave address */
    en_hsi2c_dir_t             enDir;            /*!< Direction setting @ref en_hsi2c_dir_t */
    en_hsi2c_dma_t             enDma;            /*!< Enable Dma config @ref en_hsi2c_dma_t */
    stc_hsi2c_master_config1_t stcMasterConfig1; /*!< Master MCFGR1 configuration @ref stc_hsi2c_master_config1_t */
    stc_hsi2c_master_config2_t stcMasterConfig2; /*!< Master MCFGR2 configuration @ref stc_hsi2c_master_config2_t */
    stc_hsi2c_master_config3_t stcMasterConfig3; /*!< Master MCFGR3 configuration @ref stc_hsi2c_master_config3_t */
    struct
    {
        union /*!< Sub address. MSB transmit first */
        {
            uint32_t u32SubAddr;
            uint8_t  u8SubAddr[4];
        };
        uint8_t u8SubAddrSize; /*!< Length of sub address. Max size is 4 bytes */
    };
} stc_hsi2c_master_init_t;

/**
 * @brief HSI2C从机控制寄存器SCR1结构体定义
 */
typedef struct
{
    /* SCR1 */
    uint32_t  u32FuncSelect;          /*!< Function select @ref en_hsi2c_slv_scr1_t*/
    en_hsi2c_slv_addr_t  enConfigAddrMatchMode; /*!< Configure address match mode */
} stc_hsi2c_slave_control1_t;

/**
 * @brief HSI2C从机控制寄存器SCR2结构体定义
 */
typedef struct
{
    /* SCR2 */
    en_hsi2c_slv_filt_t enFilterEnable;         /*!< Filter enable */
    uint32_t            u32SdaGlitchFilterWidth; /*!< Width in nanoseconds of the digital filter on the SDA signal. Set to 0 to disable. 数据范围：0 ~ 0xF */
    uint32_t            u32SclGlitchFilterWidth; /*!< Width in nanoseconds of the digital filter on the SCL signal. Set to 0 to disable. 数据范围：0 ~ 0xF */
    uint32_t            u32TimingDataValidDelay; /*!< Width in nanoseconds of the data valid delay. 数据范围：0 ~ 0x3F */
    uint32_t            u32TimingClockHoldTime;  /*!< Width in nanoseconds of the clock hold time.  数据范围：0 ~ 0xF */
} stc_hsi2c_slave_control2_t;

/**
 * @brief HSI2C从机配置结构体定义
 */
typedef struct
{
    boolean_t                  bResetBeforeInit; /*!< Enable reset hsi2c before init it @ref boolean_t */
    stc_hsi2c_slave_control1_t stcSlaveConfig1;  /*!< Slave SCR1 configuration @ref stc_hsi2c_slave_control1_t */
    stc_hsi2c_slave_control2_t stcSlaveConfig2;  /*!< Slave SCR2 configuration @ref stc_hsi2c_slave_control2_t */
    uint32_t                   u32SlaveAddr0;    /*!< The 10-bit or 7-bit slave address0 */
    uint32_t                   u32SlaveAddr1;    /*!< The 10-bit or 7-bit slave address1 */
    en_hsi2c_dir_t             enDir;            /*!< Direction setting @ref en_hsi2c_dir_t */
    en_hsi2c_dma_t             enDma;            /*!< Enable Dma config @ref en_hsi2c_dma_t */
    uint8_t                    u8SubAddrSize;    /*!< Length of sub address to receive in bytes. Maximum size is 4 bytes */
} stc_hsi2c_slave_init_t;



/**
 * @brief HSI2C通信配置结构体定义
 */
typedef struct
{
    uint32_t                   u32Len;         /*!< HSI2C communication data length */
    uint8_t                   *pu8Buf;         /*!< HSI2C communication data buffer pointer */
    __IO uint32_t              u32DataIndex;   /*!< HSI2C communication data transfer index */
    __IO en_hsi2c_com_status_t enComStatus;    /*!< HSI2C communication status */
    uint32_t                   u32RxSize;      /*!< Master: HSI2C receive data length */
                                               /*!< Slave:  HSI2C sub address length */
    struct
    {
        union /*!< Sub address. Receive MSB first */
        {
            uint32_t u32SubAddr;
            uint8_t  u8SubAddr[4];
        };
    };
} stc_hsi2c_com_t;


/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup HSI2C_Global_Macros HSI2C全局宏定义
 * @{
 */

/**
 * @defgroup HSI2C_Master_Cmd HSI2C主机命令选择
 * @{
 */
#define HSI2C_CMD_TX_DATA               (0x0u)   /*!< Transmit DATA[7:0] */
#define HSI2C_CMD_RX_DATA               (0x100u) /*!< Receive (DATA[7:0] + 1) bytes */
#define HSI2C_CMD_STOP                  (0x200u) /*!< Generate STOP condition */
#define HSI2C_CMD_RX_DISCARD            (0x300u) /*!< Receive and discard (DATA[7:0] + 1) bytes */
#define HSI2C_CMD_START_TX_DATA         (0x400u) /*!< Generate (repeated) START and transmit address in DATA[7:0] */
#define HSI2C_CMD_START_TX_DATA_NACK    (0x500u) /*!< Generate (repeated) START and transmit address in DATA[7:0]. This transfer expects a NACK to be returned */
#define HSI2C_CMD_HS_START_TX_DATA      (0x600u) /*!< (HS Moede) Generate (repeated) START and transmit address in DATA[7:0] */
#define HSI2C_CMD_HS_START_TX_DATA_NACK (0x700u) /*!< (HS Moede) Generate (repeated) START and transmit address in DATA[7:0]. This transfer expects a NACK to be returned */
/**
 * @}
 */
 

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/**
 * @addtogroup HSI2C_Global_Variables HSI2C全局变量定义
 * @{
 */
extern stc_hsi2c_com_t           stcHsi2cCom;
extern en_hsi2c_status_machine_t enMasterStatusMachine;
extern stc_hsi2c_master_init_t   stcHsi2cMasterInit;
extern stc_hsi2c_slave_init_t    stcHsi2cSlaveInit;
/**
 * @}
 */
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup HSI2C_Global_Functions HSI2C全局函数定义
 * @{
 */
en_result_t HSI2C_MasterInit(stc_hsi2c_master_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz);              /* 主机初始化 */
en_result_t HSI2C_MasterBaudRateSet(const stc_hsi2c_master_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz); /* 主机波特率设置 */
en_result_t HSI2C_MasterTransferInt(uint8_t *pu8Data, uint32_t u32Size);                                   /* 主机中断传输设置 */
en_result_t HSI2C_MasterTransferPoll(uint8_t *pu8Data, uint32_t u32Size, uint32_t u32Timeout);             /* 主机轮询传输 */

void HSI2C_SlaveInit(stc_hsi2c_slave_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz);   /* 从机初始化 */
en_result_t HSI2C_SlaveTransferInt(uint8_t *pu8Data, uint32_t u32Size);                       /* 从机中断传输设置 */
en_result_t HSI2C_SlaveTransferPoll(uint8_t *pu8Data, uint32_t u32Size, uint32_t u32Timeout); /* 从机轮询传输 */

void HSI2C_MasterMcfgr1Config(stc_hsi2c_master_config1_t *pstcHsi2cConfig); /* 主机配置寄存器1设置(MCFGR1寄存器设置) */
void HSI2C_MasterMcfgr2Config(stc_hsi2c_master_config2_t *pstcHsi2cConfig); /* 主机配置寄存器2设置(MCFGR2寄存器设置) */
void HSI2C_MasterMcfgr3Config(stc_hsi2c_master_config3_t *pstcHsi2cConfig); /* 主机配置寄存器3设置(MCFGR3寄存器设置) */
void HSI2C_MasterDataMatchConfig(uint32_t u32MatchValue0, uint32_t u32MatchValue1); /* 主机数据配置设置(MDMR寄存器设置) */

void HSI2C_SlaveScr1Config(stc_hsi2c_slave_control1_t *pstcHsi2cConfig); /* 从机SCR1寄存器设置 */
void HSI2C_SlaveScr2Config(stc_hsi2c_slave_control2_t *pstcHsi2cConfig); /* 从机SCR2寄存器设置 */

void HSI2C_MasterReset(void); /* 主机软件复位 */
void HSI2C_SlaveReset(void);  /* 从机软件复位 */

void HSI2C_MasterEnable(void);  /* 主机使能 */
void HSI2C_SlaveEnable(void);   /* 从机使能 */
void HSI2C_MasterDisable(void); /* 主机禁止 */
void HSI2C_SlaveDisable(void);  /* 从机禁止 */

boolean_t HSI2C_MasterFlagGet(en_hsi2c_mst_flag_it_t enHsi2cFlag); /* 主机标志位获取 */
void HSI2C_SlaveFlagClear(en_hsi2c_slv_flag_it_t enHsi2cFlag);  /* 从机标志位清除 */
boolean_t HSI2C_SlaveFlagGet(en_hsi2c_slv_flag_it_t enHsi2cFlag);  /* 从机标志位获取 */
void HSI2C_MasterFlagClear(en_hsi2c_mst_flag_it_t enHsi2cFlag); /* 主机标志位清除 */

void     HSI2C_MasterIntEnable(en_hsi2c_mst_flag_it_t enHsi2cIrq);  /* 主机中断允许 */
void     HSI2C_MasterIntDisable(en_hsi2c_mst_flag_it_t enHsi2cIrq); /* 主机中断禁止 */
void     HSI2C_SlaveIntEnable(en_hsi2c_slv_flag_it_t enHsi2cIrq);   /* 从机中断使能 */
void     HSI2C_SlaveIntDisable(en_hsi2c_slv_flag_it_t enHsi2cIrq);  /* 从机中断禁止 */
uint32_t HSI2C_MasterIntGet(void);                           /* 主机中断使能获取 */
uint32_t HSI2C_SlaveIntGet(void);                            /* 从机中断使能获取 */

void                 HSI2C_MasterStart(uint8_t u8SlaveAddr, en_hsi2c_dir_t enTransDir); /* 主机Start命令 */
void                 HSI2C_MasterStop(void);                                                  /* 主机Stop命令 */
void                 HSI2C_MasterWriteData(uint8_t u8Data);                             /* 主机写数据 */
void                 HSI2C_MasterReceiveCmd(uint8_t u8Len);                             /* 主机读数据命令 */
en_result_t          HSI2C_MasterReadData(uint8_t *pu8Data);                            /* 主机读数据 */
en_hsi2c_com_error_t HSI2C_MasterErrorGet(uint32_t u32MasterFlag);                                             /* 主机传输Error类型输出 */
void                 HSI2C_MasterTransAbort(void);                                            /* 主机传输终止 */

void                 HSI2C_SlaveWriteAddr(uint16_t u16Addr0, uint16_t u16Addr1); /* 从机写地址 */
void                 HSI2C_SlaveWriteData(uint8_t u8Data);                       /* 从机写数据 */
en_result_t          HSI2C_SlaveReadData(uint8_t *pu8Data);                      /* 从机读数据 */
en_result_t          HSI2C_SlaveReadAddr(uint16_t *pu16Data);                    /* 从机读接收的地址 */
en_hsi2c_com_error_t HSI2C_SlaveErrorGet(uint32_t u32SlaveFlag);                                        /* 从机传输Error类型输出 */
void                 HSI2C_SlaveTransAbort(void);                                      /* 从机传输终止 */
void                 HSI2C_SlaveTransNack(en_hsi2c_slv_star_t enAckNack);                  /* 从机发送ACK/NACK */

void HSI2C_MasterStatusMachineStart(void);                /* 主机状态机控制（Start） */
void HSI2C_MasterStatusMachineSubAddr(void);              /* 主机状态机控制（Sub address） */
void HSI2C_MasterStatusMachineRestart(void);              /* 主机状态机控制（Restart） */
void HSI2C_MasterStatusMachineStop(void);                 /* 主机状态机控制（Stop） */
void HSI2C_MasterStatusMachineTrans(void);                /* 主机状态机控制（Data transfer） */
void HSI2C_MasterStatusMachineRxCmd(uint32_t *pu32RxLen); /* 主机状态机控制（Receive command） */

uint8_t HSI2C_10BitAddrMdHighBitsGet(uint16_t u16AddrData); /* 10位地址模式获取高字节 */
uint8_t HSI2C_10BitAddrMdLowBitsGet(uint16_t u16AddrData);  /* 10位地址模式获取低字节 */

void HSI2C_MasterStcInit(stc_hsi2c_master_init_t *pstcInit); /* 主机结构体初始化 */
void HSI2C_SlaveStcInit(stc_hsi2c_slave_init_t *pstcInit);   /* 从机结构体初始化 */
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

#endif /* __HSI2C_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
