#include <HC_08.h>
#include "BD_fuzzy.h"

//uint8 Bluetooth_rx_buffer;
//uint8 bluetooth_uart_data[10];      //蓝牙接收缓冲区
//uint8 uartindex = 0;
// bool getball_start_flag = 0;       //接球完成标志位
//lpuart_transfer_t   Bluetooth_receivexfer;
//lpuart_handle_t    Bluetooth_g_lpuartHandle;


//void Bluetooth_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
//{
//    if(kStatus_LPUART_RxIdle == status)
//    {
//        //数据已经被写入到了 之前设置的BUFF中
//        //本例程使用的BUFF为 Bluetooth_rx_buffer
//        bluetooth_uart_data[uartindex++] = Bluetooth_rx_buffer;//将数据取出
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
//    handle->rxDataSize = Bluetooth_receivexfer.dataSize;  //还原缓冲区长度
//    handle->rxData = Bluetooth_receivexfer.data;          //还原缓冲区地址
//}

void UART_Bluetooth_Init(void)
{
		uart_init(Blueteeth_UART, 115200, Blueteeth_UART_TX, Blueteeth_UART_RX);	
    NVIC_SetPriority(UART3_IRQn,1);         //设置串口中断优先级 范围0-15 越小优先级越高
    uart_rx_irq(Blueteeth_UART,1);			//开启接收中断
    
//    //配置串口接收的缓冲区及缓冲区长度
//    Bluetooth_receivexfer.dataSize = 1;
//    Bluetooth_receivexfer.data = &Bluetooth_rx_buffer;
//    
//    //设置中断函数及其参数
//    uart_set_handle(Blueteeth_UART, &Bluetooth_g_lpuartHandle, Bluetooth_uart_callback, NULL, 0, Bluetooth_receivexfer.data, 1);
}
