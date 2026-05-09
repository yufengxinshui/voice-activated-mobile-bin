#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

void Motor_Init(void);

void Motor_Left_Forward(uint16_t speed);
void Motor_Left_Backward(uint16_t speed);

void Motor_Right_Forward(uint16_t speed);
void Motor_Right_Backward(uint16_t speed);

void Motor_Stop(void);

void Motor_Forward(uint16_t speed);
void Motor_Backward(uint16_t speed);

void Motor_LeftTurn(uint16_t speed);
void Motor_RightTurn(uint16_t speed);

#endif
