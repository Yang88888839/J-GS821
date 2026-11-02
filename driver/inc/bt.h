/**
 ******************************************************************************
 * @file  bt.h
 * @brief This file contains all the functions prototypes of the BT driver
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

#ifndef __BT_H__
#define __BT_H__

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
 * @defgroup DDL_BT BT模块驱动库
 * @brief BT Driver Library BT模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup BT_Global_Types BT全局类型定义
 * @{
 */

/**
 * @brief  定时器选择数据类型重定义
 */
typedef enum
{
    TIM0 = 0u, /*!< Timer 0 */
    TIM1 = 1u, /*!< Timer 1 */
    TIM2 = 2u, /*!< Timer 2 */
} en_bt_unit_t;

/**
 * @brief  工作模式选择数据类型重定义 (MODE)(模式0/1/23)
 */
typedef enum
{
    BtWorkMode0 = 0u, /*!< 定时器模式 */
    BtWorkMode1 = 1u, /*!< PWC模式 */
    BtWorkMode2 = 2u, /*!< 锯齿波模式 */
    BtWorkMode3 = 3u, /*!< 三角波模式 */
} en_bt_work_mode_t;

/**
 * @brief  极性控制数据类型重定义 (GATE_P)(模式0)
 */
typedef enum
{
    BtGatePositive = 0u, /*!< 高电平有效 */
    BtGateOpposite = 1u, /*!< 低电平有效 */
} en_bt_m0_gatep_t;

/**
 * @brief  TIM 预除频选择 (PRS)(模式0/1/23)
 */
typedef enum
{
    BtPCLKDiv1   = 0u, /*!< Div 1 */
    BtPCLKDiv2   = 1u, /*!< Div 2 */
    BtPCLKDiv4   = 2u, /*!< Div 4 */
    BtPCLKDiv8   = 3u, /*!< Div 8 */
    BtPCLKDiv16  = 4u, /*!< Div 16 */
    BtPCLKDiv32  = 5u, /*!< Div 32 */
    BtPCLKDiv64  = 6u, /*!< Div 64 */
    BtPCLKDiv256 = 7u, /*!< Div 256 */
} en_bt_cr_timclkdiv_t;

/**
 * @brief  计数/定时器功能选择数据类型重定义 (CT)(模式0/1/23)
 */
typedef enum
{
    BtTimer   = 0u, /*!< 定时器功能，计数时钟为内部PCLK */
    BtCounter = 1u, /*!< 计数器功能，计数时钟为外部ETR */
} en_bt_cr_ct_t;

/**
 * @brief  定时器工作模式数据类型重定义 (MD)(模式0)
 */
typedef enum
{
    Bt32bitFreeMode = 0u, /*!< 32位计数器/定时器 */
    Bt16bitArrMode  = 1u, /*!< 自动重载16位计数器/定时器 */
} en_bt_m0cr_md_t;

/**
 * @brief  BT0/BT1/BT2中断类型数据类型重定义(模式0/1/23)
 */
typedef enum
{
    BtUevIrq  = 0u,  /*!< 溢出/事件更新中断 */
    BtCA0Irq  = 2u,  /*!< 捕获/比较中断A(仅模式1/23存在) */
    BtCB0Irq  = 5u,  /*!< 捕获/比较中断B(仅模式23存在) */
    BtCA0E    = 8u,  /*!< CH0A捕获数据丢失标志(仅模式23存在),不是中断 */
    BtCB0E    = 11u, /*!< CH0B捕获数据丢失标志(仅模式23存在),不是中断 */
    BtBkIrq   = 14u, /*!< 刹车中断(仅模式23存在) */
    BtTrigIrq = 15u, /*!< 触发中断(仅模式23存在) */
    BtOVIrq   = 16u, /*!< 上溢中断(仅模式23存在) */
    BtUNDIrq  = 17u, /*!< 下溢中断(仅模式23存在) */
} en_bt_irq_type_t;

/**
 * @brief  测量开始结束数据类型重定义 (Edg1stEdg2nd)(模式1)
 */
