;*******************************************************************************
; Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
;
; This software component is licensed by XHSC under BSD 3-Clause license
; (the "License"); You may not use this file except in compliance with the
; License. You may obtain a copy of the License at:
;                    opensource.org/licenses/BSD-3-Clause
;
;/
;/*****************************************************************************/
;/*  Startup for IAR                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2025-04-23                                                   */
;/*  Target-mcu  HC32L12x                                                     */
;/*****************************************************************************/


                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table
                
                SECTION .intvec:CODE:ROOT(8)
                DATA
__vector_table  
                DCD     sfe(CSTACK)               ; Top of Stack
                DCD     Reset_Handler             ; Reset
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

; Numbered IRQ handler vectors

; Note: renaming to device dependent ISR function names are done in

                DCD     PORTA_IRQHandler
                DCD     PORTB_IRQHandler
                DCD     PORTC_IRQHandler
                DCD     PORTD_IRQHandler
                DCD     DMAC_IRQHandler
                DCD     TIM3_IRQHandler
                DCD     USART0_IRQHandler
                DCD     USART1_IRQHandler
                DCD     LPUART0_IRQHandler
                DCD     LPUART1_IRQHandler
                DCD     SPI0_IRQHandler
                DCD     SPI1_IRQHandler
                DCD     I2C0_IRQHandler
                DCD     I2C1_IRQHandler
                DCD     TIM0_IRQHandler
                DCD     TIM1_IRQHandler
                DCD     TIM2_IRQHandler
                DCD     LPTIM0_1_IRQHandler
                DCD     HSI2C_IRQHandler
                DCD     LPUART2_IRQHandler
                DCD     Dummy_IRQHandler
                DCD     WWDT_IRQHandler
                DCD     IWDT_IRQHandler
                DCD     RTC_IRQHandler
                DCD     ADC_IRQHandler
                DCD     Dummy_IRQHandler
                DCD     VC0_IRQHandler
                DCD     VC1_IRQHandler
                DCD     LVD_IRQHandler
                DCD     LCD_IRQHandler
                DCD     FLASH_RAM_IRQHandler
                DCD     CTRIM_CLKDET_IRQHandler


                THUMB

                PUBWEAK Reset_Handler
                SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
                ;reset NVIC if in rom debug
                LDR     R0, =0x20000000
                LDR     R2, =0x0              ; vector offset
                cmp     PC, R0
                bls     ROMCODE
              
              ; ram code base address. 
                ADD     R2, R0,R2
ROMCODE
              ; reset Vector table address.
                LDR     R0, =0xE000ED08
                STR     R2, [R0]
                
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK NMI_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
                B       HardFault_Handler


                PUBWEAK SVC_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
                B       SVC_Handler

                PUBWEAK PendSV_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
                B       SysTick_Handler

                PUBWEAK PORTA_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PORTA_IRQHandler
                B       PORTA_IRQHandler


                PUBWEAK PORTB_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PORTB_IRQHandler
                B       PORTB_IRQHandler


                PUBWEAK PORTC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PORTC_IRQHandler
                B       PORTC_IRQHandler


                PUBWEAK PORTD_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PORTD_IRQHandler
                B       PORTD_IRQHandler


                PUBWEAK DMAC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMAC_IRQHandler
                B       DMAC_IRQHandler


                PUBWEAK TIM3_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
                B       TIM3_IRQHandler


                PUBWEAK USART0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART0_IRQHandler
                B       USART0_IRQHandler


                PUBWEAK USART1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
                B       USART1_IRQHandler


                PUBWEAK LPUART0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LPUART0_IRQHandler
                B       LPUART0_IRQHandler


                PUBWEAK LPUART1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LPUART1_IRQHandler
                B       LPUART1_IRQHandler


                PUBWEAK SPI0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
                B       SPI0_IRQHandler


                PUBWEAK SPI1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
                B       SPI1_IRQHandler


                PUBWEAK I2C0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_IRQHandler
                B       I2C0_IRQHandler


                PUBWEAK I2C1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
                B       I2C1_IRQHandler


                PUBWEAK TIM0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM0_IRQHandler
                B       TIM0_IRQHandler


                PUBWEAK TIM1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_IRQHandler
                B       TIM1_IRQHandler


                PUBWEAK TIM2_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
                B       TIM2_IRQHandler


                PUBWEAK LPTIM0_1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM0_1_IRQHandler
                B       LPTIM0_1_IRQHandler


                PUBWEAK HSI2C_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
HSI2C_IRQHandler
                B       HSI2C_IRQHandler


                PUBWEAK LPUART2_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LPUART2_IRQHandler
                B       LPUART2_IRQHandler


                PUBWEAK Dummy_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
Dummy_IRQHandler
                B       Dummy_IRQHandler


                PUBWEAK WWDT_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
WWDT_IRQHandler
                B       WWDT_IRQHandler


                PUBWEAK IWDT_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
IWDT_IRQHandler
                B       IWDT_IRQHandler


                PUBWEAK RTC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
                B       RTC_IRQHandler


                PUBWEAK ADC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
                B       ADC_IRQHandler


;                PUBWEAK Dummy_IRQHandler
;                SECTION .text:CODE:NOROOT:REORDER(1)
;Dummy_IRQHandler
;                B       Dummy_IRQHandler


                PUBWEAK VC0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
VC0_IRQHandler
                B       VC0_IRQHandler


                PUBWEAK VC1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
VC1_IRQHandler
                B       VC1_IRQHandler


                PUBWEAK LVD_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
                B       LVD_IRQHandler


                PUBWEAK LCD_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LCD_IRQHandler
                B       LCD_IRQHandler


                PUBWEAK FLASH_RAM_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_RAM_IRQHandler
                B       FLASH_RAM_IRQHandler


                PUBWEAK CTRIM_CLKDET_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
CTRIM_CLKDET_IRQHandler
                B       CTRIM_CLKDET_IRQHandler



                
                
                END
