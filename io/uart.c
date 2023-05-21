#include "uart.h"
#include <gba/io_reg.h>

#define SIO_UART 0x3000
#define SIO_UART_BAUD_9600 0
#define SIO_UART_BAUD_38400 1
#define SIO_UART_BAUD_57600 2
#define SIO_UART_BAUD_115200 3
#define SIO_UART_SENDING (1<<4)
#define SIO_UART_RECVING (1<<5)
#define SIO_UART_ERRORED (1<<6)
#define SIO_UART_LENGTH_8 (1<<7)
#define SIO_UART_FIFO (1<<8)
#define SIO_UART_SEND_ENABLE (1<<10)
#define SIO_UART_RECV_ENABLE (1<<11)

void uart_init()
{
    REG_RCNT = 0;
    REG_SIOCNT = 0;
    REG_SIOCNT = SIO_UART_BAUD_115200
               | SIO_UART_LENGTH_8
               | SIO_UART_SEND_ENABLE
               | SIO_UART_RECV_ENABLE
               | SIO_UART;
    REG_SIOCNT |= SIO_UART_FIFO;
}

void uart_send(u32 packet)
{
    const u8* ptr = (const u8*)&packet;
    for(int i = 0; i < 4; i++)
    {
        while((REG_SIOCNT & SIO_UART_SENDING) != 0);
        REG_SIODATA8 = ptr[i];
    }
}

u32 uart_recv()
{
    u32 packet;
    u8* ptr = (u8*)&packet;
    for (int i = 0; i < 4; i++)
    {
        while((REG_SIOCNT & SIO_UART_RECVING) != 0);
        ptr[i] = REG_SIODATA8;
    }
    return packet;
}
