#ifndef GBA_PROTOCOL_NETWORK_H
#define GBA_PROTOCOL_NETWORK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * send handle for use with await_send
 * evaluates to true for valid values and false on error
 */
typedef int send_handle_t;

/**
 * send data to add on port
 * fails if send buffer is full
 *
 * @param addr
 * @param port
 * @param length number of bytes in data
 * @param data
 * @return handle to be used with await_send, or null handle on error
 */
send_handle_t send(uint8_t addr, uint8_t port, uint8_t length, void *data);
/**
 * block on a previous send
 *
 * @param handle handle returned by send
 */
void await_send(send_handle_t handle);
/**
 * send but blocks until the packet was sent
 */
void send_blocking(uint8_t addr, uint8_t port, uint8_t length, void *data);

/**
 * receive a packet
 * data buffer must fit at least MAX_PACKET_SIZE bytes
 *
 * @param port
 * @param addr out sender address
 * @param size size of data
 * @param data out packet data
 * @return number of bytes in packet or 0 if no packet available
 */
uint8_t recv(uint8_t port, uint8_t *addr, uint8_t size, void *data);
/**
 * recv but blocks until a packet is available
 */
uint8_t recv_blocking(uint8_t port, uint8_t *addr, uint8_t size, void *data);

#ifdef __cplusplus
}
#endif


#endif //GBA_PROTOCOL_NETWORK_H
