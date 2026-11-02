
#define DRIVER_UART_C

#include "usart.h"
#include "gpio.h"

#include "main.h"
#include "driver_uart.h"

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
void Init_usart0_fun(unsigned char fun)
{
    stc_usart_uart_init_t    stcUartCfg;
	DDL_ZERO_STRUCT(stcUartCfg);
	
	EnableNvic(USART0_IRQn, IrqLevel3, FALSE); /* 系统中断除能 */
	if(fun==UART_FUN_FCT)
    {
		/* UART Init */
		stcUartCfg.enFrameLength = UsartMskFrame8Bit;     /* 数据帧长度:8bit */
		stcUartCfg.enStopBit     = UsartMskStop1bit;      /* 1bit停止位 */
		stcUartCfg.enParity      = UsartMskFParityNone;   /* 无检验 */
		stcUartCfg.u32BaudRate   = 115200;                /* 波特率9600 */
		stcUartCfg.enSampleMode  = UsartMskOver8;         /* 通道采样分频配置 */
		stcUartCfg.u32Pclk       = Sysctrl_GetPClkFreq(); /* 获得外设时钟（PCLK）频率值 */
		stcUartCfg.enTransMode   = UsartMskTxRxEnable;    /* 收发使能 */
		stcUartCfg.stcAdvFeature.enClockCtrl = UsartMskUartInnerClkNoOutput;    /* UART使用内部时钟，不输出到CK引脚 */
		stcUartCfg.stcAdvFeature.enDMATxRxTransfer = UsartMskDmaDisable;        /* DMA传输禁止 */
		stcUartCfg.stcAdvFeature.enHWFlowCtrl = UsartMskHwFlowDisable;          /* 硬件流控禁止 */
		stcUartCfg.stcAdvFeature.enMSBFirst = UsartMskLSBFirst;                 /* 传输顺序LSB */
		stcUartCfg.stcAdvFeature.enStartBitDetectMode = UsartMskStartRxEdge;    /* 起始位检测方式：边沿检测 */
		stcUartCfg.stcAdvFeature.enTxRxCombine = UsartMskTxRxSeparate;          /* TxRx分别使用 */
		stcUartCfg.stcAdvFeature.enTxRxPinLevelInvert = UsartMskTxRxInvDisable; /* TxRx反相禁止 */
		stcUartCfg.stcAdvFeature.enTxRxSwap = UsartMskTxRxSwapDisable;          /* TxRx交换禁止 */
		Usart_Uart_Init(M0P_USART0, &stcUartCfg);  /* 串口初始化 */
        myprintf("usart fct...\r\n");		
	}
    else
    {
		/* UART Init */
		stcUartCfg.enFrameLength = UsartMskFrame8Bit;     /* 数据帧长度:8bit */
		stcUartCfg.enStopBit     = UsartMskStop1bit;      /* 1bit停止位 */
		stcUartCfg.enParity      = UsartMskFParityEven;   /* 无检验 */
		stcUartCfg.u32BaudRate   = 4800  ;                /* 波特率4800 */
		stcUartCfg.enSampleMode  = UsartMskOver8;         /* 通道采样分频配置 */
		stcUartCfg.u32Pclk       = Sysctrl_GetPClkFreq(); /* 获得外设时钟（PCLK）频率值 */
		stcUartCfg.enTransMode   = UsartMskTxRxEnable;    /* 收发使能 */
		stcUartCfg.stcAdvFeature.enClockCtrl = UsartMskUartInnerClkNoOutput;    /* UART使用内部时钟，不输出到CK引脚 */
		stcUartCfg.stcAdvFeature.enDMATxRxTransfer = UsartMskDmaDisable;        /* DMA传输禁止 */
		stcUartCfg.stcAdvFeature.enHWFlowCtrl = UsartMskHwFlowDisable;          /* 硬件流控禁止 */
		stcUartCfg.stcAdvFeature.enMSBFirst = UsartMskLSBFirst;                 /* 传输顺序LSB */
		stcUartCfg.stcAdvFeature.enStartBitDetectMode = UsartMskStartRxEdge;    /* 起始位检测方式：边沿检测 */
		stcUartCfg.stcAdvFeature.enTxRxCombine = UsartMskTxRxSeparate;          /* TxRx分别使用 */
		stcUartCfg.stcAdvFeature.enTxRxPinLevelInvert = UsartMskTxRxInvEnable;  /* TxRx反相禁止 */
		stcUartCfg.stcAdvFeature.enTxRxSwap = UsartMskTxRxSwapEnable;           /* TxRx交换禁止 */
		Usart_Uart_Init(M0P_USART0, &stcUartCfg);  /* 串口初始化 */
        myprintf("usart log...\r\n");		
	}
    /* UART中断使能 */
    Usart_ClrStatus(M0P_USART0, UsartRC);  /* 清接收请求 */
    Usart_ClrStatus(M0P_USART0, UsartTC);  /* 清发送请求 */
    Usart_EnableIrq(M0P_USART0, UsartRxIrq);  /* 使能串口接收中断 */
//  Usart_EnableIrq(M0P_USART0, UsartTxIrq);  /* 使能串口发送中断 */
    EnableNvic(USART0_IRQn, IrqLevel3, TRUE); /* 系统中断使能 */		
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_usart0(void)
{
	stc_gpio_cfg_t           stcGpioCfg;

    DDL_ZERO_STRUCT(stcGpioCfg);
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); /* 使能GPIO外设时钟门控开关 */
    /* TX */
    stcGpioCfg.enDir = GpioDirOut;
    stcGpioCfg.bOutputVal = TRUE;
    Gpio_Init(GpioPortA, GpioPin9, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin9, GpioAf1);   /* PA09 配置为URART0_TX */
    /* RX */
    stcGpioCfg.enDir = GpioDirIn;
	//stcGpioCfg.enPu = GpioPuEnable;
    Gpio_Init(GpioPortA, GpioPin10, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin10, GpioAf1);  /* PA10 配置为UART0 RX */	

    /* 开启外设时钟 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralUsart0, TRUE); /* 使能usart0模块时钟 */
    /* 配置 */
}

