#include <save.h>
#include <common.h>
#include <flags.h>

u32 FinalizeSave(void) {
    if (gSave.invalid || gSave.initialized != 1) {
        gSave.invalid = 0;
        gSave.initialized = 1;
        gSave.global_progress = 1;
        gSave.stats.health = 24;
        gSave.stats.maxHealth = 24;
        gSave.saved_status.area_next = 0x22;
        gSave.saved_status.room_next = 0x15; // links room
        gSave.saved_status.start_anim = Direction8ToAnimationState(DirectionSouth);
        gSave.saved_status.spawn_type = PL_SPAWN_DEFAULT;
        gSave.saved_status.layer = 1;
        gSave.saved_status.start_pos_x = 0x58;
        gSave.saved_status.start_pos_y = 0x38;
        SetGlobalFlag(0x246);
        {
            extern u32 gRand;
            gRand = 0x248AA711;
        }
    }
    if (gSave.name[0] == 0) {
        MemCopy(gUnk_0811E470, &gSave.name, FILENAME_LENGTH - 1);
    }
    return 1;
}
