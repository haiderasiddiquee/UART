#include <termios.h>
#include <stdio.h>
#include <syslog.h>

#include "ndx_uart.h"

int uart_deinit(FILE* fd){
    int ret = UART_ERR_NONE;

    fclose(fd);
    if(fd == NULL){
        printf("ERROR: UART device did not deinitialized\n");
        ret = UART_ERR_FILE;
        goto Exit;
    }

    Exit:
        return ret;
}

int uart_init(char* dev, FILE* fd, int flags, int speed){
    int ret = UART_ERR_NONE;

    fd = open(dev, flags);
    if(fd < 0){
        printf("Error: UART device open = %i\n", fd);
        ret = UART_ERR_FILE;
        goto Exit;
    }

    if(uart_set_interface_attribs(fd, speed) == UART_ERR_ATTR){
        ret = UART_ERR_ATTR;
        goto Exit;
    }

    Exit:
        return ret;
}

int uart_rx(FILE* fd, unsigned char* rxData, int length){
    int ret = UART_ERR_NONE;

    read
}

int uart_set_interface_attribs(FILE* fd, int speed){
    int ret = UART_ERR_NONE;
    struct  termios tty;

    if(tcgetattr(fd, &tty) < 0){
        printf("Error from tcgetattr: %s\n", strerror(errno));
        ret = UART_ERR_ATTR;
        goto Exit;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    // setup for non-canonical mode
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    // fetch bytes as they become available
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    cfmakeraw(&tty);

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        ret = UART_ERR_ATTR;
        goto Exit;
    }

    Exit:
        return ret;
}

int uart_tx(FILE* fd, const unsigned char* txData, int length){
    int ret = UART_ERR_NONE;
    int temp_len;

    temp_len = write(fd, txData, length);
    if (temp_len != length) {
        printf("Error: UART error in data transfer = %d\n", ret);
        ret = UART_ERR_IO;
        goto ret;
    }
    tcdrain(fd);
    Exit:
        return ret;
}

