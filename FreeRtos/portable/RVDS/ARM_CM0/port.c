/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the ARM CM0 port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"

#include "hc32l12x.h"
#include "system_hc32l12x.h"
#include "sysctrl.h"
#include "task.h"

/* Constants required to manipulate the NVIC. */
#define portNVIC_SYSTICK_CTRL			( ( volatile uint32_t * ) 0xe000e010 )
#define portNVIC_SYSTICK_LOAD			( ( volatile uint32_t * ) 0xe000e014 )
#define portNVIC_SYSTICK_CURRENT_VALUE	( ( volatile uint32_t * ) 0xe000e018 )
#define portNVIC_INT_CTRL			( ( volatile uint32_t *) 0xe000ed04 )
#define portNVIC_SYSPRI2			( ( volatile uint32_t *) 0xe000ed20 )
#define portNVIC_SYSTICK_CLK		0x00000004
#define portNVIC_SYSTICK_INT		0x00000002
#define portNVIC_SYSTICK_ENABLE		0x00000001
#define portNVIC_PENDSVSET			0x10000000
#define portMIN_INTERRUPT_PRIORITY	( 255UL )
#define portNVIC_PENDSV_PRI			( portMIN_INTERRUPT_PRIORITY << 16UL )
#define portNVIC_SYSTICK_PRI		( portMIN_INTERRUPT_PRIORITY << 24UL )

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR			( 0x01000000 )

/* Constants used with memory barrier intrinsics. */
#define portSY_FULL_READ_WRITE		( 15 )

/* Each task maintains its own interrupt status in the critical nesting
variable. */
//static UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * Setup the timer to generate the tick interrupts.
 */
static void prvSetupTimerInterrupt( void );

/*
 * Exception handlers.
 */
void xPortPendSVHandler( void );
void xPortSysTickHandler( void );
void vPortSVCHandler( void );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
static void prvPortStartFirstTask( void );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
static void prvTaskExitError( void )
{
    /* 函数停止在这里 */
    for(;;);
}
/*------------------------------------------------------------------------------------
Function:  
------------------------------------------------------------------------------------*/
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode )
{
	/* Simulate the stack frame as it would be created by a context switch
	interrupt. */
	pxTopOfStack--; /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
	*pxTopOfStack = portINITIAL_XPSR;	/* xPSR */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) pxCode;	/* PC */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) prvTaskExitError;	/* LR */
	pxTopOfStack -= 5;	/* R12, R3, R2 and R1. */
	//*pxTopOfStack = ( StackType_t ) pvParameters;	/* R0 */
	pxTopOfStack -= 8; /* R11..R4. */

	return pxTopOfStack;
}
/*------------------------------------------------------------------------------------
Function:  
------------------------------------------------------------------------------------*/
void vPortSVCHandler( void )
{
	/* This function is no longer used, but retained for backward
	compatibility. */
}

