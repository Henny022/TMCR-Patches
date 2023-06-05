#include <flags.h>

extern void ClearFlagArray(const u16*);
extern void ResetTimerFlags(void);

void ResetTmpFlags(void) {
    static const u16 sClearFlags[] = {
        FLAG_BANK_2, BILL00_SHICHOU_00,     //
        FLAG_BANK_2, BILL0A_YADO_TAKARA_00, //
        FLAG_BANK_2, BILL0C_SCHOOLR_00,     //
        FLAG_BANK_1, MACHI00_00,            //
        FLAG_BANK_1, MACHI00_02,            //
        FLAG_BANK_2, MHOUSE06_00,           //
        FLAG_BANK_2, MHOUSE14_00,           //
        FLAG_BANK_2, MHOUSE2_00_02,         //
        FLAG_BANK_2, MHOUSE2_01_T0,         //
        FLAG_BANK_2, MHOUSE2_02_KAME,       //
        FLAG_BANK_2, SHOP00_ITEM_01,        //
        FLAG_BANK_2, SHOP01_CAFE_01,        //
        0xFFFF,
    };

    ResetTimerFlags();
    ClearFlagArray(sClearFlags);

    if (!CheckGlobalFlag(WATERBEAN_PUT))
        ClearGlobalFlag(WATERBEAN_OUT);
}