typedef enum
{
    BtPwcRiseToRise = 0u, /*!< 上升沿到上升沿(周期) */
    BtPwcFallToRise = 1u, /*!< 下降沿到上升沿(低电平) */
    BtPwcRiseToFall = 2u, /*!< 上升沿到下降沿(高电平) */
    BtPwcFallToFall = 3u, /*!< 下降沿到下降沿(周期) */
} en_bt_m1cr_Edge_t;

/**
 * @brief  PWC测量测试模式选择数据类型重定义 (Oneshot)(模式1)
 */
typedef enum
{
    BtPwcCycleDetect   = 0u, /*!< PWC循环测量 */
    BtPwcOneShotDetect = 1u, /*!< PWC单次测量 */
} en_bt_m1cr_oneshot_t;

/**
 * @brief  PWC IA0选择数据类型重定义 (IA0S)(模式1)
 */
typedef enum
{
    BtIA0Input = 0u, /*!< CHA输入           (TIM0/1/2); CH0A输入            (TIM3) */
    BtXORInput = 1u, /*!< CHA ETR GATE XOR  (TIM0/1/2); CH0A CH1A CH2A XOR  (TIM3) */
} en_bt_m1_mscr_ia0s_t;

/**
 * @brief  PWC IB0选择数据类型重定义 (IA0S)(模式1)
 */
typedef enum
{
    BtIB0Input = 0u, /*!< CH0B输入 */
    BtTsInput  = 1u, /*!< 内部触发TS选择信号 */
} en_bt_m1_mscr_ib0s_t;

/**
 * @brief  输出极性、输入相位 数据类型重定义 (CCPA0/CCPB0/ETP/BKP)(模式1/23)
 */
typedef enum
{
    BtPortPositive = 0u, /*!< 正常输入输出 */
    BtPortOpposite = 1u, /*!< 反向输入输出 */
} en_bt_port_polarity_t;

/**
 * @brief  滤波选择数据类型重定义 (FLTET/FLTA0/FLAB0)(模式1/23)
 */
typedef enum
{
    BtFltNone         = 0u, /*!< 无滤波 */
    BtFltPlckDiv1Cnt2 = 1u, /*!< PCLK/1 2个连续有效 */
    BtFltPlckDiv1Cnt4 = 2u, /*!< PCLK/1 4个连续有效 */
    BtFltPlckDiv1Cnt6 = 3u, /*!< PCLK/1 6个连续有效 */
    BtFltPCLKDiv4Cnt4 = 4u, /*!< PCLK/4 4个连续有效 */
    BtFltPCLKDiv4Cnt6 = 5u, /*!< PCLK/4 6个连续有效 */
    BtFltPCLKDiv8Cnt4 = 6u, /*!< PCLK/8 4个连续有效 */
    BtFltPCLKDiv8Cnt6 = 7u, /*!< PCLK/8 6个连续有效 */
} en_bt_flt_t;

/**
 * @brief  通道比较控制 数据类型重定义 (OCMA/OCMB)(模式23)
 */
typedef enum
{
    BtForceLow      = 0u, /*!< 强制为0 */
    BtForceHigh     = 1u, /*!< 强制为1 */
    BtCMPForceLow   = 2u, /*!< 比较匹配时强制为0 */
    BtCMPForceHigh  = 3u, /*!< 比较匹配时强制为1 */
    BtCMPInverse    = 4u, /*!< 比较匹配时翻转电平 */
    BtCMPOnePrdHigh = 5u, /*!< 比较匹配时输出一个计数周期的高电平 */
    BtPWMMode1      = 6u, /*!< 通道控制为PWM mode 1 */
    BtPWMMode2      = 7u, /*!< 通道控制为PWM mode 2 */
} en_bt_m23_fltr_ocm_t;

/**
 * @brief  主从模式TS数据类型重定义 (TS)(模式1/23)
 */
