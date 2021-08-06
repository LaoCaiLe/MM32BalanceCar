#include "Car_IMU.h"
#include "Car_FilterCalculate.h"

void spi_icm20602_get_data(GYRO_VAR *gyro_var)
{
    if (gyro_var->fiter.offset_flag)
    {
        get_icm20602_accdata_spi();
        get_icm20602_gyro_spi();
        gyro_var->orig.acc.x = icm_acc_x;
        gyro_var->orig.acc.y = icm_acc_y;
        gyro_var->orig.acc.z = icm_acc_z;

        gyro_var->orig.gyro.x = icm_gyro_x - gyro_var->fiter.gyro_offset.x;
        gyro_var->orig.gyro.y = icm_gyro_y - gyro_var->fiter.gyro_offset.y;
        gyro_var->orig.gyro.z = icm_gyro_z - gyro_var->fiter.gyro_offset.z;
    }
    else
    {
        get_icm20602_accdata_spi();
        get_icm20602_gyro_spi();
        gyro_var->orig.acc.x = icm_acc_x;
        gyro_var->orig.acc.y = icm_acc_y;
        gyro_var->orig.acc.z = icm_acc_z;

        gyro_var->orig.gyro.x = icm_gyro_x ;
        gyro_var->orig.gyro.y = icm_gyro_y ;
        gyro_var->orig.gyro.z = icm_gyro_z ;
    }
}