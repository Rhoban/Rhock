/**
 * Defaults weak symbols for event that can be overloaded
 */

#define RHOCK_EVENT __attribute__((weak))
#include "event.h"

void rhock_on_all_stopped()
{
}

void rhock_on_reset()
{
}

void rhock_on_run(struct rhock_program *program)
{
}

void rhock_on_freeze(struct rhock_program *program)
{
}

void rhock_on_kill(struct rhock_program *program)
{
}

extern void rhock_on_start(struct rhock_context *context)
{
}

extern void rhock_on_pause(struct rhock_context *context)
{
}

extern void rhock_on_stop(struct rhock_context *context)
{
}

void rhock_on_monitor()
{
}

char rhock_on_packet(uint8_t type)
{
    return 0;
}
