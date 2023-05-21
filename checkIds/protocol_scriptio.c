#include "protocol.h"
#include "../scriptio.h"

void protocol_send(u32 packet)
{
    scriptio_send(packet);
}

u32 protocol_recv(bool32 request)
{
    (void) request;
    return scriptio_recv();
}
