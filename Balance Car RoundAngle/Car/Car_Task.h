#ifndef _CAR_TASK_H
#define _CAR_TASK_H

#include "headfile.h"

extern int16 Encoder_Left;
extern int16 Encoder_Right;

extern uint16 Inductance1;	//电感1
extern uint16 Inductance2;	//电感2
extern uint16 Inductance3;	//电感3
extern uint16 Inductance4;	//电感3

extern float Mid_Angle;
extern int Angle_Out;
extern int Speed_Out;
extern int Turn_Out;
extern int AngleSpeed_Out;
extern int Indutance_error;
extern int Speed_factor;
extern bool Elec_Control;
extern bool Stand_Enable;
extern bool AddError_Left;
extern bool AddError_Right;
extern bool Stop_Flag;

extern int32 tnow;
extern int16 Fall_time;		//倒地时间
extern int32 GetBall_time;
extern int StartAngle;
extern bool abandon_Round;
extern bool InRound_Enable;		//环岛检测
extern bool InRound_Flag1;
extern bool InRound_Flag2;
extern bool InRound_Flag3;
extern bool InRound_Flag4;
extern bool InRound_ToRight;	//右进环
extern bool InRound_ToLeft;	//左进环
extern int InRound_Angle;
extern float InRound_factor;
extern int InRound_Inductance_mid;
extern int InRound_Inductance_left;
extern int InRound_Inductance_right;

extern bool ForkRoad_Enable;	//三岔路口检测
extern bool ForkRoad_Flag1;
extern bool ForkRoad_Flag2;
extern bool ForkRoad_Flag3;
extern bool ForkRoad_Flag4;
extern bool ForkRoad_ToLeft;
extern bool ForkRoad_ToRight;
extern int16 InFork_time;
extern int InFork_TurnKd;
extern int InFork_Angle;
extern float InFork_factor;
extern int InFork_Inductance_mid;
extern int InFork_Inductance_left;
extern int InFork_Inductance_right;

extern int16 InFork_Speed;
extern int16 CarSpeed_Set;
extern int16 CarSpeed_Now;
extern bool getball_start_flag;
extern uint8 Tx_buff[4] ;
extern uint8 Tx_buff1[4] ;
void task_2ms(void);
void task_5ms(void);
void task_10ms(void);
void task_100ms(void);
extern float pitch,roll,yaw; 		//欧拉角
extern float gyrox,gyroy,gyroz;	//陀螺仪原始数据

#endif 
