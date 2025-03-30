#include "base.h"
#include <flags.h>
#include <item.h>

#include "../debug/mgba.h"

extern const u32 n_checks;
extern const struct{
    u16 flag;
    u16 item;
} checks[];

int peek_item_for_global_flag(int flag)
{
    for (u32 i = 0; i < n_checks; i++)
    {
        if (checks[i].flag == flag)
        {
            return checks[i].item;
        }
    }
    return ITEM_FIRE_ROD;
}

int get_item_for_global_flag(int flag)
{
    SetGlobalFlag(flag);
    for (u32 i = 0; i < n_checks; i++)
    {
        if (checks[i].flag == flag)
        {
            return checks[i].item;
        }
    }
    return ITEM_FIRE_ROD;
}
