#include <global.h>
#include <area.h>

int peek_item_for_global_flag(int flag);
int get_item_for_global_flag(int flag);

#define unknown_item_value 0xFFFF

inline int peek_item_for_global_flag_with_default(int flag, int default_value) {
    int item = peek_item_for_global_flag(flag);
    if (item == unknown_item_value) item = default_value;
    return item;
}

inline int get_item_for_global_flag_with_default(int flag, int default_value) {
    int item = get_item_for_global_flag(flag);
    if (item == unknown_item_value) item = default_value;
    return item;
}

inline int get_item_id(int item)
{
    return item & 0xff;
}

inline int get_item_subvalue(int item)
{
    return (item >> 8) & 0xff;
}

inline int get_item_from_value_and_subvalue(int value, int subvalue)
{
    return ((value & 0xff) | ((subvalue & 0xff) << 8));
}

inline int local2global(int flag)
{
    return gArea.localFlagOffset + flag;
}

inline int flag2global(int flag)
{
    u32 type;
    u32 index;

    if (flag != 0) {
        index = flag & 0x3ff;
        type = (flag & 0xc000) >> 0xe;
        switch (type) {
            case 2:
                // room flag
                return -1;
            case 0:
                // local flag
                return local2global(index);
            case 1:
                // global flag
                return index;
        }
    }
    return -1;
}

inline int global2flag(int flag)
{
    return (1 << 0xe) | flag;
}
