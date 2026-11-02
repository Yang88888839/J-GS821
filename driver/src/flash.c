/**
 *******************************************************************************
 * @file  flash.c
 * @brief This file provides - functions to manage the FLASH.
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
#include "flash.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_FLASH FLASH模块驱动库
 * @brief FLASH Driver Library FLASH模块驱动库
 * @{
 */


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FLASH_Local_Macros FLASH局部宏定义
 * @{
 */
/**
 * @defgroup FLASH (KEIL)连续编程和片擦函数使能设置(特定例程（连续编程和片擦除例程使用）
 * @{
 */
#define USED           1u
#define UNUSED         0u

#define CONT_WRITE     UNUSED

#define CHIP_ERASE     UNUSED

/**
 * @}
 */
 
/**
 * @defgroup FLASH_Value_Define FLASH模式值设置
 * @{
 */

#define FLASH_END_ADDR              (0x0001FFFFu)
#define FLASH_BYPASS()              do{ M0P_FLASH->BYPASS = 0x5A5A;\
                                        M0P_FLASH->BYPASS = 0xA5A5;\
                                    }while(0);

#define FLASH_TIMEOUT_INIT          (0xFFFFu)
#define FLASH_TIMEOUT_PGM           (0xFFFFFFu)
#define FLASH_TIMEOUT_ERASE         (0xFFFFFFu)

#define FLASH_LOCK_ALL              (0u)
#define FLASH_UNLOCK_ALL            (0xFFFFFFFFu)


/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

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
 * @defgroup FLASH_Global_Functions FLASH全局函数定义
 * @{
 */



/**
 * @brief  Flash中断标志获取
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t
 * @retval boolean_t:
 *              - TRUE: 标志置位
 *              - FALSE: 标志未置位
 */
boolean_t Flash_GetIntFlag(en_flash_int_type_t enFlashIntType)
{
    boolean_t bRetVal = FALSE;

    if (M0P_FLASH->IFR & enFlashIntType)
    {
        bRetVal =  TRUE;
    }

    return bRetVal;
}


/**
 * @brief  Flash中断标志清除
 * @param  [in] enFlashIntType: Flash 中断类型枚举  @ref en_flash_int_type_t
 * @retval en_result_t:
 *              - Ok: 标志置位
 *              - Error: 标志未置位
 */
en_result_t Flash_ClearIntFlag(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    M0P_FLASH->ICLR &= ~(uint32_t)enFlashIntType;
    enResult = Ok;

    return enResult;
}


/**
 * @brief  Flash中断使能
 * @param  [in] enFlashIntType: Flash Flash中断类型  @ref en_flash_int_type_t
 * @retval en_result_t:
 *              - Ok: 标志置位
 *              - Error: 标志未置位
 */
en_result_t Flash_EnableIrq(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.IE |= enFlashIntType;

    enResult = Ok;

    return enResult;
}


/**
 * @brief  Flash中断禁止
 * @param  [in] enFlashIntType: Flash Flash中断类型  @ref en_flash_int_type_t
 * @retval en_result_t:
 *              - Ok: 禁止成功
 *              - Error: 禁止失败
 */
en_result_t Flash_DisableIrq(en_flash_int_type_t enFlashIntType)
{
    en_result_t enResult = Error;

    FLASH_BYPASS();
    M0P_FLASH->CR_f.IE &= ~(uint32_t)enFlashIntType;

    enResult = Ok;

    return enResult;
}

/**
 * @brief  FLASH 初始化函数——低功耗模式

 * @param  [in] bDpstbEn: 低功耗模式使能位:
 *              - TRUE   : 当系统进入DeepSleep模式，FLASH进入低功耗模式;
 *              - FALSE  : 当系统进入DeepSleep模式，FLASH不进入低功耗模式;
 * @retval en_result_t:
 *              - Ok                    :操作成功.
 *              - ErrorInvalidParameter :参数无效.
 *              - ErrorUninitialized    :初始化失败
 */
en_result_t Flash_Init(uint8_t u8FreqCfg, boolean_t bDpstbEn)
{
    en_result_t             enResult  = Ok;
    volatile uint32_t       u32TimeOut;
    
    u32TimeOut = FLASH_TIMEOUT_INIT;
    while (bDpstbEn != M0P_FLASH->CR_f.DPSTB_EN)
    {
        FLASH_BYPASS();
        M0P_FLASH->CR_f.DPSTB_EN = bDpstbEn;

        if (0u == u32TimeOut--)
        {
            return ErrorUninitialized;
        }
    }

    return (enResult);
}


/**
 * @brief  Flash 字节编程,以字节方式向FLASH写入连续的数据
 * @param  [in] u32Addr: Flash目标首地址
 * @param  [in] pu8Data: 数据Buffer首地址
 * @param  [in] u32Len: 写入数据长度
 * @retval en_result_t:
 *              - Ok:                    写入成功.
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout:          操作超时
 *              - Error:                 编程、校验失败
 *              - ErrorInvalidMode:      操作模式无效
 */
en_result_t Flash_Write8(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0;

    if (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1))
    {
        return ErrorInvalidParameter;
    }

    /* busy */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t *)u32Addr) = pu8Data[u32Index];

        /* busy */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        if (pu8Data[u32Index] != *((volatile uint8_t *)u32Addr))
        {
            return Error;
        }
        u32Addr++;
    }

    return (enResult);
}