typedef enum
{
    BtTs0ETR      = 0u, /*!< ETR外部输入滤波后的相位选择信号 */
    BtTs1TIM0TRGO = 1u, /*!< Timer0的TRGO输出信号 */
    BtTs2TIM1TRGO = 2u, /*!< Timer1的TRGO输出信号 */
    BtTs3TIM2TRGO = 3u, /*!< Timer2的TRGO输出信号 */
    BtTs4TIM3TRGO = 4u, /*!< Timer3的TRGO输出信号 */
    BtTs5IA0ED    = 5u, /*!< CH0A的边沿信号 (模式1无效) */
    BtTs6IAFP     = 6u, /*!< CH0A 外部输输入滤波后的相位选择信号 */
    BtTs7IBFP     = 7u, /*!< CH0B 外部输输入滤波后的相位选择信号 */
} en_bt_mscr_ts_t;

/**
 * @brief  PWM输出模式选择数据类型重定义 (COMP)(模式23)
 */
typedef enum
{
    BtIndependentPWM   = 0u, /*!< 独立PWM输出 */
    BtComplementaryPWM = 1u, /*!< 互补PWM输出 */
} en_bt_m23cr_comp_t;

/**
 * @brief  计数方向选择数据类型重定义 (DIR)(模式23)
 */
typedef enum
{
    BtCntUp   = 0u, /*!< 向上计数 */
    BtCntDown = 1u, /*!< 向下计数 */
} en_bt_m23cr_dir_t;

/**
 * @brief  计数方向选择数据类型重定义 (PWM2S)(模式23)
 */
typedef enum
{
    BtDoublePointCmp = 0u, /*!< 双点比较使能，使用CCRA,CCRB比较控制OCREFA输出 */
    BtSinglePointCmp = 1u, /*!< 单点比较使能，使用CCRA比较控制OCREFA输出 */
} en_bt_m23cr_pwm2s_t;

/**
 * @brief  GATE在PWM互补模式下捕获或比较功能 选择数据类型重定义 (CSG)(模式23)
 */
typedef enum
{
    BtPWMCompGateCmpOut = 0u, /*!< 在PWM互补模式下，Gate作为比较输出 */
    BtPWMCompGateCapIn  = 1u, /*!< 在PWM互补模式下，Gate作为捕获输入 */
} en_bt_m23cr_csg_t;

/**
 * @brief  比较捕获寄存器 数据类型重定义 (CCR0A,CCR0B)(模式23)
 */
typedef enum
{
    BtCCR0A = 0u, /*!< CCR0A比较捕获寄存器 */
    BtCCR0B = 1u, /*!< CCR0B比较捕获寄存器 */
} en_bt_m23_ccrx_t;

/**
 * @brief  OCREF清除源 选择数据类型重定义 (OCCS)(模式23)
 */
typedef enum
{
    BtOC_Ref_Clr = 0u, /*!< 来自VC的OC_Ref_Clr */
    BtETRf       = 1u, /*!< 外部ETRf */
} en_bt_m23ce_occs_t;

/**
 * @brief  比较匹配中断模式 选择数据类型重定义 (CIS/CISB)(模式23)
 */
typedef enum
{
    BtCmpIntNone     = 0u, /*!< 无比较匹配中断 */
    BtCmpIntRise     = 1u, /*!< 比较匹配上升沿中断 */
    BtCmpIntFall     = 2u, /*!< 比较匹配下降沿中断 */
    BtCmpIntRiseFall = 3u, /*!< 比较匹配上升沿下降沿中断 */
} en_bt_m23_cisa_cisb_t;

/**
 * @brief  BT端口控制 - 刹车时CHx输出状态控制(BKSA/BKSB)(模式23)
 */
typedef enum
{
    BtCHxBksHiZ  = 0u, /*!< 刹车使能时，CHx端口输出高阻态 */
    BtCHxBksNorm = 1u, /*!< 刹车使能时，CHx端口正常输出 */
    BtCHxBksLow  = 2u, /*!< 刹车使能时，CHx端口输出低电平 */
    BtCHxBksHigh = 3u, /*!< 刹车使能时，CHx端口输出高电平 */
} en_bt_m23_crch0_bks_t;

/**
 * @brief  BT端口控制 - CHx上升沿下降沿捕获(CRx/CFx)(模式23)
 */
