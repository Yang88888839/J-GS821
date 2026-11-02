
#define DRIVER_PWM_C

#include "bt.h"
#include "flash.h"
#include "timer3.h"

#include "driver_gpio.h"
#include "driver_timer.h"
#include "driver_pwm.h"

#include "main.h"
#include "bsp_eeprom.h"

/*-------------------------------------------------------------
 * @brief  蜂鸣片驱动
 * @param
 * @return
-------------------------------------------------------------*/
void Init_pwm(void)
{
    uint16_t                   u16CntValue;
    uint8_t                    u8ValidPeriod;
	stc_gpio_cfg_t             stcTIM3Port;
    stc_tim3_mode23_cfg_t      stcTim3BaseCfg;
    stc_tim3_m23_compare_cfg_t stcTim3PortCmpCfg;
	
    /* 结构体初始化清零 */
    DDL_ZERO_STRUCT(stcTIM3Port);
    DDL_ZERO_STRUCT(stcTim3BaseCfg);
    DDL_ZERO_STRUCT(stcTim3PortCmpCfg);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); /* GPIO 外设时钟使能 */
    stcTIM3Port.enDir = GpioDirOut;
    Gpio_Init(GpioPortA, GpioPin15, &stcTIM3Port);
    Gpio_SetAfMode(GpioPortA, GpioPin15, GpioAf6); /* PA15设置为TIM3_CHA */

    Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, TRUE); /* Timer3外设时钟使能 */

    stcTim3BaseCfg.enWorkMode   = Tim3WorkMode3;       /* 三角波模式 */
    stcTim3BaseCfg.enCT         = Tim3Timer;           /* 定时器功能，计数时钟为内部PCLK */
    stcTim3BaseCfg.enPRS        = Tim3PCLKDiv8;        /* PCLK */
    stcTim3BaseCfg.enPWMTypeSel = Tim3IndependentPWM;  /* 独立输出PWM */
    stcTim3BaseCfg.enPWM2sSel   = Tim3SinglePointCmp;  /* 双点比较功能 */
    stcTim3BaseCfg.bOneShot     = FALSE;               /* 循环计数 */
    stcTim3BaseCfg.bURSSel      = FALSE;               /* 上下溢更新 */
    Tim3_Mode23_Init(&stcTim3BaseCfg);                 /* TIM3 的模式0功能初始化 */	
	
    Tim3_M23_ARRSet(PWM_BASE_FRQ, TRUE);              /* 设置重载值,并使能缓存 */
    Tim3_M23_CCR_Set(Tim3CCR1A, PWM_BASE_FRQ>>1);     /* 设置CH1比较值A */
	
    stcTim3PortCmpCfg.enCHxACmpCtrl   = Tim3PWMMode2;     /* OCREFA输出控制OCMA:PWM模式2 */
    stcTim3PortCmpCfg.enCHxAPolarity  = Tim3PortOpposite; /* 正常输出 */
    stcTim3PortCmpCfg.bCHxACmpBufEn   = TRUE;             /* A通道缓存控制 */
    stcTim3PortCmpCfg.enCHxACmpIntSel = Tim3CmpIntNone;   /* A通道比较中断控制:无 */	

    Tim3_M23_PortOutput_Cfg(Tim3CH1, &stcTim3PortCmpCfg); /* 比较输出端口配置 */
    
    /* 事件更新周期设置，OV Mask 使能之后，0代表三角波每个周期的下溢产生中断,每+1代表延迟一个周期 */
    u8ValidPeriod = 0;
    Tim3_M23_SetValidPeriod(u8ValidPeriod, TRUE, FALSE); /* 重复周期周期设置 */    

    u16CntValue = 0;
    Tim3_M23_Cnt16Set(u16CntValue); /* 设置计数初值 */

}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Tim3_IRQHandler(void)
{
    /* Timer3 模式23 更新中断 */
    if (TRUE == Tim3_GetIntFlag(Tim3UevIrq))
    {
		Tim3_ClearIntFlag(Tim3UevIrq); /* 清中断标志 */
	}		
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void pwm_enable(void)
{
	stc_gpio_cfg_t stcTIM3Port;
	DDL_ZERO_STRUCT(stcTIM3Port);
	
    stcTIM3Port.enDir = GpioDirOut;
    Gpio_Init(GpioPortA, GpioPin15, &stcTIM3Port);
    Gpio_SetAfMode(GpioPortA, GpioPin15, GpioAf6); /* PA07设置为TIM2_CHA */

    Tim3_M23_EnPWM_Output(TRUE, FALSE); /* 端口输出使能 */
	Tim3_M23_Run(); /* 运行 */
}   

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void pwm_disable(void) 
{
	stc_gpio_cfg_t stcTIM3Port;
	DDL_ZERO_STRUCT(stcTIM3Port);
	
	Tim3_M23_Stop();
	Tim3_M23_EnPWM_Output(FALSE, FALSE); /* 端口输出失能 */
    stcTIM3Port.enDir = GpioDirOut;
    Gpio_Init(GpioPortA, GpioPin15, &stcTIM3Port);
    Gpio_ClrIO(GpioPortA, GpioPin15);	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void frequency_set(unsigned short cycle,unsigned short duty)
{
    Tim3_M23_ARRSet(cycle, TRUE);          /* 设置重载值,并使能缓存 */
    Tim3_M23_CCR_Set(Tim3CCR1A, duty);     /* 设置CH1比较值A */	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void frequency_duty_set(unsigned char volume)
{
	switch(volume)
	{
		case 1 :	
		     frequency_set(PWM_BASE_FRQ,1);
			 break;
		case 2 : 
		     frequency_set(PWM_BASE_FRQ,5);
             break;		
		case 3 :			
		     frequency_set(PWM_BASE_FRQ,20);				
		     break;
		case 4 :
		     frequency_set(PWM_BASE_FRQ,50);
             break;
		case 5 :
		     frequency_set(PWM_BASE_FRQ,80);
             break;
		case 6 :
		     frequency_set(PWM_BASE_FRQ,200);
             break;			
		default:
		     frequency_set(PWM_BASE_FRQ,PWM_BASE_FRQ>>1);  
			 break;                  
	}	
}	













