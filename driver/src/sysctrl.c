/**
 *******************************************************************************
 * @file  sysctrl.c
 * @brief This file provides - functions to manage the SYSCTRL.
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
#include "sysctrl.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SYSCTRL SYSCTRL模块驱动库
 * @brief Sysctrl Driver Library SYSCTRL模块驱动库
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Macros SYSCTRL局部宏定义
 * @{
 */
#define CLK_TIMEOUT             (1000000u)

#define IS_VALID_SRC(x)         (   ClkRCH == (x)||\
                                    ClkXTH == (x)||\
                                    ClkRCL == (x)||\
                                    ClkXTL == (x) )


#define IS_VALID_FUNC(x)        (   ClkFuncWkupRCH == (x)||\
                                    ClkFuncXTHEn == (x)||\
                                    ClkFuncXTLEn == (x)||\
                                    ClkFuncXTLAWSON == (x)||\
                                    ClkFuncFaultEn == (x)||\
                                    ClkFuncRtcLPWEn == (x)||\
                                    ClkFuncLockUpEn == (x)||\
                                    ClkFuncRstPinIOEn == (x)||\
                                    ClkFuncSwdPinIOEn == (x) )

#define RC_TRIM_BASE_ADDR           ((volatile uint32_t*)   (0x00101BA8ul))

#define RCL_HPM_CR_TRIM_32768_VAL   (*((volatile uint16_t*) (0x00101BA8ul)))
#define RCL_HPM_CR_TRIM_38400_VAL   (*((volatile uint16_t*) (0x00101BACul)))
    
#define RCL_LPM_CR_TRIM_32768_VAL   (*((volatile uint16_t*) (0x00101BC4ul)))
#define RCL_LPM_CR_TRIM_38400_VAL   (*((volatile uint16_t*) (0x00101BC8ul)))

