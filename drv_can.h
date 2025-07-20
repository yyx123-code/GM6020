#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#include <stdint.h>
#include "stm32f4xx.h"                  // Device header

void CAN_Init(void);//can初始化
void CAN_Send(uint8_t *message);//can发送函数
void CAN_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data);

#endif
