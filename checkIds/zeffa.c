#include <item.h>
#include <flags.h>
#include <entity.h>
#include <player.h>
#include <room.h>
#include <save.h>
#include <collision.h>

#include "base.h"

extern u32 sub_0800445C(Entity*);

void Bird_Type2_Action1(Entity* this) {
    if ((gPlayerState.flags & PL_MINISH) != 0) {
        sub_0800445C(this);
    } else if (IsCollidingPlayer(this) != 0) {
        SetGlobalFlag(LV3_CLEAR);
        UpdateGlobalProgress();
        int item = get_item_for_global_flag_with_default(MACHI_SET_3,ITEM_OCARINA);
        CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
        gSave.windcrests |= 0x10000000;
        DeleteThisEntity();
    }
}

extern void LoadStaticBackground(u32);
extern EntityData gUnk_080E3850;

void sub_StateChange_FortressOfWindsTop_Main(void) {
    LoadStaticBackground(3);
    if (!CheckGlobalFlag(LV3_CLEAR) && CheckLocalFlag(LV3_OCARINA_FALL)) {
        LoadRoomEntityList(&gUnk_080E3850);
    }
}
