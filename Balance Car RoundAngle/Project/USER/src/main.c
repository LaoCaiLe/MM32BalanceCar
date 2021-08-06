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

// **************************** �������� ****************************

float Turn_UFF_kp_max = 300.0f; //ģ�����Ʋ�����ʼ��
float Turn_UFF_kd_max = 6000.0f;

int main(void)
{
	board_init(true);		// ��ʼ�� debug �������
	
	ips200_init();	//ips��Ļ��ʼ��	E7 E8 E0 E1 F0-F7
	
	seekfree_wireless_init();	//���ߴ��ڳ�ʼ��
	UART_Bluetooth_Init(); //����ģ���ʼ��

	icm20602_init_spi();	  //�����ǳ�ʼ�� B12 B13 B14 B15
	IMU_offset(&gyroscope); //У׼ У׼�����Ҫ1s��ʱ��
	
	tim_interrupt_init(TIM_1,500,0,0);	//��ʱ��TIM1 500Hz 2ms
	tim_interrupt_init(TIM_5,200,0,1);	//��ʱ��TIM5 200Hz 5ms
	tim_interrupt_init(TIM_6,100,0,2);	//��ʱ��TIM6 100Hz 10ms
	tim_interrupt_init(TIM_7,10, 0,3);	//��ʱ��TIM7 10Hz 100ms
 
	Key_Init();	// ������ʼ�� C8 G7 G5 G3
	
	tim_counter_init(Encoder_LeftTimer,Encoder_Left_A,Encoder_Left_B);	//������� B4 B5
	tim_counter_init(Encoder_RightTimer,Encoder_Right_A,Encoder_Right_B);	//�ұ����� B6 B7
	
	adc_init(ADC_1, Inductance_Pin1, ADC_12BIT);	//C0
	adc_init(ADC_1, Inductance_Pin2, ADC_12BIT);	//C1
	adc_init(ADC_1, Inductance_Pin3, ADC_12BIT);	//C2
	adc_init(ADC_1, Inductance_Pin4, ADC_12BIT);	//C3
 
	gpio_init(Beep, GPO, GPIO_LOW, GPO_PUSH_PULL);	//beep G8
	gpio_init(LED1, GPO, GPIO_LOW, GPO_PUSH_PULL);	//led H2
	
	fuzzy_init(Turn_UFF_kp_max, Turn_UFF_kd_max, &Turn_UFF); //���ģ�����Ʋ�����ʼ��
	
	Car_Data_Read(); //�ڴ����ݶ�ȡ
	
	pwm_init(PWM_TIM, MotorA_1, 17000, 0);	//����A�� A2
	pwm_init(PWM_TIM, MotorA_2, 17000, 0);	//�ҵ��B�� A0
	pwm_init(PWM_TIM, MotorB_1, 17000, 0);	//����A�� A1
	pwm_init(PWM_TIM, MotorB_2, 17000, 0);	//�ҵ��B�� A3
		
	Menu_Init();	//�༶�˵���ʼ��

	while(1)
	{
	
	}
}

