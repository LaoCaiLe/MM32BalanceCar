#ifndef _CAR_CONTROL_H
#define _CAR_CONTROL_H
#include "BD_fuzzy.h"

extern _Fuzzy_PD_t Turn_FuzzyPD;
extern _UFF_t Turn_UFF, L_UFF, R_UFF;

extern float Speed_kp;
extern float Speed_ki;
extern float Speed_kd;
extern int SpeedPid_OutMax;
extern int SpeedPid_OutMin;

extern float Angle_Kp;
extern float Angle_Ki;
extern float Angle_Kd;
extern int AnglePid_OutMax;
extern int AnglePid_OutMin;

extern float Turn_Kp;
extern float Turn_Ki;
extern float Turn_Kd;
extern int TurnPid_OutMax;
extern int TurnPid_OutMin;

extern float AngleSpeed_Kp;
extern float AngleSpeed_Ki;
extern float AngleSpeed_Kd;
extern int AngleSpeedPid_OutMax;
extern int AngleSpeedPid_OutMin;


int Speed_Control(int Target, int currentvalue);
int Stand_Control(int Target, float currentvalue, int groy_y);
int AngleSpeed_Control(int error);
int Turn_Control(int error);

void Turn_Right(void);
void Turn_Left(void);
void Car_Stop(void);
void Set_PWM(int duty1,int duty2);
void Beep_Start(void);
void Beep_Stop(void);
#endif

