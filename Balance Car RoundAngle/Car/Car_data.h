#ifndef _CAR_DATA_H
#define _CAR_DATA_H

#include "headfile.h"
#include "Car_Image.h"
#include "Car_control.h"
#include "isr.h"
#include "ANO_Data_Transfer.h"
#include "Car_Task.h"

#define DATA_FLASH_SAVE_NUM 50 //�궨����Ҫ�洢�����ĸ���    һ��ҳ���Ϊ256�ֽڣ�һ��������Ҫռ4���ֽڣ�����������Ϊ256/4=64

//����flash���һ������������������ͻ
//�洢������ô����һ��������ʼʹ��
#define DATA_FLASH_SECTOR        FLASH_SECTION_127

//��������������ҳ��� ���һҳ
#define DATA_FLASH_SECTOR_PAGE   FLASH_PAGE_3

#define     float_conversion_uint32(float_data)     (*(uint32 *)&float_data)
#define     uint32_conversion_float(uint32_data)    (*(float *)&uint32_data)
	
extern uint32 write_buf[DATA_FLASH_SAVE_NUM];
extern uint32 read_buf[DATA_FLASH_SAVE_NUM];
	
void Car_Data_Write(void);
void Car_Data_Read(void);

#endif 
