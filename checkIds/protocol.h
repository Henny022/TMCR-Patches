#include <global.h>

void protocol_send(u32 packet);
u32 protocol_recv(bool32 request);

inline void protocol_nack(u32 packet)
{
    protocol_send(packet|0x80000000);
}

inline u32 packet(u32 type, u32 value)
{
    return (type <<24)|(value&0xffffff);
}

inline u32 packet_type(u32 packet)
{
    return (packet>>24)&0xff;
}

inline u32 packet_value(u32 packet)
{
    return packet&0xffffff;
}
