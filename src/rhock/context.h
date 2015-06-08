#ifndef _RHOCK_CONTEXT
#define _RHOCK_CONTEXT

#ifdef __cplusplus
extern "C" {
#endif

struct rhock_context;

#include <stdint.h>
#include "obj.h"
#include "config.h"
#include "native.h"
#include "memory.h"

struct rhock_program;

struct rhock_context
{
    // Value stack and stack pointer
    rhock_memory_addr stack;
    uint16_t vsp;
    // Call and frame pointer stacks
    uint16_t cstack[RHOCK_CSTACK_SIZE];
    uint8_t fpstack[RHOCK_CSTACK_SIZE];
    uint8_t csp;
    // Frame pointer
    uint8_t fp;
    // Program counter
    rhock_addr pc;
    // Context type
    uint8_t type;
    // Pointer to the data
    const uint8_t *data;
    // Pre-computed data_size
    uint16_t data_size;
    // State (0: playing, 1: stopped, 2: paused)
    uint8_t state;
    // If currently in a native, this will points to it
    rhock_native native;
    // Elapsed in native
    union {
        uint32_t nativeStart;
        uint32_t waitEvent;
    };
    
    struct rhock_program *program;
};

/**
 * Context allocation
 */
struct rhock_context *rhock_get_context(rhock_memory_addr addr);
rhock_memory_addr rhock_context_alloc();
void rhock_context_free(rhock_memory_addr addr);
void rhock_context_reset(struct rhock_context *context, rhock_addr addr);

/**
 * Ticking a context
 */
uint8_t rhock_context_tick(struct rhock_context *context);

/**
 * Stack control
 */
void rhock_context_push(struct rhock_context *context, rhock_value value);
void rhock_context_pushf(struct rhock_context *context, float f);
void rhock_context_pushi(struct rhock_context *context, int32_t i);

rhock_value rhock_context_stack_top(struct rhock_context *context);
rhock_value rhock_context_stack_nth(struct rhock_context *context, uint8_t off);
rhock_value *rhock_context_stack_frame(struct rhock_context *context, uint16_t arg);

rhock_value rhock_context_pop(struct rhock_context *context);
float rhock_context_popf(struct rhock_context *context);
int32_t rhock_context_popi(struct rhock_context *context);

void rhock_context_smash(struct rhock_context *context, uint8_t n);

/**
 * Call/ret
 */
void rhock_context_call(struct rhock_context *context, rhock_addr addr);
void rhock_context_call_event(struct rhock_context *context, rhock_value *values, int size);
void rhock_context_ret(struct rhock_context *context);

/**
 * Control the execution of threads
 */
void rhock_context_start(struct rhock_context *context, rhock_entry id);
void rhock_context_stop(struct rhock_context *context);
void rhock_context_pause(struct rhock_context *context);

void rhock_context_start_by_id(struct rhock_program *caller, struct rhock_program *target, rhock_entry id);
void rhock_context_stop_by_id(struct rhock_program *caller, struct rhock_program *target, rhock_entry id);
void rhock_context_pause_by_id(struct rhock_program *caller, struct rhock_program *target, rhock_entry id);

void rhock_context_pause_native(struct rhock_context *context);
void rhock_context_resume_native(struct rhock_context *context);

void rhock_context_emit(struct rhock_context *context, int id, int args);
void rhock_context_wait(struct rhock_context *context, int id);

#ifdef RHOCK_DEBUG_ENABLE
void rhock_context_dump(struct rhock_context *context);
#endif

#ifdef __cplusplus
}
#endif

#endif