#define RCH_TRIM_BASE_ADDR         ((volatile uint32_t*)   (0x00101BBCul))
#define RCH_CR_TRIM_48M_VAL        (*((volatile uint32_t*) (0x00101BB0ul)))
#define RCH_CR_TRIM_32M_VAL        (*((volatile uint32_t*) (0x00101BB4ul)))
#define RCH_CR_TRIM_6M_VAL         (*((volatile uint32_t*) (0x00101BB8ul)))
#define RCH_CR_TRIM_4M_VAL         (*((volatile uint32_t*) (0x00101BBCul)))
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Global_Variables SYSCTRL全局变量定义
 * @{
 */
extern uint32_t SystemCoreClock;
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Global_Functions SYSCTRL全局函数定义
 * @{
 */

/**
 * @brief SYSCTRL0\SYSCTRL1寄存器操作解锁
 *
 * @retval None
 */
static void _SysctrlUnlock(void)
{
    M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
    M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
}

/**
 * @brief 系统时钟源使能
 * @param [in]  enSource   目标时钟源 @ref en_sysctrl_clk_source_t
 * @param [in]  bFlag      TRUE: 使能; FALSE: 关闭
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 * @note 注意：调用此函数使能时钟之前，必须先设置目标时钟的相关参数，
 * @note       如RCH的TRIM值，RCH_CR寄存器参数，PLL的参数或外部时钟源的频率（振幅）范围、驱动能力和稳定时间等
 */
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag)
{
    en_result_t enRet = Ok;
    uint32_t u32Temp;

    _SysctrlUnlock();
    bFlag = !!bFlag;

    u32Temp = M0P_SYSCTRL->PERI_CLKEN0;
    switch (enSource)
    {
        case SysctrlClkXTH:
            M0P_SYSCTRL->PERI_CLKEN0_f.GPIO = TRUE;
            M0P_GPIO->PDADS |= 3u;
            M0P_SYSCTRL->SYSCTRL0_f.XTH_EN = bFlag;
            while (bFlag && (1u != M0P_SYSCTRL->XTH_CR_f.STABLE))
            {
                ;
            }
            break;

        case SysctrlClkRCL:
            M0P_SYSCTRL->SYSCTRL0_f.RCL_EN = bFlag;
            while (bFlag && (1u != M0P_SYSCTRL->RCL_CR_f.STABLE))
            {
                ;
            }
            break;

        case SysctrlClkXTL:
            M0P_SYSCTRL->PERI_CLKEN0_f.GPIO = TRUE;
            M0P_GPIO->PCADS |= 0xC000u;
            M0P_SYSCTRL->SYSCTRL0_f.XTL_EN = bFlag;
            while (bFlag && (1u != M0P_SYSCTRL->XTL_CR_f.STABLE))
            {
                ;
            }
            break;
            
        case SysctrlClkRCH:
            M0P_SYSCTRL->SYSCTRL0_f.RCH_EN = bFlag;
            while (bFlag && (1u != M0P_SYSCTRL->RCH_CR_f.STABLE))
            {
                ;
            }
            break;

        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    M0P_SYSCTRL->PERI_CLKEN0 = u32Temp;

    return enRet;
}

/**
 * @brief 外部输入时钟信号使能
 * @param [in]  enSource   目标时钟源 @ref en_sysctrl_extclk_t
 * @param [in]  bFlag      TRUE: 使能; FALSE: 关闭
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 * @note 注意：调调用此函数使能时钟之前，必须先设置目标时钟的稳定时间参数
 */
en_result_t Sysctrl_Ext_Enable(en_sysctrl_extclk_t enSource, boolean_t bFlag)
{
    en_result_t enRet = Ok;
    uint32_t u32Temp;
    
     _SysctrlUnlock();
    bFlag = !!bFlag;
    
    u32Temp = M0P_SYSCTRL->PERI_CLKEN0;
    switch (enSource)
    {
        case SysctrlExtXth:
            M0P_SYSCTRL->PERI_CLKEN0_f.GPIO = TRUE;
            M0P_GPIO->PDADS_f.PD00 = 0u;
            M0P_GPIO->PDDIR_f.PD00 = 1u;
            M0P_SYSCTRL->SYSCTRL1_f.EXTH_EN = bFlag;
            while (bFlag && (1u != M0P_SYSCTRL->XTH_CR_f.STABLE))
            {
                ;
            }
            break;

        case SysctrlExtXtl:
            M0P_SYSCTRL->PERI_CLKEN0_f.GPIO = TRUE;
            M0P_GPIO->PCADS_f.PC14 = 0u;
            M0P_GPIO->PCDIR_f.PC14 = 1u;
            M0P_SYSCTRL->SYSCTRL1_f.EXTL_EN = bFlag;
            while (bFlag && (1u != M0P_SYSCTRL->XTL_CR_f.STABLE))
            {
                ;
            }
            break;


        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    M0P_SYSCTRL->PERI_CLKEN0 = u32Temp;
    
    return enRet;
}

/**
 * @brief 时钟源切换，该函数执行后会开启新时钟源
 * @note  选择时钟源之前，需根据需要配置目标时钟源的频率/驱动参数/使能时钟源等
 * @param [in]  enSource   新时钟源 @ref en_sysctrl_clk_source_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 * @note 注意1：调用此函数前，必须确保新的系统时钟源的相关参数已经初始化，并且新时钟源已经使能且稳定运行
 * @note 注意2：时钟切换前后，必须根据目标频率值设置Flash读等待周期，可配置插入周期为0、1、2
 * @note 注意3：当HCLK大于24MHz时，FLASH等待周期插入必须至少为1,否则程序运行可能产生未知错误
 */
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource)
{
    en_result_t enRet = Ok;

    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.CLKSW = enSource;

    /* 更新Core时钟（HCLK）*/
    SystemCoreClockUpdate();

    return enRet;
}

/**
 * @brief   获得系统时钟（HCLK）频率值
 * @retval  uint32_t: HCLK频率值
 * @note 注意:本驱动默认宏定义：SYSTEM_XTH=8MHz,SYSTEM_XTL=32768Hz,如使用其它外部晶振，必须修改这两个宏定义的值
 * @note 注意:如果手动修改或者调用CLKTRIM/CTRIM修改RCH/RCH/RCL时钟的TRIM值，此函数可能不会返回正确的HCLK频率值
 */
uint32_t Sysctrl_GetHClkFreq(void)
{
    uint32_t u32Val = 0;
    const uint16_t u32lcr_tbl[] = { 32768, 38400};
    const uint32_t u32rch_tbl[] = {4000000, 6000000, 32000000, 48000000};
    
    en_sysctrl_clk_source_t enSrc;
    uint16_t u16Trim[5] = {0};
    u16Trim[0] = RCL_HPM_CR_TRIM_32768_VAL & 0x3FFu;
    u16Trim[1] = RCL_LPM_CR_TRIM_32768_VAL & 0x3FFu;

    /* 获取当前系统时钟 */
    enSrc = (en_sysctrl_clk_source_t)(M0P_SYSCTRL->SYSCTRL0_f.CLKSW);

    switch (enSrc)
    {
        case SysctrlClkRCH:
        {
            if (M0P_SYSCTRL->RCH_CR_f.FSEL == 3u)
            {
                u32Val = u32rch_tbl[3];
            }
            else if (M0P_SYSCTRL->RCH_CR_f.FSEL == 2u)
            {
                u32Val = u32rch_tbl[2];
            }
            else if (M0P_SYSCTRL->RCH_CR_f.FSEL == 1u)
            {
                u32Val = u32rch_tbl[1];
            }
            else
            {
                u32Val = u32rch_tbl[0];
            }
        }
            break;
        case SysctrlClkXTH:
            u32Val = SYSTEM_XTH;
            break;
        case SysctrlClkRCL:
        {
            if ((u16Trim[0] == (uint16_t)(M0P_SYSCTRL->RCL_CR_f.TRIM)) || (u16Trim[1] == (uint16_t)(M0P_SYSCTRL->RCL_CR_f.TRIM)))
            {
                u32Val = u32lcr_tbl[0];
            }
            else
            {
                u32Val = u32lcr_tbl[1];
            }
        }
            break;
        case SysctrlClkXTL:
            u32Val = SYSTEM_XTL;
            break;
        default:
            u32Val = 0u;
            break;
    }

    u32Val = (u32Val >> M0P_SYSCTRL->SYSCTRL0_f.HCLK_PRS);

    return u32Val;
}

/**
 * @brief 获得外设时钟（PCLK）频率值
 * @retval uint32_t: PCLK频率值(Hz)
 */
uint32_t Sysctrl_GetPClkFreq(void)
{
    uint32_t u32Val = 0;

    u32Val = Sysctrl_GetHClkFreq();
    u32Val = (u32Val >> (M0P_SYSCTRL->SYSCTRL0_f.PCLK_PRS));

    return u32Val;
}


/**
 * @brief 时钟初始化函数
 * @note 用于上电后，系统工作之前对主频及外设时钟进行初始化
 * @param [in]  pstcCfg    初始化配置结构体指针 @ref stc_sysctrl_clk_cfg_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 * @note 注意1:使用该初始化函数前需要根据系统，必须优先设置目标内部时钟源RCH或RCL的TRIM值、外部时高速钟源XTH的频率范围
 * @note 注意2:XTH、XTL的频率范围设定，驱动能力设置需要根据外部晶振决定，用户需根据实际情况修改此函数内的默认值
 * @note 注意3:本驱动默认宏定义：SYSTEM_XTH=8MHz,SYSTEM_XTL=32768Hz,如使用其它频率外部晶振，必须修改这两个宏定义的值
 * @note 注意4:本函数默认配置RCL功耗模式为低功耗模式
 * @note 注意5:如果选择的时钟源频率超过24MHz，需要在调用此函数前合理设置FLASH读等待周期
 */
en_result_t Sysctrl_ClkInit(stc_sysctrl_clk_cfg_t *pstcCfg)
{
    en_result_t enRet = Ok;

    /* 系统时钟参数配置 */
    switch (pstcCfg->enClkSrc)
    {
        case SysctrlClkRCH:

            break;
        case SysctrlClkXTH:
            Sysctrl_XTHDriverCfg(SysctrlXtalDriver2);
            Sysctrl_SetXTHStableTime(SysctrlXthStableCycle2621144);
            break;
        case SysctrlClkRCL:

            break;
        case SysctrlClkXTL:
            Sysctrl_XTLDriverCfg(SysctrlXtlAmp2, SysctrlXtalDriver2);
            Sysctrl_SetXTLStableTime(SysctrlXtlStableCycle16384);
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    /* 时钟源使能 */
    Sysctrl_ClkSourceEnable(pstcCfg->enClkSrc, TRUE);

    /* 时钟源切换 */
    Sysctrl_SysClkSwitch(pstcCfg->enClkSrc);

    /* 时钟分频设置 */
    Sysctrl_SetHCLKDiv(pstcCfg->enHClkDiv);
    Sysctrl_SetPCLKDiv(pstcCfg->enPClkDiv);

    return enRet;
}

/**
 * @brief 时钟去初始化函数
 * @param [in]  None
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_ClkDeInit(void)
{
    en_result_t enRet = Ok;

    /* 配置RCH为内部4Hz */
    Sysctrl_SetRCHTrim(SysctrlRchFreq4MHz);

    /* 时钟源使能 */
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);

    /* 时钟源切换 */
    Sysctrl_SysClkSwitch(SysctrlClkRCH);

    /* 其它时钟源使能关闭 */
    Sysctrl_ClkSourceEnable(SysctrlClkXTH, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, FALSE);
    Sysctrl_ClkSourceEnable(SysctrlClkXTL, FALSE);

    /* 时钟分频设置 */
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);

    return enRet;
}


