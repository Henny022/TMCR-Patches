#define NENT_DEPRECATED
#include <entity.h>
#include <room.h>
#include <player.h>
#include <new_player.h>
#include <game.h>
#include <message.h>
#include <save.h>
#include <common.h>
#include <object.h>
#include <item.h>
#include <script.h>

#include "base.h"

#define ITEM_SHOP_ENTITY 0xfb

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u8 unk_68[0x18];
    /*0x80*/ u16 unk_80;
    /*0x82*/ u16 unk_82;
    /*0x84*/ u16 price;
    /*0x86*/ u16 flag;
} ItemForSaleEntity;

extern GenericEntity gUnk_030015A0[];

extern struct_03003DF8* sub_080784E4(void);

bool32 sub_080782C0(void) {
    u8 tmp;
    GenericEntity* entity;

    if (gPlayerState.framestate == PL_STATE_IDLE) {
        tmp = gPlayerState.framestate_last;
    } else {
        tmp = gPlayerState.framestate;
    }
    switch (tmp) {
        case PL_STATE_SWORD:
        case PL_STATE_GUSTJAR:
        case PL_STATE_C:
        case PL_STATE_DIE:
        case PL_STATE_ITEMGET:
        case PL_STATE_DROWN:
            return FALSE;
    }
    if ((gPlayerState.field_0x27[0] | gPlayerState.swim_state) != 0) {
        return FALSE;
    }
    if (gPlayerState.floor_type == SURFACE_PIT) {
        if (gPlayerState.field_0x14 == 0) {
            return FALSE;
        }
        if (CanDispEzloMessage()) {
            return TRUE;
        }
        return FALSE;
    }
    if ((gPlayerState.flags & PL_DRUGGED) != 0) {
        return FALSE;
    }
    if (CanDispEzloMessage()) {
        return TRUE;
    }
    entity = (GenericEntity*) sub_080784E4()->entity;
    if (entity == NULL) {
        return FALSE;
    }
    if (gPlayerState.heldObject != 0) {
        if (gPlayerState.heldObject != 4) {
            return FALSE;
        }
        if ((gNewPlayerEntity.unk_74)->child->kind != OBJECT || (gNewPlayerEntity.unk_74)->child->id != SHOP_ITEM) {
            return FALSE;
        }
    }
    if (((gPlayerState.playerInput.newInput & PLAYER_INPUT_1000) != 0) && ((u8)(gUnk_03003DF0.unk_4[3] - 1) < 100)) {
        AddKinstoneToBag(0);
        if (gSave.kinstoneAmounts[0] != 0) {
            gUnk_03003DF0.unk_2 = gUnk_03003DF0.unk_4[3];
            *(u8*)(*(int*)(gUnk_03003DF0.unk_4 + 8) + 0x39) = 2;
            gPlayerState.queued_action = PLAYER_08070E9C;
        } else {
            CreateEzloHint(TEXT_INDEX(TEXT_EZLO, 0x65), 0);
        }
        ForceSetPlayerState(PL_STATE_TALKEZLO);
        return TRUE;
    }
    if ((gPlayerState.playerInput.newInput & (PLAYER_INPUT_80 | PLAYER_INPUT_8)) == 0) {
        return FALSE;
    }
    switch (gUnk_03003DF0.unk_4[1]) {
        default:
        case 0:
            return TRUE;
        case 1:
        case 6:
        case 9:
        case 0xa:
            gPlayerState.queued_action = PLAYER_08070E9C;
            ForceSetPlayerState(PL_STATE_TALKEZLO);
            // fallthrough
        case 3:
        case 5:
        case 7:
            entity->base.interactType = 1;
            gUnk_03003DF0.unk_2 = 0;
            return TRUE;
        case 8:
            if (gRoomVars.shopItemType == 0) {
                entity->base.interactType = 1;
                int index = entity - gUnk_030015A0;
                gRoomVars.shopItemType = ITEM_SHOP_ENTITY; // special value to indicate entity list index
                gRoomVars.shopItemType2 = index;
                return TRUE;
            }
            return FALSE;
    }
    return TRUE;
}

s32 GetItemPrice(u32 item) {
    if (item == ITEM_SHOP_ENTITY)
    {
        ItemForSaleEntity* e = (ItemForSaleEntity*) &gUnk_030015A0[gRoomVars.shopItemType2];
        if (e->price)
            return e->price;
        item = e->base.type;
    }
    const struct_080FD964* ptr = &gUnk_080FD964[item];
    return ptr->itemPrice;
}

extern void SetPlayerItemGetState(GenericEntity*, u32, u32);
extern GenericEntity* GiveItemWithCutscene(u32 item, u32 type2, u32 delay);

void InitItemGetSequence(u32 type, u32 type2, u32 delay) {
    if (type == ITEM_SHOP_ENTITY)
    {
        ItemForSaleEntity* e = (ItemForSaleEntity*) &gUnk_030015A0[gRoomVars.shopItemType2];
        type = e->base.type;
        type2 = e->base.type2;
        if(e->flag)
        {
            int item = get_item_for_global_flag_with_default(flag2global(e->flag), get_item_from_value_and_subvalue(type, type2));
            type = get_item_id(item);
            type2 = get_item_subvalue(item);
        }
    }
    GenericEntity* e = GiveItemWithCutscene(type, type2, delay);
    if (e != NULL) {
        e->base.parent = &gPlayerEntity;
        SetPlayerItemGetState(e, e->base.type, 0);
    }
}

