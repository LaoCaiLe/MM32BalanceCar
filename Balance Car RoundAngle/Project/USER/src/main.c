/*
 * @Author: your name
 * @Date: 2021-07-18 13:48:27
 * @LastEditTime: 2021-07-18 19:52:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDKc:\Users\13784\Desktop\Balance Car RoundAngle\Project\USER\src\main.c
 */
#include "headfile.h"
#include "ANO_Data_Transfer.h"
#include "Car_FilterCalculate.h"
#include "Car_IMU.h"
#include "Car_data.h"
#include "isr.h"
#include "Key.h"
#include "HC_08.h"
#include "Car_Image.h"
#include "Car_control.h"
#include "menu_core.h"
#include "BD_fuzzy.h"
#include "menu_display.h"

// **************************** 代码区域 ****************************

float Turn_UFF_kp_max = 300.0f; //模糊控制参数初始化
float Turn_UFF_kd_max = 6000.0f;

int main(void)
{
	board_init(true);		// 初始化 debug 输出串口
	
	ips200_init();	//ips屏幕初始化	E7 E8 E0 E1 F0-F7
	
	seekfree_wireless_init();	//无线串口初始化
	UART_Bluetooth_Init(); //蓝牙模块初始化

	icm20602_init_spi();	  //陀螺仪初始化 B12 B13 B14 B15
	IMU_offset(&gyroscope); //校准 校准大概需要1s的时间
	
	tim_interrupt_init(TIM_1,500,0,0);	//定时器TIM1 500Hz 2ms
	tim_interrupt_init(TIM_5,200,0,1);	//定时器TIM5 200Hz 5ms
	tim_interrupt_init(TIM_6,100,0,2);	//定时器TIM6 100Hz 10ms
	tim_interrupt_init(TIM_7,10, 0,3);	//定时器TIM7 10Hz 100ms
 
	Key_Init();	// 按键初始化 C8 G7 G5 G3
	
	tim_counter_init(Encoder_LeftTimer,Encoder_Left_A,Encoder_Left_B);	//左编码器 B4 B5
	tim_counter_init(Encoder_RightTimer,Encoder_Right_A,Encoder_Right_B);	//右编码器 B6 B7
	
	adc_init(ADC_1, Inductance_Pin1, ADC_12BIT);	//C0
	adc_init(ADC_1, Inductance_Pin2, ADC_12BIT);	//C1
	adc_init(ADC_1, Inductance_Pin3, ADC_12BIT);	//C2
	adc_init(ADC_1, Inductance_Pin4, ADC_12BIT);	//C3
 
	gpio_init(Beep, GPO, GPIO_LOW, GPO_PUSH_PULL);	//beep G8
	gpio_init(LED1, GPO, GPIO_LOW, GPO_PUSH_PULL);	//led H2
	
	fuzzy_init(Turn_UFF_kp_max, Turn_UFF_kd_max, &Turn_UFF); //电磁模糊控制参数初始化
	
	Car_Data_Read(); //内存数据读取
	
	pwm_init(PWM_TIM, MotorA_1, 17000, 0);	//左电机A相 A2
	pwm_init(PWM_TIM, MotorA_2, 17000, 0);	//右电机B相 A0
	pwm_init(PWM_TIM, MotorB_1, 17000, 0);	//左电机A相 A1
	pwm_init(PWM_TIM, MotorB_2, 17000, 0);	//右电机B相 A3
		
	Menu_Init();	//多级菜单初始化

	while(1)
	{
	
	}
}

