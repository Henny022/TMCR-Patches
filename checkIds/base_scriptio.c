#include "base.h"
#include <flags.h>
#include "../scriptio.h"

int get_item_for_global_flag(int flag)
{
    scriptio_send((1<<24) | flag);
    return scriptio_recv();
}

void set_item_global_flag(int flag)
{
    scriptio_send((2<<24) | flag);
    SetGlobalFlag(flag);
}
