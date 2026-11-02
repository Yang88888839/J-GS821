/**
 ******************************************************************************
 * @file  crc.h
 * @brief This file contains all the functions prototypes of the CRC driver
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

#ifndef __CRC_H__
#define __CRC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "sysctrl.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_CRC CRC模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CRC_Global_Types CRC全局类型定义
 * @{
 */
 
/**
 * @brief CRC CRC16算法选择类型定义
 */
typedef enum
{
    Crc16ModeX25        = 0x00u,    /*!< CRC16 X25 算法 */
    Crc16ModeCCITT      = 0x01u,    /*!< CRC16 CCITT 算法 */
    Crc16ModeCCITTFALSE = 0x02u,    /*!< CRC16 CCITT FALSE算法 */
    Crc16ModeXMODEM     = 0x03u,    /*!< CRC16 XMODEM 算法 */
} en_crc_16_sel_t;


/**
 * @brief CRC CRC32算法选择类型定义
 */
typedef enum
{
    Crc32Mode32        = 0x00u,    /*!< CRC32算法*/
    Crc32ModeMPEG2     = 0x01u,    /*!< CRC32MPEG2算法 */
} en_crc_32_sel_t;

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
 * @addtogroup CRC_Global_Functions CRC全局函数定义
 * @{
 */
/* CRC16 初始化 */
en_result_t CRC16_Cfg(en_crc_16_sel_t enCrc16Sel);
/* CRC16 编码值获取 */
uint16_t CRC16_Get8(uint8_t *pu8Data, uint32_t u32Len);
uint16_t CRC16_Get16(uint16_t *pu16Data, uint32_t u32Len);
uint16_t CRC16_Get32(uint32_t *pu32Data, uint32_t u32Len);
/* CRC16 校验 */
en_result_t CRC16_Check8(uint8_t *pu8Data, uint32_t u32Len, uint16_t u16CRC);
en_result_t CRC16_Check16(uint16_t *pu16Data, uint32_t u32Len, uint16_t u16CRC);
en_result_t CRC16_Check32(uint32_t *pu32Data, uint32_t u32Len, uint16_t u16CRC);

/* CRC32 初始化 */
en_result_t CRC32_Cfg(en_crc_32_sel_t enCrc32Sel);
/* CRC32 编码值获取 */
uint32_t CRC32_Get8(uint8_t *pu8Data, uint32_t u32Len);
uint32_t CRC32_Get16(uint16_t *pu16Data, uint32_t u32Len);
uint32_t CRC32_Get32(uint32_t *pu32Data, uint32_t u32Len);
/* CRC32 校验 */
en_result_t CRC32_Check8(uint8_t *pu8Data, uint32_t u32Len, uint32_t u32CRC);
en_result_t CRC32_Check16(uint16_t *pu16Data, uint32_t u32Len, uint32_t u32CRC);
en_result_t CRC32_Check32(uint32_t *pu32Data, uint32_t u32Len, uint32_t u32CRC);

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

#endif /* __CRC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

