#include <entity.h>
#include <item.h>
#include "../network/network.h"
#include "../checkIds/base.h"

extern void(*const sPlayerActions[])(PlayerEntity*);

void DoPlayerAction(PlayerEntity* this) {
    if (super->action==1 /*&& gPlayerState.controlMode == CONTROL_ENABLED*/)
    {
        u16 item = 0;
        u8 addr = 0;
        if (recv(2, &addr, 2, &item))
        {
            CreateItemEntity(get_item_id(item), get_item_subvalue(item), 0);
            return;
        }
    }
    sPlayerActions[super->action](this);
}
