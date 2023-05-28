#define NENT_DEPRECATED
#include <entity.h>
#include <object.h>
#include <flags.h>
#include <player.h>
#include <collision.h>
#include <screen.h>
#include <fade.h>
#include <sound.h>
#include "base.h"

typedef struct {
    /*0x00*/ Entity base;
    /*0x68*/ u16 unk_68;
    /*0x6a*/ u8 unk_6a;
} FourElementsEntity;


void sub_080A0424(FourElementsEntity*);
void sub_080A0444(FourElementsEntity*);

void FourElements_Action2(FourElementsEntity* this) {
    sub_080A0424(this);
    sub_080A0444(this);
    if (IsCollidingPlayer(super)) {
        DeleteEntity(super->child);
        super->spriteSettings.draw = 0;
        super->action = 3;
        super->timer = 45;
        gScreen.controls.layerFXControl = 0x640;
        gScreen.controls.alphaBlend = 0;
        {//new code: look up an appropriate flag based on the element originally given
            u32 flag;
            u32 item;
            switch (super->type) {
                case 0x40:
                    flag = MACHI_SET_1;
                    break;
                case 0x41:
                    flag = MACHI_SET_2;
                    break;
                case 0x42:
                    flag = MACHI_SET_4;
                    break;
                case 0x43:
                    flag = MACHI_SET_5;
                    break;
                default:
                    flag = -1;
                    break;
            }
            item = get_item_for_global_flag(flag);
            InitItemGetSequence(get_item_id(item), get_item_subvalue(item), 1);
        }
        sub_0808C650(super, 1);
        SetFade(FADE_BLACK_WHITE | FADE_INSTANT, 2);
        SoundReq(SFX_F8);
        SoundReq(SFX_148);
        SoundReq(BGM_ELEMENT_GET);
        SoundReq(SONG_BGM_0);
    }
}
