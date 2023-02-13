#include "Key.h"
#include "menu_display.h"
#include "menu_core.h"
#include "Car_control.h"
#include "Car_Task.h"
#include "Car_data.h"
#include "Car_Image.h"
#include "Car_FilterCalculate.h"
#include "Car_IMU.h"
#include <stdio.h>
#include "HC_08.h"
#include "BD_fuzzy.h"
//MainMenuMenu MenuItem;
//MainMenuMenu Last_MenuItem;
//SubMenuItem psMenuItem;
bool show_flag =0;
struct MainMenu * MenuItem;
struct MainMenu * Last_MenuItem;
struct SubMenu * psMenuItem;

int menu_Index=0; //鑿滃崟涓嬫爣
int Last_menu_Index = 0;

char dis_buff[50]={0}; //字符串缓冲区

char Rx_buff[20];

//速度控制菜单
struct SubMenu CarspeedItems[] = 
{
	{"CarSpeed_Add",CarSpeed_Add,Nop_Func,NULL},
	{"CarSpeed_Sub",CarSpeed_Sub,Nop_Func,NULL},
	{"Mid_Angle_Add",Mid_Angle_Add,Nop_Func,NULL},
	{"Mid_Angle_Sub",Mid_Angle_Sub,Nop_Func,NULL},
	{"StartAngle_Add",StartAngle_Add,Nop_Func,NULL},
	{"StartAngle_Sub",StartAngle_Sub,Nop_Func,NULL},
	{"getball_start_flag",getball_flag,Nop_Func,NULL},
	{"Elec_Control",Follow_Mode,Nop_Func,NULL},
	{"Stand_Enable",Stand_Mode,Nop_Func,NULL},
	{"Transmit_buff",Transmit_buff,Nop_Func,NULL},
	{"Save",Car_Data_Write,Nop_Func,NULL},
	{"Reset",Car_Data_Read,Nop_Func,NULL},
};
struct MainMenu Car_Speed = {"Car_Speed",CarspeedItems, COUNT_OF(CarspeedItems)};


//角速度pid菜单
struct SubMenu AngleSpeedPidItems[] = 
{
	{"AngleSpeed_Kp_Add",AngleSpeed_kp_Add,Nop_Func,NULL},
	{"AngleSpeed_Kp_Sub",AngleSpeed_kp_Sub,Nop_Func,NULL},
	{"AngleSpeed_Ki_Add",AngleSpeed_ki_Add,Nop_Func,NULL},
	{"AngleSpeed_Ki_Sub",AngleSpeed_ki_Sub,Nop_Func,NULL},
	{"AngleSpeed_Kd_Add",AngleSpeed_kd_Add,Nop_Func,NULL},
	{"AngleSpeed_Kd_Sub",AngleSpeed_kd_Sub,Nop_Func,NULL},
	{"AngleSpeedPid_OutMax_Add",AngleSpeedPid_OutMax_Add,Nop_Func,NULL},
	{"AngleSpeedPid_OutMax_Sub",AngleSpeedPid_OutMax_Sub,Nop_Func,NULL},
	{"AngleSpeedPid_OutMin_Add",AngleSpeedPid_OutMin_Add,Nop_Func,NULL},
	{"AngleSpeedPid_OutMin_Sub",AngleSpeedPid_OutMin_Sub,Nop_Func,NULL},
	{"Save",Car_Data_Write,Nop_Func,NULL},
	{"Reset",Car_Data_Read,Nop_Func,NULL},
};
struct MainMenu AngleSpeed_PID = {"AngleSpeed_PID",AngleSpeedPidItems, COUNT_OF(AngleSpeedPidItems)};

//电磁转向环pid
struct SubMenu TurnPidItems[] = 
{
	{"Turn_Kp_Add",Turn_kp_Add,Nop_Func,NULL},
	{"Turn_Kp_Sub",Turn_kp_Sub,Nop_Func,NULL},		
	{"InFork_TurnKd_Add",InFork_TurnKd_Add,Nop_Func,NULL},
	{"InFork_TurnKd_Sub",InFork_TurnKd_Sub,Nop_Func,NULL},
	{"Turn_Kd_Add",Turn_kd_Add,Nop_Func,NULL},
	{"Turn_Kd_Sub",Turn_kd_Sub,Nop_Func,NULL},
	{"Turn_OutMax_Add",Turn_OutMax_Add,Nop_Func,NULL},
	{"Turn_OutMax_Sub",Turn_OutMax_Sub,Nop_Func,NULL},
	{"Turn_OutMin_Add",Turn_OutMin_Add,Nop_Func,NULL},
	{"Turn_OutMin_Sub",Turn_OutMin_Sub,Nop_Func,NULL},
	{"Save",Car_Data_Write,Nop_Func,NULL},
	{"Reset",Car_Data_Read,Nop_Func,NULL},
};
struct MainMenu Turn_PID = {"Turn_PID",TurnPidItems, COUNT_OF(TurnPidItems)};

//速度pid菜单
struct SubMenu SpeedPidItems[] = 
{
	{"Speed_Kp_Add",speed_kp_Add,Nop_Func,NULL},
	{"Speed_Kp_Sub",speed_kp_Sub,Nop_Func,NULL},
	{"Speed_Ki_Add",speed_ki_Add,Nop_Func,NULL},
	{"Speed_Ki_Sub",speed_ki_Sub,Nop_Func,NULL},
	{"Speed_Kd_Add",speed_kd_Add,Nop_Func,NULL},
	{"Speed_Kd_Sub",speed_kd_Sub,Nop_Func,NULL},
	{"SpeedPid_OutMax_Add",SpeedPid_OutMax_Add,Nop_Func,NULL},
	{"SpeedPid_OutMax_Sub",SpeedPid_OutMax_Sub,Nop_Func,NULL},
	{"SpeedPid_OutMin_Add",SpeedPid_OutMin_Add,Nop_Func,NULL},
	{"SpeedPid_OutMin_Sub",SpeedPid_OutMin_Sub,Nop_Func,NULL},
	{"Save",Car_Data_Write,Nop_Func,NULL},
	{"Reset",Car_Data_Read,Nop_Func,NULL},
};
struct MainMenu Speed_PID = {"Speed_PID",SpeedPidItems, COUNT_OF(SpeedPidItems)};


