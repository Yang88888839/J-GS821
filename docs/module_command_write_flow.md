# `module_command_write` 流程图

函数位置：[source/bsp_module.c](../source/bsp_module.c)

```c
unsigned char module_command_write(char *command, char *ack)
```

```mermaid
flowchart TD
    A([开始]) --> B[最多尝试 3 次]
    B --> C[延时 20 tick，清零接收状态]
    C --> D[发送 command]
    D --> E{等待接收完成}
    E -- 未完成 --> F[延时 10 tick]
    F --> G{本次等待达到 20 轮?}
    G -- 否 --> E
    G -- 是 --> H[本次尝试失败]
    H --> I{还有重试次数?}
    I -- 是 --> C
    I -- 否 --> Z([返回 0：失败])

    E -- 已完成 --> J[打印接收数据]
    J --> K{接收数据匹配 ack?}
    K -- 是 --> L[清零接收状态]
    L --> S([返回 1：成功])
    K -- 否 --> M[清零接收状态]
    M --> F
```

- 最多发送 3 次。
- 每次发送后最多等待 20 轮，每轮延时 10 tick。
- 收到匹配的 `ack` 立即返回 `1`。
- 未匹配或超时则继续重试，全部失败后返回 `0`。
