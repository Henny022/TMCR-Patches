#include <item.h>
#include <script.h>
#include <flags.h>
#include <save.h>

void sub_08068CFC(Entity* this, ScriptExecutionContext* context) {
    u8 bVar1;
    u8 itemID;

    context->condition = 0;
    bVar1 = this->timer;
    if (bVar1 > 10)
        return;

    switch (bVar1) {
        case 0:
        default:
            context->condition = 1;
            return;
        case 1:{
                static const u8 white_swords[3] = {
                    ITEM_RED_SWORD,
                    ITEM_BLUE_SWORD,
                    ITEM_FOURSWORD,
                };
                for (unsigned int i = 0; i < ARRAY_COUNT(white_swords); i++) {
                    if (GetInventoryValue(white_swords[i])) 
                    {
                        context->condition = 1;
                        return;
                    }
                }
            }
            itemID = ITEM_GREEN_SWORD;
            break;
        case 2:
            itemID = ITEM_PEGASUS_BOOTS;
            break;
        case 3:
            itemID = ITEM_ROCS_CAPE;
            break;
        case 5:
            if (CheckLocalFlag(DOUKUTU_05_EVENT) == 0) {
                return;
            }
            context->condition = 1;
            return;
        case 6:
            if (gSave.stats.maxHealth < (10 * 8)) // ten hearts
                return;
            context->condition = 1;
            return;
        case 7:
            {
                static const u8 scrolls[11] = {
                    ITEM_SKILL_SPIN_ATTACK,
                    ITEM_SKILL_ROLL_ATTACK,
                    ITEM_SKILL_DASH_ATTACK,
                    ITEM_SKILL_ROCK_BREAKER,
                    ITEM_SKILL_SWORD_BEAM,
                    ITEM_SKILL_GREAT_SPIN,
                    ITEM_SKILL_DOWN_THRUST,
                    ITEM_SKILL_PERIL_BEAM,
                    ITEM_SKILL_FAST_SPIN,
                    ITEM_SKILL_FAST_SPLIT,
                    ITEM_SKILL_LONG_SPIN,
                };
                int counter = 0;
                for (unsigned int i = 0; i < ARRAY_COUNT(scrolls); i++) {
                    if (GetInventoryValue(scrolls[i])) counter++;
                }
                context->condition = counter >= 7;
            }
            return;
    }

    if (GetInventoryValue(itemID) == 0) {
        return;
    }
    context->condition = 1;
}