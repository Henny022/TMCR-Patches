#include <object.h>
#include <room.h>
#include "base.h"

extern Entity* GetEmptyEntityByKind(u32 kind);
extern void RegisterRoomEntity(Entity*, const EntityData*);
extern void sub_0804AF0C(Entity*, const EntityData*);

Entity* LoadRoomEntity(const EntityData* dat) {
    int kind;
    Entity* entity;

    kind = dat->kind & 0xF;
    if ((dat->flags & 0xF0) == 0x50 && DeepFindEntityByID(kind, dat->id))
        return NULL;
    entity = GetEmptyEntityByKind(kind);
    if (entity != NULL) {
        entity->kind = kind;
        entity->id = dat->id;
        if(entity->kind == OBJECT && entity->id == GROUND_ITEM)
        {
            int flag = flag2global(dat->spritePtr >> 16);
            if (flag == -1)
            {
                entity->type = dat->type;
            }
            else
            {
                int item = get_item_for_global_flag(flag);
                entity->type = get_item_id(item);
            }
        }
        else
        {
            entity->type = dat->type;
        }
        RegisterRoomEntity(entity, dat);
        if ((dat->flags & 0xF0) != 16) {
            u8 kind2;
            if(entity->kind == OBJECT && entity->id == GROUND_ITEM)
            {
                int flag = flag2global(dat->spritePtr >> 16);
                if(flag == -1)
                {
                    entity->type2 = *(u8*)&dat->type2;
                }
                else
                {
                    int item = get_item_for_global_flag(flag);
                    entity->type2 = get_item_subvalue(item);
                }
            }
            else
            {
                entity->type2 = *(u8*)&dat->type2;
            }
            entity->type2 = *(u8*)&dat->type2;
            entity->timer = (dat->type2 & 0xFF00) >> 8;
            if (kind == 9)
                return entity;
            sub_0804AF0C(entity, dat);
            if (!entity->next)
                return entity;
            kind2 = dat->kind & 0xF0;
            if ((kind2 & 0x10) == 0) {
                if ((kind2 & 0x20) != 0) {
                    entity->collisionLayer = 2;
                    return entity;
                }
            }

            if ((kind2 & 0x10) || (gRoomControls.scroll_flags & 2)) {
                entity->collisionLayer = 1;
                return entity;
            }

            ResolveCollisionLayer(entity);
            return entity;
        }
    }
    return entity;
}

void sub_08081404(Entity* this, u32 arg1) {
    if (arg1 && this->field_0x86.HWORD) {
        int flag = flag2global(this->field_0x86.HWORD);
        if (flag == -1)
            SetFlag(this->field_0x86.HWORD);
        else
            set_item_global_flag(flag);
    }

    DeleteThisEntity();
}
