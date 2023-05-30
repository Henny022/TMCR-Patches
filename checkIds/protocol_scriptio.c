#include "protocol.h"
#include "../scriptio.h"

void protocol_send(u32 packet)
{
    scriptio_send(packet);
}

u32 protocol_recv(bool32 request)
{
    if(request && !gScriptIO.rx.status)
    {
        return packet(0x7f, 0);
    }
    return scriptio_recv();
}
