#include <item.h>
#include <flags.h>
#include <script.h>
#include "base.h"

extern const u8 gUnk_08111623[];
extern const u8 gUnk_0811162B[];

void sub_08068C28(Entity* this) {
    this->timer = gUnk_08111623[this->type];
    if (this->type == 1) {
        if (CheckGlobalFlag(2563)) {
            this->timer = 1;
            if (CheckGlobalFlag(2564)) {
                this->timer = 2;
                if (CheckGlobalFlag(2565)) {
                    this->timer = 3;
                }
            }
        }
    }
}

void sub_08068CA0(Entity* this, ScriptExecutionContext* context) {
    context->condition = CheckGlobalFlag(2563 + this->timer);
}

void BladeBrothers_GetScroll(Entity* this) {
    int scroll = this->timer;
    int flag = 2563 + scroll;
    int vanilla = gUnk_0811162B[scroll] & 0xffffff7f;
    int item = get_item_for_global_flag_with_default(flag, vanilla);
    InitItemGetSequence(get_item_id(item), get_item_subvalue(item), 0);
    SetGlobalFlag(flag);
}
