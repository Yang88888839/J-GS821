/**
 *******************************************************************************
 * @file  hsi2c.c
 * @brief This file provides firmware functions to manage the HSI2C
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-05-23       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hsi2c.h"

/**
 * @addtogroup HC32L12X_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_HSI2C HSI2C模块驱动库
 * @brief HSI2C Driver Library HSI2C模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @addtogroup HSI2C_Global_Variables HSI2C全局变量定义
 * @{
 */
en_hsi2c_status_machine_t enMasterStatusMachine = Hsi2cStatusStart; /* 主机状态机状态 */
stc_hsi2c_master_init_t   stcHsi2cMasterInit    = {0x0u};           /* 主机初始化结构体 */
stc_hsi2c_slave_init_t    stcHsi2cSlaveInit     = {0x0u};           /* 从机初始化结构体 */
stc_hsi2c_com_t           stcHsi2cCom           = {0x0u};           /* 通信结构体 */
/**
 * @}
 */
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup HSI2C_Global_Functions HSI2C全局函数定义
 * @{
 */

/**
 * @addtogroup HSI2C_Global_Functions HSI2C全局函数定义
 * @{
 */

/**
 * @brief  HSI2C主机初始化
 * @param  [in] pstcHsi2cInit HSI2C主机配置结构体 @ref stc_hsi2c_master_init_t
 * @param  [in] u32SrcClockHz 时钟频率
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 */
en_result_t HSI2C_MasterInit(stc_hsi2c_master_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz)
{
    /* Master reset */
    if (pstcHsi2cInit->bResetBeforeInit)
    {
        HSI2C_MasterReset();
    }

    /* Debug enable setting */
    M0P_HSI2C->MCR_f.DBGEN = pstcHsi2cInit->enEnableDebug;

    /* Master config register setting */
    HSI2C_MasterMcfgr1Config((stc_hsi2c_master_config1_t *)(&pstcHsi2cInit->stcMasterConfig1));
    HSI2C_MasterMcfgr2Config((stc_hsi2c_master_config2_t *)(&pstcHsi2cInit->stcMasterConfig2));
    HSI2C_MasterMcfgr3Config((stc_hsi2c_master_config3_t *)(&pstcHsi2cInit->stcMasterConfig3));

    /* Baud rate setting */
    if (Ok != HSI2C_MasterBaudRateSet(pstcHsi2cInit, u32SrcClockHz))
    {
        return Error;
    }
    M0P_HSI2C->MDER = (uint32_t)pstcHsi2cInit->enDma;

    /* Master enable, slave disable */
    HSI2C_SlaveDisable();
    HSI2C_MasterEnable();

    return Ok;
}

/**
 * @brief  HSI2C主机波特率设置
 * @param  [in] pstcHsi2cInit HSI2C主机配置结构体 @ref stc_hsi2c_master_init_t
 * @param  [in] u32SrcClockHz 时钟频率
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 */
en_result_t HSI2C_MasterBaudRateSet(const stc_hsi2c_master_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz)
{
    uint8_t  u8MasterEnableStatus = 0x0u;
    uint8_t  u8FilterScl          = 0x0u;
    uint8_t  u8Prescale           = 0x0u;
    uint32_t u32ClockCycle        = 0x0u;
    uint32_t u32SclLatency        = 0x0u;
    uint32_t u32SclPeriod         = 0x0u;
    uint32_t u32ErrorOffset       = 0x0u;
    uint32_t u32CalculateBaudRate = 0x0u;
    uint16_t u16Divider           = 1u;

    uint8_t  u8ClockHigh      = 0x0u;
    uint8_t  u8ClockLow       = 0x0u;
    uint8_t  u8HoldDelay      = 0x0u;
    uint8_t  u8DataValidDelay = 0x0u;
    uint8_t  u8BestClockCycle = 0x0u;
    uint8_t  u8BestPrescale   = 0x0u;
    uint8_t  u8BestDivider    = 0x0u;
    uint32_t u32BestError     = 0xFFFFFFFFu;

    /* Disable slave mode and backup master enable status */
    M0P_HSI2C->SCR0         = 0;
    u8MasterEnableStatus = M0P_HSI2C->MCR_f.MEN;
    M0P_HSI2C->MCR_f.MEN    = 0u;

    /* Baud rate = (u32SrcClockHz / 2 ^ PRESCALE) / (CLKHI + CLKLO + 2 + SCL_LATENCY)
     * SCL_LATENCY = ROUNDDOWN ( (2 + FILTSCL + SCL_RISETIME) / (2 ^ PRESCALE) )
     */
    u8FilterScl = M0P_HSI2C->MCFGR2_f.FILTSCL;
    for (u8Prescale = 0u; u8Prescale <= 7u; u8Prescale++)
    {
        /* Calculate the u32ClockCycle, u32ClockCycle = CLKLO + CLKHI, u16Divider = 2 ^ u8Prescale */
        u32SclLatency    = (2u + u8FilterScl) / u16Divider;
        uint32_t u32Temp = (uint32_t)((10u * u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / u16Divider + 5u) / 10u);
        if (u32Temp >= u32SclLatency + 2u)
        {
            u32ClockCycle = u32Temp - u32SclLatency - 2u;
        }
        else
        {
            u32ClockCycle = 0u;
        }

        if (u32ClockCycle > (120u - u32SclLatency))
        {
            u16Divider *= 2u;
            if (u16Divider == 256)
            {
                return Error; /* Invalid setting of source clock or baud rate */
            }
            else
            {
                continue;
            }
        }

        /* Calculate the computed baudrate and compare it with the desired baudrate */
        u32CalculateBaudRate = (u32SrcClockHz / (uint32_t)u16Divider) / ((uint32_t)u32ClockCycle + 2U + u32SclLatency);
        u32ErrorOffset       = pstcHsi2cInit->u32BaudRateHz > u32CalculateBaudRate ? pstcHsi2cInit->u32BaudRateHz - u32CalculateBaudRate :
                                                                                     u32CalculateBaudRate - pstcHsi2cInit->u32BaudRateHz;
        if (u32ErrorOffset < u32BestError)
        {
            u8BestPrescale   = u8Prescale;
            u8BestDivider    = u16Divider;
            u8BestClockCycle = u32ClockCycle;
            u32BestError     = u32ErrorOffset;

            /* Target baud rate is achieved */
            if (u32ErrorOffset == 0u)
            {
                break;
            }
        }
        u16Divider *= 2u;
    }

    u32SclLatency = (2u + u8FilterScl) / u8BestDivider;
    u32SclPeriod  = u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / u8BestDivider;
    /* Clock high period */
    u8ClockHigh = (u8BestClockCycle - u32SclLatency) / 2u;
    while (u8ClockHigh > (u8BestClockCycle - 52u * u32SclPeriod / 100u + 1u))
    {
        if (u8ClockHigh > 1u)
        {
            u8ClockHigh--;
        }
        else
        {
            u8ClockHigh = 1u;
            break;
        }
    }
    if (u8ClockHigh < 1)
    {
        u8ClockHigh++;
    }

    /* Clock low period */
    if (u8BestClockCycle >= u8ClockHigh)
    {
        u8ClockLow = (uint32_t)u8BestClockCycle - (uint32_t)u8ClockHigh;
    }
    else
    {
        return Error; /* Invalid setting of source clock or baud rate */
    }
    if (u8ClockHigh >= u8ClockLow)
    {
        return Error; /* Invalid setting of source clock or baud rate */
    }
    /* Setup hold delay */
    u8HoldDelay = (uint8_t)(u32SclPeriod / 2u) - 1u;
    /* Data valid delay */
    u8DataValidDelay = (uint8_t)(u32SclPeriod / 4u) - 1u;
    /* Filter SDA */
    if ((u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / 20u) > (u8BestDivider + 2u))
    {
        /* Read out the FILTSDA configuration, if it is smaller than expected, change the setting. */
        uint8_t u8FilterSda = M0P_HSI2C->MCFGR2_f.FILTSDA;
        if (u8FilterSda < (u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / 20u - u8BestDivider - 2u))
        {
            u8FilterSda = (uint8_t)(u32SrcClockHz / pstcHsi2cInit->u32BaudRateHz / 20u) - u8BestDivider - 2u;
        }
        M0P_HSI2C->MCFGR2_f.FILTSDA = u8FilterSda;
    }

    /* Set CLKHI, CLKLO, SETHOLD, DATAVD value */
    M0P_HSI2C->MCCR0 = ((uint32_t)u8ClockHigh << 8u) | ((uint32_t)u8ClockLow << 0u)
                    | ((uint32_t)u8HoldDelay << 16u) | ((uint32_t)u8DataValidDelay << 24u);

    /* Set prescale value */
    M0P_HSI2C->MCFGR1_f.PRESCALE = u8BestPrescale;

    /* Restore master enable status */
    M0P_HSI2C->MCR_f.MEN = u8MasterEnableStatus;

    return Ok;
}
/**
 * @brief  HSI2C主机中断传输设置
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @param  [in] pu8Data 传输数据首地址
 * @param  [in] u32Size 传输数据长度（字节）
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 */
en_result_t HSI2C_MasterTransferInt(uint8_t *pu8Data, uint32_t u32Size)
{
    en_result_t enResult = Ok;
    DDL_ZERO_STRUCT(stcHsi2cCom);

    if (Hsi2cComIdle == stcHsi2cCom.enComStatus)
    {
        if (TRUE == HSI2C_MasterFlagGet(Hsi2cMskMasterStaBbf)) /* Bus busy */
        {
            enResult = Error;
        }
        else
        {
            enMasterStatusMachine      = Hsi2cStatusStart;
            stcHsi2cCom.enComStatus    = Hsi2cComBusy;
            stcHsi2cCom.u32DataIndex   = 0;
            stcHsi2cCom.u32Len         = u32Size;
            stcHsi2cCom.pu8Buf         = pu8Data;

            stcHsi2cCom.u32RxSize = (uint16_t)stcHsi2cCom.u32Len;

            HSI2C_MasterIntDisable(Hsi2cMskMasterItAll);     /* Disable interrupts */
            HSI2C_MasterFlagClear(Hsi2cMskMasterFlagClrAll); /* Clear flags */

            M0P_HSI2C->MCFGR1_f.AUTOSTOP = 0u; /* Disable auto-stop */

            HSI2C_MasterIntEnable(Hsi2cMskMasterItAll); /* Enable interrupts */
        }
    }
    else
    {
        enResult = Error;
    }

    return enResult;
}

/**
 * @brief  HSI2C主机状态机控制（Start）
 * @retval None
 */
void HSI2C_MasterStatusMachineStart(void)
{
    if (stcHsi2cMasterInit.u8SubAddrSize != 0x0u) /* 需要发送Sub address */
    {
        HSI2C_MasterStart(stcHsi2cMasterInit.u8SlaveAddr, Hsi2cMasterWriteSlaveRead); /* Start 主机写，从机读 */
        enMasterStatusMachine = Hsi2cStatusSubAddr;                                                               /* 状态：发送Sub address */
    }
    else /* 无需发送Sub address */
    {
        if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* 主机写，从机读 */
        {
            HSI2C_MasterStart(stcHsi2cMasterInit.u8SlaveAddr, Hsi2cMasterWriteSlaveRead); /* Start 主机写，从机读 */
            enMasterStatusMachine = Hsi2cStatusTransData;                                                             /* 状态：传送数据 */
        }
        else /* 主机读，从机写 */
        {
            HSI2C_MasterStart(stcHsi2cMasterInit.u8SlaveAddr, Hsi2cMasterReadSlaveWrite); /* Start 主机读，从机写 */
            enMasterStatusMachine = Hsi2cStatusRxCmd;                                                                 /* 状态：接收命令 */
        }
    }
}

/**
 * @brief  HSI2C主机状态机控制（Sub address）
 * @retval None
 */
void HSI2C_MasterStatusMachineSubAddr(void)
{
    if (stcHsi2cCom.u32DataIndex < stcHsi2cMasterInit.u8SubAddrSize) /* 发送Sub address */
    {
        M0P_HSI2C->MTDR =
            HSI2C_CMD_TX_DATA | (uint32_t)(stcHsi2cMasterInit.u8SubAddr[stcHsi2cMasterInit.u8SubAddrSize - stcHsi2cCom.u32DataIndex - 1]);
        stcHsi2cCom.u32DataIndex++;

        if (stcHsi2cCom.u32DataIndex >= stcHsi2cMasterInit.u8SubAddrSize)
        {                                                              /* Sub address已发送完成 */
            if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* 主机写，从机读 */
            {
                enMasterStatusMachine = Hsi2cStatusTransData; /* 状态：传送数据 */
            }
            else /* 主机读，从机写 */
            {
                if (stcHsi2cMasterInit.u8SubAddrSize != 0x0u) /* 已发送Sub address */
                {
                    enMasterStatusMachine = Hsi2cStatusRestart; /* 状态：Restart */
                }
                else /* 未发送Sub address */
                {
                    enMasterStatusMachine = Hsi2cStatusRxCmd; /* 状态：接收命令 */
                }
            }
            stcHsi2cCom.u32DataIndex = 0;
        }
    }
}

/**
 * @brief  HSI2C主机状态机控制（Restart）
 * @retval None
 */
void HSI2C_MasterStatusMachineRestart(void)
{
    if (stcHsi2cMasterInit.enDir == Hsi2cMasterReadSlaveWrite)
    {
        HSI2C_MasterStart(stcHsi2cMasterInit.u8SlaveAddr, Hsi2cMasterReadSlaveWrite); /* Restart 主机读，从机写 */
        enMasterStatusMachine = Hsi2cStatusRxCmd;  /* 状态：接收命令 */
    }
}

/**
 * @brief
 * @retval None
 */
/**
 * @brief  HSI2C主机状态机控制（Receive command）
 * @param  [in] pu32RxLen 接收数据长度指针值
 * @retval None
 */
void HSI2C_MasterStatusMachineRxCmd(uint32_t *pu32RxLen)
{
    if (stcHsi2cMasterInit.enDir == Hsi2cMasterReadSlaveWrite) /* 主机读，从机写 */
    {
        if (*pu32RxLen > 256U) /* Send receive and length(高字节) command */
        {
            M0P_HSI2C->MTDR = (uint32_t)(HSI2C_CMD_RX_DATA) | 0xFFul;
            *pu32RxLen -= 256U;
        }
        else /* Send receive and length(低字节) command */
        {
            M0P_HSI2C->MTDR = (uint32_t)(HSI2C_CMD_RX_DATA) | ((uint32_t)(stcHsi2cCom.u32RxSize - 1U));
            enMasterStatusMachine = Hsi2cStatusTransData; /* 状态：传送数据 */
        }
    }
}

/**
 * @brief  HSI2C主机状态机控制（Data transfer）
 * @retval None
 */
void HSI2C_MasterStatusMachineTrans(void)
{
    if (stcHsi2cCom.u32DataIndex >= stcHsi2cCom.u32Len) /* Transfer length is finished */
    {
        if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* 主机写，从机读 */
        {
            enMasterStatusMachine = Hsi2cStatusStop; /* 状态：Stop */
        }
        else /* 主机读，从机写 */
        {
            HSI2C_MasterStop(); /* Send stop command */
            enMasterStatusMachine = Hsi2cStatusWaitEnd;   /* 状态：等待结束 */
            /* Will send NACK automatically when Rx transfer size is finished */
        }
        stcHsi2cCom.u32DataIndex = 0;
    }
}

/**
 * @brief  HSI2C主机状态机控制（Stop）
 * @retval None
 */
void HSI2C_MasterStatusMachineStop(void)
{
    if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* 主机写，从机读 */
    {
        HSI2C_MasterStop(); /* Send stop command */
        enMasterStatusMachine = Hsi2cStatusWaitEnd;   /* 状态：等待结束 */
    }
}

/**
 * @brief  HSI2C主机轮询传输设置
 * @param  [in] pu8Data 传输数据首地址
 * @param  [in] u32Size 传输数据长度（字节）
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 *           - ErrorTimeout：超时
 */
en_result_t HSI2C_MasterTransferPoll(uint8_t *pu8Data, uint32_t u32Size, uint32_t u32Timeout)
{
    uint32_t    u32Flag  = 0;
    en_result_t enResult = Ok;
    DDL_ZERO_STRUCT(stcHsi2cCom);

    if (Hsi2cComIdle == stcHsi2cCom.enComStatus)
    {
        if (TRUE == HSI2C_MasterFlagGet(Hsi2cMskMasterStaBbf))
        {
            enResult = Error;
        }
        else
        {
            enMasterStatusMachine = Hsi2cStatusStart;

            stcHsi2cCom.enComStatus    = Hsi2cComBusy;
            stcHsi2cCom.u32DataIndex   = 0;
            stcHsi2cCom.u32Len         = u32Size;
            stcHsi2cCom.pu8Buf         = pu8Data;

            stcHsi2cCom.u32RxSize = stcHsi2cCom.u32Len;

            HSI2C_MasterFlagClear(Hsi2cMskMasterFlagClrAll); /* Clear flags */

            M0P_HSI2C->MCFGR1_f.AUTOSTOP = 0u; /* Disable auto-stop */

            while (1)
            {
                if (0x0u == u32Timeout--)
                {
                    enResult = ErrorTimeout; /* 等待超时 */
                    break;
                }
                u32Flag = M0P_HSI2C->MSR;
                M0P_HSI2C->MSCR = u32Flag;

                if (Hsi2cComSuccess == HSI2C_MasterErrorGet(u32Flag))
                {
                    switch (enMasterStatusMachine)
                    {
                        case Hsi2cStatusStart:
                            HSI2C_MasterStatusMachineStart();
                            break;
                        case Hsi2cStatusSubAddr:
                            if ((u32Flag & Hsi2cMskMasterStaItTd) == Hsi2cMskMasterStaItTd)
                            {
                                HSI2C_MasterStatusMachineSubAddr();
                            }
                            break;
                        case Hsi2cStatusRestart:
                            if ((u32Flag & Hsi2cMskMasterStaItTd) == Hsi2cMskMasterStaItTd)
                            {
                                HSI2C_MasterStatusMachineRestart();
                            }
                            break;
                        case Hsi2cStatusRxCmd:
                            if ((u32Flag & Hsi2cMskMasterStaItTd) == Hsi2cMskMasterStaItTd)
                            {
                                HSI2C_MasterStatusMachineRxCmd(&stcHsi2cCom.u32RxSize);
                            }
                            break;
                        case Hsi2cStatusTransData:
                            if (stcHsi2cCom.u32DataIndex < stcHsi2cCom.u32Len) /* Data transmit or receive */
                            {
                                if ((u32Flag & Hsi2cMskMasterStaItTd) == Hsi2cMskMasterStaItTd)
                                {
                                    if (stcHsi2cMasterInit.enDir == Hsi2cMasterWriteSlaveRead) /* Transmit */
                                    {
                                        HSI2C_MasterWriteData(stcHsi2cCom.pu8Buf[stcHsi2cCom.u32DataIndex++]);
                                    }
                                }
                                if ((u32Flag & Hsi2cMskMasterStaItRd) == Hsi2cMskMasterStaItRd)
                                {
                                    if (stcHsi2cMasterInit.enDir == Hsi2cMasterReadSlaveWrite) /* Recieve */
                                    {
                                        if (Ok == HSI2C_MasterReadData(&stcHsi2cCom.pu8Buf[stcHsi2cCom.u32DataIndex]))
                                        {
                                            stcHsi2cCom.u32DataIndex++;
                                        }
                                    }
                                }
                            }
                            HSI2C_MasterStatusMachineTrans();
                            break;
                        case Hsi2cStatusStop:
                            if ((u32Flag & Hsi2cMskMasterStaItTd) == Hsi2cMskMasterStaItTd)
                            {
                                HSI2C_MasterStatusMachineStop();
                            }
                            break;
                        case Hsi2cStatusWaitEnd:
                            /* Wait for transfer end */
                            if (u32Flag & Hsi2cMskMasterStaItSd)
                            {
                                stcHsi2cCom.enComStatus = Hsi2cComIdle;
                            }
                            break;
                        default:
                            break;
                    }

                    if (stcHsi2cCom.enComStatus == Hsi2cComIdle)
                    {
                        break; /* Transfer完成 */
                    }
                }
                else /* Error handling */
                {
                    /* Disable all master interrupts */
                    HSI2C_MasterIntDisable(Hsi2cMskMasterItAll);

                    /* Arbitration lost? */
                    if (u32Flag & Hsi2cMskMasterStaItAl)
                    {
                        /* Reset master */
                        HSI2C_MasterReset();
                    }
                    /* Pin low timeout? */
                    else if (u32Flag & Hsi2cMskMasterStaItPlt)
                    {
                        /* Reset master */
                        HSI2C_MasterReset();
                        /* ======================================= */
                        /* ==========       WARNING       ======== */
                        /* ======================================= */
                        /* 1. 根据实际情况添加代码处理引脚低条件      */
                        /* 2. 当引脚低超时持续时，PLTF不能被清除掉    */
                        /* 3. 在I2C可以开始启动条件之前，必须清除PLTF */
                    }
                    /* Master busy? */
                    else if (u32Flag & Hsi2cMskMasterStaMbf)
                    {
                        /* Send stop command */
                        HSI2C_MasterStop();
                    }
                    else
                    {
                        ;
                    }

                    stcHsi2cCom.enComStatus = Hsi2cComIdle;
                    enResult                = Error;
                    break;
                }
            }
        }
    }
    else
    {
        enResult = Error;
    }
    return enResult;
}

/**
 * @brief  HSI2C从机初始化
 * @param  [in] pstcHsi2cInit HSI2C从机配置结构体 @ref stc_hsi2c_slave_init_t
 * @param  [in] u32SrcClockHz 时钟频率
 * @retval None
 */
void HSI2C_SlaveInit(stc_hsi2c_slave_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz)
{
    /* Slave reset */
    if (pstcHsi2cInit->bResetBeforeInit)
    {
        HSI2C_SlaveReset();
    }

    /* Slave control register setting */
    HSI2C_SlaveScr1Config((stc_hsi2c_slave_control1_t *)(&pstcHsi2cInit->stcSlaveConfig1));
    HSI2C_SlaveScr2Config((stc_hsi2c_slave_control2_t *)(&pstcHsi2cInit->stcSlaveConfig2));

    /* Configure slave address */
    M0P_HSI2C->SADDR_f.ADDR0 = pstcHsi2cInit->u32SlaveAddr0;
    M0P_HSI2C->SADDR_f.ADDR1 = pstcHsi2cInit->u32SlaveAddr1;
    
    M0P_HSI2C->SDER = (uint32_t)pstcHsi2cInit->enDma;

    /* Slave enable, master disable */
    HSI2C_MasterDisable();
    HSI2C_SlaveEnable();
}

/**
 * @brief  HSI2C从机中断传输设置
 * @param  [in] pu8Data 传输数据首地址
 * @param  [in] u32Size 传输数据长度（字节）
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 */
en_result_t HSI2C_SlaveTransferInt( uint8_t *pu8Data, uint32_t u32Size)
{
    en_result_t enResult = Ok;
    DDL_ZERO_STRUCT(stcHsi2cCom);

    if (Hsi2cComIdle == stcHsi2cCom.enComStatus)
    {
        if (TRUE == HSI2C_SlaveFlagGet(Hsi2cMskSlaveStaBbf)) /* Bus busy */
        {
            enResult = Error;
        }
        else
        {
            enMasterStatusMachine      = Hsi2cStatusStart;
            stcHsi2cCom.enComStatus    = Hsi2cComBusy;
            stcHsi2cCom.u32DataIndex   = 0;
            stcHsi2cCom.u32Len         = u32Size;
            stcHsi2cCom.pu8Buf         = pu8Data;

            stcHsi2cCom.u32RxSize = stcHsi2cSlaveInit.u8SubAddrSize;

            HSI2C_SlaveIntDisable(Hsi2cMskSlaveItAll);     /* Disable interrupts */
            HSI2C_SlaveFlagClear(Hsi2cMskSlaveFlagClrAll); /* Clear flags */
            HSI2C_SlaveIntEnable(Hsi2cMskSlaveItAll);      /* Enable interrupts */
        }
    }
    else
    {
        enResult = Error;
    }

    return enResult;
}

/**
 * @brief  HSI2C从机轮询传输设置
 * @param  [in] pu8Data 传输数据首地址
 * @param  [in] u32Size 传输数据长度（字节）
 * @retval en_result_t
 *           - Ok: 设置成功
 *           - Error: 设置失败
 *           - ErrorTimeout：超时
 */
en_result_t HSI2C_SlaveTransferPoll(uint8_t *pu8Data, uint32_t u32Size, uint32_t u32Timeout)
{
    en_result_t enResult = Ok;
    uint32_t    u32Flag  = 0;
    DDL_ZERO_STRUCT(stcHsi2cCom);

    if (Hsi2cComIdle == stcHsi2cCom.enComStatus)
    {
        if (TRUE == HSI2C_SlaveFlagGet(Hsi2cMskSlaveStaBbf))
        {
            enResult = Error;
        }
        else
        {
            enMasterStatusMachine      = Hsi2cStatusStart;
            stcHsi2cCom.enComStatus    = Hsi2cComBusy;
            stcHsi2cCom.u32DataIndex   = 0U;
            stcHsi2cCom.u32Len         = u32Size;
            stcHsi2cCom.pu8Buf         = pu8Data;

            stcHsi2cCom.u32RxSize = stcHsi2cSlaveInit.u8SubAddrSize;

            HSI2C_SlaveFlagClear(Hsi2cMskSlaveFlagClrAll); /* Clear flags */

            while (1)
            {
                if (0x0u == u32Timeout--)
                {
                    enResult = ErrorTimeout; /* 等待超时 */
                    break;
                }

                u32Flag = M0P_HSI2C->SSR;
                M0P_HSI2C->SSCR = u32Flag;

                if (Hsi2cComSuccess == HSI2C_SlaveErrorGet(u32Flag))
                {
                    /* Receive */
                    if (u32Flag & Hsi2cMskSlaveStaItRd)
                    {
                        uint32_t u32RxData = M0P_HSI2C->SRDR;
                        if (!(u32RxData & 0x4000u))   //SRDR.REMP_MSK:0x4000u
                        {
                            if (0 != stcHsi2cCom.u32RxSize) /* 需要接收Sub address */
                            {
                                stcHsi2cCom.u8SubAddr[stcHsi2cCom.u32RxSize - 1] = (uint8_t)(u32RxData);
                                stcHsi2cCom.u32RxSize--;
                            }
                            else /* 不需要接收Sub address */
                            {
                                if (stcHsi2cCom.u32DataIndex < stcHsi2cCom.u32Len)
                                {
                                    stcHsi2cCom.pu8Buf[stcHsi2cCom.u32DataIndex++] = (uint8_t)(u32RxData);
                                }
                                if (stcHsi2cCom.u32DataIndex >= stcHsi2cCom.u32Len)
                                {
                                    M0P_HSI2C->STAR = 1u; /* Send NACK */
                                    stcHsi2cCom.u32DataIndex         = 0;
                                }
                            }
                        }
                    }

                    /* Transmit */
                    if (u32Flag & Hsi2cMskSlaveStaItTd)
                    {
                        if (stcHsi2cCom.u32DataIndex < stcHsi2cCom.u32Len)
                        {
                            HSI2C_SlaveWriteData(stcHsi2cCom.pu8Buf[stcHsi2cCom.u32DataIndex++]);
                        }
                        if (stcHsi2cCom.u32DataIndex >= stcHsi2cCom.u32Len)
                        {
                            stcHsi2cCom.u32DataIndex = 0;
                        }
                    }

                    /* Stop or restart */
                    if (u32Flag & (Hsi2cMskSlaveStaItRs | Hsi2cMskSlaveStaItSd))
                    {
                        if (u32Flag & Hsi2cMskSlaveStaItSd)
                        {
                            stcHsi2cCom.enComStatus = Hsi2cComIdle;
                        }
                        M0P_HSI2C->STAR = 0;
                    }

                    /* Valid address */
                    if (u32Flag & (Hsi2cMskSlaveStaItAv | Hsi2cMskSlaveStaItAm0 | Hsi2cMskSlaveStaItAm1))
                    {
                        /* Get received slave address */
                        volatile uint32_t u32Temp = M0P_HSI2C->SASR;
                    }

                    /* Transmit ACK */
                    if (u32Flag & Hsi2cMskSlaveStaItTa)
                    {
                        M0P_HSI2C->STAR = 0;
                    }

                    if (stcHsi2cCom.enComStatus == Hsi2cComIdle)
                    {
                        break; /* Transfer完成 */
                    }
                }
                else /* Error handling */
                {
                    HSI2C_SlaveTransAbort();
                    stcHsi2cCom.enComStatus = Hsi2cComIdle;
                    enResult                = Error;
                    break;
                }
            }
        }
    }
    return enResult;
}

/**
 * @brief  主机配置寄存器1设置(MCFGR1寄存器设置)
 * @param  [in] pstcHsi2cConfig MCFGR1寄存器配置结构体 @ref stc_hsi2c_master_config1_t
 * @retval None
 */
void HSI2C_MasterMcfgr1Config(stc_hsi2c_master_config1_t *pstcHsi2cConfig)
{
    M0P_HSI2C->MCFGR1_f.MATCFG = pstcHsi2cConfig->enMatchConfig;
    M0P_HSI2C->MCFGR1_f.RDMO   = pstcHsi2cConfig->enReceiveDataMatchOnly;
    M0P_HSI2C->MCFGR1_f.TIMECFG = pstcHsi2cConfig->enTimeoutConfig;
    M0P_HSI2C->MCFGR1_f.IGNACK  = pstcHsi2cConfig->enIgnoreNack;
    M0P_HSI2C->MCFGR1_f.AUTOSTOP = pstcHsi2cConfig->enAutoStop;
}

/**
 * @brief  主机配置寄存器2设置(MCFGR2寄存器设置)
 * @param  [in] pstcHsi2cConfig MCFGR2寄存器配置结构体 @ref stc_hsi2c_master_config2_t
 * @retval None
 */
void HSI2C_MasterMcfgr2Config(stc_hsi2c_master_config2_t *pstcHsi2cConfig)
{    
    M0P_HSI2C->MCFGR2_f.FILTSDA = pstcHsi2cConfig->u32SdaGlitchFilterConfig;
    M0P_HSI2C->MCFGR2_f.FILTSCL = pstcHsi2cConfig->u32SclGlitchFilterConfig;
    M0P_HSI2C->MCFGR2_f.BUSIDLE = pstcHsi2cConfig->u32BusIdleTimeout;
    M0P_HSI2C->MCFGR2_f.FILTBPSDA = pstcHsi2cConfig->enSdaFilterEnable;
    M0P_HSI2C->MCFGR2_f.FILTBPSCL = pstcHsi2cConfig->enSclFilterEnable;
}

/**
 * @brief  主机配置寄存器3设置(MCFGR3寄存器设置)
 * @param  [in] pstcHsi2cConfig MCFGR3寄存器配置结构体 @ref stc_hsi2c_master_config3_t
 * @retval None
 */
void HSI2C_MasterMcfgr3Config(stc_hsi2c_master_config3_t *pstcHsi2cConfig)
{
    M0P_HSI2C->MCFGR3_f.PINLOW = pstcHsi2cConfig->u32PinLowTimeout;
}

/**
 * @brief  主机数据配置设置(MDMR寄存器设置)
 * @param  [in] u32MatchValue0 Compared against the received data when receive data match is enabled. 数据范围：0 ~ 0xFF
 * @param  [in] u32MatchValue1 Compared against the received data when receive data match is enabled. 数据范围：0 ~ 0xFF
 * @retval None
 */
void HSI2C_MasterDataMatchConfig(uint32_t u32MatchValue0, uint32_t u32MatchValue1)
{
    M0P_HSI2C->MDMR_f.MATCH0 = u32MatchValue0;
    M0P_HSI2C->MDMR_f.MATCH1 = u32MatchValue1;
}

/**
 * @brief  从机控制寄存器2设置(SCR1寄存器设置)
 * @param  [in] pstcHsi2cConfig SCR1寄存器配置结构体 @ref stc_hsi2c_slave_control1_t
 * @retval None
 */
void HSI2C_SlaveScr1Config(stc_hsi2c_slave_control1_t *pstcHsi2cConfig)
{
    M0P_HSI2C->SCR1 = pstcHsi2cConfig->u32FuncSelect | (uint32_t)pstcHsi2cConfig->enConfigAddrMatchMode;
}

/**
 * @brief  从机控制寄存器2设置(SCR2寄存器设置)
 * @param  [in] pstcHsi2cConfig SCR2寄存器配置结构体 @ref stc_hsi2c_slave_control2_t
 * @retval None
 */
void HSI2C_SlaveScr2Config(stc_hsi2c_slave_control2_t *pstcHsi2cConfig)
{
    M0P_HSI2C->SCR2_f.CLKHOLD = pstcHsi2cConfig->u32TimingClockHoldTime;
    M0P_HSI2C->SCR2_f.DATAVD = pstcHsi2cConfig->u32TimingDataValidDelay;
    M0P_HSI2C->SCR2_f.FILTSDA = pstcHsi2cConfig->u32SdaGlitchFilterWidth;
    M0P_HSI2C->SCR2_f.FILTSCL = pstcHsi2cConfig->u32SclGlitchFilterWidth;
    M0P_HSI2C->SCR2_f.FILTEN = pstcHsi2cConfig->enFilterEnable;
}

/**
 * @brief  HSI2C主机软件复位
 * @param  [in] None
 * @retval None
 */
void HSI2C_MasterReset(void)
{
    M0P_HSI2C->MCR_f.RST = 1u;
    M0P_HSI2C->MCR_f.RST = 0u;
}

/**
 * @brief  HSI2C从机软件复位
 * @param  [in] None
 * @retval None
 */
void HSI2C_SlaveReset(void)
{
    M0P_HSI2C->SCR0_f.RST = 1u;
    M0P_HSI2C->SCR0_f.RST = 0u;
}

/**
 * @brief  HSI2C主机使能
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_MasterEnable(void)
{
    M0P_HSI2C->MCR_f.MEN = 1u;
}

/**
 * @brief  HSI2C主机禁止
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_MasterDisable(void)
{
    M0P_HSI2C->MCR_f.MEN = 0u;
}

/**
 * @brief  HSI2C从机使能
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_SlaveEnable(void)
{
    M0P_HSI2C->SCR0_f.SEN = 1u;
}

/**
 * @brief  HSI2C从机禁止
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_SlaveDisable(void)
{
    M0P_HSI2C->SCR0_f.SEN = 0u;
}

/**
 * @brief  HSI2C主机标志位获取
 * @param  [in] enHsi2cFlag HSI2C主机标志位选择 @ref en_hsi2c_mst_flag_it_t
 * @retval boolean_t
 *           - TRUE: 标志置位
 *           - FALSE: 标志未置位
 */
boolean_t HSI2C_MasterFlagGet(en_hsi2c_mst_flag_it_t enHsi2cFlag)
{
    return READ_BIT(M0P_HSI2C->MSR, (uint32_t)enHsi2cFlag) ? TRUE : FALSE;
}

/**
 * @brief  HSI2C从机标志位获取
 * @param  [in] enHsi2cFlag HSI2C从机标志位选择 @ref en_hsi2c_slv_flag_it_t
 * @retval boolean_t
 *           - TRUE: 标志置位
 *           - FALSE: 标志未置位
 */
boolean_t HSI2C_SlaveFlagGet(en_hsi2c_slv_flag_it_t enHsi2cFlag)
{
    return READ_BIT(M0P_HSI2C->SSR, (uint32_t)enHsi2cFlag) ? TRUE : FALSE;
}

/**
 * @brief  HSI2C主机标志位清除
 * @param  [in] enHsi2cFlag HSI2C主机标志位选择 @ref en_hsi2c_mst_flag_it_t
 * @retval None
 */
void HSI2C_MasterFlagClear(en_hsi2c_mst_flag_it_t enHsi2cFlag)
{
    SET_BIT(M0P_HSI2C->MSCR, (uint32_t)enHsi2cFlag);
}

/**
 * @brief  HSI2C从机标志位清除
 * @param  [in] enHsi2cFlag HSI2C从机标志位选择 @ref en_hsi2c_slv_flag_it_t
 * @retval None
 */
void HSI2C_SlaveFlagClear(en_hsi2c_slv_flag_it_t enHsi2cFlag)
{
    SET_BIT(M0P_HSI2C->SSCR, (uint32_t)enHsi2cFlag);
}

/**
 * @brief  HSI2C主机中断使能
 * @param  [in] enHsi2cIrq HSI2C主机中断选择 @ref en_hsi2c_mst_flag_it_t
 * @retval None
 */
void HSI2C_MasterIntEnable(en_hsi2c_mst_flag_it_t enHsi2cIrq)
{
    SET_BIT(M0P_HSI2C->MIER, (uint32_t)enHsi2cIrq);
}

/**
 * @brief  HSI2C主机中断禁止
 * @param  [in] enHsi2cIrq HSI2C主机中断选择 @ref en_hsi2c_mst_flag_it_t
 * @retval None
 */
void HSI2C_MasterIntDisable(en_hsi2c_mst_flag_it_t enHsi2cIrq)
{
    CLEAR_BIT(M0P_HSI2C->MIER, (uint32_t)enHsi2cIrq);
}

/**
 * @brief  HSI2C从机中断使能
 * @param  [in] enHsi2cIrq HSI2C从机中断选择 @ref en_hsi2c_slv_flag_it_t
 * @retval None
 */
void HSI2C_SlaveIntEnable(en_hsi2c_slv_flag_it_t enHsi2cIrq)
{
    SET_BIT(M0P_HSI2C->SIER, (uint32_t)enHsi2cIrq);
}

/**
 * @brief  HSI2C从机中断禁止
 * @param  [in] enHsi2cIrq HSI2C从机中断选择 @ref en_hsi2c_slv_flag_it_t
 * @retval None
 */
void HSI2C_SlaveIntDisable(en_hsi2c_slv_flag_it_t enHsi2cIrq)
{
    CLEAR_BIT(M0P_HSI2C->SIER, (uint32_t)enHsi2cIrq);
}
/**
 * @brief  HSI2C主机中断使能获取
 * @retval uint32_t 主机中断使能寄存器值
 */
uint32_t HSI2C_MasterIntGet(void)
{
    return READ_REG(M0P_HSI2C->MIER);
}

/**
 * @brief  HSI2C从机中断使能获取
 * @retval uint32_t 从机中断使能寄存器值
 */
uint32_t HSI2C_SlaveIntGet(void)
{
    return READ_REG(M0P_HSI2C->SIER);
}

/**
 * @brief  HSI2C主机Start命令
 * @param  [in] u8SlaveAddr 从机地址
 * @param  [in] enTransDir 传输方向 @ref en_hsi2c_dir_t
 * @retval None
 */
void HSI2C_MasterStart(uint8_t u8SlaveAddr, en_hsi2c_dir_t enTransDir)
{
    M0P_HSI2C->MTDR = HSI2C_CMD_START_TX_DATA | (((uint32_t)u8SlaveAddr << 1u) + (uint32_t)enTransDir);
}

/**
 * @brief  HSI2C主机Stop命令
 * @param  [in] HSI2Cx HSI2Cx通道 @ref HSI2C_TypeDef
 * @retval None
 */
void HSI2C_MasterStop(void)
{
    M0P_HSI2C->MTDR = HSI2C_CMD_STOP;
}

/**
 * @brief  HSI2C主机写数据命令
 * @param  [in] u8Data 主机写数据
 * @retval None
 */
void HSI2C_MasterWriteData(uint8_t u8Data)
{
    M0P_HSI2C->MTDR = HSI2C_CMD_TX_DATA | (uint32_t)u8Data;
}

/**
 * @brief  HSI2C从机写数据命令
 * @param  [in] u8Data 从机写数据
 * @retval None
 */
void HSI2C_SlaveWriteData(uint8_t u8Data)
{
    M0P_HSI2C->STDR = (uint32_t)u8Data;
}

/**
 * @brief  HSI2C主机读数据命令
 * @param  [in] u8Len 读数据长度
 * @retval None
 */
void HSI2C_MasterReceiveCmd( uint8_t u8Len)
{
    M0P_HSI2C->MTDR = HSI2C_CMD_RX_DATA | (uint32_t)u8Len;
}

/**
 * @brief  HSI2C主机读数据(RXEMPTY & DATA)
 * @param  [in] pu8Data 数据存放地址指针
 * @retval en_result_t
 *           - Ok: 读数据成功
 *           - Error: 读数据失败
 */
en_result_t HSI2C_MasterReadData(uint8_t *pu8Data)
{
    uint32_t u32Temp = M0P_HSI2C->MRDR;
    if (0 == (u32Temp & 0x4000u))  //0x4000u: HSI2C_MRDR_RXEMPTY_Msk
    {
        *pu8Data = (uint8_t)(u32Temp & 0xFFu);  //0xFFu:HSI2C_MRDR_DATA_Msk
        return Ok;
    }
    else
    {
        return Error;
    }
}

/**
 * @brief  HSI2C从机读数据(SOF，REMP & DATA)
 * @param  [in] pu8Data 数据存放地址指针
 * @retval en_result_t
 *           - Ok: 读数据成功
 *           - Error: 读数据失败
 */
en_result_t HSI2C_SlaveReadData(uint8_t *pu8Data)
{
    uint32_t u32Temp = M0P_HSI2C->SRDR;
    if (0 == (u32Temp & 0x4000u))//0x4000u:HSI2C_SRDR_REMP_Msk
    {
        *pu8Data = (uint8_t)(u32Temp & 0xFFu); //0xFFu:HSI2C_SRDR_DATA_Msk
        return Ok;
    }
    else
    {
        return Error;
    }
}

/**
 * @brief  HSI2C从机写地址
 * @param  [in] u16Addr0 从机地址0. 数据范围：0 ~ 0x3FF
 * @param  [in] u16Addr1 从机地址1. 数据范围：0 ~ 0x3FF
 * @retval None
 */
void HSI2C_SlaveWriteAddr(uint16_t u16Addr0, uint16_t u16Addr1)
{
    M0P_HSI2C->SADDR_f.ADDR0 = u16Addr0;
    M0P_HSI2C->SADDR_f.ADDR1 = u16Addr1;
}

/**
 * @brief  HSI2C从机读接收的地址
 * @param  [in] pu16Data 数据存放地址指针
 * @retval en_result_t
 *           - Ok: 读数据成功
 *           - Error: 读数据失败
 */
en_result_t HSI2C_SlaveReadAddr(uint16_t *pu16Data)
{
    uint32_t u32Temp = M0P_HSI2C->SASR;
    if (0 == (u32Temp & 0x4000u))  //0x4000u:HSI2C_SASR_ANV_Msk
    {
        *pu16Data = (uint16_t)(u32Temp & 0x7FFu);  //0x7FFu:HSI2C_SASR_RADDR_Msk
        return Ok;
    }
    else
    {
        return Error;
    }
}

/**
 * @brief  HSI2C主机错误标志位读取
 * @param  [in] u32MasterFlag 主机MSR寄存器的值
 * @retval en_hsi2c_com_error_t 主机错误结果
 *           - Hsi2cComErrorPinLowTimeout: SCL or SDA were held low longer than the timeout
 *           - Hsi2cComErrorBufError: Buffer error
 *           - Hsi2cComErrorArbitrationLost: Arbitration lost error
 *           - Hsi2cComErrorNack: The slave device sent a NACK in response to a byte
 *           - Hsi2cComSuccess: The operation is successful
 */
en_hsi2c_com_error_t HSI2C_MasterErrorGet(uint32_t u32MasterFlag)
{
    en_hsi2c_com_error_t enComResult = Hsi2cComSuccess;
    if (0 != u32MasterFlag)
    {
        /* Get master error status */
        if (0 != (u32MasterFlag & (uint32_t)Hsi2cMskMasterStaItPlt))
        {
            enComResult = Hsi2cComErrorPinLowTimeout;
        }
        else if (0 != (u32MasterFlag & (uint32_t)Hsi2cMskMasterStaItFe))
        {
            enComResult = Hsi2cComErrorBufError;
        }
        else if (0 != (u32MasterFlag & (uint32_t)Hsi2cMskMasterStaItAl))
        {
            enComResult = Hsi2cComErrorArbitrationLost;
        }
        else if (0 != (u32MasterFlag & (uint32_t)Hsi2cMskMasterStaItNd))
        {
            enComResult = Hsi2cComErrorNack;
        }
        else
        {
            enComResult = Hsi2cComSuccess;
        }
    }
    return enComResult;
}

/**
 * @brief  HSI2C从机错误标志位读取
 * @param  [in] u32SlaveFlag 从机SSR寄存器的值
 * @retval en_hsi2c_com_error_t 从机错误结果
 *           - Hsi2cComErrorBitError: Transferred bit was not seen on the bus
 *           - Hsi2cComErrorBufError: Buffer error
 *           - Hsi2cComSuccess: The operation is successful
 */
en_hsi2c_com_error_t HSI2C_SlaveErrorGet(uint32_t u32SlaveFlag)
{
    en_hsi2c_com_error_t enComResult = Hsi2cComSuccess;
    if (0 != u32SlaveFlag)
    {
        /* Get slave error status */
        if (0 != (u32SlaveFlag & (uint32_t)Hsi2cMskSlaveStaItBe))
        {
            enComResult = Hsi2cComErrorBitError;
        }
        else if (0 != (u32SlaveFlag & (uint32_t)Hsi2cMskSlaveStaItFe))
        {
            enComResult = Hsi2cComErrorBufError;
        }
        else
        {
            enComResult = Hsi2cComSuccess;
        }
    }
    return enComResult;
}

/**
 * @brief  HSI2C主机传输终止
 * @param  [in] None
 * @retval None
 */
void HSI2C_MasterTransAbort(void)
{
    /* Disable all interrupts */
    HSI2C_MasterIntDisable(Hsi2cMskMasterItAll);

    /* Master busy? */
    if (HSI2C_MasterFlagGet(Hsi2cMskMasterStaMbf))
    {
        /* Send stop command */
        HSI2C_MasterStop();
    }
}

/**
 * @brief  HSI2C从机传输终止
 * @param  [in] None
 * @retval None
 */
void HSI2C_SlaveTransAbort(void)
{
    /* Disable all interrupts */
    HSI2C_SlaveIntDisable( Hsi2cMskSlaveItAll);

    /* Transmit NACK */
    M0P_HSI2C->STAR_f.TXNACK = Hsi2cSlaveTxNack;
}

/**
 * @brief  HSI2C从机ACK/NACK发送
 * @param  [in] enAckNack @ref en_hsi2c_slv_star_t
 * @retval None
 */
void HSI2C_SlaveTransNack(en_hsi2c_slv_star_t enAckNack)
{
    M0P_HSI2C->STAR_f.TXNACK = enAckNack;
}

/**
 * @brief  HSI2C 10位地址模式获取高字节
 * @param  [in] u16AddrData 从机设备地址
 * @retval uint8_t 10位从机设备地址的高字节
 */
uint8_t HSI2C_10BitAddrMdHighBitsGet(uint16_t u16AddrData)
{
    return ((uint8_t)((u16AddrData >> 8) & 0x03u) | 0x78u);
}

/**
 * @brief  HSI2C 10位地址模式获取低字节
 * @param  [in] u16AddrData 从机设备地址
 * @retval uint8_t 10位从机设备地址的低字节
 */
uint8_t HSI2C_10BitAddrMdLowBitsGet(uint16_t u16AddrData)
{
    return (uint8_t)((u16AddrData & 0xFFu));
}

/**
 * @brief  主机结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_hsi2c_master_init_t
 * @retval None
 */
void HSI2C_MasterStcInit(stc_hsi2c_master_init_t *pstcInit)
{
    /* 初始值清零 */
    DDL_ZERO_STRUCT(*pstcInit);

    pstcInit->bResetBeforeInit                   = FALSE;
    pstcInit->enEnableDebug                      = Hsi2cMasterDebugDisable;
    pstcInit->u32BaudRateHz                      = 0;
    pstcInit->u8SlaveAddr                        = 0;
    pstcInit->enDir                              = Hsi2cMasterWriteSlaveRead;
    pstcInit->enDma                              = Hsi2cDmaDisable;
    pstcInit->stcMasterConfig2.enSdaFilterEnable = Hsi2cMasterSdaFiltDisable;
    pstcInit->stcMasterConfig2.enSclFilterEnable = Hsi2cMasterSclFiltDisable;
    pstcInit->u32SubAddr                         = 0;
    pstcInit->u8SubAddrSize                      = 0;
}
/**
 * @}
 */

/**
 * @brief  从机结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_hsi2c_slave_init_t
 * @retval None
 */
void HSI2C_SlaveStcInit(stc_hsi2c_slave_init_t *pstcInit)
{
    /* 初始值清零 */
    DDL_ZERO_STRUCT(*pstcInit);

    pstcInit->bResetBeforeInit = FALSE;
    pstcInit->u32SlaveAddr0    = 0;
    pstcInit->u32SlaveAddr1    = 0;
    pstcInit->enDir            = Hsi2cMasterWriteSlaveRead;
    pstcInit->enDma            = Hsi2cDmaDisable;
    pstcInit->u8SubAddrSize    = 0;
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
