#include <room.h>
#include <sound.h>
#include <save.h>
#include <manager/holeManager.h>

#include "checkIds/protocol.h"

extern void (*const gUnk_0811E7C4[])(s32);

extern const u32 n_entrances;
extern const u32 entrances[];

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
    u8 spawn_type;
    u8 start_anim;
} ToSwap;

typedef struct {
    u32 id;
    Position from;
    ToSwap swap;
} Send;

extern void lookup(Send*);

void lookup(Send* toSend) {
    
    u32 data_addr = toSend->id & 0x00ffffff;

    u8 from_area = toSend->from.area;
    u8 from_room = toSend->from.room;
    u16 from_x = toSend->from.x & 0xFFF;
    u16 from_y = toSend->from.y & 0xFFF;

    u8 to_area = toSend->swap.to.area;
    u8 to_room = toSend->swap.to.room;
    u16 to_x = toSend->swap.to.x;
    u16 to_y = toSend->swap.to.y;

    protocol_send(packet(10, data_addr));
    protocol_send(packet(11, from_area << 16 | from_room << 8 | toSend->from.layer));
    protocol_send(packet(12, from_x << 12 | from_y));
    protocol_send(packet(13, to_area << 16 | to_room << 8 | toSend->swap.to.layer));
    protocol_send(packet(14, to_x));
    protocol_send(packet(15, to_y));
    protocol_send(packet(16, toSend->swap.tile_type));
    protocol_send(packet(17, toSend->swap.start_anim << 8 | toSend->swap.spawn_type));

    u32 r = protocol_recv(FALSE);
    while (packet_type(r) != 13)
    {
        protocol_nack(r);
        r = protocol_recv(FALSE);
    }
    r = packet_value(r);
    toSend->swap.to.area = r >> 16;
    toSend->swap.to.room = r >> 8;
    toSend->swap.to.layer = r;

    r = protocol_recv(FALSE);
    while (packet_type(r) != 14)
    {
        protocol_nack(r);
        r = protocol_recv(FALSE);
    }
    r = packet_value(r);
    to_x = r;

    r = protocol_recv(FALSE);
    while (packet_type(r) != 15)
    {
        protocol_nack(r);
        r = protocol_recv(FALSE);
    }
    r = packet_value(r);
    to_y = r;

    r = protocol_recv(FALSE);
    while (packet_type(r) != 16)
    {
        protocol_nack(r);
        r = protocol_recv(FALSE);
    }
    r = packet_value(r);
    toSend->swap.tile_type = r;

    r = protocol_recv(FALSE);
    while (packet_type(r) != 17)
    {
        protocol_nack(r);
        r = protocol_recv(FALSE);
    }
    r = packet_value(r);
    toSend->swap.start_anim = r >> 8;
    toSend->swap.spawn_type = r;

    toSend->swap.to.x = to_x;
    toSend->swap.to.y = to_y;
}

void fillFrom(Send* toSend) {
    toSend->from.area = gRoomControls.area;
    toSend->from.room = gRoomControls.room;
    toSend->from.x = gRoomControls.camera_target->x.HALF.HI;
    toSend->from.y = gRoomControls.camera_target->y.HALF.HI;
    toSend->from.layer = gRoomControls.camera_target->collisionLayer;
    toSend->swap.tile_type = gRoomTransition.stairs_idx;
}

void readTo(ToSwap* swap) {
    PlayerRoomStatus* status;
    status = &gRoomTransition.player_status;
    status->area_next = swap->to.area;
    status->room_next = swap->to.room;
    status->start_pos_x = swap->to.x;
    status->start_pos_y = swap->to.y;
    status->layer = swap->to.layer;
    status->spawn_type = swap->spawn_type;
    status->start_anim = swap->start_anim;
    gRoomTransition.stairs_idx = swap->tile_type;
}

void DoExitTransition(const ScreenTransitionData* data) {
    Send toSend;

    const ScreenTransitionData* warp = data;

    gRoomTransition.transitioningOut = 1;
    if (warp->playerXPos <= 0x3ff) {
        toSend.swap.to.x = warp->playerXPos;
    } else {
        toSend.swap.to.x = (gRoomControls.camera_target)->x.HALF.HI | 0x8000;
    }
    if (warp->playerYPos <= 0x3ff) {
        toSend.swap.to.y = warp->playerYPos;
    } else {
        toSend.swap.to.y = (gRoomControls.camera_target)->y.HALF.HI | 0x8000;
    }
    toSend.id = (u32) data;
    toSend.swap.to.area = data->area;
    toSend.swap.to.room = data->room;
    toSend.swap.to.layer = data->playerLayer;
    toSend.swap.spawn_type = data->spawn_type;
    toSend.swap.start_anim = data->playerState;
    fillFrom(&toSend);
    if ((u32) data >= 0x08000000) {
        lookup(&toSend);
    }
    readTo(&toSend.swap);
    if (warp->transitionSFX != SFX_NONE) {
        SoundReq(warp->transitionSFX);
    }
    gUnk_0811E7C4[warp->type](warp->field_0xa);
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

//sub_0805B210
void sub_0805B210(HoleManager* this) {
    Send toSend;
    struct_08108764* tmp;
    gRoomTransition.transitioningOut = 1;
    gRoomTransition.type = TRANSITION_CUT;
    toSend.swap.start_anim = 4;
    tmp = &gUnk_08108764[super->type];
    toSend.swap.to.area = tmp->unk_01;
    toSend.swap.to.room = tmp->unk_02;
    toSend.swap.to.layer = tmp->unk_03;
    if (gPlayerState.flags & PL_MINISH) {
        toSend.swap.spawn_type = PL_SPAWN_DROP_MINISH;
    } else {
        toSend.swap.spawn_type = PL_SPAWN_DROP;
    }
    switch (tmp->unk_00) {
        case 0:
            toSend.swap.to.x = tmp->unk_04;
            toSend.swap.to.y = tmp->unk_06;
            break;
        case 1:
            toSend.swap.to.x =
                gPlayerEntity.base.x.HALF.HI - gRoomControls.origin_x + tmp->unk_04;
            toSend.swap.to.y =
                gPlayerEntity.base.y.HALF.HI - gRoomControls.origin_y + tmp->unk_06;
            break;
        case 2:
            toSend.swap.to.x = tmp->unk_04;
            toSend.swap.to.y = tmp->unk_06;
            toSend.swap.spawn_type = PL_SPAWN_DROP_MINISH;
            break;
    }

    fillFrom(&toSend);
    lookup(&toSend);
    readTo(&toSend.swap);
}
