
#define DRIVER_LPUART_C

#include "lpuart.h"
#include "gpio.h"

#include "driver_lpuart.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define SLAVEADDR01   0xC0
#define SLAVEADDR02   0xA0

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_lpusart1(void)
{
    stc_lpuart_cfg_t  stcCfg;
    stc_gpio_cfg_t stcGpioCfg;

    DDL_ZERO_STRUCT(stcCfg);
	DDL_ZERO_STRUCT(stcGpioCfg);

    /* TX */
    stcGpioCfg.enDir =  GpioDirOut;
    stcGpioCfg.bOutputVal = TRUE;
    Gpio_Init(GpioPortA, GpioPin0, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin0, GpioAf2); /* 配置PA00为LPUART1_TX */

    /* RX */
    stcGpioCfg.enDir =  GpioDirIn;
	stcGpioCfg.enPu  =  GpioPuEnable;
    Gpio_Init(GpioPortA, GpioPin1, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin1, GpioAf2); /* 配置PA01为LPUART1_RX */	
	
    /* 外设模块时钟使能 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart1, TRUE);

    /* LPUART 初始化 */
    stcCfg.enStopBit = LPUart1bit;                   /* 1停止位 */
    stcCfg.enMmdorCk = LPUartEven;                   /* 偶校验 */
    stcCfg.stcBaud.enSclkSel = LPUartMskPclk;        /* 传输时钟源 */
    stcCfg.stcBaud.u32Sclk = Sysctrl_GetPClkFreq();  /* PCLK获取 */
    stcCfg.stcBaud.enSclkDiv = LPUartMsk4Or8Div;     /* 采样分频 */
    stcCfg.stcBaud.u32Baud = 115200;                 /* 波特率 */
    stcCfg.enRunMode = LPUartMskMode1;               /* 工作模式 */
    LPUart_Init(M0P_LPUART1, &stcCfg);
    
    LPUart_EnableFunc(M0P_LPUART1, LPUartRenFunc);   /* 收发使能 */

    /* LPUART 中断使能 */
    LPUart_ClrStatus(M0P_LPUART1, LPUartRC);         /* 清接收中断请求 */
    LPUart_ClrStatus(M0P_LPUART1, LPUartTC);         /* 清发送中断请求 */
    LPUart_EnableIrq(M0P_LPUART1, LPUartRxIrq);      /* 使能接收中断 */
    //LPUart_EnableIrq(M0P_LPUART1, LPUartTxIrq);    /* 使能发送中断 */
    EnableNvic(LPUART1_IRQn, IrqLevel3, TRUE);       /* 系统中断使能 */	
}

/*-------------------------------------------------------------
 * @brief USART0中断
 * @param
 * @return
-------------------------------------------------------------*/
void LpUart1_IRQHandler(void)
{
    if (LPUart_GetStatus(M0P_LPUART1, LPUartFE))
    {
        LPUart_ClrStatus(M0P_LPUART1, LPUartFE);     /* 清帧错误请求 */
    }
    if (LPUart_GetStatus(M0P_LPUART1, LPUartPE))
    {
        LPUart_ClrStatus(M0P_LPUART1, LPUartPE);     /* 清奇偶检验错误请求 */
    }
    if (LPUart_GetStatus(M0P_LPUART1, LPUartTC))
    {
        LPUart_ClrStatus(M0P_LPUART1, LPUartTC);     /* 清发送中断请求 */
      //LPUart_SendDataIt(M0P_LPUART1, u8TxData[1]); /* 发送第二个字节 */
    }
    if (LPUart_GetStatus(M0P_LPUART1, LPUartRC))     /* 接收数据 */
    {
        LPUart_ClrStatus(M0P_LPUART1, LPUartRC);     /* 清接收中断请求 */
		
        lpuart1.buf[lpuart1.length] = LPUart_ReceiveData(M0P_LPUART1);
		if(lpuart1.length<512)
		{
			lpuart1.length++;
		}	
		lpuart1.timer=2;		
    }
}

/*-------------------------------------------------------------
 * @brief USART中断
 * @param
 * @return
-------------------------------------------------------------*/
void lpuart1_receive_timer(void)
{
	if(lpuart1.timer>0)
	{
		if((--lpuart1.timer)==0)
		{
			lpuart1.done=1;
			lpuart1.buf[lpuart1.length] = '\0';
		}	
	}	
}	

/*-------------------------------------------------------------
 * @brief USART中断
 * @param
 * @return
-------------------------------------------------------------*/
void lpuart_senddata(M0P_LPUART_TypeDef *LPUARTx, uint16_t u16Data)
{
    unsigned int timer=0;
	do
	{
		if(LPUart_GetStatus(LPUARTx, LPUartTxe)==TRUE)
		{
			break;
		}
        timer++;		
	}while(timer<60000);
    LPUARTx->SBUF_f.DATA = u16Data;
}







