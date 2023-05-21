#include <entity.h>
#include <item.h>
#include "../scriptio.h"
#include "../checkIds/base.h"

extern void(*const sPlayerActions[])(Entity*);

void DoPlayerAction(Entity* this) {
    if (this->action==1)
    {
        if (gScriptIO.rx.status)
        {
            u32 t = scriptio_recv();
            u32 cmd = t>>24;
            u32 value = t&0xffffff;
            if (cmd==5)
            {
                CreateItemEntity(get_item_id(value), get_item_subvalue(value), 0);
            }
            return;
        }
    }
    sPlayerActions[this->action](this);
}
