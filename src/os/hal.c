#include <stdio.h>
#include <time.h>
#include <rhock/clock.h>
#include <rhock/print.h>
#include <rhock/native.h>
#include <rhock/stream.h>

void rhock_print(uint8_t c)
{
    printf("%c", c);
}

void rhock_print_value(float v)
{
    printf("%g", v);
}

void rhock_println()
{
    printf("\n");
}

uint32_t rhock_gettime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec*1000+ts.tv_nsec/1000000);
}

void rhock_stream_putc(uint8_t c)
{
    printf("%c", c);
}
