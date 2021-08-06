/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file				headfile
* @company			�ɶ���ɿƼ����޹�˾
* @author			��ɿƼ�(QQ3184284598)
* @version			�鿴doc��version�ļ� �汾˵��
* @Software			IAR 8.3 or MDK 5.28
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/
 
#ifndef _headfile_h
#define _headfile_h


#include <stdint.h>

#include "board.h"
#include "SEEKFREE_PRINTF.h"


//���
#define PWM_TIM TIM_2
#define MotorA_1 TIM_2_CH4_A03
#define MotorA_2 TIM_2_CH2_A01
#define MotorB_1 TIM_2_CH1_A00
#define MotorB_2 TIM_2_CH3_A02
#define MotorPwm_Max 48000
#define MotorPwm_Min -48000


//������
#define Encoder_LeftTimer 	TIM_3
#define Encoder_Left_A TIM_3_ENC1_B04
#define Encoder_Left_B B5

#define Encoder_RightTimer	TIM_4
#define Encoder_Right_A TIM_4_ENC1_B06
#define Encoder_Right_B B7

//��Ŵ�����
#define Inductance_ADC ADC_1
#define Inductance_Pin1 ADC1_CH10_C00
#define Inductance_Pin2 ADC1_CH11_C01
#define Inductance_Pin3 ADC1_CH12_C02
#define Inductance_Pin4 ADC1_CH13_C03


//LED
#define LED2 B13
#define LED1 H2

//������
#define Beep G8


//------��ɿƼ���Ƭ����������ͷ�ļ�
#include "zf_adc.h"
#include "zf_camera.h"
#include "zf_exti.h"
#include "zf_flash.h"
#include "zf_gpio.h"
#include "zf_spi.h"
#include "zf_systick.h"
#include "zf_pit.h"
#include "zf_pwm.h"
#include "zf_tim.h"
#include "zf_uart.h"
#include "zf_fsmc.h"

//------��ɿƼ���Ʒ����ͷ�ļ�
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_7725.h"
#include "SEEKFREE_ABSOLUTE_ENCODER.h"
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_TSL1401.h"
#include "SEEKFREE_UART_7725.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_FUN.h"

#endif

