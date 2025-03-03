#include "room.h"
#include "sound.h"
extern void (*const gUnk_0811E7C4[])(s32);

extern const u32 n_entrances;
extern const u32 entrances[];

const ScreenTransitionData* lookup(const ScreenTransitionData* warp) {
    u32 warp_addr = (u32) warp;
    if (warp_addr < 0x08000000) {
        return warp;
    }
    warp_addr = warp_addr & 0x00ffffff;
    for (u32 i = 0; i < n_entrances; i++){
        if (warp_addr == entrances[i*2]) {
            warp_addr = entrances[i*2+1];
            break;
        }
    }
    warp_addr = 0x08000000 | warp_addr;
    return (const ScreenTransitionData*) warp_addr;
}

void DoExitTransition(const ScreenTransitionData* data) {
    PlayerRoomStatus* status;

    const ScreenTransitionData* warp = data;
    const ScreenTransitionData* target = lookup(warp);

    gRoomTransition.transitioningOut = 1;
    status = &gRoomTransition.player_status;
    if (target->playerXPos <= 0x3ff) {
        status->start_pos_x = target->playerXPos;
    } else {
        status->start_pos_x = (gRoomControls.camera_target)->x.HALF.HI | 0x8000;
    }
    if (target->playerYPos <= 0x3ff) {
        status->start_pos_y = target->playerYPos;
    } else {
        status->start_pos_y = (gRoomControls.camera_target)->y.HALF.HI | 0x8000;
    }
    status->area_next = target->area;
    status->room_next = target->room;
    status->layer = target->playerLayer;
    status->spawn_type = target->spawn_type;
    status->start_anim = target->playerState;
    if (warp->transitionSFX != SFX_NONE) {
        SoundReq(warp->transitionSFX);
    }
    gUnk_0811E7C4[warp->type](warp->field_0xa);
}
