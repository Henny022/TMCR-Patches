#include <entity.h>
#include <flags.h>
#include <item.h>
#include <collision.h>
#include "base.h"

extern void sub_08080CB4(Entity*);

void HeartContainer_Action3(Entity* this) {
    sub_08080CB4(this);
    if (!(gPlayerState.flags & PL_MINISH) && IsCollidingPlayer(this)) {
        u32 item = get_item_for_global_flag(flag2global(this->cutsceneBeh.HWORD));
        SetFlag(this->cutsceneBeh.HWORD);
        CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
        DeleteThisEntity();
    }
}