//角度pid菜单
struct SubMenu AnglePidItems[] = 
{
	{"Angle_Kp_Add",Angle_kp_Add,Nop_Func,NULL},
	{"Angle_Kp_Sub",Angle_kp_Sub,Nop_Func,NULL},
	{"Angle_ki_Add",Angle_ki_Add,Nop_Func,NULL},
	{"Angle_ki_Sub",Angle_ki_Sub,Nop_Func,NULL},
	{"Angle_Kd_Add",Angle_kd_Add,Nop_Func,NULL},
	{"Angle_Kd_Sub",Angle_kd_Sub,Nop_Func,NULL},
	{"AnglePid_OutMax_Add",AnglePid_OutMax_Add,Nop_Func,NULL},
	{"AnglePid_OutMax_Sub",AnglePid_OutMax_Sub,Nop_Func,NULL},
	{"AnglePid_OutMin_Add",AnglePid_OutMin_Add,Nop_Func,NULL},
	{"AnglePid_OutMin_Sub",AnglePid_OutMin_Sub,Nop_Func,NULL},
	{"Save",Car_Data_Write,Nop_Func,NULL},
	{"Reset",Car_Data_Read,Nop_Func,NULL},
};
struct MainMenu Angle_PID = {"Angle_PID",AnglePidItems, COUNT_OF(AnglePidItems)};


//环岛数据菜单
struct SubMenu RoundItems[] = 
{
	{"Round_Reset",Round_Reset,Nop_Func,NULL},
	{"InRound_Enable_Set",InRound_Enable_Set,Nop_Func,NULL},
	{"InRound_ToLeft",Round_L,Nop_Func,NULL},
	{"InRound_ToRight",Round_R,Nop_Func,NULL},
	{"InRound_factor_Add",InRound_factor_Add,Nop_Func,NULL},
	{"InRound_factor_Sub",InRound_factor_Sub,Nop_Func,NULL},
	{"InRound_Angle_Add",InRound_Angle_Add,Nop_Func,NULL},
	{"InRound_Angle_Sub",InRound_Angle_Sub,Nop_Func,NULL},
	{"abandon_Round",Is_abandon_Round,Nop_Func,NULL},
	{"Save",Car_Data_Write,Nop_Func,NULL},
};
struct MainMenu Round = {"Round_Info",RoundItems, COUNT_OF(RoundItems)};

//三岔路口数据菜单
struct SubMenu ForkRoadItems[] = 
{
	{"ForkRoad_Reset",ForkRoad_Reset,Nop_Func,NULL},
	{"ForkRoad_Enable_Set",ForkRoad_Enable_Set,Nop_Func,NULL},
	{"ForkRoad_ToLeft",ForkRoad_L,Nop_Func,NULL},
	{"ForkRoad_ToRight",ForkRoad_R,Nop_Func,NULL},
	{"InFork_factor_Add",InFork_factor_Add,Nop_Func,NULL},
	{"InFork_factor_Sub",InFork_factor_Sub,Nop_Func,NULL},
	{"InFork_speed_Add",InFork_speed_Add,Nop_Func,NULL},
	{"InFork_speed_Sub",InFork_speed_Sub,Nop_Func,NULL},
	{"InFork_Angle_Add",InFork_Angle_Add,Nop_Func,NULL},
	{"InFork_Angle_Sub",InFork_Angle_Sub,Nop_Func,NULL},
	{"Save",Car_Data_Write,Nop_Func,NULL},
};
struct MainMenu ForkRoad = {"ForkRoad_Info",ForkRoadItems, COUNT_OF(ForkRoadItems)};

//入环数据菜单
struct SubMenu InRound_SetItems[] = 
{
	{"InRound_Inductance_M_Add",InRound_Inductance_M_Add,Nop_Func,NULL},
	{"InRound_Inductance_M_Sub",InRound_Inductance_M_Sub,Nop_Func,NULL},
	{"InRound_Inductance_L_Add",InRound_Inductance_L_Add,Nop_Func,NULL},
	{"InRound_Inductance_L_Sub",InRound_Inductance_L_Sub,Nop_Func,NULL},
	{"InRound_Inductance_R_Add",InRound_Inductance_R_Add,Nop_Func,NULL},
	{"InRound_Inductance_R_Sub",InRound_Inductance_R_Sub,Nop_Func,NULL},
	{"Save",Car_Data_Write,Nop_Func,NULL},
	{"Reset",Car_Data_Read,Nop_Func,NULL},
};
struct MainMenu InRound_Set = {"InRound_Set",InRound_SetItems, COUNT_OF(InRound_SetItems)};

//入三岔路口数据菜单
struct SubMenu InFork_SetItems[] = 
{
	{"InFork_Inductance_M_Add",InFork_Inductance_M_Add,Nop_Func,NULL},
	{"InFork_Inductance_M_Sub",InFork_Inductance_M_Sub,Nop_Func,NULL},
	{"InFork_Inductance_L_Add",InFork_Inductance_L_Add,Nop_Func,NULL},
	{"InFork_Inductance_L_Sub",InFork_Inductance_L_Sub,Nop_Func,NULL},
	{"InFork_Inductance_R_Add",InFork_Inductance_R_Add,Nop_Func,NULL},
	{"InFork_Inductance_R_Sub",InFork_Inductance_R_Sub,Nop_Func,NULL},
	// {"AddError_left",AddError_left,Nop_Func,NULL},
	// {"AddError_right",AddError_right,Nop_Func,NULL},
	{"Fall_time_Add",Fall_time_Add,Nop_Func,NULL},
	{"Fall_time_Sub",Fall_time_Sub,Nop_Func,NULL},
	{"InFork_time_Add",InFork_time_Add,Nop_Func,NULL},
	{"InFork_time_Sub",InFork_time_Sub,Nop_Func,NULL},
	
	{"Save",Car_Data_Write,Nop_Func,NULL},
	{"Reset",Car_Data_Read,Nop_Func,NULL},
};
struct MainMenu InFork_Set = {"InFork_Set",InFork_SetItems, COUNT_OF(InFork_SetItems)};

