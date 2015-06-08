#define RHOCK_STREAM_W __attribute__((weak))
#include <stdio.h>
#include "event.h"
#include "vm.h"
#include "stream.h"
#include "config.h"
#include "store.h"

static struct rhock_packet in = {0}, out = {0};

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
void rhock_stream_send(uint8_t c)
{
    EM_ASM_INT({
        rhock_stream_send($0);
    }, c);
}
#else
void rhock_stream_send(uint8_t c)
{
}
#endif

void rhock_stream_ack(int code)
{
    if (code != RHOCK_NO_ACK) {
        rhock_stream_begin(RHOCK_STREAM_ACK);
        rhock_stream_append(code);
        rhock_stream_end();
    }
}

void rhock_stream_process()
{
    switch (in.type) {
        case RHOCK_STREAM_MONITOR:
            rhock_vm_monitor(rhock_stream_read_int());
            break;
        case RHOCK_STREAM_STORE:
            rhock_stream_ack(rhock_store_process());
            break;
        case RHOCK_STREAM_PROGRAM:
            if (!rhock_program_process()) {
                rhock_stream_ack(RHOCK_PROGRAM_ERROR);
            } else {
                rhock_stream_ack(RHOCK_OK);
            }
            break;
        default:
            if (!rhock_on_packet(in.type)) {
                rhock_stream_ack(RHOCK_UNKNOWN_COMMAND);
            }
            break;
    }
}

void rhock_stream_recv(uint8_t c)
{
    switch (in.state) {
        case 0:
            if (c == RHOCK_STREAM_HEADER1) {
                in.state++;
            }
            break;
        case 1:
            if (c == RHOCK_STREAM_HEADER2) {
                in.state++;
            } else {
                in.state = 0;
            }
            break;
        case 2:
            in.type = c;
            in.state++;
            break;
        case 3:
            in.size = c;
            in.state++;
            if (c == 0) {
                in.state++;
            }
            in.checksum = 0;
            in.pointer = 0;
            if (in.size > RHOCK_STREAM_BUFFER) {
                in.state = 0;
            }
            break;
        case 4:
            in.buffer[in.pointer++] = c;
            in.checksum += c;
            if (in.pointer >= in.size) {
                in.state++;
            }
            break;
        case 5:
            in.state = 0;
            if (c == in.checksum) {
                in.pointer = 0;
                rhock_stream_process();
            }
            break;
    }
}

void rhock_stream_begin(uint8_t type_)
{
    out.size = 0;
    out.checksum = 0;
    out.type = type_;
}

void rhock_stream_append(uint8_t c)
{
    if (out.size < RHOCK_STREAM_BUFFER) {
        out.checksum += c;
        out.buffer[out.size++] = c;
    }
}

void rhock_stream_append_int(int32_t i)
{
    rhock_stream_append((i>>24)&0xff);
    rhock_stream_append((i>>16)&0xff);
    rhock_stream_append((i>>8)&0xff);
    rhock_stream_append((i>>0)&0xff);
}

void rhock_stream_append_short(uint16_t s)
{
    rhock_stream_append((s>>8)&0xff);
    rhock_stream_append((s>>0)&0xff);
}

void rhock_stream_append_value(rhock_value value)
{
    rhock_stream_append((value>>24)&0xff);
    rhock_stream_append((value>>16)&0xff);
    rhock_stream_append((value>>8)&0xff);
    rhock_stream_append((value>>0)&0xff);
}

void rhock_stream_end()
{
    uint8_t k;
    rhock_stream_send(RHOCK_STREAM_HEADER1);
    rhock_stream_send(RHOCK_STREAM_HEADER2);
    rhock_stream_send(out.type);
    rhock_stream_send(out.size);
    for (k=0; k<out.size; k++) {
        rhock_stream_send(out.buffer[k]);
    }
    rhock_stream_send(out.checksum);
}

uint8_t rhock_stream_read()
{
    if (in.pointer < RHOCK_STREAM_BUFFER) {
        return in.buffer[in.pointer++];
    } else {
        return 0;
    }
}

uint16_t rhock_stream_read_short()
{
    uint16_t i = 0;
    i |= rhock_stream_read()<<8;
    i |= rhock_stream_read()<<0;

    return i;
}

uint32_t rhock_stream_read_int()
{
    uint32_t i = 0;
    i |= rhock_stream_read()<<24;
    i |= rhock_stream_read()<<16;
    i |= rhock_stream_read()<<8;
    i |= rhock_stream_read()<<0;

    return i;
}

uint8_t *rhock_stream_data()
{
    return &in.buffer[in.pointer];
}

uint8_t rhock_stream_available()
{
    return in.size-in.pointer;
}
