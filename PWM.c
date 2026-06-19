#include "stm32f10x.h"

void PWM_Init(void)
{
    // ===== 1. 开启所有需要的时钟 =====
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   // ⚠️ 关键：TIM3时钟

    // ===== 2. 配置GPIO =====
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // PA0（舵机1）
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // PA6（舵机2）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ===== 3. 定时器基础配置（共用结构体） =====
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    // ===== 4. TIM2配置（PA0） =====
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500;

    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);

    // ===== 5. TIM3配置（PA6）=====
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 1500;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);   // PA6对应TIM3的通道1
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);                     // ⚠️ 关键：启动TIM3
}

// 舵机1（PA0）
void PWM_SetServo1(u16 Compare)
{
    TIM_SetCompare1(TIM2, Compare);
}

// 舵机2（PA6）
void PWM_SetServo2(u16 Compare)
{
    TIM_SetCompare1(TIM3, Compare);   // PA6对应TIM3_CH1
}
