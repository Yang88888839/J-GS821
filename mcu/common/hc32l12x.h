/**
*******************************************************************************
** @file HC32L12X.h
** @brief Headerfile for HC32L12X series MCU
**
@verbatim
Change Logs:
Date             Author          Notes
2025-04-15       MADS            First version
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

#ifndef __HC32L12X_H__
#define __HC32L12X_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Configuration of the Cortex-M0P Processor and Core Peripherals
******************************************************************************/
#define __MPU_PRESENT           0 /* No MPU                                       */
#define __NVIC_PRIO_BITS        2 /* M0P uses 2 Bits for the Priority Levels      */
#define __Vendor_SysTickConfig  0 /* Set to 1 if different SysTick Config is used */

/******************************************************************************
* Interrupt Number Definition
******************************************************************************/
typedef enum IRQn
{
    NMI_IRQn            = -14, /*  2 Non Maskable                            */
    HardFault_IRQn      = -13, /*  3 Hard Fault                              */
    SVC_IRQn            = -5,  /* 11 SV Call                                 */
    PendSV_IRQn         = -2,  /* 14 Pend SV                                 */
    SysTick_IRQn        = -1,  /* 15 System Tick                             */
    
    PORTA_IRQn          = 0 ,
    PORTB_IRQn          = 1 ,
    PORTC_IRQn          = 2 ,
    PORTD_IRQn          = 3 ,
    DMAC_IRQn           = 4 ,
    TIM3_IRQn           = 5 ,
    USART0_IRQn         = 6 ,
    USART1_IRQn         = 7 ,
    LPUART0_IRQn        = 8 ,
    LPUART1_IRQn        = 9 ,
    SPI0_IRQn           = 10,
    SPI1_IRQn           = 11,
    I2C0_IRQn           = 12,
    I2C1_IRQn           = 13,
    TIM0_IRQn           = 14,
    TIM1_IRQn           = 15,
    TIM2_IRQn           = 16,
    LPTIM_0_1_IRQn      = 17,
    HSI2C_IRQn          = 18,
    LPUART2_IRQn        = 19,
    WWDT_IRQn           = 21,
    IWDT_IRQn           = 22,
    RTC_IRQn            = 23,
    ADC_IRQn            = 24,
    VC0_IRQn            = 26,
    VC1_IRQn            = 27,
    LVD_IRQn            = 28,
    LCD_IRQn            = 29,
    FLASH_RAM_IRQn      = 30,
    CTRIM_CLKDET_IRQn   = 31,
    
    
} IRQn_Type;


#include <core_cm0plus.h>
#include <stdint.h>

#define SUCCESS         (0)
#define ERROR           (-1)

#ifndef NULL
#define NULL            (0)
#endif


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

typedef struct
{
    __IO uint32_t BGR_EN                    : 1;
    __IO uint32_t TS_EN                     : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_adc_bgr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CLKDIV                    : 2;
    __IO uint32_t SGLMUX                    : 5;
    __IO uint32_t REF                       : 2;
    uint32_t RESERVED11                     : 4;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED16                     : 1;
    __IO uint32_t SAM                       : 4;
    uint32_t RESERVED21                     :10;
    __IO uint32_t RSV                       : 1;
} stc_adc_cr0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t THCH                      : 5;
    __IO uint32_t DMASQR                    : 1;
    __IO uint32_t DMAJQR                    : 1;
    __IO uint32_t MODE                      : 1;
    __IO uint32_t RACCEN                    : 1;
    __IO uint32_t LTCMP                     : 1;
    __IO uint32_t HTCMP                     : 1;
    __IO uint32_t REGCMP                    : 1;
    __IO uint32_t RACCCLR                   : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_adc_cr1_field_t;