/**
 * @brief 内部低速时钟频率TRIM值加载
 * @param [in]  enRCLFreq  设定的RCL目标频率值 @ref en_sysctrl_rcl_freq_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq)
{
    M0P_SYSCTRL->RCL_CR  = *(RC_TRIM_BASE_ADDR + enRCLFreq);

    return Ok;
}


/**
 * @brief 外部低速时钟稳定周期配置
 * @param [in]  enCycle     外部低速时钟稳定周期设置 @ref en_sysctrl_xtl_cycle_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetXTLStableTime(en_sysctrl_xtl_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    M0P_SYSCTRL->XTL_CR_f.STARTUP = enCycle;
    return enRet;
}

/**
 * @brief 外部低速晶振驱动配置
 * @param [in]  enAmp     外部低速晶振幅选择 @ref en_sysctrl_xtl_amp_t
 * @param [in]  enDriver   外部低速晶振驱动能力选择 @ref en_sysctrl_xtal_driver_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_XTLDriverCfg(en_sysctrl_xtl_amp_t enAmp, en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;

    M0P_SYSCTRL->XTL_CR_f.AMP_SEL = enAmp;
    M0P_SYSCTRL->XTL_CR_f.DRIVER  = enDriver;

    return enRet;
}

/**
 * @brief 内部高速时钟RCH频率TRIM值加载
 * @param [in]  enRCHFreq  设定的RCH目标频率值 @ref en_sysctrl_rch_freq_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq)
{
    /* 加载RCH Trim值 */
    M0P_SYSCTRL->RCH_CR = *(RCH_TRIM_BASE_ADDR - enRCHFreq);

    return Ok;
}

