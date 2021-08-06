#include "Car_data.h"
#include "menu_display.h"
#include "menu_core.h"
#include <HC_08.h>
uint8 status;

uint32 write_buf[DATA_FLASH_SAVE_NUM];

uint32 read_buf[DATA_FLASH_SAVE_NUM];

void Car_Data_Write(void)
{
    if(flash_check(DATA_FLASH_SECTOR, DATA_FLASH_SECTOR_PAGE)) //擦除扇区
    {
        status = flash_erase_page(DATA_FLASH_SECTOR, DATA_FLASH_SECTOR_PAGE);;
        if (status)
            while (1)
                ; //擦除失败
    }

    //速度参数写入
		write_buf[0] = CarSpeed_Set;
		write_buf[1] = float_conversion_uint32(Angle_Kp);
		write_buf[2] = float_conversion_uint32(Angle_Kd);
		write_buf[3] = float_conversion_uint32(Speed_kp);
		write_buf[4] = float_conversion_uint32(Speed_kd);
		write_buf[5] = Fall_time;
		write_buf[6] = float_conversion_uint32(AngleSpeed_Kp);
		write_buf[7] = InFork_time;
		write_buf[8] = float_conversion_uint32(AngleSpeed_Kd);
		write_buf[9] = SpeedPid_OutMax;
		write_buf[10] = SpeedPid_OutMin;
		write_buf[11] = AnglePid_OutMax;
		write_buf[12] = AnglePid_OutMin;
		write_buf[13] = float_conversion_uint32(Mid_Angle);
		write_buf[15] = InFork_TurnKd;
		write_buf[17] = TurnPid_OutMax;
		write_buf[18] = TurnPid_OutMin;
		write_buf[19] = AngleSpeedPid_OutMax;
		write_buf[20] = AngleSpeedPid_OutMin;
		write_buf[21] = InFork_Angle;
		write_buf[22] = getball_start_flag;
		write_buf[23] = ForkRoad_ToLeft;
		write_buf[24] = float_conversion_uint32(Turn_Kp);
		write_buf[25] = float_conversion_uint32(Turn_Kd);
		write_buf[26] = StartAngle;
		write_buf[27] = InRound_Angle;
		write_buf[28] = float_conversion_uint32(InRound_factor);
		write_buf[29] = ForkRoad_ToRight;
		write_buf[30] = InRound_ToLeft;
		write_buf[31] = InRound_ToRight;
		write_buf[32] = float_conversion_uint32(InFork_factor);
		write_buf[33] = InFork_Speed;
		write_buf[34] = InRound_Inductance_mid;
		write_buf[35] = InRound_Inductance_left;
		write_buf[36] = InRound_Inductance_right;
		write_buf[37] = InFork_Inductance_mid;
		write_buf[38] = InFork_Inductance_left;
		write_buf[39] = InFork_Inductance_right;
		write_buf[40] = abandon_Round;
    status = flash_page_program(DATA_FLASH_SECTOR, DATA_FLASH_SECTOR_PAGE, write_buf, DATA_FLASH_SAVE_NUM);
    if (status)
        while (1)
            ;
}

/**
 * @brief   读取数据
*/
void Car_Data_Read(void)
{
    flash_page_read(DATA_FLASH_SECTOR, DATA_FLASH_SECTOR_PAGE, read_buf, DATA_FLASH_SAVE_NUM);
  
		CarSpeed_Set = read_buf[0];
    Angle_Kp = uint32_conversion_float(read_buf[1]);
		Angle_Kd = uint32_conversion_float(read_buf[2]);
		Speed_kp = uint32_conversion_float(read_buf[3]);
		Speed_kd = uint32_conversion_float(read_buf[4]);
		Fall_time = read_buf[5];
		AngleSpeed_Kp = uint32_conversion_float(read_buf[6]);
		InFork_time = read_buf[7];
		AngleSpeed_Kd = uint32_conversion_float(read_buf[8]);
		SpeedPid_OutMax = read_buf[9];
		SpeedPid_OutMin = read_buf[10];
		AnglePid_OutMax = read_buf[11];
		AnglePid_OutMin = read_buf[12];
		Mid_Angle = uint32_conversion_float(read_buf[13]);
		InFork_TurnKd = read_buf[15];
		TurnPid_OutMax = read_buf[17];
		TurnPid_OutMin = read_buf[18];
		AngleSpeedPid_OutMax = read_buf[19];
		AngleSpeedPid_OutMin = read_buf[20];
		InFork_Angle = read_buf[21];
		getball_start_flag = read_buf[22];
		ForkRoad_ToLeft = read_buf[23];
		Turn_Kp = uint32_conversion_float(read_buf[24]);
		Turn_Kd = uint32_conversion_float(read_buf[25]);
		StartAngle = read_buf[26];
		InRound_Angle = read_buf[27];
		InRound_factor = uint32_conversion_float(read_buf[28]);
		ForkRoad_ToRight = read_buf[29];
		InRound_ToLeft = read_buf[30];
		InRound_ToRight = read_buf[31];
		InFork_factor = uint32_conversion_float(read_buf[32]);
		InFork_Speed = read_buf[33];
		InRound_Inductance_mid = read_buf[34];
		InRound_Inductance_left = read_buf[35];
		InRound_Inductance_right = read_buf[36];
		InFork_Inductance_mid = read_buf[37];
		InFork_Inductance_left = read_buf[38];
		InFork_Inductance_right = read_buf[39];
		abandon_Round = read_buf[40];
		SubMenu_Display(MenuItem);
}