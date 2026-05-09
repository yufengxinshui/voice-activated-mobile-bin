#include "Motor.h"


void Motor_Init(void)
{
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA |
        RCC_APB2Periph_GPIOB |
        RCC_APB2Periph_TIM1,
        ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    // PWM PA8 PA11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ·½Ïò¿ØÖÆ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin =
        GPIO_Pin_12 |
        GPIO_Pin_13 |
        GPIO_Pin_14 |
        GPIO_Pin_15;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;

    TIM_BaseInitStructure.TIM_Prescaler = 72 - 1;
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseInitStructure.TIM_Period = 100 - 1;
    TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_OCStructInit(&TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;

    // CH1 -> PA8
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    // CH4 -> PA11
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_Cmd(TIM1, ENABLE);
}

void Motor_Left_Forward(uint16_t speed)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_13);
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);

    TIM_SetCompare4(TIM1, speed);
}

void Motor_Left_Backward(uint16_t speed)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_13);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

    TIM_SetCompare4(TIM1, speed);
}

void Motor_Right_Forward(uint16_t speed)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_14);
    GPIO_ResetBits(GPIOB, GPIO_Pin_15);

    TIM_SetCompare1(TIM1, speed);
}

void Motor_Right_Backward(uint16_t speed)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_14);
    GPIO_SetBits(GPIOB, GPIO_Pin_15);

    TIM_SetCompare1(TIM1, speed);
}

void Motor_Stop(void)
{
    TIM_SetCompare1(TIM1, 0);
    TIM_SetCompare4(TIM1, 0);
}

void Motor_Forward(uint16_t speed)
{
    Motor_Left_Forward(speed);
    Motor_Right_Forward(speed);
}

void Motor_Backward(uint16_t speed)
{
    Motor_Left_Backward(speed);
    Motor_Right_Backward(speed);
}

void Motor_LeftTurn(uint16_t speed)
{
    Motor_Left_Backward(speed);
    Motor_Right_Forward(speed);
}

void Motor_RightTurn(uint16_t speed)
{
    Motor_Left_Forward(speed);
    Motor_Right_Backward(speed);
}