typedef enum
{
    BtCHxCapNone     = 0u, /*!< CHx通道捕获禁止 */
    BtCHxCapRise     = 1u, /*!< CHx通道上升沿捕获使能 */
    BtCHxCapFall     = 2u, /*!< CHx通道下降沿捕获使能 */
    BtCHxCapFallRise = 3u, /*!< CHx通道上升沿下降沿捕获都使能 */
} en_bt_m23_crch0_cfx_crx_t;

/**
 * @brief  BT端口控制 - CHx比较捕获模式(CSA/CSB)(模式23)
 */
typedef enum
{
    BtCHxCmpMode = 0u, /*!< CHx通道设置为比较模式 */
    BtCHxCapMode = 1u, /*!< CHx通道设置为捕获模式 */
} en_bt_m23_crch0_csa_csb_t;

/**
 * @brief  比较模式下 DMA比较触发选择 数据类型重定义 (CCDS)(模式23)
 */
typedef enum
{
    BtCmpTrigDMA = 0u, /*!< 比较匹配触发DMA */
    BtUEVTrigDMA = 1u, /*!< 事件更新代替比较匹配触发DMA */
} en_bt_m23_mscr_ccds_t;

/**
 * @brief  主从模式选择 数据类型重定义 (MSM)(模式23)
 */
typedef enum
{
    BtSlaveMode  = 0u, /*!< 从模式 */
    BtMasterMode = 1u, /*!< 主模式 */
} en_bt_m23_mscr_msm_t;

/**
 * @brief  触发主模式输出源 数据类型重定义 (MMS)(模式23)
 */
typedef enum
{
    BtMasterUG      = 0u, /*!< UG(软件更新)源 */
    BtMasterCTEN    = 1u, /*!< CTEN源 */
    BtMasterUEV     = 2u, /*!< UEV更新源 */
    BtMasterCMPSO   = 3u, /*!< 比较匹配选择输出源 */
    BtMasterOCA0Ref = 4u, /*!< OCA0_Ref源 */
    BtMasterOCB0Ref = 5u, /*!< OCB0_Ref源 */
} en_bt_m23_mscr_mms_t;

/**
 * @brief  触发从模式选择 数据类型重定义 (SMS)(模式23)
 */
typedef enum
{
    BtSlaveIClk     = 0u, /*!< 使用内部时钟 */
    BtSlaveResetTIM = 1u, /*!< 复位功能 */
    BtSlaveTrigMode = 2u, /*!< 触发模式 */
    BtSlaveEClk     = 3u, /*!< 外部时钟模式 */
    BtSlaveCodeCnt1 = 4u, /*!< 正交编码计数模式1 */
    BtSlaveCodeCnt2 = 5u, /*!< 正交编码计数模式2 */
    BtSlaveCodeCnt3 = 6u, /*!< 正交编码计数模式3 */
    BtSlaveGateCtrl = 7u, /*!< 门控功能 */
} en_bt_m23_mscr_sms_t;

/**
 * @brief  定时器运行控制数据类型重定义 (CTEN)
 */
typedef enum
{
    BtCTENDisable = 0u, /*!< 停止 */
    BtCTENEnable  = 1u, /*!< 运行 */
} en_bt_start_t;

/**
 * @brief  BaseTimer mode0 配置结构体定义(模式0)
 */
typedef struct
{
    en_bt_work_mode_t    enWorkMode; /*!< 工作模式设置 */
    en_bt_m0_gatep_t     enGateP;    /*!< 门控极性控制 */
    boolean_t            bEnGate;    /*!< 门控使能 */
    en_bt_cr_timclkdiv_t enPRS;      /*!< 预除频配置 */
    boolean_t            bEnTog;     /*!< 翻转输出使能 */
    en_bt_cr_ct_t        enCT;       /*!< 定时/计数功能选择 */
    en_bt_m0cr_md_t      enCntMode;  /*!< 计数模式配置 */
} stc_bt_mode0_cfg_t;

/**
 * @brief  BaseTimer mode1 配置结构体定义(模式1)
 */
