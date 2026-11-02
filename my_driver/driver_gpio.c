
#define DRIVER_GPIO_C

#include "lpm.h"
#include "adc.h"
#include "gpio.h"
#include "driver_gpio.h"
#include "driver_timer.h"

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_gpio(void)
{
    stc_gpio_cfg_t stcGpioCfg;

    DDL_ZERO_STRUCT(stcGpioCfg);   /* 结构体变量初始值置零 */
    /* 打开GPIO外设时钟门控 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    //------------------------------------------------------------------输出
    /* 端口方向配置->输出(其它参数与以上（输入）配置参数一致) */
    stcGpioCfg.enDir = GpioDirOut;
    /* 初始化输出电平->低电平 */
    stcGpioCfg.bOutputVal = TRUE;
    /* 端口驱动能力配置->高驱动能力 */
    stcGpioCfg.enDrv = GpioDrvH;
    /* 端口上下拉配置->无上下拉 */
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;

    /* GPIO IO LED端口初始化 */
    Gpio_Init(LED_POWER_PORT,         LED_POWER_PIN, &stcGpioCfg);    
	Gpio_Init(LED_ALARM_PORT,         LED_ALARM_PIN, &stcGpioCfg);
	Gpio_Init(LED_FAULT_PORT,         LED_FAULT_PIN, &stcGpioCfg);
	Gpio_Init(LED_LIFEOVER_PORT,      LED_LIVEOVER_PIN, &stcGpioCfg);	
	Gpio_Init(LED_VALVE_PORT,         LED_VALVE_PIN, &stcGpioCfg);
	/* 端口上下拉配置->上拉 */
    stcGpioCfg.enPu = GpioPuEnable;
	Gpio_Init(DEBUG_PORT,              DEBUG_PIN, &stcGpioCfg);
	Gpio_Init(SENSOR_RESET_PORT,       SENSOR_RESET_PIN, &stcGpioCfg);
	Gpio_Init(VALVE_CONTROL_PORT,      VALVE_CONTROL_PIN, &stcGpioCfg);
	Gpio_Init(VALVE_CHECK_PORT,        VALVE_CHECK_PIN, &stcGpioCfg);
	Gpio_Init(TEMPERATURE_POWER_PORT,  TEMPERATURE_POWER_PIN,&stcGpioCfg);
	
	//------------------------------------------------------------------
	PW_red_close();
	PW_blue_close();
	PW_green_close();
	PW_lifeover_close();
	PW_valve_check_close();
	PW_valve_control_close();
	PW_temperature_power_open();
	PW_sensor_reset_l();
	//------------------------------------------------------------------输入
    DDL_ZERO_STRUCT(stcGpioCfg);   /* 结构体变量初始值置零 */
    /* 端口方向配置->输入 */
    stcGpioCfg.enDir = GpioDirIn;
    /* 端口上下拉配置->无 */
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;
    /* 端口开漏输出配置->开漏输出关闭 */
    stcGpioCfg.enOD = GpioOdDisable;
    /* 端口输入/输出值寄存器总线控制模式配置->AHB */
    stcGpioCfg.enCtrlMode = GpioAHB;
    /* GPIO IO USER KEY初始化 */
	Gpio_Init(AC_CHECK_PORT, AC_CHECK_PIN, &stcGpioCfg);
    Gpio_Init(KEY_CHECK_PORT, KEY_CHECK_PIN, &stcGpioCfg);			
	//------------------------------------------------------------------
    DDL_ZERO_STRUCT(stcGpioCfg);   /* 结构体变量初始值置零 */
    /* 端口方向配置->输入 */
    stcGpioCfg.enDir = GpioDirIn;
    /* 端口上下拉配置->无 */
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;
    /* 端口开漏输出配置->开漏输出关闭 */
    stcGpioCfg.enOD = GpioOdEnable;
    /* 端口输入/输出值寄存器总线控制模式配置->AHB */
    stcGpioCfg.enCtrlMode = GpioAHB;
    Gpio_Init(VALVE_LEVEL_PORT, VALVE_LEVEL_PIN, &stcGpioCfg);	
	//------------------------------------------------------------------模拟
    //Gpio_SetAnalogMode(GpioPortA, GpioPin6); /* PA06 (AIN6) */
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_gpio_sleep(void)
{
    /* 打开GPIO外设时钟门控 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    /* swd as gpio */
    //Sysctrl_SetFunc(SysctrlSWDUseIOEn, TRUE);  
	
    M0P_GPIO->PAPD = 0u;  /* 取消PA10默认输入下拉 */
	
    /* 配置为数字端口*/
    M0P_GPIO->PAADS = 0xFFFFu;
    M0P_GPIO->PBADS = 0xFFFFu;    /* PB09 USER KEY */
    M0P_GPIO->PCADS = 0xFFFFu;
    M0P_GPIO->PDADS = 0xFFFFu;    /* PD06 LED; PD03 BOOT */		
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_gpio_wakeup(void)
{
    stc_gpio_cfg_t stcGpioCfg;

    DDL_ZERO_STRUCT(stcGpioCfg);   /* 结构体变量初始值置零 */

    /* 打开GPIO外设时钟门控 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    /* 端口方向配置->输入 */
    stcGpioCfg.enDir = GpioDirIn;
    /* 端口驱动能力配置->高驱动能力 */
    stcGpioCfg.enDrv = GpioDrvL;
    /* 端口上下拉配置->无 */
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;
    /* 端口开漏输出配置->开漏输出关闭 */
    stcGpioCfg.enOD = GpioOdDisable;
    /* 端口输入/输出值寄存器总线控制模式配置->AHB */
    stcGpioCfg.enCtrlMode = GpioAHB;
    /* GPIO IO USER KEY初始化 */
    Gpio_Init(AC_CHECK_PORT, AC_CHECK_PIN, &stcGpioCfg);
}

/*-------------------------------------------------------------
 * @brief 睡眠前设置
 * @param
 * @return
-------------------------------------------------------------*/
void Init_sleep(void)
{
	//< 关闭 ADC
	Adc_Disable();
	//< 关闭 BGR
	Bgr_BgrDisable();
	//< 关闭 内置温度
	Bgr_TempSensorDisable();
	//< 关闭 ADC 外设时钟
	Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, FALSE);
	/* 配置FLASH为低功耗模式 */
    Flash_FuncSet(FlashDpStbEn, TRUE);
    /* 配置Demo板上所有不使用的IO为输入下拉,避免端口漏电 */
    Init_gpio_sleep();
	/* 初始化唤醒脚*/
	Init_gpio_wakeup();
    /* 关断IR中断 */
	Gpio_DisableIrq(IR_INPUT_PORT, IR_INPUT_PIN, GpioIrqRising);
	Gpio_DisableIrq(IR_INPUT_PORT, IR_INPUT_PIN, GpioIrqFalling);
	/* 关断valve中断 */
	Gpio_DisableIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN, GpioIrqRising);
	Gpio_DisableIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN, GpioIrqFalling);	
	/* 打开并配置按键端口为下降沿中断 */
	Gpio_EnableIrq(AC_CHECK_PORT, AC_CHECK_PIN, GpioIrqFalling);
    EnableNvic(PORTD_IRQn, IrqLevel3, TRUE);
    /* 进入低功耗模式——深度休眠（使能唤醒后退出中断自动休眠特性） */ 
	Lpm_GotoDeepSleep(FALSE);
	NVIC_SystemReset();	
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_gpio_interrupt(void)
{
    stc_gpio_cfg_t stcGpioCfg;

    /* 结构体变量初始值置零 */
    DDL_ZERO_STRUCT(stcGpioCfg);

    /* 打开GPIO外设时钟门控 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    /* 端口方向配置->输入 */
    stcGpioCfg.enDir = GpioDirIn;
    /* 端口上下拉配置->无 */
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;
    /* 端口开漏输出配置->开漏输出关闭 */
    stcGpioCfg.enOD = GpioOdDisable;
    /* 端口输入/输出值寄存器总线控制模式配置->AHB */
    stcGpioCfg.enCtrlMode = GpioAHB;
    /* GPIO 初始化 */
    Gpio_Init(IR_INPUT_PORT, IR_INPUT_PIN, &stcGpioCfg);
	Gpio_Init(VALVE_PULSE_PORT, VALVE_PULSE_PIN, &stcGpioCfg);
    /* 打开并配置IR为边沿中断 */
    Gpio_EnableIrq(IR_INPUT_PORT, IR_INPUT_PIN, GpioIrqFalling);
    Gpio_EnableIrq(IR_INPUT_PORT, IR_INPUT_PIN, GpioIrqRising);
	/* 使能端口PORTD系统中断 */
	EnableNvic(PORTD_IRQn, IrqLevel3, TRUE);
    /* 打开并配置valve为边沿中断 */
    Gpio_EnableIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN, GpioIrqFalling);
    Gpio_EnableIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN, GpioIrqRising);
    /* 使能端口PORTA系统中断 */  
	EnableNvic(PORTA_IRQn, IrqLevel3, TRUE);	
    	
}

/*-------------------------------------------------------------
 * @brief 阀门中断输入设置
 * @param
 * @return
-------------------------------------------------------------*/
void valve_interrupt_set(unsigned char sw)
{
	Gpio_ClearIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN);
	if(sw==1)
	{
        Gpio_EnableIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN, GpioIrqFalling);
        Gpio_EnableIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN, GpioIrqRising);
	}
    else 
    {
		Gpio_DisableIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN, GpioIrqRising);
		Gpio_DisableIrq(VALVE_PULSE_PORT, VALVE_PULSE_PIN, GpioIrqFalling);		
	}		
}	




















