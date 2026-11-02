/**
 *******************************************************************************
 * @file  crc.c
 * @brief This file provides - functions to manage the CRC.
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
#include "crc.h"


/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_CRC CRC模块驱动库
 * @brief CRC Driver Library CRC模块驱动库
 * @{
 */

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
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
 * @defgroup CRC_Global_Functions CRC全局函数定义
 * @{
 */

/**
 *****************************************************************************
 * @brief CRC16 初始化配置.
 * @param [in]  enCrc16Sel    CRC16算法选择
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 *****************************************************************************/
en_result_t CRC16_Cfg(en_crc_16_sel_t enCrc16Sel)
{
    en_result_t enRet = Ok;
    
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->CR_f.SEL = enCrc16Sel;
    
    if((Crc16ModeX25 == enCrc16Sel) || (Crc16ModeCCITTFALSE == enCrc16Sel))
    {
        M0P_CRC->RESULT = 0xFFFFu;
    }
    else
    {
        M0P_CRC->RESULT = 0u;
    }

    return (enRet);
}

/**
 *****************************************************************************
 * @brief CRC16 编码(字节填充方式), 该函数主要用于生成CRC16编码.
 * @param [in]  pu8Data          待编码数据指针（字节方式输入）
 * @param [in]  u32Len           待编码数据长度（字节数）
 * @retval CRC16                 CRC16编码值.
 *****************************************************************************/
uint16_t CRC16_Get8(uint8_t *pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t *)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 * @brief CRC16 编码(半字填充方式), 该函数主要用于生成CRC16编码.
 * @param [in]  pu16Data          待编码数据指针（半字方式输入）
 * @param [in]  u32Len            待编码数据长度（半字数）
 * @retval CRC16                  CRC16编码值.
 *****************************************************************************/
uint16_t CRC16_Get16(uint16_t *pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 * @brief CRC16 编码(字填充方式), 该函数主要用于生成CRC16编码.
 * @param [in]  pu32Data          待编码数据指针（字方式输入）
 * @param [in]  u32Len            待编码数据长度（字数）
 * @retval CRC16                  CRC16编码值.
 *****************************************************************************/
uint16_t CRC16_Get32(uint32_t *pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 * @brief CRC16 校验(字节填充方式), 该函数主要用于对数据及CRC16值进行校验.
 * @param [in]  pu8Data          待校验数据指针（字节方式输入）
 * @param [in]  u32Len           待校验数据长度（字节数）
 * @param [in]  u16CRC           待校验CRC16值
 * @retval  enResult
 *          - Ok                    CRC校验正确
 *          - Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC16_Check8(uint8_t *pu8Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t *)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }
    if((Crc16ModeCCITTFALSE == M0P_CRC->CR_f.SEL) || (Crc16ModeXMODEM == M0P_CRC->CR_f.SEL))   //CCITTFALSE or XMODE
    { 
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = (uint16_t)((((uint32_t)u16CRC & 0x00FF) << 8u) + (((uint32_t)u16CRC >> 8u) &0x00FFu));
    }
    else
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = u16CRC;
    }
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;

    return (enResult);
}

/**
 *****************************************************************************
 * @brief CRC16 校验(半字填充方式), 该函数主要用于对数据及CRC16值进行校验.
 * @param [in]  pu16Data         待校验数据指针（半字方式输入）
 * @param [in]  u32Len           待校验数据长度（半字数）
 * @param [in]  u16CRC           待校验CRC16值
 * @retval  enResult
 *          - Ok                    CRC校验正确
 *          - Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC16_Check16(uint16_t *pu16Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
    
    if((Crc16ModeCCITTFALSE == M0P_CRC->CR_f.SEL) || (Crc16ModeXMODEM == M0P_CRC->CR_f.SEL))   //CCITTFALSE or XMODE
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = (uint16_t)((((uint32_t)u16CRC & 0x00FF) << 8u) + (((uint32_t)u16CRC >> 8u) &0x00FFu));
    }
    else
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = u16CRC;
    }
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;

    return (enResult);
}

/**
 *****************************************************************************
 * @brief CRC16 校验(字填充方式), 该函数主要用于对数据及CRC16值进行校验.
 * @param [in]  pu32Data         待校验数据指针（字方式输入）
 * @param [in]  u32Len           待校验数据长度（字数）
 * @param [in]  u16CRC           待校验CRC16值
 * @retval  enResult
 *          - Ok                    CRC校验正确
 *          - Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC16_Check32(uint32_t *pu32Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint32_t *)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }
    
    if((Crc16ModeCCITTFALSE == M0P_CRC->CR_f.SEL) || (Crc16ModeXMODEM == M0P_CRC->CR_f.SEL))   //CCITTFALSE or XMODE
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = (uint16_t)((((uint32_t)u16CRC & 0x00FF) << 8u) + (((uint32_t)u16CRC >> 8u) &0x00FFu));
    }
    else
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = ((uint16_t)u16CRC);
    }
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;

    return (enResult);
}

/**
 *****************************************************************************
 * @brief CRC32 初始化配置.
 * @param [in]  enCrc32Sel    CRC32算法选择
 * @retval      en_result_t
 *              - Ok         设定成功
 *              - 其他       设定失败
 *****************************************************************************/
