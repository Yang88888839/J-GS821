
#define DRIVER_ADC_C

#include "adc.h"
#include "gpio.h"
#include "stdio.h"

#define  CHANNEL_GAS    AdcExInputCH6

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_AdcPort(void)
{
    /* 开启 GPIO外设时钟 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    //Gpio_SetAnalogMode(GpioPortA, GpioPin6); /* PA06 (AIN6) */	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Adc_config(en_adc_ref_vol_sel_t ref)
{
    stc_adc_cfg_t stcAdcCfg;

    DDL_ZERO_STRUCT(stcAdcCfg);
    /* 开启ADC/BGR 外设时钟 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, TRUE);
    /* 开启BGR */
    Bgr_BgrEnable();        
    /* ADC 初始化配置 */
    stcAdcCfg.enAdcMode         = AdcSglMode;               /* 采样模式-单次 */
    stcAdcCfg.enAdcClkDiv       = AdcMskClkDiv8;            /* 采样分频-1 */
    stcAdcCfg.enAdcSampCycleSel = AdcMskSampCycle127Clk;    /* 采样周期数-12 */
    stcAdcCfg.enAdcRefVolSel    = ref;                      /* 参考电压选择-内部2.5V */
    Adc_Init(&stcAdcCfg);	
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_Adc(void)
{
    Adc_config(AdcMskRefVolSelAVDD);
    //---------------------------------
	Bgr_TempSensorEnable();
	//---------------------------------
	Init_AdcPort();	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned short adc_read(en_adc_samp_ch_sel_t channel)
{
    unsigned short temp=0;
	/* ADC 采样通道配置 */
    Adc_CfgSglChannel(channel);	
	/* 清除中断标志位 */
	Adc_ClrIrqStatus(AdcMskIrqSgl);
	/* 启动单次转换采样 */
	Adc_SGL_Start();
	/* 等待转换完成 */
	do
	{
		temp++;
		if(TRUE == Adc_GetIrqStatus(AdcMskIrqSgl))
		{
			break;
		}	
	}while(temp<6000);	
	temp = Adc_GetSglResult(); /* 获取采样值 */
	return temp ;
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
unsigned short get_sensor_voltage(void)
{
	unsigned int adc,voltage ;
	
	Adc_config(AdcMskRefVolSelAVDD);
	adc = adc_read(AdcExInputCH6);	
	voltage = (3300*adc)>>12;
	return (voltage&0xffff);
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return 
-------------------------------------------------------------*/
unsigned short get_vcc_voltage(void)
{
	unsigned int adc,voltage ;

	Adc_config(AdcMskRefVolSelAVDD);
	adc = adc_read(AdcVref1_2Input);
	printf("vcc_adc=%d\r\n",adc);
	
	voltage = (1200*4096)/adc;
	return (voltage&0xffff);		
}

__attribute__((used)) static int16_t int16AdcC0Ref15;
__attribute__((used)) static int16_t int16AdcT0;
__attribute__((used)) static uint16_t u16AdcResult;
__attribute__((used)) static int16_t AdcValue;
__attribute__((used)) static float fAdcK;
__attribute__((used)) static float AdcRef;

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return 
-------------------------------------------------------------*/
signed char get_temperature(void)
{
	float Temperate;
	signed char out ;
	
    int16AdcC0Ref15 = *((int16_t *)0x00101BE8);
    int16AdcT0      = *((int16_t *)0x00101BEC);	
    fAdcK           = 0.0798;
	
	Adc_config(AdcMskRefVolSelInBgr1p5);
	u16AdcResult = adc_read(AdcAiTsInput);
	
	AdcValue = ((int16_t)u16AdcResult - int16AdcC0Ref15);
	AdcRef = 1.5 * fAdcK * ((float)AdcValue);
	Temperate = (float)(int16AdcT0 >> 4u) + AdcRef;	
	out = (signed char)(Temperate*10) ;
	return out ;
}	




















/*-------------------------------------------------------------
 * @brief
 * @param
 * @return 
-------------------------------------------------------------*/
//unsigned short get_vcc_voltage(void)
//{
//	unsigned int adc,voltage ;

//	Adc_config(AdcMskRefVolSelInBgr2p5);
//	adc = adc_read(AdcAVccdiv3Input);
//	printf("vcc_adc=%d\r\n",adc);
//	
//	voltage = ((2500*adc)/4096)*3;
//	return (voltage&0xffff);		
//}











