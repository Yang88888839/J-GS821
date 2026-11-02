# Flash_write_smart 时间线图

```mermaid
timeline
    title Flash_write_smart 执行时间线

    section 第 1 轮写入
        0 ms : 调用 Flash_write_smart()
        1 ms : 调用 Flash_read_find()，定位有效页和读取地址
        2 ms : 调用 Flash_blank_find()，定位可写空白区
        3 ms : 设置 eep.sys.byte.heard = 0x55555555
        4 ms : 设置 eep.sys.byte.erase = 0xffffffff
        5 ms : 计算校验和，写入 eep.sys.buffer[15]
        6 ms : 执行 eep_write(eep.addr_write, &eep.sys.buffer[0], 16)
        7 ms : 执行 eep_write(eep.addr_read + 4, &datum_zero, 1)
        8 ms : 调用 Flash_erase_judge()
        9 ms : 记录 r_add / w_add（若开启 FLASH_PRINT）
        10 ms : 若 result == flash_normal，则成功退出循环
        11 ms : 若 result != flash_normal，则继续第 2 轮重试

    section 第 2~8 轮重试
        12 ms : 重新执行 Flash_read_find() 与 Flash_blank_find()
        13 ms : 重新组包并设置头标志与校验和
        14 ms : 再次写入有效数据块到新地址
        15 ms : 再次清理旧页标记并判断是否擦除旧页
        16 ms : 继续判断 result，直到成功或重试次数耗尽

    section 结束
        17 ms : 函数返回，写入过程结束
        18 ms : 若最终失败，仍在循环上限内停止重试
```

## 关键说明

- `Flash_write_smart` 采用“最多重试 8 次”的方式写入 EEPROM/Flash 参数。
- 每次写入前都会先调用 `Flash_read_find` 和 `Flash_blank_find`，以定位有效页和空白页。
- 写入前会更新头标志位和校验和，然后执行一次实际写入。
- 若 `Flash_Write` 返回正常值 `flash_normal`，则结束循环；否则继续尝试直到上限。
- 逻辑中还会在写入后调用 `Flash_erase_judge`，用于根据地址判断是否需要擦除旧页。



