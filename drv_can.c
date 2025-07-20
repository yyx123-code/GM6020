#include "stm32f4xx.h"                  // Device header
#include "can.h"
#include "drv_can.h"
#include <stdint.h>

typedef struct
{
		uint16_t can_id;//电机ID
    int16_t  set_voltage;//电压
    uint16_t rotor_angle;//角度
    int16_t  rotor_speed;//速度
    int16_t  torque_current;//扭矩电流
    uint8_t  temp;//温度
}motor_measure_t;
motor_measure_t motor_yaw_measure;

/*can初始化*/
void CAN_Init()
{
	CAN_FilterTypeDef CAN1_Filter0;
	/*过滤器初始化*/
	CAN1_Filter0.FilterFIFOAssignment=CAN_FILTER_FIFO0;
	CAN1_Filter0.FilterScale=CAN_FILTERSCALE_16BIT;
	CAN1_Filter0.FilterBank=0;
	CAN1_Filter0.FilterMode=CAN_FILTERMODE_IDMASK;
	CAN1_Filter0.FilterActivation=CAN_FILTER_ENABLE;
	CAN1_Filter0.FilterIdHigh=0x0000;
	CAN1_Filter0.FilterIdLow=0x0000;
	CAN1_Filter0.FilterMaskIdHigh=0x0000;
	CAN1_Filter0.FilterMaskIdLow=0x0000;
	if(HAL_CAN_ConfigFilter(&hcan1,&CAN1_Filter0)!=HAL_OK)
	{
		Error_Handler();
	}
	HAL_CAN_Start(&hcan1);//开启can1
}

/*发送函数*/
void CAN_Send(uint8_t *message)
{
	CAN_TxHeaderTypeDef CAN1_TxHeader0;
	uint32_t TxMailBox0;
	
	CAN1_TxHeader0.DLC = 8;//数据长度为8字节
	CAN1_TxHeader0.ExtId = 0;//扩展ID为0
	CAN1_TxHeader0.IDE = CAN_ID_STD;//标准ID
	CAN1_TxHeader0.RTR = CAN_RTR_DATA;//发送数据帧
	CAN1_TxHeader0.StdId = 0x1ff;//电机ID 1-4的标识符
	CAN1_TxHeader0.TransmitGlobalTime = DISABLE;//关闭全局时间发送
  
	TxMailBox0=CAN_TX_MAILBOX0;//指定邮箱

	HAL_CAN_AddTxMessage(&hcan1,&CAN1_TxHeader0,message,&TxMailBox0);//发送信息
}

/*接收函数*/
void CAN_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data)//使用数组与指针接收数据
{
    CAN_RxHeaderTypeDef RxMessage;
    uint8_t             Rx_data[8];
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxMessage, Rx_data); 
    
    if (RxMessage.IDE == CAN_ID_STD)
    {
            *ID = RxMessage.StdId;
    }
    else
    {
            *ID = RxMessage.ExtId;
    }
    
    if (RxMessage.RTR == CAN_RTR_DATA)
    {
            *Length = RxMessage.DLC;
            for (uint8_t i = 0; i < *Length; i ++)
            {
                    Data[i] = Rx_data[i];
            }
    }
    else
    {
     
    }
}