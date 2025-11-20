/*
 * @Author: rogue-wave zhangjingjie@zju.edu.cn
 * @Date: 2025-11-19 21:51:59
 * @LastEditors: rogue-wave zhangjingjie@zju.edu.cn
 * @LastEditTime: 2025-11-19 21:54:30
 * @FilePath: \dipan1_project\Tasks\main_task.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/**
*******************************************************************************
* @file      :main_task.cpp
* @brief     :
* @history   :
*  Version     Date            Author          Note
*  V0.9.0      yyyy-mm-dd      <author>        1. <note>
*******************************************************************************
* @attention :
*******************************************************************************
*  Copyright (c) 2024 Hello World Team，Zhejiang University.
*  All Rights Reserved.
*******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "main_task.hpp"
#include "system_user.hpp"

#include "DT7.hpp"
#include "HW_can.hpp"
#include "dm4310_drv.hpp"
#include "iwdg.h"
#include "math.h"
#include "pid.hpp"
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

uint32_t tick = 0;
//常量定义
//变量定义
PID_ pid1(1.0f,0.0f,0.01f,0.0f,0.0f);
float now_vel = 0.0f;
//函数声明
void MODE4(void);
void MODE1(void);

namespace remote_control = hello_world::devices::remote_control;
static const uint8_t kRxBufLen = remote_control::kRcRxDataLen;
static uint8_t rx_buf[kRxBufLen];
remote_control::DT7 *rc_ptr;

void RobotInit(void) { rc_ptr = new remote_control::DT7(); }

void MainInit(void) {
  RobotInit();

  // 开启CAN1和CAN2
  CanFilter_Init(&hcan1);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

  CanFilter_Init(&hcan2);
  HAL_CAN_Start(&hcan2);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING);

  // 开启遥控器接收
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, kRxBufLen);

  // 开启定时器
  HAL_TIM_Base_Start_IT(&htim6);
}

void MainTask(void) { 
  tick++; 
  if(tick < 1000){
    MODE4();
    return;
  }
  MODE1();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

  if (htim == &htim6) {
    MainTask();
  }
}
uint8_t rx_data = 0;
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
  if (huart == &huart3) {
    if (Size == remote_control::kRcRxDataLen) {
      // TODO:在这里刷新看门狗
      HAL_IWDG_Refresh(&hiwdg);
      rc_ptr->decode(rx_buf);
    }

    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, kRxBufLen);
  }
}
void MODE4(void) {
  uint8_t KONG[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  CAN_Send_Msg(&hcan2,KONG,0x200,8);
}
void MODE1(void) {
  float b = 4.0f;
  pid1.set_error(b - now_vel);
  pid1.calc();
  int16_t a = pid1.get_output();//会损失一次精度
  uint8_t DATA[8] = {0, 0, 0, 0, 0, 0, 0, 0};//这里控制电流可能不够大
  DATA[0] = (uint8_t)(a >> 8);
  DATA[1] = (uint8_t)(a);
  CAN_Send_Msg(&hcan2,DATA,0x200,8);
}