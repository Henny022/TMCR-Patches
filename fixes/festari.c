#include <entity.h>
#include <item.h>
#include <npc.h>

extern const Dialog gUnk_08109DC8[][4];

void sub_0806021C(Entity* this) {
    u32 uVar2 = 0;

    if (GetInventoryValue(ITEM_JABBERNUT)) {
        uVar2 = 1;
    }

    if (CheckGlobalFlag(LV1_CLEAR)) {
        uVar2 = 2;
    }

    if (GetInventoryValue(ITEM_MOLE_MITTS)) {
        uVar2 = 3;
    }
    ShowNPCDialogue(this, &gUnk_08109DC8[this->type2][uVar2]);
}