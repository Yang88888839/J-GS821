/**
 *******************************************************************************
 * @file  interrupts_hc32l12x.c
 * @brief Source file for INTERRUPTS functions
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
#include "ddl.h"
#include "interrupts_hc32l12x.h"

/*******************************************************************************
 *                       IRQ WEAK DEFINE
 ******************************************************************************/
__WEAK void SysTick_IRQHandler(void);
__WEAK void PortA_IRQHandler(void);
__WEAK void PortB_IRQHandler(void);
__WEAK void PortC_IRQHandler(void);
__WEAK void PortD_IRQHandler(void);
__WEAK void Dmac_IRQHandler(void);
__WEAK void Tim3_IRQHandler(void);
__WEAK void Usart0_IRQHandler(void);
__WEAK void Usart1_IRQHandler(void);
__WEAK void LpUart0_IRQHandler(void);
__WEAK void LpUart1_IRQHandler(void);
__WEAK void LpUart2_IRQHandler(void);
__WEAK void Spi0_IRQHandler(void);
__WEAK void Spi1_IRQHandler(void);
__WEAK void I2c0_IRQHandler(void);
__WEAK void I2c1_IRQHandler(void);
__WEAK void Hsi2c_IRQHandler(void);
__WEAK void Tim0_IRQHandler(void);
__WEAK void Tim1_IRQHandler(void);
__WEAK void Tim2_IRQHandler(void);
__WEAK void LpTim0_IRQHandler(void);
__WEAK void LpTim1_IRQHandler(void);
__WEAK void Wwdt_IRQHandler(void);
__WEAK void Iwdt_IRQHandler(void);
__WEAK void Rtc_IRQHandler(void);
__WEAK void Adc_IRQHandler(void);
__WEAK void Vc0_IRQHandler(void);
__WEAK void Vc1_IRQHandler(void);
__WEAK void Lvd_IRQHandler(void);
__WEAK void Lcd_IRQHandler(void);
__WEAK void Flash_IRQHandler(void);
__WEAK void Ram_IRQHandler(void);
__WEAK void Ctrim_IRQHandler(void);
__WEAK void Clkdet_IRQHandler(void);

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup INT_Global_Functions INT全局函数定义
 * @{
 */

/**
 * @brief NVIC 中断使能
 *
 * @param [in]  enIrq          中断号枚举类型
 * @param [in]  enLevel        中断优先级枚举类型
 * @param [in]  bEn            中断开关
 * @retval None
 */
void EnableNvic(IRQn_Type enIrq, en_irq_level_t enLevel, boolean_t bEn)
{
    NVIC_ClearPendingIRQ(enIrq);
    NVIC_SetPriority(enIrq, enLevel);
    if (TRUE == bEn)
    {
        NVIC_EnableIRQ(enIrq);
    }
    else
    {
        NVIC_DisableIRQ(enIrq);
    }
}

/**
 * @brief NVIC hardware fault 中断实现
 * @param [in] None
 * @retval None
 */
void HardFault_Handler(void)
{    
    volatile int a = 0;

    while( 0 == a)
    {
        ;
    }
}


/**
 * @brief NVIC SysTick 中断实现
 * @param [in] None
 * @retval None
 */
//void SysTick_Handler(void)
//{
//   SysTick_IRQHandler();
//}

/**
 * @brief GPIO PortA 中断处理函数
 * @param [in] None
 * @retval None
 */
void PORTA_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTA)    
    PortA_IRQHandler();
#endif    
}

/**
 * @brief GPIO PortB 中断处理函数
 * @param [in] None
 * @retval None
 */
void PORTB_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTB)    
    PortB_IRQHandler();
#endif    
}

/**
 * @brief GPIO PortC 中断处理函数
 * @param [in] None
 * @retval None
 */
void PORTC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTC)    
    PortC_IRQHandler();
#endif
}

/**
 * @brief GPIO PortD 中断处理函数
 * @param [in] None
 * @retval None
 */
void PORTD_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_PORTD)    
    PortD_IRQHandler();
#endif  
}

/**
 * @brief DMAC  中断处理函数
 * @param [in] None
 * @retval None
 */
void DMAC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_DMAC)    
    Dmac_IRQHandler();
#endif    
}

/**
 * @brief TIM3 中断处理函数
 * @param [in] None
 * @retval None
 */
void TIM3_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM3)    
    Tim3_IRQHandler();
#endif
}

/**
 * @brief USART0 中断处理函数
 * @param [in] None
 * @retval None
 */
void USART0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_USART0)    
    Usart0_IRQHandler();
#endif 
}

/**
 * @brief USART1 中断处理函数
 * @param [in] None
 * @retval None
 */
void USART1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_USART1)    
    Usart1_IRQHandler();