typedef struct
{
    __IO uint32_t CH0MUX                    : 5;
    __IO uint32_t CH1MUX                    : 5;
    __IO uint32_t CH2MUX                    : 5;
    __IO uint32_t CH3MUX                    : 5;
    __IO uint32_t CH4MUX                    : 5;
    __IO uint32_t CH5MUX                    : 5;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqr0_field_t;

typedef struct
{
    __IO uint32_t CNT                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqr1_field_t;

typedef struct
{
    __IO uint32_t CH0MUX                    : 5;
    __IO uint32_t CH1MUX                    : 5;
    __IO uint32_t CH2MUX                    : 5;
    __IO uint32_t CH3MUX                    : 5;
    __IO uint32_t CNT                       : 2;
    uint32_t RESERVED22                     : 9;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqr_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult0_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult1_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult2_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult3_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult4_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrresult5_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrresult0_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrresult1_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrresult2_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrresult3_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_result_field_t;

typedef struct
{
    __IO uint32_t RESULTACC                 :20;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_adc_resultacc_field_t;

typedef struct
{
    __IO uint32_t HT                        :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_ht_field_t;

typedef struct
{
    __IO uint32_t LT                        :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_adc_lt_field_t;

typedef struct
{
    __IO uint32_t SGLIF                     : 1;
    __IO uint32_t LTIF                      : 1;
    __IO uint32_t HTIF                      : 1;
    __IO uint32_t REGIF                     : 1;
    __IO uint32_t SQRIF                     : 1;
    __IO uint32_t JQRIF                     : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_adc_ifr_field_t;

typedef struct
{
    __IO uint32_t SGLIC                     : 1;
    __IO uint32_t LTIC                      : 1;
    __IO uint32_t HTIC                      : 1;
    __IO uint32_t REGIC                     : 1;
    __IO uint32_t SQRIC                     : 1;
    __IO uint32_t JQRIC                     : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_adc_icr_field_t;

typedef struct
{
    __IO uint32_t EXTTRIGEN                 : 4;
    uint32_t RESERVED4                      :27;
    __IO uint32_t RSV                       : 1;
} stc_adc_exttrigger0_field_t;

typedef struct
{
    __IO uint32_t EXTTRIGEN                 : 4;
    uint32_t RESERVED4                      :27;
    __IO uint32_t RSV                       : 1;
} stc_adc_exttrigger1_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_sglstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_sqrstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_jqrstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_adc_allstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    __IO uint32_t MODE                      : 1;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t KEYSIZE                   : 2;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_aes_cr_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_aes_data0_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_aes_data1_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_aes_data2_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_aes_data3_field_t;

typedef struct
{
    __IO uint32_t KEY                       :32;
} stc_aes_key0_field_t;

typedef struct
{
    __IO uint32_t KEY                       :32;
} stc_aes_key1_field_t;

typedef struct
{
    __IO uint32_t KEY                       :32;
} stc_aes_key2_field_t;

typedef struct
{
    __IO uint32_t KEY                       :32;
} stc_aes_key3_field_t;

typedef struct
{
    __IO uint32_t KEY                       :32;
} stc_aes_key4_field_t;

typedef struct
{
    __IO uint32_t KEY                       :32;
} stc_aes_key5_field_t;

typedef struct
{
    __IO uint32_t KEY                       :32;
} stc_aes_key6_field_t;

typedef struct
{
    __IO uint32_t KEY                       :32;
} stc_aes_key7_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    __IO uint32_t MODE                      : 1;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t KEYSIZE                   : 2;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_aes_crdm_field_t;

typedef struct
{
    __IO uint32_t CR                        : 1;
    __IO uint32_t FLAG                      : 1;
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_crc_cr_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :32;
} stc_crc_result_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_crc_data_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cnt_field_t;

typedef struct
{
    __IO uint32_t STEP                      : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t ETRFLT                    : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t SRC                       : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cr0_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t MD                        : 2;
    __IO uint32_t AUTO                      : 1;
    __IO uint32_t PRS                       : 4;
    __IO uint32_t OST                       : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_cr1_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_ier_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    __IO uint32_t DIR                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_isr_field_t;

typedef struct
{
    __IO uint32_t UD                        : 1;
    __IO uint32_t END                       : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t MISS                      : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t OK                        : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_icr_field_t;

typedef struct
{
    __IO uint32_t FCAP                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_fcap_field_t;

typedef struct
{
    __IO uint32_t TVAL                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_tval_field_t;

typedef struct
{
    __IO uint32_t FLIM                      :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_ctrim_flim_field_t;

typedef struct
{
    __IO uint32_t TIM0                      : 1;
    __IO uint32_t TIM1                      : 1;
    __IO uint32_t TIM2                      : 1;
    __IO uint32_t LPTIM0                    : 1;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t IWDT                      : 1;
    __IO uint32_t RTC                       : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t TIM3                      : 1;
    __IO uint32_t LPTIM1                    : 1;
    __IO uint32_t WWDT                      : 1;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_debug_active_field_t;

typedef struct
{
    uint32_t RESERVED0                      :24;
    __IO uint32_t HALT                      : 4;
    __IO uint32_t PRIO                      : 1;
    uint32_t RESERVED29                     : 2;
    __IO uint32_t EN                        : 1;
} stc_dmac_conf_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 2;
    __IO uint32_t TRI_SEL                   : 7;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa0_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FIS_IE                    : 1;
    __IO uint32_t ERR_IE                    : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb0_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr0_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr0_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 2;
    __IO uint32_t TRI_SEL                   : 7;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa1_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FIS_IE                    : 1;
    __IO uint32_t ERR_IE                    : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb1_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr_field_t;

typedef struct
{
    __IO uint32_t OP                        : 2;
    __IO uint32_t WAIT                      : 2;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t IE                        : 2;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t DPSTB_EN                  : 1;
    __IO uint32_t CONTP                     : 1;
    __IO uint32_t RO                        : 1;
    __IO uint32_t RSV                       :20;
} stc_flash_cr_field_t;

typedef struct
{
    __IO uint32_t PC                        : 1;
    __IO uint32_t PROT                      : 1;
    __IO uint32_t RSV                       :30;
} stc_flash_ifr_field_t;

typedef struct
{
    __IO uint32_t PC                        : 1;
    __IO uint32_t PROT                      : 1;
    __IO uint32_t RSV                       :30;
} stc_flash_iclr_field_t;

typedef struct
{
    __IO uint32_t BYSEQ                     :16;
    __IO uint32_t RSV                       :16;
} stc_flash_bypass_field_t;

typedef struct
{
    __IO uint32_t SLOCK                     :32;
} stc_flash_slock0_field_t;

typedef struct
{
    __IO uint32_t SLOCK                     :32;
} stc_flash_slock1_field_t;

typedef struct
{
    __IO uint32_t LOCK_ST                   : 2;
    __IO uint32_t RSV                       :30;
} stc_flash_lock_st_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa07_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa08_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa09_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa10_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa11_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa12_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa13_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa15_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb07_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb08_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb09_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb10_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb11_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb12_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb13_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb15_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc07_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc08_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc09_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc10_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc11_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc12_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc13_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc15_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd07_sel_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_padir_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pain_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_paout_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_paads_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pabset_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pabclr_field_t;

typedef struct
{
    __IO uint32_t PABCLR                    :16;
    __IO uint32_t PABSET                    :16;
} stc_gpio_pabsetclr_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_padr_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_papu_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_papd_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_paod_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pahie_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_palie_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_parie_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pafie_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbdir_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbin_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbout_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbads_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbbset_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbbclr_field_t;

typedef struct
{
    __IO uint32_t PBBCLR                    :16;
    __IO uint32_t PBBSET                    :16;
} stc_gpio_pbbsetclr_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbdr_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbpu_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbpd_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbod_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbhie_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pblie_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbrie_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pbfie_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcdir_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcin_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcout_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcads_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcbset_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcbclr_field_t;

typedef struct
{
    __IO uint32_t PCBCLR                    :16;
    __IO uint32_t PCBSET                    :16;
} stc_gpio_pcbsetclr_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcdr_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcpu_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcpd_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcod_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pchie_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pclie_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcrie_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pcfie_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pddir_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdin_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdout_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdads_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdbset_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdbclr_field_t;

typedef struct
{
    __IO uint32_t PDBCLR                    : 8;
    uint32_t RESERVED8                      : 8;
    __IO uint32_t PDBSET                    :16;
} stc_gpio_pdbsetclr_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pddr_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdpu_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdpd_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdod_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdhie_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdlie_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdrie_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pdfie_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa_stat_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pa_iclr_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb_stat_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pb_iclr_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc_stat_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pc_iclr_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd_stat_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_gpio_pd_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t PCLK_SEL                  : 2;
    __IO uint32_t HCLK_SEL                  : 2;
    __IO uint32_t PCLK_EN                   : 1;
    __IO uint32_t HCLK_EN                   : 1;
    __IO uint32_t IR_POL                    : 1;
    __IO uint32_t HSI2C_LSEL                : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_ctrl1_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t TCLK_SEL                  : 2;
    __IO uint32_t TCLK_DIV                  : 2;
    uint32_t RESERVED8                      : 7;
    __IO uint32_t AHB_SEL                   : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_gpio_ctrl2_field_t;

typedef struct
{
    __IO uint32_t TIM0_G                    : 3;
    __IO uint32_t TIM1_G                    : 3;
    __IO uint32_t TIM2_G                    : 3;
    __IO uint32_t TIM3_G                    : 3;
    __IO uint32_t LPTIM0_G                  : 3;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_gpio_timgs_field_t;

typedef struct
{
    __IO uint32_t TIM0_E                    : 3;
    __IO uint32_t TIM1_E                    : 3;
    __IO uint32_t TIM2_E                    : 3;
    __IO uint32_t TIM3_E                    : 3;
    __IO uint32_t LPTIM0_E                  : 3;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_gpio_times_field_t;

typedef struct
{
    __IO uint32_t TIM0_CA                   : 3;
    __IO uint32_t TIM1_CA                   : 3;
    __IO uint32_t TIM2_CA                   : 3;
    __IO uint32_t TIM3_CA                   : 3;
    __IO uint32_t TIM3_CB                   : 3;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_gpio_timcps0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 6;
    __IO uint32_t LPTIM1_G                  : 3;
    __IO uint32_t LPTIM1_E                  : 3;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_gpio_timcps1_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t PB08FLTEN                 : 1;
    __IO uint32_t PB00FLTEN                 : 1;
    __IO uint32_t PA08FLTEN                 : 1;
    __IO uint32_t PA00FLTEN                 : 1;
    __IO uint32_t FCLK_DIV                  : 2;
    __IO uint32_t FCLK_SEL                  : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_gpio_fltcfg_field_t;

typedef struct
{
    __IO uint32_t MEN                       : 1;
    __IO uint32_t RST                       : 1;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t DBGEN                     : 1;
    uint32_t RESERVED4                      :27;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mcr_field_t;

typedef struct
{
    __IO uint32_t TDF                       : 1;
    __IO uint32_t RDF                       : 1;
    uint32_t RESERVED2                      : 6;
    __IO uint32_t EPF                       : 1;
    __IO uint32_t SDF                       : 1;
    __IO uint32_t NDF                       : 1;
    __IO uint32_t ALF                       : 1;
    __IO uint32_t FEF                       : 1;
    __IO uint32_t PLTF                      : 1;
    __IO uint32_t DMF                       : 1;
    uint32_t RESERVED15                     : 9;
    __IO uint32_t MBF                       : 1;
    __IO uint32_t BBF                       : 1;
    uint32_t RESERVED26                     : 5;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_msr_field_t;

typedef struct
{
    __IO uint32_t TDIE                      : 1;
    __IO uint32_t RDIE                      : 1;
    uint32_t RESERVED2                      : 6;
    __IO uint32_t EPIE                      : 1;
    __IO uint32_t SDIE                      : 1;
    __IO uint32_t NDIE                      : 1;
    __IO uint32_t ALIE                      : 1;
    __IO uint32_t FEIE                      : 1;
    __IO uint32_t PLTIE                     : 1;
    __IO uint32_t DMIE                      : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mier_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t EPC                       : 1;
    __IO uint32_t SDC                       : 1;
    __IO uint32_t NDC                       : 1;
    __IO uint32_t ALC                       : 1;
    __IO uint32_t FEC                       : 1;
    __IO uint32_t PLTC                      : 1;
    __IO uint32_t DMC                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mscr_field_t;

typedef struct
{
    __IO uint32_t PRESCALE                  : 3;
    uint32_t RESERVED3                      : 5;
    __IO uint32_t AUTOSTOP                  : 1;
    __IO uint32_t IGNACK                    : 1;
    __IO uint32_t TIMECFG                   : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t RDMO                      : 1;
    __IO uint32_t MATCFG                    : 3;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mcfgr1_field_t;

typedef struct
{
    __IO uint32_t BUSIDLE                   :12;
    uint32_t RESERVED12                     : 4;
    __IO uint32_t FILTSCL                   : 4;
    uint32_t RESERVED20                     : 3;
    __IO uint32_t FILTBPSCL                 : 1;
    __IO uint32_t FILTSDA                   : 4;
    uint32_t RESERVED28                     : 3;
    __IO uint32_t FILTBPSDA                 : 1;
} stc_hsi2c_mcfgr2_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t PINLOW                    :12;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mcfgr3_field_t;

typedef struct
{
    __IO uint32_t CLKLO                     : 6;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CLKHI                     : 6;
    uint32_t RESERVED14                     : 2;
    __IO uint32_t SETHOLD                   : 6;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t DATAVD                    : 6;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mccr0_field_t;

typedef struct
{
    __IO uint32_t CLKLO                     : 6;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CLKHI                     : 6;
    uint32_t RESERVED14                     : 2;
    __IO uint32_t SETHOLD                   : 6;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t DATAVD                    : 6;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mccr1_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    __IO uint32_t CMD                       : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mtdr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    uint32_t RESERVED8                      : 6;
    __IO uint32_t RXEMPTY                   : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mrdr_field_t;

typedef struct
{
    __IO uint32_t MATCH0                    : 8;
    uint32_t RESERVED8                      : 8;
    __IO uint32_t MATCH1                    : 8;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mdmr_field_t;

typedef struct
{
    __IO uint32_t TDDE                      : 1;
    __IO uint32_t RDDE                      : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_mder_field_t;

typedef struct
{
    __IO uint32_t SEN                       : 1;
    __IO uint32_t RST                       : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_scr0_field_t;

typedef struct
{
    __IO uint32_t TDF                       : 1;
    __IO uint32_t RDF                       : 1;
    __IO uint32_t AVF                       : 1;
    __IO uint32_t TAF                       : 1;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t RSF                       : 1;
    __IO uint32_t SDF                       : 1;
    __IO uint32_t BEF                       : 1;
    __IO uint32_t FEF                       : 1;
    __IO uint32_t AM0F                      : 1;
    __IO uint32_t AM1F                      : 1;
    __IO uint32_t GCF                       : 1;
    __IO uint32_t SARF                      : 1;
    uint32_t RESERVED16                     : 8;
    __IO uint32_t SBF                       : 1;
    __IO uint32_t BBF                       : 1;
    uint32_t RESERVED26                     : 5;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_ssr_field_t;

typedef struct
{
    __IO uint32_t TDIE                      : 1;
    __IO uint32_t RDIE                      : 1;
    __IO uint32_t AVIE                      : 1;
    __IO uint32_t TAIE                      : 1;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t RSIE                      : 1;
    __IO uint32_t SDIE                      : 1;
    __IO uint32_t BEIE                      : 1;
    __IO uint32_t FEIE                      : 1;
    __IO uint32_t AM0IE                     : 1;
    __IO uint32_t AM1IE                     : 1;
    __IO uint32_t GCIE                      : 1;
    __IO uint32_t SARIE                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_sier_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t RSC                       : 1;
    __IO uint32_t SDC                       : 1;
    __IO uint32_t BEC                       : 1;
    __IO uint32_t FEC                       : 1;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_sscr_field_t;

typedef struct
{
    __IO uint32_t ADRSTALL                  : 1;
    __IO uint32_t RXSTALL                   : 1;
    __IO uint32_t TXDSTALL                  : 1;
    __IO uint32_t ACKSTALL                  : 1;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t GCEN                      : 1;
    __IO uint32_t SAEN                      : 1;
    __IO uint32_t TXCFG                     : 1;
    __IO uint32_t RXCFG                     : 1;
    __IO uint32_t IGNACK                    : 1;
    __IO uint32_t HSMEN                     : 1;
    uint32_t RESERVED14                     : 2;
    __IO uint32_t ADDRMODE                  : 3;
    uint32_t RESERVED19                     :12;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_scr1_field_t;

typedef struct
{
    __IO uint32_t CLKHOLD                   : 4;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t DATAVD                    : 6;
    __IO uint32_t FILTEN                    : 1;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t FILTSCL                   : 4;
    __IO uint32_t FILTSDA                   : 4;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_scr2_field_t;

typedef struct
{
    __IO uint32_t TXNACK                    : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_star_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_stdr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    uint32_t RESERVED8                      : 6;
    __IO uint32_t REMP                      : 1;
    __IO uint32_t SOF                       : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_srdr_field_t;

typedef struct
{
    __IO uint32_t TDDE                      : 1;
    __IO uint32_t RDDE                      : 1;
    __IO uint32_t AVDE                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_sder_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t ADDR0                     :10;
    uint32_t RESERVED11                     : 6;
    __IO uint32_t ADDR1                     :10;
    uint32_t RESERVED27                     : 4;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_saddr_field_t;

typedef struct
{
    __IO uint32_t RADDR                     :11;
    uint32_t RESERVED11                     : 3;
    __IO uint32_t ANV                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_hsi2c_sasr_field_t;

typedef struct
{
    __IO uint32_t TME                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_i2c_tmrun_field_t;

typedef struct
{
    __IO uint32_t TM                        : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_tm_field_t;

typedef struct
{
    __IO uint32_t H1M                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t AA                        : 1;
    __IO uint32_t SI                        : 1;
    __IO uint32_t STO                       : 1;
    __IO uint32_t STA                       : 1;
    __IO uint32_t ENS                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_i2c_cr_field_t;

typedef struct
{
    __IO uint32_t DAT                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_data_field_t;

typedef struct
{
    __IO uint32_t GC                        : 1;
    __IO uint32_t ADDR0                     : 7;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_addr0_field_t;

typedef struct
{
    __IO uint32_t STA                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_stat_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t ADDR1                     : 7;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_addr1_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t ADDR2                     : 7;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_i2c_addr2_field_t;

typedef struct
{
    __IO uint32_t AD0F                      : 1;
    __IO uint32_t AD1F                      : 1;
    __IO uint32_t AD2F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_i2c_match_field_t;

typedef struct
{
    __IO uint32_t KR                        :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_kr_field_t;

typedef struct
{
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t ACTION                    : 1;
    __IO uint32_t PAUSE                     : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_cr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_arr_field_t;

typedef struct
{
    __IO uint32_t CRF                       : 1;
    __IO uint32_t ARRF                      : 1;
    __IO uint32_t WINRF                     : 1;
    __IO uint32_t OV                        : 1;
    __IO uint32_t RUN                       : 1;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_sr_field_t;

typedef struct
{
    __IO uint32_t WINR                      :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_iwdt_winr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t BIAS                      : 2;
    __IO uint32_t CPCLK                     : 2;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t DUTY                      : 3;
    __IO uint32_t BSEL                      : 3;
    __IO uint32_t CONTRAST                  : 4;
    __IO uint32_t VODEN                     : 1;
    uint32_t RESERVED17                     :14;
    __IO uint32_t RSV                       : 1;
} stc_lcd_cr0_field_t;

typedef struct
{
    __IO uint32_t BLINKCNT                  : 6;
    __IO uint32_t BLINKEN                   : 1;
    __IO uint32_t CLKSRC                    : 1;
    __IO uint32_t MODE                      : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t DMAEN                     : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t DRVRES                    : 3;
    __IO uint32_t DIV                       : 4;
    __IO uint32_t PSC                       : 3;
    __IO uint32_t DEAD                      : 3;
    uint32_t RESERVED25                     : 6;
    __IO uint32_t RSV                       : 1;
} stc_lcd_cr1_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_lcd_sr_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_lcd_intclr_field_t;

typedef struct
{
    __IO uint32_t S0                        : 1;
    __IO uint32_t S1                        : 1;
    __IO uint32_t S2                        : 1;
    __IO uint32_t S3                        : 1;
    __IO uint32_t S4                        : 1;
    __IO uint32_t S5                        : 1;
    __IO uint32_t S6                        : 1;
    __IO uint32_t S7                        : 1;
    __IO uint32_t S8                        : 1;
    __IO uint32_t S9                        : 1;
    __IO uint32_t S10                       : 1;
    __IO uint32_t S11                       : 1;
    __IO uint32_t S12                       : 1;
    __IO uint32_t S13                       : 1;
    __IO uint32_t S14                       : 1;
    __IO uint32_t S15                       : 1;
    __IO uint32_t S16                       : 1;
    __IO uint32_t S17                       : 1;
    __IO uint32_t S18                       : 1;
    __IO uint32_t S19                       : 1;
    __IO uint32_t S20                       : 1;
    __IO uint32_t S21                       : 1;
    __IO uint32_t S22                       : 1;
    __IO uint32_t S23                       : 1;
    __IO uint32_t S24                       : 1;
    __IO uint32_t S25                       : 1;
    __IO uint32_t S26                       : 1;
    __IO uint32_t S27                       : 1;
    __IO uint32_t S28                       : 1;
    __IO uint32_t S29                       : 1;
    __IO uint32_t S30                       : 1;
    __IO uint32_t S31                       : 1;
} stc_lcd_poen0_field_t;

typedef struct
{
    __IO uint32_t S32                       : 1;
    __IO uint32_t S33                       : 1;
    __IO uint32_t S34                       : 1;
    __IO uint32_t S35                       : 1;
    __IO uint32_t S36C7                     : 1;
    __IO uint32_t S37C6                     : 1;
    __IO uint32_t S38C5                     : 1;
    __IO uint32_t S39C4                     : 1;
    uint32_t RESERVED8                      :12;
    __IO uint32_t MUX                       : 1;
    __IO uint32_t C0                        : 1;
    __IO uint32_t C1                        : 1;
    __IO uint32_t C2                        : 1;
    __IO uint32_t C3                        : 1;
} stc_lcd_poen1_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram0_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram1_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram2_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram3_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram4_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram5_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram6_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram7_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t RSV                       : 8;
} stc_lcd_ram8_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t RSV                       : 8;
} stc_lcd_ram9_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t RSV                       : 8;
} stc_lcd_rama_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t RSV                       : 8;
} stc_lcd_ramb_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t RSV                       : 8;
} stc_lcd_ramc_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t RSV                       : 8;
} stc_lcd_ramd_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t RSV                       : 8;
} stc_lcd_rame_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t RSV                       : 8;
} stc_lcd_ramf_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lptimer_cnt_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lptimer_arr_field_t;

typedef struct
{
    __IO uint32_t CMP                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lptimer_cmp_field_t;

typedef struct
{
    __IO uint32_t TR                        : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOG_EN                    : 1;
    __IO uint32_t TCK_SEL                   : 2;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t WT_FLAG                   : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATE_P                    : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t PRS                       : 4;
    __IO uint32_t SYNCCOUNTRST              : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lptimer_cr_field_t;

typedef struct
{
    __IO uint32_t OV                        : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_lptimer_ifr_field_t;

typedef struct
{
    __IO uint32_t OV                        : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_lptimer_iclr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    __IO uint32_t DATA8                     : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_sbuf_field_t;

typedef struct
{
    __IO uint32_t RCIE                      : 1;
    __IO uint32_t TCIE                      : 1;
    __IO uint32_t B8CONT                    : 2;
    __IO uint32_t REN                       : 1;
    __IO uint32_t ADRDET                    : 1;
    __IO uint32_t SM                        : 2;
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t OVER                      : 2;
    __IO uint32_t SCLKSEL                   : 2;
    __IO uint32_t PEIE                      : 1;
    __IO uint32_t STOPBIT                   : 2;
    __IO uint32_t DMARXEN                   : 1;
    __IO uint32_t DMATXEN                   : 1;
    __IO uint32_t RTSEN                     : 1;
    __IO uint32_t CTSEN                     : 1;
    __IO uint32_t CTSIE                     : 1;
    __IO uint32_t FEIE                      : 1;
    __IO uint32_t HDSEL                     : 1;
    uint32_t RESERVED23                     : 8;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_scon_field_t;

typedef struct
{
    __IO uint32_t SADDR                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_saddr_field_t;

typedef struct
{
    __IO uint32_t SADEN                     : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_saden_field_t;

typedef struct
{
    __IO uint32_t RC                        : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t CTSIF                     : 1;
    __IO uint32_t CTS                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_isr_field_t;

typedef struct
{
    __IO uint32_t RCCF                      : 1;
    __IO uint32_t TCCF                      : 1;
    __IO uint32_t FECF                      : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PECF                      : 1;
    __IO uint32_t CTSIFCF                   : 1;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_icr_field_t;

typedef struct
{
    __IO uint32_t SCNT                      :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_scnt_field_t;

typedef struct
{
    __IO uint32_t BSEL                      : 2;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_bsel_field_t;

typedef struct
{
    __IO uint32_t MODU                      :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_lpuart_modu_field_t;

typedef struct
{
    __IO uint32_t LVDEN                     : 1;
    __IO uint32_t ACT                       : 1;
    __IO uint32_t SOURCE_SEL                : 2;
    __IO uint32_t VTDS                      : 4;
    __IO uint32_t DEBOUNCE_TIME             : 4;
    __IO uint32_t FTEN                      : 1;
    __IO uint32_t RTEN                      : 1;
    __IO uint32_t HTEN                      : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED16                     : 1;
    __IO uint32_t FLT_MODE                  : 2;
    uint32_t RESERVED19                     :12;
    __IO uint32_t RSV                       : 1;
} stc_lvd_cr_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    __IO uint32_t FILTER                    : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_lvd_ifr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_ram_cr_field_t;

typedef struct
{
    __IO uint32_t ERRADDR                   :14;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_ram_erraddr_field_t;

typedef struct
{
    __IO uint32_t ERR                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_ram_ifr_field_t;

typedef struct
{
    __IO uint32_t ERRCLR                    : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_ram_iclr_field_t;

typedef struct
{
    __IO uint32_t POR5V                     : 1;
    __IO uint32_t POR15V                    : 1;
    __IO uint32_t LVD                       : 1;
    __IO uint32_t IWDT                      : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t LOCKUP                    : 1;
    __IO uint32_t SYSREQ                    : 1;
    __IO uint32_t RSTB                      : 1;
    __IO uint32_t WWDT                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_reset_flag_field_t;

typedef struct
{
    __IO uint32_t USART0                    : 1;
    __IO uint32_t USART1                    : 1;
    __IO uint32_t LPUART0                   : 1;
    __IO uint32_t LPUART1                   : 1;
    __IO uint32_t I2C0                      : 1;
    __IO uint32_t I2C1                      : 1;
    __IO uint32_t SPI0                      : 1;
    __IO uint32_t SPI1                      : 1;
    __IO uint32_t TIM012                    : 1;
    __IO uint32_t LPTIM0                    : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t TIM3                      : 1;
    uint32_t RESERVED12                     : 4;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VC                        : 1;
    __IO uint32_t TRNG                      : 1;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t RTC                       : 1;
    uint32_t RESERVED21                     : 1;
    __IO uint32_t LCD                       : 1;
    uint32_t RESERVED23                     : 3;
    __IO uint32_t CRC                       : 1;
    __IO uint32_t AES                       : 1;
    __IO uint32_t GPIO                      : 1;
    __IO uint32_t DMA                       : 1;
    __IO uint32_t HSI2C                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_reset_peri_reset0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t CTRIM                     : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t LPTIM1                    : 1;
    uint32_t RESERVED5                      : 3;
    __IO uint32_t LPUART2                   : 1;
    uint32_t RESERVED9                      : 1;
    __IO uint32_t WWDT                      : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_reset_peri_reset1_field_t;

typedef struct
{
    __IO uint32_t PRDS                      : 3;
    __IO uint32_t AMPM                      : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t HZ1OE                     : 1;
    __IO uint32_t HZ1SEL                    : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t PRDX                      : 6;
    __IO uint32_t PRDSEL                    : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr0_field_t;

typedef struct
{
    __IO uint32_t WAIT                      : 1;
    __IO uint32_t WAITF                     : 1;
    uint32_t RESERVED2                      : 6;
    __IO uint32_t CKSEL                     : 3;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr1_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_sec_field_t;

typedef struct
{
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_min_field_t;

typedef struct
{
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_rtc_hour_field_t;

typedef struct
{
    __IO uint32_t WEEK                      : 3;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_rtc_week_field_t;

typedef struct
{
    __IO uint32_t DAYL                      : 4;
    __IO uint32_t DAYH                      : 2;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_rtc_day_field_t;

typedef struct
{
    __IO uint32_t MON                       : 5;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_rtc_mon_field_t;

typedef struct
{
    __IO uint32_t YEARL                     : 4;
    __IO uint32_t YEARH                     : 4;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_rtc_year_field_t;

typedef struct
{
    __IO uint32_t CR                        :13;
    uint32_t RESERVED13                     : 1;
    __IO uint32_t CSTEPS                    : 1;
    __IO uint32_t EN                        : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_compen_field_t;

typedef struct
{
    __IO uint32_t PARA                      : 6;
    uint32_t RESERVED6                      :25;
    __IO uint32_t RSV                       : 1;
} stc_rtc_hcomp_field_t;

typedef struct
{
    __IO uint32_t WUCKSEL                   : 3;
    __IO uint32_t TSEDG                     : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t TSE                       : 1;
    __IO uint32_t WUTE                      : 1;
    uint32_t RESERVED8                      : 1;
    __IO uint32_t ALMAE                     : 1;
    __IO uint32_t ALMBE                     : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_rtc_cr2_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    __IO uint32_t MSKS                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    __IO uint32_t MSKM                      : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 1;
    __IO uint32_t MSKH                      : 1;
    __IO uint32_t WEEK                      : 7;
    __IO uint32_t RSV                       : 1;
} stc_rtc_alma_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    __IO uint32_t MSKS                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    __IO uint32_t MSKM                      : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 1;
    __IO uint32_t MSKH                      : 1;
    __IO uint32_t WEEK                      : 7;
    __IO uint32_t RSV                       : 1;
} stc_rtc_almb_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
    uint32_t RESERVED22                     : 9;
    __IO uint32_t RSV                       : 1;
} stc_rtc_tstr_field_t;

typedef struct
{
    __IO uint32_t DAYL                      : 4;
    __IO uint32_t DAYH                      : 2;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t MON                       : 5;
    __IO uint32_t WEEK                      : 3;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_tsdr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_rtc_wutr_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_ier_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    __IO uint32_t TSOV                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_ifr_field_t;

typedef struct
{
    __IO uint32_t ALMA                      : 1;
    __IO uint32_t ALMB                      : 1;
    __IO uint32_t WU                        : 1;
    __IO uint32_t TS                        : 1;
    __IO uint32_t TSOV                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t PRD                       : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_rtc_icr_field_t;

typedef struct
{
    __IO uint32_t WPR                       : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_rtc_wpr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t BRR                       : 3;
    __IO uint32_t CPHA                      : 1;
    __IO uint32_t CPOL                      : 1;
    __IO uint32_t MSTR                      : 1;
    __IO uint32_t LSBF                      : 1;
    __IO uint32_t WIDTH                     : 4;
    __IO uint32_t SSM                       : 1;
    __IO uint32_t CM                        : 2;
    __IO uint32_t SMP                       : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_spi_cr0_field_t;

typedef struct
{
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t RXNEIE                    : 1;
    __IO uint32_t SSFIE                     : 1;
    __IO uint32_t SSRIE                     : 1;
    __IO uint32_t UDFIE                     : 1;
    __IO uint32_t OVFIE                     : 1;
    __IO uint32_t SSERRIE                   : 1;
    __IO uint32_t MODFIE                    : 1;
    __IO uint32_t DMARXEN                   : 1;
    __IO uint32_t DMATXEN                   : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_spi_cr1_field_t;

typedef struct
{
    __IO uint32_t HDOE                      : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_spi_hdoe_field_t;

typedef struct
{
    __IO uint32_t SSI                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_spi_ssi_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t SSF                       : 1;
    __IO uint32_t SSR                       : 1;
    __IO uint32_t UDF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t SSERR                     : 1;
    __IO uint32_t MODF                      : 1;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t SSLVL                     : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_spi_sr_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t SSF                       : 1;
    __IO uint32_t SSR                       : 1;
    __IO uint32_t UDF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t SSERR                     : 1;
    __IO uint32_t MODF                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_spi_icr_field_t;

typedef struct
{
    __IO uint32_t DR                        :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_spi_dr_field_t;

typedef struct
{
    __IO uint32_t RCH_EN                    : 1;
    __IO uint32_t XTH_EN                    : 1;
    __IO uint32_t RCL_EN                    : 1;
    __IO uint32_t XTL_EN                    : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t CLKSW                     : 3;
    __IO uint32_t HCLK_PRS                  : 3;
    __IO uint32_t PCLK_PRS                  : 2;
    uint32_t RESERVED13                     : 2;
    __IO uint32_t WAKEUP_BYRCH              : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t EXTH_EN                   : 1;
    __IO uint32_t EXTL_EN                   : 1;
    __IO uint32_t XTL_ALWAYS_ON             : 1;
    __IO uint32_t CLK_FAULT_EN              : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t LOCKUP_EN                 : 1;
    __IO uint32_t SPI_PCTRL                 : 1;
    __IO uint32_t SWD_USE_IO                : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl1_field_t;

typedef struct
{
    __IO uint32_t SYSCTRL2                  :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_sysctrl2_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t TRIMF                     : 6;
    __IO uint32_t TRIMC                     : 8;
    __IO uint32_t FSEL                      : 2;
    uint32_t RESERVED18                     : 6;
    __IO uint32_t ITC                       : 4;
    uint32_t RESERVED28                     : 3;
    __IO uint32_t STABLE                    : 1;
} stc_sysctrl_rch_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t XTH_FSEL                  : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
    __IO uint32_t DETIE                     : 1;
    uint32_t RESERVED8                      : 1;
    __IO uint32_t DETEN                     : 1;
    __IO uint32_t FAULT_STATE               : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_xth_cr_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :10;
    __IO uint32_t MSEL                      : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t STABLE                    : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_rcl_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t AMP_SEL                   : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
    __IO uint32_t DETIE                     : 1;
    __IO uint32_t DETTIME                   : 1;
    __IO uint32_t DETEN                     : 1;
    __IO uint32_t FAULT_STATE               : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_xtl_cr_field_t;

typedef struct
{
    __IO uint32_t USART0                    : 1;
    __IO uint32_t USART1                    : 1;
    __IO uint32_t LPUART0                   : 1;
    __IO uint32_t LPUART1                   : 1;
    __IO uint32_t I2C0                      : 1;
    __IO uint32_t I2C1                      : 1;
    __IO uint32_t SPI0                      : 1;
    __IO uint32_t SPI1                      : 1;
    __IO uint32_t TIM012                    : 1;
    __IO uint32_t LPTIM0                    : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t TIM3                      : 1;
    uint32_t RESERVED12                     : 3;
    __IO uint32_t IWDT                      : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VC                        : 1;
    __IO uint32_t TRNG                      : 1;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t RTC                       : 1;
    uint32_t RESERVED21                     : 1;
    __IO uint32_t LCD                       : 1;
    uint32_t RESERVED23                     : 3;
    __IO uint32_t CRC                       : 1;
    __IO uint32_t AES                       : 1;
    __IO uint32_t GPIO                      : 1;
    __IO uint32_t DMA                       : 1;
    __IO uint32_t HSI2C                     : 1;
    __IO uint32_t FLASH                     : 1;
} stc_sysctrl_peri_clken0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t CTRIM                     : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t LPTIM1                    : 1;
    uint32_t RESERVED5                      : 3;
    __IO uint32_t LPUART2                   : 1;
    uint32_t RESERVED9                      : 1;
    __IO uint32_t WWDT                      : 1;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_sysctrl_peri_clken1_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim0_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim0_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CIEA                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
    __IO uint32_t OVE                       : 1;
    __IO uint32_t UNDE                      : 1;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim0_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t CMB0E                     : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t ADTE                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VCE                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim0_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim1_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim1_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CIEA                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
    __IO uint32_t OVE                       : 1;
    __IO uint32_t UNDE                      : 1;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim1_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t CMB0E                     : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t ADTE                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VCE                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim1_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim2_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim2_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CIEA                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
    __IO uint32_t OVE                       : 1;
    __IO uint32_t UNDE                      : 1;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim2_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t CMB0E                     : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t ADTE                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VCE                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim2_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim3_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      :28;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim3_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CIEA                      : 1;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
    __IO uint32_t OVE                       : 1;
    __IO uint32_t UNDE                      : 1;
    uint32_t RESERVED30                     : 1;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    __IO uint32_t CA1F                      : 1;
    __IO uint32_t CA2F                      : 1;
    __IO uint32_t CB0F                      : 1;
    __IO uint32_t CB1F                      : 1;
    __IO uint32_t CB2F                      : 1;
    __IO uint32_t CA0E                      : 1;
    __IO uint32_t CA1E                      : 1;
    __IO uint32_t CA2E                      : 1;
    __IO uint32_t CB0E                      : 1;
    __IO uint32_t CB1E                      : 1;
    __IO uint32_t CB2E                      : 1;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    __IO uint32_t CA3F                      : 1;
    __IO uint32_t CB3F                      : 1;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    __IO uint32_t CA1F                      : 1;
    __IO uint32_t CA2F                      : 1;
    __IO uint32_t CB0F                      : 1;
    __IO uint32_t CB1F                      : 1;
    __IO uint32_t CB2F                      : 1;
    __IO uint32_t CA0E                      : 1;
    __IO uint32_t CA1E                      : 1;
    __IO uint32_t CA2E                      : 1;
    __IO uint32_t CB0E                      : 1;
    __IO uint32_t CB1E                      : 1;
    __IO uint32_t CB2E                      : 1;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
    __IO uint32_t OVF                       : 1;
    __IO uint32_t UNDF                      : 1;
    __IO uint32_t CA3F                      : 1;
    __IO uint32_t CB3F                      : 1;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
    uint32_t RESERVED13                     :18;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    __IO uint32_t OCMA1_FLTA1               : 3;
    __IO uint32_t CCPA1                     : 1;
    __IO uint32_t OCMB1_FLTB1               : 3;
    __IO uint32_t CCPB1                     : 1;
    __IO uint32_t OCMA2_FLTA2               : 3;
    __IO uint32_t CCPA2                     : 1;
    __IO uint32_t OCMB2_FLTB2               : 3;
    __IO uint32_t CCPB2                     : 1;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim3_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    __IO uint32_t CMA1E                     : 1;
    __IO uint32_t CMA2E                     : 1;
    __IO uint32_t CMB0E                     : 1;
    __IO uint32_t CMB1E                     : 1;
    __IO uint32_t CMB2E                     : 1;
    __IO uint32_t ADTE                      : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_crch1_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_crch2_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VCE                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
    __IO uint32_t OV                        : 1;
    __IO uint32_t UND                       : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t CCR1A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ccr1a_field_t;

typedef struct
{
    __IO uint32_t CCR1B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ccr1b_field_t;

typedef struct
{
    __IO uint32_t CCR2A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ccr2a_field_t;

typedef struct
{
    __IO uint32_t CCR2B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ccr2b_field_t;

typedef struct
{
    __IO uint32_t CCR3A                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ccr3a_field_t;

typedef struct
{
    __IO uint32_t BUF                       : 1;
    __IO uint32_t CIE                       : 1;
    __IO uint32_t CDE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t C3AEN                     : 1;
    __IO uint32_t CM3AE                     : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_crch3a_field_t;

typedef struct
{
    __IO uint32_t CCR3B                     :16;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_ccr3b_field_t;

typedef struct
{
    __IO uint32_t BUF                       : 1;
    __IO uint32_t CIE                       : 1;
    __IO uint32_t CDE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t C3BEN                     : 1;
    __IO uint32_t CM3BE                     : 1;
    uint32_t RESERVED7                      :24;
    __IO uint32_t RSV                       : 1;
} stc_tim3_mode23_crch3b_field_t;

typedef struct
{
    __IO uint32_t TRNGCIR_EN                : 1;
    __IO uint32_t TRNG_RUN                  : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_trng_cr_field_t;

typedef struct
{
    __IO uint32_t LOAD                      : 1;
    __IO uint32_t FDBK                      : 1;
    __IO uint32_t CNT                       : 3;
    uint32_t RESERVED5                      :26;
    __IO uint32_t RSV                       : 1;
} stc_trng_mode_field_t;

typedef struct
{
    __IO uint32_t DATA0                     :32;
} stc_trng_data0_field_t;

typedef struct
{
    __IO uint32_t DATA1                     :32;
} stc_trng_data1_field_t;

typedef struct
{
    __IO uint32_t RE                        : 1;
    __IO uint32_t TE                        : 1;
    __IO uint32_t PS                        : 1;
    __IO uint32_t PCE                       : 1;
    __IO uint32_t CHLEN                     : 1;
    __IO uint32_t STOP                      : 1;
    __IO uint32_t MSB                       : 1;
    __IO uint32_t OVER8                     : 1;
    __IO uint32_t TOE                       : 3;
    __IO uint32_t SBS                       : 1;
    __IO uint32_t COMB                      : 1;
    __IO uint32_t MPE                       : 1;
    __IO uint32_t SLME                      : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_usart_cr1_field_t;

typedef struct
{
    __IO uint32_t RXDMAEN                   : 1;
    __IO uint32_t TXDMAEN                   : 1;
    __IO uint32_t RTSEN                     : 1;
    __IO uint32_t CTSEN                     : 1;
    __IO uint32_t RXINV                     : 1;
    __IO uint32_t TXINV                     : 1;
    __IO uint32_t SYNC                      : 1;
    __IO uint32_t SWAP                      : 1;
    __IO uint32_t CLKC                      : 2;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_usart_cr2_field_t;

typedef struct
{
    __IO uint32_t LINEN                     : 1;
    __IO uint32_t LBDE                      : 1;
    __IO uint32_t ABRE                      : 1;
    __IO uint32_t BREAK                     : 1;
    __IO uint32_t SCEN                      : 1;
    __IO uint32_t BCN                       : 3;
    __IO uint32_t SMCPU                     : 2;
    uint32_t RESERVED10                     : 3;
    __IO uint32_t IREN                      : 1;
    __IO uint32_t IRCW                      : 1;
    __IO uint32_t IRMOD                     : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t RSV                       : 1;
} stc_usart_cr3_field_t;

typedef struct
{
    __IO uint32_t DIVF                      : 7;
    __IO uint32_t FBME                      : 1;
    __IO uint32_t DIVI                      : 8;
    __IO uint32_t PSC                       : 2;
    uint32_t RESERVED18                     :13;
    __IO uint32_t RSV                       : 1;
} stc_usart_brr_field_t;

typedef struct
{
    __IO uint32_t TOR                       :20;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_usart_tor_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t OR                        : 1;
    __IO uint32_t TO                        : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t MPB                       : 1;
    __IO uint32_t AM                        : 1;
    __IO uint32_t CTSV                      : 1;
    __IO uint32_t CTS                       : 1;
    __IO uint32_t ABR                       : 1;
    __IO uint32_t LBD                       : 1;
    __IO uint32_t DWK                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_usart_sr_field_t;

typedef struct
{
    __IO uint32_t TDR                       : 9;
    __IO uint32_t MPID                      : 1;
    uint32_t RESERVED10                     :21;
    __IO uint32_t RSV                       : 1;
} stc_usart_tdr_field_t;

typedef struct
{
    __IO uint32_t TXE                       : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t OR                        : 1;
    __IO uint32_t TO                        : 1;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t AM                        : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t CTS                       : 1;
    __IO uint32_t ABR                       : 1;
    __IO uint32_t LBD                       : 1;
    __IO uint32_t DWK                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_usart_ier_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t OR                        : 1;
    __IO uint32_t TO                        : 1;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t AM                        : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t CTS                       : 1;
    __IO uint32_t ABR                       : 1;
    __IO uint32_t LBD                       : 1;
    __IO uint32_t DWK                       : 1;
    uint32_t RESERVED15                     :16;
    __IO uint32_t RSV                       : 1;
} stc_usart_icr_field_t;

typedef struct
{
    __IO uint32_t RDR                       : 9;
    uint32_t RESERVED9                      :22;
    __IO uint32_t RSV                       : 1;
} stc_usart_rdr_field_t;

typedef struct
{
    __IO uint32_t ADDR                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_usart_addr_field_t;

typedef struct
{
    __IO uint32_t ADDM                      : 8;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_usart_addmr_field_t;

typedef struct
{
    __IO uint32_t BDR                       :12;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_usart_bdr_field_t;

typedef struct
{
    __IO uint32_t DCNTL                     :11;
    uint32_t RESERVED11                     : 5;
    __IO uint32_t DCNTH                     :11;
    uint32_t RESERVED27                     : 4;
    __IO uint32_t RSV                       : 1;
} stc_usart_ir_field_t;

typedef struct
{
    __IO uint32_t DIV                       : 6;
    __IO uint32_t DIV_EN                    : 1;
    __IO uint32_t REF                       : 1;
    __IO uint32_t BIAS                      : 2;
    __IO uint32_t HYS                       : 2;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_vc_cr0_field_t;

typedef struct
{
    __IO uint32_t PSEL                      : 4;
    __IO uint32_t NSEL                      : 4;
    __IO uint32_t FLTTIME                   : 4;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t EN                        : 1;
    __IO uint32_t FLTCLK                    : 1;
    __IO uint32_t FLTMODE                   : 2;
    uint32_t RESERVED20                     :11;
    __IO uint32_t RSV                       : 1;
} stc_vc_cr1_field_t;

typedef struct
{
    __IO uint32_t POL                       : 1;
    __IO uint32_t TIM0CLR                   : 1;
    __IO uint32_t TIM1CLR                   : 1;
    __IO uint32_t TIM2CLR                   : 1;
    __IO uint32_t TIM3CLR                   : 1;
    __IO uint32_t TIMBK                     : 1;
    __IO uint32_t WINDOW                    : 1;
    __IO uint32_t BLANK                     : 4;
    uint32_t RESERVED11                     :20;
    __IO uint32_t RSV                       : 1;
} stc_vc_cr2_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    __IO uint32_t FILTER                    : 1;
    uint32_t RESERVED2                      :29;
    __IO uint32_t RSV                       : 1;
} stc_vc_ifr_field_t;

typedef struct
{
    __IO uint32_t TRIM0                     : 4;
    uint32_t RESERVED4                      : 4;
    __IO uint32_t TRIM1                     : 4;
    uint32_t RESERVED12                     :19;
    __IO uint32_t RSV                       : 1;
} stc_vctrim_field_t;

typedef struct
{
    __IO uint32_t WCNT                      : 7;
    __IO uint32_t EN                        : 1;
    uint32_t RESERVED8                      :23;
    __IO uint32_t RSV                       : 1;
} stc_wwdt_cr0_field_t;

typedef struct
{
    __IO uint32_t WINR                      : 7;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t IE                        : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED14                     :17;
    __IO uint32_t RSV                       : 1;
} stc_wwdt_cr1_field_t;

typedef struct
{
    __IO uint32_t POV                       : 1;
    uint32_t RESERVED1                      :30;
    __IO uint32_t RSV                       : 1;
} stc_wwdt_sr_field_t;


typedef struct
{
    union
    {
        __IO uint32_t BGR;
        stc_adc_bgr_field_t BGR_f;
    };
    union
    {
        __IO uint32_t CR0;
        stc_adc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_adc_cr1_field_t CR1_f;
    };
    uint8_t RESERVED3[52];
    union
    {
        __IO uint32_t SQR0;
        stc_adc_sqr0_field_t SQR0_f;
    };
    uint8_t RESERVED4[4];
    union
    {
        __IO uint32_t SQR1;
        stc_adc_sqr1_field_t SQR1_f;
    };
    union
    {
        __IO uint32_t JQR;
        stc_adc_jqr_field_t JQR_f;
    };
    union
    {
        __IO uint32_t SQRRESULT0;
        stc_adc_sqrresult0_field_t SQRRESULT0_f;
    };
    union
    {
        __IO uint32_t SQRRESULT1;
        stc_adc_sqrresult1_field_t SQRRESULT1_f;
    };
    union
    {
        __IO uint32_t SQRRESULT2;
        stc_adc_sqrresult2_field_t SQRRESULT2_f;
    };
    union
    {
        __IO uint32_t SQRRESULT3;
        stc_adc_sqrresult3_field_t SQRRESULT3_f;
    };
    union
    {
        __IO uint32_t SQRRESULT4;
        stc_adc_sqrresult4_field_t SQRRESULT4_f;
    };
    union
    {
        __IO uint32_t SQRRESULT5;
        stc_adc_sqrresult5_field_t SQRRESULT5_f;
    };
    uint8_t RESERVED12[40];
    union
    {
        __IO uint32_t JQRRESULT0;
        stc_adc_jqrresult0_field_t JQRRESULT0_f;
    };
    union
    {
        __IO uint32_t JQRRESULT1;
        stc_adc_jqrresult1_field_t JQRRESULT1_f;
    };
    union
    {
        __IO uint32_t JQRRESULT2;
        stc_adc_jqrresult2_field_t JQRRESULT2_f;
    };
    union
    {
        __IO uint32_t JQRRESULT3;
        stc_adc_jqrresult3_field_t JQRRESULT3_f;
    };
    union
    {
        __IO uint32_t RESULT;
        stc_adc_result_field_t RESULT_f;
    };
    union
    {
        __IO uint32_t RESULTACC;
        stc_adc_resultacc_field_t RESULTACC_f;
    };
    union
    {
        __IO uint32_t HT;
        stc_adc_ht_field_t HT_f;
    };
    union
    {
        __IO uint32_t LT;
        stc_adc_lt_field_t LT_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_adc_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_adc_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t EXTTRIGGER0;
        stc_adc_exttrigger0_field_t EXTTRIGGER0_f;
    };
    union
    {
        __IO uint32_t EXTTRIGGER1;
        stc_adc_exttrigger1_field_t EXTTRIGGER1_f;
    };
    union
    {
        __IO uint32_t SGLSTART;
        stc_adc_sglstart_field_t SGLSTART_f;
    };
    union
    {
        __IO uint32_t SQRSTART;
        stc_adc_sqrstart_field_t SQRSTART_f;
    };
    union
    {
        __IO uint32_t JQRSTART;
        stc_adc_jqrstart_field_t JQRSTART_f;
    };
    union
    {
        __IO uint32_t ALLSTART;
        stc_adc_allstart_field_t ALLSTART_f;
    };
}M0P_ADC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_aes_cr_field_t CR_f;
    };
    uint8_t RESERVED1[12];
    union
    {
        __IO uint32_t DATA0;
        stc_aes_data0_field_t DATA0_f;
    };
    union
    {
        __IO uint32_t DATA1;
        stc_aes_data1_field_t DATA1_f;
    };
    union
    {
        __IO uint32_t DATA2;
        stc_aes_data2_field_t DATA2_f;
    };
    union
    {
        __IO uint32_t DATA3;
        stc_aes_data3_field_t DATA3_f;
    };
    union
    {
        __IO uint32_t KEY0;
        stc_aes_key0_field_t KEY0_f;
    };
    union
    {
        __IO uint32_t KEY1;
        stc_aes_key1_field_t KEY1_f;
    };
    union
    {
        __IO uint32_t KEY2;
        stc_aes_key2_field_t KEY2_f;
    };
    union
    {
        __IO uint32_t KEY3;
        stc_aes_key3_field_t KEY3_f;
    };
    union
    {
        __IO uint32_t KEY4;
        stc_aes_key4_field_t KEY4_f;
    };
    union
    {
        __IO uint32_t KEY5;
        stc_aes_key5_field_t KEY5_f;
    };
    union
    {
        __IO uint32_t KEY6;
        stc_aes_key6_field_t KEY6_f;
    };
    union
    {
        __IO uint32_t KEY7;
        stc_aes_key7_field_t KEY7_f;
    };
    union
    {
        __IO uint32_t CRDM;
        stc_aes_crdm_field_t CRDM_f;
    };
}M0P_AES_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_crc_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t RESULT;
        stc_crc_result_field_t RESULT_f;
    };
    uint8_t RESERVED2[120];
    union
    {
        __IO uint32_t DATA;
        stc_crc_data_field_t DATA_f;
    };
}M0P_CRC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_ctrim_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_ctrim_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t CR0;
        stc_ctrim_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_ctrim_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_ctrim_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_ctrim_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_ctrim_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t FCAP;
        stc_ctrim_fcap_field_t FCAP_f;
    };
    union
    {
        __IO uint32_t TVAL;
        stc_ctrim_tval_field_t TVAL_f;
    };
    union
    {
        __IO uint32_t FLIM;
        stc_ctrim_flim_field_t FLIM_f;
    };
}M0P_CTRIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t DEBUG_ACTIVE;
        stc_debug_active_field_t DEBUG_ACTIVE_f;
    };
}M0P_DEBUG_ACTIVE_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CONF;
        stc_dmac_conf_field_t CONF_f;
    };
    uint8_t RESERVED1[12];
    union
    {
        __IO uint32_t CONFA0;
        stc_dmac_confa0_field_t CONFA0_f;
    };
    union
    {
        __IO uint32_t CONFB0;
        stc_dmac_confb0_field_t CONFB0_f;
    };
    union
    {
        __IO uint32_t SRCADR0;
        stc_dmac_srcadr0_field_t SRCADR0_f;
    };
    union
    {
        __IO uint32_t DSTADR0;
        stc_dmac_dstadr0_field_t DSTADR0_f;
    };
    union
    {
        __IO uint32_t CONFA1;
        stc_dmac_confa1_field_t CONFA1_f;
    };
    union
    {
        __IO uint32_t CONFB1;
        stc_dmac_confb1_field_t CONFB1_f;
    };
    union
    {
        __IO uint32_t SRCADR;
        stc_dmac_srcadr_field_t SRCADR_f;
    };
    union
    {
        __IO uint32_t DSTADR;
        stc_dmac_dstadr_field_t DSTADR_f;
    };
}M0P_DMAC_TypeDef;

typedef struct
{
    uint8_t RESERVED0[32];
    union
    {
        __IO uint32_t CR;
        stc_flash_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_flash_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_flash_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t BYPASS;
        stc_flash_bypass_field_t BYPASS_f;
    };
    union
    {
        __IO uint32_t SLOCK0;
        stc_flash_slock0_field_t SLOCK0_f;
    };
    union
    {
        __IO uint32_t SLOCK1;
        stc_flash_slock1_field_t SLOCK1_f;
    };
    uint8_t RESERVED6[52];
    union
    {
        __IO uint32_t LOCK_ST;
        stc_flash_lock_st_field_t LOCK_ST_f;
    };
}M0P_FLASH_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t PA00_SEL;
        stc_gpio_pa00_sel_field_t PA00_SEL_f;
    };
    union
    {
        __IO uint32_t PA01_SEL;
        stc_gpio_pa01_sel_field_t PA01_SEL_f;
    };
    union
    {
        __IO uint32_t PA02_SEL;
        stc_gpio_pa02_sel_field_t PA02_SEL_f;
    };
    union
    {
        __IO uint32_t PA03_SEL;
        stc_gpio_pa03_sel_field_t PA03_SEL_f;
    };
    union
    {
        __IO uint32_t PA04_SEL;
        stc_gpio_pa04_sel_field_t PA04_SEL_f;
    };
    union
    {
        __IO uint32_t PA05_SEL;
        stc_gpio_pa05_sel_field_t PA05_SEL_f;
    };
    union
    {
        __IO uint32_t PA06_SEL;
        stc_gpio_pa06_sel_field_t PA06_SEL_f;
    };
    union
    {
        __IO uint32_t PA07_SEL;
        stc_gpio_pa07_sel_field_t PA07_SEL_f;
    };
    union
    {
        __IO uint32_t PA08_SEL;
        stc_gpio_pa08_sel_field_t PA08_SEL_f;
    };
    union
    {
        __IO uint32_t PA09_SEL;
        stc_gpio_pa09_sel_field_t PA09_SEL_f;
    };
    union
    {
        __IO uint32_t PA10_SEL;
        stc_gpio_pa10_sel_field_t PA10_SEL_f;
    };
    union
    {
        __IO uint32_t PA11_SEL;
        stc_gpio_pa11_sel_field_t PA11_SEL_f;
    };
    union
    {
        __IO uint32_t PA12_SEL;
        stc_gpio_pa12_sel_field_t PA12_SEL_f;
    };
    union
    {
        __IO uint32_t PA13_SEL;
        stc_gpio_pa13_sel_field_t PA13_SEL_f;
    };
    union
    {
        __IO uint32_t PA14_SEL;
        stc_gpio_pa14_sel_field_t PA14_SEL_f;
    };
    union
    {
        __IO uint32_t PA15_SEL;
        stc_gpio_pa15_sel_field_t PA15_SEL_f;
    };
    union
    {
        __IO uint32_t PB00_SEL;
        stc_gpio_pb00_sel_field_t PB00_SEL_f;
    };
    union
    {
        __IO uint32_t PB01_SEL;
        stc_gpio_pb01_sel_field_t PB01_SEL_f;
    };
    union
    {
        __IO uint32_t PB02_SEL;
        stc_gpio_pb02_sel_field_t PB02_SEL_f;
    };
    union
    {
        __IO uint32_t PB03_SEL;
        stc_gpio_pb03_sel_field_t PB03_SEL_f;
    };
    union
    {
        __IO uint32_t PB04_SEL;
        stc_gpio_pb04_sel_field_t PB04_SEL_f;
    };
    union
    {
        __IO uint32_t PB05_SEL;
        stc_gpio_pb05_sel_field_t PB05_SEL_f;
    };
    union
    {
        __IO uint32_t PB06_SEL;
        stc_gpio_pb06_sel_field_t PB06_SEL_f;
    };
    union
    {
        __IO uint32_t PB07_SEL;
        stc_gpio_pb07_sel_field_t PB07_SEL_f;
    };
    union
    {
        __IO uint32_t PB08_SEL;
        stc_gpio_pb08_sel_field_t PB08_SEL_f;
    };
    union
    {
        __IO uint32_t PB09_SEL;
        stc_gpio_pb09_sel_field_t PB09_SEL_f;
    };
    union
    {
        __IO uint32_t PB10_SEL;
        stc_gpio_pb10_sel_field_t PB10_SEL_f;
    };
    union
    {
        __IO uint32_t PB11_SEL;
        stc_gpio_pb11_sel_field_t PB11_SEL_f;
    };
    union
    {
        __IO uint32_t PB12_SEL;
        stc_gpio_pb12_sel_field_t PB12_SEL_f;
    };
    union
    {
        __IO uint32_t PB13_SEL;
        stc_gpio_pb13_sel_field_t PB13_SEL_f;
    };
    union
    {
        __IO uint32_t PB14_SEL;
        stc_gpio_pb14_sel_field_t PB14_SEL_f;
    };
    union
    {
        __IO uint32_t PB15_SEL;
        stc_gpio_pb15_sel_field_t PB15_SEL_f;
    };
    union
    {
        __IO uint32_t PC00_SEL;
        stc_gpio_pc00_sel_field_t PC00_SEL_f;
    };
    union
    {
        __IO uint32_t PC01_SEL;
        stc_gpio_pc01_sel_field_t PC01_SEL_f;
    };
    union
    {
        __IO uint32_t PC02_SEL;
        stc_gpio_pc02_sel_field_t PC02_SEL_f;
    };
    union
    {
        __IO uint32_t PC03_SEL;
        stc_gpio_pc03_sel_field_t PC03_SEL_f;
    };
    union
    {
        __IO uint32_t PC04_SEL;
        stc_gpio_pc04_sel_field_t PC04_SEL_f;
    };
    union
    {
        __IO uint32_t PC05_SEL;
        stc_gpio_pc05_sel_field_t PC05_SEL_f;
    };
    union
    {
        __IO uint32_t PC06_SEL;
        stc_gpio_pc06_sel_field_t PC06_SEL_f;
    };
    union
    {
        __IO uint32_t PC07_SEL;
        stc_gpio_pc07_sel_field_t PC07_SEL_f;
    };
    union
    {
        __IO uint32_t PC08_SEL;
        stc_gpio_pc08_sel_field_t PC08_SEL_f;
    };
    union
    {
        __IO uint32_t PC09_SEL;
        stc_gpio_pc09_sel_field_t PC09_SEL_f;
    };
    union
    {
        __IO uint32_t PC10_SEL;
        stc_gpio_pc10_sel_field_t PC10_SEL_f;
    };
    union
    {
        __IO uint32_t PC11_SEL;
        stc_gpio_pc11_sel_field_t PC11_SEL_f;
    };
    union
    {
        __IO uint32_t PC12_SEL;
        stc_gpio_pc12_sel_field_t PC12_SEL_f;
    };
    union
    {
        __IO uint32_t PC13_SEL;
        stc_gpio_pc13_sel_field_t PC13_SEL_f;
    };
    union
    {
        __IO uint32_t PC14_SEL;
        stc_gpio_pc14_sel_field_t PC14_SEL_f;
    };
    union
    {
        __IO uint32_t PC15_SEL;
        stc_gpio_pc15_sel_field_t PC15_SEL_f;
    };
    union
    {
        __IO uint32_t PD00_SEL;
        stc_gpio_pd00_sel_field_t PD00_SEL_f;
    };
    union
    {
        __IO uint32_t PD01_SEL;
        stc_gpio_pd01_sel_field_t PD01_SEL_f;
    };
    union
    {
        __IO uint32_t PD02_SEL;
        stc_gpio_pd02_sel_field_t PD02_SEL_f;
    };
    union
    {
        __IO uint32_t PD03_SEL;
        stc_gpio_pd03_sel_field_t PD03_SEL_f;
    };
    union
    {
        __IO uint32_t PD04_SEL;
        stc_gpio_pd04_sel_field_t PD04_SEL_f;
    };
    union
    {
        __IO uint32_t PD05_SEL;
        stc_gpio_pd05_sel_field_t PD05_SEL_f;
    };
    union
    {
        __IO uint32_t PD06_SEL;
        stc_gpio_pd06_sel_field_t PD06_SEL_f;
    };
    union
    {
        __IO uint32_t PD07_SEL;
        stc_gpio_pd07_sel_field_t PD07_SEL_f;
    };
    uint8_t RESERVED56[32];
    union
    {
        __IO uint32_t PADIR;
        stc_gpio_padir_field_t PADIR_f;
    };
    union
    {
        __IO uint32_t PAIN;
        stc_gpio_pain_field_t PAIN_f;
    };
    union
    {
        __IO uint32_t PAOUT;
        stc_gpio_paout_field_t PAOUT_f;
    };
    union
    {
        __IO uint32_t PAADS;
        stc_gpio_paads_field_t PAADS_f;
    };
    union
    {
        __IO uint32_t PABSET;
        stc_gpio_pabset_field_t PABSET_f;
    };
    union
    {
        __IO uint32_t PABCLR;
        stc_gpio_pabclr_field_t PABCLR_f;
    };
    union
    {
        __IO uint32_t PABSETCLR;
        stc_gpio_pabsetclr_field_t PABSETCLR_f;
    };
    union
    {
        __IO uint32_t PADR;
        stc_gpio_padr_field_t PADR_f;
    };
    union
    {
        __IO uint32_t PAPU;
        stc_gpio_papu_field_t PAPU_f;
    };
    union
    {
        __IO uint32_t PAPD;
        stc_gpio_papd_field_t PAPD_f;
    };
    uint8_t RESERVED66[4];
    union
    {
        __IO uint32_t PAOD;
        stc_gpio_paod_field_t PAOD_f;
    };
    union
    {
        __IO uint32_t PAHIE;
        stc_gpio_pahie_field_t PAHIE_f;
    };
    union
    {
        __IO uint32_t PALIE;
        stc_gpio_palie_field_t PALIE_f;
    };
    union
    {
        __IO uint32_t PARIE;
        stc_gpio_parie_field_t PARIE_f;
    };
    union
    {
        __IO uint32_t PAFIE;
        stc_gpio_pafie_field_t PAFIE_f;
    };
    union
    {
        __IO uint32_t PBDIR;
        stc_gpio_pbdir_field_t PBDIR_f;
    };
    union
    {
        __IO uint32_t PBIN;
        stc_gpio_pbin_field_t PBIN_f;
    };
    union
    {
        __IO uint32_t PBOUT;
        stc_gpio_pbout_field_t PBOUT_f;
    };
    union
    {
        __IO uint32_t PBADS;
        stc_gpio_pbads_field_t PBADS_f;
    };
    union
    {
        __IO uint32_t PBBSET;
        stc_gpio_pbbset_field_t PBBSET_f;
    };
    union
    {
        __IO uint32_t PBBCLR;
        stc_gpio_pbbclr_field_t PBBCLR_f;
    };
    union
    {
        __IO uint32_t PBBSETCLR;
        stc_gpio_pbbsetclr_field_t PBBSETCLR_f;
    };
    union
    {
        __IO uint32_t PBDR;
        stc_gpio_pbdr_field_t PBDR_f;
    };
    union
    {
        __IO uint32_t PBPU;
        stc_gpio_pbpu_field_t PBPU_f;
    };
    union
    {
        __IO uint32_t PBPD;
        stc_gpio_pbpd_field_t PBPD_f;
    };
    uint8_t RESERVED81[4];
    union
    {
        __IO uint32_t PBOD;
        stc_gpio_pbod_field_t PBOD_f;
    };
    union
    {
        __IO uint32_t PBHIE;
        stc_gpio_pbhie_field_t PBHIE_f;
    };
    union
    {
        __IO uint32_t PBLIE;
        stc_gpio_pblie_field_t PBLIE_f;
    };
    union
    {
        __IO uint32_t PBRIE;
        stc_gpio_pbrie_field_t PBRIE_f;
    };
    union
    {
        __IO uint32_t PBFIE;
        stc_gpio_pbfie_field_t PBFIE_f;
    };
    union
    {
        __IO uint32_t PCDIR;
        stc_gpio_pcdir_field_t PCDIR_f;
    };
    union
    {
        __IO uint32_t PCIN;
        stc_gpio_pcin_field_t PCIN_f;
    };
    union
    {
        __IO uint32_t PCOUT;
        stc_gpio_pcout_field_t PCOUT_f;
    };
    union
    {
        __IO uint32_t PCADS;
        stc_gpio_pcads_field_t PCADS_f;
    };
    union
    {
        __IO uint32_t PCBSET;
        stc_gpio_pcbset_field_t PCBSET_f;
    };
    union
    {
        __IO uint32_t PCBCLR;
        stc_gpio_pcbclr_field_t PCBCLR_f;
    };
    union
    {
        __IO uint32_t PCBSETCLR;
        stc_gpio_pcbsetclr_field_t PCBSETCLR_f;
    };
    union
    {
        __IO uint32_t PCDR;
        stc_gpio_pcdr_field_t PCDR_f;
    };
    union
    {
        __IO uint32_t PCPU;
        stc_gpio_pcpu_field_t PCPU_f;
    };
    union
    {
        __IO uint32_t PCPD;
        stc_gpio_pcpd_field_t PCPD_f;
    };
    uint8_t RESERVED96[4];
    union
    {
        __IO uint32_t PCOD;
        stc_gpio_pcod_field_t PCOD_f;
    };
    union
    {
        __IO uint32_t PCHIE;
        stc_gpio_pchie_field_t PCHIE_f;
    };
    union
    {
        __IO uint32_t PCLIE;
        stc_gpio_pclie_field_t PCLIE_f;
    };
    union
    {
        __IO uint32_t PCRIE;
        stc_gpio_pcrie_field_t PCRIE_f;
    };
    union
    {
        __IO uint32_t PCFIE;
        stc_gpio_pcfie_field_t PCFIE_f;
    };
    union
    {
        __IO uint32_t PDDIR;
        stc_gpio_pddir_field_t PDDIR_f;
    };
    union
    {
        __IO uint32_t PDIN;
        stc_gpio_pdin_field_t PDIN_f;
    };
    union
    {
        __IO uint32_t PDOUT;
        stc_gpio_pdout_field_t PDOUT_f;
    };
    union
    {
        __IO uint32_t PDADS;
        stc_gpio_pdads_field_t PDADS_f;
    };
    union
    {
        __IO uint32_t PDBSET;
        stc_gpio_pdbset_field_t PDBSET_f;
    };
    union
    {
        __IO uint32_t PDBCLR;
        stc_gpio_pdbclr_field_t PDBCLR_f;
    };
    union
    {
        __IO uint32_t PDBSETCLR;
        stc_gpio_pdbsetclr_field_t PDBSETCLR_f;
    };
    union
    {
        __IO uint32_t PDDR;
        stc_gpio_pddr_field_t PDDR_f;
    };
    union
    {
        __IO uint32_t PDPU;
        stc_gpio_pdpu_field_t PDPU_f;
    };
    union
    {
        __IO uint32_t PDPD;
        stc_gpio_pdpd_field_t PDPD_f;
    };
    uint8_t RESERVED111[4];
    union
    {
        __IO uint32_t PDOD;
        stc_gpio_pdod_field_t PDOD_f;
    };
    union
    {
        __IO uint32_t PDHIE;
        stc_gpio_pdhie_field_t PDHIE_f;
    };
    union
    {
        __IO uint32_t PDLIE;
        stc_gpio_pdlie_field_t PDLIE_f;
    };
    union
    {
        __IO uint32_t PDRIE;
        stc_gpio_pdrie_field_t PDRIE_f;
    };
    union
    {
        __IO uint32_t PDFIE;
        stc_gpio_pdfie_field_t PDFIE_f;
    };
    union
    {
        __IO uint32_t PA_STAT;
        stc_gpio_pa_stat_field_t PA_STAT_f;
    };
    uint8_t RESERVED117[12];
    union
    {
        __IO uint32_t PA_ICLR;
        stc_gpio_pa_iclr_field_t PA_ICLR_f;
    };
    uint8_t RESERVED118[44];
    union
    {
        __IO uint32_t PB_STAT;
        stc_gpio_pb_stat_field_t PB_STAT_f;
    };
    uint8_t RESERVED119[12];
    union
    {
        __IO uint32_t PB_ICLR;
        stc_gpio_pb_iclr_field_t PB_ICLR_f;
    };
    uint8_t RESERVED120[44];
    union
    {
        __IO uint32_t PC_STAT;
        stc_gpio_pc_stat_field_t PC_STAT_f;
    };
    uint8_t RESERVED121[12];
    union
    {
        __IO uint32_t PC_ICLR;
        stc_gpio_pc_iclr_field_t PC_ICLR_f;
    };
    uint8_t RESERVED122[44];
    union
    {
        __IO uint32_t PD_STAT;
        stc_gpio_pd_stat_field_t PD_STAT_f;
    };
    uint8_t RESERVED123[12];
    union
    {
        __IO uint32_t PD_ICLR;
        stc_gpio_pd_iclr_field_t PD_ICLR_f;
    };
    uint8_t RESERVED124[48];
    union
    {
        __IO uint32_t CTRL1;
        stc_gpio_ctrl1_field_t CTRL1_f;
    };
    union
    {
        __IO uint32_t CTRL2;
        stc_gpio_ctrl2_field_t CTRL2_f;
    };
    union
    {
        __IO uint32_t TIMGS;
        stc_gpio_timgs_field_t TIMGS_f;
    };
    union
    {
        __IO uint32_t TIMES;
        stc_gpio_times_field_t TIMES_f;
    };
    union
    {
        __IO uint32_t TIMCPS0;
        stc_gpio_timcps0_field_t TIMCPS0_f;
    };
    union
    {
        __IO uint32_t TIMCPS1;
        stc_gpio_timcps1_field_t TIMCPS1_f;
    };
    uint8_t RESERVED130[20];
    union
    {
        __IO uint32_t FLTCFG;
        stc_gpio_fltcfg_field_t FLTCFG_f;
    };
}M0P_GPIO_TypeDef;

typedef struct
{
    uint8_t RESERVED0[16];
    union
    {
        __IO uint32_t MCR;
        stc_hsi2c_mcr_field_t MCR_f;
    };
    union
    {
        __IO uint32_t MSR;
        stc_hsi2c_msr_field_t MSR_f;
    };
    union
    {
        __IO uint32_t MIER;
        stc_hsi2c_mier_field_t MIER_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_hsi2c_mscr_field_t MSCR_f;
    };
    uint8_t RESERVED4[4];
    union
    {
        __IO uint32_t MCFGR1;
        stc_hsi2c_mcfgr1_field_t MCFGR1_f;
    };
    union
    {
        __IO uint32_t MCFGR2;
        stc_hsi2c_mcfgr2_field_t MCFGR2_f;
    };
    union
    {
        __IO uint32_t MCFGR3;
        stc_hsi2c_mcfgr3_field_t MCFGR3_f;
    };
    union
    {
        __IO uint32_t MCCR0;
        stc_hsi2c_mccr0_field_t MCCR0_f;
    };
    union
    {
        __IO uint32_t MCCR1;
        stc_hsi2c_mccr1_field_t MCCR1_f;
    };
    union
    {
        __IO uint32_t MTDR;
        stc_hsi2c_mtdr_field_t MTDR_f;
    };
    union
    {
        __IO uint32_t MRDR;
        stc_hsi2c_mrdr_field_t MRDR_f;
    };
    union
    {
        __IO uint32_t MDMR;
        stc_hsi2c_mdmr_field_t MDMR_f;
    };
    uint8_t RESERVED12[8];
    union
    {
        __IO uint32_t MDER;
        stc_hsi2c_mder_field_t MDER_f;
    };
    uint8_t RESERVED13[192];
    union
    {
        __IO uint32_t SCR0;
        stc_hsi2c_scr0_field_t SCR0_f;
    };
    union
    {
        __IO uint32_t SSR;
        stc_hsi2c_ssr_field_t SSR_f;
    };
    union
    {
        __IO uint32_t SIER;
        stc_hsi2c_sier_field_t SIER_f;
    };
    union
    {
        __IO uint32_t SSCR;
        stc_hsi2c_sscr_field_t SSCR_f;
    };
    union
    {
        __IO uint32_t SCR1;
        stc_hsi2c_scr1_field_t SCR1_f;
    };
    union
    {
        __IO uint32_t SCR2;
        stc_hsi2c_scr2_field_t SCR2_f;
    };
    union
    {
        __IO uint32_t STAR;
        stc_hsi2c_star_field_t STAR_f;
    };
    union
    {
        __IO uint32_t STDR;
        stc_hsi2c_stdr_field_t STDR_f;
    };
    union
    {
        __IO uint32_t SRDR;
        stc_hsi2c_srdr_field_t SRDR_f;
    };
    uint8_t RESERVED22[8];
    union
    {
        __IO uint32_t SDER;
        stc_hsi2c_sder_field_t SDER_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_hsi2c_saddr_field_t SADDR_f;
    };
    uint8_t RESERVED24[12];
    union
    {
        __IO uint32_t SASR;
        stc_hsi2c_sasr_field_t SASR_f;
    };
}M0P_HSI2C_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t TMRUN;
        stc_i2c_tmrun_field_t TMRUN_f;
    };
    union
    {
        __IO uint32_t TM;
        stc_i2c_tm_field_t TM_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_i2c_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t DATA;
        stc_i2c_data_field_t DATA_f;
    };
    union
    {
        __IO uint32_t ADDR0;
        stc_i2c_addr0_field_t ADDR0_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_i2c_stat_field_t STAT_f;
    };
    uint8_t RESERVED6[8];
    union
    {
        __IO uint32_t ADDR1;
        stc_i2c_addr1_field_t ADDR1_f;
    };
    union
    {
        __IO uint32_t ADDR2;
        stc_i2c_addr2_field_t ADDR2_f;
    };
    union
    {
        __IO uint32_t MATCH;
        stc_i2c_match_field_t MATCH_f;
    };
}M0P_I2C_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t KR;
        stc_iwdt_kr_field_t KR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_iwdt_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t ARR;
        stc_iwdt_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_iwdt_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t WINR;
        stc_iwdt_winr_field_t WINR_f;
    };
}M0P_IWDT_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_lcd_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_lcd_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_lcd_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t INTCLR;
        stc_lcd_intclr_field_t INTCLR_f;
    };
    union
    {
        __IO uint32_t POEN0;
        stc_lcd_poen0_field_t POEN0_f;
    };
    union
    {
        __IO uint32_t POEN1;
        stc_lcd_poen1_field_t POEN1_f;
    };
    uint8_t RESERVED6[40];
    union
    {
        __IO uint32_t RAM0;
        stc_lcd_ram0_field_t RAM0_f;
    };
    union
    {
        __IO uint32_t RAM1;
        stc_lcd_ram1_field_t RAM1_f;
    };
    union
    {
        __IO uint32_t RAM2;
        stc_lcd_ram2_field_t RAM2_f;
    };
    union
    {
        __IO uint32_t RAM3;
        stc_lcd_ram3_field_t RAM3_f;
    };
    union
    {
        __IO uint32_t RAM4;
        stc_lcd_ram4_field_t RAM4_f;
    };
    union
    {
        __IO uint32_t RAM5;
        stc_lcd_ram5_field_t RAM5_f;
    };
    union
    {
        __IO uint32_t RAM6;
        stc_lcd_ram6_field_t RAM6_f;
    };
    union
    {
        __IO uint32_t RAM7;
        stc_lcd_ram7_field_t RAM7_f;
    };
    union
    {
        __IO uint32_t RAM8;
        stc_lcd_ram8_field_t RAM8_f;
    };
    union
    {
        __IO uint32_t RAM9;
        stc_lcd_ram9_field_t RAM9_f;
    };
    union
    {
        __IO uint32_t RAMA;
        stc_lcd_rama_field_t RAMA_f;
    };
    union
    {
        __IO uint32_t RAMB;
        stc_lcd_ramb_field_t RAMB_f;
    };
    union
    {
        __IO uint32_t RAMC;
        stc_lcd_ramc_field_t RAMC_f;
    };
    union
    {
        __IO uint32_t RAMD;
        stc_lcd_ramd_field_t RAMD_f;
    };
    union
    {
        __IO uint32_t RAME;
        stc_lcd_rame_field_t RAME_f;
    };
    union
    {
        __IO uint32_t RAMF;
        stc_lcd_ramf_field_t RAMF_f;
    };
}M0P_LCD_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CNT;
        stc_lptimer_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t ARR;
        stc_lptimer_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CMP;
        stc_lptimer_cmp_field_t CMP_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_lptimer_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_lptimer_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_lptimer_iclr_field_t ICLR_f;
    };
}M0P_LPTIMER_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SBUF;
        stc_lpuart_sbuf_field_t SBUF_f;
    };
    union
    {
        __IO uint32_t SCON;
        stc_lpuart_scon_field_t SCON_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_lpuart_saddr_field_t SADDR_f;
    };
    union
    {
        __IO uint32_t SADEN;
        stc_lpuart_saden_field_t SADEN_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_lpuart_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_lpuart_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t SCNT;
        stc_lpuart_scnt_field_t SCNT_f;
    };
    union
    {
        __IO uint32_t BSEL;
        stc_lpuart_bsel_field_t BSEL_f;
    };
    union
    {
        __IO uint32_t MODU;
        stc_lpuart_modu_field_t MODU_f;
    };
}M0P_LPUART_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_lvd_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_lvd_ifr_field_t IFR_f;
    };
}M0P_LVD_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_ram_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t ERRADDR;
        stc_ram_erraddr_field_t ERRADDR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_ram_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_ram_iclr_field_t ICLR_f;
    };
}M0P_RAM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t RESET_FLAG;
        stc_reset_flag_field_t RESET_FLAG_f;
    };
    uint8_t RESERVED1[8];
    union
    {
        __IO uint32_t PERI_RESET0;
        stc_reset_peri_reset0_field_t PERI_RESET0_f;
    };
    union
    {
        __IO uint32_t PERI_RESET1;
        stc_reset_peri_reset1_field_t PERI_RESET1_f;
    };
}M0P_RESET_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_rtc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_rtc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t SEC;
        stc_rtc_sec_field_t SEC_f;
    };
    union
    {
        __IO uint32_t MIN;
        stc_rtc_min_field_t MIN_f;
    };
    union
    {
        __IO uint32_t HOUR;
        stc_rtc_hour_field_t HOUR_f;
    };
    union
    {
        __IO uint32_t WEEK;
        stc_rtc_week_field_t WEEK_f;
    };
    union
    {
        __IO uint32_t DAY;
        stc_rtc_day_field_t DAY_f;
    };
    union
    {
        __IO uint32_t MON;
        stc_rtc_mon_field_t MON_f;
    };
    union
    {
        __IO uint32_t YEAR;
        stc_rtc_year_field_t YEAR_f;
    };
    uint8_t RESERVED9[12];
    union
    {
        __IO uint32_t COMPEN;
        stc_rtc_compen_field_t COMPEN_f;
    };
    union
    {
        __IO uint32_t HCOMP;
        stc_rtc_hcomp_field_t HCOMP_f;
    };
    uint8_t RESERVED11[4];
    union
    {
        __IO uint32_t CR2;
        stc_rtc_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t ALMA;
        stc_rtc_alma_field_t ALMA_f;
    };
    union
    {
        __IO uint32_t ALMB;
        stc_rtc_almb_field_t ALMB_f;
    };
    union
    {
        __IO uint32_t TSTR;
        stc_rtc_tstr_field_t TSTR_f;
    };
    union
    {
        __IO uint32_t TSDR;
        stc_rtc_tsdr_field_t TSDR_f;
    };
    union
    {
        __IO uint32_t WUTR;
        stc_rtc_wutr_field_t WUTR_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_rtc_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_rtc_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_rtc_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t WPR;
        stc_rtc_wpr_field_t WPR_f;
    };
}M0P_RTC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_spi_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_spi_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t HDOE;
        stc_spi_hdoe_field_t HDOE_f;
    };
    union
    {
        __IO uint32_t SSI;
        stc_spi_ssi_field_t SSI_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_spi_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_spi_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t DR;
        stc_spi_dr_field_t DR_f;
    };
}M0P_SPI_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SYSCTRL0;
        stc_sysctrl_sysctrl0_field_t SYSCTRL0_f;
    };
    union
    {
        __IO uint32_t SYSCTRL1;
        stc_sysctrl_sysctrl1_field_t SYSCTRL1_f;
    };
    union
    {
        __IO uint32_t SYSCTRL2;
        stc_sysctrl_sysctrl2_field_t SYSCTRL2_f;
    };
    union
    {
        __IO uint32_t RCH_CR;
        stc_sysctrl_rch_cr_field_t RCH_CR_f;
    };
    union
    {
        __IO uint32_t XTH_CR;
        stc_sysctrl_xth_cr_field_t XTH_CR_f;
    };
    union
    {
        __IO uint32_t RCL_CR;
        stc_sysctrl_rcl_cr_field_t RCL_CR_f;
    };
    union
    {
        __IO uint32_t XTL_CR;
        stc_sysctrl_xtl_cr_field_t XTL_CR_f;
    };
    uint8_t RESERVED7[4];
    union
    {
        __IO uint32_t PERI_CLKEN0;
        stc_sysctrl_peri_clken0_field_t PERI_CLKEN0_f;
    };
    union
    {
        __IO uint32_t PERI_CLKEN1;
        stc_sysctrl_peri_clken1_field_t PERI_CLKEN1_f;
    };
}M0P_SYSCTRL_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim0_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim0_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim0_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_tim0_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim0_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim0_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_tim0_mode0_dtr_field_t DTR_f;
    };
}M0P_TIM0_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_tim0_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_tim0_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim0_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim0_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim0_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim0_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_tim0_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_tim0_mode1_ccr0a_field_t CCR0A_f;
    };
}M0P_TIM0_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim0_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim0_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_tim0_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim0_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim0_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim0_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim0_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_tim0_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_tim0_mode23_crch0_field_t CRCH0_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t DTR;
        stc_tim0_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_tim0_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_tim0_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_tim0_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_tim0_mode23_ccr0b_field_t CCR0B_f;
    };
}M0P_TIM0_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim1_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim1_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim1_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_tim1_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim1_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim1_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_tim1_mode0_dtr_field_t DTR_f;
    };
}M0P_TIM1_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_tim1_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_tim1_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim1_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim1_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim1_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim1_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_tim1_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_tim1_mode1_ccr0a_field_t CCR0A_f;
    };
}M0P_TIM1_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim1_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim1_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_tim1_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim1_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim1_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim1_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim1_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_tim1_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_tim1_mode23_crch0_field_t CRCH0_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t DTR;
        stc_tim1_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_tim1_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_tim1_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_tim1_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_tim1_mode23_ccr0b_field_t CCR0B_f;
    };
}M0P_TIM1_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim2_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim2_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim2_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_tim2_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim2_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim2_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_tim2_mode0_dtr_field_t DTR_f;
    };
}M0P_TIM2_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_tim2_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_tim2_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim2_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim2_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim2_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim2_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_tim2_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_tim2_mode1_ccr0a_field_t CCR0A_f;
    };
}M0P_TIM2_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim2_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim2_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_tim2_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim2_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim2_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim2_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim2_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_tim2_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_tim2_mode23_crch0_field_t CRCH0_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t DTR;
        stc_tim2_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_tim2_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_tim2_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_tim2_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_tim2_mode23_ccr0b_field_t CCR0B_f;
    };
}M0P_TIM2_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim3_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim3_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim3_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_tim3_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim3_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim3_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_tim3_mode0_dtr_field_t DTR_f;
    };
}M0P_TIM3_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_tim3_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_tim3_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim3_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim3_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim3_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim3_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_tim3_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_tim3_mode1_ccr0a_field_t CCR0A_f;
    };
}M0P_TIM3_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim3_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim3_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_tim3_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim3_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim3_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim3_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim3_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_tim3_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_tim3_mode23_crch0_field_t CRCH0_f;
    };
    union
    {
        __IO uint32_t CRCH1;
        stc_tim3_mode23_crch1_field_t CRCH1_f;
    };
    union
    {
        __IO uint32_t CRCH2;
        stc_tim3_mode23_crch2_field_t CRCH2_f;
    };
    union
    {
        __IO uint32_t DTR;
        stc_tim3_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_tim3_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_tim3_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_tim3_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_tim3_mode23_ccr0b_field_t CCR0B_f;
    };
    union
    {
        __IO uint32_t CCR1A;
        stc_tim3_mode23_ccr1a_field_t CCR1A_f;
    };
    union
    {
        __IO uint32_t CCR1B;
        stc_tim3_mode23_ccr1b_field_t CCR1B_f;
    };
    union
    {
        __IO uint32_t CCR2A;
        stc_tim3_mode23_ccr2a_field_t CCR2A_f;
    };
    union
    {
        __IO uint32_t CCR2B;
        stc_tim3_mode23_ccr2b_field_t CCR2B_f;
    };
    union
    {
        __IO uint32_t CCR3A;
        stc_tim3_mode23_ccr3a_field_t CCR3A_f;
    };
    union
    {
        __IO uint32_t CRCH3A;
        stc_tim3_mode23_crch3a_field_t CRCH3A_f;
    };
    union
    {
        __IO uint32_t CCR3B;
        stc_tim3_mode23_ccr3b_field_t CCR3B_f;
    };
    union
    {
        __IO uint32_t CRCH3B;
        stc_tim3_mode23_crch3b_field_t CRCH3B_f;
    };
}M0P_TIM3_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_trng_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t MODE;
        stc_trng_mode_field_t MODE_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t DATA0;
        stc_trng_data0_field_t DATA0_f;
    };
    union
    {
        __IO uint32_t DATA1;
        stc_trng_data1_field_t DATA1_f;
    };
}M0P_TRNG_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR1;
        stc_usart_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_usart_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t CR3;
        stc_usart_cr3_field_t CR3_f;
    };
    union
    {
        __IO uint32_t BRR;
        stc_usart_brr_field_t BRR_f;
    };
    union
    {
        __IO uint32_t TOR;
        stc_usart_tor_field_t TOR_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_usart_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t TDR;
        stc_usart_tdr_field_t TDR_f;
    };
    union
    {
        __IO uint32_t IER;
        stc_usart_ier_field_t IER_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_usart_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t RDR;
        stc_usart_rdr_field_t RDR_f;
    };
    union
    {
        __IO uint32_t ADDR;
        stc_usart_addr_field_t ADDR_f;
    };
    union
    {
        __IO uint32_t ADDMR;
        stc_usart_addmr_field_t ADDMR_f;
    };
    union
    {
        __IO uint32_t BDR;
        stc_usart_bdr_field_t BDR_f;
    };
    uint8_t RESERVED13[188];
    union
    {
        __IO uint32_t IR;
        stc_usart_ir_field_t IR_f;
    };
}M0P_USART_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_vc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_vc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_vc_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_vc_ifr_field_t IFR_f;
    };
}M0P_VC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t VCTRIM;
        stc_vctrim_field_t VCTRIM_f;
    };
}M0P_VCTRIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_wwdt_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_wwdt_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t SR;
        stc_wwdt_sr_field_t SR_f;
    };
}M0P_WWDT_TypeDef;



#define M0P_PERIPH_BASE                        (0x40000000UL)
#define M0P_ADC_BASE                           (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_AES_BASE                           (M0P_PERIPH_BASE + 0x00021400UL)
#define M0P_CRC_BASE                           (M0P_PERIPH_BASE + 0x00020800UL)
#define M0P_CTRIM_BASE                         (M0P_PERIPH_BASE + 0x00009000UL)
#define M0P_DEBUG_ACTIVE_BASE                  (M0P_PERIPH_BASE + 0x00021838UL)
#define M0P_DMAC_BASE                          (M0P_PERIPH_BASE + 0x00021000UL)
#define M0P_FLASH_BASE                         (M0P_PERIPH_BASE + 0x00020000UL)
#define M0P_GPIO_BASE                          (M0P_PERIPH_BASE + 0x00020C00UL)
#define M0P_HSI2C_BASE                         (M0P_PERIPH_BASE + 0x0000BC00UL)
#define M0P_I2C0_BASE                          (M0P_PERIPH_BASE + 0x00000400UL)
#define M0P_I2C1_BASE                          (M0P_PERIPH_BASE + 0x00008400UL)
#define M0P_IWDT_BASE                          (M0P_PERIPH_BASE + 0x00001080UL)
#define M0P_LCD_BASE                           (M0P_PERIPH_BASE + 0x00009C00UL)
#define M0P_LPTIMER0_BASE                      (M0P_PERIPH_BASE + 0x00000C00UL)
#define M0P_LPTIMER1_BASE                      (M0P_PERIPH_BASE + 0x00003C00UL)
#define M0P_LPUART0_BASE                       (M0P_PERIPH_BASE + 0x00000000UL)
#define M0P_LPUART1_BASE                       (M0P_PERIPH_BASE + 0x00008000UL)
#define M0P_LPUART2_BASE                       (M0P_PERIPH_BASE + 0x0000B400UL)
#define M0P_LVD_BASE                           (M0P_PERIPH_BASE + 0x00002C00UL)
#define M0P_RAM_BASE                           (M0P_PERIPH_BASE + 0x00020400UL)
#define M0P_RESET_BASE                         (M0P_PERIPH_BASE + 0x0002181CUL)
#define M0P_RTC_BASE                           (M0P_PERIPH_BASE + 0x00001400UL)
#define M0P_SPI0_BASE                          (M0P_PERIPH_BASE + 0x00000800UL)
#define M0P_SPI1_BASE                          (M0P_PERIPH_BASE + 0x00008800UL)
#define M0P_SYSCTRL_BASE                       (M0P_PERIPH_BASE + 0x00021800UL)
#define M0P_TIM0_MODE0_BASE                    (M0P_PERIPH_BASE + 0x00003000UL)
#define M0P_TIM0_MODE1_BASE                    (M0P_PERIPH_BASE + 0x00003000UL)
#define M0P_TIM0_MODE23_BASE                   (M0P_PERIPH_BASE + 0x00003000UL)
#define M0P_TIM1_MODE0_BASE                    (M0P_PERIPH_BASE + 0x00003400UL)
#define M0P_TIM1_MODE1_BASE                    (M0P_PERIPH_BASE + 0x00003400UL)
#define M0P_TIM1_MODE23_BASE                   (M0P_PERIPH_BASE + 0x00003400UL)
#define M0P_TIM2_MODE0_BASE                    (M0P_PERIPH_BASE + 0x00003800UL)
#define M0P_TIM2_MODE1_BASE                    (M0P_PERIPH_BASE + 0x00003800UL)
#define M0P_TIM2_MODE23_BASE                   (M0P_PERIPH_BASE + 0x00003800UL)
#define M0P_TIM3_MODE0_BASE                    (M0P_PERIPH_BASE + 0x00009800UL)
#define M0P_TIM3_MODE1_BASE                    (M0P_PERIPH_BASE + 0x00009800UL)
#define M0P_TIM3_MODE23_BASE                   (M0P_PERIPH_BASE + 0x00009800UL)
#define M0P_TRNG_BASE                          (M0P_PERIPH_BASE + 0x00008C00UL)
#define M0P_USART0_BASE                        (M0P_PERIPH_BASE + 0x0000A000UL)
#define M0P_USART1_BASE                        (M0P_PERIPH_BASE + 0x0000A400UL)
#define M0P_VC0_BASE                           (M0P_PERIPH_BASE + 0x00002800UL)
#define M0P_VC1_BASE                           (M0P_PERIPH_BASE + 0x00002810UL)
#define M0P_VCTRIM_BASE                        (M0P_PERIPH_BASE + 0x00002820UL)
#define M0P_WWDT_BASE                          (M0P_PERIPH_BASE + 0x0000B800UL)


#define M0P_ADC                                ((M0P_ADC_TypeDef *)0x40002400UL)
#define M0P_AES                                ((M0P_AES_TypeDef *)0x40021400UL)
#define M0P_CRC                                ((M0P_CRC_TypeDef *)0x40020800UL)
#define M0P_CTRIM                              ((M0P_CTRIM_TypeDef *)0x40009000UL)
#define M0P_DEBUG_ACTIVE                       ((M0P_DEBUG_ACTIVE_TypeDef *)0x40021838UL)
#define M0P_DMAC                               ((M0P_DMAC_TypeDef *)0x40021000UL)
#define M0P_FLASH                              ((M0P_FLASH_TypeDef *)0x40020000UL)
#define M0P_GPIO                               ((M0P_GPIO_TypeDef *)0x40020C00UL)
#define M0P_HSI2C                              ((M0P_HSI2C_TypeDef *)0x4000BC00UL)
#define M0P_I2C0                               ((M0P_I2C_TypeDef *)0x40000400UL)
#define M0P_I2C1                               ((M0P_I2C_TypeDef *)0x40008400UL)
#define M0P_IWDT                               ((M0P_IWDT_TypeDef *)0x40001080UL)
#define M0P_LCD                                ((M0P_LCD_TypeDef *)0x40009C00UL)
#define M0P_LPTIMER0                           ((M0P_LPTIMER_TypeDef *)0x40000C00UL)
#define M0P_LPTIMER1                           ((M0P_LPTIMER_TypeDef *)0x40003C00UL)
#define M0P_LPUART0                            ((M0P_LPUART_TypeDef *)0x40000000UL)
#define M0P_LPUART1                            ((M0P_LPUART_TypeDef *)0x40008000UL)
#define M0P_LPUART2                            ((M0P_LPUART_TypeDef *)0x4000B400UL)
#define M0P_LVD                                ((M0P_LVD_TypeDef *)0x40002C00UL)
#define M0P_RAM                                ((M0P_RAM_TypeDef *)0x40020400UL)
#define M0P_RESET                              ((M0P_RESET_TypeDef *)0x4002181CUL)
#define M0P_RTC                                ((M0P_RTC_TypeDef *)0x40001400UL)
#define M0P_SPI0                               ((M0P_SPI_TypeDef *)0x40000800UL)
#define M0P_SPI1                               ((M0P_SPI_TypeDef *)0x40008800UL)
#define M0P_SYSCTRL                            ((M0P_SYSCTRL_TypeDef *)0x40021800UL)
#define M0P_TIM0_MODE0                         ((M0P_TIM0_MODE0_TypeDef *)0x40003000UL)
#define M0P_TIM0_MODE1                         ((M0P_TIM0_MODE1_TypeDef *)0x40003000UL)
#define M0P_TIM0_MODE23                        ((M0P_TIM0_MODE23_TypeDef *)0x40003000UL)
#define M0P_TIM1_MODE0                         ((M0P_TIM1_MODE0_TypeDef *)0x40003400UL)
#define M0P_TIM1_MODE1                         ((M0P_TIM1_MODE1_TypeDef *)0x40003400UL)
#define M0P_TIM1_MODE23                        ((M0P_TIM1_MODE23_TypeDef *)0x40003400UL)
#define M0P_TIM2_MODE0                         ((M0P_TIM2_MODE0_TypeDef *)0x40003800UL)
#define M0P_TIM2_MODE1                         ((M0P_TIM2_MODE1_TypeDef *)0x40003800UL)
#define M0P_TIM2_MODE23                        ((M0P_TIM2_MODE23_TypeDef *)0x40003800UL)
#define M0P_TIM3_MODE0                         ((M0P_TIM3_MODE0_TypeDef *)0x40009800UL)
#define M0P_TIM3_MODE1                         ((M0P_TIM3_MODE1_TypeDef *)0x40009800UL)
#define M0P_TIM3_MODE23                        ((M0P_TIM3_MODE23_TypeDef *)0x40009800UL)
#define M0P_TRNG                               ((M0P_TRNG_TypeDef *)0x40008C00UL)
#define M0P_USART0                             ((M0P_USART_TypeDef *)0x4000A000UL)
#define M0P_USART1                             ((M0P_USART_TypeDef *)0x4000A400UL)
#define M0P_VC0                                ((M0P_VC_TypeDef *)0x40002800UL)
#define M0P_VC1                                ((M0P_VC_TypeDef *)0x40002810UL)
#define M0P_VCTRIM                             ((M0P_VCTRIM_TypeDef *)0x40002820UL)
#define M0P_WWDT                               ((M0P_WWDT_TypeDef *)0x4000B800UL)


#ifdef __cplusplus
}
#endif

#endif /* __HC32L12X_H__ */

