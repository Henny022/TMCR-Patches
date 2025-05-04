#include <manager.h>
#include <manager/ezloHintManager.h>
#include <player.h>
#include <flags.h>
#include <asm.h>

extern bool32 PlayerStateValid(EzloHintManager* this);
extern void sub_080585DC(EzloHintManager* this);

void EzloHintManager_Action2(EzloHintManager* this) {
    if (gPlayerState.flags & PL_NO_CAP)
        return;
    if (!CheckPlayerInRegion(this->x, this->y, this->rx, this->ry))
        return;
    switch (super->type) {
        case 1:
            return;
        case 2:
            sub_080585DC(this);
            if ((gPlayerState.flags & PL_MINISH) == 0)
                return;
            // fallthrough
        case 0:
        default:
            sub_080585DC(this);
            if (!PlayerStateValid(this))
                return;
            SetFlag(this->flag1);
            DeleteThisEntity();
            return;
        case 3:
            super->action = 4;
            super->subAction = 0;
            SetNextAreaHint(this->msg_idx);
            return;
    }
}