/**
 * @brief  Flash 半字（16位方式）编程,以半字方式向FLASH写入连续的数据
 * @param  [in] u32Addr: Flash目标首地址
 * @param  [in] pu16Data: 数据Buffer首地址
 * @param  [in] u32Len: 写入数据长度
 * @retval en_result_t:
 *              - Ok:                    写入成功.
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout:          操作超时
 *              - Error:                 编程、校验失败
 *              - ErrorInvalidMode:      操作模式无效
 */
en_result_t Flash_Write16(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0;

    if (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len << 1u) - 1))
    {
        return ErrorInvalidParameter;
    }

    /* busy */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint16_t *)u32Addr) = pu16Data[u32Index];

        /* busy */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        if (pu16Data[u32Index] != *((volatile uint16_t *)u32Addr))
        {
            return Error;
        }
        u32Addr += 2u;
    }

    return (enResult);
}


/**
 * @brief  Flash 字（32位方式）编程,以字方式向FLASH写入连续的数据
 * @param  [in] u32Addr: Flash目标首地址
 * @param  [in] pu32Data: 数据Buffer首地址
 * @param  [in] u32Len: 写入数据长度
 * @retval en_result_t:
 *              - Ok:                    写入成功.
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout:          操作超时
 *              - Error:                 编程、校验失败
 *              - ErrorInvalidMode:      操作模式无效
 */
en_result_t Flash_Write32(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_PGM;
    uint32_t                u32Index = 0;

    if (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len << 2u) - 1))
    {
        return ErrorInvalidParameter;
    }

    /* busy */
    u32TimeOut = FLASH_TIMEOUT_PGM;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint32_t *)u32Addr) = pu32Data[u32Index];

        /* busy */
        u32TimeOut = FLASH_TIMEOUT_PGM;
        while (TRUE == M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        if (pu32Data[u32Index] != *((volatile uint32_t *)u32Addr))
        {
            return Error;
        }
        u32Addr += 4u;
    }

    return (enResult);
}

/**
 * @brief  Flash 扇区擦除,对目标地址所在的FLASH 扇区进行擦除，擦除后该扇区FLASH数据为全0xFF
 * @param  [in] u32SectorAddr: 所擦除扇区内的地址
 * @retval en_result_t:
 *              - Ok:                    擦除成功.
 *              - ErrorInvalidParameter: FLASH地址无效
 *              - ErrorTimeout:          操作超时
 *              - ErrorInvalidMode:      操作模式无效
 */
en_result_t Flash_SectorErase(uint32_t u32SectorAddr)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = FLASH_TIMEOUT_ERASE;

    if (FlashSectorEraseMode != M0P_FLASH->CR_f.OP)
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < u32SectorAddr)
    {
        return ErrorInvalidParameter;
    }

    /* busy */
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data */
    *((volatile uint8_t *)u32SectorAddr) = 0;

    /* busy */
    u32TimeOut = FLASH_TIMEOUT_ERASE;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}


/**
 * @brief  FLASH 操作模式配置
 * @param  [in] enFlashOpMode: 操作模式配置  @ref en_flash_op_mode_t
 * @retval en_result_t:
 *              - Ok:                    配置成功
 *              - Error:                 配置失败
 */
en_result_t Flash_OpModeConfig(en_flash_op_mode_t enFlashOpMode)
{
    en_result_t          enResult = Ok;
    volatile uint32_t    u32TimeOut;
    
    if (enFlashOpMode != FlashContinueWriteMode)
    {
        u32TimeOut = FLASH_TIMEOUT_INIT;
        while (enFlashOpMode != M0P_FLASH->CR_f.OP)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = enFlashOpMode;

            if (0u == u32TimeOut--)
            {
                return ErrorUninitialized;
            }
        }
    }
    else
    {        
        u32TimeOut = FLASH_TIMEOUT_INIT;
        while (FlashReadMode != M0P_FLASH->CR_f.OP)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.OP = FlashReadMode;

            if (0u == u32TimeOut--)
            {
                return ErrorUninitialized;
            }
        }
        
        u32TimeOut = FLASH_TIMEOUT_INIT;
        while (TRUE != M0P_FLASH->CR_f.CONTP)
        {
            FLASH_BYPASS();
            M0P_FLASH->CR_f.CONTP = TRUE;

            if (0u == u32TimeOut--)
            {
                return ErrorUninitialized;
            }
        }
    }

    return enResult;
}


