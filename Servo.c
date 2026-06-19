#include "stm32f10x.h"
#include "PWM.h"

void Servo_Init(void)
{
    PWM_Init();
}

void Servo1_SetAngle(float Angle)
{
    u16 pulse = (u16)(Angle / 180.0f * 2000 + 500);
    PWM_SetServo1(pulse);
}

void Servo2_SetAngle(float Angle)
{
    u16 pulse = (u16)(Angle / 180.0f * 2000 + 500);
    PWM_SetServo2(pulse);
}
