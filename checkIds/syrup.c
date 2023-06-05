#include <room.h>
#include <common.h>
#include <flags.h>
#include <kinstone.h>

extern EntityData gUnk_080F9FA8;
extern EntityData gUnk_080F9F88;

void sub_StateChange_TreeInteriors_WitchHut(void) {
    if (CheckKinstoneFused(KINSTONE_14)) {
        LoadRoomEntityList(&gUnk_080F9FA8);
    }
    if (!CheckLocalFlagByBank(0xa00, 36)) {
        LoadRoomEntityList(&gUnk_080F9F88);
    }
}