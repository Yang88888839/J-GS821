/**
 *******************************************************************************
 * @file  ctrim.h
 * @brief This file contains all the functions prototypes of the CTRIM driver
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
 *******************************************************************************
 */
#ifndef __CTRIM_H__
#define __CTRIM_H__

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
 * @addtogroup DDL_CTRIM CTRIM模块驱动库
 * @{
 */
 
/*******************************************************************************
 * Global definitions
 ******************************************************************************/
/**
* @defgroup CTRIM_Global_Types CTRIM全局类型定义
* @{
*/


/**
 * @brief CTRIM 工作模式类型定义
 * @note
 */
typedef enum
{
    CtrimModeRch     = 0u,    /*!< RCH校准 */
    CtrimModeRcl     = 1u,    /*!< RCL校准 */
    CtrimModeTimer   = 3u,    /*!< 定时器模式 */
} en_ctrim_md_t;

/**
 * @brief CTRIM RCH/RCL自动Trim配置类型定义
 * @note
 */
typedef enum
{
    CtrimAutoTrimDisable    = 0u,    /*!< RCH/RCL自动校准禁止 */  
    CtrimAutoTrimEnable     = 1u,    /*!< RCH/RCL自动校准使能 */
} en_ctrim_auto_t;

/**
 * @brief CTRIM 时钟来源配置类型定义
 * @note
 */
typedef enum
{
    CtrimSrcEtr    = 0u,    /*!< 时钟来源 ETR */  
    CtrimSrcXth    = 1u,    /*!< 时钟来源 XTH*/
    CtrimSrcXtl    = 2u,    /*!< 时钟来源 XTL*/
    CtrimSrcPclk   = 3u,    /*!< 时钟来源 PCLK*/
    CtrimSrcRcl    = 4u,    /*!< 时钟来源 RCL*/
    CtrimSrcRCH    = 5u,    /*!< 时钟来源 RCH*/
} en_ctrim_src_t;

/**
 * @brief CTRIM 参考时钟预分频类型定义
 * @note
 */
typedef enum
{
    CtrimRefPrsDiv2     = 1u,  /*!< 2 分频 */  
    CtrimRefPrsDiv4     = 2u,  /*!< 4 分频 */
    CtrimRefPrsDiv8     = 3u,  /*!< 8 分频 */
    CtrimRefPrsDiv16    = 4u,  /*!< 16 分频 */
    CtrimRefPrsDiv32    = 5u,  /*!< 32 分频 */
    CtrimRefPrsDiv64    = 6u,  /*!< 64 分频 */
    CtrimRefPrsDiv128   = 7u,  /*!< 128 分频 */  
    CtrimRefPrsDiv256   = 8u,  /*!< 256 分频 */
    CtrimRefPrsDiv512   = 9u,  /*!< 512 分频 */
    CtrimRefPrsDiv1024  = 10u, /*!< 1024 分频 */
    CtrimRefPrsDiv2048  = 11u, /*!< 2048 分频 */
    CtrimRefPrsDiv4096  = 12u, /*!< 4096 分频 */
    CtrimRefPrsDiv8192  = 13u, /*!< 8192 分频 */  
    CtrimRefPrsDiv16384 = 14u, /*!< 16384 分频 */
    CtrimRefPrsDiv32768 = 15u, /*!< 32768 分频 */
} en_ctrim_prs_t;


/**
 * @brief CTRIM 实时持续/单次校准配置类型定义
 * @note
 */
typedef enum
{
    CtrimTrimConti    = 0u,    /*!< 实时校准模式 */  
    CtrimTrimOneshot  = 1u,    /*!< 单次校准模式 */
} en_ctrim_ost_t;

/**
 * @brief CTRIM 初始步量类型定义
 * @note
 */
typedef enum
{
    CtrimInitStep2    = 1u,    /*!< 初始步量 2 */  
    CtrimInitStep8    = 2u,    /*!< 初始步量 8 */
    CtrimInitStep16   = 0u,    /*!< 初始步量 16 */  
    CtrimInitStep32   = 3u,    /*!< 初始步量 32 */
    CtrimInitStep128  = 4u,    /*!< 初始步量 128 */
    CtrimInitStep256  = 5u,    /*!< 初始步量 256 */  
    CtrimInitStep512  = 6u,    /*!< 初始步量 512 */
    CtrimInitStep1024 = 7u,    /*!< 初始步量 1024 */
} en_ctrim_step_t;


/**
 * @brief CTRIM 外部管脚输入滤波配置类型定义
 * @note
 */
typedef enum
{
    CtrimEtrFltNone         = 0u,    /*!< 无滤波 */  
    CtrimEtrFltPCLKDiv1Cyc2 = 2u,    /*!< PCLK 2周期 */
    CtrimEtrFltPCLKDiv1Cyc4 = 0u,    /*!< PCLK 4周期 */  
    CtrimEtrFltPCLKDiv1Cyc6 = 3u,    /*!< PCLK 6周期 */
    CtrimEtrFltPCLKDiv4Cyc4 = 4u,    /*!< PCLK/4 4周期 */
    CtrimEtrFltPCLKDiv4Cyc6 = 5u,    /*!< PCLK/4 6周期 */  
    CtrimEtrFltPCLKDiv8Cyc4 = 6u,    /*!< PCLK/8 4周期 */
    CtrimEtrFltPCLKDiv8Cyc6 = 7u,    /*!< PCLK/8 6周期 */
} en_ctrim_etrflt_t;

/**
 * @brief CTRIM 误差计数方向类型定义
 * @note
 */
typedef enum
{
    CtrimDirCntUp    = 0u,    /*!< 递增计数: RCH输出频率高于目标频率，RCL输出频率低于目标频率 */  
    CtrimDirCntdown  = 1u,    /*!< 递减计数: RCH输出频率低于目标频率，RCL输出频率高于目标频率*/
} en_ctrim_cntdir_t;

/**
 * @brief CTRIM 标志/中断类型定义
 * @note
 */
typedef enum
{
    CtrimFlagItUd   = 0x1u,  /*!< 误差计数器下溢中断、标志 (误差计数器已计数到0) */  
    CtrimFlagItEnd  = 0x2u,  /*!< 自动Trim结束中断、标志 */
    CtrimFlagItPs   = 0x4u,  /*!< 误差计数器完成中断、标志 (误差计数器已完成一次计数并停止)*/
    CtrimFlagItMiss = 0x8u,  /*!< 计数失败中断、标志 (在一个GCLK周期内，误差计数器已计数到ARR) */
    CtrimFlagItOv   = 0x10u, /*!< TrimCode溢出中断、标志 (RCH/RCL的TrimCode已调整为0x000u或0x1FFu) */
    CtrimFlagItOk   = 0x20u, /*!< 自动Trim结果在范围内中断、标志 (Trim完成时精度满足要求) */
} en_ctrim_flag_it_t;

/**
 * @}
 */


/*******************************************************************************
 * Global type definitions ('#define')
 ******************************************************************************/


/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CTRIM_Global_Types CTRIM全局类型定义
 * @{
 */

/**
 * @brief  CTRIM 自动校准 配置结构体定义
 */
typedef struct
{
    en_ctrim_md_t     enMode;          /*!< 校准模式 */
    en_ctrim_auto_t   enAutoTrim;
    en_ctrim_src_t    enAccurateClock; /*!< 精确时钟源选择 */
    en_ctrim_prs_t    enRefClockDiv;   /*!< 参考时钟分频 */
    en_ctrim_ost_t    enOneShot;       /*!< 校准模式，实时校准或单次校准 */
    en_ctrim_step_t   enInitialStep;   /*!< TRIM初始步进量 */
    en_ctrim_etrflt_t enEtrFilter;     /*!< 外部输入管脚滤波配置 */
    uint16_t u16ReloadVal;       /*!< 自动装载寄存器ARR配置值 取值范围 0x0 ~ 0xFFFF */
    uint16_t u16CountErrorLimit; /*!< 误差允许值  取值范围 0x0 ~ 0xFFF */
} stc_ctrim_cali_init_t;

/**
 * @brief  CTRIM 定时器 配置结构体定义
 */
typedef struct
{
    en_ctrim_src_t    enClock;     /*!< 时钟源选择 */
    en_ctrim_prs_t    enClockDiv;  /*!< 时钟分频 */
    en_ctrim_etrflt_t enEtrFilter; /*!< 外部输入管脚滤波配置 */
    uint32_t u16ReloadVal; /*!< 自动装载寄存器ARR配置值 取值范围 0x0 ~ 0xFFFF */
} stc_ctrim_timer_init_t;
/**
 * @}
 */

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
/**
 * @addtogroup CTRIM_Global_Functions CTRIM全局函数定义
 * @{
 */
en_result_t CTRIM_CaliInit(stc_ctrim_cali_init_t *pstcInitCfg);
en_result_t CTRIM_TimerInit(stc_ctrim_timer_init_t *pstcInitCfg);
uint32_t    CTRIM_GetCounter(void);
void        CTRIM_SetAutoReload(uint32_t u32AutoReload);
uint32_t    CTRIM_GetAutoReload(void);
void        CTRIM_SetInitialStep(en_ctrim_step_t enTrimStep);
void        CTRIM_SetEtrClockFilter(en_ctrim_etrflt_t enExClockFilter);
void        CTRIM_SetAccurateClock(en_ctrim_src_t enClockSource);
void        CTRIM_SetMode(en_ctrim_md_t enMode);
void        CTRIM_SetRefClockDiv(en_ctrim_prs_t enRefClockDiv);
void        CTRIM_SetOneShot(en_ctrim_ost_t enOneShotMode);
uint32_t    CTRIM_GetARRCoutDir(void);
uint16_t    CTRIM_GetTrimCode(void);
uint16_t    CTRIM_GetCountErrorCapture(void);
void        CTRIM_SetCountErrorLimit(uint16_t u16ErrLimit);
uint16_t    CTRIM_GetCountErrorLimit(void);
void        CTRIM_Enable(void);
void        CTRIM_Disable(void);
boolean_t   CTRIM_IsEnable(void);
void        CTRIM_EnableIT(en_ctrim_flag_it_t enIT);
void        CTRIM_DisableIT(en_ctrim_flag_it_t enIT);
boolean_t   CTRIM_IsEnableIT(en_ctrim_flag_it_t enIT);
boolean_t   CTRIM_IsActiveFlag(en_ctrim_flag_it_t enITFlag);
void        CTRIM_ClearFlag(en_ctrim_flag_it_t enITFlag);
void        CTRIM_ClearFlag_ALL(void);

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

#endif /* __CTRIM_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
