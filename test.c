#include <global.h>
#include <save.h>
#include <screenTransitions.h>
#include <area.h>
#include <roomid.h>
#include <game.h>

void UpdateGlobalProgress(void) {
    gSave.global_progress = 7;
}

u32 sub_unk3_HyruleField_OutsideCastle(void) {
    return 1;
}

const ScreenTransitionData gUnk_0813AC20 = { 1, { 0, 0, 0, 0 }, 0x198, 0x38, 0, AREA_DARK_HYRULE_CASTLE, ROOM_DARK_HYRULE_CASTLE_B1_MAP, 1, 0, 0, 0 };

// small key TODO fix after merge
bool32 HasDungeonMap(void) {
    return AreaHasKeys();
}

//big key TODO fix after merge
bool32 HasDungeonCompass(void) {
    return AreaHasKeys();
}

void ModDungeonKeys(s32 keys) {
    (void)keys;
}
