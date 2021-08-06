//#include "Car_Image.h"
//#include "Car_Task.h"
//#include "Car_control.h"
//#include <stdio.h>
//#include "menu_display.h"
//#include "menu_core.h"

//#define ERROR 2

//float Threshold = 130; //迭代阈值
//int16 EdgeThres = 17;  //跳变沿阈值
//uint8 CAR_IMAGE[CAR_IMAGE_High][CAR_IMAGE_Width];  //摄像头图像二维数组

//int Center[CAR_IMAGE_High];   	//中心线数组
//int left_line[CAR_IMAGE_High];	//左边界数组
//int right_line[CAR_IMAGE_High];	//右边界数组
//int street_width[CAR_IMAGE_High];//	赛道宽度数组

//int street_len;//赛道长度
//int Left_Lost_Num[10];
//int Right_Lost_Num[10];

//int time=0;
//char disbuff[50];
//int boder_line;
//float mid_factor = 0.5;

//int CenterFind = 50; 	//中心线查找位置
//int Center_line = 0;   //中心线

////各阶段使能
//bool Out_Garage_Enable = 1;
//bool In_Garage_Enable = 1;
//bool In_Round_Enable = 0;

////选择出库左转右转
//bool out_left = 0;
//bool out_right = 1;

////入库标志位
//bool In_Garage_Flag = 0;
//bool In_Garage_OK_Flag = 0;

////出库标志位
//bool Out_Garage_Flag1 = 1;
//bool Out_Garage_Flag2 = 0;
//bool Out_Garage_Flag3 = 0;


////边界找到标志位
//bool RightBoder_Find_Flag= 0;
//bool LeftBoder_Find_Flag = 0;

////左右丢线数量
//int RightBoder_Lost_Num = 0;
//int LeftBoder_Lost_Num = 0;

////左圆环标志位
//bool LeftRound_Flag0 = 1;
//bool LeftRound_Flag1 = 0;
//bool LeftRound_Flag2 = 0;
//bool LeftRound_Flag3 = 0;
//bool LeftRound_Flag4 = 0;
//bool LeftRound_Flag5 = 0;

////右圆环标志位
//bool RightRound_Flag0 = 1;
//bool RightRound_Flag1 = 0;
//bool RightRound_Flag2 = 0;
//bool RightRound_Flag3 = 0;
//bool RightRound_Flag4 = 0;
//bool RightRound_Flag5 = 0;

////左右补线标志位
//bool AddLine_left = 0;
//bool AddLine_right = 0;

////结束标志位
//bool Over_Flag = 0;

//bool ImageShow_flag = 0;
//int Black_Piont_one = 0,Black_Point_two = 0,Black_Point_three = 0;
//int White_Piont_one = 0,White_Point_two = 0;

//int Left_Black_Piont = 0; //左边界黑点数量
//int Right_Black_Piont = 0;//右边界黑点数量

//int White_Point = 0;	//白点数量
//int Black_Point = 0;	//黑点数量

//bool first_Flag = 1;	
//bool second_Flag = 0;
//bool third_Flag = 0;
//bool fourth_Flag = 0;
//bool fifth_Flag = 0;
//	

////void CarImage_Duty(void)
////{
////	CAR_IMAGE_Get();
////	Get_Threshold();
//////	Image_Threshold(Threshold,CAR_IMAGE_Width,CAR_IMAGE_High);
//////	Round_Addlight();
////	Find_Boder();
////	BlackPoint_Count();
////	
//////	if(Out_Garage_Enable) Out_Garage_Check();
//////	if(In_Garage_Enable) In_Garage_Check();
//////	if(In_Round_Enable) 
//////	{
//////		if(out_right) Right_Round_Check();
//////		if(out_left) Left_Round_Check();
//////	}
////	if(ForkRoad_Enable) Tri_Check();
////	street_duty();
////	if(ImageShow_flag)
////	{
////		Show_CAR_IMAGE_Info();
////	}
////}

////void Image_Threshold(int threshold,uint16 width, uint16 height)  //二值化处理
////{	
////		
////	uint16 i,j;
////	for(i=0;i<CAR_IMAGE_Width;i++)
////	{
////		for(j=0;j<CAR_IMAGE_High;j++)
////		{
////			if(CAR_IMAGE[j][i]<threshold) CAR_IMAGE[j][i] = 0;
////			else CAR_IMAGE[j][i] = 255;
////		}
////	}
////	
////}

