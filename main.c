#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Servo.h"

uint8_t Count = 0;          // 动作执行次数
uint8_t IsRunning = 0;      // 防止重复触发

/**
  * @brief  执行一次完整的舵机动作（加速版）
  * @param  无
  * @retval 无
  */
void ServoAction(void)
{
    if (IsRunning == 1) return;
    
    IsRunning = 1;
    OLED_ShowString(3, 1, "gogogo~~~ ");
    OLED_ShowString(4, 1, "            ");
    
    // ===== 舵机1：0°→180°→0°（加速：300ms间隔） =====
    Servo1_SetAngle(0);
    Delay_ms(300);          // 从1000ms改为300ms
    Servo1_SetAngle(180);
    Delay_ms(300);
    Servo1_SetAngle(0);
    Delay_ms(300);
    
    // ===== 舵机2：0°→180°→0°（加速：300ms间隔） =====
    Servo2_SetAngle(0);
    Delay_ms(300);
    Servo2_SetAngle(180);
    Delay_ms(300);
    Servo2_SetAngle(0);
    Delay_ms(300);
    
    // ===== 计数+1并更新显示 =====
    Count++;
    OLED_ShowNum(2, 7, Count, 3);
    
    OLED_ShowString(3, 1, "Press PB0   ");
    OLED_ShowString(4, 1, "to Start    ");
    
    IsRunning = 0;
}

int main(void)
{
    // 初始化
    OLED_Init();
    Key_Init();
    Servo_Init();
    
    // 舵机复位到0°
    Servo1_SetAngle(0);
    Servo2_SetAngle(0);
    Delay_ms(500);
    
    // 显示初始界面
    OLED_ShowString(1, 1, "AAA guanli");
    OLED_ShowString(2, 1, "Count:000");
    OLED_ShowString(3, 1, "Press PB0   ");
    OLED_ShowString(4, 1, "to Start    ");
    
    while (1)
    {
        if (Key_GetNum() == 1)
        {
            ServoAction();   // 执行动作，计数+1
        }
    }
}
