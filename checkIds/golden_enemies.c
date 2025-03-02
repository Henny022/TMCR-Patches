#include <entity.h>
#include <object.h>
#include <item.h>
#include <enemy.h>
#include "base.h"
#include <object/itemOnGround.h>

void OctorokGolden_OnDeath(Entity* this) {
    EnemyCreateDeathFX((Enemy*)this, 0xff, 0);

    int flag = this->type2;
    int item = peek_item_for_global_flag_with_default(flag, ITEM_RUPEE100);

    ItemOnGroundEntity* entity = (ItemOnGroundEntity*) CreateObjectWithParent(this, GROUND_ITEM, get_item_id(item), get_item_subvalue(item));
    if (entity != NULL) {
        entity->base.timer = 5;
        entity->unk_86 = global2flag(flag);
    }
    DeleteThisEntity();
}

void RopeGolden_OnDeath(Entity* this) {
    EnemyCreateDeathFX((Enemy*)this, 0xff, 0);

    int flag = this->type2;
    int item = peek_item_for_global_flag_with_default(flag, ITEM_RUPEE100);

    ItemOnGroundEntity* entity = (ItemOnGroundEntity*) CreateObjectWithParent(this, GROUND_ITEM, get_item_id(item), get_item_subvalue(item));
    if (entity != NULL) {
        entity->base.timer = 5;
        entity->unk_86 = global2flag(flag);
    }
    DeleteThisEntity();
}

void TektiteGolden_OnDeath(Entity* this) {
    EnemyCreateDeathFX((Enemy*)this, 0xff, 0);

    int flag = this->type2;
    int item = peek_item_for_global_flag_with_default(flag, this->type ? ITEM_RUPEE200 : ITEM_RUPEE100);

    ItemOnGroundEntity* entity = (ItemOnGroundEntity*) CreateObjectWithParent(this, GROUND_ITEM, get_item_id(item), get_item_subvalue(item));
    if (entity != NULL) {
        entity->base.timer = 5;
        entity->unk_86 = global2flag(flag);
    }
    DeleteThisEntity();
}
