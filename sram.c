#include "global.h"

#define SRAM_BASE ((u8*)0x0E000000)

/**
 * read arbitrary data from EEPROM
 * @param address EEPROM address
 * @param data buffer to read into
 * @param size size in bytes to read
 * @return TRUE on success
 */
bool32 DataRead(u32 address, void* data, u32 size) {
    u8* dest = data;
    const u8* src = SRAM_BASE + address;
    for (u32 i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
    return TRUE;
}

/**
 * write arbitrary data to EEPROM
 * @param address EEPROM address
 * @param data buffer to write from
 * @param size size in bytes to write
 * @return TRUE on success
 */
bool32 DataWrite(u32 address, const void* data, u32 size) {
    const u8* src = data;
    u8* dest = SRAM_BASE + address;
    for (u32 i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
    return TRUE;
}

/**
 * compare arbitrary data with EEPROM
 * @param address EEPROM address
 * @param data buffer to compare to
 * @param size size in bytes to compare
 * @return TRUE on success
 */
bool32 DataCompare(u32 address, const void* data, u32 size) {
    const u8* rhs = data;
    const u8* lhs = SRAM_BASE + address;
    for (u32 i = 0; i < size; i++)
    {
        if(lhs[i] != rhs[i]) return FALSE;
    }
    return TRUE;
}
