#include <entity.h>
#include <item.h>
#include "../checkIds/protocol.h"
#include "../checkIds/base.h"

extern void(*const sPlayerActions[])(PlayerEntity*);

void DoPlayerAction(PlayerEntity* this) {
    if (super->action==1 /*&& gPlayerState.controlMode == CONTROL_ENABLED*/)
    {
        u32 t = protocol_recv(TRUE);
        u32 cmd = packet_type(t);
        if (cmd != 0x7f)
        {
            u32 value = packet_value(t);
            if (cmd==5)
            {
                CreateItemEntity(get_item_id(value), get_item_subvalue(value), 0);
            }
            return;
        }
    }
    sPlayerActions[super->action](this);
}
