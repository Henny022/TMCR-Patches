#include <room.h>
#include <sound.h>
#include <save.h>
#include <area.h>
#include <common.h>
#include <tiles.h>
#include <game.h>
#include <main.h>
#include <manager/holeManager.h>

#include "network/network.h"
#include "debug/mgba.h"

extern void (*const gUnk_0811E7C4[])(s32);

extern const u32 n_entrances;
extern const u32 entrances[];


//extern u32 exit_transition_handle;
#define exit_transition_handle (*(u32*)0x02038620)

typedef struct {
    u8 area;
    u8 room;
    u8 layer;
    s16 x;
    s16 y;
} Position;

typedef struct {
    Position to;
    u16 tile_type;
    u8 start_anim;
    u8 spawn_type;
} ToSwap;

typedef struct {
    u32 id;
    Position from;
    ToSwap swap;
} Send;

void write_swap(u32 id) {
    if (exit_transition_handle) {
        mgba_print(LOG_ERROR, "hey, wtf? e0ee7638-24ed-4e17-93fe-41c73e877b8d");
        return;
    }
    Send toSend;
    toSend.id = id;
    toSend.swap.to.x = gRoomTransition.player_status.start_pos_x;
    toSend.swap.to.y = gRoomTransition.player_status.start_pos_y;
    toSend.swap.to.area = gRoomTransition.player_status.area_next;
    toSend.swap.to.room = gRoomTransition.player_status.room_next;
    toSend.swap.to.layer = gRoomTransition.player_status.layer;
    toSend.swap.spawn_type = gRoomTransition.player_status.spawn_type;
    toSend.swap.start_anim = gRoomTransition.player_status.start_anim;
    toSend.from.area = gRoomControls.area;
    toSend.from.room = gRoomControls.room;
    toSend.from.x = gRoomControls.camera_target->x.HALF.HI;
    toSend.from.y = gRoomControls.camera_target->y.HALF.HI;
    toSend.from.layer = gRoomControls.camera_target->collisionLayer;
    toSend.swap.tile_type = gRoomTransition.stairs_idx;

    mgba_print(LOG_DEBUG, "entrance lookup");
    exit_transition_handle = send(0xfu, 3, sizeof(Send), &toSend);
}

void read_swap() {
    if (exit_transition_handle) {
        await_send(exit_transition_handle);
        ToSwap swap;
        u8 sender;
        recv_blocking(3, &sender, sizeof(ToSwap), &swap);
        PlayerRoomStatus* status;
        status = &gRoomTransition.player_status;
        status->area_next = swap.to.area;
        status->room_next = swap.to.room;
        status->start_pos_x = swap.to.x;
        status->start_pos_y = swap.to.y;
        status->layer = swap.to.layer;
        status->spawn_type = swap.spawn_type;
        status->start_anim = swap.start_anim;
        gRoomTransition.stairs_idx = swap.tile_type;
        exit_transition_handle = 0;
    }
}

void DoExitTransition(const ScreenTransitionData* data) {
    PlayerRoomStatus* status;
    gRoomTransition.transitioningOut = 1;
    status = &gRoomTransition.player_status;
    if ((u16)data->playerXPos <= 0x3ff) {
        status->start_pos_x = data->playerXPos;
    } else {
        status->start_pos_x = (gRoomControls.camera_target)->x.HALF.HI | 0x8000;
    }
    if ((u16)data->playerYPos <= 0x3ff) {
        status->start_pos_y = data->playerYPos;
    } else {
        status->start_pos_y = (gRoomControls.camera_target)->y.HALF.HI | 0x8000;
    }
    status->area_next = data->area;
    status->room_next = data->room;
    status->layer = data->playerLayer;
    status->spawn_type = data->spawn_type;
    status->start_anim = data->playerState;
    if (!gRoomTransition.player_status.spawn_type) {
        switch (gRoomTransition.stairs_idx) {
            case TILE_TYPE_145:
            case TILE_TYPE_147:
            case TILE_TYPE_149:
            case TILE_TYPE_151:
                gRoomTransition.player_status.spawn_type = PL_SPAWN_STAIRS_ASCEND;
                break;
            case TILE_TYPE_146:
            case TILE_TYPE_148:
            case TILE_TYPE_150:
            case TILE_TYPE_152:
                gRoomTransition.player_status.spawn_type = PL_SPAWN_STAIRS_DESCEND;
                break;
            default:
                break;
        }
    }

    if ((u32) data >= 0x08000000) {
        write_swap((u32) data);
    }
    if (data->transitionSFX != SFX_NONE) {
        SoundReq(data->transitionSFX);
    }
    gUnk_0811E7C4[data->type](data->field_0xa);
}


