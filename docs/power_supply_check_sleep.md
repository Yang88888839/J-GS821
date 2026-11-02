# power_supply_check 休眠/掉电检测功能说明

## 1. 函数定位

函数 `power_supply_check(void)` 位于 [source/bsp_key.c](../source/bsp_key.c) 中，主要用于检测电源状态变化，并在系统确认进入或恢复供电状态时执行相应的休眠/唤醒处理。

## 2. 功能概述

这个函数本质上是一个“电源状态去抖 + 事件判断”逻辑：

- 读取 `PR_sleep()` 的状态，判断当前是否处于“掉电/休眠”状态；
- 使用 `f_ac_read` 记录上一次状态，避免因为瞬时抖动误触发；
- 通过 `level_low` 和 `level_high` 连续计数器，确保只有稳定持续的低电平/高电平状态才认为是真实事件；
- 一旦确认进入掉电或恢复供电，就执行日志记录和系统休眠/唤醒动作。

其中：

- `PR_sleep() == 1` 被视为“掉电/休眠”状态；
- `PR_sleep() == 0` 被视为“上电/正常供电”状态；
- 连续 10 次稳定采样后才处理状态变化，能明显抑制毛刺。

## 3. 详细处理流程

### 3.1 状态去抖

```c
if(f_ac_read!=PR_sleep())
{
    delay_ms(10);
    if(f_ac_read!=PR_sleep())
    {
        f_ac_read = PR_sleep() ;
        return ;
    }
}
```

这段逻辑的目标是过滤瞬间抖动：

- 若当前状态与上一次记录不同，先等待 10ms；
- 再次读取，如果状态仍然不同，则更新 `f_ac_read`，并直接返回；
- 也就是说，只有状态稳定后才继续进入下一阶段处理。

这样可以避免在电源线上出现短暂波动时，误认为设备进入了休眠或恢复供电。

### 3.2 掉电/休眠判断

```c
if(1==PR_sleep()) //掉电
{
    level_high=0;
    if((++level_low)<10)
    {
        return ;
    }
    level_low=0;
    if(f_status_ac==1)
    { 
        if(f_fault_gas)
        {
            log_write(FlashFault_clear); 
        }
        if(f_alarm_gas)
        {
            log_write(FlashAlarm_exit);
        }
        f_status_ac=0;
    }
    else
    {
        log_write(FlashPower_on); 
    }
    myprintf("AC_Off...\r\n");
    log_write(FlashPower_down);
    Init_sleep();
}
```

当 `PR_sleep()` 连续稳定为 1 达到 10 次时，判定设备已进入掉电状态：

1. 清空 `level_high`，用于上电计数复位；
2. 累加 `level_low`；
3. 计数未达到 10 时直接返回，继续等待稳定确认；
4. 确认掉电后：
   - 若此前 `f_status_ac == 1`，说明之前处于上电状态，此时要清理故障/报警状态；
   - 关闭或退出相关告警逻辑；
   - 设置 `f_status_ac = 0`，表示当前已失电；
   - 记录 `FlashPower_down`，并调用 `Init_sleep()`，进入休眠/低功耗模式。

### 3.3 上电/恢复供电判断

```c
else//上电
{
    level_low=0;
    if((++level_high)<10)
    {
        return ;
    }
    level_high=0;
    if(0==f_status_ac)
    { 
        f_status_ac=1 ;
        myprintf("AC_ON...\r\n");
        log_write(FlashPower_on); 
    }
}
```

当 `PR_sleep()` 连续稳定为 0 达到 10 次时，判定设备已恢复供电：

1. 清空 `level_low`，用于掉电计数复位；
2. 累加 `level_high`；
3. 计数未达到 10 时直接返回；
4. 一旦确认上电并且此前状态为失电：
   - `f_status_ac = 1`，说明设备已恢复供电；
   - 打印 `AC_ON...`；
   - 记录 `FlashPower_on`。

## 4. 休眠功能的整体含义

从这个函数看，休眠功能不是简单地“睡眠一段时间”，而是围绕“AC/电源状态有效性”做的安全管理：

- 对电源瞬态波动做抗抖处理；
- 把真正的电源掉电事件判定为“稳定持续 10 次采样”；
- 在掉电时执行清障、退出报警、进入休眠；
- 在上电时恢复供电状态并记录上电日志；
- 把休眠和唤醒动作与设备状态变量 `f_status_ac` 绑定，确保系统状态准确同步。

这使得设备在电源异常或长时间断电时进入低功耗状态，并在恢复供电后重新进入正常工作模式。

## 5. Mermaid 流程图

```mermaid
flowchart TD
    A[开始 power_supply_check] --> B[读取 PR_sleep() 当前状态]
    B --> C{是否出现状态变化?}
    C -- 是 --> D[延时 10ms 再次读取]
    D --> E{状态是否仍变化?}
    E -- 是 --> F[更新 f_ac_read 并返回]
    E -- 否 --> G[继续正常判定]
    C -- 否 --> G

    G --> H{PR_sleep() == 1 ?}
    H -- 是 --> I[level_high = 0]
    I --> J[level_low++]
    J --> K{level_low >= 10?}
    K -- 否 --> Z[结束]
    K -- 是 --> L[清零 level_low]
    L --> M{f_status_ac == 1?}
    M -- 是 --> N[若存在故障/报警，写清除日志]
    N --> O[f_status_ac = 0]
    M -- 否 --> P[记录上电状态或忽略]
    O --> Q[打印 AC_Off...]
    P --> Q
    Q --> R[log_write(FlashPower_down)]
    R --> S[Init_sleep() 进入休眠]
    S --> Z

    H -- 否 --> T[level_low = 0]
    T --> U[level_high++]
    U --> V{level_high >= 10?}
    V -- 否 --> Z
    V -- 是 --> W[level_high = 0]
    W --> X{f_status_ac == 0?}
    X -- 是 --> Y[f_status_ac = 1; 打印 AC_ON...; log_write(FlashPower_on)]
    X -- 否 --> Z
    Y --> Z

    Z[结束]
```

## 6. 一句话总结

`power_supply_check` 是一个基于电源状态的休眠控制判断函数：它通过去抖和稳定计数确认“掉电”或“上电”事件，然后在确认后执行故障清理、状态切换、日志记录及 `Init_sleep()` 进入休眠，保证系统在异常断电时低功耗运行，并在供电恢复后正常唤醒。
