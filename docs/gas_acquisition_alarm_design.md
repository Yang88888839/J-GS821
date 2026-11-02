# 气体采集与报警设计简要说明

本文基于 [source/bsp_gas.c](source/bsp_gas.c) 与 [source/bsp_sound_led.c](source/bsp_sound_led.c) 的实现，概述气体浓度采集、报警判定和报警输出的核心流程。

## 1. 数据采集方式

气体浓度采集主要在 [source/bsp_gas.c](source/bsp_gas.c) 中完成。系统通过串口接收传感器数据，并读取以下字段：

- LEL（燃气浓度值）
- 温度值
- 故障码
- 校验和

关键函数包括：

- calculate_checksum()
- gas_sensor_convert()
- gas_sensor_analysis()

采集时，程序首先对串口原始数据执行校验和计算，确认数据有效后解析字符帧。实际数据格式类似：

- A + 000.00 + 32.7 0669.80 + 22.1 B + 003.0 00 18

解析后，代码会将原始传感器值写入中间变量：

- gas.result_value_lel
- gas.result_fault
- gas.result_temperature
- gas.result_check

若校验通过，则进一步把这些结果写回设备状态变量：

- gas.value_lel = gas.result_value_lel * 20
- gas.value_fault = gas.result_fault
- gas.value_temperature = gas.result_temperature

这说明传感器原始值会被换算成设备内部可用的 LEL/百分比值，供后续报警判断和上报使用。

## 2. 报警判定逻辑

报警判定入口为 gas_sensor_alarm()，逻辑顺序如下：

1. 先判断传感器是否故障；
2. 若存在故障，则直接禁止泄漏报警；
3. 若无故障，再判断 gas.value_lel 是否达到报警阈值；
4. 达到阈值后进入报警状态。

相关阈值定义：

- GAS_alarm_level_9lel
- GAS_alarm_level_10lel
- GAS_alarm_level_25lel

判定规则为：

- gas.value_lel < 9：报警退出或保持静默；
- gas.value_lel >= 10：进入报警状态；
- gas.value_lel > 25：认为达到严重报警条件。

## 3. 报警进入与退出

对应函数如下：

- gas_alarm_input()
- gas_alarm_exit()

当报警进入时，系统会执行：

- f_alarm_gas = 1
- gas.alarm_exit = 0
- gas.alarm_enter = 0
- log_write(FlashAlarm_enter)
- device.alarm_mute_disable = 60

当报警退出时，系统会执行：

- f_alarm_gas = 0
- gas.alarm_exit = 0
- log_write(FlashAlarm_exit)

也就是说，报警进入时触发告警状态和记录日志；报警解除后清除标志并记录退出事件。

## 4. 报警输出

报警输出由 [source/bsp_sound_led.c](source/bsp_sound_led.c) 中的 alarm_control() 负责，表现为：

- 红灯持续亮起；
- 蜂鸣器发出周期性报警声；
- 声音频率随时间变化；
- 报警持续到浓度恢复正常或手动消音。

该逻辑结合显示和声音总控，实现明显的报警提示，方便现场人员及时处理异常状态。

## 5. 流程图

```mermaid
flowchart TD
    A[开始] --> B[串口接收传感器数据]
    B --> C[calculate_checksum() 计算校验和]
    C --> D{校验和正确?}
    D -- 否 --> E[丢弃数据并结束]
    D -- 是 --> F[gas_sensor_convert() 解析 LEL/温度/故障码/校验和]
    F --> G[写入 result_value_lel / result_fault / result_temperature / result_check]
    G --> H{是否存在故障?}
    H -- 是 --> I[禁止泄漏报警]
    H -- 否 --> J[gas.value_lel = result_value_lel * 20]
    J --> K[gas_sensor_alarm() 判定报警]
    K --> L{gas.value_lel < 9?}
    L -- 是 --> M{当前已报警?}
    M -- 是 --> N[gas_alarm_exit() 退出报警]
    M -- 否 --> O[保持静默]
    L -- 否 --> P{gas.value_lel >= 10?}
    P -- 是 --> Q{当前未报警?}
    Q -- 是 --> R[gas_alarm_input() 进入报警]
    Q -- 否 --> S[保持报警]
    P -- 否 --> T[继续监测]
    R --> U[设置 f_alarm_gas = 1]
    U --> V[记录日志并开启消音倒计时]
    N --> W[设置 f_alarm_gas = 0]
    W --> X[记录退出日志]
    V --> Y[alarm_control() 执行报警输出]
    X --> Z[结束]
    S --> Y
    T --> Z
    I --> Z
    O --> Z
    Y --> AA[红灯持续亮 + 蜂鸣器周期报警]
    AA --> AB{浓度恢复正常或手动消音?}
    AB -- 否 --> Y
    AB -- 是 --> Z
```