/**
 * @brief  FLASH 读等待周期设置
 * @param  [in] enWaitCycle: 插入FLASH读等待周期数枚举类型  @ref en_flash_waitcycle_t
 * @retval en_result_t:
 *              - Ok:                    配置成功
 *              - Error:                 配置失败
 */
en_result_t Flash_WaitCycle(en_flash_waitcycle_t enWaitCycle)
{
    en_result_t          enResult = Ok;
    volatile uint32_t    u32TimeOut;
    
    u32TimeOut = FLASH_TIMEOUT_INIT;
    while (enWaitCycle != M0P_FLASH->CR_f.WAIT)
    {
        FLASH_BYPASS();
        M0P_FLASH->CR_f.WAIT = enWaitCycle;

        if (0u == u32TimeOut--)
        {
            return ErrorUninitialized;
        }
    }

    return enResult;
}

/**
 * @brief  Flash 功能配置:该函数用于配置低功耗模式和只读模式
 * @param  [in] enFunc: 低功耗模式或只读模式枚举定义;
 * @param  [in] bFlag:  低功耗使能位;
 *                - TRUE:模式使能;
*                 - FALSE:模式不使能;
 * @retval en_result_t:
 *              - Ok:                    操作成功.
 *              - ErrorInvalidParameter: 参数无效
 *              - ErrorUninitialized:    初始化失败
 */

en_result_t Flash_FuncSet(en_flash_func_type_t enFunc, boolean_t bFlag)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut;

    u32TimeOut = FLASH_TIMEOUT_INIT;
    
    while (bFlag != GetBit((uint32_t)&M0P_FLASH->CR, enFunc))
    {
        FLASH_BYPASS();
        SetBit((uint32_t)&M0P_FLASH->CR, enFunc, bFlag);

        if (0u == u32TimeOut--)
        {
            return ErrorUninitialized;
        }
    }

    return (enResult);
}


/**
 * @brief  FLASH 编程保护加锁
 * @retval en_result_t:
 *              - Ok:    加锁成功.
 *              - Error: 加锁失败
 */
en_result_t Flash_LockAll(void)
{
    en_result_t enResult = Ok;
    volatile uint32_t       u32TimeOut;

    u32TimeOut = FLASH_TIMEOUT_INIT;
    while (FLASH_LOCK_ALL != M0P_FLASH->SLOCK0)
    {
        FLASH_BYPASS();
        M0P_FLASH->SLOCK0 = FLASH_LOCK_ALL;

        if (0u == u32TimeOut--)
        {
            return ErrorUninitialized;
        }
    }
    
    u32TimeOut = FLASH_TIMEOUT_INIT;
    while (FLASH_LOCK_ALL != M0P_FLASH->SLOCK1)
    {
        FLASH_BYPASS();
        M0P_FLASH->SLOCK1 = FLASH_LOCK_ALL;

        if (0u == u32TimeOut--)
        {
            return ErrorUninitialized;
        }
    }
    
    return enResult;
}

/**
 * @brief  FLASH 编程保护解锁
 * @retval en_result_t:
 *              - Ok:    解锁成功.
 *              - Error: 解锁失败
 */
en_result_t Flash_UnlockAll(void)
{
    en_result_t enResult = Ok;
    volatile uint32_t       u32TimeOut;

    u32TimeOut = FLASH_TIMEOUT_INIT;
    while (FLASH_UNLOCK_ALL != M0P_FLASH->SLOCK0)
    {
        FLASH_BYPASS();
        M0P_FLASH->SLOCK0 = FLASH_UNLOCK_ALL;

        if (0u == u32TimeOut--)
        {
            return ErrorUninitialized;
        }
    }
    
    u32TimeOut = FLASH_TIMEOUT_INIT;
    while (FLASH_UNLOCK_ALL != M0P_FLASH->SLOCK1)
    {
        FLASH_BYPASS();
        M0P_FLASH->SLOCK1 = FLASH_UNLOCK_ALL;

        if (0u == u32TimeOut--)
        {
            return ErrorUninitialized;
        }
    }

    return enResult;
}