//主页菜单
struct SubMenu Car_MenuItems[] = 
{	
	{"Turn_PID",Nop_Func,Nop_Func,&Turn_PID},
	{"Speed_PID",Nop_Func,Nop_Func,&Speed_PID},
	{"Angle_PID",Nop_Func,Nop_Func,&Angle_PID},
	{"AngleSpeed_PID",Nop_Func,Nop_Func,&AngleSpeed_PID},
	{"Car_Speed",Nop_Func,Nop_Func,&Car_Speed},
	{"InRound_Set",Nop_Func,Nop_Func,&InRound_Set},
	{"InFork_Set",Nop_Func,Nop_Func,&InFork_Set},		
	{"Round_Infor",Nop_Func,Nop_Func,&Round},	
	{"ForkRoad_Infor",Nop_Func,Nop_Func,&ForkRoad},
	{"Car_Infor",show_Enable,show_Disable,NULL},
	
};
struct MainMenu Car_mainMenu = {"Car_Setting",Car_MenuItems, COUNT_OF(Car_MenuItems)};

void Nop_Func()
{
	//nothing;
}

//按键任务
void Key_task(void)
{
	uint8 key_event;
	key_event = Key_Scan(1);	//按键扫描
	switch(key_event)
	{
		case Key1: UpFunc(); 		  break;
		case Key2: DownFunc(); 		break;
		case Key3: SelectFunc(); 	break;
		case Key4: ReturnFunc(); 	break;	
		default: break;
	}
	//SubMenu_Display(MenuItem);
}

void UpFunc(void)
{
	//取消选中当前行，背景改为黑色
	MENU_drawRectagnleFill(0, (menu_Index+1) * ITEM_H, ITEM_W, (menu_Index+2) * ITEM_H, BACK_COLOR);
	//重新显示该行信息
	MENU_DisplayStringLine(menu_Index+1, MenuItem->psItems[menu_Index].Menu_Title);
	
	//改变下标
	menu_Index--;
	if(menu_Index<0) menu_Index=MenuItem->nItems-1;
	
	//选中当前行，背景为红色
	MENU_drawRectagnleFill(0, (menu_Index+1) * ITEM_H, ITEM_W, (menu_Index+2) * ITEM_H, SELECT_COLOR);
	//显示该行信息
	MENU_DisplayStringLine(menu_Index+1, MenuItem->psItems[menu_Index].Menu_Title);
}

void DownFunc(void)
{
	//取消选中当前行，背景改为黑色
	MENU_drawRectagnleFill(0, (menu_Index+1) * ITEM_H, ITEM_W, (menu_Index+2) * ITEM_H, BACK_COLOR);
	//重新显示该行信息
	MENU_DisplayStringLine(menu_Index+1, MenuItem->psItems[menu_Index].Menu_Title);
	
	//改变下标
	menu_Index++;
	if(menu_Index>=MenuItem->nItems) menu_Index=0;
	
	//选中当前行，背景为红色
	MENU_drawRectagnleFill(0, (menu_Index+1) * ITEM_H, ITEM_W, (menu_Index+2) * ITEM_H, SELECT_COLOR);
	//显示该行信息
	MENU_DisplayStringLine(menu_Index+1, MenuItem->psItems[menu_Index].Menu_Title);
}
	

void SelectFunc(void)
{
	if(MenuItem->psItems[menu_Index].Next_Menu != NULL) //如果当前菜单有子菜单
	{
		Last_menu_Index = menu_Index;	//记录上一菜单
		Last_MenuItem = MenuItem;	//记录上一下标位置
		
		MenuItem = MenuItem->psItems[menu_Index].Next_Menu;	//MenuItem更新为子菜单
		menu_Index = 0;//下标初始为0
		
		Menu_Display(MenuItem,MenuItem->nItems);//显示菜单项目
	}
	else
	{	
		psMenuItem =MenuItem->psItems;
		psMenuItem[menu_Index].Menu_SureFunc();	//执行确定函数
	}

}

void ReturnFunc(void)
{
	if(show_flag/*||ImageShow_flag*/)
	{
		psMenuItem[menu_Index].Menu_CancelFunc();	//执行取消函数
	}
	else
	{
		menu_Index = Last_menu_Index;	//更新下标
		MenuItem = Last_MenuItem;	//返回上一菜单
	}
	Menu_Display(MenuItem,MenuItem->nItems);	//显示菜单项目
}

//菜单各项目显示
void Menu_Display(struct MainMenu *MenuItem_Show,char Str_num)	
{
	MENU_setScreenColor(BACK_COLOR);
	MENU_DisplayStringTitle(0,MenuItem_Show->Menu_Title);
	
	MENU_drawRectagnleFill(0, (menu_Index+1) * ITEM_H, ITEM_W, (menu_Index+2) * ITEM_H, SELECT_COLOR);
	for(int i=0 ; i<Str_num; i++)
	{
		MENU_DisplayStringLine(i+1,MenuItem_Show->psItems[i].Menu_Title);
	}
	SubMenu_Display(MenuItem_Show);
}

