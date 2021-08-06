#include "Car_control.h"
#include "headfile.h"
#include "Car_Task.h"

//�ٶȻ�pid����
float Speed_kp = 1.2;
float Speed_ki = 0;
float Speed_kd = 0;

//���ٶȻ�pid����
float AngleSpeed_Kp = 15;	//15
float AngleSpeed_Ki = 0.0;
float AngleSpeed_Kd = 2;

//�ǶȻ�pid����
float Angle_Kp = 110; 	//60
float Angle_Ki = 0;//0
float Angle_Kd = 1;	//0

//���ת��pid
float Turn_Kp = 150;
float Turn_Ki = 0;
float Turn_Kd = 2100;

//�ǶȻ������Χ
int AnglePid_OutMax = 3500; //1500
int AnglePid_OutMin = -3500;//-1500

//ת�������Χ
int TurnPid_OutMax = 24000;
int TurnPid_OutMin = -24000;

//���ٶȻ������Χ
int AngleSpeedPid_OutMax = 40000;
int AngleSpeedPid_OutMin = -40000;

//�ٶȻ������Χ
int SpeedPid_OutMax = 52;
int SpeedPid_OutMin = -48;


_UFF_t Turn_UFF, L_UFF, R_UFF;

_Fuzzy_PD_t Turn_FuzzyPD = {
    //���PID
    .Kp0 = 4.0,
    .Kd0 = 4.0,
    .CurrentValue = 0.0,
    .LeastValue = 0.0,
    .SetValue = 0.0,
    .err = 0.0,
    .errlast = 0.0,
    .errlastlast = 0.0,
    .out = 0.0,
    .outlast = 0.0,
    .threshold = 50000,
    .maximum = 40000,
    .minimum = -40000,
    .factor = 9.0,
};


//���ת��pid
int Turn_Control(int error)
{
	static int pid_out, integ, last_error;
	
	integ += error;
	
	integ = limit_ab(integ,-100000,100000);
	
	pid_out = Turn_Kp * error + Turn_Ki*integ + Turn_Kd * (error - last_error);
	
	pid_out = limit_ab(pid_out,TurnPid_OutMin,TurnPid_OutMax);

	last_error = error;
	
	return pid_out;
}


//���ٶȿ���
int AngleSpeed_Control(int error)
{
	static int pid_out, integ, last_error, last_out;
	
	integ += error;
	
	integ = limit_ab(integ,-40000,40000);

	pid_out = AngleSpeed_Kp*error + AngleSpeed_Ki*integ + AngleSpeed_Kd * (error - last_error);
	
	pid_out = limit_ab(pid_out,AngleSpeedPid_OutMin,AngleSpeedPid_OutMax);

	last_error = error;
	
	last_out = pid_out;
	
	return pid_out;
}


//�ٶ�pid����
int Speed_Control(int Target, int currentvalue)
{
	static int pid_out, error, last_error, integ, lastlast_error, devir;
	
	error = Target - currentvalue;
	
	integ += error;
	
	integ = limit_ab(integ,-1000,1000);
	
	pid_out = Speed_kp*error + Speed_ki*integ + Speed_kd*(error - last_error);
	
	pid_out = limit_ab(pid_out,SpeedPid_OutMin,SpeedPid_OutMax);
	
	last_error = error;
	
	return pid_out;
	
}

//ֱ����pid����
int Stand_Control(int Target, float currentvalue, int groy_y)
{
	static int pid_out,error,integ;
	
	error = Target - currentvalue;
	
	integ += error;
	
	integ = limit_ab(integ,-10000,10000);
	
	pid_out = Angle_Kp*error + Angle_Ki * integ + Angle_Kd * groy_y ;
	
	//pid_out = limit_ab(pid_out,AnglePid_OutMin,AnglePid_OutMax);
	
	return pid_out;
}

//��������
void Beep_Start(void)
{
	gpio_set(Beep,1);
}

//������ֹͣ
void Beep_Stop(void)
{
	gpio_set(Beep,0);
}

//���pwm�趨
void Set_PWM(int duty1,int duty2)
{
//���ҵ��ռ�ձ��޷�
	duty1 = limit_ab(duty1,MotorPwm_Min,MotorPwm_Max); 
	duty2 = limit_ab(duty2,MotorPwm_Min,MotorPwm_Max);


	if(duty1<0)
	{
		pwm_duty_updata(PWM_TIM,MotorA_1,-duty1);
		pwm_duty_updata(PWM_TIM,MotorA_2,0);
	}
	else
	{
		pwm_duty_updata(PWM_TIM,MotorA_1,0);
		pwm_duty_updata(PWM_TIM,MotorA_2,duty1);
	}

	if(duty2<0)
	{
		pwm_duty_updata(PWM_TIM,MotorB_1,-duty2);
		pwm_duty_updata(PWM_TIM,MotorB_2,0);
	}
	else
	{		
		pwm_duty_updata(PWM_TIM,MotorB_1,0);
		pwm_duty_updata(PWM_TIM,MotorB_2,duty2);
	}
}
