#define NENT_DEPRECATED
#include <object.h>
#include <item.h>

#include "base.h"

typedef struct {
    Entity base;
    u16 px, py, pz;
    u8 off;
    u8 fill[0x14];
    void* ctx;
} CutsceneMiscObjectEntity;

void sub_08094FA8(CutsceneMiscObjectEntity* this) {
    switch (super->action) {
        case 0:
            super->action = 1;
            super->frameIndex = 0;
            super->spritePriority.b0 = 7;
            sub_080787B4(super);
            break;
        case 1:
            if (super->interactType != 0) {
                super->interactType = 0;
                super->action = 2;
                sub_080788E0(super);
                gPlayerState.queued_action = PLAYER_EMPTYBOTTLE;
                gPlayerState.field_0x38 = 54;
            }
            break;
        case 2:
            if (GetInventoryValue(ITEM_QST_DOGFOOD) == 2) {
                super->action = 3;
                super->spriteSettings.draw = 1;
            }
            break;
        case 3:
            if (gPlayerEntity.action != PLAYER_EMPTYBOTTLE) {
                super->action = 4;
                if (!CheckGlobalFlag(BIN_DOGFOOD)) {
                    int item = get_item_for_global_flag_with_default(BIN_DOGFOOD, ITEM_BOTTLE1);
                    CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
                    SetGlobalFlag(BIN_DOGFOOD);
                }
            }
            break;
    }
}