#endif  
}

/**
 * @brief LPUART0 低功耗串口0 中断处理函数
 * @param [in] None
 * @retval None
 */
void LPUART0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPUART0)    
    LpUart0_IRQHandler();
#endif    
}

/**
 * @brief LPUART1 低功耗串口1 中断处理函数
 * @param [in] None
 * @retval None
 */
void LPUART1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPUART1)    
    LpUart1_IRQHandler();
#endif
}

/**
 * @brief SPI0 中断处理函数
 * @param [in] None
 * @retval None
 */
void SPI0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_SPI0)    
    Spi0_IRQHandler();
#endif
}

/**
 * @brief SPI1 中断处理函数
 * @param [in] None
 * @retval None
 */
void SPI1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_SPI1)    
    Spi1_IRQHandler();
#endif
}

/**
 * @brief I2C0 中断处理函数
 * @param [in] None
 * @retval None
 */
void I2C0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_I2C0)    
    I2c0_IRQHandler();
#endif    
}

/**
 * @brief I2C1 中断处理函数
 * @param [in] None
 * @retval None
 */
void I2C1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_I2C1)    
    I2c1_IRQHandler();
#endif
}

/**
 * @brief TIM0 中断处理函数
 * @param [in] None
 * @retval None
 */
void TIM0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM0)    
    Tim0_IRQHandler();
#endif
}

/**
 * @brief TIM1 中断处理函数
 * @param [in] None
 * @retval None
 */
void TIM1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM1)    
    Tim1_IRQHandler();
#endif
}

/**
 * @brief TIM2 中断处理函数
 * @param [in] None
 * @retval None
 */
void TIM2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_TIM2)    
    Tim2_IRQHandler();
#endif
}

/**
 * @brief LPTIM0/1 低功耗时钟 中断处理函数
 * @param [in] None
 * @retval None
 */
void LPTIM0_1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPTIM0)
    LpTim0_IRQHandler();
#endif
    
#if (INT_CALLBACK_ON == INT_CALLBACK_LPTIM1)
    LpTim1_IRQHandler();
#endif
}

/**
 * @brief HSI2C 中断处理函数
 * @param [in] None
 * @retval None
 */
void HSI2C_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_HSI2C)    
    Hsi2c_IRQHandler();
#endif
}

/**
 * @brief LPUART2 中断处理函数
 * @param [in] None
 * @retval None
 */
void LPUART2_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LPUART2)
    LpUart2_IRQHandler();
#endif
}

/**
 * @brief WWDT 中断处理函数
 * @param [in] None
 * @retval None
 */
void WWDT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_WWDT)
    Wwdt_IRQHandler();
#endif
}

/**
 * @brief IWDT 中断处理函数
 * @param [in] None
 * @retval None
 */
void IWDT_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_IWDT)
    Iwdt_IRQHandler();
#endif
}

/**
 * @brief RTC 中断处理函数
 * @param [in] None
 * @retval None
 */
void RTC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_RTC)
    Rtc_IRQHandler();
#endif
}

/**
 * @brief ADC 中断处理函数
 * @param [in] None
 * @retval None
 */
void ADC_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_ADC)
    Adc_IRQHandler();
#endif
}

/**
 * @brief VC0 中断处理函数
 * @param [in] None
 * @retval None
 */
void VC0_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_VC0)
    Vc0_IRQHandler();
#endif
}

/**
 * @brief VC1 中断处理函数
 * @param [in] None
 * @retval None
 */
void VC1_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_VC1)
    Vc1_IRQHandler();
#endif
}

/**
 * @brief LVD 中断处理函数
 * @param [in] None
 * @retval None
 */
void LVD_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LVD)
    Lvd_IRQHandler();    
#endif
}

/**
 * @brief LCD 中断处理函数
 * @param [in] None
 * @retval None
 */
void LCD_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_LCD)
    Lcd_IRQHandler();
#endif
}

/**
 * @brief FLASH/RAM 中断处理函数
 * @param [in] None
 * @retval None
 */
void FLASH_RAM_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_FLASH)
    Flash_IRQHandler();
#endif    
    
#if (INT_CALLBACK_ON == INT_CALLBACK_RAM)
    Ram_IRQHandler();
#endif
}

/**
 * @brief CTRIM/CLKDET 中断处理函数
 * @param [in] None
 * @retval None
 */
void CTRIM_CLKDET_IRQHandler(void)
{
#if (INT_CALLBACK_ON == INT_CALLBACK_CTRIM)
    Ctrim_IRQHandler();
#endif
#if (INT_CALLBACK_ON == INT_CALLBACK_CLKDET)
    Clkdet_IRQHandler();
#endif
}

/**
 * @}
 */


/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