////void Find_Boder(void)//查找边界与中线
////{
////	uint16 i,j,sum = 0,num=0;
////	
////	for(i=Fine_Line_Down; i>Find_Line_Up; i--)
////	{
////		RightBoder_Find_Flag = 0;
////		LeftBoder_Find_Flag = 0;
////		//查找右边界
////		for(j = CenterFind; j<99 && j>=0; j++)  
////		{
////			if(CAR_IMAGE[i][j] <Threshold && CAR_IMAGE[i][j-1] -CAR_IMAGE[i][j+1]>EdgeThres && CAR_IMAGE[i][j-2]-CAR_IMAGE[i][j+2]>EdgeThres)
////			{
////				RightBoder_Find_Flag = 1;		
////				right_line[i] = j;
////				break;
////			}
////		}
////		if(!RightBoder_Find_Flag) 
////		{
////			right_line[i] = 100;
////		}		
////		
////		//查找左边界
////		for(j = CenterFind; j<99 && j>=1; j--)	
////		{			
////			if(CAR_IMAGE[i][j] <Threshold && CAR_IMAGE[i][j+1] -CAR_IMAGE[i][j-1]>EdgeThres && CAR_IMAGE[i][j+2]-CAR_IMAGE[i][j-2]>EdgeThres)
////			{
////				LeftBoder_Find_Flag = 1;
////				left_line[i] = j;
////				break;
////			}
////		}	
////		if(!LeftBoder_Find_Flag) 
////		{
////			left_line[i] = 0;
////		}
////		street_width[i] = right_line[i] - left_line[i];
////		Center[i] = (left_line[i]+right_line[i])/2;
////		//if(abs(Center[i]-Center[i+1])>10)	Center[i]=Center[i+1];
////		Round_AddMidlight(i);
////		num++;
////		sum+=Center[i];	

////		CenterFind = Center[i];
////		if(Center[i]>80&&Center[i]<20)
////			CenterFind = 50;		

////	}
////	//计算中心线
//// 	Center_line = sum/num;
////}

////void CAR_IMAGE_Get(void)	//获取摄像头图像数组
////{
////    uint8 i, j;
////	
////    for (i = 0; i < CAR_IMAGE_High; i++)
////    {
////        for (j = 0; j < CAR_IMAGE_Width; j++)
////        {
////            CAR_IMAGE[i][j] = mt9v03x_image[i][j*2];
////        }
////    }
////	
////}

////void In_Garage_Check(void)	//入库检测                             
////{
////	boder_line = 0;
////	White_Piont_one = 0;
////	White_Point_two = 0;
////	Black_Point = 0;
////	int Check_line = 62;
////	for(int i = 0;i<99; i++)
////	{
////		if(CAR_IMAGE[Check_line][i]>Threshold) White_Piont_one++;
////		else Black_Point++;
////		
////		if(CAR_IMAGE[Check_line-7][i]>Threshold) White_Point_two++;
////		if(CAR_IMAGE[Check_line][i] != CAR_IMAGE[Check_line][i+1])
////			boder_line++;
////	}
////	if(Black_Point>50&&White_Piont_one>37 &&boder_line>8&&White_Point_two>35)
////		In_Garage_Flag = 1;
////	
////	else In_Garage_Flag = 0;
//////	if(In_Garage_Flag)
//////	{
//////		if(CAR_IMAGE[75][1] == 255 && CAR_IMAGE[75][2] == 255 && CAR_IMAGE[75][3] == 255)  //左入库检测
//////		{
//////			In_GarageLeft_Flag = 1;
//////		}
//////		else In_GarageLeft_Flag = 0;

//////		if(CAR_IMAGE[70][195] == 255 && CAR_IMAGE[70][196] == 255 && CAR_IMAGE[70][197] == 255)	//右入库检测
//////		{
//////			In_GarageRight_Flag = 1;
//////		}
//////		else In_GarageRight_Flag = 0;
//////	}
//// 	if(In_Garage_Flag /*&&(In_GarageRight_Flag ||In_GarageLeft_Flag)&&(!Over_Flag)*/)
//// 	{
//// 		Beep_Start();
////// 		ServoPid_Enable = 0;
//// 		In_Garage_Flag = 0;
////// 		if(out_right) Turn_Right();	
////// 		if(out_left ) Turn_Left();
////		pwm_duty_updata(PWM_TIM,MotorB_1,4000);
////		pwm_duty_updata(PWM_TIM,MotorB_2,0);
//// 		systick_delay_ms(580);

