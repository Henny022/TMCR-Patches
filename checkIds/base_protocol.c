#include "base.h"
#include "protocol.h"


int peek_item_for_global_flag(int flag)
{
    protocol_send(packet(1, flag));
    u32 r = protocol_recv(FALSE);
    while (!(packet_type(r)==2))
    {
        protocol_nack(r);
        r = protocol_recv(FALSE);
    }
    return packet_value(r);
}

int get_item_for_global_flag(int flag)
{
    protocol_send(packet(3, flag));
    u32 r = protocol_recv(FALSE);
    while (!(packet_type(r)==4))
    {
        protocol_nack(r);
        r = protocol_recv(FALSE);
    }
    return packet_value(r);
}
