#include <room.h>

extern void sub_0801AFE4(void);
extern EntityData gUnk_080DB238;

void sub_StateChange_MinishHouseInteriors_Librari(void) {
    LoadRoomEntityList(&gUnk_080DB238);
    sub_0801AFE4();
}