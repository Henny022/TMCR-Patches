#define NENT_DEPRECATED
#include <flags.h>
#include <entity.h>
#include <kinstone.h>
#include <collision.h>
#include <global.h>
#include <hitbox.h>
#include <item.h>
#include <object.h>
#include <subtask.h>

#include "base.h"

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u8 unk_68[0xc];
    /*0x74*/ u16 unk_74;
    /*0x76*/ u16 unk_76;
    /*0x78*/ u8 unk_78[0xf];
    /*0x87*/ u8 unk_87;
} ObjectA8Entity;

extern void sub_08080CB4(Entity*);
extern void sub_0809FECC(ObjectA8Entity*);
extern bool32 sub_0809FE9C(ObjectA8Entity*);
extern void ObjectA8_Init(ObjectA8Entity*);
extern void ObjectA8_Action1(ObjectA8Entity*);
extern void ObjectA8_Action2(ObjectA8Entity*);
extern void ObjectA8_Action3(ObjectA8Entity*);
extern void ObjectA8_Action4(ObjectA8Entity*);
extern void ObjectA8_Action5(ObjectA8Entity*);
extern void ObjectA8_Action6(ObjectA8Entity*);
extern void ObjectA8_Action2Subaction0(ObjectA8Entity*);
extern void ObjectA8_Action2Subaction1(ObjectA8Entity*);
extern void ObjectA8_Action2Subaction2(ObjectA8Entity*);

void ObjectA8(ObjectA8Entity* this) {
    static void (*const ObjectA8_Actions[])(ObjectA8Entity*) = {
        ObjectA8_Init,    ObjectA8_Action1, ObjectA8_Action2, ObjectA8_Action3,
        ObjectA8_Action4, ObjectA8_Action5, ObjectA8_Action6,
    };
    if ((super->contactFlags & 0x80) != 0) {
        switch (super->contactFlags & 0x7f) {
            case 0:
            case 1:
            case 4:
            case 5:
            case 6:
            case 8:
            case 9:
            case 10:
            case 0xb:
            case 0xc:
            case 0x1e:
            case 0x1f:
                super->action = 5;
                super->child = &gPlayerEntity;
                {
                    int flag = super->type - ITEM_ARROW_BUTTERFLY + 2577;
                    int item = get_item_for_global_flag_with_default(flag, super->type);
                    CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
                    SetGlobalFlag(flag);
                }
                DeleteThisEntity();
        }
    }
    ObjectA8_Actions[super->action](this);
    sub_08080CB4(super);
}

extern void sub_0801876C(u32 worldEventId, bool32 isKinstoneFused);
extern void sub_080189EC(u32 worldEventId);
extern void sub_08018A58(u32 worldEventId);
extern void sub_08018AB4(int);
extern void sub_08018B50(u32 worldEventId);
extern void sub_08018BB4(u32 worldEventId);

extern const EntityData gUnk_080FEBE8[];
extern const EntityData gUnk_080FEC28[];
extern const EntityData gUnk_080FECC8[];
extern const EntityData gUnk_080FED18[];
extern const EntityData gUnk_080FED58[];
extern const void* gUnk_080FED98[];
extern const EntityData gUnk_080FEE18[];
extern const EntityData gUnk_080FEE38[];
extern const EntityData gUnk_080FEE48[];
extern const EntityData gUnk_080FEE58[];
extern const EntityData gUnk_080FEE78[];

