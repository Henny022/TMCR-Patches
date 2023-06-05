#include <room.h>
#include <flags.h>
#include <script.h>
#include <message.h>
#include <npc.h>

extern EntityData gUnk_080F62E4;
extern EntityData gUnk_080F6324;
extern EntityData windtribe_tower_door_blocker;

void sub_StateChange_WindTribeTower_Floor2(void) {
    if (!CheckGlobalFlag(WARP_EVENT_END) || !CheckLocalFlag(SORA_ELDER_TALK1ST)) {
        LoadRoomEntityList(&gUnk_080F62E4); // we remove the door blocking npc in ea
        if (!CheckGlobalFlag(WARP_EVENT_END)) {
            LoadRoomEntityList(&windtribe_tower_door_blocker); // so we add them back in here
        }
    } else {
        if (CheckLocalFlag(SORA_ELDER_RECOVER)) {
            LoadRoomEntityList(&gUnk_080F6324);
        }
    }
}

void sub_0806C9F8(Entity* this, ScriptExecutionContext* context) {
    (void) context;
    static const u16 messageIndices[] = {
        TEXT_INDEX(TEXT_WIND_TRIBE, 0x04),
        TEXT_INDEX(TEXT_WIND_TRIBE, 0x10),
        0x0,
    };
    u32 flagAsBool = 0;
    if (CheckGlobalFlag(WARP_EVENT_END) && CheckLocalFlag(SORA_ELDER_TALK1ST)) {
        flagAsBool = 1;
    }
    MessageNoOverlap(messageIndices[flagAsBool], this);
}


void sub_0806C99C(Entity* this, ScriptExecutionContext* context) {
    (void) context;
    static const u16 messageIndices[] = {
        TEXT_INDEX(TEXT_WIND_TRIBE, 0x03),
        TEXT_INDEX(TEXT_WIND_TRIBE, 0x0a),
        TEXT_INDEX(TEXT_WIND_TRIBE, 0x15),
        TEXT_INDEX(TEXT_WIND_TRIBE, 0x0f),
    };
    u32 flagAsBool = 0; //normalerweise

    if (CheckGlobalFlag(WARP_EVENT_END) && CheckLocalFlag(SORA_ELDER_TALK1ST)) {
        flagAsBool = 2;
    }
    if (CheckLocalFlag(SORA_ELDER_RECOVER)) {
        flagAsBool++;
    }
    MessageNoOverlap(messageIndices[flagAsBool], this);
}

extern u16 script_WindTribespeople6;

void sub_0806C7D4(Entity* this) {
    if (this->interactType == '\x02') {
        this->action = 3;
        this->interactType = 0;
        sub_0806F118(this);
    } else {
        sub_0807DD94(this, NULL);
        if ((this->type2 == 3) && (!CheckGlobalFlag(WARP_EVENT_END) || !CheckLocalFlag(SORA_ELDER_TALK1ST)) && (CheckLocalFlag(SORA_ELDER_RECOVER)) && (CheckRoomFlag(0))) {
            this->type2 = 7;
            sub_0807DD80(this, &script_WindTribespeople6);
        }
    }
}