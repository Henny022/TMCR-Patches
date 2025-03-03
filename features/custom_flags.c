#include <flags.h>

#include "../debug/mgba.h"

void SetFlag(u32 flag) {
    mgba_print(LOG_DEBUG, "SetFlag()");
    u32 type;
    u32 index;

    if (flag != 0) {
        index = flag & 0x3ff;
        type = (flag & 0xc000) >> 0xe;
        switch (type) {
            case 2:
                SetRoomFlag(index);
                return;
            case 0:
                SetLocalFlag(index);
                return;
            case 1:
                SetGlobalFlag(index);
                return;
            case 3:
                SetLocalFlagByBank(0xa00, index);
                return;
        }
    }
}

u32 CheckFlags(u32 flags) {
    mgba_print(LOG_DEBUG, "CheckFlags()");
    u32 type;
    u32 index;
    u32 length;
    index = flags & 0x3ff;
    length = (((flags & (0xf0) << 0x6) >> 0xa) + 1);
    type = (flags & 0xc000) >> 0xe;
    switch (type) {
        case 2:
            return CheckRoomFlags(index, length);
        case 0:
            return CheckLocalFlags(index, length);
        case 1:
            return CheckGlobalFlags(index, length);
        case 3:
            return CheckLocalFlagsByBank(0xa00, index, length);
    }
    return 0;
}
