#include <global.h>
#include <save.h>
#include <screenTransitions.h>
#include <area.h>
#include <roomid.h>
#include <game.h>
#include <item.h>
#include <flags.h>
#include <asm.h>
#include <kinstone.h>
#include <common.h>

void UpdateGlobalProgress(void) {
    gSave.global_progress = 7;
}

u32 sub_unk3_HyruleField_OutsideCastle(void) {
    return 1;
}

extern EntityData gUnk_080DC390;
extern EntityData gUnk_080DC3F0;
extern EntityData gUnk_080DC430;
extern EntityData gUnk_080DC530;
extern EntityData gUnk_080DC470;
extern EntityData gUnk_080DC4C0;
extern void sub_08057E64(void);

void sub_StateChange_MinishVillage_Main(void) {
    if (!GetInventoryValue(ITEM_JABBERNUT)) {
        LoadRoomEntityList(&gUnk_080DC390);
        if (!CheckLocalFlagByBank(FLAG_BANK_2, M_PRIEST_TALK)) {
            LoadRoomEntityList(&gUnk_080DC3F0);
        }
    } else {
        LoadRoomEntityList(&gUnk_080DC430);
        if (!GetInventoryValue(ITEM_GUST_JAR)) {
            LoadRoomEntityList(&gUnk_080DC530);
        }
    }
    /* Don't block the south exit of minish village after the gust jar is obtained but before the curtain to bellari is opened */
    // if ((!CheckLocalFlagByBank(FLAG_BANK_2, M_ELDER_TALK2ND)) && GetInventoryValue(ITEM_GUST_JAR)) {
    //     LoadRoomEntityList(&gUnk_080DC470);
    // }
    // entrance cutscene - doesn't matter since we set the flag
    if (!CheckLocalFlag(KOBITO_MORI_1ST)) {
        LoadRoomEntityList(&gUnk_080DC4C0);
    }
    // setup tileset stuff
    sub_08057E64();
}

extern EntityData gUnk_080F5E68;

void sub_StateChange_HouseInteriors3_FigurineHouse(void) {
    if (!GetInventoryValue(ITEM_QST_CARLOV_MEDAL)) {
        LoadRoomEntityList(&gUnk_080F5E68);
    }
}

extern u16 gUnk_080EED2C[];
extern u16 gUnk_080EED7A[];
extern u16 gUnk_080EED8C[];

void sub_0804E150(void) {
    u16* pTileData;
    u32 uVar3;

    pTileData = gUnk_080EED2C;
    uVar3 = 1 << gSave.global_progress;
    for (; pTileData[1] != 0; pTileData += 3) {
        if ((pTileData[0] & uVar3) != 0) {
            SetTile(pTileData[2], pTileData[1], 1);
        }
    }
    // figurine checks carlov medal instead of flag SHOP05_OPEN
    if (!GetInventoryValue(ITEM_QST_CARLOV_MEDAL)) {
        pTileData = gUnk_080EED7A;
        uVar3 = 1 << gSave.global_progress;
        for (; pTileData[0] != 0; pTileData += 3) {
            if ((pTileData[0] & uVar3) != 0) {
                SetTile(pTileData[2], pTileData[1], 1);
            }
        }
    }
    if (CheckGlobalFlag(MIZUKAKI_START) == 0) {
        pTileData = gUnk_080EED8C;
        uVar3 = 1 << gSave.global_progress;
        for (; pTileData[0] != 0; pTileData += 3) {
            if ((pTileData[0] & uVar3) != 0) {
                SetTile(pTileData[2], pTileData[1], 1);
            }
        }
    }
}

extern EntityData gUnk_080F9FA8;
extern EntityData gUnk_080F9F88;

void sub_StateChange_TreeInteriors_WitchHut(void) {
    if (!GetInventoryValue(ITEM_QST_MUSHROOM)) {
        LoadRoomEntityList(&gUnk_080F9F88);
    } else if (CheckKinstoneFused(KINSTONE_14)) {
        LoadRoomEntityList(&gUnk_080F9FA8);
    }
}

const ScreenTransitionData gUnk_0813AC20 = { 1, { 0, 0, 0, 0 }, 0x198, 0x38, 0, AREA_DARK_HYRULE_CASTLE, ROOM_DARK_HYRULE_CASTLE_B1_MAP, 1, 0, 0, 0 };

/*
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
*/
