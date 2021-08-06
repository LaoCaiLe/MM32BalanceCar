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
#include "BD_fuzzy.h"
#include <string.h>
#define EC_FACTOR 9
#define ABS(x) (((x) > 0) ? (x) : (-(x)))

//模糊论域
float PFF[4] = {0.0, 250.0, 500.0, 750.0};
float DFF[4] = {0.0, 250.0, 500.0, 750.0};
//float PFF[4] = {0.0, 33.0, 66.0, 99.0};
//float DFF[4] = {0.0, 4.0, 8.0, 12.0};


//p规则表
unsigned int rule_p[7][7] = {
//误差变化率 -3,-2,-1, 0, 1, 2, 3     // 误差
    {6, 5, 4, 3, 2, 0, 0,},   //   -3
    {5, 4, 3, 2, 1, 0, 1,},   //   -2
    {4, 3, 2, 1, 0, 1, 2,},   //   -1
    {3, 2, 1, 0, 1, 2, 3,},   //    0
    {2, 1, 0, 1, 2, 3, 4,},   //    1
    {1, 0, 1, 2, 3, 4, 5,},   //    2
    {0, 0, 2, 3, 4, 5, 6}};   //    3

//i规则表
unsigned int rule_i[7][7] = {
//误差变化率 -3,-2,-1, 0, 1, 2, 3     // 误差
    {6, 6, 4, 3, 1, 0, 0,},   //   -3
    {6, 5, 4, 2, 1, 0, 0,},   //   -2
    {5, 4, 2, 1, 0, 1, 2,},   //   -1
    {4, 3, 1, 0, 1, 3, 4,},   //    0
    {2, 1, 0, 1, 2, 4, 5,},   //    1
    {0, 0, 1, 2, 4, 5, 6,},   //    2
    {0, 0, 1, 3, 4, 6, 6}};   //    3

//d规则表
unsigned int rule_d[7][7] = {
//误差变化率 -3,-2,-1, 0, 1, 2, 3    // 误差
    {2, 2, 6, 5, 6, 4, 2,},   //   -3
    {1, 2, 5, 4, 3, 1, 0,},   //   -2
    {0, 1, 3, 3, 1, 1, 0,},   //   -1
    {0, 1, 1, 1, 1, 1, 0,},   //    0
    {0, 0, 0, 0, 0, 0, 0,},   //    1
    {5, 1, 1, 1, 1, 1, 1,},   //    2
    {6, 4, 4, 3, 3, 1, 1}};   //    3


const int FMAX = 1000; //语言值的满幅值

void fuzzy_init(float uff_p_max, float uff_d_max, _UFF_t* UFF)
{
    for(int i = 0; i < 7; i++)
    {
        UFF->UFF_P[i] = uff_p_max * ((float)i / 6);
        UFF->UFF_D[i] = uff_d_max * ((float)i / 6);
    }
}

static void count_DMF(float e, float ec, float* PFF, float* DFF, _DMF_t* DMF)
{
    int Pn, Dn;
    float PF[2], DF[2];

    if(e>-PFF[3] && e<PFF[3])//E的变化在幅值内
    {
        if(e<=-PFF[2])
        {
            Pn=-2;
            PF[0]=(int)(FMAX*(float)(-PFF[2]-e)/(PFF[3]-PFF[2]));
        }
        else if(e<=-PFF[1])
        {
            Pn=-1;
            PF[0]=(int)(FMAX*(float)(-PFF[1]-e)/(PFF[2]-PFF[1]));
        }
        else if(e<=PFF[0])
        {
            Pn=0;
            PF[0]=(int)(FMAX*(float)(-PFF[0]-e)/(PFF[1]-PFF[0]));
        }
        else if(e<=PFF[1])
        {
            Pn=1;
            PF[0]=(int)(FMAX*(float)(PFF[1]-e)/(PFF[1]-PFF[0]));
        }
        else if(e<=PFF[2])
        {
            Pn=2;
            PF[0]=(int)(FMAX*(float)(PFF[2]-e)/(PFF[2]-PFF[1]));
        }
        else if(e<=PFF[3])
        {
            Pn=3;
            PF[0]=(int)(FMAX*(float)(PFF[3]-e)/(PFF[3]-PFF[2]));
        }
    }
    else if(e<=-PFF[3])  //限幅
    {
        Pn=-2;
        PF[0]=FMAX;
    }
    else if(e>=PFF[3])
    {
        Pn=3;
        PF[0]=0;
    }
    PF[1]=FMAX-PF[0];

    if(ec>-DFF[3] && ec<DFF[3])
    {
        if(ec<=-DFF[2])
        {
            Dn=-2;
            DF[0]=(int)(FMAX*(float)(-DFF[2]-ec)/(DFF[3]-DFF[2]));
        }
        else if(ec<=-DFF[1])
        {
            Dn=-1;
            DF[0]=(int)(FMAX*(float)(-DFF[1]-ec)/(DFF[2]-DFF[1]));
        }
        else if(ec<=DFF[0])
        {
            Dn=0;
            DF[0]=(int)(FMAX*(float)(-DFF[0]-ec)/(DFF[1]-DFF[0]));
        }
        else if(ec<=DFF[1])
        {
            Dn=1;
            DF[0]=(int)(FMAX*(float)(DFF[1]-ec)/(DFF[1]-DFF[0]));
        }
        else if(ec<=DFF[2])
        {
            Dn=2;
            DF[0]=(int)(FMAX*(float)(DFF[2]-ec)/(DFF[2]-DFF[1]));
        }
        else if(ec<=DFF[3])
        {
            Dn=3;
            DF[0]=(int)(FMAX*(float)(DFF[3]-ec)/(DFF[3]-DFF[2]));
        }
    }
    else if(ec<=-DFF[3])
    {
        Dn=-2;
        DF[0]=FMAX;
    }
    else if(ec>=DFF[3])
    {
        Dn=3;
        DF[0]=0;
    }
    DF[1]=FMAX-DF[0];

    memcpy(DMF->PF, PF, sizeof(float)*2);
    memcpy(DMF->DF, DF, sizeof(float)*2);
    DMF->Pn = Pn;
    DMF->Dn = Dn;
}

