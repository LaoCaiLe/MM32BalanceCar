#include <HC_08.h>
#include "BD_fuzzy.h"

//uint8 Bluetooth_rx_buffer;
//uint8 bluetooth_uart_data[10];      //�������ջ�����
//uint8 uartindex = 0;
// bool getball_start_flag = 0;       //������ɱ�־λ
//lpuart_transfer_t   Bluetooth_receivexfer;
//lpuart_handle_t    Bluetooth_g_lpuartHandle;


//void Bluetooth_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
//{
//    if(kStatus_LPUART_RxIdle == status)
//    {
//        //�����Ѿ���д�뵽�� ֮ǰ���õ�BUFF��
//        //������ʹ�õ�BUFFΪ Bluetooth_rx_buffer
//        bluetooth_uart_data[uartindex++] = Bluetooth_rx_buffer;//������ȡ��
//        if (uartindex >= 4)
//        {
//            uartindex = 0;
//        }
//        if(bluetooth_uart_data[0] == 0x11 && bluetooth_uart_data[1] == 0x23
//						&& bluetooth_uart_data[2] == 0x01 && bluetooth_uart_data[3] == 0x07)
//        {
//            //getball_start_flag = 1;
//				//	Bluetooth_Senddata(fuzzy_txt);
//        }
//    }
//    handle->rxDataSize = Bluetooth_receivexfer.dataSize;  //��ԭ����������
//    handle->rxData = Bluetooth_receivexfer.data;          //��ԭ��������ַ
//}

void UART_Bluetooth_Init(void)
{
		uart_init(Blueteeth_UART, 115200, Blueteeth_UART_TX, Blueteeth_UART_RX);	
    NVIC_SetPriority(UART3_IRQn,1);         //���ô����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
    uart_rx_irq(Blueteeth_UART,1);			//���������ж�
    
//    //���ô��ڽ��յĻ�����������������
//    Bluetooth_receivexfer.dataSize = 1;
//    Bluetooth_receivexfer.data = &Bluetooth_rx_buffer;
//    
//    //�����жϺ����������
//    uart_set_handle(Blueteeth_UART, &Bluetooth_g_lpuartHandle, Bluetooth_uart_callback, NULL, 0, Bluetooth_receivexfer.data, 1);
}
