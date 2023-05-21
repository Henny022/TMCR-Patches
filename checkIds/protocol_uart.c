#include "protocol.h"
#include "../io/uart.h"

void protocol_send(u32 packet)
{
    uart_send(packet);
}

u32 protocol_recv(bool32 request)
{
    if (request)
    {
        uart_send(packet(0x7f, 0));
    }
    return uart_recv();
}
