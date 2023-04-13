#include <global.h>
#include "mgba.h"
#include "string.h"

#define REG_DEBUG_ENABLE ((vu16*) 0x4FFF780)
#define REG_DEBUG_FLAGS ((vu16*) 0x4FFF700)
#define REG_DEBUG_STRING ((volatile char*) 0x4FFF600)

int mgba_debug_enable()
{
	*REG_DEBUG_ENABLE = 0xC0DE;
	return *REG_DEBUG_ENABLE == 0x1DEA;
}

void mgba_print(LogLevel level, const char* s)
{
    (void)s;
    for (int i = 0; i < 0x100; i++)
    {
        REG_DEBUG_STRING[i] = s[i];
        if (s[i] == '\0') break;
    }
	*REG_DEBUG_FLAGS = level | 0x100;
}