typedef struct
{
    en_bt_work_mode_t    enWorkMode; /*!< 工作模式设置 */
    en_bt_cr_timclkdiv_t enPRS;      /*!< 预除频配置 */
    en_bt_cr_ct_t        enCT;       /*!< 定时/计数功能选择 */
    en_bt_m1cr_oneshot_t enOneShot;  /*!< 单次测量/循环测量选择 */
} stc_bt_mode1_cfg_t;

/**
 * @brief  PWC输入配置结构体定义(模式1)
 */
typedef struct
{
    en_bt_mscr_ts_t       enTsSel;    /*!< 触发输入源选择 */
    en_bt_m1_mscr_ia0s_t  enIA0Sel;   /*!< CH0A输入选择 */
    en_bt_m1_mscr_ib0s_t  enIB0Sel;   /*!< CH0B输入选择 */
    en_bt_port_polarity_t enETRPhase; /*!< ETR相位选择 */
    en_bt_flt_t           enFltETR;   /*!< ETR滤波设置 */
    en_bt_flt_t           enFltIA0;   /*!< CH0A滤波设置 */
    en_bt_flt_t           enFltIB0;   /*!< CH0B滤波设置 */
} stc_bt_pwc_input_cfg_t;

/**
 * @brief  BaseTimer mode23 配置结构体定义(模式23)
 */
typedef struct
{
    en_bt_work_mode_t    enWorkMode;   /*!< 工作模式设置 */
    en_bt_m23cr_dir_t    enCntDir;     /*!< 计数方向 */
    en_bt_cr_timclkdiv_t enPRS;        /*!< 时钟预除频配置 */
    en_bt_cr_ct_t        enCT;         /*!< 定时/计数功能选择 */
    en_bt_m23cr_comp_t   enPWMTypeSel; /*!< PWM模式选择（独立/互补） */
    en_bt_m23cr_pwm2s_t  enPWM2sSel;   /*!< OCREFA双点比较功能选择 */
    boolean_t            bOneShot;     /*!< 单次触发模式使能/禁止 */
    boolean_t            bURSSel;      /*!< 更新源选择 */
} stc_bt_mode23_cfg_t;

/**
 * @brief  GATE在PWM互补模式下捕获或比较功能 配置结构体定义(模式23)
 */
typedef struct
{
    en_bt_m23cr_csg_t enGateFuncSel; /*!< Gate比较、捕获功能选择 */
    boolean_t         bGateRiseCap;  /*!< GATE作为捕获功能时，上沿捕获有效控制 */
    boolean_t         bGateFallCap;  /*!< GATE作为捕获功能时，下沿捕获有效控制 */
} stc_bt_m23_gate_cfg_t;

/**
 * @brief  CHA/CHB通道比较控制 配置结构体定义(模式23)
 */
typedef struct
{
    en_bt_m23_crch0_csa_csb_t enCh0ACmpCap;    /*!< CH0A比较/捕获功能选择 */
    en_bt_m23_fltr_ocm_t      enCH0ACmpCtrl;   /*!< CH0A通道比较控制 */
    en_bt_port_polarity_t     enCH0APolarity;  /*!< CH0A输出极性控制 */
    boolean_t                 bCh0ACmpBufEn;   /*!< 比较A缓存功能 使能/禁止 */
    en_bt_m23_cisa_cisb_t     enCh0ACmpIntSel; /*!< CH0A比较匹配中断选择 */

    en_bt_m23_crch0_csa_csb_t enCh0BCmpCap;    /*!< CH0B比较/捕获功能选择 */
    en_bt_m23_fltr_ocm_t      enCH0BCmpCtrl;   /*!< CH0B通道比较控制 */
    en_bt_port_polarity_t     enCH0BPolarity;  /*!< CH0B输出极性控制 */
    boolean_t                 bCH0BCmpBufEn;   /*!< 比较B缓存功能 使能/禁止 */
    en_bt_m23_cisa_cisb_t     enCH0BCmpIntSel; /*!< CH0B比较匹配中断选择 */
} stc_bt_m23_compare_cfg_t;

