#include "Car_Task.h"
#include "headfile.h"
#include "isr.h"
#include "Key.h"
#include "Car_Image.h"
#include "ANO_Data_Transfer.h"
#include "Car_control.h"
#include "Car_data.h"
#include "menu_core.h"
#include "Car_FilterCalculate.h"
#include "Car_IMU.h"
#include <stdio.h>
#include "BD_fuzzy.h"
#include <math.h>
#include "HC_08.h"

int32 tnow = 0;				//用于时间判断
int32 GetBall_time = 0; 	//接到球后时间
int16 Fall_time = 80;		//倒地时间
int16 Stop_time = 0;		//停止时间
int16 InFork_time = 0;		//进三岔提前时间

int16 Encoder_Left; 	//左编码器
int16 Encoder_Right;	//右编码器

uint8 Tx_buff[4] = {0x20,0x01,0x06,0x14};	//蓝牙发送字符串
uint8 Tx_buff1[4] = {0x19,0x99,0x11,0x23};	//蓝牙发送字符串

uint16 Inductance1;	//电感1
uint16 Inductance2;	//电感2
uint16 Inductance3;	//电感3
uint16 Inductance4;	//电感3

int16 CarSpeed_Set=130;	//速度设定值
int16 CarSpeed_Now=0;		//当前速度  

float Mid_Angle =-10;		//机械中值
int Mid_Line = 50;

int Turn_Out = 0;		//转向环输出值
int Angle_Out = 0;		//直立环输出值
int Speed_Out = 0;		//速度环输出值
int AngleSpeed_Out = 0;	//角速度环输出值

int Indutance_error; //电感误差

bool Elec_Control = 1; 		//电磁循迹
bool Stand_Enable = 1;		//直立模式
bool AddError_Left = 0;		//左误差补偿
bool AddError_Right = 0;	//右误差补偿

bool abandon_Round = 0; //舍弃环岛呜呜呜
bool InRound_Enable = 1;	//环岛检测
bool InRound_Flag1 = 1;
bool InRound_Flag2 = 0;
bool InRound_Flag3 = 0;
bool InRound_Flag4 = 0;
bool InRound_Flag5 = 0;
int InRound_Angle = 60;
bool InRound_ToRight = 0;	//右进环
bool InRound_ToLeft = 0;	//左进环
int InRound_Inductance_mid = 1600;
int InRound_Inductance_left = 850;
int InRound_Inductance_right = 850;
float yaw1;	//角度记录参数
int StartAngle = 3;

bool ForkRoad_Enable = 0;	//三岔路口检测
bool ForkRoad_Flag1 = 1;
bool ForkRoad_Flag2 = 0;
bool ForkRoad_Flag3 = 0;
bool ForkRoad_Flag4 = 0;
bool ForkRoad_ToLeft = 0;	
bool ForkRoad_ToRight = 0;
int InFork_Angle = 30;
int InFork_TurnKd = 4000;
int InFork_Inductance_mid = 650; 
int InFork_Inductance_left = 700;
int InFork_Inductance_right = 700;

float Elec_factor = 0;
float InRound_factor=0.6;
float InFork_factor=0.80;
int16 InFork_Speed = 100;

bool Stop_Flag = 0;
bool getball_start_flag = 0;

/****2ms任务函数******/
void task_2ms(void)
{
	spi_icm20602_get_data(&gyroscope);     //读取数据
	Data_steepest(&gyroscope);             //梯度下降绿标
	Q_IMUupdata(&gyroscope);               //解算姿态
	
}

/****5ms任务函数******/
void task_5ms(void)
{
	//Test_Send_User(AddError_Right,AddError_Left,0,gyroscope.euler.yaw,gyroscope.euler.pit,gyroscope.orig.gyro.y,Inductance1,Inductance2,Inductance3,Inductance4);	//发送数据到上位机
	
	Inductance1 = adc_mean_filter(Inductance_ADC,Inductance_Pin1,10);	//电感均值滤波10次
	Inductance2 = adc_mean_filter(Inductance_ADC,Inductance_Pin2,10);
	Inductance3 = adc_mean_filter(Inductance_ADC,Inductance_Pin3,10);
	Inductance4 = adc_mean_filter(Inductance_ADC,Inductance_Pin4,10);
	
	Encoder_Left = Encoder_Left*0.7f+(tim_counter_get_count(Encoder_LeftTimer,Encoder_Left_B))*0.3f; //获取左编码器值 一阶滤波
	Encoder_Right = Encoder_Right*0.7f+(-tim_counter_get_count(Encoder_RightTimer,Encoder_Right_B))*0.3f;	//获取右编码器值 一阶滤波
	CarSpeed_Now = (Encoder_Left + Encoder_Right)/2;
	
	tim_counter_rst(Encoder_LeftTimer);
	tim_counter_rst(Encoder_RightTimer);
	
	AngleSpeed_Out = AngleSpeed_Control(Angle_Out + gyroscope.orig.gyro.y);	//5ms角速度环计算

	if(getball_start_flag && Stand_Enable)
	{
//		if(GetBall_time<1000)
		GetBall_time++;
		
		if(AngleSpeed_Out>=0)
		{
			Set_PWM(AngleSpeed_Out+Turn_Out+2000, AngleSpeed_Out-Turn_Out+2000);
		}
		else
		{
			Set_PWM(AngleSpeed_Out+Turn_Out-1500, AngleSpeed_Out-Turn_Out-1500);
		}
	}
	
	if(CarSpeed_Now>5&&!getball_start_flag)
	{
		getball_start_flag = 1;
		seekfree_wireless_send_buff(Tx_buff1, sizeof(uint8)*4);
		seekfree_wireless_send_buff(Tx_buff1, sizeof(uint8)*4);
		seekfree_wireless_send_buff(Tx_buff1, sizeof(uint8)*4);
		seekfree_wireless_send_buff(Tx_buff1, sizeof(uint8)*4);
		seekfree_wireless_send_buff(Tx_buff1, sizeof(uint8)*4);
		uart_putbuff(Blueteeth_UART, Tx_buff1, sizeof(uint8)*4);
		uart_putbuff(Blueteeth_UART, Tx_buff1, sizeof(uint8)*4);
		uart_putbuff(Blueteeth_UART, Tx_buff1, sizeof(uint8)*4);
		uart_putbuff(Blueteeth_UART, Tx_buff1, sizeof(uint8)*4);
		uart_putbuff(Blueteeth_UART, Tx_buff1, sizeof(uint8)*4);
	}
}

