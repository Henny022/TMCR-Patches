#include <transitions.h>
#include <room.h>
#include <sound.h>
#include <subtask.h>


extern const Transition gExitList_HouseInteriors2_LinksHouseEntrance[];

extern void sub_08050384(void);

void sub_080A5BB8(void) {
    if (!gFadeControl.active) {
        sub_08050384();
        DoExitTransition((const ScreenTransitionData*) &gExitList_HouseInteriors2_LinksHouseEntrance[0]);
        SetFade(FADE_BLACK_WHITE | FADE_INSTANT, 8);
        sub_080A4E84(2);
        gPauseMenuOptions.unk16 = 16;
    }
}
