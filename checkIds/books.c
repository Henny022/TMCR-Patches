#include <entity.h>
#include <object.h>
#include <room.h>
#include <item.h>
#include "base.h"


void Book_Init(Entity* this) {
    u32 obtained = GetInventoryValue(this->type + ITEM_QST_BOOK1);
    if (this->type2 != 3) {
        if (obtained != 0) {
            DeleteThisEntity();
        }
    } else {
        if (CheckLocalFlag(MIZUKAKI_BOOK_ALLBACK)) {
            DeleteThisEntity();
        }

        if (obtained != 2) {
            this->spriteSettings.draw = 0;
        }
    }

    this->spriteOffsetY = 3;
    if (CheckFlags(this->field_0x86.HWORD)) {
        if (this->type2 == 0) {
            this->y.HALF.HI += 48;
        }
        int flag = 2574 + this->type;
        int item = peek_item_for_global_flag_with_default(flag, this->type + ITEM_QST_BOOK1);
        Entity* ent = CreateObject(GROUND_ITEM, get_item_id(item), get_item_subvalue(item));
        if (ent) {
            ent->field_0x86.HWORD = flag;
            CopyPosition(this, ent);
            DeleteThisEntity();
        }
    }

    UpdateSpriteForCollisionLayer(this);
    InitAnimationForceUpdate(this, this->type + ITEM_QST_BOOK1);

    switch (this->type2) {
        case 0:
            this->action = 1;
            this->timer = 22;
            this->subtimer = 2;
            this->field_0x80.HALF.LO = 0;
            this->spritePriority.b0 = 3;
            break;
        case 1: {
            u32 scroll;
            u32 height;

            this->action = 3;
            scroll = (u16)gRoomControls.scroll_y - 0x10;
            height = (u16)this->y.HALF.HI - scroll;
            this->z.HALF.HI -= height;
            break;
        }
        case 2:
            this->action = 4;
            break;
        case 3:
            this->action = 5;
            this->subAction = 0;
            this->spritePriority.b0 = 3;
            break;
        default:
            break;
    }
}
