#ifndef _CAR_DATA_H
#define _CAR_DATA_H

#include "headfile.h"
#include "Car_Image.h"
#include "Car_control.h"
#include "isr.h"
#include "ANO_Data_Transfer.h"
#include "Car_Task.h"

#define DATA_FLASH_SAVE_NUM 50 //宏定义需要存储参数的个数    一个页最多为256字节，一个参数需要占4个字节，因此最多这里为256/4=64

//定义flash最后一个扇区，避免与程序冲突
//存储参数最好从最后一个扇区开始使用
#define DATA_FLASH_SECTOR        FLASH_SECTION_127

//定义所在扇区的页编号 最后一页
#define DATA_FLASH_SECTOR_PAGE   FLASH_PAGE_3

#define     float_conversion_uint32(float_data)     (*(uint32 *)&float_data)
#define     uint32_conversion_float(uint32_data)    (*(float *)&uint32_data)
	
extern uint32 write_buf[DATA_FLASH_SAVE_NUM];
extern uint32 read_buf[DATA_FLASH_SAVE_NUM];
	
void Car_Data_Write(void);
void Car_Data_Read(void);

#endif 