/**
 * @brief  FLASH LOCK 设置
 * @param  [in] enLock: 加锁使能位             @ref en_flash_lock_t
 * @param  [in] u32LockValue 32bits，对应bit=0:加锁，对应Sector不允许擦写；对应bit=1:解锁。
 * @note   加解锁范围Sector:[enLock*128 + i*4, enLock*128 + i*4+3]
 *         -i: 表示u32LockValue的bit位置，0~31;
 *         -enLock: 表示枚举编号(FlashLock[n]:n=0~3),并非枚举值;)
 *         例如:enLock = FlashLock1, u32LockValue = 0x00000005,
 *         则FLASH解锁范围为:[Sector128,Sector131]和[Sector136,Sector139]
 * @retval en_result_t:
 *              - Ok:    解锁成功.
 *              - Error: 解锁失败
 */

en_result_t Flash_LockSet(en_flash_lock_t enLock, uint32_t u32LockValue)
{
    en_result_t enResult = Ok;
    volatile uint32_t       u32TimeOut;

    u32TimeOut = FLASH_TIMEOUT_INIT;
    while (u32LockValue != *((&M0P_FLASH->SLOCK0) + enLock))
    {
        FLASH_BYPASS();
        *((&M0P_FLASH->SLOCK0) + enLock) = u32LockValue;

        if (0u == u32TimeOut--)
        {
            return ErrorUninitialized;
        }
    }

    return enResult;
}


#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)

#if ((CONT_WRITE == USED) || (CHIP_ERASE == USED))

#pragma clang section text = "ramfunc"

/**
 * @brief   Flash 整片擦除
 * @note    该函数需要放到RAM中执行
 * @retval  en_result_t:
 *              - Ok: 执行成功
 *              - Error: 执行失败
*/
en_result_t Flash_Chip_Erase(void)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32TimeOut;

    u32TimeOut = 0xFFFFu;
    while (FlashChipEraseMode != M0P_FLASH->CR_f.OP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.OP = FlashChipEraseMode;

        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    u32TimeOut = 0xFFFFu;
    while (0xFFFFFFFFu != M0P_FLASH->SLOCK0)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->SLOCK0 = 0xFFFFFFFFu;

        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    u32TimeOut = 0xFFFFu;
    while (0xFFFFFFFFu != M0P_FLASH->SLOCK1)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->SLOCK1 = 0xFFFFFFFFu;

        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    *((volatile unsigned int *)0x00000000u) = 0u;

    u32TimeOut = 0xFFFFFFu;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}


