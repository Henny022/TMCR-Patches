#include <flags.h>
#include <room.h>

extern EntityData gUnk_080DCB10;

void sub_StateChange_MinishCracks_CastorWildsBow(void) {
    if (!CheckLocalFlag(KOBITOANA_06_T0)) {
        LoadRoomEntityList(&gUnk_080DCB10);
    }
}
