#include <main.h>
#include <common.h>

#include "debug/mgba.h"

typedef void(*InitFunc)(void);
extern const InitFunc custom_init[];
extern const u32 n_custom_init;

extern void InitOverlays(void);
extern void InitSound(void);
extern void InitSaveData(void);
extern void InitSaveHeader(void);
extern void MessageInitialize(void);
extern void ReadKeyInput(void);
extern bool32 SoftResetKeysPressed(void);
extern void MessageMain(void);
extern void AudioMain(void);
extern void WaitForNextFrame(void);

extern const InitFunc sTaskHandlers[];
extern u32 gRand;

void AgbMain(void) {
    // Initialization
    mgba_debug_enable();
    InitOverlays();
    InitSound();
    InitDMA();
    InitSaveData();
    InitSaveHeader();
    InitVBlankDMA();
    gUnk_02000010.field_0x4 = 0xc1;
    InitFade();
    DmaCopy32(3, BG_PLTT, gPaletteBuffer, BG_PLTT_SIZE);
    SetBrightness(1);
    MessageInitialize();
    ResetPalettes();
    gRand = 0x1234567;
    MemClear(&gMain, sizeof(gMain));
    SetTask(TASK_TITLE);

    for (u32 i = 0; i < n_custom_init; i++)
    {
        custom_init[i]();
    }

    // Game Loop
    while (TRUE) {
        ReadKeyInput();
        if (SoftResetKeysPressed()) {
            DoSoftReset();
        }

        switch (gMain.sleepStatus) {
            case SLEEP:
                SetSleepMode();
                break;
            case DEFAULT:
            default:
                if (gMain.pauseFrames != 0) {
                    do {
                        VBlankIntrWait();
                    } while (--gMain.pauseFrames);
                }

                if (gMain.pauseCount != 0) {
                    int cnt;
                    gMain.pauseCount--;
                    cnt = gMain.pauseInterval;
                    while (cnt-- > 0) {
                        VBlankIntrWait();
                    }
                }

                gMain.ticks++;
                sTaskHandlers[gMain.task]();
                MessageMain();
                FadeMain();
                AudioMain();
                break;
        }
        WaitForNextFrame();
    }
}
