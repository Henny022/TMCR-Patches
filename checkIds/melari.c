#include <room.h>
#include <flags.h>
#include <message.h>
#include <item.h>

extern EntityData gUnk_additional_8_MelarisMine_Main;
extern EntityData gUnk_additional_9_MelarisMine_Main;
extern EntityData gUnk_080DD294;
extern EntityData melari_replacement_item_on_ground;

void sub_StateChange_MelarisMine_Main(void) {
    //make melari show up ~~all the time~~ never
    //LoadRoomEntityList(&gUnk_additional_8_MelarisMine_Main);
    if (CheckGlobalFlag(MACHI_SET_2)) {
        LoadRoomEntityList(&melari_replacement_item_on_ground);
    }
    if (!CheckLocalFlag(YAMAKOBITO_OPEN)) {
        LoadRoomEntityList(&gUnk_additional_9_MelarisMine_Main);
    } else {
        LoadRoomEntityList(&gUnk_080DD294);
    }
    SetLocalFlag(KOBITO_YAMA_ENTER);
}


extern const u16 gUnk_0811130E[][4];

void sub_08068190(Entity* this) {
    u32 uVar2;
    u32 uVar3;

    uVar3 = this->type2;
    if (uVar3 > 8) {
        uVar3 = 8;
    }

    uVar2 = 0;
    if (CheckLocalFlag(OYAKATA_DEMO)) {
        uVar2 = 1;
    }
    if (CheckGlobalFlag(MACHI_SET_2) != 0) {
        uVar2 = 2;
    }
    if (CheckLocalFlagByBank(0xa00, 37) != 0) {
        uVar2 = 3;
    }

    MessageNoOverlap(gUnk_0811130E[uVar3][uVar2], this);
}