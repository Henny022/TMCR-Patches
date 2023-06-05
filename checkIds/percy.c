#include <script.h>
#include <item.h>
#include <message.h>
#include <entity.h>
#include <save.h>
#include <flags.h>

#include "base.h"

void sub_0806B540(Entity* this) {
    ScriptExecutionContext* context;

    context = *(ScriptExecutionContext**)&this->cutsceneBeh;
    switch (context->unk_18) {
        case 0:
            MessageNoOverlap(TEXT_INDEX(TEXT_PERCY, 0x12), this);
            if (CheckLocalFlag(0x3f) != 0) {
                return;
            }
            context->unk_18++;
            SetLocalFlag(0x3f);
            break;
        case 1:
            if ((gMessage.doTextBox & 0x7f) == 0) {
                context->unk_18 = 2;
                MessageNoOverlap(TEXT_INDEX(TEXT_PERCY, 0x15), this);
            }
            break;
        case 2:
            if ((gMessage.doTextBox & 0x7f) == 0) {
                context->unk_18 = 3;
                {
                    int item;
                    if (gSave.stats.hasAllFigurines != 0) {
                        item = ITEM_RUPEE100;
                    } else {
                        item = get_item_from_value_and_subvalue(ITEM_SHELLS, 100);
                    }
                    item = get_item_for_global_flag_with_default(local2global(MHOUSE08_00), item);
                    InitItemGetSequence(get_item_id(item), get_item_subvalue(item), 0);
                }
                
                SetRoomFlag(0xf);
            }
            break;
        case 3:
            if ((gPlayerEntity.action != PLAYER_ITEMGET)) {
                context->wait = 0x2d;
                return;
            }
            break;
    }

    gActiveScriptInfo.commandSize = 0;
}