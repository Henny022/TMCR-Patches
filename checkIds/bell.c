#define NENT_DEPRECATED
#include <manager/hyruleTownBellManager.h>
#include <object.h>
#include <player.h>
#include <room.h>
#include <sound.h>
#include <item.h>

#include "base.h"


typedef struct {
    Entity base;
    u8 unk68;
    u8 unk69;
    u8 fhgg;
    u16 despawnTimer;
    u16 tileType;
    u16 filler[11];
    u16 flag;
} ItemOnGroundEntity;

void HyruleTownBellManager_Main(HyruleTownBellManager* this) {
    RoomControls* roomControls = &gRoomControls;
    u32 a = roomControls->origin_x + 0x1f8;
    u32 x = (a - gPlayerEntity.base.x.HALF.HI) + 0x10;
    u32 b = roomControls->origin_y + 0x140;
    u32 y = (b - gPlayerEntity.base.y.HALF.HI) + 0x10;
    if (super->action == 0) {
        if (x < 0x20 && y < 0x20 && gPlayerEntity.base.z.HALF.HI < -0x18 && gPlayerState.framestate == PL_STATE_CAPE) {
            super->action++;
            super->timer = 90;
            SoundReq(SFX_10A);
        }
    } else {
        if (--super->timer == 0) {
            {
                int flag = local2global(MACHI_07_BELL);
                int item = peek_item_for_global_flag_with_default(flag, ITEM_HEART_PIECE);
                ItemOnGroundEntity* object = (ItemOnGroundEntity*) CreateObject(GROUND_ITEM, get_item_id(item), get_item_subvalue(item));
                if (object != NULL) {
                    object->flag = MACHI_07_BELL;
                    object->base.x.HALF.HI = roomControls->origin_x + 0x1f8;
                    object->base.y.HALF.HI = roomControls->origin_y + 0x140;
                    object->base.z.HALF.HI = -24;
                }
            }
            DeleteThisEntity();
        }
    }
}