void sub_08065370(Entity* this, ScriptExecutionContext* context) {
    u32 bVar1;
    u32 shopItemType;
    u32 itemPrice;
    u32 messageIndex;
    int localFlag;

    bVar1 = 1;
    shopItemType = gRoomVars.shopItemType;
    localFlag = 0;
    switch (shopItemType) {
        case ITEM_ARROWS10:
        case ITEM_ARROWS30:
            if (gQuiverSizes[gSave.stats.quiverType] <= gSave.stats.arrowCount) {
                messageIndex = TEXT_INDEX(TEXT_STOCKWELL, 0xe);
                goto showmsg;
            }
            break;
        case ITEM_SHIELD:
            if (GetInventoryValue(ITEM_SHIELD) || GetInventoryValue(ITEM_MIRROR_SHIELD)) {
                messageIndex = TEXT_INDEX(TEXT_STOCKWELL, 0xb);
                goto showmsg;
            }
            break;
        case ITEM_BOMBS10:
        case ITEM_BOMBS30:
            if (gBombBagSizes[gSave.stats.bombBagType] <= gSave.stats.bombCount) {
                messageIndex = TEXT_INDEX(TEXT_STOCKWELL, 0xe);
                goto showmsg;
            }
            break;
        case ITEM_WALLET:
            localFlag = SHOP00_SAIFU;
            break;
        case ITEM_LARGE_QUIVER:
            localFlag = SHOP00_YAZUTSU;
            break;
        case ITEM_SHELLS30:
            if (999 <= gSave.stats.shells) {
                MessageNoOverlap(TEXT_INDEX(TEXT_STOCKWELL, 0xe), this);
                bVar1 = 0;
            }
            break;
        case ITEM_SHOP_ENTITY:
            {
                ItemForSaleEntity* e = (ItemForSaleEntity*) &gUnk_030015A0[gRoomVars.shopItemType2];
                localFlag = e->flag;
            }
    }

    if (bVar1) {
        itemPrice = GetItemPrice(shopItemType);
        if (itemPrice <= gSave.stats.rupees) {
            ModRupees(-itemPrice);
            InitItemGetSequence(shopItemType, gRoomVars.shopItemType2, 2);
            gRoomVars.shopItemType = 0;
            gRoomVars.shopItemType2 = 0;
            context->condition = 1;
            if (localFlag) {
                SetFlag(localFlag);
            }
            if (gSave.unk5C <= ~1u) {
                gSave.unk5C++;
            }

            if (gSave.unk5C >= 10) {
                context->intVariable = TEXT_INDEX(TEXT_STOCKWELL, 0x11);
            } else {
                if (itemPrice >= 100) {
                    context->intVariable = TEXT_INDEX(TEXT_STOCKWELL, 0x10);
                } else {
                    context->intVariable = TEXT_INDEX(TEXT_STOCKWELL, 0xf);
                }
            }
            return;
        }
        messageIndex = TEXT_INDEX(TEXT_STOCKWELL, 0xd);
    showmsg:
        MessageNoOverlap(messageIndex, this);
    }
    context->condition = 0;
}

extern EntityData gUnk_080F5758;
extern EntityData gUnk_080F57E8;
extern EntityData gUnk_080F57A8;
extern EntityData gUnk_080F57C8;
extern EntityData gUnk_080F5888;
extern EntityData gUnk_080F58A8;
extern EntityData gUnk_080F5868;
extern EntityData gUnk_080F5828;
extern EntityData gUnk_080F5848;
extern EntityData gUnk_080F5788;

void sub_StateChange_HouseInteriors3_StockwellShop(void) {
    LoadRoomEntityList(&gUnk_080F5758);
    if (!CheckGlobalFlag(2582) && CheckLocalFlagByBank(FLAG_BANK_2, KHOUSE52_KINOKO)) {
        LoadRoomEntityList(&gUnk_080F57E8);
    }
    if (!CheckLocalFlag(SHOP00_SAIFU)) {
        LoadRoomEntityList(&gUnk_080F57A8);
    } else {
        if (gBombBagSizes[gSave.stats.bombBagType] >= 30) {
            LoadRoomEntityList(&gUnk_080F57C8);
        }
        if (!CheckGlobalFlag(2583)) {
            LoadRoomEntityList(&gUnk_080F5888);
        /* TODO sell the bomb bag
        } else {
            if (!CheckLocalFlag(0xcd)) {
                LoadRoomEntityList(&gUnk_080F58A8);
            }
        */
        }
    }
    // TODO add back for new logic
    //if (GetInventoryValue(ITEM_BOW) || CheckGlobalFlag(LV3_CLEAR)) {
        LoadRoomEntityList(&gUnk_080F5868);
        if (!CheckLocalFlag(SHOP00_YAZUTSU)) {
            LoadRoomEntityList(&gUnk_080F5828);
        } else {
            LoadRoomEntityList(&gUnk_080F5848);
        }
    //}
    if (gSave.stats.hasAllFigurines == 0) {
        LoadRoomEntityList(&gUnk_080F5788);
    }
}

/*
void GoronMerchant_TryToBuyKinstone(Entity* this, ScriptExecutionContext* context) {
    s32 salePrice = GoronMerchant_GetSalePrice(this);
    if (salePrice <= gSave.stats.rupees) {
        if (GetAmountInKinstoneBag(gRoomVars.shopItemType2) < 99) {
            ModRupees(-salePrice);
            InitItemGetSequence(ITEM_KINSTONE, gRoomVars.shopItemType2, 0);
            gRoomVars.shopItemType = 0;
            gRoomVars.shopItemType2 = 0;
            context->condition = 1;
        } else {
            MessageNoOverlap(TEXT_INDEX(TEXT_STOCKWELL, 0x1f), this);
            context->condition = 0;
        }
    } else {
        MessageNoOverlap(TEXT_INDEX(TEXT_STOCKWELL, 0x1e), this);
        context->condition = 0;
    }
    gActiveScriptInfo.flags |= 1;
}
*/