typedef struct struct_08108764 {
    u8 unk_00;
    u8 unk_01; // area ID?
    u8 unk_02; // room ID?
    u8 unk_03; // layer?
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0a;
    u8 unk_0b;
    struct {
        u32 unk_00;
        u16 unk_04;
        u16 unk_06;
        u16 unk_08;
        u16 unk_0a;
    } * unk_0c;
    struct {
        u8 unk_00;
        u8 unk_01;
        u8 unk_02[2];
        u16 unk_04;
        u16 unk_06;
    } * unk_10;
} struct_08108764;

extern struct_08108764 gUnk_08108764[];

void sub_0805B210(HoleManager* this) {
    struct_08108764* tmp;
    gRoomTransition.transitioningOut = 1;
    gRoomTransition.type = TRANSITION_CUT;
    gRoomTransition.player_status.start_anim = 4;
    tmp = &gUnk_08108764[super->type];
    gRoomTransition.player_status.area_next = tmp->unk_01;
    gRoomTransition.player_status.room_next = tmp->unk_02;
    gRoomTransition.player_status.layer = tmp->unk_03;
    if (gPlayerState.flags & PL_MINISH) {
        gRoomTransition.player_status.spawn_type = PL_SPAWN_DROP_MINISH;
    } else {
        gRoomTransition.player_status.spawn_type = PL_SPAWN_DROP;
    }
    switch (tmp->unk_00) {
        case 0:
            gRoomTransition.player_status.start_pos_x = tmp->unk_04;
            gRoomTransition.player_status.start_pos_y = tmp->unk_06;
            break;
        case 1:
            gRoomTransition.player_status.start_pos_x =
                gPlayerEntity.base.x.HALF.HI - gRoomControls.origin_x + tmp->unk_04;
            gRoomTransition.player_status.start_pos_y =
                gPlayerEntity.base.y.HALF.HI - gRoomControls.origin_y + tmp->unk_06;
            break;
        case 2:
            gRoomTransition.player_status.start_pos_x = tmp->unk_04;
            gRoomTransition.player_status.start_pos_y = tmp->unk_06;
            gRoomTransition.player_status.spawn_type = PL_SPAWN_DROP_MINISH;
            break;
    }
    if ((u32) tmp >= 0x08000000) {
        write_swap((u32) tmp);
    }
}

extern void SetBGDefaults(void);
extern void ClearTileMaps(void);
extern void sub_0806FD8C(void);

void GameTask_Init(void) {
    DispReset(1);
    gFadeControl.mask = 0xffffffff;
    MemClear(&gOAMControls, 0xB74);
    MemClear(&gUI, sizeof(gUI));
    EraseAllEntities();
    SetBGDefaults();
    ClearTileMaps();
    ResetPalettes();
    ResetPaletteTable(1);
    sub_0806FD8C();
    
    read_swap();

    gRoomControls.area = gRoomTransition.player_status.area_next;
    gRoomControls.room = gRoomTransition.player_status.room_next;
    LoadGfxGroups();
    gGFXSlots.unk0 = 1;
    gMain.state = GAMETASK_MAIN;
}