static float Fuzzy_Kp(_DMF_t* DMF, _UFF_t* UFF)
{
    int Un[4], UF[4], Un_out[4];
    int Pn = DMF->Pn, Dn = DMF->Dn;
    float* PF = DMF->PF, *DF = DMF->DF;
    float* UFF_P = UFF->UFF_P;

    //使用误差范围优化后的规则表rule[7][7]
    //输出值使用13个隶属函数,中心值由UFF[7]指定
    //一般都是四个规则有效
    Un[0]=rule_p[Pn+2][Dn+2];
    Un[1]=rule_p[Pn+3][Dn+2];
    Un[2]=rule_p[Pn+2][Dn+3];
    Un[3]=rule_p[Pn+3][Dn+3];

    if(PF[0]<=DF[0])
        UF[0]=PF[0];
    else
        UF[0]=DF[0];

    if(PF[1]<=DF[0])
        UF[1]=PF[1];
    else
        UF[1]=DF[0];

    if(PF[0]<=DF[1])
        UF[2]=PF[0];
    else
        UF[2]=DF[1];

    if(PF[1]<=DF[1])
        UF[3]=PF[1];
    else
        UF[3]=DF[1];

    /*同隶属函数输出语言值求大*/
    if(Un[0]==Un[1])
    {
        if(UF[0]>UF[1])
            UF[1]=0;
        else
            UF[0]=0;
    }

    if(Un[0]==Un[2])
    {
        if(UF[0]>UF[2])
            UF[2]=0;
        else
            UF[0]=0;
    }

    if(Un[0]==Un[3])
    {
        if(UF[0]>UF[3])
            UF[3]=0;
        else
            UF[0]=0;
    }

    if(Un[1]==Un[2])
    {
        if(UF[1]>UF[2])
            UF[2]=0;
        else
            UF[1]=0;
    }

    if(Un[1]==Un[3])
    {
        if(UF[1]>UF[3])
            UF[3]=0;
        else
            UF[1]=0;
    }

    if(Un[2]==Un[3])
    {
        if(UF[2]>UF[3])
            UF[3]=0;
        else
            UF[2]=0;
    }


    /*重心法反模糊*/
    /*Un[]原值为输出隶属函数标号，转换为隶属函数值*/
    if(Un[0]>=0)
        Un_out[0]=UFF_P[Un[0]];
    else
        Un_out[0]=-UFF_P[-Un[0]];

    if(Un[1]>=0)
        Un_out[1]=UFF_P[Un[1]];
    else
        Un_out[1]=-UFF_P[-Un[1]];

    if(Un[2]>=0)
        Un_out[2]=UFF_P[Un[2]];
    else
        Un_out[2]=-UFF_P[-Un[2]];

    if(Un[3]>=0)
        Un_out[3]=UFF_P[Un[3]];
    else
        Un_out[3]=-UFF_P[-Un[3]];

    float temp1 = (int)(UF[0]*Un_out[0]+UF[1]*Un_out[1]+UF[2]*Un_out[2]+UF[3]*Un_out[3]);
    float temp2 = UF[0]+UF[1]+UF[2]+UF[3];
    float out   = (float)temp1 / temp2;

    return out;
}