/**
 * @brief 外部高速时钟稳定周期配置
 * @param [in]  enCycle     外部高速时钟稳定周期设置 @ref en_sysctrl_xth_cycle_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle)
{
    en_result_t enRet = Ok;
    M0P_SYSCTRL->XTH_CR_f.STARTUP = enCycle;
    return enRet;
}

/**
 * @brief 外部高速晶振驱动配置
 * @param [in]  enDriver   外部高速晶振驱动能力选择 @ref en_sysctrl_xtal_driver_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_XTHDriverCfg(en_sysctrl_xtal_driver_t enDriver)
{
    en_result_t enRet = Ok;

    M0P_SYSCTRL->XTH_CR_f.DRIVER   = enDriver;

    return enRet;
}

/**
 * @brief 外部高速时钟频率范围设定
 * @param [in]  enXTHFreq  设定的频率值
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq)
{
    en_result_t enRet = Ok;

    M0P_SYSCTRL->XTH_CR_f.XTH_FSEL = enXTHFreq;

    return enRet;
}

/**
 * @brief 系统时钟（HCLK）分频设定
 * @param [in]  enHCLKDiv  分频设定值 @ref en_sysctrl_hclk_div_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv)
{
    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.HCLK_PRS = enHCLKDiv;

    return Ok;
}

/**
 * @brief 外设时钟（PCLK）分频设定
 * @param [in]  enPCLKDiv  分频设定值
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv)
{
    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.PCLK_PRS = enPCLKDiv;

    return Ok;
}

/**
 * @brief 设置外设时钟门控开关
 * @param [in]  enPeripheral   目标外设 @ref en_sysctrl_peripheral_gate_t
 * @param [in]  bFlag          使能开关
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag)
{
    if (enPeripheral & 0x20u)
    {
        enPeripheral &= ~0x20u;
        SetBit((uint32_t)(&(M0P_SYSCTRL->PERI_CLKEN1)), enPeripheral, bFlag);
    }
    else
    {
        SetBit((uint32_t)(&(M0P_SYSCTRL->PERI_CLKEN0)), enPeripheral, bFlag);
    }

    return Ok;
}

/**
 * @brief 获得外设时钟门控开关状态
 * @param [in]  enPeripheral   目标外设 @ref en_sysctrl_peripheral_gate_t
 * @retval boolean_t
 *         - TRUE: 开
 *         - FALSE: 关
 */