## 6. 报警消音说明

报警消音功能由按键触发和定时退出共同控制，核心逻辑分为两部分：

1. 手动消音触发
   - 入口函数是 key_alarm_mute()。
   - 当报警状态存在且未处于禁止消音条件下时，若当前未处于静音状态，则设置 f_alarm_mute = 1，并记录 FlashMute 日志。
   - 其中，若 status_alarm.byte == 0 或 device.alarm_mute_disable > 0，则直接返回，不允许立即消音。

2. 自动消音退出
   - 进入报警时，gas_alarm_input() 会设置 device.alarm_mute_disable = 60，表示新报警进入后有一段时间内禁止重复手动消音。
   - alarm_control() 在输出蜂鸣器时会判断 f_alarm_mute 是否为 0；若为 1，则跳过蜂鸣器输出，从而实现静音。
   - alarm_mute_exit() 会在报警仍然存在时，通过计时器判断是否达到 C_time_mute_alarm，达到后自动清除 f_alarm_mute。
   - 若报警状态已消失，则直接清除静音标志，并结束静音状态。

也就是说，报警消音不是永久关闭，而是“临时抑制声响”，并会在条件允许时自动恢复/退出；同时，系统会避免用户在报警刚进入时立即误消音，以防止报警被短暂关闭而忽略真实危险。

## 7. 报警消音流程图

```mermaid
flowchart TD
    A[报警已触发] --> B[gas_alarm_input() 进入报警]
    B --> C[设置 f_alarm_gas = 1]
    C --> D[device.alarm_mute_disable = 60]
    D --> E[alarm_control() 执行红灯+蜂鸣器输出]
    E --> F{是否按下消音键?}
    F -- 否 --> G{报警是否持续?}
    G -- 是 --> E
    G -- 否 --> H[报警恢复正常]
    H --> I[gas_alarm_exit() 清除报警]
    I --> J[结束]
    F -- 是 --> K{status_alarm.byte == 0 或 alarm_mute_disable > 0?}
    K -- 是 --> L[禁止消音]
    L --> E
    K -- 否 --> M{f_alarm_mute == 0 且 device.alarm_mute_timer == 0?}
    M -- 是 --> N[key_alarm_mute() 设置 f_alarm_mute = 1]
    N --> O[记录 FlashMute 日志]
    O --> P[alarm_control() 检测到 f_alarm_mute == 1]
    P --> Q[蜂鸣器静音，红灯仍可提示]
    Q --> R{报警是否解除?}
    R -- 否 --> S{是否达到静音超时?}
    S -- 是 --> T[alarm_mute_exit() 清除 f_alarm_mute]
    S -- 否 --> Q
    R -- 是 --> U[gas_alarm_exit() 退出报警]
    T --> V[恢复正常警报输出状态]
    U --> J
```

## 8. 电磁阀控制说明

电磁阀控制逻辑主要在 [source/bsp_valve.c](source/bsp_valve.c) 中实现，核心目的为：在泄漏报警触发后执行自动关阀，并持续检测阀门状态、学习阀门脉冲宽度和判断故障。

### 8.1 阀门输出控制

电磁阀输出控制通过以下函数实现：

- valve_output()
- valve_open_set()
- valve_check_handler()
- valve_check_task()

其行为包括：

- 根据阀门类型选择不同输出通道：
  - va_action：执行阀门动作控制
  - va_check：执行阀门检测控制
- 通过 PW_valve_control_open()/close() 和 PW_valve_check_open()/close() 驱动外部硬件。
- 在切换控制对象时，调用 valve_interrupt_set(name) 关闭不相关中断，以过滤无效脉冲。

### 8.2 阀门动作流程

在 valve_working() 中，程序按以下顺序处理：

1. 若有任务等待执行，则按 delay 进行延时；
2. 若存在需要检测的阀门，则在指定时间后执行输出开/关动作；
3. 当动作阀门关闭后，启动 2000 ms 的后续检测窗口；
4. 若是检查阀门任务，则进入 check_timer 计时，随后调用 valve_check_handler() 判断状态。

也就是说，阀门动作并不是瞬时完成，而是一个带延时、带检测、带反馈的闭环控制流程。

### 8.3 学习与校准

为保证阀门动作准确，系统在 valve_study_handler() 中增加了学习功能：

- 采集阀门脉冲宽度
- 过滤无效脉冲
- 若脉冲宽度在学习范围内，则保存到 eep.sys.byte.valve_width
- 并调用 Flash_write_smart() 持久化保存

在 valve_judge() 中，程序根据学习到的阀门宽度计算两个判定门限：

- pulse_close_value = valve_width * 1.5
- pulse_open_value = valve_width * 4

随后根据当前脉冲宽度判断阀门处于：

