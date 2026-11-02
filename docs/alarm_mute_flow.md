# 报警消音简化流程图

根据项目中的报警逻辑，报警消音流程可以简化为下面这张 Mermaid 图：

```mermaid
flowchart TD
    A[进入报警状态] --> B{status_alarm.byte == 0 ?}
    B -- 是 --> C[退出流程]
    B -- 否 --> D{alarm_mute_disable > 0 ?}
    D -- 是 --> C
    D -- 否 --> E{f_alarm_mute == 0 且 alarm_mute_timer == 0 ?}
    E -- 否 --> F[已处于消音状态]
    E -- 是 --> G[f_alarm_mute = 1]
    G --> H[记录 log_write(FlashMute)]
    H --> I[报警消音开启]
    I --> J[继续监测报警]

    J --> K{报警是否结束？}
    K -- 是 --> L[device.alarm_mute_timer = 0]
    L --> M[f_alarm_mute = 0]
    M --> N[退出报警消音]
    K -- 否 --> O{f_alarm_mute == 1 ?}
    O -- 是 --> P[device.alarm_mute_timer++]
    P --> Q{timer > C_time_mute_alarm ?}
    Q -- 是 --> R[f_alarm_mute = 0]
    R --> N
    Q -- 否 --> J
    O -- 否 --> J
```

## 说明

- 当有报警且未被禁止时，进入消音状态。
- 消音状态由 `f_alarm_mute` 控制。
- 报警消失时，直接清除消音标志。
- 若报警持续存在，则按 `device.alarm_mute_timer` 累计时间，超过 `C_time_mute_alarm` 后自动退出消音。
