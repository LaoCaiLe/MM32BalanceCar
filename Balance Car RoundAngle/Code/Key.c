#include "key.h"

/**
 * @brief 按键初始化
 * 
*/
void Key_Init(void)
{
    gpio_init(Key1_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(Key2_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(Key3_PIN, GPI, 1, GPI_PULL_UP);
    gpio_init(Key4_PIN, GPI, 1, GPI_PULL_UP);
}



/**
 * @brief 按键按下事件
*/
uint8 Key_Scan(uint8 mode)
{
    static uint8 button_status_flag = 1;
    if(button_status_flag && (gpio_get(Key1_PIN) == 0 || gpio_get(Key2_PIN) == 0 || gpio_get(Key4_PIN) == 0 || gpio_get(Key3_PIN) == 0))
    {
        systick_delay_ms(10);
        button_status_flag = 0;

        if (gpio_get(Key1_PIN) == 0)
            return Key1;
				
        else if (gpio_get(Key2_PIN) == 0)
            return Key2;
				
        else if (gpio_get(Key3_PIN) == 0)
            return Key3;
				
        else if (gpio_get(Key4_PIN) == 0)
            return Key4;
    }
    else if(gpio_get(Key1_PIN) == 1 && gpio_get(Key2_PIN) == 1 && gpio_get(Key3_PIN) == 1 && gpio_get(Key4_PIN) == 1)
    {
        button_status_flag = 1;
    }
    if(mode==1) //连续按键按下
    {
        button_status_flag = 1;
    }
    return 0;
}