- em_valve_close
- em_valve_open
- em_valve_open_fault
- em_valve_short_fault
- em_valve_other_fault
- em_valve_uncalibrated

### 8.4 报警时自动关阀

在 valve_check_task() 中，若检测到 f_alarm_gas == 1，则执行：

- valve_open_set(va_action, 0, 100)
- 使动作阀门按固定时间关闭
- 同时完成阀门状态检测和指示灯更新

如果阀门状态小于 3，则认为无故障；否则设置 f_fault_valve = 1，以便上层进行故障上报和显示提示。

### 8.5 电磁阀控制框图

```mermaid
flowchart TD
    A[系统周期任务] --> B[valve_working()]
    B --> C{是否有待执行阀门动作?}
    C -- 否 --> D[继续等待下一轮]
    C -- 是 --> E[读取 valve.control[i].start]
    E --> F{delay 是否结束?}
    F -- 否 --> G[继续延时]
    F -- 是 --> H{close 是否大于0?}
    H -- 是 --> I[valve_output(i,1) 打开阀门]
    I --> J[close--]
    J --> K{是否达到关闭时长?}
    K -- 否 --> I
    K -- 是 --> L{是否为动作阀门?}
    L -- 是 --> M[记录 FlashValve_on\n设置 valve_close_start = 1\n延时 2000 ms]
    L -- 否 --> N{是否为检查阀门?}
    N -- 是 --> O[check_timer = 2]
    N -- 否 --> P[结束本次动作]
    M --> P
    O --> P
    P --> Q[valve_output(i,0) 关闭阀门]
    Q --> R[valve_check_handler() 检测状态]
    R --> S[读取 pulse 宽度]
    S --> T[valve_judge() 判断阀门状态]
    T --> U{状态是否变化或关闭故障?}
    U -- 是 --> V[更新 valve.status\n记录反馈/故障日志]
    U -- 否 --> W[保持当前状态]
    V --> X[结束]
    W --> X

    D --> Y{是否发生泄漏报警?}
    Y -- 是 --> Z[valve_check_task()]
    Z --> AA[valve_open_set(va_action,0,100)]
    AA --> AB[自动关闭动作阀门]
    AB --> AC[持续检测阀门状态]
    AC --> AD{阀门状态正常?}
    AD -- 否 --> AE[f_fault_valve = 1]
    AD -- 是 --> AF[f_fault_valve = 0]
    AE --> X
    AF --> X

    B --> AG[valve_study_handler()] 
    AG --> AH{检测到脉冲且在学习范围内?}
    AH -- 是 --> AI[保存 valve_width 到 EEPROM]
    AH -- 否 --> X
```

## 9. 自检测试功能说明

自检测试功能由按键事件和指示灯/蜂鸣器联动实现，入口函数为 key_alarm_start()，实际触发方式是“双击按键”或等效的自检命令。

### 9.1 触发方式

在 [source/bsp_key.c](source/bsp_key.c) 中，按键分发逻辑为：

- `KEY_PRESS_TWO`：双击按键
- 触发 `key_alarm_start()`

该函数中逻辑如下：

1. 若当前已处于泄漏报警状态 `f_alarm_gas`，则直接退出自检流程；
2. 若当前未在自检中，则执行：
   - `alarm_test_init()`：初始化自检音量和计数器
   - `log_write(FlashCheck)`：记录自检日志
   - `f_alarm_test = 1`：开启自检标志
3. 若再次触发且 `f_alarm_test == 1`，则退出自检：
   - `f_alarm_test = 0`
   - 延时 500 ms
   - `buzzer_short(100)` 发出短鸣，表示自检结束

### 9.2 自检输出方式

在 [source/bsp_sound_led.c](source/bsp_sound_led.c) 中，自检输出由 `voice_DBlow_control()` 负责，内容包括：

- LED 颜色按周期切换：红、黄、绿
- 蜂鸣器按频率渐增输出测试音
- 通过 `voice.DBlow` 控制鸣叫强度和节拍
- 当 `voice.DBlow > 7` 时，认为自检完成

自检结束时，系统会执行：

- `f_alarm_test = 0`
- `led_open_set(colour_valve, 10, 10, 15)`
- `valve_open_set(va_action, 0, 100)`：关闭动作阀门
- `valve.study_timer = 500`：进入阀门学习窗口

该逻辑说明，自检测试既是功能检测，也是一个“模拟报警音 + 视觉提示 + 阀门复位”的综合调试动作。

### 9.3 自检与常态显示的关系

在 `display_handler()` 中，如果当前处于 `f_alarm_test` 状态，则程序直接进入自检提示状态：

- `display_timer = 0`
- 调用 `voice_DBlow_control()`
- 退出正常故障/报警显示分支

这说明自检是一个高优先级的测试模式，会覆盖常规报警和待机显示。

## 10. 自检测试流程图

