#include "base.h"

extern const u32 n_checks;
extern const u16 checks[];

u16 get_item_for_check_id(u16 check_id)
{
    if (check_id >= n_checks)
        return 0;
    return checks[check_id];
}