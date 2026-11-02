/**
 ******************************************************************************
 * @file   lvd.h
 *
 * @brief This file contains all the functions prototypes of the LVD driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-04-23       MDAS            First version
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

#ifndef __LVD_H__
#define __LVD_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_LVD LVD模块驱动库
 * @{
 */

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 * @defgroup LVD_Global_Types LVD全局类型定义
 * @{
 */

/**
 * @brief  LVD监测电压源选择
 */
typedef enum
{
    LvdInputSrcMskVCC  = 0x0u,    /*!< Vcc */
    LvdInputSrcMskPC13 = 0x4u,    /*!< PC13 */
    LvdInputSrcMskPB08 = 0x8u,    /*!< PB08 */
    LvdInputSrcMskPB07 = 0xCu     /*!< PB07 */
} en_lvd_input_src_t;

/**
 * @brief  LVD阈值电压选择
 */
typedef enum
{
    LvdMskTH1_8V = 0x0u,     /*!< 1.8V */
    LvdMskTH2_0V = 0x10u,    /*!< 2.0V */
    LvdMskTH2_2V = 0x20u,    /*!< 2.2V */
    LvdMskTH2_4V = 0x30u,    /*!< 2.4V */
    LvdMskTH2_6V = 0x40u,    /*!< 2.6V */
    LvdMskTH2_8V = 0x50u,    /*!< 2.8V */
    LvdMskTH3_0V = 0x60u,    /*!< 3.0V */
    LvdMskTH3_2V = 0x70u,    /*!< 3.2V */
    LvdMskTH3_4V = 0x80u,    /*!< 3.4V */
    LvdMskTH3_6V = 0x90u,    /*!< 3.6V */
    LvdMskTH3_8V = 0xA0u,    /*!< 3.8V */
    LvdMskTH4_0V = 0xB0u,    /*!< 4.0V */
    LvdMskTH4_2V = 0xC0u,    /*!< 4.2V */
    LvdMskTH4_4V = 0xD0u,    /*!< 4.4V */
    LvdMskTH4_6V = 0xE0u,    /*!< 4.6V */
    LvdMskTH4_8V = 0xF0u     /*!< 4.8V */
} en_lvd_threshold_t;

/**
 * @brief  LVD输出滤波时间
 */
typedef enum
{
    LvdFilterMskNone      = 0x0u,      /*!< 无滤波 */
    LvdFilterMsk2Cycle    = 0x100u,    /*!< 滤波时间 2 周期 */
    LvdFilterMsk4Cycle    = 0x200u,    /*!< 滤波时间 4 周期 */
    LvdFilterMsk8Cycle    = 0x300u,    /*!< 滤波时间 8 周期 */
    LvdFilterMsk16Cycle   = 0x400u,    /*!< 滤波时间 16 周期 */
    LvdFilterMsk32Cycle   = 0x500u,    /*!< 滤波时间 32 周期 */
    LvdFilterMsk64Cycle   = 0x600u,    /*!< 滤波时间 64 周期 */
    LvdFilterMsk128Cycle  = 0x700u,    /*!< 滤波时间 128 周期 */
    LvdFilterMsk256Cycle  = 0x800u,    /*!< 滤波时间 256 周期 */
    LvdFilterMsk512Cycle  = 0x900u,    /*!< 滤波时间 512 周期 */
    LvdFilterMsk1024Cycle = 0xA00u,    /*!< 滤波时间 1024 周期 */
    LvdFilterMsk2048Cycle = 0xB00u,    /*!< 滤波时间 2048 周期 */
    LvdFilterMsk4096Cycle = 0xC00u     /*!< 滤波时间 4096 周期 */
} en_lvd_filter_time_t;

/**
 * @brief  LVD中断触发方式
 */
typedef enum
{
    LvdIrqMskRiseFall = 0x3000u,    /*!< 上升/下降沿触发 */
    LvdIrqMskHigh     = 0x4000u,    /*!< 高电平触发 */
    LvdIrqMskRise     = 0x2000u,    /*!< 上升沿触发 */
    LvdIrqMskFall     = 0x1000u,    /*!< 下降沿触发 */
} en_lvd_irq_type_t;

/**
 * @brief  LVD触发动作选择
 */
typedef enum
{
    LvdActMskReset = 0x2u,   /*!< 系统复位 */
    LvdActMskInt   = 0u,     /*!< NVIC中断 */
} en_lvd_act_t;

/**
 * @brief  LVD滤波模式选择
 */
typedef enum
{
    LvdFltModeMskNormal    = 0u,        /*!< 普通滤波模式 */
    LvdFltModeMskFltPeak   = 0x20000u,  /*!< 滤峰模式 */
    LvdFltModeMskFltValley = 0x40000u,  /*!< 滤谷模式 */
    LvdFltModeMskFltGlitch = 0x60000u,  /*!< 滤刺模式 */
} en_lvd_flt_mode_t;

/**
 * @brief  LVD配置
 */
typedef struct
{
    en_lvd_act_t            enAct;          /*!< LVD触发动作 */
    en_lvd_input_src_t      enInputSrc;     /*!< LVD输入电压源 */
    en_lvd_threshold_t      enThreshold;    /*!< LVD监测电压 */
    en_lvd_flt_mode_t       enFltMode;      /*!< 滤波模式 */
    en_lvd_filter_time_t    enFilterTime;   /*!< 输出滤波时间 */
    en_lvd_irq_type_t       enIrqType;      /*!< 中断触发方式 */
} stc_lvd_cfg_t;

/**
 * @}
 */
/******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup LVD_Global_Functions LVD全局函数定义
 * @{
 */
void Lvd_EnableIrq(void);
void Lvd_DisableIrq(void);

void Lvd_Init(stc_lvd_cfg_t *pstcCfg);

void Lvd_Enable(void);
void Lvd_Disable(void);

boolean_t Lvd_GetIrqStat(void);
void Lvd_ClearIrq(void);

boolean_t Lvd_GetFilterResult(void);
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

#endif /* __LVD_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