en_result_t CRC32_Cfg(en_crc_32_sel_t enCrc32Sel)
{
    en_result_t enRet = Ok;
    
    M0P_CRC->CR_f.CR = 1;
    M0P_CRC->CR_f.SEL = enCrc32Sel;
    
    M0P_CRC->RESULT = 0xFFFFFFFFu;

    return (enRet);
}

/**
 *****************************************************************************
 * @brief CRC32 编码(字节填充方式), 该函数主要用于生成CRC32编码.
 * @param [in]  pu8Data          待编码数据指针（字节方式输入）
 * @param [in]  u32Len           待编码数据长度（字节数）
 * @retval CRC32                 CRC32编码值.
 *****************************************************************************/
uint32_t CRC32_Get8(uint8_t *pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t *)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 * @brief CRC32 编码(半字填充方式), 该函数主要用于生成CRC32编码.
 * @param [in]  pu16Data          待编码数据指针（半字方式输入）
 * @param [in]  u32Len            待编码数据长度（半字数）
 * @retval CRC32                  CRC32编码值.
 *****************************************************************************/
uint32_t CRC32_Get16(uint16_t *pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 * @brief CRC32编码(字填充方式), 该函数主要用于生成CRC32编码.
 * @param [in]  pu32Data          待编码数据指针（字方式输入）
 * @param [in]  u32Len            待编码数据长度（字数）
 * @retval CRC32                  CRC32编码值.
 *****************************************************************************/
uint32_t CRC32_Get32(uint32_t *pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 * @brief CRC32 校验(字节填充方式), 该函数主要用于对数据及CRC32值进行校验.
 * @param [in]  pu8Data          待校验数据指针（字节方式输入）
 * @param [in]  u32Len           待校验数据长度（字节数）
 * @param [in]  u32CRC           待校验CRC32值
 * @retval  enResult
 *          - Ok                    CRC校验正确
 *          - Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC32_Check8(uint8_t *pu8Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint8_t *)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }

    if(Crc32ModeMPEG2 == M0P_CRC->CR_f.SEL)   //CRC32-MPEG-2
    {
        *((volatile uint32_t *)(&(M0P_CRC->DATA))) = (uint32_t)(((u32CRC << 24u) & 0xFF000000u) + ((u32CRC << 8u) & 0x00FF0000u) + ((u32CRC >> 8u) & 0x0000FF00u) + ((u32CRC >> 24u) & 0x000000FFu));
    }
    else
    {
        *((volatile uint32_t *)(&(M0P_CRC->DATA))) = u32CRC;
    }
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;

    return (enResult);
}

/**
 *****************************************************************************
 * @brief CRC32 校验(半字填充方式), 该函数主要用于对数据及CRC32值进行校验.
 * @param [in]  pu16Data         待校验数据指针（半字方式输入）
 * @param [in]  u32Len           待校验数据长度（半字数）
 * @param [in]  u32CRC           待校验CRC32值
 * @retval  enResult
 *          - Ok                    CRC校验正确
 *          - Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC32_Check16(uint16_t *pu16Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint16_t *)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }

    if(Crc32ModeMPEG2 == M0P_CRC->CR_f.SEL)   //CRC32-MPEG-2
    { 
        *((volatile uint32_t *)(&(M0P_CRC->DATA))) = (uint32_t)(((u32CRC << 24u) & 0xFF000000u) + ((u32CRC << 8u) & 0x00FF0000u) + ((u32CRC >> 8u) & 0x0000FF00u) + ((u32CRC >> 24u) & 0x000000FFu));
    }
    else
    {
        *((volatile uint32_t *)(&(M0P_CRC->DATA))) = u32CRC;
    }

    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;

    return (enResult);
}

/**
 *****************************************************************************
 * @brief CRC32 校验(字填充方式), 该函数主要用于对数据及CRC32值进行校验.
 * @param [in]  pu32Data         待校验数据指针（字方式输入）
 * @param [in]  u32Len           待校验数据长度（字数）
 * @param [in]  u32CRC           待校验CRC32值
 * @retval  enResult
 *          - Ok                    CRC校验正确
 *          - Error                 CRC校验错误
 *****************************************************************************/
en_result_t CRC32_Check32(uint32_t *pu32Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    for (u32Index = 0; u32Index < u32Len; u32Index++)
    {
        *((volatile uint32_t *)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }

    if(Crc32ModeMPEG2 == M0P_CRC->CR_f.SEL)   //CRC32-MPEG-2
    { 
        *((volatile uint32_t *)(&(M0P_CRC->DATA))) = (uint32_t)(((u32CRC << 24u) & 0xFF000000u) + ((u32CRC << 8u) & 0x00FF0000u) + ((u32CRC >> 8u) & 0x0000FF00u) + ((u32CRC >> 24u) & 0x000000FFu));
    }
    else
    {
        *((volatile uint32_t *)(&(M0P_CRC->DATA))) = u32CRC;
    }

    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;

    return (enResult);
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