/*-------------------------------------------------------------
 * @brief USART0中断
 * @param
 * @return
-------------------------------------------------------------*/
void Usart0_IRQHandler(void)
{
    if (Usart_GetStatus(M0P_USART0, UsartFE))    /* 帧错误 */
    {
        Usart_ClrStatus(M0P_USART0, UsartFE);    /* 清除帧错误标记 */
    }
    if (Usart_GetStatus(M0P_USART0, UsartPE)) /* 校验错误 */
    {
        Usart_ClrStatus(M0P_USART0, UsartPE); /* 清除奇偶校验错误标记 */
    }
    if (Usart_GetStatus(M0P_USART0, UsartRC))
    {
        Usart_ClrStatus(M0P_USART0, UsartRC);              /* 清除中断状态位 */

        uart0.buf[uart0.length] = Usart_ReceiveData(M0P_USART0);
		if(uart0.length<UART_LEN_MAX)
		{
			uart0.length++;
		}	
		uart0.timer=3;
		
//		if (TRUE == Usart_GetStatus(M0P_USART0, UsartAM))   /*地址匹配,CR1.SLME自动清零 */
//        {
//            u8AddrFlg = 1;
//            u16AddrData = Usart_ReceiveData(M0P_USART0);    /* 首字节为地址字节 */
//            Usart_ClrStatus(M0P_USART0, UsartAM);
//        }
//        else
//        {
//            u8RxData[u8RxCnt++] = Usart_ReceiveData(M0P_USART0); /* 数据字节 */
//        }
    }

//    if (Usart_GetStatus(M0P_USART0, UsartTC))
//    {
//        Usart_ClrStatus(M0P_USART0, UsartTC);              /* 清除中断状态位 */
//        
//        if(u8TxCnt <=1)
//        {
//            Usart_SendDataIt(M0P_USART0, u8TxData[u8TxCnt++]);/* 发送数据 */
//        }
//        else                                /* 如果已发送两个字节 */
//        {
//            u8TxCnt = 0;
//            u8RxCnt = 0;
//        }
//    }
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_usart1(void)
{
    stc_usart_uart_init_t    stcUartCfg;
	stc_gpio_cfg_t           stcGpioCfg;

    DDL_ZERO_STRUCT(stcUartCfg);
    DDL_ZERO_STRUCT(stcGpioCfg);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); /* 使能GPIO外设时钟门控开关 */
    /* TX */
    stcGpioCfg.enDir = GpioDirOut;
    stcGpioCfg.bOutputVal = TRUE;
    Gpio_Init(GpioPortA, GpioPin2, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin2, GpioAf1);   /* PA2 配置为URART0_TX */
    /* RX */
	//stcGpioCfg.enDrv = GpioDrvH;
    stcGpioCfg.enDir = GpioDirIn;
    /* 端口上下拉配置->无上下拉 */
    stcGpioCfg.enPu = GpioPuEnable;
    Gpio_Init(GpioPortA, GpioPin3, &stcGpioCfg);
    Gpio_SetAfMode(GpioPortA, GpioPin3, GpioAf1);  /* PA3 配置为UART0 RX */	

    /* 开启外设时钟 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralUsart1, TRUE); /* 使能usart1模块时钟 */

    /* UART Init */
    stcUartCfg.enFrameLength = UsartMskFrame8Bit;     /* 数据帧长度:8bit */
    stcUartCfg.enStopBit     = UsartMskStop1bit;      /* 1bit停止位 */
    stcUartCfg.enParity      = UsartMskFParityNone;   /* 无检验 */
    stcUartCfg.u32BaudRate   = 9600;                  /* 波特率9600 */
    stcUartCfg.enSampleMode  = UsartMskOver8;         /* 通道采样分频配置 */
    stcUartCfg.u32Pclk       = Sysctrl_GetPClkFreq(); /* 获得外设时钟（PCLK）频率值 */
    stcUartCfg.enTransMode   = UsartMskTxRxEnable;    /* 收发使能 */
    stcUartCfg.stcAdvFeature.enClockCtrl = UsartMskUartInnerClkNoOutput;    /* UART使用内部时钟，不输出到CK引脚 */
    stcUartCfg.stcAdvFeature.enDMATxRxTransfer = UsartMskDmaDisable;        /* DMA传输禁止 */
    stcUartCfg.stcAdvFeature.enHWFlowCtrl = UsartMskHwFlowDisable;          /* 硬件流控禁止 */
    stcUartCfg.stcAdvFeature.enMSBFirst = UsartMskLSBFirst;                 /* 传输顺序LSB */
    stcUartCfg.stcAdvFeature.enStartBitDetectMode = UsartMskStartRxEdge;    /* 起始位检测方式：边沿检测 */
    stcUartCfg.stcAdvFeature.enTxRxCombine = UsartMskTxRxSeparate;          /* TxRx分别使用 */
    stcUartCfg.stcAdvFeature.enTxRxPinLevelInvert = UsartMskTxRxInvDisable; /* TxRx反相禁止 */
    stcUartCfg.stcAdvFeature.enTxRxSwap = UsartMskTxRxSwapDisable;          /* TxRx交换禁止 */
    Usart_Uart_Init(M0P_USART1, &stcUartCfg);  /* 串口初始化 */
    
    /* UART中断使能 */
    Usart_ClrStatus(M0P_USART1, UsartRC);  /* 清接收请求 */
    Usart_ClrStatus(M0P_USART1, UsartTC);  /* 清发送请求 */
    Usart_EnableIrq(M0P_USART1, UsartRxIrq);  /* 使能串口接收中断 */
//  Usart_EnableIrq(M0P_USART1, UsartTxIrq);  /* 使能串口发送中断 */
    EnableNvic(USART1_IRQn, IrqLevel3, TRUE); /* 系统中断使能 */	
}

