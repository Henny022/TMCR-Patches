#include "protocol.h"
#include "../scriptio.h"

void protocol_send(u32 packet)
{
    scriptio_send(packet);
}

u32 protocol_recv(bool32 request)
{
    (void) request;
    if(gScriptIO.rx.status)
    {
        return scriptio_recv();
    }
    else
    {
        return packet(0x7f, 0);
    }
}
