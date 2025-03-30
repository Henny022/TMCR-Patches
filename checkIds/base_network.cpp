#include <cstdint>
#include "../network/network.h"

extern "C" {

int peek_item_for_global_flag(int flag) {
    uint16_t packet = flag;
    send(0xfu, 0, 2, &packet);
    uint8_t addr = 0;
    uint16_t item = 0;
    recv_blocking(0, &addr, 2, &item);
    return item;
}

int get_item_for_global_flag(int flag) {
    uint16_t packet = flag;
    send(0xfu, 1, 2, &packet);
    uint8_t addr = 0;
    uint16_t item = 0;
    recv_blocking(1, &addr, 2, &item);
    return item;
}

}