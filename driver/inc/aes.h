/**
 ******************************************************************************
 * @file  aes.h
 * @brief This file contains all the functions prototypes of the AES driver
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

#ifndef __AES_H__
#define __AES_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_AES AES模块驱动库
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup AES_Global_Types AES全局类型定义
 * @{
 */

/**
 * @brief AES密钥长度类型定义
 */
typedef enum
{
    AesKey128 = 0u,               /*!< 128 bits */
    AesKey192 = 1u,               /*!< 192 bits */
    AesKey256 = 2u,               /*!< 256 bits */
} en_aes_key_type_t;

/**
 * @brief AES配置结构体
 */
typedef struct
{
    uint32_t           *pu32Cipher;           /*!< AES 密文指针 */
    uint32_t           *pu32Plaintext;        /*!< AES 明文指针 */
    uint32_t           *pu32Key;              /*!< AES 密钥指针 */
    en_aes_key_type_t   enKeyLen;             /*!< AES 密钥长度类型 */
} stc_aes_cfg_t;

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
 * @addtogroup AES_Global_Functions AES全局函数定义
 * @{
 */
/* AES加密 */
en_result_t AES_Encrypt(stc_aes_cfg_t *pstcAesCfg);
/* AES解密 */
en_result_t AES_Decrypt(stc_aes_cfg_t *pstcAesCfg);

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

#endif /* __AES_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

