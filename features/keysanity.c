#include <item.h>
#include <game.h>
#include <itemMetaData.h>
#include <sound.h>
#include <common.h>
#include <save.h>

extern const u16 gUnk_080FD5A8[];

u32 GiveItem(Item item, u32 param_2) {
    u32 uVar4;
    u32 result;
    u32 uVar9;
    const ItemMetaData* metaData;

    uVar4 = GetInventoryValue(item);
    metaData = &gItemMetaData[item];

    if (uVar4 == 0) {
        result = *(u16*)&metaData->textId;
    } else {
        result = *(u16*)&metaData->unk6;
    }
    if (!ItemIsBottle(item)) {
        PutItemOnSlot(item);
        if (uVar4 == 0) {
            SetInventoryValue(item, 1);
        }
    }
    switch (metaData->unk1) {
        case 0:
        default:
            break;
        case 1:
            ModHealth(metaData->unk2);
            SoundReq(SFX_HEART_GET);
            break;
        case 2:
            ModRupees((u32)gUnk_080FD5A8[metaData->unk2]);
            SoundReq(SFX_RUPEE_GET);
            break;
        case 3:
            uVar9 = 0;
            while (TRUE) {
                if (3 < uVar9) {
                    return result;
                }
                if (GetInventoryValue(ITEM_BOTTLE1 + uVar9) == 0)
                    break;
                uVar9++;
            }
            item = ITEM_BOTTLE1 + uVar9;
            if (gSave.stats.bottles[uVar9] == 0) {
                gSave.stats.bottles[uVar9] = 0x20;
            }
            SetInventoryValue(item, 1);
            PutItemOnSlot(item);
            break;
        case 4:
            uVar9 = 0;
            while (gSave.stats.bottles[uVar9] != 0x20) {
                uVar9++;
                if (3 < uVar9) {
                    return result;
                }
            }
            if (3 < uVar9) {
                break;
            }
            gSave.stats.bottles[uVar9] = (u8)item;
            SetInventoryValue(item, 1);
            SoundReq(SFX_ITEM_GET);
            break;
        case 5:
            {
                unsigned int t = param_2 == 0 ? gArea.dungeon_idx : param_2;
                int amount = t >> 3;
                if (amount == 0) amount = 1;
                t &= ~(~0u << 3);
                if (t == 0) break;
                gSave.dungeonKeys[t] += amount;
            }
            SoundReq(SFX_103);
            break;
        case 6: // TODO dungeon item?
            {
                unsigned int t = param_2 == 0 ? gArea.dungeon_idx : param_2;
                t &= ~(~0u << 3);
                if (t == 0) break;
                gSave.dungeonItems[t] |= metaData->unk2;
            }
            break;
        case 0xd:
            AddKinstoneToBag(0x72);
            break;
        case 0x12:
            if (item == ITEM_BOOMERANG) {
                SetInventoryValue(ITEM_MAGIC_BOOMERANG, 0);
            } else {
                SetInventoryValue(ITEM_BOOMERANG, 0);
            }
            // fallthrough
        case 0x11:
            LoadItemGfx();
            break;
        case 7:
            if (item == ITEM_BOMBS) {
                SetInventoryValue(ITEM_REMOTE_BOMBS, 0);
            } else {
                SetInventoryValue(ITEM_BOMBS, 0);
            }
            ModBombs(99);
            LoadItemGfx();
            break;
        case 8:
            if (uVar4 == 0) {
                SetInventoryValue(ITEM_BOMBS, 1);
                PutItemOnSlot(7);
            } else {
                gSave.stats.bombBagType++;
                if (3 < gSave.stats.bombBagType) {
                    gSave.stats.bombBagType = 3;
                }
            }
            ModBombs(99);
            break;
        case 9:
            ModBombs(metaData->unk2);
            SoundReq(SFX_103);
            break;
        case 0xb:
            if (GetInventoryValue(ITEM_LARGE_QUIVER) == 0) {
                SetInventoryValue(ITEM_LARGE_QUIVER, 1);
            }
            ModArrows(99);
            LoadItemGfx();
            break;
        case 0xa:
            gSave.stats.quiverType++;
            if (3 < gSave.stats.quiverType) {
                gSave.stats.quiverType = 3;
            }
            ModArrows(99);
            break;
        case 0xc:
            ModArrows(metaData->unk2);
            SoundReq(SFX_103);
            break;
        case 0x0e:
            SetInventoryValue(ITEM_SHELLS, 1);
            ModShells(param_2);
            SoundReq(SFX_103);
            break;
        case 0x0f:
            AddKinstoneToBag(param_2);
            break;
        case 0x10:
            gSave.stats.walletType++;
            if (gSave.stats.walletType < 4) {
                break;
            }
            gSave.stats.walletType = 3;
            break;
    }
    return result;
}
