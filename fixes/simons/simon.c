#include <flags.h>
#include <room.h>
#include <asm.h>
#include <sound.h>

extern u8* gUnk_080F0D58[4];
extern Entity* gUnk_080F0CB8[15];
extern u8* gUnk_080F0E08[];
extern TileEntity gUnk_080F0E1C[];

extern void LoadSmallChestTile2(TileEntity*);

void sub_StateChange_SimonsSimulation_Main(void) {
    u32 r;
    u32 index;
    index = 0;
    if (CheckGlobalFlag(LV4_CLEAR)) {
        index = 1;
    }
    if (CheckGlobalFlag(LV5_CLEAR)) {
        index = 2;
    }
    if (CheckGlobalFlag(GAMECLEAR)) {
        index = 3;
    }
    r = Random();
    index = gUnk_080F0D58[index][r & 0x1f];
    LoadRoomEntityList((EntityData*)gUnk_080F0CB8[index & 0xF]);
    index >>= 4;
    r >>= 8;
    index = gUnk_080F0E08[index][r & 0x1F];
    if (!CheckLocalFlag(0xC6)) {
        //SetLocalFlag(0xC6); don't do this - instead have the flag be set on chest open
        index = 0xE;
    }
    LoadSmallChestTile2(&gUnk_080F0E1C[index]);
    SoundReq(SONG_STOP_BGM);
}
