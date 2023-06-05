#define NENT_DEPRECATED
#include <area.h>
#include <message.h>
#include <object.h>
#include <screen.h>
#include <script.h>
#include <item.h>
#include <room.h>
#include <flags.h>

#include "base.h"

#define CUSTOM_FLAG_PICKED_UP_JABBERNUT_CHECK 2580

extern void sub_0801AFE4(void);
extern u32 sub_08060354(void);

extern EntityData gUnk_080DAB44;
extern EntityData gUnk_080DAB64;
extern EntityData gUnk_080DAB84;
extern EntityData gUnk_080DAC54;
extern EntityData gUnk_080DAD24;
extern EntityData gUnk_080DABC4;
extern EntityData gUnk_080DAC94;
extern EntityData gUnk_080DAD64;
extern EntityData gUnk_080DAC04;
extern EntityData gUnk_080DACD4;
extern EntityData gUnk_080DADA4;

void sub_StateChange_MinishHouseInteriors_BarrelMinish(void) {
    u32 uVar1;

    if (!CheckGlobalFlag(CUSTOM_FLAG_PICKED_UP_JABBERNUT_CHECK))
        LoadRoomEntityList(&gUnk_080DAB44);
    else
        LoadRoomEntityList(&gUnk_080DAB64);

    if (CheckGlobalFlag(DRUG_COUNT) && sub_08060354()) {
        SetRoomFlag(0);
        if (!CheckGlobalFlag(DRUG_1))
            uVar1 = 0x3200;
        else if (!CheckGlobalFlag(DRUG_2))
            uVar1 = 0x4600;
        else
            uVar1 = 0x4880;
    } else {
        if (CheckGlobalFlag(DRUG_3))
            uVar1 = 0x4900;
        else if (CheckGlobalFlag(DRUG_2))
            uVar1 = 0x4a00;
        else if (CheckGlobalFlag(DRUG_1))
            uVar1 = 0x5200;
        else
            uVar1 = 0x9200;
    }
    if (uVar1 & 0x8000)
        LoadRoomEntityList(&gUnk_080DAB84);

    if (uVar1 & 0x4000)
        LoadRoomEntityList(&gUnk_080DAC54);

    if (uVar1 & 0x2000)
        LoadRoomEntityList(&gUnk_080DAD24);

    if (uVar1 & 0x1000)
        LoadRoomEntityList(&gUnk_080DABC4);

    if (uVar1 & 0x800)
        LoadRoomEntityList(&gUnk_080DAC94);

    if (uVar1 & 0x400)
        LoadRoomEntityList(&gUnk_080DAD64);

    if (uVar1 & 0x200)
        LoadRoomEntityList(&gUnk_080DAC04);

    if (uVar1 & 0x100)
        LoadRoomEntityList(&gUnk_080DACD4);

    if (uVar1 & 0x80)
        LoadRoomEntityList(&gUnk_080DADA4);

    sub_0801AFE4();
}

typedef struct {
    Entity base;
    u16 px, py, pz;
    u8 off;
    u8 fill[0x14];
    void* ctx;
} CutsceneMiscObjectEntity;

extern void sub_08080CB4(Entity*);

void sub_08095088(CutsceneMiscObjectEntity* this) {
    u32 tmp;

    switch (super->action) {
        case 0:
            if (CheckGlobalFlag(CUSTOM_FLAG_PICKED_UP_JABBERNUT_CHECK))
                DeleteThisEntity();
            super->action = 1;
            super->spritePriority.b0 = 7;
            sub_080787B4(super);
            break;
        case 1:
            if (super->interactType != 0) {
                super->interactType = 0;
                super->action = 2;
                sub_080788E0(super);
                CreateEzloHint(TEXT_INDEX(TEXT_BELARI, 0x1F), 0);
            }
            break;
        case 2:
            if ((gMessage.doTextBox & 0x7F) == 0) {
                int item = get_item_for_global_flag_with_default(CUSTOM_FLAG_PICKED_UP_JABBERNUT_CHECK, ITEM_JABBERNUT);
                CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
                SetGlobalFlag(CUSTOM_FLAG_PICKED_UP_JABBERNUT_CHECK);
                DeleteThisEntity();
            }
            break;
    }
    tmp = super->type;
    super->type = 91;
    sub_08080CB4(super);
    super->type = tmp;
}