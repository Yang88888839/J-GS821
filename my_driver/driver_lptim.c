
#define DRIVER_LPTIM_C

#include "bt.h"
#include "lpm.h"
#include "lptim.h"
#include "flash.h"

#include "driver_gpio.h"
#include "driver_timer.h"

#include "main.h"
#include "bsp_eeprom.h"

//#define  SYS_FREQUENCY  14700

unsigned int b_uart_tx=0;
/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void LpTim0_IRQHandler(void)
{
    if (TRUE == Lptim_GetItStatus(M0P_LPTIMER0))
    {
        Lptim_ClrItStatus(M0P_LPTIMER0); /* 清除LPTimer的中断标志位 */
        b_uart_tx=!b_uart_tx;			
    }
}

/*-------------------------------------------------------------
 * @brief 
 * @param
 * @return
-------------------------------------------------------------*/
void Init_lptim0(void)
{
    stc_lptim_cfg_t stcLptCfg;
    DDL_ZERO_STRUCT(stcLptCfg);

    /* 使能LPTIM0 外设时钟 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpTim0, TRUE);

    stcLptCfg.enGate   = LptimGateDisable;
    stcLptCfg.enGatep  = LptimGatePLowStop;
    stcLptCfg.enPrs    = LptimPrsDiv4;
    stcLptCfg.enTcksel = LptimPclk;
    stcLptCfg.enTogen  = LptimTogEnLow;
    stcLptCfg.enCt     = LptimTimerFun; /* 计数器功能 */
    stcLptCfg.enMd     = LptimMode2;    /* 工作模式为模式2自动重载16位计数器/定时器 */
    stcLptCfg.u16Arr   = 0x10000-310;    /* 预装载寄存器值 */
    Lptim_Init(M0P_LPTIMER0, &stcLptCfg);

    Lptim_ClrItStatus(M0P_LPTIMER0);  /* 清除中断标志位 */
    Lptim_ConfIt(M0P_LPTIMER0, TRUE); /* 允许LPTIMER中断 */
    EnableNvic(LPTIM_0_1_IRQn, IrqLevel3, TRUE);

    Lptim_SyncCntRst(M0P_LPTIMER0);
    //Lptim_Cmd(M0P_LPTIMER0, TRUE); /* LPT 运行 */	
}	

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return   
-------------------------------------------------------------*/
void debug_send(unsigned char datum)
{	
	unsigned int  j ;
	unsigned char i=0 ;
	
	Lptim_Cmd(M0P_LPTIMER0, TRUE);
	for(j=0;j<0xffffff;j++)
    {	
		if(b_uart_tx)
		{			
			i++;
			b_uart_tx=0;
			switch(i)
			{
				case 1 :	
				     break;
                case 2 :				
					 PW_debug_l();   //低电平
                     break;
				case 11 :
					 PW_debug_h();  //高电平
                     break;
				case 12 :
					 j=0xffffff;
				     break;
                default :
					 if((datum&0x01)==0x01)
					 {
						 PW_debug_h();
					 }
					 else
					 {
						 PW_debug_l();
					 }
					 datum>>=1;
                     break;					 
			}									
		}
    }
    Lptim_Cmd(M0P_LPTIMER0, FALSE);
}

/*-------------------------------------------------------------
 * @brief 
 * @param
 * @return
-------------------------------------------------------------*/
void debug_send_string(char *str)
{
	while(*str)
	{
		debug_send(*str);
		str++;
	}	
}

/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
#if 1
int fputc(int ch, FILE *p) 
{
    debug_send(ch);	
    return ch;
}
#endif













