#ifndef __MENU_CORE_H
#define __MENU_CORE_H

#include "headfile.h"

typedef struct SubMenu *SubMenuItem;
typedef struct MainMenu *MainMenuMenu;
typedef void (*tMenuFunc)(void);

extern bool show_flag;
extern struct MainMenu * MenuItem;
struct SubMenu  //�Ӳ˵��ṹ��
{
	const char *Menu_Title;
	tMenuFunc Menu_SureFunc;
	tMenuFunc Menu_CancelFunc;
	MainMenuMenu Next_Menu;
};

struct MainMenu //���˵��ṹ��
{
	const char *Menu_Title; //�˵�ҳ����
	SubMenuItem psItems;    //�˵�ҳ�а����Ĳ˵���
	uint8 nItems;         //�˵�����
};

#define COUNT_OF(A) (sizeof(A) / sizeof(*(A)))
//#define MAX_MENU_LEVELS 6

//typedef void (*tMenuFunc)(void);
//typedef struct sMenuItem *tMenuItem;
//typedef struct sMenu *tMenu;

///*�˵���*/
//struct sMenuItem
//{
//    const char *pszTitle;       //�˵�ҳ����
//    tMenuFunc pfMenuFunc;       //���ܺ���
//    tMenuFunc pfUpDownMenuFunc; //���¶���ִ�еĹ���
//    tMenu psSubMenu;            //�Ӳ˵�
//};

///*�˵�ҳ*/
//struct sMenu
//{
//    const char *pszTitle; //�˵�ҳ����
//    tMenuItem psItems;    //�˵�ҳ�а����Ĳ˵���
//    uint8 nItems;         //�˵�����
//};

void Nop_Func();
void Menu_Init(void);
void Key_task(void);
void Menu_Display(struct MainMenu *MenuItem_Show,char Str_num);
void SubMenu_Display(struct MainMenu *MenuItem_Show);

extern void SelectFunc(void);
extern void ReturnFunc(void);
extern void UpFunc(void);
extern void DownFunc(void);

void speed_kp_Add(void);
void speed_kp_Sub(void);
void speed_ki_Add(void);
void speed_ki_Sub(void);
void speed_kd_Add(void);
void speed_kd_Sub(void);
void SpeedPid_OutMax_Add(void);
void SpeedPid_OutMax_Sub(void);
void SpeedPid_OutMin_Add(void);
void SpeedPid_OutMin_Sub(void);

void Angle_kp_Add(void);
void Angle_kp_Sub(void);
void Angle_ki_Add(void);
void Angle_ki_Sub(void);
void Angle_kd_Add(void);
void Angle_kd_Sub(void);
void AnglePid_OutMax_Add(void);
void AnglePid_OutMax_Sub(void);
void AnglePid_OutMin_Add(void);
void AnglePid_OutMin_Sub(void);

void Mid_Angle_Add(void);
void Mid_Angle_Sub(void);

void AngleSpeed_kp_Add(void);
void AngleSpeed_kp_Sub(void);
void AngleSpeed_ki_Add(void);
void AngleSpeed_ki_Sub(void);
void AngleSpeed_kd_Add(void);
void AngleSpeed_kd_Sub(void);
void AngleSpeedPid_OutMax_Add(void);
void AngleSpeedPid_OutMax_Sub(void);
void AngleSpeedPid_OutMin_Add(void);
void AngleSpeedPid_OutMin_Sub(void);

void Turn_kp_Add(void);
void Turn_kp_Sub(void);
void InFork_TurnKd_Add(void);
void InFork_TurnKd_Sub(void);
void Turn_kd_Add(void);
void Turn_kd_Sub(void);
void Turn_OutMax_Add(void);
void Turn_OutMax_Sub(void);
void Turn_OutMin_Add(void);
void Turn_OutMin_Sub(void);

void CarSpeed_Add(void);
void CarSpeed_Sub(void);
void getball_flag();
void StartAngle_Add(void);
void StartAngle_Sub(void);

void Information_show();
void show_Enable();
void show_Disable();
void Follow_Mode();
void Stand_Mode();
void Camera_mode();
void Transmit_buff();

void ForkRoad_Reset();
void ForkRoad_Enable_Set();
void InFork_factor_Add();
void InFork_factor_Sub();
void InFork_speed_Add();
void InFork_speed_Sub();
void ForkRoad_L();
void ForkRoad_R();
void InFork_Angle_Add();
void InFork_Angle_Sub();

void Round_Reset();
void InRound_Enable_Set();

void Round_L();
void Round_R();

void Fall_time_Add();
void Fall_time_Sub();

void InRound_factor_Add();
void InRound_factor_Sub();
void InRound_Inductance_M_Add();
void InRound_Inductance_M_Sub();
void InRound_Inductance_L_Add();
void InRound_Inductance_L_Sub();
void InRound_Inductance_R_Add();
void InRound_Inductance_R_Sub();
void InRound_Angle_Add();
void InRound_Angle_Sub();
void AddError_left();
void AddError_right();

void InFork_Inductance_M_Add();
void InFork_Inductance_M_Sub();
void InFork_Inductance_L_Add();
void InFork_Inductance_L_Sub();
void InFork_Inductance_R_Add();
void InFork_Inductance_R_Sub();
void InFork_time_Add();
void InFork_time_Sub();
void Is_abandon_Round();
#endif