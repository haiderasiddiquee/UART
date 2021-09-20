#ifndef NDX_UART_H_INCLUDED
#define NDX_UART_H_INCLUDED

#include <stdio.h>

#define UART_ERR_NONE      0
#define UART_ERR_UNKNOWN   -1
#define UART_ERR_IO        -2
#define UART_ERR_FILE      -3
#define UART_ERR_DEFAULT   -4
#define UART_ERR_ATTR      -5

extern int uart_deinit(FILE* __fd);
extern int uart_init(char* __dev, FILE* __fd, int __flags, int __speed);
extern int uart_rx();
extern int uart_set_interface_attribs(FILE* __fd, int __speed);
extern int uart_tx(FILE* __fd, const unsigned char* __TxData, int __length);


#endif