# 看门狗复位流程

```mermaid
flowchart TD
    A[上电或复位] --> B[main 初始化并调用 Init_iwdt]
    B --> C[创建 Task1~Task4]
    C --> D[启动 FreeRTOS]
    D --> E[Task1~Task4 周期运行]
    E --> F[各任务更新 task_run.bit0~bit3]
    F --> G{task_run & 0x0F == 0x0F?}
    G -- 是 --> H[清零 task_run]
    H --> I[Task2 调用 IWDT_Feed]
    I --> E
    G -- 否 --> J[停止喂狗]
    J --> K{IWDT 是否超时?}
    K -- 否 --> J
    K -- 是 --> L[IwdtResetEn 触发 MCU 复位]
    L --> A

    classDef normal fill:#e8f5e9,stroke:#388e3c,color:#1b5e20;
    classDef check fill:#fff8e1,stroke:#f9a825,color:#5d4037;
    classDef reset fill:#ffebee,stroke:#d32f2f,color:#b71c1c;
    class A,B,C,D,E,F,H,I normal;
    class G,K check;
    class J,L reset;