```mermaid
flowchart TD
    A[用户操作] --> B{是否双击按键?}
    B -- 否 --> C[继续正常运行]
    B -- 是 --> D[key_alarm_start()]
    D --> E{当前是否存在泄漏报警 f_alarm_gas?}
    E -- 是 --> F[直接退出自检]
    E -- 否 --> G{当前是否已处于自检状态 f_alarm_test?}
    G -- 是 --> H[f_alarm_test = 0\n延时500ms\n短鸣提示]
    H --> I[结束自检]
    G -- 否 --> J[alarm_test_init() 初始化测试参数]
    J --> K[log_write(FlashCheck) 记录自检日志]
    K --> L[f_alarm_test = 1]
    L --> M[display_handler() 检测到测试状态]
    M --> N[voice_DBlow_control() 执行自检输出]
    N --> O[红/黄/绿 LED 周期切换]
    O --> P[蜂鸣器频率递增]
    P --> Q{voice.DBlow > 7?}
    Q -- 否 --> N
    Q -- 是 --> R[f_alarm_test = 0]
    R --> S[阀门指示灯复位]
    S --> T[valve_open_set(va_action, 0, 100)]
    T --> U[valve.study_timer = 500]
    U --> V[自检结束]
    F --> I
    C --> I
```

## 11. 总结

该方案的核心思想是：先通过串口获取传感器数据，再进行校验、转换和阈值判断，最终将报警状态通过声音和指示灯输出给用户。逻辑上遵循“先故障判定，再浓度判定，再输出报警”的顺序，能够有效避免传感器异常导致的误报警，同时保证现场报警信息明确、持续和可识别。对于消音控制，系统采用“按键静音 + 定时自动退出”的机制，兼顾报警有效性和现场操作便捷性。电磁阀控制则采用“动作 + 延时 + 反馈检测 + 故障判断”的闭环方式，保证在泄漏报警后能够可靠关闭阀门并进行状态监测。自检测试则以双击按键为入口，利用声音和 LED 进行系统功能验证，并在测试结束后自动恢复到常规工作状态。


flowchart TD
    A[开始] --> B[串口接收传感器数据]
    B --> C[计算校验和]
    C --> D{校验和正确?}
    D -- 否 --> E[丢弃数据并结束]
    D -- 是 --> F[解析 LEL/温度/故障码/校验和]
    F --> G[写入 result_value_lel / result_fault  / result_check]
    G --> H{是否存在故障?}
    H -- 是 --> I[禁止泄漏报警]
    H -- 否 --> J[gas.value_lel]
    J --> K[判定报警]
    K --> L{gas.value_lel < 9?}
    L -- 是 --> M{当前已报警?}
    M -- 是 --> N[退出报警]
    M -- 否 --> O[保持静默]
    L -- 否 --> Q{当前未报警?}
    P -- 是 --> Q{当前未报警?}
    Q -- 是 --> R[进入报警]
    Q -- 否 --> S[保持报警]
    P -- 否 --> T[继续监测]
    R --> U[设置 f_alarm_gas = 1]
    U --> V[记录日志并开启消音倒计时]
    N --> W[设置 f_alarm_gas = 0]
    W --> X[记录退出日志]
    V --> Y[执行报警输出]
    X --> Z[结束]
    S --> Y
    T --> Z
    I --> Z
    O --> Z
    Y --> AA[红灯持续亮 + 蜂鸣器周期报警]
    AA --> AB{浓度恢复正常或手动消音?}
    AB -- 否 --> Y
    AB -- 是 --> Z











flowchart TD
    A[报警已触发] --> B[进入报警]
    B --> C[设置 f_alarm_gas = 1]
    C --> D[device.alarm_mute_disable = 60]
    D --> E[执行红灯+蜂鸣器输出]
    E --> F{是否按下消音键?}
    F -- 否 --> G{报警是否持续?}
    G -- 是 --> E
    G -- 否 --> H[报警恢复正常]
    H --> I[清除报警]
    I --> J[结束]

    
    F -- 是 --> K{status_alarm.byte == 0 或 alarm_mute_disable > 0?}
    K -- 是 --> L[禁止消音]
    L --> E
    K -- 否 --> M{f_alarm_mute == 0 且 device.alarm_mute_timer == 0?}
    M -- 是 --> N[设置 f_alarm_mute = 1]
    N --> O[记录 FlashMute 日志]
    O --> P[检测到 f_alarm_mute == 1]
    P --> Q[蜂鸣器静音，红灯仍可提示]
    Q --> R{报警是否解除?}
    R -- 否 --> S{是否达到静音超时?}
    S -- 是 --> T[清除 f_alarm_mute]
    S -- 否 --> Q
    R -- 是 --> U[退出报警]
    T --> V[恢复正常警报输出状态]
    U --> J


