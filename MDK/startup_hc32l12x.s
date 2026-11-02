;/******************************************************************************
;*  
;* Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
;* 
;* This software component is licensed by XHSC under BSD 3-Clause license
;* (the "License"); You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                    opensource.org/licenses/BSD-3-Clause
;* 
;*/
;/*****************************************************************************/

;/*****************************************************************************/
;/*  Startup for ARM                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2025-04-23                                                   */
;/*  Target-mcu  HC32L12x                                                     */
;/*****************************************************************************/

; Stack Configuration
; Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors                       
                DCD     __initial_sp              ; Top of Stack
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

                

__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

               ;reset NVIC if in rom debug
                LDR     R0, =0x20000000
                LDR     R2, =0x0
                MOVS    R1, #0                 ; for warning, 
                ADD     R1, PC,#0              ; for A1609W, 
                CMP     R1, R0
                BLS     RAMCODE

              ; ram code base address. 
                ADD     R2, R0,R2
RAMCODE
              ; reset Vector table address.
                LDR     R0, =0xE000ED08 
                STR     R2, [R0]

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
                
                
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  PORTA_IRQHandler              [WEAK]
                EXPORT  PORTB_IRQHandler              [WEAK]
                EXPORT  PORTC_IRQHandler              [WEAK]
                EXPORT  PORTD_IRQHandler              [WEAK]
                EXPORT  DMAC_IRQHandler               [WEAK]
                EXPORT  TIM3_IRQHandler               [WEAK]
                EXPORT  USART0_IRQHandler             [WEAK]
                EXPORT  USART1_IRQHandler             [WEAK]
                EXPORT  LPUART0_IRQHandler            [WEAK]
                EXPORT  LPUART1_IRQHandler            [WEAK]
                EXPORT  SPI0_IRQHandler               [WEAK]
                EXPORT  SPI1_IRQHandler               [WEAK]
                EXPORT  I2C0_IRQHandler               [WEAK]
                EXPORT  I2C1_IRQHandler               [WEAK]
                EXPORT  TIM0_IRQHandler               [WEAK]
                EXPORT  TIM1_IRQHandler               [WEAK]
                EXPORT  TIM2_IRQHandler               [WEAK]
                EXPORT  LPTIM0_1_IRQHandler           [WEAK]
                EXPORT  HSI2C_IRQHandler              [WEAK]
				EXPORT  LPUART2_IRQHandler            [WEAK]
                EXPORT  Dummy_IRQHandler              [WEAK]
                EXPORT  WWDT_IRQHandler               [WEAK]
                EXPORT  IWDT_IRQHandler               [WEAK]
                EXPORT  RTC_IRQHandler                [WEAK]
                EXPORT  ADC_IRQHandler                [WEAK]
                EXPORT  VC0_IRQHandler                [WEAK]
                EXPORT  VC1_IRQHandler                [WEAK]
                EXPORT  LVD_IRQHandler                [WEAK]
                EXPORT  LCD_IRQHandler                [WEAK]
                EXPORT  FLASH_RAM_IRQHandler          [WEAK]
                EXPORT  CTRIM_CLKDET_IRQHandler       [WEAK]
PORTA_IRQHandler
PORTB_IRQHandler
PORTC_IRQHandler
PORTD_IRQHandler
DMAC_IRQHandler
TIM3_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
LPUART0_IRQHandler
LPUART1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
TIM0_IRQHandler
TIM1_IRQHandler
TIM2_IRQHandler
LPTIM0_1_IRQHandler
HSI2C_IRQHandler
LPUART2_IRQHandler
Dummy_IRQHandler
WWDT_IRQHandler
IWDT_IRQHandler
RTC_IRQHandler
ADC_IRQHandler
VC0_IRQHandler
VC1_IRQHandler
LVD_IRQHandler
LCD_IRQHandler
FLASH_RAM_IRQHandler
CTRIM_CLKDET_IRQHandler

                
               B .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
