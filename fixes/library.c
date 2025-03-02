#include <room.h>
#include <flags.h>
#include <save.h>
#include <item.h>
#include <message.h>
#include <script.h>

extern EntityData gUnk_080D6578;
extern EntityData gUnk_080D6638;
extern EntityData gUnk_080D6558;
extern EntityData gUnk_080D6618;

void sub_StateChange_HouseInteriors1_Library2F(void) {
    LoadRoomEntityList(&gUnk_080D6578);
    if (CheckLocalFlag(MIZUKAKI_BOOK_ALLBACK) == 0) {
        LoadRoomEntityList(&gUnk_080D6638);
        return;
    }
    LoadRoomEntityList(&gUnk_080D6618);
}

extern EntityData gUnk_080D6714;
extern EntityData gUnk_additional_9_HouseInteriors1_Library1F;
extern EntityData gUnk_additional_8_HouseInteriors1_Library1F;

void sub_StateChange_HouseInteriors1_Library1F(void) {
    if (gSave.global_progress > 4) {
        LoadRoomEntityList(&gUnk_080D6714);
    }
    //todo maybe re-add some condition to go back to normal
    if (CheckGlobalFlag(MIZUKAKI_START) && CheckLocalFlag(MIZUKAKI_KOBITO)) {
        LoadRoomEntityList(&gUnk_additional_9_HouseInteriors1_Library1F);
    } else {
        LoadRoomEntityList(&gUnk_additional_8_HouseInteriors1_Library1F);
    }
}


extern u32 gUnk_080DB910;

u32 sub_unk3_TownMinishHoles_LibraryBookshelf(void) {
    if (CheckGlobalFlag(MIZUKAKI_START) && !CheckLocalFlag(MIZUKAKI_BOOK_ALLBACK)) {
        gRoomVars.properties[1] = &gUnk_080DB910;
    }
    return 1;
}

extern EntityData gUnk_080DB8F0;
extern EntityData gUnk_additional_a_TownMinishHoles_LibraryBookshelf;
extern void sub_0801AFE4(void);

void sub_StateChange_TownMinishHoles_LibraryBookshelf(void) {
    LoadRoomEntityList(&gUnk_080DB8F0);
    // todo maybe replace flippers check instead of removing it
    if (CheckGlobalFlag(MIZUKAKI_START)) {
        LoadRoomEntityList(&gUnk_additional_a_TownMinishHoles_LibraryBookshelf);
    }
    sub_0801AFE4();
}


extern EntityData gUnk_080DBA08;

void sub_StateChange_TownMinishHoles_LibrariBookHouse(void) {
    if (GetInventoryValue(ITEM_FLIPPERS) || !CheckLocalFlag(MIZUKAKI_BOOK_ALLBACK)) {
        LoadRoomEntityList(&gUnk_080DBA08);
    }
    sub_0801AFE4();
}


void sub_0806B004(Entity* this, ScriptExecutionContext* context) {
    static const u16 messageIndices[5] = { TEXT_INDEX(TEXT_TOWN_MINISH1, 0x11), TEXT_INDEX(TEXT_TOWN_MINISH1, 0x01),
                                           TEXT_INDEX(TEXT_TOWN_MINISH1, 0x03), TEXT_INDEX(TEXT_TOWN_MINISH1, 0x05),
                                           TEXT_INDEX(TEXT_TOWN_MINISH1, 0x13) };
    int idx = 0;

    if (CheckGlobalFlag(MIZUKAKI_START)) {
        if (CheckLocalFlag(MIZUKAKI_BOOK_ALLBACK)) {
            idx = 3;
            if (CheckLocalFlag(KHOUSE51_00) == 0) {
                idx = 2;
                context->condition = 1;
                SetLocalFlag(KHOUSE51_00);
            }
        } else {
            idx = 1;
            SetLocalFlag(MIZUKAKI_KOBITO);
        }
    }
    MessageNoOverlap(messageIndices[idx], this);
}

// lake minish start bookquest even when you have flippers

extern const u16 gUnk_0810A35A[];

