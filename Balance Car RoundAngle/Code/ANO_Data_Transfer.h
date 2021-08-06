#ifndef _MONITOR_H
#define _MONITOR_H

#include <headfile.h>
//#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
//#include "uart_calc.h"

typedef uint16_t u16;
//typedef uint32_t u32;
typedef uint64_t u64;
//typedef uint8_t u8;





#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

#define HEAD_FRAME 0xAA //数据帧头
#define D_ADDRESS 0xFF  //广播数据输出

/*禁止修改*/
#define USER_FRAME_1 0xF1 //用户自定义帧
#define USER_FRAME_2 0xF2
#define USER_FRAME_3 0xF3
#define USER_FRAME_4 0xF4
#define USER_FRAME_5 0xF5
#define USER_FRAME_6 0xF6
#define USER_FRAME_7 0xF7
#define USER_FRAME_8 0xF8
#define USER_FRAME_9 0xF9
#define USER_FRAME_A 0xFA


//void ANO_DT_Send_data(uint16 data1, uint16 data2, uint16 data3, uint16 data4, uint16 data5);

void Test_Send_User(int16_t data1, int16_t data2, int16_t data3,int16_t data4,int16_t data5,int16_t data6,int16_t data7,int16_t data8,int16_t data9,int16_t data10);

void usart1_send_char(int16_t c);


#endif