/**
 * @brief  Flash字节连续写 用于向FLASH写入字节数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu8Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功.
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if ((FlashReadMode != M0P_FLASH->CR_f.OP) && (M0P_FLASH->CR_f.CONTP))
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        return ErrorInvalidParameter;
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t *)u32Addr) = pu8Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        u32Addr++;
    }

    u32TimeOut = 0xFFFFu;
    while (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.OP = FlashWriteMode;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    u32TimeOut = 0xFFFFu;
    while (M0P_FLASH->CR_f.CONTP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.CONTP = FALSE;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}

/**
 * @brief  Flash半字连续写 用于向FLASH写入半字数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu16Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if ((FlashReadMode != M0P_FLASH->CR_f.OP) && (M0P_FLASH->CR_f.CONTP))
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len << 1u)  - 1u))
    {
        return ErrorInvalidParameter;
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint16_t *)u32Addr) = pu16Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }
        u32Addr += 2u;
    }

    u32TimeOut = 0xFFFFu;
    while (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.OP = FlashWriteMode;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    u32TimeOut = 0xFFFFu;
    while (M0P_FLASH->CR_f.CONTP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.CONTP = FALSE;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}

/**
 * @brief  Flash字连续写 用于向FLASH写入字的数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu32Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if ((FlashReadMode != M0P_FLASH->CR_f.OP) && (M0P_FLASH->CR_f.CONTP))
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len << 2u) - 1u))
    {
        return ErrorInvalidParameter;
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint32_t *)u32Addr) = pu32Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr += 4u;
    }

    u32TimeOut = 0xFFFFu;
    while (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.OP = FlashWriteMode;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    u32TimeOut = 0xFFFFu;
    while (M0P_FLASH->CR_f.CONTP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.CONTP = FALSE;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}

#pragma clang section

#endif

#elif defined(__ICCARM__) || (defined (__GNUC__) && !defined (__CC_ARM))
__RAM_FUNC en_result_t Flash_Chip_Erase(void)
{
    en_result_t enResult = Ok;
    volatile uint32_t u32TimeOut;

    u32TimeOut = 0xFFFFu;
    while (FlashChipEraseMode != M0P_FLASH->CR_f.OP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.OP = FlashChipEraseMode;

        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    u32TimeOut = 0xFFFFu;
    while (0xFFFFFFFFu != M0P_FLASH->SLOCK0)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->SLOCK0 = 0xFFFFFFFFu;

        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    
    u32TimeOut = 0xFFFFu;
    while (0xFFFFFFFFu != M0P_FLASH->SLOCK1)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5A;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5;
        M0P_FLASH->SLOCK1 = 0xFFFFFFFFu;

        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    


    *((volatile unsigned int *)0x00000000) = 0;

    u32TimeOut = 0xFFFFFFu;
    while (TRUE == M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}

/**
 * @brief  Flash字节连续写 用于向FLASH写入字节数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu8Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功.
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__RAM_FUNC en_result_t Flash_ContWrite_Byte(uint32_t u32Addr, uint8_t pu8Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if ((FlashReadMode != M0P_FLASH->CR_f.OP) && (M0P_FLASH->CR_f.CONTP))
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + u32Len - 1u))
    {
        return ErrorInvalidParameter;
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t *)u32Addr) = pu8Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr++;
    }

    u32TimeOut = 0xFFFFu;
    while (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.OP = FlashWriteMode;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    u32TimeOut = 0xFFFFu;
    while (M0P_FLASH->CR_f.CONTP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.CONTP = FALSE;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}

/**
 * @brief  Flash半字连续写 用于向FLASH写入半字数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu16Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__RAM_FUNC en_result_t Flash_ContWrite_HalfWord(uint32_t u32Addr, uint16_t pu16Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if ((FlashReadMode != M0P_FLASH->CR_f.OP) && (M0P_FLASH->CR_f.CONTP))
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len << 1u) - 1u))
    {
        return ErrorInvalidParameter;
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint16_t *)u32Addr) = pu16Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr += 2u;
    }

    u32TimeOut = 0xFFFFu;
    while (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.OP = FlashWriteMode;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    u32TimeOut = 0xFFFFu;
    while (M0P_FLASH->CR_f.CONTP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.CONTP = FALSE;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    return (enResult);
}

/**
 * @brief  Flash字连续写 用于向FLASH写入字的数据
 * @param [in]  u32Addr:    Flash地址
 * @param [in]  pu32Data[]:  数据buf
 * @param [in]  u32Len:   buf长度
 * @retval en_result_t:
 *              - Ok: 写入成功
 *              - ErrorInvalidMode: 模式错误
 *              - ErrorTimeout: 操作超时
 */
__RAM_FUNC en_result_t Flash_ContWrite_Word(uint32_t u32Addr, uint32_t pu32Data[], uint32_t u32Len)
{
    en_result_t             enResult = Ok;
    volatile uint32_t       u32TimeOut = 0xFFFFFFu;
    uint32_t                u32Index = 0u;

    if ((FlashReadMode != M0P_FLASH->CR_f.OP) && (M0P_FLASH->CR_f.CONTP))
    {
        return ErrorInvalidMode;
    }

    if (FLASH_END_ADDR < (u32Addr + (u32Len << 2u) - 1u))
    {
        return ErrorInvalidParameter;
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }

    /* write data byte */
    for (u32Index = 0u; u32Index < u32Len; u32Index++)
    {
        *((volatile uint32_t *)u32Addr) = pu32Data[u32Index];
        /* busy? */
        u32TimeOut = 0xFFFFFFu;
        while (TRUE == M0P_FLASH->CR_f.BUSY)
        {
            if (0u == u32TimeOut--)
            {
                return ErrorTimeout;
            }
        }

        u32Addr += 4u;
    }

    u32TimeOut = 0xFFFFu;
    while (FlashWriteMode != M0P_FLASH->CR_f.OP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.OP = FlashWriteMode;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    u32TimeOut = 0xFFFFu;
    while (M0P_FLASH->CR_f.CONTP)
    {
        M0P_FLASH->BYPASS = (uint32_t)0x5A5Au;
        M0P_FLASH->BYPASS = (uint32_t)0xA5A5u;
        M0P_FLASH->CR_f.CONTP = FALSE;
        if (0u == u32TimeOut--)
        {
            enResult = ErrorTimeout;
            break;
        }
    }

    /* busy? */
    u32TimeOut = 0xFFFFFFu;
    while (M0P_FLASH->CR_f.BUSY)
    {
        if (0u == u32TimeOut--)
        {
            return ErrorTimeout;
        }
    }
    
    return (enResult);
}

#endif







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
