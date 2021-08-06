#ifndef __CAR_IMU_H
#define __CAR_IMU_H

#include "headfile.h"
//#include "Car_config.h"
#include "Car_FilterCalculate.h"

void spi_icm20602_get_data(GYRO_VAR *gyro_var);


#endif // !__CAR_IMU_H