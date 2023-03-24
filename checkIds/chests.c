#include <room.h>
#include <sound.h>
#include <item.h>
#include <flags.h>
#include "base.h"

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
            u16 check_id = t->_2 | (t->_3<<8);
            u16 item = get_item_for_check_id(check_id);
            SetLocalFlag(t->localFlag);
            CreateItemEntity(item & 0xff, (item >> 8)&0xff, 0);
        } else {
            CreateItemEntity(ITEM_FAIRY, 0, 0);
        }
        sub_0807B7D8(0x74, pos, layer);
        RequestPriorityDuration(NULL, 120);
        SoundReq(SFX_CHEST_OPEN);
    }
}
