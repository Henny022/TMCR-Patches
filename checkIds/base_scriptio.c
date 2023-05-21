#include "base.h"
#include <flags.h>
#include "../scriptio.h"

int peek_item_for_global_flag(int flag)
{
    scriptio_send((1<<24) | flag);
    u32 r = scriptio_recv();
    while (!((r>>24)==2))
    {
        scriptio_send((6<<24) | (r&0xffffff));
        r = scriptio_recv();
    }
    return r&0xffffff;
}

int get_item_for_global_flag(int flag)
{
    scriptio_send((3<<24) | flag);
    u32 r = scriptio_recv();
    while (!((r>>24)==4))
    {
        scriptio_send((6<<24) | (r&0xffffff));
        r = scriptio_recv();
    }
    return r&0xffffff;
}
