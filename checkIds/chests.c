#include <room.h>
#include <sound.h>
#include <item.h>
#include <flags.h>
#include "base.h"
#include "../debug/mgba.h"

extern void CreateItemEntity(u32 type, u32 type2, u32 delay);

void OpenSmallChest(u32 pos, u32 layer) {
    TileEntity* t = gSmallChests;
    u32 found = 0;
    u32 i;
    for (i = 0; i < 8; ++i, ++t) {
        if (*(u16*)&t->tilePos == pos) {
            found = 1;
            break;
        }
    }
    if ((layer >> 1) == ((u32)(t->_6 << 31) >> 31)) {
        if (found) {
            int item = get_item_for_global_flag_with_default(local2global(t->localFlag), get_item_from_value_and_subvalue(t->_2, t->_3));
            //set_item_global_flag(local2global(t->localFlag));
            SetLocalFlag(t->localFlag);
            CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
        } else {
            CreateItemEntity(ITEM_FAIRY, 0, 0);
        }
        sub_0807B7D8(0x74, pos, layer);
        RequestPriorityDuration(NULL, 120);
        SoundReq(SFX_CHEST_OPEN);
    }
}

void sub_08084074(u32 param_1) {
    TileEntity* tileEntity = (TileEntity *)GetCurrentRoomProperty(3);
    if (tileEntity != NULL) {
        for (; tileEntity->type != 0; tileEntity++) {
            if ((tileEntity->type == BIG_CHEST) && (param_1 == tileEntity->localFlag)) {
                int item = get_item_for_global_flag_with_default(local2global(tileEntity->localFlag), get_item_from_value_and_subvalue(tileEntity->_2, tileEntity->_3));
                //set_item_global_flag(local2global(t->localFlag));
                CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
                return;
            }
        }
    }
}