//子菜单信息数值显示
void SubMenu_Display(struct MainMenu *MenuItem_Show)
{
	if(MenuItem_Show == &Car_Speed)
	{	
		sprintf(dis_buff, "CarSpeed_Set: %3d", CarSpeed_Set);
		MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 2, dis_buff);
		sprintf(dis_buff,"Mid_Angle: %.1f  ",Mid_Angle);
		MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 3, dis_buff);
		sprintf(dis_buff,"Elec_Control: %d ",Elec_Control);
		MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 4, dis_buff);
		sprintf(dis_buff,"Stand_Enable: %d  ",Stand_Enable);
		MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 5, dis_buff);
		sprintf(dis_buff,"StartAngle: %d  ",StartAngle);
		MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 6, dis_buff);
		sprintf(dis_buff, "getball_start_flag: %3d ", getball_start_flag);
		MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 7, dis_buff);
	}
	
	else if(MenuItem_Show == &Speed_PID)
	{
		sprintf(dis_buff, "Speed_kp: %.2f ", Speed_kp);
		MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 2, dis_buff);
		sprintf(dis_buff, "Speed_ki: %.4f ", Speed_ki);
		MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 3, dis_buff);
		sprintf(dis_buff, "Speed_kd: %.2f ", Speed_kd);
		MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 4, dis_buff);
		sprintf(dis_buff, "SpeedPid_OutMax: %3d ", SpeedPid_OutMax);
		MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 5, dis_buff);
		sprintf(dis_buff, "SpeedPid_OutMin: %3d ", SpeedPid_OutMin);
		MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 6, dis_buff);
	
	}
	
	else if(MenuItem_Show == &AngleSpeed_PID)
	{
		sprintf(dis_buff, "AngleSpeed_Kp: %.2f", AngleSpeed_Kp);
		MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 2, dis_buff);
		sprintf(dis_buff, "AngleSpeed_Ki: %.2f", AngleSpeed_Ki);
		MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 3, dis_buff);
		sprintf(dis_buff, "AngleSpeed_Kd: %.2f", AngleSpeed_Kd);
		MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 4, dis_buff);
		sprintf(dis_buff, "AngleSpeedPid_OutMax: %d", AngleSpeedPid_OutMax);
		MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 5, dis_buff);
		sprintf(dis_buff, "AngleSpeedPid_OutMin: %d", AngleSpeedPid_OutMin);
		MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 6, dis_buff);
	}
	
	else if(MenuItem_Show == &Turn_PID)
	{
		sprintf(dis_buff, "Turn_Kp: %.2f", Turn_Kp);
		MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 2, dis_buff);
		sprintf(dis_buff, "InFork_TurnKd: %d", InFork_TurnKd);
		MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 3, dis_buff);
		sprintf(dis_buff, "Turn_Kd: %.2f", Turn_Kd);
		MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 4, dis_buff);
		sprintf(dis_buff, "TurnPid_OutMax: %3d ", TurnPid_OutMax);
		MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 5, dis_buff);
		sprintf(dis_buff, "TurnPid_OutMin: %3d ", TurnPid_OutMin);
		MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 6, dis_buff);
	}
	
	else if(MenuItem_Show == &InRound_Set)
	{
		sprintf(dis_buff, "InRound_Inductance_M: %d", InRound_Inductance_mid);
		MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 2, dis_buff);
		sprintf(dis_buff, "InRound_Inductance_L: %d", InRound_Inductance_left);
		MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 3, dis_buff);
		sprintf(dis_buff, "InRound_Inductance_R: %d", InRound_Inductance_right);
		MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 4, dis_buff);
		// sprintf(dis_buff, "AddError_Left: %d", AddError_Left);
		// MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 5, dis_buff);
		// sprintf(dis_buff, "AddError_Right: %d", AddError_Right);
		// MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 6, dis_buff);
	}
	
	else if(MenuItem_Show == &InFork_Set)
	{
		sprintf(dis_buff, "InFork_Inductance_M: %d", InFork_Inductance_mid);
		MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 2, dis_buff);
		sprintf(dis_buff, "InFork_Inductance_L: %d", InFork_Inductance_left);
		MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 3, dis_buff);
		sprintf(dis_buff, "InFork_Inductance_R: %d", InFork_Inductance_right);
		MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 4, dis_buff);
		// sprintf(dis_buff, "AddError_Left: %d", AddError_Left);
		// MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 5, dis_buff);
		// sprintf(dis_buff, "AddError_Right: %d", AddError_Right);
		// MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 6, dis_buff);
		sprintf(dis_buff,"Fall_time: %d  ",Fall_time);
		MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 5, dis_buff);
		sprintf(dis_buff,"InFork_time: %d  ",InFork_time);
		MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 6, dis_buff);
	}
	
	else if(MenuItem_Show == &Angle_PID)
	{
		sprintf(dis_buff, "Angle_Kp: %.2f", Angle_Kp);
		MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 2, dis_buff);
		sprintf(dis_buff, "Angle_Ki: %.2f", Angle_Ki);
		MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 3, dis_buff);
		sprintf(dis_buff, "Angle_Kd: %.2f", Angle_Kd);
		MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 4, dis_buff);
		sprintf(dis_buff, "AnglePid_OutMax: %d", AnglePid_OutMax);
		MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 5, dis_buff);
		sprintf(dis_buff, "AnglePid_OutMin: %d", AnglePid_OutMin);
		MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 6, dis_buff);
	}
	
	else if(MenuItem_Show == &Round)
	{
		sprintf(dis_buff, "InRound_Enable: %d", InRound_Enable);
		MENU_DisplayStringLine(COUNT_OF(RoundItems) + 2, dis_buff);
		if(InRound_Flag1)
		{
			sprintf(dis_buff, "InRound_Flag: 1");
			MENU_DisplayStringLine(COUNT_OF(RoundItems) + 3, dis_buff);
		}
		else if(InRound_Flag2)
		{
			sprintf(dis_buff, "InRound_Flag: 2");
			MENU_DisplayStringLine(COUNT_OF(RoundItems) + 3, dis_buff);
		}
		else if(InRound_Flag3)
		{
			sprintf(dis_buff, "InRound_Flag: 3");
			MENU_DisplayStringLine(COUNT_OF(RoundItems) + 3, dis_buff);
		}
		else if(InRound_Flag4)
		{
			sprintf(dis_buff, "InRound_Flag: 4");
			MENU_DisplayStringLine(COUNT_OF(RoundItems) + 3, dis_buff);
		}
		else
		{
			sprintf(dis_buff, "InRound_Flag: 0");
			MENU_DisplayStringLine(COUNT_OF(RoundItems) + 3, dis_buff);
		}
		sprintf(dis_buff, "InRound_ToLeft: %d", InRound_ToLeft);
		MENU_DisplayStringLine(COUNT_OF(RoundItems) + 4, dis_buff);
		sprintf(dis_buff, "InRound_ToRight: %d", InRound_ToRight);
		MENU_DisplayStringLine(COUNT_OF(RoundItems) + 5, dis_buff);
		sprintf(dis_buff, "InRound_factor: %.2f", InRound_factor);
		MENU_DisplayStringLine(COUNT_OF(RoundItems) + 6, dis_buff);
		sprintf(dis_buff, "InRound_Angle: %2d", InRound_Angle);
		MENU_DisplayStringLine(COUNT_OF(RoundItems) + 7, dis_buff);
		sprintf(dis_buff, "abandon_Round: %d", abandon_Round);
		MENU_DisplayStringLine(COUNT_OF(RoundItems) + 8, dis_buff);
		
	}
	
	else if(MenuItem_Show == &ForkRoad)
	{
		sprintf(dis_buff, "ForkRoad_Enable: %d", ForkRoad_Enable);
		MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 2, dis_buff);
		if(ForkRoad_Flag1)
		{
			sprintf(dis_buff, "ForkRoad_Flag: 1");
			MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 3, dis_buff);
		}
		else if(ForkRoad_Flag2)
		{
			sprintf(dis_buff, "ForkRoad_Flag: 2");
			MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 3, dis_buff);
		}
		else if(ForkRoad_Flag3)
		{
			sprintf(dis_buff, "ForkRoad_Flag: 3");
			MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 3, dis_buff);
		}
		else if(ForkRoad_Flag4)
		{
			sprintf(dis_buff, "ForkRoad_Flag: 4");
			MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 3, dis_buff);
		}
		else
		{
			sprintf(dis_buff, "ForkRoad_Flag: 0");
			MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 3, dis_buff);
		}
		sprintf(dis_buff, "ForkRoad_ToLeft: %d", ForkRoad_ToLeft);
		MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 4, dis_buff);
		sprintf(dis_buff, "ForkRoad_ToRight: %d", ForkRoad_ToRight);
		MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 5, dis_buff);
		sprintf(dis_buff, "InFork_Speed: %.d", InFork_Speed);
		MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 6, dis_buff);
		sprintf(dis_buff, "InFork_factor: %.2f", InFork_factor);
		MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 7, dis_buff);
		sprintf(dis_buff, "InFork_Angle: %2d", InFork_Angle);
		MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 8, dis_buff);

	}
}