void sub_0801876C(u32 worldEventId, bool32 isKinstoneFused) {
    Entity* roomEnt;
    Entity* ent;
    u32 uVar3;
    u32 uVar5;
    const WorldEvent* ptr;

    ptr = &gWorldEvents[worldEventId];
    switch (ptr->type) {
        case WORLD_EVENT_TYPE_6:
            if (isKinstoneFused == 0) {
                sub_08018AB4((ptr->x >> 4 & 0x3f) | (ptr->y >> 4 & 0x3f) << 6);
            }
            break;
        case WORLD_EVENT_TYPE_0:
            break;
        case WORLD_EVENT_TYPE_2:
            if (isKinstoneFused != 0) {
                sub_08018BB4(worldEventId);
            }
            break;
        case WORLD_EVENT_TYPE_1:
            if (isKinstoneFused == 0) {
                return;
            }
            if (CheckGlobalFlag(ptr->flag)) {
                return;
            }
            LoadRoomEntity(gUnk_080FEC28 + ptr->entity_idx);
            break;
        case WORLD_EVENT_TYPE_3:
            if (isKinstoneFused == 0) {
                return;
            }
            {
                int flag = 2577 + ptr->entity_idx;
                if (CheckGlobalFlag(flag)) {
                    return;
                }
                LoadRoomEntity(gUnk_080FEBE8 + ptr->entity_idx);
            }
            break;
        case WORLD_EVENT_TYPE_4:
            if (isKinstoneFused == 0) {
                sub_08018A58(worldEventId);
            }
            break;
        case WORLD_EVENT_TYPE_5:
            if (isKinstoneFused != 0) {
                sub_08018B50(worldEventId);
            }
            break;

        case WORLD_EVENT_TYPE_7:
            if (isKinstoneFused != 0) {
                return;
            }
            if (ptr->entity_idx != 0x80) {
                LoadRoomEntity(gUnk_080FECC8 + ptr->entity_idx);
            } else {
                sub_080189EC(worldEventId);
            }
            break;
        case WORLD_EVENT_TYPE_25:
            roomEnt = LoadRoomEntity(&gUnk_080FED18[ptr->entity_idx]);
            if (roomEnt != 0) {
                roomEnt->type = isKinstoneFused ? 2 : 0;
            }
            break;
        case WORLD_EVENT_TYPE_8:
            if (isKinstoneFused == 0) {
                return;
            }
            SetTileType(0x168, (ptr->x >> 4 & 0x3f) | (ptr->y >> 4 & 0x3f) << 6, 1);
            break;
        case WORLD_EVENT_TYPE_11:
            if (isKinstoneFused != 0) {
                LoadRoomEntity(&gUnk_080FED58[ptr->entity_idx]);
                gRoomVars.field_0x8c[ptr->entity_idx] = (void*)gUnk_080FED98[ptr->entity_idx];
            }
            break;
        case WORLD_EVENT_TYPE_9:
            if (isKinstoneFused == 0) {
                return;
            }
            ent = LoadRoomEntity(&gUnk_080FEE78[ptr->entity_idx]);
            if (ent != 0) {
                *(u16*)&ent->collisionLayer = ptr->x + gRoomControls.origin_x;
                *(u16*)&ent->gustJarState = ptr->y + gRoomControls.origin_y;
            }
            if (ptr->entity_idx == 0) {
                SetTileType(0x8d, (ptr->x >> 4 & 0x3f) | (ptr->y >> 4 & 0x3f) << 6, 1);
            } else {
                uVar5 = (ptr->x >> 4 & 0x3f) | (ptr->y >> 4 & 0x3f) << 6;
                SetTileType(0x8c, uVar5 - 1, 1);
                uVar3 = 0x8e;
                SetTileType(uVar3, uVar5, 1);
            }
            break;
        case WORLD_EVENT_TYPE_24:
            if (isKinstoneFused != 0) {
                LoadRoomEntityList(gUnk_080FEE18);
            }
            break;
        case WORLD_EVENT_TYPE_15:
            if (isKinstoneFused != 0) {
                LoadRoomEntity(gUnk_080FEE58);
            } else {
                LoadRoomEntity(gUnk_080FEE48);
            }
            break;
        case WORLD_EVENT_TYPE_17:
            if (isKinstoneFused != 0) {
                SetLocalFlagByBank(FLAG_BANK_1, SOUGEN_05_BOMB_00);
                LoadRoomEntityList(gUnk_080FEE38);
            }
            break;
        case WORLD_EVENT_TYPE_26:
        case WORLD_EVENT_TYPE_27:
        case WORLD_EVENT_TYPE_28:
            break;
    }
}