/*-------------------------------------------------------------
 * @brief USART0中断
 * @param
 * @return
-------------------------------------------------------------*/
void Usart1_IRQHandler(void)
{
    if (Usart_GetStatus(M0P_USART1, UsartFE))    /* 帧错误 */
    {
        Usart_ClrStatus(M0P_USART1, UsartFE);    /* 清除帧错误标记 */
    }
    if (Usart_GetStatus(M0P_USART1, UsartPE)) /* 校验错误 */
    {
        Usart_ClrStatus(M0P_USART1, UsartPE); /* 清除奇偶校验错误标记 */
    }
    if (Usart_GetStatus(M0P_USART1, UsartRC))
    {
        Usart_ClrStatus(M0P_USART1, UsartRC);              /* 清除中断状态位 */

        uart1.buf[uart1.length] = Usart_ReceiveData(M0P_USART1);
		if(uart1.length<UART_LEN_MAX)
		{
			uart1.length++;
		}	
		uart1.timer=3;
		
//		if (TRUE == Usart_GetStatus(M0P_USART0, UsartAM))   /*地址匹配,CR1.SLME自动清零 */
//        {
//            u8AddrFlg = 1;
//            u16AddrData = Usart_ReceiveData(M0P_USART0);    /* 首字节为地址字节 */
//            Usart_ClrStatus(M0P_USART0, UsartAM);
//        }
//        else
//        {
//            u8RxData[u8RxCnt++] = Usart_ReceiveData(M0P_USART0); /* 数据字节 */
//        }
    }

//    if (Usart_GetStatus(M0P_USART0, UsartTC))
//    {
//        Usart_ClrStatus(M0P_USART0, UsartTC);              /* 清除中断状态位 */
//        
//        if(u8TxCnt <=1)
//        {
//            Usart_SendDataIt(M0P_USART0, u8TxData[u8TxCnt++]);/* 发送数据 */
//        }
//        else                                /* 如果已发送两个字节 */
//        {
//            u8TxCnt = 0;
//            u8RxCnt = 0;
//        }
//    }
}

