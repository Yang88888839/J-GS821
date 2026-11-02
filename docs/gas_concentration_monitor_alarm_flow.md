# 气体浓度监测及泄漏告警流程

## 流程图

```mermaid
flowchart TD
    A[系统启动] --> B[等待传感器串口数据]
    B --> C{是否收到新数据?}
    C -- 否 --> B
    C -- 是 --> D[calculate_checksum() 计算校验和]
    D --> E{校验和是否正确?}
    E -- 否 --> F[丢弃当前帧，清空接收状态]
    F --> B
    E -- 是 --> G[判断数据是否含 A 开头]
    G -- 否 --> F
    G -- 是 --> H[gas_sensor_convert() 解析数据]
    H --> I[提取 LEL / 温度 / 故障码 / 校验和]
    I --> J{是否存在寿命终止故障?}
    J -- 是 --> K[gas.value_lel = 0\ngas.value_fault = 0]
    J -- 否 --> L[gas.value_lel = gas.result_value_lel * 20\ngas.value_fault = gas.result_fault\ngas.value_temperature = gas.result_temperature]
    K --> M[gas.sensor_online = 3]
    L --> M
    M --> N[gas_judge_fault() 检查传感器在线/故障状态]
    N --> O{是否发生传感器故障?}
    O -- 是 --> P[f_fault_gas = 1\n禁止泄漏报警]
    P --> Q[结束本轮判断]
    O -- 否 --> R{gas.value_lel < 9?}
    R -- 是 --> S{当前已处于报警状态?}
    S -- 是 --> T[gas_alarm_exit() 退出报警]
    S -- 否 --> Q
    R -- 否 --> U{gas.value_lel >= 10?}
    U -- 是 --> V{当前未处于报警状态?}
    V -- 是 --> W[gas_alarm_input() 进入报警]
    V -- 否 --> X[保持报警状态]
    U -- 否 --> Q
    W --> Y[f_alarm_gas = 1\n记录 FlashAlarm_enter\ndevice.alarm_mute_disable = 60]
    T --> Z[f_alarm_gas = 0\n记录 FlashAlarm_exit]
    Y --> AA[报警输出]
    Z --> AA
    X --> AA
    Q --> B

    AA --> AB[alarm_control() 处理报警输出]
    AB --> AC[红灯持续亮起]
    AC --> AD[蜂鸣器发出周期性报警声]
    AD --> AE{浓度恢复正常 or 手动消音?}
    AE -- 否 --> AB
    AE -- 是 --> AF[停止报警输出]
    AF --> B
```

## 说明

1. 传感器数据通过串口接收，先执行校验和校验，确保帧有效。
2. 数据解析后，提取 LEL、温度、故障码和校验值。
3. 若校验通过，则将结果写入设备内部状态变量，主要包括：
   - gas.value_lel
   - gas.value_fault
   - gas.value_temperature
4. 设备会先判断传感器是否故障，若存在故障则直接屏蔽泄漏报警。
5. 若无故障，再判断 gas.value_lel 是否达到泄漏报警阈值：
   - < 9：报警退出或静默
   - >= 10：报警进入
   - > 25：严重报警处理
6. 报警输出由 alarm_control() 负责，表现为红灯亮起和蜂鸣器周期报警，直到浓度恢复正常或手动消音后结束。
