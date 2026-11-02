/**
 *******************************************************************************
 * @file  dmac.c
 * @brief This file provides - functions to manage the DMAC.
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

/*******************************************************************************
* Include files
******************************************************************************/
#include "dmac.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_DMAC DMAC模块驱动库
 * @brief DMAC Driver Library DMAC模块驱动库
 * @{
 */

/*******************************************************************************
* Local type definitions ('typedef')
******************************************************************************/

/*******************************************************************************
* Local pre-processor symbols/macros ('#define')
******************************************************************************/
/**
 * @defgroup DMAC_Local_Macros DMA局部宏定义
 * @{
 */


/** @defgroup DMA_CONFB_WIDTH Bits definition for DMA_CONFBx.WIDTH(x=0~1)
  * @{
  */
#define DMA_TRANSFER_WIDTH_Pos      (26U)                                 /*!< DMAC_CONFBx: WIDTH Position */
#define DMA_TRANSFER_WIDTH_Msk      (0x03U << DMA_TRANSFER_WIDTH_Pos)     /*!< DMAC_CONFBx: WIDTH Mask 0x0C000000 */
/**
  * @}
  */

/** @defgroup DMA_CONFB_ERRIE Bits definition for DMA_CONFBx.ERRIE(x=0~1)
  * @{
  */
#define DMA_ERR_IE_Pos              (20U)                                 /*!< DMAC_CONFBx: ERR_IE Position */
#define DMA_ERR_IE_Msk              (0x01U << DMA_ERR_IE_Pos)             /*!< DMAC_CONFBx: ERR_IE Mask 0x00100000 */
/**
  * @}
  */

/** @defgroup DMA_CONFB_FISIE Bits definition for DMA_CONFBx.FISIE(x=0~1)
  * @{
  */
#define DMA_FIS_IE_Pos              (19U)                                 /*!< DMAC_CONFBx: FIS_IE Position */
#define DMA_FIS_IE_Msk              (0x01U << DMA_FIS_IE_Pos)             /*!< DMAC_CONFBx: FIS_IE Mask 0x00080000 */
/**
  * @}
  */

/** @defgroup DMA_CONFB_STAT Bits definition for DMA_CONFBx.STAT(x=0~1)
  * @{
  */
#define DMA_STAT_Pos                (16U)                                 /*!< DMAC_CONFBx: STAT Position */
#define DMA_STAT_Msk                (0x07U << DMA_STAT_Pos)               /*!< DMAC_CONFBx: STAT Mask 0x00070000 */
/**
  * @}
  */

/** @defgroup DMA_CONFB_MSK Bits definition for DMA_CONFBx.MSK(x=0~1)
  * @{
  */
#define DMA_TRANSFER_RELOAD_Pos     (0U)                                   /*!< DMAC_CONFBx: MSK Position */
#define DMA_TRANSFER_RELOAD_Msk     (0x01U << DMA_TRANSFER_RELOAD_Pos)     /*!< DMAC_CONFBx: MSK Mask 0x00000001 */
/**
  * @}
  */

/** @defgroup DMA_CONFA_ENS Bits definition for DMA_CONFAx.ENS(x=0~1)
  * @{
  */
#define DMA_CH_ENABLE_Pos           (31U)                                  /*!< DMAC_CONFAx: ENS Position */
#define DMA_CH_ENABLE_Msk           (0x01U << DMA_CH_ENABLE_Pos)           /*!< DMAC_CONFAx: ENS Mask 0x80000000 */
/**
  * @}
  */

/** @defgroup DMA_CONFA_PAS Bits definition for DMA_CONFAx.PAS(x=0~1)
  * @{
  */
#define DMA_CH_PAUSE_Pos            (30U)                                  /*!< DMAC_CONFAx: PAS Position */
#define DMA_CH_PAUSE_Msk            (0x01U << DMA_CH_PAUSE_Pos)            /*!< DMAC_CONFAx: PAS Mask 0x40000000 */
/**
  * @}
  */

/** @defgroup DMA_CONFA_ST Bits definition for DMA_CONFAx.ST(x=0~1)
  * @{
  */
#define DMA_SOFTWARE_START_Pos      (29U)                                  /*!< DMAC_CONFAx: SOFTWARE START(ST) Position */
#define DMA_SOFTWARE_START_Msk      (0x01U << DMA_SOFTWARE_START_Pos)      /*!< DMAC_CONFAx: SOFTWARE START(ST) Mask 0x20000000 */
/**
  * @}
  */

/** @defgroup DMA_CONFA_TRISEL Bits definition for DMA_CONFAx.TRISEL(x=0~1)
  * @{
  */
#define DMA_TRI_SEL_Pos             (22U)                                  /*!< DMAC_CONFAx: TRISEL Position */
#define DMA_TRI_SEL_Msk             (0x7FU << DMA_TRI_SEL_Pos)             /*!< DMAC_CONFAx: TRISEL Mask 0x1FC00000 */
/**
  * @}
  */

/** @defgroup DMA_CONFA_BC Bits definition for DMA_CONFAx.BC(x=0~1)
  * @{
  */
#define DMA_BC_SEL_Pos              (16U)                                  /*!< DMAC_CONFAx: BC Position */
#define DMA_BC_SEL_Msk              (0x0FU << DMA_BC_SEL_Pos)              /*!< DMAC_CONFAx: BC Mask 0x000F0000 */
/**
  * @}
  */

/** @defgroup DMA_CONFA_TC Bits definition for DMA_CONFAx.TC(x=0~1)
  * @{
  */
#define DMA_TC_SEL_Pos              (0U)                                   /*!< DMAC_CONFAx: TC Position */
#define DMA_TC_SEL_Msk              (0xFFFFU << DMA_TC_SEL_Pos)            /*!< DMAC_CONFAx: TC Mask 0x0000FFFF */
/**
  * @}
  */

/** @defgroup DMA_CONF_EN Bits definition for DMA_CONF.EN
  * @{
  */
#define DMA_ENABLE_Pos              (31U)                                  /*!< DMAC_CONF: ENABLE Position */
#define DMA_ENABLE_Msk              (0x01U << DMA_ENABLE_Pos)              /*!< DMAC_CONF: ENABLE Mask 0x80000000 */
/**
  * @}
  */

/** @defgroup DMA_CONF_PRIO Bits definition for DMA_CONF.PRIO
  * @{
  */
#define DMA_PRIORITY_Pos            (28U)                                  /*!< DMAC_CONF: PRIORITY Position */
#define DMA_PRIORITY_Msk            (0x01U << DMA_PRIORITY_Pos)            /*!< DMAC_CONF: PRIORITY Mask 0x10000000 */
/**
  * @}
  */

/**
 * @brief DMAC通道参数有效性检查
 */
#define IS_VALID_CH(x)              ((DmaCh0 == (x)) || (DmaCh1 == (x)))

/**
 * @brief DMAC 传输数据宽度，参数有效性检查
 */
#define IS_VALID_TRN_WIDTH(x)               \
(   (DmaMsk8Bit == (x))                  || \
    (DmaMsk16Bit == (x))                 || \
    (DmaMsk32Bit == (x)))

/**
 * @brief DMAC源地址控制模式，参数有效性检查
 */
#define IS_VALID_SRC_ADDR_MODE(x)   ((DmaMskSrcAddrFix == (x))||(DmaMskSrcAddrInc == (x)))

/**
 * @brief DMAC 目的地址控制模式，参数有效性检查
 */
#define IS_VALID_DST_ADDR_MODE(x)   ((DmaMskDstAddrFix == (x))||(DmaMskDstAddrInc == (x)))

/**
 * @brief DMAC 优先级, 参数有效性检查
 */
#define IS_VALID_PRIO_MODE(x)       ((DmaMskPriorityFix == (x))||(DmaMskPriorityLoop == (x)))

/**
 * @brief DMAC 传输模式，参数有效性检查
 */
#define IS_VALID_TRANSFER_MODE(x)   ((DmaMskOneTransfer == (x))||(DmaMskContinuousTransfer == (x)))

/**
 * @brief 块传输大小，参数有效性检查
 */
#define IS_VALID_BLKSIZE(x)         ((!((x) & ~(DMA_BC_SEL_Msk >> DMA_BC_SEL_Pos)))&&((x)>0))

/**
 * @brief 块传输次数，参数有效性检查
 */
#define IS_VALID_TRNCNT(x)          (!((x) & ~(DMA_TC_SEL_Msk >> DMA_TC_SEL_Pos)))

/**
 * @}
 */
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
 * @defgroup DMAC_Global_Functions DMAC全局函数定义
 * @{
 */

/**
 * @brief 初始化DMAC通道
 * @param  [in] enCh         指定通道 @ref en_dma_channel_t
 * @param  [in] pstcCfg      DMAC通道初始化配置结构体指针 @ref stc_dma_cfg_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - ErrorInvalidParameter       pstcCfg是空指针
 */
en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_cfg_t *pstcCfg)
{
    ASSERT(IS_VALID_CH(enCh));
    ASSERT(NULL != pstcCfg);
    ASSERT(IS_VALID_BLKSIZE(pstcCfg->u16BlockSize));
    ASSERT(IS_VALID_TRNCNT(pstcCfg->u16TransferCnt));
    ASSERT(IS_VALID_TRN_WIDTH(pstcCfg->enTransferWidth));
    ASSERT(IS_VALID_SRC_ADDR_MODE(pstcCfg->enSrcAddrMode));
    ASSERT(IS_VALID_DST_ADDR_MODE(pstcCfg->enDstAddrMode));
    ASSERT(IS_VALID_PRIO_MODE(pstcCfg->enPriority));
    ASSERT(IS_VALID_TRANSFER_MODE(pstcCfg->enTransferMode));

    /* 检查通道值有效性和pstcCfg是否空指针 */
    if (NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }

    *(&M0P_DMAC->CONFB0 + enCh) = 0;
    *(&M0P_DMAC->CONFB0 + enCh) = (uint32_t)pstcCfg->enMode             |
                                  (uint32_t)pstcCfg->enTransferWidth    |
                                  (uint32_t)pstcCfg->enSrcAddrMode      |
                                  (uint32_t)pstcCfg->enDstAddrMode      |
                                  (uint32_t)pstcCfg->enSrcAddrReloadCtl |
                                  (uint32_t)pstcCfg->enDestAddrReloadCtl |
                                  (uint32_t)pstcCfg->enSrcBcTcReloadCtl |
                                  (uint32_t)pstcCfg->enTransferMode;

    /*首先把TRI_SEL[6:0]     BC[3:0] TC[15:0]这些位清零，然后再赋值*/
    *(&M0P_DMAC->CONFA0 + enCh) &= ((uint32_t)~(DMA_TRI_SEL_Msk | DMA_BC_SEL_Msk | DMA_TC_SEL_Msk));
    *(&M0P_DMAC->CONFA0 + enCh)    |= (uint32_t)(pstcCfg->u16TransferCnt - 1)    |
                                      ((uint32_t)(pstcCfg->u16BlockSize - 1) << 16) |
                                      (uint32_t)(pstcCfg->enRequestNum << 22);

    M0P_DMAC->CONF |= (uint32_t)(pstcCfg->enPriority);

    *(&M0P_DMAC->SRCADR0 + enCh) = (uint32_t)(pstcCfg->u32SrcAddress);
    *(&M0P_DMAC->DSTADR0 + enCh) = (uint32_t)(pstcCfg->u32DstAddress);

    return Ok;
}
/**
 * @brief  DMA模块使能函数，使能所有通道的操作，每个通道按照各自设置工作.
 * @retval None
 * @note   None
 */
void Dma_Enable(void)
{
    M0P_DMAC->CONF |= DMA_ENABLE_Msk;
}

/**
 * @brief  DMA模块功能禁止函数，所有通道禁止工作.
 * @retval None
 * @note   None
 */
void Dma_Disable(void)
{
    M0P_DMAC->CONF &= (~DMA_ENABLE_Msk);
}
/**
 * @brief  触发指定DMA通道软件传输功能
 * @param  [in] enCh     指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_SwStart(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFA0 + enCh) |= DMA_SOFTWARE_START_Msk;
}

/**
 * @brief  停止指定DMA通道软件传输功能
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_SwStop(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFA0 + enCh) &= (~DMA_SOFTWARE_START_Msk);
}
/**
 * @brief  使能指定dma通道的（传输完成）中断
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_EnableChannelIrq(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFB0 + enCh) |= DMA_FIS_IE_Msk;
}

/**
 * @brief  禁用指定dma通道的（传输完成）中断
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_DisableChannelIrq(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFB0 + enCh) &= (~DMA_FIS_IE_Msk);
}
/**
 * @brief  使能指定dma通道的（传输错误）中断
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_EnableChannelErrIrq(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFB0 + enCh) |= DMA_ERR_IE_Msk;
}

/**
 * @brief  禁用指定dma通道的（传输错误）中断
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_DisableChannelErrIrq(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFB0 + enCh) &= (~DMA_ERR_IE_Msk);
}

/**
 * @brief  使能指定dma通道
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_EnableChannel(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFA0 + enCh) |= DMA_CH_ENABLE_Msk;
}

/**
 * @brief  禁用指定dma通道
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_DisableChannel(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFA0 + enCh) &= (~DMA_CH_ENABLE_Msk);
}

/**
 * @brief  设定指定通道的块(Block)尺寸
 * @param  [in] enCh        指定dma通道 @ref en_dma_channel_t
 * @param  [in] u16BlkSize  块(Block)尺寸
 * @retval None
 * @note   None
 */
void Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize)
{
    volatile uint32_t *pReg = (&M0P_DMAC->CONFA0 + enCh);

    *pReg = ((*pReg) & ((uint32_t)~DMA_BC_SEL_Msk)) | ((((uint32_t)u16BlkSize - 1) & 0x0f) << DMA_BC_SEL_Pos);
}

