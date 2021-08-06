#ifndef __CAR_FILTERCALCULATE_H
#define __CAR_FILTERCALCULATE_H

//#include "Car_config.h"
#include "headfile.h"

typedef struct
{
	int16 x;
	int16 y;			 
	int16 z;		 	 
} INT16_XYZ;

typedef struct
{
	float x;
	float y;			 
	float z;		 	 
} FLOAT_XYZ;

typedef struct
{
	float pit;
	float roll;			 
	float yaw;		 	 
} FLOAT_EULER;

typedef struct
{
	int32 x;			 
	int32 y;			 
	int32 z;		 	 
	
} INT32_XYZ ; 

typedef struct
{
	INT16_XYZ gyro;		  
	INT16_XYZ acc;		   
} GYRO_ORIG;

typedef struct
{
	FLOAT_XYZ gyro_fiter;   
	FLOAT_XYZ acc_fiter;	 	
	INT16_XYZ gyro_offset;
	INT16_XYZ acc_offset;
	uint8     offset_flag;
} GYRO_FITER;

typedef struct
{
	INT32_XYZ tar_ang_vel;  	 
	INT32_XYZ tar_ang_vel_last;  
	INT32_XYZ tar_ang;           
} GYRO_TAR_ANG;

typedef struct
{
	GYRO_TAR_ANG target;
	GYRO_ORIG    orig;
	GYRO_FITER   fiter;
	INT16_XYZ    gyro_res;
	INT16_XYZ    acc_res;
	FLOAT_EULER    euler;

} GYRO_VAR;

typedef struct
{
    uint8 cnt;

    int32 lst_pow_sum;

    int32 now_out;
    int32 lst_out;
    int32 now_velocity_xdt;
} _steepest_st;

typedef struct
{
    float x;
    float y;
    float z;
} _xyz_f_st;

typedef struct
{
    float lpf_1;

    float out;
} _lf_t;

//ButterworthµÍÍ¨ÂË²¨Æ÷
typedef struct
{
    float Input_Butter[3];
    float Output_Butter[3];
} Butter_BufferData;

typedef struct
{
    float a[3];
    float b[3];
} Butter_Parameter;
#define M_PI_F 3.141592653589793f

extern GYRO_VAR gyroscope;

extern Butter_Parameter Butter_80HZ_Parameter_Acce, Butter_60HZ_Parameter_Acce, Butter_51HZ_Parameter_Acce,
    Butter_30HZ_Parameter_Acce, Butter_20HZ_Parameter_Acce, Butter_15HZ_Parameter_Acce,
    Butter_10HZ_Parameter_Acce, Butter_5HZ_Parameter_Acce, Butter_2HZ_Parameter_Acce;

#define ABS(x) ((x) > 0 ? (x) : -(x)) //????
#define LIMIT(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define my_pow(a) ((a) * (a))
extern _xyz_f_st vec_err_i;
extern _xyz_f_st x_vec;
extern _xyz_f_st y_vec;
extern _xyz_f_st z_vec;
extern _xyz_f_st a_acc;
extern _xyz_f_st w_acc;
static float invSqrt(float x);
float my_sqrt(float number);
void IMU_offset(GYRO_VAR *gyro_var); // ÁãÆ«
void quaternion_data_filter(GYRO_VAR *gyro_var);
void Q_IMUupdata(GYRO_VAR *gyro_var);

void Kalman_Filter(GYRO_VAR *gyro_var);
void kalman_data_filter(GYRO_VAR *gyro_var);
float data_filtering(int32 *filter_arr, const int16 filter_data, const uint8 filter_depth);
void Data_steepest(GYRO_VAR *gyro_var);
void steepest_descend(int32 arr[], uint8 len, _steepest_st *steepest, uint8 step_num, int32 in);
void Butterworth_Parameter_Init(void);
float LPButterworth(float curr_input, Butter_BufferData *Buffer, Butter_Parameter *Parameter);

#endif // !__CAR_FILTERCALCULATE_H