boolean_t Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral)
{
    if (enPeripheral & 0x20u)
    {
        enPeripheral &= ~0x20u;
        return GetBit((uint32_t)(&(M0P_SYSCTRL->PERI_CLKEN1)), enPeripheral);
    }
    else
    {
        return GetBit((uint32_t)(&(M0P_SYSCTRL->PERI_CLKEN0)), enPeripheral);
    }

}

/**
 * @brief 系统功能设定
 * @param [in]  enFunc     系统功能枚举类型 @ref en_sysctrl_func_t
 * @param [in]  bFlag      TRUE: 使能 / FALSE: 关闭
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag)
{
    _SysctrlUnlock();
    SetBit((uint32_t)(&(M0P_SYSCTRL->SYSCTRL1)), enFunc, bFlag);

    return Ok;
}

/**
 * @brief 设定Deepsleep唤醒后系统时钟来源
 * @param [in]  bFlag   TRUE: 唤醒后系统时钟为RCH 
 *                      FALSE: 唤醒后不改变系统时钟来源，为进入Deepsleep之前的时钟源
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_SetWakeupByRch(boolean_t bFlag)
{
    _SysctrlUnlock();
    M0P_SYSCTRL->SYSCTRL0_f.WAKEUP_BYRCH = bFlag;

    return Ok;
}


/**
 * @brief 设定XTH 失效检测功能
 * @param [in]    pstcCfg    XTH失效检测配置结构体指针 @ref stc_sysctrl_xth_det_cfg_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_XthFaultDetectCfg(stc_sysctrl_xth_det_cfg_t *pstcCfg)
{
    en_result_t enRet = Ok;
    
    if(1u == M0P_SYSCTRL->XTH_CR_f.STABLE)
    {
        M0P_SYSCTRL->XTH_CR_f.DETEN = pstcCfg->bFaultDetectEn;
        M0P_SYSCTRL->XTH_CR_f.DETIE = pstcCfg->bFaultDetectIntEn;
    }
    else
    {
        enRet = Error;
    }
    
    return enRet;
}

/**
 * @brief 获得XTH 失效检测中断状态
 * @param [in]  None
 * @retval      XTH 失效检测中断状态
 */
boolean_t Sysctrl_GetXthFaultStatus(void)
{
    return GetBit((uint32_t)&M0P_SYSCTRL->XTH_CR, 10u);
}

/**
 * @brief 清除XTH 失效检测中断状态
 * @param [in]  None
 * @retval      None
 */
void Sysctrl_ClrXthFaultStatus(void)
{
    M0P_SYSCTRL->XTH_CR_f.FAULT_STATE = 0u;
}

/**
 * @brief 设定XTL 失效检测功能
 * @param [in]    pstcCfg    XTH失效检测配置结构体指针 @ref stc_sysctrl_xth_det_cfg_t
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 */
en_result_t Sysctrl_XtlFaultDetectCfg(stc_sysctrl_xtl_det_cfg_t *pstcCfg)
{
    en_result_t enRet = Ok;
    
    if(1u == M0P_SYSCTRL->XTL_CR_f.STABLE)
    {
        M0P_SYSCTRL->XTL_CR_f.DETEN   = pstcCfg->bFaultDetectEn;
        M0P_SYSCTRL->XTL_CR_f.DETIE   = pstcCfg->bFaultDetectIntEn;
        M0P_SYSCTRL->XTL_CR_f.DETTIME = pstcCfg->enFaultDetTime;
        _SysctrlUnlock();
        M0P_SYSCTRL->SYSCTRL1_f.CLK_FAULT_EN = 1u;
    }
    else
    {
        enRet = Error;
    }
    
    return enRet;
}

/**
 * @brief 获得XTL 失效检测中断状态
 * @param [in]  None
 * @retval      XTL 失效检测中断状态
 */
boolean_t Sysctrl_GetXtlFaultStatus(void)
{
    return GetBit((uint32_t)&M0P_SYSCTRL->XTL_CR, 10u);
}

/**
 * @brief 清除XTL 失效检测中断状态
 * @param [in]  None
 * @retval      None
 */
void Sysctrl_ClrXtlFaultStatus(void)
{
    M0P_SYSCTRL->XTL_CR_f.FAULT_STATE = 0u;
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