/**
 * @brief  设定指定通道块(Block)传输次数
 * @param  [in] enCh       指定dma通道 @ref en_dma_channel_t
 * @param  [in] u16TrnCnt  块(Block)传输次数
 * @retval None
 * @note   None
 */
void Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt)
{
    volatile uint32_t *pReg = (&M0P_DMAC->CONFA0 + enCh);

    *pReg = ((*pReg) & ((uint32_t)~DMA_TC_SEL_Msk)) | (((uint32_t)(u16TrnCnt - 1) << DMA_TC_SEL_Pos));
}

/**
 * @brief  允许指定通道可连续传输，即DMAC在传输完成时不清除CONFA:ENS位
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_EnableContinusTranfer(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFB0 + enCh) |= DMA_TRANSFER_RELOAD_Msk;
}

/**
 * @brief  禁止指定通道连续传输，即DMAC在传输完成时清除.
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_DisableContinusTranfer(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFB0 + enCh) &= (~DMA_TRANSFER_RELOAD_Msk);
}
/**
 * @brief  暂停所有dma通道
 * @retval None.
 * @note   None
 */
void Dma_HaltTranfer(void)
{
    M0P_DMAC->CONF_f.HALT = 0x1;
}
/**
 * @brief  恢复（之前暂停的）所有dma通道
 * @retval None
 * @note   None
 */
