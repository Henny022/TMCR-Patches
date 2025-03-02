#include <entity.h>
#include <flags.h>
#include <item.h>
#include <collision.h>
#include "base.h"

extern void sub_08080CB4(Entity*);

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u8 unused1[28];
    /*0x84*/ u16 unk_84;
    /*0x86*/ u16 unk_86;
} HeartContainerEntity;

void HeartContainer_Action3(HeartContainerEntity* this) {
    sub_08080CB4(super);
    if (!(gPlayerState.flags & PL_MINISH) && IsCollidingPlayer(super)) {
        u32 item = get_item_for_global_flag_with_default(flag2global(this->unk_84), ITEM_HEART_CONTAINER);
        SetFlag(this->unk_84);
        CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
        DeleteThisEntity();
    }
}
