#define RHOCK_PRINT_W __attribute__((weak))
#include "print.h"
#include "stream.h"

// By default, printed values goes to the output print stream
#define RHOCK_PRINT_CHARS   0
#define RHOCK_PRINT_VALUE   1
#define RHOCK_PRINT_LN      2
#define RHOCK_PRINT_BUFFER  32

static uint8_t rhock_print_buffer[RHOCK_PRINT_BUFFER];
static uint8_t rhock_print_pos = 0;

void rhock_print(uint8_t c)
{
    rhock_print_stream(c);
}

void rhock_print_value(float value)
{
    rhock_print_value_stream(value);
}

void rhock_print_int(uint32_t value)
{
    rhock_print_int_stream(value);
}

void rhock_println()
{
    rhock_println_stream();
}

static void rhock_print_buffer_flush()
{
    uint8_t k;
    if (rhock_print_pos >= 0) {
        rhock_stream_begin(RHOCK_STREAM_PRINT);
        rhock_stream_append(RHOCK_PRINT_CHARS);
        for (k=0; k<rhock_print_pos; k++) {
            rhock_stream_append(rhock_print_buffer[k]);
        }
        rhock_stream_end();
        rhock_print_pos = 0;
    }
}


void rhock_print_stream(uint8_t c)
{
    rhock_print_buffer[rhock_print_pos++] = c;
    if (rhock_print_pos >= RHOCK_PRINT_BUFFER) {
        rhock_print_buffer_flush();
    }
}

void rhock_print_int_stream(uint32_t i)
{
    rhock_print_buffer_flush();
    rhock_stream_begin(RHOCK_STREAM_PRINT);
    rhock_stream_append(RHOCK_PRINT_VALUE);
    rhock_stream_append_int(i);
    rhock_stream_end();
}


void rhock_print_value_stream(float value)
{
    rhock_print_buffer_flush();
    rhock_stream_begin(RHOCK_STREAM_PRINT);
    rhock_stream_append(RHOCK_PRINT_VALUE);
    rhock_stream_append_int(RHOCK_NUMBER_TO_VALUE(value));
    rhock_stream_end();
}

void rhock_println_stream()
{
    rhock_print_buffer_flush();
    rhock_stream_begin(RHOCK_STREAM_PRINT);
    rhock_stream_append(RHOCK_PRINT_LN);
    rhock_stream_end();
}
