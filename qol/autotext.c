#include "global.h"
#include "common.h"
#include "message.h"
#include "sound.h"

#define MESSAGE_ADVANCE_KEYS (A_BUTTON | B_BUTTON | DPAD_ANY | R_BUTTON)
#define MESSAGE_PRESS_ANY_ADVANCE_KEYS ((get_keys(this->message.textSpeed) & MESSAGE_ADVANCE_KEYS) != 0)

typedef enum {
    MSG_IDLE,
    MSG_INIT,
    MSG_UPDATE,
    MSG_OPEN,
    MSG_CLOSE,
    MSG_DIE,
} MessageStatus;

typedef enum {
    RENDER_INIT,
    RENDER_UPDATE,
    RENDER_DIE,
    RENDER_WAIT,
    RENDER_ROLL,
    RENDER_ENQUIRY,
} TextRenderStatus;

void StatusUpdate(u32 status);
u16 RunTextCommand(TextRender* this);
void SetState(u32 status);

static inline u16 get_keys(int speed) {
    switch (speed)
    {
    case 0:
        return gInput.newKeys;
    case 1:
        return gInput.heldKeys;
    case 2:
        return 0xffff;
    default:
        return 0;
    }
}

void TextDispWait(TextRender* this) {
    gMessage.unk = 0;
    if (this->_94 != 0) {
        if (--this->_94 == 0) {
            this->renderStatus = RENDER_ROLL;
        }
    } else if (MESSAGE_PRESS_ANY_ADVANCE_KEYS) {
        SoundReq(SFX_TEXTBOX_SWAP);
        this->_98.bytes.b2 = 0;
        this->renderStatus = RENDER_ROLL;
    } else {
        this->_98.bytes.b2++;
    }
}

void TextDispUpdate(TextRender* this) {
    u32 speedModifier;
    s32 numCharsToRead, pxDrawn;

    if (this->delay != 0) {
        this->delay--;
        return;
    }

    if (this->message.textSpeed > 0) {
        speedModifier = 128;
    } else if ((gInput.heldKeys & B_BUTTON) != 0) {
        speedModifier = 8;
    } else {
        speedModifier = 1;
    }
    this->typeSpeed -= speedModifier;

    if (this->typeSpeed > 0) {
        return;
    }

    numCharsToRead = 0;
    do {
        numCharsToRead++;
        this->typeSpeed += 1;
    } while (this->typeSpeed <= 0);

    pxDrawn = 0;
    do {
        u32 pxCnt = RunTextCommand(this);
        if (pxCnt == 0 || this->delay != 0 || this->newlineDelay != 0)
            break;
        pxDrawn += pxCnt;
        numCharsToRead--;
    } while (0 < numCharsToRead);

    if (pxDrawn != 0) {
        gTextRender.updateDraw = 1;
    } else {
        this->typeSpeed = 0;
    }
}

void TextDispDie(TextRender* this) {
    gMessage.unk = 0;
    SetState(7);
    if ((this->_8e != 1) && (this->_8e == 2 || MESSAGE_PRESS_ANY_ADVANCE_KEYS)) {
        StatusUpdate(MSG_CLOSE);
    }
}