static float Fuzzy_Kd(_DMF_t* DMF, _UFF_t* UFF)
{
    int Un[4], UF[4], Un_out[4];
    int Pn = DMF->Pn, Dn = DMF->Dn;
    float* PF = DMF->PF, *DF = DMF->DF;
    float* UFF_D = UFF->UFF_D;

    //使用误差范围优化后的规则表rule[7][7]
    //输出值使用13个隶属函数,中心值由UFF[7]指定
    //一般都是四个规则有效
    Un[0]=rule_d[Pn+2][Dn+2];
    Un[1]=rule_d[Pn+3][Dn+2];
    Un[2]=rule_d[Pn+2][Dn+3];
    Un[3]=rule_d[Pn+3][Dn+3];

    if(PF[0]<=DF[0])
        UF[0]=PF[0];
    else
        UF[0]=DF[0];

    if(PF[1]<=DF[0])
        UF[1]=PF[1];
    else
        UF[1]=DF[0];

    if(PF[0]<=DF[1])
        UF[2]=PF[0];
    else
        UF[2]=DF[1];

    if(PF[1]<=DF[1])
        UF[3]=PF[1];
    else
        UF[3]=DF[1];

    /*同隶属函数输出语言值求大*/
    if(Un[0]==Un[1])
    {
        if(UF[0]>UF[1])
            UF[1]=0;
        else
            UF[0]=0;
    }

    if(Un[0]==Un[2])
    {
        if(UF[0]>UF[2])
            UF[2]=0;
        else
            UF[0]=0;
    }

    if(Un[0]==Un[3])
    {
        if(UF[0]>UF[3])
            UF[3]=0;
        else
            UF[0]=0;
    }

    if(Un[1]==Un[2])
    {
        if(UF[1]>UF[2])
            UF[2]=0;
        else
            UF[1]=0;
    }

    if(Un[1]==Un[3])
    {
        if(UF[1]>UF[3])
            UF[3]=0;
        else
            UF[1]=0;
    }

    if(Un[2]==Un[3])
    {
        if(UF[2]>UF[3])
            UF[3]=0;
        else
            UF[2]=0;
    }


    /*重心法反模糊*/
    /*Un[]原值为输出隶属函数标号，转换为隶属函数值*/
    if(Un[0]>=0)
        Un_out[0]=UFF_D[Un[0]];
    else
        Un_out[0]=-UFF_D[-Un[0]];

    if(Un[1]>=0)
        Un_out[1]=UFF_D[Un[1]];
    else
        Un_out[1]=-UFF_D[-Un[1]];

    if(Un[2]>=0)
        Un_out[2]=UFF_D[Un[2]];
    else
        Un_out[2]=-UFF_D[-Un[2]];

    if(Un[3]>=0)
        Un_out[3]=UFF_D[Un[3]];
    else
        Un_out[3]=-UFF_D[-Un[3]];

    float temp1 = (int)(UF[0]*Un_out[0]+UF[1]*Un_out[1]+UF[2]*Un_out[2]+UF[3]*Un_out[3]);
    float temp2 = UF[0]+UF[1]+UF[2]+UF[3];
    float out   = (float)temp1 / temp2;

    return out;
}

_DMF_t DMF;
float PID_FuzzyPD(float currentvalue, float* PFF, float* DFF, _Fuzzy_PD_t *Fuzzy_PD, _UFF_t* UFF)
{
	Fuzzy_PD->CurrentValue=currentvalue;
	Fuzzy_PD->err=Fuzzy_PD->SetValue-Fuzzy_PD->CurrentValue;
	float EC = Fuzzy_PD->err - Fuzzy_PD->errlast;
	
	count_DMF(Fuzzy_PD->err * Fuzzy_PD->factor, EC * Fuzzy_PD->factor * EC_FACTOR, PFF, DFF, &DMF);
	Fuzzy_PD->Kp = Fuzzy_PD->Kp0 + Fuzzy_Kp(&DMF, UFF);
	Fuzzy_PD->Kd = Fuzzy_PD->Kd0 + Fuzzy_Kd(&DMF, UFF);
	
	Fuzzy_PD->out=Fuzzy_PD->Kp*Fuzzy_PD->err + Fuzzy_PD->Kd*(Fuzzy_PD->err-Fuzzy_PD->errlast);
    
  Fuzzy_PD->LeastValue=Fuzzy_PD->CurrentValue;
	Fuzzy_PD->errlast=Fuzzy_PD->err;
	Fuzzy_PD->errlastlast=Fuzzy_PD->errlast;
    
    if (ABS(Fuzzy_PD->out - Fuzzy_PD->outlast) > Fuzzy_PD->threshold)
    {
        if(Fuzzy_PD->out > Fuzzy_PD->outlast)
            Fuzzy_PD->out=Fuzzy_PD->outlast+Fuzzy_PD->threshold;
        else
            Fuzzy_PD->out=Fuzzy_PD->outlast-Fuzzy_PD->threshold;
    }
	if (Fuzzy_PD->out >= Fuzzy_PD->maximum)
		Fuzzy_PD->out = Fuzzy_PD->maximum;
	else if (Fuzzy_PD->out <= Fuzzy_PD->minimum)
		Fuzzy_PD->out = Fuzzy_PD->minimum;
    Fuzzy_PD->outlast=Fuzzy_PD->out;
	
	return Fuzzy_PD->out;
}

