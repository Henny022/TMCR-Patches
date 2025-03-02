#define NENT_DEPRECATED
#include <entity.h>
#include <item.h>
#include <flags.h>
#include <save.h>

#include "base.h"

typedef struct {
    u8 item;
    u8 subtype;
    u8 unk2;
    u8 unk3;
} CuccoMinigamePrizeData;

extern const CuccoMinigamePrizeData prizeData[];

typedef struct {
    Entity base;
    s16 timer;
    s16 currentCuccos;
    s16 targetCuccos;
    u16 unk6e;
    u8 returnedCuccoTypes[0x18];
} CuccoMinigameEntity;

extern u32 CuccoMinigame_GetLevel(void);

void CuccoMinigame_WinItem(CuccoMinigameEntity* this) {
    bool32 skipItem;
    int level = CuccoMinigame_GetLevel();
    const CuccoMinigamePrizeData* prize = &prizeData[level];
    int flag = 2585+level;
    int item = get_item_for_global_flag_with_default(flag, get_item_from_value_and_subvalue(prize->item, prize->subtype));
    int itemid = get_item_id(item);
    skipItem = CheckGlobalFlag(flag);
    switch (itemid) {
        case ITEM_SHELLS:
            if (gSave.stats.hasAllFigurines) {
                skipItem = 1;
            }
            break;
        case ITEM_KINSTONE:
            if (gSave.kinstones.didAllFusions) {
                skipItem = 1;
            }
            break;
    }

    if (!skipItem) {
        InitItemGetSequence(itemid, get_item_subvalue(item), 0);
    } else {
        this->unk6e = 2;
    }
}