////		In_Garage_OK_Flag = 1;
////		In_Garage_Enable = 0;
//// 	}
////}

////void Out_Garage_Check(void)	//出库检测
////{
////	int i,j,num=0;
////	if(Out_Garage_Flag1)
////	{
////		Set_PWM(15000,15000);
////		for(i=0; i<100; i++)
////		{
////			if(CAR_IMAGE[50][i]<Threshold) num++;
////			
////		}
////		if(num>60) 
////			{
////				Beep_Start();
////				Out_Garage_Flag2 = 1;
//////				time = tnow;
////				num = 0;
////			}		
////	}
////	if(Out_Garage_Flag2)
////	{
////		Out_Garage_Flag1 = 0;
//////		if(out_right) Turn_Right();
//////		else if(out_left) Turn_Left();
////		Black_Point = 0;
////		for(i=35; i<70; i++)
////		{
////			if(CAR_IMAGE[i][50]<Threshold) Black_Point++;	
////		}
////		if(!Black_Point) Out_Garage_Flag3 =1;
////	}
////	
////	if(Out_Garage_Flag3)
////	{
////		Out_Garage_Flag2 = 0;
//////		ServoPid_Enable = 1;
//////		SpeedPid_Enable = 1;
////		Out_Garage_Flag3 = 0;
////		Out_Garage_Enable = 0;
////		In_Round_Enable = 1;
////		In_Garage_Enable = 1;
////		
////	}
////}

////void street_duty(void) //赛道直道长度测量
////{
////    /*中线直道长度测量*/
////		int img_y;
////    for (img_y = 30; img_y >= 1; img_y--)
////    {
////        if (CAR_IMAGE[img_y][47] < Threshold && CAR_IMAGE[img_y - 1][47] < Threshold)
////            break;
////    }
////    street_len = 69 - img_y;
////}

////void Get_Threshold(void)	//迭代求阈值
////{
////    /*迭代出最佳阈值*/
////    uint32 i = 0, j = 0, N0 = 0, N1 = 0, flag = 0;
////    float T0, T1, T2, T_center;
////    uint32 S0 = 0, S1 = 0;
////    /*迭代出最佳阈值*/
////    T2 = Threshold;
////    do
////    {
////        for (i = 0; i < CAR_IMAGE_High - 1; i++)
////        {
////            for (j = 0; j < CAR_IMAGE_Width - 1; j++)
////            {
////                if (CAR_IMAGE[i][j] > Threshold) //前景灰度值
////                {
////                    S0 += CAR_IMAGE[i][j];
////                    N0++;
////                }
////                else //背景灰度值
////                {
////                    S1 += CAR_IMAGE[i][j];
////                    N1++;
////                }
////            }
////        }

////        if (N0 != 0 && N1 != 0)
////        {
////            T0 = S0 / N0;
////            T1 = S1 / N1;
////            T_center = (T0 + T1) / 2;
////        }

////        if (T2 < T_center)
////        {
////            if ((T_center - T2) > ERROR)
////            {
////                flag = 1;
////            }
////            else
////            {
////                flag = 0;
////            }
////        }
////        else
////        {
////            if ((T2 - T_center) > ERROR)
////            {
////                flag = 1;
////            }
////            else
////            {
////                flag = 0;
////            }
////        }
////        T2 = T_center;
////        Threshold = (int)T2;
////        S0 = N0 = S1 = N1 = 0;
////    } while (flag);
////}

////int Left_Round_Check(void)
////{
////	return 0 ;
////}

////int Right_Round_Check(void)  //环岛检测
////{
////	return 0 ;
////}

////int linear_equation(int x1,int y1, int x2, int y2, int x0) //两点间直线方程
////{
////	int k,b;
////	int y0;
////	if(x1-x2==0)
////		return x1;
////	k = (y1 - y2)/(x1 - x2);
////	b = y1 - k*x1;
////	
////	y0 = k*x0 + b;
////	return y0;
////}