/*-------------------------------------------------------------
 * @brief USART中断
 * @param
 * @return
-------------------------------------------------------------*/
void uart0_receive_timer(void)
{
	if(uart0.timer>0)
	{
		if((--uart0.timer)==0)
		{
			uart0.done=1;
			uart0.buf[uart0.length] = '\0';
		}	
	}	
}

/*-------------------------------------------------------------
 * @brief USART中断
 * @param
 * @return
-------------------------------------------------------------*/
void uart1_receive_timer(void)
{
	if(uart1.timer>0)
	{
		if((--uart1.timer)==0)
		{
			uart1.done=1;
			uart1.buf[uart1.length] = '\0';
		}	
	}	
}

/*-------------------------------------------------------------
 * @brief USART中断
 * @param
 * @return
-------------------------------------------------------------*/
void uart_senddata(M0P_USART_TypeDef *USARTx, uint16_t u16Data)
{
    unsigned int timer=0;
	do
	{
		if(Usart_GetStatus(USARTx, UsartTxE)==TRUE)
		{
			break;
		}
        timer++;		
	}while(timer<60000);	
    USARTx->TDR = u16Data;
}

/*-------------------------------------------------------------
 * @brief 
 * @param
 * @return
-------------------------------------------------------------*/
void uart_send_string(M0P_USART_TypeDef *USARTx, char *str)
{
	while(*str)
	{
		uart_senddata(USARTx,*str);
		str++;
	}	
}

/*-------------------------------------------------------------
 * @brief 
 * @param
 * @return
-------------------------------------------------------------*/
void uart_send_array(M0P_USART_TypeDef *USARTx,unsigned char *buf,unsigned char len)
{
	unsigned char i ;
	for(i=0;i<len;i++)
	{
		uart_senddata(USARTx,buf[i]);
	}
}	

/*-------------------------------------------------------------
 * @brief USART中断
 * @param
 * @return
-------------------------------------------------------------*/
#if 0
int fputc(int ch, FILE *p) 
{
    unsigned int timer=0;
	do
	{
		if(Usart_GetStatus(M0P_USART0, UsartTxE)==TRUE)
		{
			break;
		}
        timer++;		
	}while(timer<60000);	
    M0P_USART0->TDR = ch;	
    return ch;
}
#endif






