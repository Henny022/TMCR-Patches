#include "network.h"

#define MAX_PACKET_SIZE 32

struct Buffer {
    uint8_t busy;
    uint8_t addr;
    uint8_t port;
    uint8_t length;
    uint8_t data[MAX_PACKET_SIZE];
};

struct ScriptIO {
    Buffer send_buffer;
    Buffer recv_buffer[4];
};
#define gScriptIO (*(volatile ScriptIO*)0x02038560)


send_handle_t send(uint8_t addr, uint8_t port, uint8_t length, void *data) {
    if (gScriptIO.send_buffer.busy)
    {
        return 0;
    }
    
    gScriptIO.send_buffer.addr = addr;
    gScriptIO.send_buffer.port = port;
    gScriptIO.send_buffer.length = length;
    for (int i = 0; i < length; i++)
    {
        gScriptIO.send_buffer.data[i] = ((uint8_t*)data)[i];
    }
    gScriptIO.send_buffer.busy = 1;
    return 1;
}

void await_send(send_handle_t handle){
    if (handle == 0)
    {
        return;
    }
    while (gScriptIO.send_buffer.busy);
};

void send_blocking(uint8_t addr, uint8_t port, uint8_t length, void *data){
    while (gScriptIO.send_buffer.busy);
    send(addr, port, length, data);
    while (gScriptIO.send_buffer.busy);
}

uint8_t recv(uint8_t port, uint8_t* addr, uint8_t size, void* data) {
    if (port >= 4)
    {
        return 0;
    }
    if (gScriptIO.recv_buffer[port].busy != 1)
    {
        return 0;
    }
    if (size < gScriptIO.recv_buffer[port].length)
    {
        // TODO
        return 0;
    }
    
    *addr = gScriptIO.recv_buffer[port].addr;
    for (int i = 0; i < gScriptIO.recv_buffer[port].length; i++)
    {
        ((uint8_t*)data)[i] = gScriptIO.recv_buffer[port].data[i];
    }
    gScriptIO.recv_buffer[port].busy = 2;
    return gScriptIO.recv_buffer[port].length;
}

uint8_t recv_blocking(uint8_t port, uint8_t* addr, uint8_t size, void* data) {
    if (port >= 4)
    {
        return 0;
    }
    uint8_t length = 0;
    while (length == 0) {
        length = recv(port, addr, size, data);
    }  
    return length;
}