/**
 * @brief  CHA/CHB通道捕获控制 配置结构体定义(模式23)
 */
typedef struct
{
    en_bt_m23_crch0_csa_csb_t enCh0ACmpCap;   /*!< CH0A比较/捕获功能选择 */
    en_bt_m23_crch0_cfx_crx_t enCH0ACapSel;   /*!< CH0A捕获边沿选择 */
    en_bt_flt_t               enCH0AInFlt;    /*!< CH0A通道捕获滤波控制 */
    en_bt_port_polarity_t     enCH0APolarity; /*!< CH0A输入相位 */

    en_bt_m23_crch0_csa_csb_t enCh0BCmpCap;   /*!< CH0B比较/捕获功能选择 */
    en_bt_m23_crch0_cfx_crx_t enCH0BCapSel;   /*!< CH0B捕获边沿选择 */
    en_bt_flt_t               enCH0BInFlt;    /*!< CH0B通道捕获滤波控制 */
    en_bt_port_polarity_t     enCH0BPolarity; /*!< CH0B输入相位 */

} stc_bt_m23_input_cfg_t;

/**
 * @brief  ETR输入相位滤波配置结构体定义(模式23)
 */
typedef struct
{
    en_bt_port_polarity_t enETRPolarity; /*!< ETR输入极性设置 */
    en_bt_flt_t           enETRFlt;      /*!< ETR滤波设置 */
} stc_bt_m23_etr_input_cfg_t;

/**
 * @brief  刹车BK输入相位滤波配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t             bEnBrake;        /*!< 刹车使能 */
    boolean_t             bEnVCBrake;      /*!< 使能VC刹车 */
    boolean_t             bEnSafetyBk;     /*!< 使能safety刹车 */
    boolean_t             bEnBKSync;       /*!< TIM0/TIM1/TIM2刹车同步使能 */
    en_bt_m23_crch0_bks_t enBkCH0AStat;    /*!< 刹车时CHA端口状态设置 */
    en_bt_m23_crch0_bks_t enBkCH0BStat;    /*!< 刹车时CHB端口状态设置 */
    en_bt_port_polarity_t enBrakePolarity; /*!< 刹车BK输入极性设置 */
    en_bt_flt_t           enBrakeFlt;      /*!< 刹车BK滤波设置 */
} stc_bt_m23_bk_input_cfg_t;

/**
 * @brief  死区功能配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t bEnDeadTime;     /*!< 死区控制使能 */
    uint8_t   u8DeadTimeValue; /*!< 死区时间设置 */
} stc_bt_m23_dt_cfg_t;

/**
 * @brief  触发ADC配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t bEnTrigADC;        /*!< 触发ADC全局控制 */
    boolean_t bEnUevTrigADC;     /*!< 事件更新触发ADC */
    boolean_t bEnCH0ACmpTrigADC; /*!< CH0A比较匹配触发ADC */
    boolean_t bEnCH0BCmpTrigADC; /*!< CH0B比较匹配触发ADC */
} stc_bt_m23_adc_trig_cfg_t;

/**
 * @brief  DMA触发 配置结构体定义(模式23)
 */
typedef struct
{
    boolean_t             bUevTrigDMA;     /*!< 更新 触发DMA使能 */
    boolean_t             bTITrigDMA;      /*!< Trig 触发DMA功能 */
    boolean_t             bCmpATrigDMA;    /*!< A捕获比较触发DMA使能 */
    boolean_t             bCmpBTrigDMA;    /*!< B捕获比较触发DMA使能 */
    en_bt_m23_mscr_ccds_t enCmpUevTrigDMA; /*!< 比较模式下DMA比较触发选择 */
} stc_bt_m23_trig_dma_cfg_t;

/**
 * @brief  主从模式 配置结构体定义(模式23)
 */
typedef struct
{
    en_bt_m23_mscr_msm_t enMasterSlaveSel; /*!< 主从模式选择 */
    en_bt_m23_mscr_mms_t enMasterSrc;      /*!< 主模式触发源选择 */
    en_bt_m23_mscr_sms_t enSlaveModeSel;   /*!< 从模式选择 */
    en_bt_mscr_ts_t      enTsSel;          /*!< 触发输入源选择 */
} stc_bt_m23_master_slave_cfg_t;