void sub_08060270(Entity* this) {
    u32 index;


    if (CheckGlobalFlag(MIZUKAKI_START) == 0) {
        index = 0;
        SetGlobalFlag(MIZUKAKI_START);
    }
    else if (GetInventoryValue(ITEM_FLIPPERS) == 0) {
        index = 1;
    } else {
        index = 3;
        if (CheckLocalFlag(0x76) == 0) {
            index = 2;
            SetLocalFlag(0x76);
        }
    }
    MessageNoOverlap(gUnk_0810A35A[index], this);
}

//todo split into bookquest stuff


extern EntityData gUnk_080F23BC;
extern EntityData gUnk_080F238C;
extern EntityData gUnk_additional_c_HouseInteriors2_Romio;

void sub_StateChange_HouseInteriors2_Romio(void) {
    if (gSave.global_progress > 7) {
        LoadRoomEntityList(&gUnk_080F23BC);
    }
    LoadRoomEntityList(&gUnk_080F238C);
}

extern EntityData gUnk_080F2570;
extern EntityData gUnk_080F2590;
extern EntityData gUnk_080F25C0;
extern EntityData gUnk_080F2600;

void sub_StateChange_HouseInteriors2_Julietta(void) {
    if (!GetInventoryValue(ITEM_QST_BOOK1)) {
        LoadRoomEntityList(&gUnk_080F25C0);
    }
}

extern EntityData gUnk_080F3A48;

void sub_StateChange_HouseInteriors4_MayorLakeCabin(void) {
    if (!GetInventoryValue(ITEM_QST_BOOK3)) {
        LoadRoomEntityList(&gUnk_080F3A48);
    }
    gRoomTransition.player_status.overworld_map_x = 0xf28;
    gRoomTransition.player_status.overworld_map_y = 0x82d;
}


extern EntityData gUnk_080DB4D0;
extern EntityData gUnk_080DB4A0;

void sub_StateChange_TownMinishHoles_MayorsHouse(void) {
    if (!GetInventoryValue(ITEM_FLIPPERS) && !GetInventoryValue(ITEM_QST_BOOK3) && CheckLocalFlag(MIZUKAKI_HINT3_MAYOR))
        LoadRoomEntityList(&gUnk_080DB4D0);
    else
        LoadRoomEntityList(&gUnk_080DB4A0);

    sub_0801AFE4();
}

extern EntityData gUnk_080F2174;
extern EntityData gUnk_080F2194;
extern EntityData gUnk_080F21B4;

void sub_StateChange_HouseInteriors2_DrLeft(void) {
    LoadRoomEntityList(&gUnk_080F2174);
    if (!GetInventoryValue(ITEM_QST_BOOK2) && CheckGlobalFlag(MIZUKAKI_HARIFALL)) {
        LoadRoomEntityList(&gUnk_080F2194);
    }
    if (gRoomTransition.player_status.spawn_type == PL_SPAWN_MINISH) {
        LoadRoomEntityList(&gUnk_080F21B4);
    }
}

extern EntityData gUnk_080D9800;
extern void sub_08058324(u32);

void sub_StateChange_MinishRafters_DrLeft(void) {

    sub_08058324(2);

    if (!CheckGlobalFlag(MIZUKAKI_HARIFALL))
        LoadRoomEntityList(&gUnk_080D9800);
}

//todo split out flippers cave fix

void sub_0806B260(Entity* this, ScriptExecutionContext* context) {
    static const u16 messageIndices[] = {
        TEXT_INDEX(TEXT_TOWN_MINISH1, 0X19),
        TEXT_INDEX(TEXT_TOWN_MINISH1, 0X1a),
        TEXT_INDEX(TEXT_TOWN_MINISH1, 0X22),
        TEXT_INDEX(TEXT_TOWN_MINISH1, 0X27),
    };
    u32 index;

    context->condition = 0;
    index = 2;
    context->condition = 1;
    MessageNoOverlap(messageIndices[index], this);
}


void Trapdoor_Init(Entity* this) {
    this->collisionLayer = 1;
    this->spriteRendering.b3 = 3;
    this->spritePriority.b0 = 7;
    this->subAction = 0;
    this->action = 1;
    InitializeAnimation(this, 0);
}