//小车信息显示函数
void Information_show(void)
{
		sprintf(dis_buff, "Car_Information");
		MENU_DisplayStringTitle(0,dis_buff);
		sprintf(dis_buff, "Encoder_left: %3d ", Encoder_Left);
		MENU_DisplayStringLine(1, dis_buff);
		sprintf(dis_buff, "Encoder_right: %3d ", Encoder_Right);
		MENU_DisplayStringLine(2, dis_buff);
		sprintf(dis_buff, "CarSpeed_Now: %3d", CarSpeed_Now);
		MENU_DisplayStringLine(3, dis_buff);
		sprintf(dis_buff, "yaw: %.2f    ",gyroscope.euler.yaw);
		MENU_DisplayStringLine(4, dis_buff);
		sprintf(dis_buff, "pitch: %.2f     ",gyroscope.euler.pit);
		MENU_DisplayStringLine(5, dis_buff);
//		sprintf(dis_buff, "distance: %d  ", distance);
//		MENU_DisplayStringLine(6, dis_buff);
//		sprintf(dis_buff, "Speed_Out: %3d ", Speed_Out);
//		MENU_DisplayStringLine(7, dis_buff);
		sprintf(dis_buff, "Turn_Out: %3d ", Turn_Out);
		MENU_DisplayStringLine(8, dis_buff);
		sprintf(dis_buff, "AngleSpeed_Out: %3d ", AngleSpeed_Out);
		MENU_DisplayStringLine(9, dis_buff);
		sprintf(dis_buff, "Indutance_error: %3d ", Indutance_error);
		MENU_DisplayStringLine(10, dis_buff);
		sprintf(dis_buff, "GetBall_time: %ld ", GetBall_time);
		MENU_DisplayStringLine(11, dis_buff);
		sprintf(dis_buff, "Inductance1: %3d ", Inductance1);
		MENU_DisplayStringLine(12, dis_buff);
		sprintf(dis_buff, "Inductance2: %3d ", Inductance2);
		MENU_DisplayStringLine(13, dis_buff);
		sprintf(dis_buff, "Inductance3: %3d ", Inductance3);
		MENU_DisplayStringLine(14, dis_buff);
		sprintf(dis_buff, "Inductance4: %3d ", Inductance4);
		MENU_DisplayStringLine(15, dis_buff);
		// sprintf(dis_buff, "intro_dirve: %3d ", intro_dirve);
		// MENU_DisplayStringLine(16, dis_buff);
//		sprintf(dis_buff, "wireless_rx_buffer1: %3d ", wireless_rx_buffer[1]);
//		MENU_DisplayStringLine(17, dis_buff);
//		sprintf(dis_buff, "wireless_rx_buffer2: %3d ", wireless_rx_buffer[2]);
//		MENU_DisplayStringLine(18, dis_buff);
//		sprintf(dis_buff, "wireless_rx_buffer3: %3d ", wireless_rx_buffer[3]);
//		MENU_DisplayStringLine(19, dis_buff);
		


}

//菜单初始化
void Menu_Init(void)
{
	MenuItem = &Car_mainMenu;
	MENU_setScreenColor(BLACK);
	
	MENU_drawRectagnleFill(0, (menu_Index+1) * ITEM_H, ITEM_W, (menu_Index+2) * ITEM_H, SELECT_COLOR);
	Menu_Display(MenuItem,MenuItem->nItems);
}

void show_Enable()
{
	MENU_setScreenColor(BLACK);
	show_flag = 1;
}
void show_Disable()
{
	MENU_setScreenColor(BLACK);
	show_flag = 0;
}
void ImageShow_Enable()
{
//	MENU_setScreenColor(BLACK);
//	ImageShow_flag = 1;
}
void ImageShow_Disable()
{
//	MENU_setScreenColor(BLACK);
//	ImageShow_flag = 0;
}
void CarSpeed_Add(void)
{
	CarSpeed_Set += 5;
	sprintf(dis_buff, "CarSpeed_Set: %3d", CarSpeed_Set);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 2, dis_buff);
}
void CarSpeed_Sub(void)
{
	CarSpeed_Set -= 5;
	sprintf(dis_buff, "CarSpeed_Set: %3d", CarSpeed_Set);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 2, dis_buff);
}
void speed_kp_Add(void)
{
	Speed_kp+=0.1;
	sprintf(dis_buff, "Speed_kp: %.2f ", Speed_kp);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 2, dis_buff);
}
void speed_kp_Sub(void)
{
	Speed_kp-=0.1;
	sprintf(dis_buff, "Speed_kp: %.2f ", Speed_kp);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 2, dis_buff);
}
void speed_ki_Add(void)
{
	Speed_ki+=0.01;
	sprintf(dis_buff, "Speed_ki: %.4f ", Speed_ki);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 3, dis_buff);
}
void speed_ki_Sub(void)
{
	Speed_ki-=0.01;
	sprintf(dis_buff, "Speed_ki: %.4f ", Speed_ki);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 3, dis_buff);
}
void speed_kd_Add(void)
{
	Speed_kd+=0.1;
	sprintf(dis_buff, "Speed_kd: %.2f ", Speed_kd);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 4, dis_buff);
}
void speed_kd_Sub(void)
{
	Speed_kd-=0.1;
	sprintf(dis_buff, "Speed_kd: %.2f ", Speed_kd);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 4, dis_buff);
}
void SpeedPid_OutMax_Add(void)
{
	SpeedPid_OutMax+=2;
	sprintf(dis_buff, "SpeedPid_OutMax: %3d ", SpeedPid_OutMax);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 5, dis_buff);
}
void SpeedPid_OutMax_Sub(void)
{
	SpeedPid_OutMax-=2;
	sprintf(dis_buff, "SpeedPid_OutMax: %3d ", SpeedPid_OutMax);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 5, dis_buff);
}
void SpeedPid_OutMin_Add(void)
{
	SpeedPid_OutMin+=2;
	sprintf(dis_buff, "SpeedPid_OutMin: %3d ", SpeedPid_OutMin);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 6, dis_buff);
}
void SpeedPid_OutMin_Sub(void)
{
	SpeedPid_OutMin-=2;
	sprintf(dis_buff, "SpeedPid_OutMin: %3d ", SpeedPid_OutMin);
	MENU_DisplayStringLine(COUNT_OF(SpeedPidItems) + 6, dis_buff);
}

