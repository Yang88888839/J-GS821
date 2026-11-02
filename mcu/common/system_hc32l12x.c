/**
 *******************************************************************************
 * @file  system_hc32l12x.c
 * @brief Source file for SYSTEM functions
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

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"
#include "hc32l12x.h"
#include "system_hc32l12x.h"
#include "sysctrl.h"

/******************************************************************************/
/* Global pre-processor symbols/macros ('define')                             */
/******************************************************************************/
#define VECT_TAB_OFFSET                ( 0x00003000 )
/**
 * @brief  System Clock Frequency (Core Clock) Variable according CMSIS
 */
uint32_t SystemCoreClock = 4000000;

/**
 * @brief  Update SystemCoreClock variable
 * @retval None
 */
void SystemCoreClockUpdate (void)
{
    SystemCoreClock = Sysctrl_GetHClkFreq();
}


/**
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 * @param [in] None
 * @retval None
 */
void SystemInit(void)
{
    //ÖÐ¶ÏÏòÁ¿Æ«ÒÆ
	(*((volatile uint32_t*) (SCB_BASE + 0x08)))  = VECT_TAB_OFFSET;
	//------------------------------------------------------------    
	M0P_SYSCTRL->RCL_CR = (*((volatile uint32_t*) (0x00101BA8ul)));
    M0P_SYSCTRL->RCH_CR = (*((volatile uint32_t*) (0x00101BBCul)));
    SystemCoreClockUpdate();
    
    //SysTick->LOAD = 0xFFFFFF;
    //SysTick->VAL  = 0;
	//SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;    
}


#if defined (__CC_ARM)
extern int32_t $Super$$main(void);
/* re-define main function */
int $Sub$$main(void)
{
    SystemInit();
    $Super$$main();
    return 0;
}
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
extern int32_t $Super$$main(void);
/* re-define main function */
int $Sub$$main(void)
{
    SystemInit();
    $Super$$main();
    return 0;
}
#elif defined(__ICCARM__)
extern int32_t main(void);
/* __low_level_init will auto called by IAR cstartup */
extern void __iar_data_init3(void);
int __low_level_init(void)
{
    // call IAR table copy function.
    __iar_data_init3();
    SystemInit();
    main();
    return 0;
}
#endif

