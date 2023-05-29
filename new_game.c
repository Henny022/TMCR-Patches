#include <save.h>
#include <common.h>
#include <flags.h>
#include <game.h>

extern const u32 n_starting_items;
extern const u8 starting_items[];
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
        for (u32 i = 0; i < n_starting_flags; i++)
        {
            SetGlobalFlag(starting_flags[i]);
        }
        for (u32 i = 0; i < n_starting_items; i++)
        {
            GiveItem(starting_items[i], 0);
        }
        for (u32 i = 0; i < n_starting_fusions; i++)
        {
            WriteBit(gSave.fusedKinstones, starting_fusions[i]);
        }
    }
    if (gSave.name[0] == 0) {
        MemCopy(gUnk_0811E470, &gSave.name, FILENAME_LENGTH - 1);
    }
    return 1;
}
