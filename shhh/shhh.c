#include <entity.h>
#include <item.h>
#include "../checkIds/protocol.h"
#include "../checkIds/base.h"

extern void(*const sPlayerActions[])(Entity*);

void DoPlayerAction(Entity* this) {
    if (this->action==1)
    {
        if (gScriptIO.rx.status)
        {
            u32 t = protocol_recv(TRUE);
            u32 cmd = packet_type(t);
            u32 value = packet_value(t);
            if (cmd==5)
            {
                CreateItemEntity(get_item_id(value), get_item_subvalue(value), 0);
            }
            return;
        }
    }
    sPlayerActions[this->action](this);
}