////int createPoint(int type ,int line)
////{
////	int *linePointer;
////	int8 tmp = 0;
////	double sumX = 0;
////	double sumY = 0;
////	double averageX = 0;
////	double averageY = 0;
////	double sumUp = 0;
////	double sumDown = 0;
////	double parameterA;
////	double parameterB;
////	
////	if(type == FIND_LEFT)
////		linePointer = &left_line[line];
////	else if(type == FIND_RIGHT)
////		linePointer = &right_line[line];
////	else
////		linePointer = &Center[line];
////	
////	// 取邻近的 POINT_COUNT 个点进行拟合
////	while(++tmp <= 15)
////	{
////		sumX += (line+tmp);
////		sumY += linePointer[tmp];
////	}
////	--tmp;
////	averageX = sumX/tmp;
////	averageY = sumY/tmp;
////	do
////	{
////		sumUp += (linePointer[tmp]-averageY) * (line+tmp-averageX);
////		sumDown += (line+tmp-averageX) * (line+tmp-averageX);
////	} while(--tmp > 0);
////	
////	if(sumDown == 0)
////		parameterB = 0;
////	else
////		parameterB = sumUp/sumDown;
////	parameterA = averageY-parameterB*averageX;
////	return (int16)(parameterA+parameterB*line+0.5);
////}

////void Draw_Height(void)
////{
////	int i;
////	for(i = 0 ; i<=70 ;i+=30)
////	{
////		ips200_drawpoint(220,i,YELLOW);
////		ips200_drawpoint(220,i+10,PINK);
////		ips200_drawpoint(220,i+20,PURPLE);
////	}
////}

////void Show_CAR_IMAGE_Info(void)
////{
////		ips200_displayimage032(CAR_IMAGE[0], CAR_IMAGE_Width, CAR_IMAGE_High);
////		for(int i=Fine_Line_Down; i>Find_Line_Up; i--)
////		{
////			ips200_drawpoint((int)left_line[i],i,RED);
////			ips200_drawpoint((int)right_line[i],i,GREEN);
////			ips200_drawpoint((int)Center[i],i,BLUE);
////		}
////		//Draw_Height();
////		sprintf(disbuff, "Center_line: %d", Center_line);
////		MENU_DisplayStringLine(71, disbuff);
////		sprintf(disbuff, "street_len: %3d", street_len);
////		MENU_DisplayStringLine(72, disbuff);
////		sprintf(disbuff, "Left_Black_Piont: %3d", Left_Black_Piont);
////		MENU_DisplayStringLine(73, disbuff);
////		sprintf(disbuff, "Right_Black_Piont: %3d", Right_Black_Piont);
////		MENU_DisplayStringLine(74, disbuff);
////		sprintf(disbuff, "street_width[69]: %3d", street_width[69]);
////		MENU_DisplayStringLine(75, disbuff);
////		sprintf(disbuff, "street_width[60]: %3d", street_width[60]);
////		MENU_DisplayStringLine(76, disbuff);
////		sprintf(disbuff, "street_width[50]: %3d", street_width[50]);
////		MENU_DisplayStringLine(77, disbuff);
////		sprintf(disbuff, "street_width[40]: %3d", street_width[41]);
////		MENU_DisplayStringLine(78, disbuff);

////}	


////void Round_Addlight(void)
////{
////	uint16 i,j;
////	//右环岛补线			
////	if(AddLine_right)  
////	{
////		
////		int Width=0;
////		int number;
////		static int Height=10;

////		//找到最少黑点的一行
////		for(i=0;i<50;i++)
////		{
////			number = 0;
////			for( j=50;j<100;j++)
////			{
////				if(CAR_IMAGE[i][j] < Threshold) number = 1;	
////			}
////			if(!number)
////			{
////				Height = i-1;
////				break;
////			}
////		}
////		
////		if(Height)
////		{
////			Black_Point = 0;
////			Width=0;
////			for( j=40; j<100; j++)
////			{
////				if(CAR_IMAGE[Height][j] < Threshold)
////				{
////					Black_Point++;
////					Width+=j;
////				}
////			}
////		}
////		for(int i=Height;i<Height+20;i++)
////		{	
////			int temp=0;
////			if(Black_Point)
////			{
////				temp= linear_equation(Height+20,0,Height,Width/Black_Point,i);
////			}
////			if(temp<=0) temp = 0;			
////			CAR_IMAGE[i][temp] = 0;			
////			CAR_IMAGE[i][temp-1] = 0;
////			CAR_IMAGE[i][temp+1] = 0;
////		}
////	}
////	
////	//左环岛补线
////	if(AddLine_left)
////	{
////		int Width=0;
////		int number;
////		static int Height=10;