/****10ms任务函数******/
void task_10ms(void)
{
	Angle_Out = Stand_Control(Mid_Angle - (float)Speed_Out/4, gyroscope.euler.pit, gyroscope.orig.gyro.y); //10ms直立环计算
	
	if(Elec_Control)
	{
		Indutance_error = 100*(Inductance3-Inductance2)/(Inductance3+Inductance2); //200 2800

		if(AddError_Right)
		{
			Indutance_error = 100*(Inductance4-Inductance2)/(Inductance4+Inductance2); 
			Indutance_error = Indutance_error*Elec_factor;
		}
		if(AddError_Left)
		{
			Indutance_error = 100*(Inductance3-Inductance1)/(Inductance3+Inductance1); 
			Indutance_error = Indutance_error*Elec_factor;
		}

		//Turn_Out = Turn_Control(Indutance_error); //10ms转向环计算
		Turn_FuzzyPD.Kp0 = Turn_Kp;
		Turn_FuzzyPD.Kd0 = Turn_Kd;
		Turn_Out = PID_FuzzyPD(-Indutance_error, PFF, DFF, &Turn_FuzzyPD, &Turn_UFF);
		
	}
	
	//环岛检测
	if(InRound_Enable)	
	{
		if(Inductance3>InRound_Inductance_mid && Inductance2>InRound_Inductance_mid && 
			Inductance1>InRound_Inductance_left && Inductance4>InRound_Inductance_right 
			&& InRound_Flag1 && GetBall_time>30)
		{
			if(abandon_Round)
			{
				InRound_Enable = 0;		
				ForkRoad_Reset();
			}
			else
			{
				InRound_Flag1 = 0;			//环岛标志位1
				InRound_Flag2 = 1;
			}	
			Beep_Start();

		}
	
		if(InRound_Flag2 /*&& Inductance1<580 && Inductance1>300*/)
		{	
			yaw1 = gyroscope.euler.yaw;	//记录当前转向角的值
			// if(InRound_ToRight)
			// {
			// 	if(yaw1 > 120)
			// 	{
			// 		yaw1-=300;
			// 	}
			// 	else
			// 	{
			// 		yaw1+=60;
			// 	}
			// 	AddError_Left = 0;
			// 	AddError_Right = 1;
			// }
			// if(InRound_ToLeft)
			// {
			// 	if(yaw1 < -120)
			// 	{
			// 		yaw1 += 300;
			// 	}
			// 	else
			// 	{
			// 		yaw1 -= 60;
			// 	}
			// 	AddError_Left = 1;
			// 	AddError_Right = 0;
				
			// }
			if(InRound_ToRight)
			{
				if(yaw1 > (180 - InRound_Angle))
				{
					yaw1-= (360 - InRound_Angle);
				}
				else
				{
					yaw1+=InRound_Angle;
				}
				AddError_Left = 0;
				AddError_Right = 1;
			}
			if(InRound_ToLeft)
			{
				if(yaw1 < -(180 - InRound_Angle))
				{
					yaw1 += (360 - InRound_Angle);
				}
				else
				{
					yaw1 -= InRound_Angle;
				}
				AddError_Left = 1;
				AddError_Right = 0;
				
			}
			Elec_factor = InRound_factor;
			InRound_Flag2 = 0;
			InRound_Flag3 = 1;
		}
		
		if(InRound_Flag3)
		{
			if((gyroscope.euler.yaw > yaw1-5) && (gyroscope.euler.yaw < yaw1+5))	
			{					
				InRound_Flag3 = 0;
				InRound_Flag4 = 1;

				AddError_Right = 0;
				AddError_Left = 0;
			}
			else
			{
				Beep_Start();
			}
		}
		if(InRound_Flag4)
		{
			tnow++;
			if(Inductance3>InRound_Inductance_mid-100 && 
				Inductance2>InRound_Inductance_mid-100 &&
			  	tnow > 150)
			{
				tnow = 0;				
				InRound_Flag4 = 0;
				InRound_Enable = 0;
				Beep_Start();		
				ForkRoad_Reset();				
			}
		}
	}
	
	
	//三岔路口检测
	if(ForkRoad_Enable)
	{
		if(ForkRoad_Flag1)
		{
			tnow++;
			if(tnow>InFork_time) //一定时间后开启三岔路口检测
			{
				tnow = 0;
				Beep_Start();
				CarSpeed_Set = InFork_Speed;
				ForkRoad_Flag1 = 0;
				ForkRoad_Flag2 = 1;
			}
		}
		
		if(Inductance3<InFork_Inductance_mid+250 && Inductance2<InFork_Inductance_mid+250 
			&& Inductance3>InFork_Inductance_mid && Inductance2>InFork_Inductance_mid 
			&& Inductance1>InFork_Inductance_left && Inductance4>InFork_Inductance_right
			&& ForkRoad_Flag2 )
		{
	
			yaw1 = gyroscope.euler.yaw;	//记录当前转向角的值
			if(ForkRoad_ToRight)
			{
				if(yaw1 > (180-InFork_Angle))
				{
					yaw1-=(360-InFork_Angle);
				}
				else
				{
					yaw1+=InFork_Angle;
				}
				AddError_Right = 1;
				AddError_Left = 0;
			}
			if(ForkRoad_ToLeft)
			{
				if(yaw1 < -(180-InFork_Angle))
				{
					yaw1 += (360-InFork_Angle);
				}
				else
				{
					yaw1 -= InFork_Angle;
				}
				AddError_Left = 1;
				AddError_Right = 0;
			}
			Elec_factor = InFork_factor;
			ForkRoad_Flag2 = 0;
			ForkRoad_Flag3 = 1;
			Beep_Start();
		}
		
		if(ForkRoad_Flag3)
		{
					
			if((gyroscope.euler.yaw > yaw1-5) && (gyroscope.euler.yaw < yaw1+5))	
			{
				ForkRoad_Flag3 = 0;
				ForkRoad_Flag4 = 1;
				CarSpeed_Set = read_buf[0];
				AddError_Right = 0;
				AddError_Left = 0;
				
			}	
		
		}
		
		if(ForkRoad_Flag4)
		{			
			tnow++;
			if(tnow > Fall_time)
			{
				
				seekfree_wireless_send_buff(Tx_buff, sizeof(uint8)*4);
				seekfree_wireless_send_buff(Tx_buff, sizeof(uint8)*4);
				seekfree_wireless_send_buff(Tx_buff, sizeof(uint8)*4);
				seekfree_wireless_send_buff(Tx_buff, sizeof(uint8)*4);
				seekfree_wireless_send_buff(Tx_buff, sizeof(uint8)*4);
				uart_putbuff(Blueteeth_UART, Tx_buff, sizeof(uint8)*4);
				uart_putbuff(Blueteeth_UART, Tx_buff, sizeof(uint8)*4);
				uart_putbuff(Blueteeth_UART, Tx_buff, sizeof(uint8)*4);
				uart_putbuff(Blueteeth_UART, Tx_buff, sizeof(uint8)*4);
				uart_putbuff(Blueteeth_UART, Tx_buff, sizeof(uint8)*4);
			
				Stop_Flag=1;
				Stand_Enable = 0;
				Turn_Out=0;
				Set_PWM(-8000,-8000);
				Beep_Start();		
				systick_delay_ms(400);
				Set_PWM(0,0);
				
				ForkRoad_Flag4 = 0;				
				ForkRoad_Enable = 0;
				getball_start_flag = 0;
				
			}
		}
	}
}

/****100ms任务函数******/
void task_100ms(void)
{	
	Speed_Out = Speed_Control(CarSpeed_Set, CarSpeed_Now);	//100ms速度环计算
	Key_task();				//菜单按键任务扫描
	gpio_toggle(LED1);	//led闪烁
	Beep_Stop();
		
	if(show_flag)	Information_show();//小车各信息显示

	if(GetBall_time>0 && GetBall_time<200)
	{
		Mid_Angle = StartAngle;	
		Turn_Kd = 1000;
		Beep_Start();
	}
	else if(GetBall_time<600)
	{
		Mid_Angle = uint32_conversion_float(read_buf[13]);
		Turn_Kd = uint32_conversion_float(read_buf[25]);
	}
	

	if(!Stop_Flag)
	{
		if((/*gyroscope.euler.pit<-50 || gyroscope.euler.pit > -1 || */Inductance1+Inductance4<100) && GetBall_time>300 )
		{
			Stop_time++;
			// Stand_Enable = 0;
			// Set_PWM(0,0);
		}
		else
		{	
			Stop_time = 0;			
			Stand_Enable = 1;
		}

		if(Stop_time>5&& GetBall_time>300 )
		{
			Stand_Enable = 0;
			Set_PWM(0,0);
		}
	}

}