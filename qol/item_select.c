#include <menu.h>
#include <item.h>
#include <sound.h>
#include <itemMetaData.h>
#include <game.h>
#include <save.h>
#include <common.h>

typedef struct {
    u8 up;
    u8 down;
    u8 left;
    u8 right;
    u8 type;
    u8 unk0;
    u8 x;
    u8 y;
} ItemMenuTableEntry;

extern const ItemMenuTableEntry gItemMenuTable[];

extern bool32 sub_080A51F4(void);
extern void sub_080A6F6C(u32);
extern void sub_080A5F48(u32,u32);
extern void sub_080A4E84(u32);

void PauseMenu_ItemMenu_Update(void) {
    static const u8 gUnk_08128BF4[] = { 14, 15, 2, 0 };
    u32 item;
    u32 menuSlot;
    const ItemMenuTableEntry* entry;

    if (sub_080A51F4()) {
        gMenu.field_0xc = (u8*)gUnk_08128BF4;
        menuSlot = gMenu.field_0x3;

        entry = &gItemMenuTable[menuSlot];
        switch (gInput.newKeys) {
            case A_BUTTON:
                if (menuSlot == MENU_SLOT_SAVE_BUTTON) {
#if defined(DEMO_USA) || defined(DEMO_JP)
                    SoundReq(SFX_MENU_ERROR);
#else
                    sub_080A4E84(0xb);
                    SoundReq(SFX_TEXTBOX_SELECT);
#endif
                    break;
                }
                // fallthrough
            case B_BUTTON:
                if (gPauseMenu.items[menuSlot] != 0) {
                    u32 t = !!(gInput.newKeys ^ 1);
                    ForceEquipItem(gPauseMenu.items[menuSlot], t);
                    SoundReq(SFX_TEXTBOX_SELECT);
                }
                break;
            case SELECT_BUTTON: {
                Item selected_item = gPauseMenu.items[menuSlot];
                switch (selected_item) {
                    case ITEM_RED_SWORD:
                        if(GetInventoryValue(ITEM_BLUE_SWORD)){
                            selected_item = ITEM_BLUE_SWORD;
                            break;
                        }
                        // fallthrough
                    case ITEM_BLUE_SWORD:
                        if(GetInventoryValue(ITEM_FOURSWORD)){
                            selected_item = ITEM_FOURSWORD;
                            break;
                        }
                        // fallthrough
                    case ITEM_FOURSWORD:
                        if(GetInventoryValue(ITEM_RED_SWORD)){
                            selected_item = ITEM_RED_SWORD;
                            break;
                        }
                        if(GetInventoryValue(ITEM_BLUE_SWORD)){
                            selected_item = ITEM_BLUE_SWORD;
                        }
                        break;
                    case ITEM_BOMBS:
                        if(GetInventoryValue(ITEM_REMOTE_BOMBS)){
                            selected_item = ITEM_REMOTE_BOMBS;
                        }
                        break;
                    case ITEM_REMOTE_BOMBS:
                        if(GetInventoryValue(ITEM_BOMBS)){
                            selected_item = ITEM_BOMBS;
                        }
                        break;
                    case ITEM_BOW:
                        if(GetInventoryValue(ITEM_LIGHT_ARROW)){
                            selected_item = ITEM_LIGHT_ARROW;
                        }
                        break;
                    case ITEM_LIGHT_ARROW:
                        if(GetInventoryValue(ITEM_BOW)){
                            selected_item = ITEM_BOW;
                        }
                        break;
                    case ITEM_BOOMERANG:
                        if(GetInventoryValue(ITEM_MAGIC_BOOMERANG)){
                            selected_item = ITEM_MAGIC_BOOMERANG;
                        }
                        break;
                    case ITEM_MAGIC_BOOMERANG:
                        if(GetInventoryValue(ITEM_BOOMERANG)){
                            selected_item = ITEM_BOOMERANG;
                        }
                        break;
                    case ITEM_SHIELD:
                        if(GetInventoryValue(ITEM_MIRROR_SHIELD)){
                            selected_item = ITEM_MIRROR_SHIELD;
                        }
                        break;
                    case ITEM_MIRROR_SHIELD:
                        if(GetInventoryValue(ITEM_SHIELD)){
                            selected_item = ITEM_SHIELD;
                        }
                        break;
                    default:
                        break;
                }
                if (selected_item != gPauseMenu.items[menuSlot]) {
                    gPauseMenu.items[menuSlot] = selected_item;
                    sub_080A5F48(selected_item, menuSlot * 8 + 0x360);
                }
            } break;
            default:
                switch (gInput.unk4) {
                    case DPAD_UP:
                        menuSlot = entry->up;
                        break;
                    case DPAD_DOWN:
                        menuSlot = entry->down;
                        break;
                    case DPAD_LEFT:
                        menuSlot = entry->left;
                        break;
                    case DPAD_RIGHT:
                        menuSlot = entry->right;
                        break;
                }
                break;
        }
        if (gMenu.field_0x3 != menuSlot) {
            gMenu.field_0x3 = menuSlot;
            SoundReq(SFX_TEXTBOX_CHOICE);
        }
        item = gPauseMenu.items[menuSlot];
        switch (menuSlot) {
            case MENU_SLOT_BOTTLE0:
            case MENU_SLOT_BOTTLE1:
            case MENU_SLOT_BOTTLE2:
            case MENU_SLOT_BOTTLE3:
                if (item != 0) {
                    item = gSave.saved_status.field_0x24[item - 6];
                }
                break;
            case MENU_SLOT_SAVE_BUTTON:
                // ITEM_SKILL_FAST_SPIN, but that does not make any sense at all
                item = 0x73;
                break;
            default:
                break;
        }
        sub_080A6F6C(item + 0x400);
    }
}
