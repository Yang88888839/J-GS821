
#define DRIVER_IWDT_C

#include "iwdt.h"
/*-------------------------------------------------------------
 * @brief
 * @param
 * @return
-------------------------------------------------------------*/
void Init_iwdt(void)
{
    stc_iwdt_init_t stcIwdtCfg;
    
    DDL_ZERO_STRUCT(stcIwdtCfg);
    
    /* 开启IWDT外设时钟 */
    Sysctrl_SetPeripheralGate(SysctrlPeripheralIwdt, TRUE);
    
    stcIwdtCfg.enAction = IwdtResetEn;
    stcIwdtCfg.enPrescaler = IwdtClkDiv512;
    stcIwdtCfg.u32Window = 0xFFFu;
    stcIwdtCfg.u32ArrCounter = 1024u;
    stcIwdtCfg.enIrqCfg = IwdtIrqDisable;
    stcIwdtCfg.enLpmCfg = IwdtDeepsleepStop;
    /* IWDT 初始化 */
    IWDT_Init(&stcIwdtCfg);
	/* 喂狗 */
	IWDT_Feed();   
}





