/**
 * @brief  OCREF清除功能 配置结构体定义(模式23)
 */
typedef struct
{
    en_bt_m23ce_occs_t enOCRefClrSrcSel; /*!< OCREF清除源选择 */
    boolean_t          bVCClrEn;         /*!< 是否使能来自VC的OCREF_Clr */
} stc_bt_m23_OCREF_Clr_cfg_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup BT_Global_Functions BT全局函数定义
 * @{
 */

/* 中断相关函数 */

/* 中断标志获取 */
boolean_t Bt_GetIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
/* 中断标志清除 */
en_result_t Bt_ClearIntFlag(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
/* 所有中断标志清除 */
en_result_t Bt_ClearAllIntFlag(en_bt_unit_t enUnit);
/* 模式0中断使能 */
en_result_t Bt_Mode0_EnableIrq(en_bt_unit_t enUnit);
/* 模式1中断使能 */
en_result_t Bt_Mode1_EnableIrq(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
/* 模式2中断使能 */
en_result_t Bt_Mode23_EnableIrq(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
/* 模式0中断禁止 */
en_result_t Bt_Mode0_DisableIrq(en_bt_unit_t enUnit);
/* 模式1中断禁止 */
en_result_t Bt_Mode1_DisableIrq(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);
/* 模式2中断禁止 */
en_result_t Bt_Mode23_DisableIrq(en_bt_unit_t enUnit, en_bt_irq_type_t enBtIrq);

/* 模式0初始化及相关功能操作 */

/* timer配置及初始化 */
en_result_t Bt_Mode0_Init(en_bt_unit_t enUnit, stc_bt_mode0_cfg_t *pstcCfg);
/* timer 启动 */
en_result_t Bt_M0_Run(en_bt_unit_t enUnit);
/* timer 停止 */
en_result_t Bt_M0_Stop(en_bt_unit_t enUnit);
/* 重载值设置 */
en_result_t Bt_M0_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data);
/* 16位计数值设置 */
en_result_t Bt_M0_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
/* 16位计数值获取 */
uint16_t Bt_M0_Cnt16Get(en_bt_unit_t enUnit);
/* 32位计数值设置 */
en_result_t Bt_M0_Cnt32Set(en_bt_unit_t enUnit, uint32_t u32Data);
/* 32位计数值获取 */
uint32_t Bt_M0_Cnt32Get(en_bt_unit_t enUnit);
/* 翻转输出使能/禁止（低电平）设定 */
en_result_t Bt_M0_EnTOG_Output(en_bt_unit_t enUnit, boolean_t bEnTOG);
/* 端口输出使能/禁止设定 */
en_result_t Bt_M0_Enable_Output(en_bt_unit_t enUnit, boolean_t bEnOutput);

/* 模式1初始化及相关功能操作 */

/* timer配置及初始化 */
en_result_t Bt_Mode1_Init(en_bt_unit_t enUnit, stc_bt_mode1_cfg_t *pstcCfg);
/* PWC 输入配置 */
en_result_t Bt_M1_Input_Cfg(en_bt_unit_t enUnit, stc_bt_pwc_input_cfg_t *pstcCfg);
/* PWC测量边沿起始结束选择 */
en_result_t Bt_M1_PWC_Edge_Sel(en_bt_unit_t enUnit, en_bt_m1cr_Edge_t enEdgeSel);
/* timer 启动 */
en_result_t Bt_M1_Run(en_bt_unit_t enUnit);
/* timer 停止 */
en_result_t Bt_M1_Stop(en_bt_unit_t enUnit);
/* 16位计数值设置 */
en_result_t Bt_M1_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
/* 16位计数值获取 */
uint16_t Bt_M1_Cnt16Get(en_bt_unit_t enUnit);
/* 脉冲宽度测量结果数值获取 */
uint16_t Bt_M1_PWC_CapValueGet(en_bt_unit_t enUnit);

/* 模式23初始化及相关功能操作 */

/* timer配置及初始化 */
en_result_t Bt_Mode23_Init(en_bt_unit_t enUnit, stc_bt_mode23_cfg_t *pstcCfg);
/* timer 启动 */
en_result_t Bt_M23_Run(en_bt_unit_t enUnit);
/* timer 停止 */
en_result_t Bt_M23_Stop(en_bt_unit_t enUnit);
/* PWM输出使能 */
en_result_t Bt_M23_EnPWM_Output(en_bt_unit_t enUnit, boolean_t bEnOutput, boolean_t bEnAutoOutput);
/* 重载值设置 */
en_result_t Bt_M23_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data, boolean_t bArrBufEn);
/* 16位计数值设置 */
en_result_t Bt_M23_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
/* 16位计数值获取 */
uint16_t Bt_M23_Cnt16Get(en_bt_unit_t enUnit);
/* 比较捕获寄存器CCR0A/CCR0B设置 */
en_result_t Bt_M23_CCR_Set(en_bt_unit_t enUnit, en_bt_m23_ccrx_t enCCRSel, uint16_t u16Data);
/* 比较捕获寄存器CCR0A/CCR0B读取 */
uint16_t Bt_M23_CCR_Get(en_bt_unit_t enUnit, en_bt_m23_ccrx_t enCCRSel);
/* PWM互补输出模式下，GATE功能选择 */
en_result_t Bt_M23_GateFuncSel(en_bt_unit_t enUnit, stc_bt_m23_gate_cfg_t *pstcCfg);
/* 主从模式配置 */
en_result_t Bt_M23_MasterSlave_Set(en_bt_unit_t enUnit, stc_bt_m23_master_slave_cfg_t *pstcCfg);
/* CH0A/CH0B比较通道控制 */
en_result_t Bt_M23_PortOutput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_compare_cfg_t *pstcCfg);
/* CH0A/CH0B输入控制 */
en_result_t Bt_M23_PortInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_input_cfg_t *pstcCfg);
/* ERT输入控制 */
en_result_t Bt_M23_ETRInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_etr_input_cfg_t *pstcCfg);
/* 刹车BK输入控制 */
en_result_t Bt_M23_BrakeInput_Cfg(en_bt_unit_t enUnit, stc_bt_m23_bk_input_cfg_t *pstcCfg);
/* 触发ADC控制 */
en_result_t Bt_M23_TrigADC_Cfg(en_bt_unit_t enUnit, stc_bt_m23_adc_trig_cfg_t *pstcCfg);
/* 死区功能 */
en_result_t Bt_M23_DT_Cfg(en_bt_unit_t enUnit, stc_bt_m23_dt_cfg_t *pstcCfg);
/* 重复周期设置 */
en_result_t Bt_M23_SetValidPeriod(en_bt_unit_t enUnit, uint8_t u8ValidPeriod, boolean_t bOVMaskEn, boolean_t bUDMaskEn);
/* OCREF清除功能 */
en_result_t Bt_M23_OCRefClr(en_bt_unit_t enUnit, stc_bt_m23_OCREF_Clr_cfg_t *pstcCfg);
/* 使能DMA传输 */
en_result_t Bt_M23_EnDMA(en_bt_unit_t enUnit, stc_bt_m23_trig_dma_cfg_t *pstcCfg);
/* 捕获比较A软件触发 */
en_result_t Bt_M23_EnSwTrigCapCmpA(en_bt_unit_t enUnit);
/* 捕获比较B软件触发 */
en_result_t Bt_M23_EnSwTrigCapCmpB(en_bt_unit_t enUnit);
/* 软件更新使能 */
en_result_t Bt_M23_EnSwUev(en_bt_unit_t enUnit);
/* 软件触发使能 */
en_result_t Bt_M23_EnSwTrig(en_bt_unit_t enUnit);
/* 软件刹车使能 */
en_result_t Bt_M23_EnSwBk(en_bt_unit_t enUnit);

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

#endif /* __BT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
