#include "stm32f10x.h"

void Delay_us(uint32_t us)
{
    uint32_t i;
    while (us--)
    {
        i = 8;  // 72MHz 下约 1us
        while (i--);
    }
}

void Delay_ms(uint32_t ms)
{
    while (ms--)
    {
        Delay_us(1000);
    }
}
