#include <room.h>
#include <sound.h>
#include <save.h>

#include "debug/mgba.h"
#include "checkIds/protocol.h"

extern void (*const gUnk_0811E7C4[])(s32);

extern const u32 n_entrances;
extern const u32 entrances[];

char digit(int d) {
    if (d < 10)
    {
        return '0' + d;
    }
    return 'a' + d - 10;
}

void print(const ScreenTransitionData* data, u16 to_x, u16 to_y) {
    u32 data_addr = (u32) data;

    u8 from_area = gRoomTransition.player_status.area_next;
    u8 from_room = gRoomTransition.player_status.room_next;
    u16 from_x = gRoomControls.camera_target->x.HALF.HI | 0x8000;
    u16 from_y = gRoomControls.camera_target->y.HALF.HI | 0x8000;

    u8 to_area = data->area;
    u8 to_room = data->room;

    char buffer[] = "transition xxxxxx from xx.xx@xx:xx to xx.xx@xx:xx";
    buffer[11] = digit((data_addr >> 20) & 0xf);
    buffer[12] = digit((data_addr >> 16) & 0xf);
    buffer[13] = digit((data_addr >> 12) & 0xf);
    buffer[14] = digit((data_addr >> 8) & 0xf);
    buffer[15] = digit((data_addr >> 4) & 0xf);
    buffer[16] = digit((data_addr >> 0) & 0xf);

    buffer[23] = digit((from_area >> 4) & 0xf);
    buffer[24] = digit((from_area >> 0) & 0xf);

    buffer[26] = digit((from_room >> 4) & 0xf);
    buffer[27] = digit((from_room >> 0) & 0xf);

    buffer[29] = digit((from_x >> 8) & 0xf);
    buffer[30] = digit((from_x >> 4) & 0xf);

    buffer[32] = digit((from_y >> 8) & 0xf);
    buffer[33] = digit((from_y >> 4) & 0xf);

    buffer[38] = digit((to_area >> 4) & 0xf);
    buffer[39] = digit((to_area >> 0) & 0xf);

    buffer[41] = digit((to_room >> 4) & 0xf);
    buffer[42] = digit((to_room >> 0) & 0xf);

    buffer[44] = digit((to_x >> 8) & 0xf);
    buffer[45] = digit((to_x >> 4) & 0xf);

    buffer[47] = digit((to_y >> 8) & 0xf);
    buffer[48] = digit((to_y >> 4) & 0xf);

    mgba_print(LOG_INFO, buffer);
}

const ScreenTransitionData* lookup_p(const ScreenTransitionData* warp) {
    u32 data_addr = (u32) warp;

    u8 from_area = gRoomTransition.player_status.area_next;
    u8 from_room = gRoomTransition.player_status.room_next;
    u16 from_x = gRoomControls.camera_target->x.HALF.HI | 0x8000;
    u16 from_y = gRoomControls.camera_target->y.HALF.HI | 0x8000;

    u8 to_area = warp->area;
    u8 to_room = warp->room;

}

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
    print(data, status->start_pos_x, status->start_pos_y);
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
