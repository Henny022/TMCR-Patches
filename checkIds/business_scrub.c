#include <entity.h>
#include <enemy.h>
#include <item.h>
#include <message.h>
#include <save.h>

#include "base.h"

struct SalesOffering {
    u8 field_0x0;
    u8 field_0x1;
    u16 price;
    u16 field_0x4;
    u16 field_0x6;
    u8 offeredItem; /**< @see Item */
    u8 item_subtype;
    u16 local_flag;
};

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u8 unused1[12];
    /*0x74*/ u16 unk_74;
    /*0x76*/ u16 unk_76;
    /*0x78*/ u16 unk_78;
    /*0x7a*/ u16 unk_7a;
    /*0x7c*/ const struct SalesOffering* unk_7c;
    /*0x80*/ u8 unk_80;
    /*0x81*/ u8 unk_81;
    /*0x82*/ u8 unused2[4];
    /*0x86*/ u16 unk_86;
} BusinessScrubEntity;

extern void sub_0802922C(Entity* this);
void sub_080290E0(BusinessScrubEntity*, u32);
bool32 BusinessScrub_CheckRefillFitsBag(BusinessScrubEntity* this);
extern s32 sub_08056338(void);
bool32 sub_0802915C(BusinessScrubEntity* this);

extern const u8 kinstoneTypes[];

void BusinessScrub_Action5(BusinessScrubEntity* this) {
    struct SalesOffering* offer = (struct SalesOffering*)this->unk_7c;
    u32 subtype;

    if ((gMessage.state & MESSAGE_ACTIVE) == 0 && sub_0802915C(this) && !sub_08056338()) {
        if (offer->price <= gSave.stats.rupees) {
            if (BusinessScrub_CheckRefillFitsBag(this)) {
                /* Bag full. */
                MessageFromTarget(TEXT_INDEX(TEXT_BUSINESS_SCRUB, 0x04));
                SetPlayerControl(0);
            } else {
                ModRupees(-offer->price);
                switch (offer->field_0x0 >> 2) {
                    case 0: //random kinstone
                        subtype = offer->item_subtype;
                        if (subtype == 0xff) {
                            subtype = kinstoneTypes[Random() & 7];
                        }

                        CreateItemEntity(offer->offeredItem, subtype, 0);

                        super->action = 6;
                        super->timer = 4;
                        this->unk_80 = 0;
                        sub_080290E0(this, 3);
#if defined(USA) || defined(DEMO_USA)
                        SetLocalFlag(KS_B06);
#endif
                        return;
                    case 1: //refill, bottle, specific kinstone
                        {
                            int itemid, itemsub;
                            if (offer->offeredItem == ITEM_BOTTLE1) {
                                int item = get_item_for_global_flag_with_default(AKINDO_BOTTLE_SELL, get_item_from_value_and_subvalue(offer->offeredItem, offer->item_subtype));
                                itemid = get_item_id(item);
                                itemsub = get_item_subvalue(item);
                            } else {
                                itemid = offer->offeredItem;
                                itemsub = offer->item_subtype;
                            }
                            CreateItemEntity(itemid, itemsub, 0);
                            super->timer = 4;
                            sub_0802922C(super);
                            return;
                        }
                    case 2: //grip ring
                        {
                            int itemid, itemsub;
                            if (offer->offeredItem == ITEM_GRIP_RING) {
                                int item = get_item_for_global_flag_with_default(2584, get_item_from_value_and_subvalue(offer->offeredItem, offer->item_subtype));
                                itemid = get_item_id(item);
                                itemsub = get_item_subvalue(item);
                                SetLocalFlagByBank(0xa00, 24);
                            } else {
                                itemid = offer->offeredItem;
                                itemsub = offer->item_subtype;
                            }
                            CreateItemEntity(itemid, itemsub, 0);
                            super->timer = 8;
                            sub_0802922C(super);
                            return;
                        }
                }
            }
        } else {
            /* Not enough money. */
            MessageFromTarget(TEXT_INDEX(TEXT_BUSINESS_SCRUB, 0x03));
            SetPlayerControl(0);
        }
    }

    sub_0800445C(super);
    super->action = 4;
    super->timer = 48;
    sub_080290E0(this, 0);
}


bool32 sub_0802915C(BusinessScrubEntity* this) {
    const struct SalesOffering* offer = (const struct SalesOffering*)this->unk_7c;

    switch (offer->offeredItem) {
        case ITEM_GRIP_RING:
            if (CheckLocalFlagByBank(0xA00, 24) == 0)
                return TRUE;
            break;
        case ITEM_BOTTLE1:
            if (CheckGlobalFlag(AKINDO_BOTTLE_SELL) == 0)
                return TRUE;
            break;
        case ITEM_KINSTONE:
        case ITEM_BOMBS10:
        case ITEM_ARROWS30:
            return TRUE;
    }
    return FALSE;
}


bool32 sub_08029198(const struct SalesOffering* offer) {
    u32 tmp;

    if ((offer->field_0x0 & 0xfc) != 0xc) {
        switch (offer->offeredItem) {
            case ITEM_BOTTLE1:
                tmp = CheckGlobalFlag(AKINDO_BOTTLE_SELL);
                break;
            case ITEM_BOW:
                tmp = 0;
                break;
            case ITEM_GRIP_RING:
                tmp = CheckLocalFlagByBank(0xa00, 24);
                break;
            default:
                return 0;
        }
    } else {
        tmp = CheckLocalFlag(offer->local_flag);
    }

    if (tmp == 0) {
        return FALSE;
    }

    return TRUE;
}