void AngleSpeed_kp_Add(void)
{
	AngleSpeed_Kp+=1;
	sprintf(dis_buff, "AngleSpeed_Kp: %.2f", AngleSpeed_Kp);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 2, dis_buff);
}
void AngleSpeed_kp_Sub(void)
{
	AngleSpeed_Kp-=1;
	sprintf(dis_buff, "AngleSpeed_Kp: %.2f", AngleSpeed_Kp);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 2, dis_buff);
}
void AngleSpeed_ki_Add(void)
{
	AngleSpeed_Ki+=0.01;
	sprintf(dis_buff, "AngleSpeed_Ki: %.2f", AngleSpeed_Ki);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 3, dis_buff);
}
void AngleSpeed_ki_Sub(void)
{
	AngleSpeed_Ki-=0.01;
	sprintf(dis_buff, "AngleSpeed_Ki: %.2f", AngleSpeed_Ki);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 3, dis_buff);
}
void AngleSpeed_kd_Add(void)
{
	AngleSpeed_Kd+=0.1;
	sprintf(dis_buff, "AngleSpeed_Kd: %.2f", AngleSpeed_Kd);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 4, dis_buff);
}
void AngleSpeed_kd_Sub(void)
{
	AngleSpeed_Kd-=0.1;
	sprintf(dis_buff, "AngleSpeed_Kd: %.2f", AngleSpeed_Kd);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 4, dis_buff);
}
void AngleSpeedPid_OutMax_Add(void)
{
	AngleSpeedPid_OutMax+=1000;
	sprintf(dis_buff, "AngleSpeedPid_OutMax: %d", AngleSpeedPid_OutMax);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 5, dis_buff);
}
void AngleSpeedPid_OutMax_Sub(void)
{
	AngleSpeedPid_OutMax-=1000;
	sprintf(dis_buff, "AngleSpeedPid_OutMax: %d", AngleSpeedPid_OutMax);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 5, dis_buff);
}
void AngleSpeedPid_OutMin_Add(void)
{
	AngleSpeedPid_OutMin+=1000;
	sprintf(dis_buff, "AngleSpeedPid_OutMin: %d", AngleSpeedPid_OutMin);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 6, dis_buff);
}
void AngleSpeedPid_OutMin_Sub(void)
{
	AngleSpeedPid_OutMin-=1000;
	sprintf(dis_buff, "AngleSpeedPid_OutMin: %d", AngleSpeedPid_OutMin);
	MENU_DisplayStringLine(COUNT_OF(AngleSpeedPidItems) + 6, dis_buff);
}
void Turn_kp_Add(void)
{
	Turn_Kp+=10;
	sprintf(dis_buff, "Turn_Kp: %.2f", Turn_Kp);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 2, dis_buff);
}
void Turn_kp_Sub(void)
{
	Turn_Kp-=10;
	sprintf(dis_buff, "Turn_Kp: %.2f", Turn_Kp);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 2, dis_buff);
}
void InFork_TurnKd_Add(void)
{
	InFork_TurnKd+=500;
	sprintf(dis_buff, "InFork_TurnKd: %d", InFork_TurnKd);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 3, dis_buff);
}
void InFork_TurnKd_Sub(void)
{
	InFork_TurnKd-=500;
	sprintf(dis_buff, "InFork_TurnKd: %d", InFork_TurnKd);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 3, dis_buff);
}
void Turn_kd_Add(void)
{
	Turn_Kd+=100;
	sprintf(dis_buff, "Turn_Kd: %.2f", Turn_Kd);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 4, dis_buff);
}
void Turn_kd_Sub(void)
{
	Turn_Kd-=100;
	sprintf(dis_buff, "Turn_Kd: %.2f", Turn_Kd);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 4, dis_buff);
}