/*------------------------------------------------------------------------------------
Function:  
------------------------------------------------------------------------------------*/
BaseType_t xPortStartScheduler( void )
{
	/* 配置PendSV 和 SysTick 的中断优先级为最低 */
	*(portNVIC_SYSPRI2) |= portNVIC_PENDSV_PRI;
	*(portNVIC_SYSPRI2) |= portNVIC_SYSTICK_PRI;

	/* 初始化SysTick */
	prvSetupTimerInterrupt();

	/* 启动第一个任务，不再返回 */
	prvPortStartFirstTask();

	/* 不应该运行到这里 */
	return 0;
}
/*------------------------------------------------------------------------------------
Function:  设置PendSV 请求上下文切换
------------------------------------------------------------------------------------*/
void vPortYield( void )
{
	/* Set a PendSV to request a context switch. */
	*( portNVIC_INT_CTRL ) = portNVIC_PENDSVSET;

	/* Barriers are normally not required but do ensure the code is completely
	within the specified behaviour for the architecture. */
	__dsb( portSY_FULL_READ_WRITE );
	__isb( portSY_FULL_READ_WRITE );
}
/*------------------------------------------------------------------------------------
Function:  
------------------------------------------------------------------------------------*/
__asm uint32_t ulSetInterruptMaskFromISR( void )
{
	mrs r0, PRIMASK
	cpsid i
	bx lr
}
/*------------------------------------------------------------------------------------
Function:  
------------------------------------------------------------------------------------*/
__asm void vClearInterruptMaskFromISR( uint32_t ulMask )
{
	msr PRIMASK, r0
	bx lr
}
/*------------------------------------------------------------------------------------
Function:  
------------------------------------------------------------------------------------*/
__asm void prvPortStartFirstTask( void )
{
	extern pxCurrentTCB;

	PRESERVE8

	/* The MSP stack is not reset as, unlike on M3/4 parts, there is no vector
	table offset register that can be used to locate the initial stack value.
	Not all M0 parts have the application vector table at address 0. */

	ldr	r3, =pxCurrentTCB	/* Obtain location of pxCurrentTCB. */
	ldr r1, [r3]
	ldr r0, [r1]			/* The first item in pxCurrentTCB is the task top of stack. */
	adds r0, #32			/* Discard everything up to r0. */
	msr psp, r0				/* This is now the new top of stack to use in the task. */
	movs r0, #2				/* Switch to the psp stack. */
	msr CONTROL, r0
	isb
	pop {r0-r5}				/* Pop the registers that are saved automatically. */
	mov lr, r5				/* lr is now in r5. */
	pop {r3}				/* The return address is now in r3. */
	pop {r2}				/* Pop and discard the XPSR. */
	cpsie i					/* The first task has its context and interrupts can be enabled. */
	bx r3					/* Finally, jump to the user defined task code. */

	ALIGN
}
/*------------------------------------------------------------------------------------
Function:  
------------------------------------------------------------------------------------*/
__asm void xPortPendSVHandler( void )
{
	extern vTaskSwitchContext
	extern pxCurrentTCB

	PRESERVE8

	mrs r0, psp

	ldr	r3, =pxCurrentTCB 	/* Get the location of the current TCB. */
	ldr	r2, [r3]

	subs r0, #32			/* Make space for the remaining low registers. */
	str r0, [r2]			/* Save the new top of stack. */
	stmia r0!, {r4-r7}		/* Store the low registers that are not saved automatically. */
	mov r4, r8				/* Store the high registers. */
	mov r5, r9
	mov r6, r10
	mov r7, r11
	stmia r0!, {r4-r7}

	push {r3, r14}
	cpsid i
	bl vTaskSwitchContext
	cpsie i
	pop {r2, r3}			/* lr goes in r3. r2 now holds tcb pointer. */

	ldr r1, [r2]
	ldr r0, [r1]			/* The first item in pxCurrentTCB is the task top of stack. */
	adds r0, #16			/* Move to the high registers. */
	ldmia r0!, {r4-r7}		/* Pop the high registers. */
	mov r8, r4
	mov r9, r5
	mov r10, r6
	mov r11, r7

	msr psp, r0				/* Remember the new top of stack for the task. */

	subs r0, #32			/* Go back for the low registers that are not automatically restored. */
	ldmia r0!, {r4-r7}      /* Pop low registers.  */

	bx r3
	ALIGN
}
/*------------------------------------------------------------------------------------
Function:  初始化SysTick
------------------------------------------------------------------------------------*/
void prvSetupTimerInterrupt( void )
{
	/* Stop and reset the SysTick. */
	*(portNVIC_SYSTICK_CTRL) = 0UL;
	*(portNVIC_SYSTICK_CURRENT_VALUE) = 0UL;

	/* Configure SysTick to interrupt at the requested rate. */
	*(portNVIC_SYSTICK_LOAD) = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
	*(portNVIC_SYSTICK_CTRL) = portNVIC_SYSTICK_CLK | portNVIC_SYSTICK_INT | portNVIC_SYSTICK_ENABLE;
}
/*------------------------------------------------------------------------------------
Function:  SysTick中断服务函数
------------------------------------------------------------------------------------*/
void xPortSysTickHandler( void )
{
    uint32_t ulPreviousMask;

	/* 关中断 */
    ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
    
    /* 更新系统时基 */
    xTaskIncrementTick();
	
    /* 开中断 */
	portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );	
}


