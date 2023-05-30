#include <menu.h>
#include <common.h>
#include <sound.h>
#include <game.h>
#include <subtask.h>
#include <fileselect.h>
#include <main.h>

extern bool32 sub_080A51F4(void);

void sub_080A59C8(void) {
    if (!sub_080A51F4()) {
        return;
    }

    u32 cursor_position = gMenu.field_0x3;

    switch (gInput.newKeys) {
        case DPAD_UP:
            cursor_position = 0;
            break;
        case B_BUTTON:
            gMenu.transitionTimer = 255;
            SetMenuType(3);
            SoundReq(SFX_MENU_CANCEL);
            return;
        case DPAD_DOWN:
            cursor_position = 1;
            break;
        case A_BUTTON:
            gMenu.transitionTimer = 255;
            if (cursor_position == 0) {
                CreateDialogBox(8, 0);
                SetMenuType(2);
                SoundReq(SFX_TEXTBOX_SELECT);
            } else {
                SetMenuType(2);
                SoundReq(SFX_TEXTBOX_SELECT);
                SetFade(5, 8);
                SetTask(2);
            }
            return;
    }

    if (gMenu.field_0x3 != cursor_position) {
        gMenu.field_0x3 = cursor_position;
        SetPopupState(0, cursor_position);
        SoundReq(SFX_TEXTBOX_CHOICE);
    }
}
