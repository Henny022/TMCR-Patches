#include <save.h>
#include <fileselect.h>
#include <common.h>
#include <fade.h>
#include <game.h>
#include <message.h>
#include <object.h>
#include <screen.h>
#include <main.h>
#include <menu.h>

typedef enum {
    STATE_NONE,
    STATE_NEW,
    STATE_CHOOSE_LANG,
    STATE_OPTIONS,
    STATE_VIEW,
    STATE_COPY,
    STATE_ERASE,
    STATE_START,
} FileSelectState;

extern void SetFileSelectState(FileSelectState mode);
extern void ResetEmptyOrDeletedSaveFile(u32 index);
extern void sub_080503A8(u32 gfxGroup);
extern void HideButtonR(void);

extern const KeyButtonLayout gUnk_080FC8D0;

void HandleFileScreenEnter(void) {
    u32 i;

    DispReset(1);
    InitSoundPlayingInfo();
    MemClear((void*)VRAM, 0x80); // clear palettes
    MessageInitialize();
    EraseAllEntities();
    ClearTileMaps();
    ResetPalettes();
    ResetPaletteTable(0);
    MemClear(&gHUD, sizeof(gHUD));
    MemClear(&gMapDataBottomSpecial, sizeof(gMapDataBottomSpecial));
    gMapDataBottomSpecial.unk3 = 7;
    gMapDataBottomSpecial.unk6 = 0;
    MemClear(&gUI, sizeof(gUI));
    gUI.lastState = 8;
    SetFileSelectState(STATE_NONE);
    InitDMA();
    ResetEmptyOrDeletedSaveFile(0);
    ResetEmptyOrDeletedSaveFile(1);
    ResetEmptyOrDeletedSaveFile(2);
    InitVBlankDMA();
    sub_080503A8(0x5);
    LoadPaletteGroup(0x9);
    for (i = 0; i < 26; i++) {
        CreateObject(FILE_SCREEN_OBJECTS, i, 0);
    }

    sub_080A70AC(&gUnk_080FC8D0);
    HideButtonR();
    gScreen.lcd.displayControl |= DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON;
    gScreen.bg3.control = BGCNT_PRIORITY(3) | BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(30);
    gScreen.controls.layerFXControl = BLDCNT_TGT1_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_EFFECT_BLEND;
    gScreen.controls.alphaBlend = BLDALPHA_BLEND(15, 10);
    gGFXSlots.unk0 = 1;
    gMain.state = GAMETASK_INIT;
    SoundReq(BGM_FILE_SELECT);
    SetFade(FADE_INSTANT, 8);
}
