#include "ANO_Data_Transfer.h"

uint8 testdatatosend[50];
void Test_Send_User(int16_t data1, int16_t data2, int16_t data3,int16_t data4,int16_t data5,int16_t data6,int16_t data7,int16_t data8,int16_t data9,int16_t data10)	
{
	uint8 _cnt=0;
	uint8 i;
	uint8 sum = 0;
	
	testdatatosend[_cnt++]=0xAA;
	testdatatosend[_cnt++]=0x05;
	testdatatosend[_cnt++]=0xAF;
	testdatatosend[_cnt++]=0xF1;
	testdatatosend[_cnt++]=0;
 
	testdatatosend[_cnt++]=BYTE1(data1);
	testdatatosend[_cnt++]=BYTE0(data1);
	
	testdatatosend[_cnt++]=BYTE1(data2);
	testdatatosend[_cnt++]=BYTE0(data2);
	
	testdatatosend[_cnt++]=BYTE1(data3);
	testdatatosend[_cnt++]=BYTE0(data3);
	
	testdatatosend[_cnt++]=BYTE1(data4);
	testdatatosend[_cnt++]=BYTE0(data4);
	
	testdatatosend[_cnt++]=BYTE1(data5);
	testdatatosend[_cnt++]=BYTE0(data5);
	
	testdatatosend[_cnt++]=BYTE1(data6);
	testdatatosend[_cnt++]=BYTE0(data6);
	
	testdatatosend[_cnt++]=BYTE1(data7);
	testdatatosend[_cnt++]=BYTE0(data7);
	
	testdatatosend[_cnt++]=BYTE1(data8);
	testdatatosend[_cnt++]=BYTE0(data8);
	
	testdatatosend[_cnt++]=BYTE1(data9);
	testdatatosend[_cnt++]=BYTE0(data9);
	
	testdatatosend[_cnt++]=BYTE1(data10);
	testdatatosend[_cnt++]=BYTE0(data10);
	
	
 
	testdatatosend[4] = _cnt-5;
	
		
	for( i=0;i<_cnt;i++)
		sum += testdatatosend[i];
	
	testdatatosend[_cnt++]=sum;	
	for(i=0;i<_cnt;i++)
//	usart1_send_char(testdatatosend[i]);	//�������ݵ�����1
	seekfree_wireless_send_buff(&testdatatosend[i],sizeof(uint8));
}

void usart1_send_char(int16_t c)//�����ַ��� ����   Ӧ��ָ�� ����
{
//				
//	while(MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE)& EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG); //ѭ������,ֱ���������   
//	    MAP_UART_transmitData(EUSCI_A0_BASE, c);
//		seekfree_wireless_send_buff((uint8)&c, sizeof(int16_t));
}


//void ANO_DT_Send_data(uint16_t data1, uint16_t data2, uint16_t data3, uint16_t data4, uint16_t data5)
//{
//	uint8 _cnt = 0;
//    uint8 sumcheck = 0; //��У��
//    uint8 addcheck = 0; //���Ӻ�У��
//    uint8 i;

//    data_to_send[_cnt++] = HEAD_FRAME;
//    data_to_send[_cnt++] = D_ADDRESS;
//    data_to_send[_cnt++] = USER_FRAME_1;
//    data_to_send[_cnt++] = 0; //���ݳ���
//    data_to_send[_cnt++] = BYTE1(data1);
//		data_to_send[_cnt++] = BYTE0(data1);
//    data_to_send[_cnt++] = BYTE1(data2);
//    data_to_send[_cnt++] = BYTE0(data2);
//    data_to_send[_cnt++] = BYTE1(data3);
//    data_to_send[_cnt++] = BYTE0(data3);
//    data_to_send[_cnt++] = BYTE1(data4);
//    data_to_send[_cnt++] = BYTE0(data4);
//		data_to_send[_cnt++] = BYTE1(data5);
//    data_to_send[_cnt++] = BYTE0(data5);

//	
//    data_to_send[3] = _cnt - 4;

//    for (i = 0; i < _cnt; i++)
//    {
//        sumcheck += data_to_send[i];
//        addcheck += sumcheck;
//    }

//    data_to_send[_cnt++] = sumcheck;
//    data_to_send[_cnt++] = addcheck;
//	
////	uart_putbuff(EUSCI_A0_BASE,data_to_send,_cnt);
//}
