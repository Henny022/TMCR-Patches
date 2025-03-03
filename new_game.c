#include <save.h>
#include <common.h>
#include <flags.h>
#include <game.h>

#include "checkIds/base.h"
#include "debug/mgba.h"

extern const u32 n_starting_items;
extern const u16 starting_items[];
extern const u32 n_starting_flags;
extern const u16 starting_flags[];
extern const u32 n_starting_fusions;
extern const u8 starting_fusions[];
extern const u8 starting_area;
extern const u8 starting_room;
extern const u8 starting_anim_state;
extern const struct{
    s16 x;
    s16 y;
} starting_pos;

extern u32 GiveItem(u32 item, u32 param_2);

u32 FinalizeSave(void) {
    if (gSave.invalid || gSave.initialized != 1) {
        mgba_print(LOG_DEBUG, "finalizing save");
        gSave.invalid = 0;
        gSave.initialized = 1;
        gSave.global_progress = 1;
        gSave.stats.health = 3*8;
        gSave.stats.maxHealth = 3*8;
        gSave.saved_status.area_next = starting_area;
        gSave.saved_status.room_next = starting_room;
        gSave.saved_status.start_anim = starting_anim_state;
        gSave.saved_status.spawn_type = PL_SPAWN_DEFAULT;
        gSave.saved_status.layer = 1;
        gSave.saved_status.start_pos_x = starting_pos.x;
        gSave.saved_status.start_pos_y = starting_pos.y;
        mgba_print(LOG_DEBUG, "finalizing flags");
        for (u32 i = 0; i < n_starting_flags; i++)
        {
            SetGlobalFlag(starting_flags[i]);
        }
        mgba_print(LOG_DEBUG, "finalizing items");
        for (u32 i = 0; i < n_starting_items; i++)
        {
            int item = starting_items[i];
            GiveItem(get_item_id(item), get_item_subvalue(item));
        }
        mgba_print(LOG_DEBUG, "finalizing fusions");
        for (u32 i = 0; i < n_starting_fusions; i++)
        {
            if (++gSave.kinstones.fusedCount > 99) {
                gSave.kinstones.didAllFusions = 1;
            }
            WriteBit(gSave.kinstones.fusedKinstones, starting_fusions[i]);
        }
        mgba_print(LOG_DEBUG, "finalizing done");
    }
    if (gSave.name[0] == 0) {
        MemCopy(gUnk_0811E470, &gSave.name, FILENAME_LENGTH - 1);
    }
    return 1;
}
