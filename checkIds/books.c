#include <entity.h>
#include <object.h>
#include <room.h>
#include <item.h>
#include "base.h"
#include <object/itemOnGround.h>

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u8 unused1[24];
    /*0x80*/ u8 unk_80;
    /*0x81*/ u8 unused2[5];
    /*0x86*/ u16 unk_86;
} BookEntity;


void Book_Init(BookEntity* this) {
    u32 obtained = GetInventoryValue(super->type + ITEM_QST_BOOK1);
    if (super->type2 != 3) {
        if (obtained != 0) {
            DeleteThisEntity();
        }
    } else {
        if (CheckLocalFlag(MIZUKAKI_BOOK_ALLBACK)) {
            DeleteThisEntity();
        }

        if (obtained != 2) {
            super->spriteSettings.draw = 0;
        }
    }

    super->spriteOffsetY = 3;
    if (CheckFlags(this->unk_86)) {
        if (super->type2 == 0) {
            super->y.HALF.HI += 48;
        }
        int flag = 2574 + super->type;
        int item = peek_item_for_global_flag_with_default(flag, super->type + ITEM_QST_BOOK1);
        ItemOnGroundEntity* ent = (ItemOnGroundEntity*) CreateObject(GROUND_ITEM, get_item_id(item), get_item_subvalue(item));
        if (ent) {
            ent->unk_86 = flag;
            CopyPosition(super, (Entity*)ent);
            DeleteThisEntity();
        }
    }

    UpdateSpriteForCollisionLayer(super);
    InitAnimationForceUpdate(super, super->type + ITEM_QST_BOOK1);

    switch (super->type2) {
        case 0:
            super->action = 1;
            super->timer = 22;
            super->subtimer = 2;
            this->unk_80 = 0;
            super->spritePriority.b0 = 3;
            break;
        case 1: {
            u32 scroll;
            u32 height;

            super->action = 3;
            scroll = (u16)gRoomControls.scroll_y - 0x10;
            height = (u16)super->y.HALF.HI - scroll;
            super->z.HALF.HI -= height;
            break;
        }
        case 2:
            super->action = 4;
            break;
        case 3:
            super->action = 5;
            super->subAction = 0;
            super->spritePriority.b0 = 3;
            break;
        default:
            break;
    }
}
