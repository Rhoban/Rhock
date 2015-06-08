#ifndef _RHOCK_OPCODE
#define _RHOCK_OPCODE

#ifdef __cplusplus
extern "C" {
#endif

#include "context.h"

/**
 * This ticks exactly one opcode on the appropriate context, and
 * returns 1 if the current thread should be ticked, 0 else
 */
uint8_t rhock_opcode_tick(struct rhock_context *context);

#ifdef __cplusplus
}
#endif

#endif