//#define PMAX  100
//#define PMIN -100
//#define DMAX  100
//#define DMIN -100
//#define FMAX  100       //语言值的满幅值
//int PFF[4] = {0,33,66,99};  //28为电感数值最大值
///*输入量D语言值特征点*/ 
//int DFF[4] = {0,4,8,12};    //6为电感变化量最大值
///*输出量U语言值特征点*/
//int UFF[7] = {0,2000,4000,6000,8000,10000,12000}; //

//int rule[7][7]={//误差变化率 -3,-2,-1, 0, 1, 2, 3                //   误差
//                {-6,-6,-6,-6,-5,-5,-4,},                        //   -3      0
//                {-5,-5,-5,-4,-4,-3,-1,},                        //   -2      1
//                {-4,-4,-3,-1, 0, 1, 2,},                        //   -1      2
//                {-4,-3,-1, 0, 1, 3, 4,},                        //    0      3
//                {-2,-1, 0, 1, 3, 4, 4,},                        //    1      4
//                { 1, 3, 4, 4, 5, 5, 5,},                        //    2      5
//                { 4, 5, 5, 6, 6, 6, 6}};                        //    3      6  5.94

////P误差 D误差变化量 返回电机输出值
//float Fuzzy(float P, float D)
//{
//    float U;                //偏差,偏差微分以及输出值的精确量
//    float PF[2], DF[2], UF[4];//偏差,偏差微分以及输出值的隶属度
//    int Pn, Dn, Un[4];
//    float temp1, temp2;

//    /*隶属度的确定*/
//    /*根据PD的指定语言值获得有效隶属度*/
//    if (P > -PFF[3] && P < PFF[3])
//    {
//        if (P <= -PFF[2])
//        {
//            Pn = -2;
//            PF[0] = FMAX * ((float)(-PFF[2] - P) / (PFF[3] - PFF[2]));
//        }
//        else if (P <= -PFF[1])
//        {
//            Pn = -1;
//            PF[0] = FMAX * ((float)(-PFF[1] - P) / (PFF[2] - PFF[1]));
//        }
//        else if (P <= PFF[0])
//        {
//            Pn = 0;
//            PF[0] = FMAX * ((float)(-PFF[0] - P) / (PFF[1] - PFF[0]));
//        }
//        else if (P <= PFF[1])
//        {
//            Pn = 1; PF[0] = FMAX * ((float)(PFF[1] - P) / (PFF[1] - PFF[0]));
//        }
//        else if (P <= PFF[2])
//        {
//            Pn = 2; PF[0] = FMAX * ((float)(PFF[2] - P) / (PFF[2] - PFF[1]));
//        }
//        else if (P <= PFF[3])
//        {
//            Pn = 3; PF[0] = FMAX * ((float)(PFF[3] - P) / (PFF[3] - PFF[2]));
//        }
//    }
//    else if (P <= -PFF[3])
//    {
//        Pn = -2; PF[0] = FMAX;
//    }
//    else if (P >= PFF[3])
//    {
//        Pn = 3; PF[0] = 0;
//    }
//    PF[1] = FMAX - PF[0];

