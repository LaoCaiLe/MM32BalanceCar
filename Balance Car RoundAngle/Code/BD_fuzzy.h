/*BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
【平    台】湖南工业大学
【编    写】BlueDeer
【E-mail  】2835923772@qq.com
【软件版本】V1.0
【最后更新】2019年7月15日
------------------------------------------------
【dev.env.】keil5及以上版本
【Target 】 i.MX RT1052
【Crystal】 24.000Mhz
【ARM PLL】 1200MHz
【SYS PLL】 528MHz
【USB PLL】 480MHz
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD*/

#ifndef BD_FUZZY_H_
#define BD_FUZZY_H_

#include "headfile.h"
extern float PFF[4];
extern float DFF[4];

extern uint8 fuzzy_txt[8];

typedef struct{
	float UFF_P[7];
	float UFF_D[7];
}_UFF_t;

typedef struct{
	float PF[2], DF[2];
	int Pn, Dn;
}_DMF_t;

typedef struct{
	float Kp0;
	float Kd0;
	float Kp;
	float Kd;
	float CurrentValue;
  float LeastValue;
	float SetValue;
	float err;
	float errlast;
	float errlastlast;
	float out;
	float outlast;
	float threshold;
	float maximum;
	float minimum;
	float factor;
}_Fuzzy_PD_t;

void fuzzy_init(float uff_p_max, float uff_d_max, _UFF_t* UFF);
float PID_FuzzyPD(float currentvalue, float* PFF, float* DFF, _Fuzzy_PD_t *Fuzzy_PD, _UFF_t* UFF);
float Fuzzy(float P, float D);
#endif
