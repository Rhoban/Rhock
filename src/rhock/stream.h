#ifndef _RHOCK_STREAM_H
#define _RHOCK_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "obj.h"

#ifndef RHOCK_STREAM_W
#define RHOCK_STREAM_W
#endif

// Packet heades
#define RHOCK_STREAM_HEADER1 0xff
#define RHOCK_STREAM_HEADER2 0xaa

// Packet types
#define RHOCK_STREAM_ACK        0x00
#define RHOCK_STREAM_MONITOR    0x01
#define RHOCK_STREAM_STORE      0x02
#define RHOCK_STREAM_PROGRAM    0x03
#define RHOCK_STREAM_PRINT      0x04
#define RHOCK_STREAM_USER       0x05
#define RHOCK_STREAM_RESET      0x06

// Errors
#define RHOCK_OK                0
#define RHOCK_STORE_ALLOC_ERR   1
#define RHOCK_STORE_CHUNK_ERR   2
#define RHOCK_STORE_LOAD_ERR    3
#define RHOCK_UNKNOWN_COMMAND   4
#define RHOCK_PROGRAM_ERROR     5
#define RHOCK_NO_ACK            0xff

struct rhock_packet
{
    uint8_t state;
    uint8_t buffer[RHOCK_STREAM_BUFFER];
    uint8_t size;
    uint8_t checksum;
    uint8_t type;
    uint8_t pointer;
};

// Abstraction layer
extern void rhock_stream_send(uint8_t c) RHOCK_STREAM_W; // To implement
extern void rhock_stream_recv(uint8_t c); // To call

void rhock_stream_begin(uint8_t type);
void rhock_stream_append(uint8_t c);
void rhock_stream_append_int(int32_t i);
void rhock_stream_append_short(uint16_t s);
void rhock_stream_append_value(rhock_value value);
void rhock_stream_end();

uint8_t *rhock_stream_data();
uint8_t rhock_stream_available();
uint8_t rhock_stream_read();
uint16_t rhock_stream_read_short();
uint32_t rhock_stream_read_int();

void rhock_stream_ack(int code);

#ifdef __cplusplus
}
#endif

#endif
