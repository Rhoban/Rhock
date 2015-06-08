#ifndef _RHOCK_PRINT_H
#define _RHOCK_PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef RHOCK_PRINT_W
#define RHOCK_PRINT_W
#endif

// These methods are weak and can be overloaded
void rhock_print(uint8_t c) RHOCK_PRINT_W;
void rhock_print_value(float value) RHOCK_PRINT_W;
void rhock_print_int(uint32_t value) RHOCK_PRINT_W;
void rhock_println() RHOCK_PRINT_W;

// Send data to the print stream
void rhock_print_stream(uint8_t c);
void rhock_print_value_stream(float value);
void rhock_print_int_stream(uint32_t);
void rhock_println_stream();

#ifdef __cplusplus
}
#endif

#endif