void Turn_OutMax_Add(void)
{
	TurnPid_OutMax+=500;
	sprintf(dis_buff, "TurnPid_OutMax: %3d ", TurnPid_OutMax);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 5, dis_buff);
}
void Turn_OutMax_Sub(void)
{
	TurnPid_OutMax-=500;
	sprintf(dis_buff, "TurnPid_OutMax: %3d ", TurnPid_OutMax);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 5, dis_buff);
}
void Turn_OutMin_Add(void)
{
	TurnPid_OutMin+=500;
	sprintf(dis_buff, "TurnPid_OutMin: %3d ", TurnPid_OutMin);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 6, dis_buff);
}
void Turn_OutMin_Sub(void)
{
	TurnPid_OutMin-=500;
	sprintf(dis_buff, "TurnPid_OutMin: %3d ", TurnPid_OutMin);
	MENU_DisplayStringLine(COUNT_OF(TurnPidItems) + 6, dis_buff);
}
void Angle_kp_Add(void)
{
	Angle_Kp+=10;
	sprintf(dis_buff, "Angle_Kp: %.2f", Angle_Kp);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 2, dis_buff);
}
void Angle_kp_Sub(void)
{
	Angle_Kp-=10;
	sprintf(dis_buff, "Angle_Kp: %.2f", Angle_Kp);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 2, dis_buff);
}
void Angle_ki_Add(void)
{
	Angle_Ki+=0.01;
	sprintf(dis_buff, "Angle_Ki: %.2f", Angle_Ki);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 3, dis_buff);
}
void Angle_ki_Sub(void)
{
	Angle_Ki-=0.01;
	sprintf(dis_buff, "Angle_Ki: %.2f", Angle_Ki);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 3, dis_buff);
}
void Angle_kd_Add(void)
{
	Angle_Kd+=0.1;
	sprintf(dis_buff, "Angle_Kd: %.2f", Angle_Kd);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 4, dis_buff);
}
void Angle_kd_Sub(void)
{
	Angle_Kd-=0.1;
	sprintf(dis_buff, "Angle_Kd: %.2f", Angle_Kd);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 4, dis_buff);
}
void Mid_Angle_Add(void)
{
	Mid_Angle+=0.5;
	sprintf(dis_buff,"Mid_Angle: %.1f  ",Mid_Angle);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 3, dis_buff);
}
void Mid_Angle_Sub(void)
{
	Mid_Angle-=0.5;
	sprintf(dis_buff,"Mid_Angle: %.1f  ",Mid_Angle);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 3, dis_buff);
}
void AnglePid_OutMax_Add(void)
{
	AnglePid_OutMax+=100;
	sprintf(dis_buff, "AnglePid_OutMax: %d", AnglePid_OutMax);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 5, dis_buff);
}
void AnglePid_OutMax_Sub(void)
{
	AnglePid_OutMax-=100;
	sprintf(dis_buff, "AnglePid_OutMax: %d", AnglePid_OutMax);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 5, dis_buff);
}
void AnglePid_OutMin_Add(void)
{
	AnglePid_OutMin+=100;
	sprintf(dis_buff, "AnglePid_OutMin: %d", AnglePid_OutMin);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 6, dis_buff);
}
void AnglePid_OutMin_Sub(void)
{
	AnglePid_OutMin-=100;
	sprintf(dis_buff, "AnglePid_OutMin: %d", AnglePid_OutMin);
	MENU_DisplayStringLine(COUNT_OF(AnglePidItems) + 6, dis_buff);
}

void Follow_Mode()
{
	Elec_Control=!Elec_Control;
	Turn_Out = 0;
	sprintf(dis_buff,"Elec_Control: %d ",Elec_Control);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 4, dis_buff);
}
void Stand_Mode()
{
	Stand_Enable=!Stand_Enable;
	AngleSpeed_Out = 0;
	sprintf(dis_buff,"Stand_Enable: %d  ",Stand_Enable);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 5, dis_buff);
}
void getball_flag()
{
	getball_start_flag = !getball_start_flag;
	sprintf(dis_buff, "getball_start_flag: %3d ", getball_start_flag);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 7, dis_buff);
}

void Transmit_buff()
{
	seekfree_wireless_send_buff(Tx_buff,sizeof(uint8)*4);
	uart_putbuff(Blueteeth_UART, Tx_buff, sizeof(uint8)*4);
}
void StartAngle_Add(void)
{
	StartAngle+=2;
	sprintf(dis_buff,"StartAngle: %d  ",StartAngle);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 6, dis_buff);
	
}
void StartAngle_Sub(void)
{
	StartAngle-=2;
	sprintf(dis_buff,"StartAngle: %d  ",StartAngle);
	MENU_DisplayStringLine(COUNT_OF(CarspeedItems) + 6, dis_buff);
}

void Is_abandon_Round()
{
	abandon_Round = !abandon_Round;
	sprintf(dis_buff, "abandon_Round: %d", abandon_Round);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 8, dis_buff);
}

void Round_Reset()
{
	InRound_Enable = 1;
	InRound_Flag1 = 1;
	InRound_Flag2 = 0;
	InRound_Flag3 = 0;
	InRound_Flag4 = 0;
	
	AddError_Right = 0;
	AddError_Left = 0;
	
	Elec_Control = 1;
	sprintf(dis_buff, "InRound_Enable: %d", InRound_Enable);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 2, dis_buff);

	sprintf(dis_buff, "InRound_Flag: 1");
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 3, dis_buff);

}

void AddError_left()
{
	AddError_Left = !AddError_Left;
	sprintf(dis_buff, "AddError_Left: %d", AddError_Left);
	MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 5, dis_buff);
		
}
void AddError_right()
{
	AddError_Right = !AddError_Right;
	sprintf(dis_buff, "AddError_Right: %d", AddError_Right);
	MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 6, dis_buff);
}

void InRound_Enable_Set()
{
	InRound_Enable=!InRound_Enable;
	sprintf(dis_buff, "InRound_Enable: %d", InRound_Enable);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 2, dis_buff);
}


void ForkRoad_Reset()
{
	ForkRoad_Enable = 1;
	ForkRoad_Flag1 = 1;
	ForkRoad_Flag2 = 0;
	ForkRoad_Flag3 = 0;
	ForkRoad_Flag4 = 0;
	AddError_Right = 0;
	AddError_Left = 0;

	sprintf(dis_buff, "ForkRoad_Enable: %d", ForkRoad_Enable);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 2, dis_buff);

	sprintf(dis_buff, "ForkRoad_Flag: 1");
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 3, dis_buff);


}

void ForkRoad_Enable_Set()
{
	ForkRoad_Enable=!ForkRoad_Enable;
	sprintf(dis_buff, "ForkRoad_Enable: %d", ForkRoad_Enable);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 2, dis_buff);
}
void InFork_factor_Add()
{
	InFork_factor += 0.1;
	sprintf(dis_buff, "InFork_factor: %.2f", InFork_factor);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 7, dis_buff);
}
void InFork_factor_Sub()
{
	InFork_factor -= 0.1;
	sprintf(dis_buff, "InFork_factor: %.2f", InFork_factor);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 7, dis_buff);
}

