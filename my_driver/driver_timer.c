
#define DRIVER_TIMER_C

#include "bt.h"
#include "flash.h"

#include "driver_gpio.h"
#include "driver_timer.h"

#include "main.h"
#include "bsp_eeprom.h"

#define  SYS_FREQUENCY  14700
/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_ClockSys(void)
{
    /* 时钟分频设置 */
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);    
	/* HCLK超过24M：此处设置FLASH读等待周期为1 cycle */
    Flash_WaitCycle(FlashWaitCycle1);
    /* 加载目标频率的RCH的数据 */
    Sysctrl_SetRCHTrim(SysctrlRchFreq48MHz);
    
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);    

    Sysctrl_SysClkSwitch(SysctrlClkRCH);	
}

static unsigned char timer_sec ;
/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Tim0_IRQHandler(void)
{
    /* Timer0 模式0 溢出中断 */
    if (TRUE == Bt_GetIntFlag(TIM0, BtUevIrq))
    {
        Bt_ClearIntFlag(TIM0, BtUevIrq); /* 中断标志清零 */	
    }
}

/*-------------------------------------------------------------
 * @brief  IR脉冲计数
 * @param
 * @return
-------------------------------------------------------------*/
void Tim1_IRQHandler(void)
{
    /* Timer1 模式0 溢出中断 */
    if (TRUE == Bt_GetIntFlag(TIM1, BtUevIrq))
    {
        Bt_ClearIntFlag(TIM1, BtUevIrq); /* 中断标志清零 */
    }	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Tim2_IRQHandler(void)
{
    /* Timer0 模式0 溢出中断 */
    if (TRUE == Bt_GetIntFlag(TIM2, BtUevIrq))
    {
        Bt_ClearIntFlag(TIM2, BtUevIrq); /* 中断标志清零 */
		f_timer_10ms =1 ;
		
		if((++timer_sec)<100)
		{
			return ;
		}
		timer_sec=0;
		f_timer_sec=1;
		if(eep.sys.byte.life_ticker<0xffffffff)
		{
			eep.sys.byte.life_ticker++;
		}	
    }
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_timer0(void)
{
    uint16_t                 u16CntValue;
    uint8_t                  u8ValidPeriod;
	stc_gpio_cfg_t           stcTIM0Port;
    stc_bt_mode23_cfg_t      stcBtBaseCfg;
    stc_bt_m23_compare_cfg_t stcBtPortCmpCfg;

    /* 结构体初始化清零 */
	DDL_ZERO_STRUCT(stcTIM0Port);
    DDL_ZERO_STRUCT(stcBtBaseCfg);
    DDL_ZERO_STRUCT(stcBtPortCmpCfg);
	
    stcTIM0Port.enDir = GpioDirOut;
    Gpio_Init(GpioPortB, GpioPin14, &stcTIM0Port);
    Gpio_SetAfMode(GpioPortB, GpioPin14, GpioAf4); /* PB14设置为TIM0_CHA */	
	
    Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, TRUE); /* Base Timer外设时钟使能 */

    stcBtBaseCfg.enWorkMode   = BtWorkMode2;      /* 锯齿波模式 */
    stcBtBaseCfg.enCT         = BtTimer;          /* 定时器功能，计数时钟为内部PCLK */
    stcBtBaseCfg.enPRS        = BtPCLKDiv1;       /* PCLK */
    stcBtBaseCfg.enCntDir     = BtCntUp;          /* 向上计数，在三角波模式时只读 */
    stcBtBaseCfg.enPWMTypeSel = BtIndependentPWM; /* 独立输出PWM */
    stcBtBaseCfg.enPWM2sSel   = BtSinglePointCmp; /* 单点比较功能 */
    stcBtBaseCfg.bOneShot     = FALSE;            /* 循环计数 */
    stcBtBaseCfg.bURSSel      = FALSE;            /* 上下溢更新 */
    Bt_Mode23_Init(TIM0, &stcBtBaseCfg);          /* TIM0 的模式23功能初始化 */

    Bt_M23_ARRSet(TIM0, 1000, TRUE);              /* 设置重载值,并使能缓存 */
    Bt_M23_CCR_Set(TIM0, BtCCR0A, 2000);          /* 设置比较值A */

    stcBtPortCmpCfg.enCH0ACmpCtrl   = BtPWMMode2;     /* OCREFA输出控制OCMA:PWM模式2 */
    stcBtPortCmpCfg.enCH0APolarity  = BtPortPositive; /* 正常输出 */
    stcBtPortCmpCfg.bCh0ACmpBufEn   = TRUE;           /* A通道缓存控制 */
    stcBtPortCmpCfg.enCh0ACmpIntSel = BtCmpIntNone;   /* A通道比较控制:无 */
    Bt_M23_PortOutput_Cfg(TIM0, &stcBtPortCmpCfg);    /* 比较输出端口配置 */

    /* 事件更新周期设置，OV和UND Mask都无效时，0表示锯齿波每个周期更新一次，每+1代表延迟1个周期 */
    u8ValidPeriod = 0;
    Bt_M23_SetValidPeriod(TIM0, u8ValidPeriod, FALSE, FALSE); /* 重复周期设置 */

    u16CntValue = 0;
    Bt_M23_Cnt16Set(TIM0, u16CntValue);       /* 设置计数初值 */

    //Bt_ClearAllIntFlag(TIM0);                 /* 清中断标志 */
    //Bt_Mode23_EnableIrq(TIM0, BtUevIrq);      /* 使能TIM0 UEV更新中断 */
    //EnableNvic(TIM0_IRQn, IrqLevel0, TRUE);   /* TIM0中断使能 */
	
    Bt_M23_EnPWM_Output(TIM0, TRUE, FALSE); /* TIM0 端口输出使能 */
    Bt_M23_Run(TIM0); /* TIM0 运行 */	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void green_pwm_output(unsigned short duty)
{
	stc_gpio_cfg_t stcTIM0Port;
    /* 结构体初始化清零 */
	DDL_ZERO_STRUCT(stcTIM0Port);
	
    stcTIM0Port.enDir = GpioDirOut;
    Gpio_Init(GpioPortB, GpioPin14, &stcTIM0Port);
    Gpio_SetAfMode(GpioPortB, GpioPin14, GpioAf4); /* PB14设置为TIM0_CHA */	

	Bt_M23_CCR_Set(TIM0, BtCCR0A, duty);	
	
    Bt_M23_EnPWM_Output(TIM0, TRUE, FALSE); /* TIM0 端口输出使能 */
    Bt_M23_Run(TIM0); /* TIM0 运行 */
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void green_gpio_output(unsigned char bit) 
{
	stc_gpio_cfg_t stcTIM0Port;
    /* 结构体初始化清零 */
	DDL_ZERO_STRUCT(stcTIM0Port);
	
    stcTIM0Port.enDir = GpioDirOut;
    Gpio_Init(GpioPortB, GpioPin14, &stcTIM0Port);
    Gpio_SetAfMode(GpioPortB, GpioPin14, GpioAf0); /* PB14设置为TIM0_CHA */		
	
    Bt_M23_EnPWM_Output(TIM0, FALSE, FALSE); /* TIM0 端口输出使能 */
    Bt_M23_Stop(TIM0);                       /* TIM0 运行 */
	
	if(bit==0)
	{
		Gpio_SetIO(GpioPortB, GpioPin11);
	}	
	else
	{
		Gpio_ClrIO(GpioPortB, GpioPin11);
	}
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void green_set_duty(unsigned short duty)
{
	Bt_M23_CCR_Set(TIM0, BtCCR0A,duty);
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_timer1(void)
{
    stc_bt_mode0_cfg_t stcBtBaseCfg;

    DDL_ZERO_STRUCT(stcBtBaseCfg);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, TRUE); /* Base Timer外设时钟使能 */

    stcBtBaseCfg.enWorkMode = BtWorkMode0;    /* 定时器模式 */
    stcBtBaseCfg.enCT       = BtTimer;        /* 定时器功能，计数时钟为内部PCLK */
    stcBtBaseCfg.enPRS      = BtPCLKDiv64;    /* PCLK/256 */
    stcBtBaseCfg.enCntMode  = Bt32bitFreeMode;/* 32位计数器/定时器 */
    stcBtBaseCfg.bEnTog     = FALSE;
    stcBtBaseCfg.bEnGate    = FALSE;
    stcBtBaseCfg.enGateP    = BtGatePositive;
    Bt_Mode0_Init(TIM1, &stcBtBaseCfg);       /* TIM0 的模式0功能初始化 */
	
	Bt_M0_Run(TIM1);        /* TIM1 运行 */
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Timer1_enable(void)
{
	Bt_M0_Cnt32Set(TIM1,0); /* 计数清零 */
	Bt_M0_Run(TIM1);        /* TIM1 运行 */
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned int Timer1_disable(void)
{
	unsigned int t ;
	Bt_M0_Stop(TIM1);         /* TIM1 停止 */
	t = Bt_M0_Cnt32Get(TIM1);
	return t ;
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_timer2(void)
{
    uint16_t           u16ArrValue;
    uint16_t           u16CntValue;
    stc_bt_mode0_cfg_t stcBtBaseCfg;

    DDL_ZERO_STRUCT(stcBtBaseCfg);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, TRUE); /* Base Timer外设时钟使能 */

    stcBtBaseCfg.enWorkMode = BtWorkMode0;   /* 定时器模式 */
    stcBtBaseCfg.enCT       = BtTimer;       /* 定时器功能，计数时钟为内部PCLK */
    stcBtBaseCfg.enPRS      = BtPCLKDiv32;   /* PCLK/256 */
    stcBtBaseCfg.enCntMode  = Bt16bitArrMode;/* 自动重载16位计数器/定时器 */
    stcBtBaseCfg.bEnTog     = FALSE;
    stcBtBaseCfg.bEnGate    = FALSE;
    stcBtBaseCfg.enGateP    = BtGatePositive;
    Bt_Mode0_Init(TIM2, &stcBtBaseCfg);     /* TIM0 的模式0功能初始化 */

    u16ArrValue = 0x10000 - SYS_FREQUENCY;
    Bt_M0_ARRSet(TIM2, u16ArrValue);        /* 设置重载值(ARR = 0x10000 - 周期) */

    u16CntValue = 0x10000 - SYS_FREQUENCY;
    Bt_M0_Cnt16Set(TIM2, u16CntValue);      /* 设置计数初值 */
	
    Bt_ClearIntFlag(TIM2, BtUevIrq);        /* 清中断标志 */
    Bt_Mode0_EnableIrq(TIM2);               /* 使能TIM2中断(模式0时只有一个中断) */
    EnableNvic(TIM2_IRQn, IrqLevel3, TRUE); /* TIM2中断使能 */

    Bt_M0_Run(TIM2); /* TIM2 运行 */
}













