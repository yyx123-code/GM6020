#include <stdint.h>
#include <stdio.h>

/**
 * @brief 将一个16位的十进制数拆分为高八位和低八位
 * @param value 十进制输入值
 * @param high_byte 输出高八位
 * @param low_byte 输出低八位
 */
void split_into_high_low(int16_t value, uint8_t *high_byte, uint8_t *low_byte)
{
    // 将输入值转换为无符号类型，避免符号扩展问题
    uint16_t unsigned_value = (uint16_t)value;

    // 提取高八位
    *high_byte = (unsigned_value >> 8) & 0xFF;

    // 提取低八位
    *low_byte = unsigned_value & 0xFF;
}