void Round_L()
{
	InRound_ToLeft = 1;
	InRound_ToRight = 0;
	sprintf(dis_buff, "InRound_ToLeft: %d", InRound_ToLeft);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 4, dis_buff);
	sprintf(dis_buff, "InRound_ToRight: %d", InRound_ToRight);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 5, dis_buff);
}
void Round_R()
{
	InRound_ToRight = 1;
	InRound_ToLeft = 0;
	sprintf(dis_buff, "InRound_ToLeft: %d", InRound_ToLeft);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 4, dis_buff);
	sprintf(dis_buff, "InRound_ToRight: %d", InRound_ToRight);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 5, dis_buff);
}
void InRound_factor_Add()
{
	InRound_factor+=0.1;
	sprintf(dis_buff, "InRound_factor: %.2f", InRound_factor);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 6, dis_buff);
}
void InRound_factor_Sub()
{
	InRound_factor-=0.1;
	sprintf(dis_buff, "InRound_factor: %.2f", InRound_factor);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 6, dis_buff);
}
void ForkRoad_L()
{
	ForkRoad_ToLeft = 1;
	ForkRoad_ToRight = 0;
	sprintf(dis_buff, "ForkRoad_ToLeft: %d", ForkRoad_ToLeft);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 4, dis_buff);
	sprintf(dis_buff, "ForkRoad_ToRight: %d", ForkRoad_ToRight);	
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 5, dis_buff);
}
void ForkRoad_R()
{
	ForkRoad_ToRight = 1;
	ForkRoad_ToLeft = 0;
	sprintf(dis_buff, "ForkRoad_ToLeft: %d", ForkRoad_ToLeft);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 4, dis_buff);
	sprintf(dis_buff, "ForkRoad_ToRight: %d", ForkRoad_ToRight);	
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 5, dis_buff);
}

void Fall_time_Add()
{
	Fall_time+=5;
	sprintf(dis_buff,"Fall_time: %d  ",Fall_time);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 5, dis_buff);
}
void Fall_time_Sub()
{
	Fall_time-=5;
	sprintf(dis_buff,"Fall_time: %d  ",Fall_time);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 5, dis_buff);
}
void InFork_speed_Add()
{
	InFork_Speed+=5;
	sprintf(dis_buff, "InFork_Speed: %.d", InFork_Speed);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 6, dis_buff);
}
void InFork_speed_Sub()
{
	InFork_Speed-=5;
	sprintf(dis_buff, "InFork_Speed: %.d", InFork_Speed);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 6, dis_buff);
}

void InRound_Inductance_M_Add()
{
	InRound_Inductance_mid+=50;
	sprintf(dis_buff, "InRound_Inductance_M: %d", InRound_Inductance_mid);
	MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 2, dis_buff);
}
void InRound_Inductance_M_Sub()
{
	InRound_Inductance_mid-=50;
	sprintf(dis_buff, "InRound_Inductance_M: %d", InRound_Inductance_mid);
	MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 2, dis_buff);
}
void InRound_Inductance_L_Add()
{
	InRound_Inductance_left+=50;
	sprintf(dis_buff, "InRound_Inductance_L: %d", InRound_Inductance_left);
	MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 3, dis_buff);
}
void InRound_Inductance_L_Sub()
{
	InRound_Inductance_left-=50;
	sprintf(dis_buff, "InRound_Inductance_L: %d", InRound_Inductance_left);
	MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 3, dis_buff);
}
void InRound_Inductance_R_Add()
{
	InRound_Inductance_right+=50;
	sprintf(dis_buff, "InRound_Inductance_R: %d", InRound_Inductance_right);
	MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 4, dis_buff);
}
void InRound_Inductance_R_Sub()
{
	InRound_Inductance_right-=50;
	sprintf(dis_buff, "InRound_Inductance_R: %d", InRound_Inductance_right);
	MENU_DisplayStringLine(COUNT_OF(InRound_SetItems) + 4, dis_buff);
}
void InRound_Angle_Add()
{
	InRound_Angle+=5;
	sprintf(dis_buff, "InRound_Angle: %2d", InRound_Angle);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 7, dis_buff);

}
void InRound_Angle_Sub()
{
	InRound_Angle-=5;
	sprintf(dis_buff, "InRound_Angle: %2d", InRound_Angle);
	MENU_DisplayStringLine(COUNT_OF(RoundItems) + 7, dis_buff);
}

void InFork_Angle_Add()
{
	InFork_Angle+=5;
	sprintf(dis_buff, "InFork_Angle: %2d", InFork_Angle);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 8, dis_buff);
}
void InFork_Angle_Sub()
{
	InFork_Angle-=5;
	sprintf(dis_buff, "InFork_Angle: %2d", InFork_Angle);
	MENU_DisplayStringLine(COUNT_OF(ForkRoadItems) + 8, dis_buff);
}
void InFork_Inductance_M_Add()
{
	InFork_Inductance_mid+=50;
	sprintf(dis_buff, "InFork_Inductance_M: %d", InFork_Inductance_mid);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 2, dis_buff);
}
void InFork_Inductance_M_Sub()
{
	InFork_Inductance_mid-=50;
	sprintf(dis_buff, "InFork_Inductance_M: %d", InFork_Inductance_mid);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 2, dis_buff);
}
void InFork_Inductance_L_Add()
{
	InFork_Inductance_left+=50;
	sprintf(dis_buff, "InFork_Inductance_L: %d", InFork_Inductance_left);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 3, dis_buff);
}
void InFork_Inductance_L_Sub()
{
	InFork_Inductance_left-=50;
	sprintf(dis_buff, "InFork_Inductance_L: %d", InFork_Inductance_left);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 3, dis_buff);
}
void InFork_Inductance_R_Add()
{
	InFork_Inductance_right+=50;
	sprintf(dis_buff, "InFork_Inductance_R: %d", InFork_Inductance_right);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 4, dis_buff);
}
void InFork_Inductance_R_Sub()
{
	InFork_Inductance_right-=50;
	sprintf(dis_buff, "InFork_Inductance_R: %d", InFork_Inductance_right);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 4, dis_buff);
}

void InFork_time_Add()
{
	InFork_time+=10;
	sprintf(dis_buff,"InFork_time: %d  ",InFork_time);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 6, dis_buff);
}
void InFork_time_Sub()
{
	InFork_time-=10;
	sprintf(dis_buff,"InFork_time: %d  ",InFork_time);
	MENU_DisplayStringLine(COUNT_OF(InFork_SetItems) + 6, dis_buff);
}