void Dma_RecoverTranfer(void)
{
    M0P_DMAC->CONF_f.HALT = 0x0;
}
/**
 * @brief  暂停指定dma通道
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval void
 * @note   None
 */
void Dma_PauseChannelTranfer(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFA0 + enCh) |= DMA_CH_PAUSE_Msk;
}
/**
 * @brief  恢复（之前暂定的）指定dma通道
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_RecoverChannelTranfer(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFA0 + enCh) &= (~DMA_CH_PAUSE_Msk);
}
/**
 * @brief  设定指定通道传输数据宽度
 * @param  [in] enCh     指定dma通道 @ref en_dma_channel_t
 * @param  [in] enWidth  指定数据宽度.
 * @retval None
 * @note   None
 */
void Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth)
{
    volatile uint32_t *pReg = (&M0P_DMAC->CONFB0 + enCh);

    *pReg = ((*pReg) & ((uint32_t)~DMA_TRANSFER_WIDTH_Msk)) | ((uint32_t)enWidth);
}
/**
 * @brief  设定dma通道优先级
 * @param  [in] enPrio    通道优先级设定参数
 * @retval None
 * @note   None
 */
void Dma_SetChPriority(en_dma_priority_t enPrio)
{
    M0P_DMAC->CONF = ((M0P_DMAC->CONF) & ((uint32_t)~DMA_PRIORITY_Msk)) | ((uint32_t)enPrio);
}
/**
 * @brief  获取指定DMA通道的状态.
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval en_dma_stat_t  DMA传输当前状态
 * @note   None
 */
en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh)
{
    return (en_dma_stat_t)((*(&M0P_DMAC->CONFB0 + enCh) & (DMA_STAT_Msk)) >> DMA_STAT_Pos);
}
/**
 * @brief  清除指定DMA通道的状态值.
 * @param  [in] enCh    指定dma通道 @ref en_dma_channel_t
 * @retval None
 * @note   None
 */
void Dma_ClrStat(en_dma_channel_t enCh)
{
    *(&M0P_DMAC->CONFB0 + enCh) &= (~DMA_STAT_Msk);
}


/**
 * @brief  设定指定通道源地址
 * @param  [in] enCh        指定dma通道 @ref en_dma_channel_t
 * @param  [in] u32Address  传输源地址.
 * @retval None
 * @note   None
 */
void Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
    *(&M0P_DMAC->SRCADR0 + enCh) = u32Address;
}

/**
 * @brief  设定指定通道目标地址.
 * @param  [in] enCh        指定dma通道 @ref en_dma_channel_t
 * @param  [in] u32Address  传输目标地址
 * @retval None
 * @note   None
 */
void Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
    *(&M0P_DMAC->DSTADR0 + enCh) = u32Address;
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

/*******************************************************************************
* EOF (not truncated)
******************************************************************************/
