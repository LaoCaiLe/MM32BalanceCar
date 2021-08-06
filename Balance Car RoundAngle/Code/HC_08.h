#ifndef _HC_08_H
#define _HC_08_H

#include <headfile.h>

#define Blueteeth_UART     UART_3  
#define Blueteeth_UART_TX     UART3_TX_B10
#define Blueteeth_UART_RX     UART3_RX_B11
// extern bool getball_start_flag;

void UART_Bluetooth_Init(void);

#endif