////		for(i=0;i<50;i++)
////		{
////			number = 0;
////			
////			for( j=50;j>0;j--)
////			{
////				if(CAR_IMAGE[i][j] < Threshold) number = 1;	
////			}
////			if(!number)
////			{
////				Height = i-1;
////				break;
////			}

////		}
////		if(Height)
////		{
////			Black_Point = 0;
////			Width=0;
////			for( j=60; j>0; j--)
////			{
////				if(CAR_IMAGE[Height][j] < Threshold)
////				{
////					Black_Point++;
////					Width+=j;
////				}
////			}
////		}
////		for(int i=Height;i<Height+20;i++)
////		{	
////			int temp=0;
////			if(Black_Point)
////			{
////				temp= linear_equation(Height+20,100,Height,Width/Black_Point,i);
////			}
////			if(temp<=0) temp = 0;			
////			CAR_IMAGE[i][temp] = 0;			
////			CAR_IMAGE[i][temp-1] = 0;
////			CAR_IMAGE[i][temp+1] = 0;
////		}
////	}
////}

////int MidLine_Acc(int i)
////{
////	if(i>=60&&i<70)
////	{
////		return i-20;
////	}
////	else if(i>=40 && i<60)
////	{
////		return i*0.75-5;
////	}
////	
////	else 
////		return 0;
////}
////void Round_AddMidlight(int height)
////{
////	if(AddLine_left)
////	{
////		//for(int i = Find_Line_Up; i<Fine_Line_Down; i++)
////		{
////			Center[height] = left_line[height] + MidLine_Acc(height) * mid_factor;
////		}
////	}
////	
////	if(AddLine_right)
////	{
////		//for(int i = Find_Line_Up; i<Fine_Line_Down; i++)
////		{
////			Center[height] = right_line[height] - MidLine_Acc(height) * mid_factor;
////		}
////	}
////	
////}



////void BlackPoint_Count(void)
////{
////	Left_Black_Piont = 0;
////	Right_Black_Piont = 0;
////	for(int i=0; i<70; i++)
////	{
////		if(CAR_IMAGE[i][5] < Threshold) Left_Black_Piont++;			//左边界黑点数量
////		if(CAR_IMAGE[i][95] < Threshold)	Right_Black_Piont++;	//右边界黑点数量
////	}
////}

////void Tri_Check(void)
////{
////	int nowline;
////	uint8 tri_left_white_num=0;     //左丢线
////	uint8 tri_right_white_num=0;	//右丢线
////	uint8 tri_draw_point=0;
////	uint8 tri_draw_line=0;

////	bool tri_left = 0;
////	bool tri_right = 1;

////	for(nowline=0;nowline<70;nowline++)
////	{
////		if(CAR_IMAGE[nowline][1]>Threshold)
////			tri_left_white_num++;

////		if(CAR_IMAGE[nowline][99]>Threshold)
////			tri_right_white_num++;
////	}

////	//左右都丢线，且电感误差小于10（走直线），且中线顶端出现黑色

////	if(tri_left_white_num>60 && tri_right_white_num>60
////		&& CAR_IMAGE[0][50]<Threshold && CAR_IMAGE[1][50]<Threshold && CAR_IMAGE[2][50]<Threshold)
////	{
//////		for(nowline=0;nowline<70;nowline++)
//////		{
//////			for(int i=99;i>0;i--)
//////			{
//////				if(CAR_IMAGE[nowline][i]<Threshold)
//////				{
//////					tri_draw_line=nowline;
//////					tri_draw_point=i;
//////					break;
//////				}
//////				//else ave=80;
//////			}
//////		}
////		ForkRoad_Flag1=1;
////	}

////	

////}