//    if (D > -DFF[3] && D < DFF[3])
//    {
//        if (D <= -DFF[2])
//        {
//            Dn = -2; DF[0] = FMAX * ((float)(-DFF[2] - D) / (DFF[3] - DFF[2]));
//        }
//        else if (D <= -DFF[1])
//        {
//            Dn = -1;
//            DF[0] = FMAX * ((float)(-DFF[1] - D) / (DFF[2] - DFF[1]));
//        }
//        else if (D <= DFF[0])
//        {
//            Dn = 0;
//            DF[0] = FMAX * ((float)(-DFF[0] - D) / (DFF[1] - DFF[0]));
//        }
//        else if (D <= DFF[1])
//        {
//            Dn = 1;
//            DF[0] = FMAX * ((float)(DFF[1] - D) / (DFF[1] - DFF[0]));
//        }
//        else if (D <= DFF[2])
//        {
//            Dn = 2; DF[0] = FMAX * ((float)(DFF[2] - D) / (DFF[2] - DFF[1]));
//        }
//        else if (D <= DFF[3])
//        {
//            Dn = 3; DF[0] = FMAX * ((float)(DFF[3] - D) / (DFF[3] - DFF[2]));
//        }
//    }
//    else if (D <= -DFF[3])
//    {
//        Dn = -2;
//        DF[0] = FMAX;
//    }
//    else if (D >= DFF[3])
//    {
//        Dn = 3;
//        DF[0] = 0;
//    }
//    DF[1] = FMAX - DF[0];

//    /*使用误差范围优化后的规则表rule[7][7]*/
//    /*输出值使用13个隶属函数,中心值由UFF[7]指定*/
//    /*一般都是四个规则有效*/
////    fuzzy_txt[0]=Pn - 1 + 3;
////    fuzzy_txt[1]=Dn - 1 + 3;
////    fuzzy_txt[2]=Pn + 3;
////    fuzzy_txt[3]=Dn - 1 + 3;
////    fuzzy_txt[4]=Pn - 1 + 3;
////    fuzzy_txt[5]=Dn + 3;
////    fuzzy_txt[6]=Pn + 3;
////    fuzzy_txt[7]=Dn + 3;
//    
//    Un[0] = rule[Pn - 1 + 3][Dn - 1 + 3];
//    Un[1] = rule[Pn + 3][Dn - 1 + 3];
//    Un[2] = rule[Pn - 1 + 3][Dn + 3];
//    Un[3] = rule[Pn + 3][Dn + 3];
//    if (PF[0] <= DF[0])	UF[0] = PF[0];
//    else 	UF[0] = DF[0];
//    if (PF[1] <= DF[0])	UF[1] = PF[1];
//    else 	UF[1] = DF[0];
//    if (PF[0] <= DF[1])	UF[2] = PF[0];
//    else 	UF[2] = DF[1];
//    if (PF[1] <= DF[1])	UF[3] = PF[1];
//    else 	UF[3] = DF[1];

//    /*同隶属函数输出语言值求大*/
//    if (Un[0] == Un[1])
//    {
//        if (UF[0] > UF[1])	UF[1] = 0;
//        else	UF[0] = 0;
//    }
//    if (Un[0] == Un[2])
//    {
//        if (UF[0] > UF[2])	UF[2] = 0;
//        else	UF[0] = 0;
//    }
//    if (Un[0] == Un[3])
//    {
//        if (UF[0] > UF[3])	UF[3] = 0;
//        else	UF[0] = 0;
//    }
//    if (Un[1] == Un[2])
//    {
//        if (UF[1] > UF[2])	UF[2] = 0;
//        else	UF[1] = 0;
//    }
//    if (Un[1] == Un[3])
//    {
//        if (UF[1] > UF[3])	UF[3] = 0;
//        else	UF[1] = 0;
//    }
//    if (Un[2] == Un[3])
//    {
//        if (UF[2] > UF[3])	UF[3] = 0;
//        else	UF[2] = 0;
//    }
////
//    /*重心法反模糊*/
//    /*Un[]原值为输出隶属函数标号，转换为隶属函数值*/
//    if (Un[0] >= 0)	Un[0] = UFF[Un[0]];
//    else			Un[0] = -UFF[-Un[0]];
//    if (Un[1] >= 0)	Un[1] = UFF[Un[1]];
//    else			Un[1] = -UFF[-Un[1]];
//    if (Un[2] >= 0)	Un[2] = UFF[Un[2]];
//    else			Un[2] = -UFF[-Un[2]];
//    if (Un[3] >= 0)	Un[3] = UFF[Un[3]];
//    else			Un[3] = -UFF[-Un[3]];

//    temp1 = UF[0] * Un[0] + UF[1] * Un[1] + UF[2] * Un[2] + UF[3] * Un[3];
//    temp2 = UF[0] + UF[1] + UF[2] + UF[3];
//    U = temp1 / temp2;

//    return U;
//}