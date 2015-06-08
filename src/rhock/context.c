#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "context.h"
#include "opcode.h"
#include "program.h"
#include "clock.h"

struct rhock_context *rhock_get_context(rhock_memory_addr addr)
{
    return (struct rhock_context *)rhock_get(addr, 0);
}

rhock_memory_addr rhock_context_alloc()
{
    return rhock_alloc(sizeof(struct rhock_context), 1);
}

void rhock_context_free(rhock_memory_addr addr)
{
    struct rhock_context *context = rhock_get_context(addr);
    if (context->state != RHOCK_THREAD_STOPPED) {
        rhock_on_stop(context);
    }

    rhock_free(context->stack);
}

uint8_t rhock_context_tick(struct rhock_context *context)
{
    uint16_t op;

    if (context->program->state == RHOCK_PROGRAM_RUNNING
            && context->state == RHOCK_THREAD_RUNNING) {
        for (op=0; op<RHOCK_OPCODE_PER_TICK; op++) {
            if (!rhock_opcode_tick(context)) {
                break;
            }
            if (context->program->state != RHOCK_PROGRAM_RUNNING ||
                    context->state != RHOCK_THREAD_RUNNING) {
                break;
            }
        }
        return 1;
    }  else {
        return 0;
    }
}

void rhock_context_reset(struct rhock_context *context, rhock_addr addr)
{
    context->pc = addr;
    context->vsp = 0;
    context->csp = 0;
    context->fp = 0;
    context->native = NULL;
}

rhock_value *rhock_context_stack_ptr(struct rhock_context *context, uint16_t index)
{
    uint32_t offset = index*sizeof(rhock_value);

    rhock_value *value = (rhock_value*)rhock_get(context->stack, offset);
    if (value == NULL) {
        rhock_realloc(context->stack, offset*2);
        value = (rhock_value*)rhock_get(context->stack, offset);
    }
    
    return value;
}

void rhock_context_push(struct rhock_context *context, rhock_value value)
{
    rhock_value *val = rhock_context_stack_ptr(context, context->vsp++);
    if (val != NULL) {
        *val = value;
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_OVERFLOW);
    }
}

void rhock_context_pushi(struct rhock_context *context, int32_t i)
{
    rhock_value *value = rhock_context_stack_ptr(context, context->vsp++);
    if (value != NULL) {
        *value = i;
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_OVERFLOW);
    }
}

void rhock_context_pushf(struct rhock_context *context, float f)
{
    rhock_value *value = rhock_context_stack_ptr(context, context->vsp++);
    if (value != NULL) {
        *value = RHOCK_NUMBER_TO_VALUE(f);
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_OVERFLOW);
    }
}

rhock_value rhock_context_stack_nth(struct rhock_context *context, uint8_t off)
{
    if (context->vsp > off) {
        rhock_value *value = rhock_context_stack_ptr(context, context->vsp-1-off);
        if (value != NULL) {
            return *value;
        } else {
            rhock_program_crash(context->program, RHOCK_ERROR_STACK_ILLEGAL);
            return 0;
        }
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_UNDERFLOW);
        return 0;
    }
}

rhock_value rhock_context_stack_top(struct rhock_context *context)
{
    return rhock_context_stack_nth(context, 0);
}

rhock_value *rhock_context_stack_frame(struct rhock_context *context, uint16_t arg)
{
    rhock_value *value = rhock_context_stack_ptr(context, context->fp+arg);
    if (value != NULL) {
        return value;
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_ILLEGAL);
        return NULL;
    }
}

rhock_value rhock_context_pop(struct rhock_context *context)
{ 
    if (context->vsp > 0) {
        rhock_value *value = rhock_context_stack_ptr(context, --context->vsp);
        return *value;
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_UNDERFLOW);
        return 0;
    }
}

int32_t rhock_context_popi(struct rhock_context *context)
{
    if (context->vsp > 0) {
        rhock_value *val = rhock_context_stack_ptr(context, --context->vsp);
        return *val;
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_UNDERFLOW);
        return 0;
    }
}

float rhock_context_popf(struct rhock_context *context)
{
    if (context->vsp > 0) {
        rhock_value *val = rhock_context_stack_ptr(context, --context->vsp);
        return RHOCK_VALUE_TO_NUMBER(*val);
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_UNDERFLOW);
        return 0;
    }
}

void rhock_context_smash(struct rhock_context *context, uint8_t n)
{
    if (context->vsp >= n) {
        context->vsp -= n;
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_STACK_UNDERFLOW);
    }
}

void rhock_context_call(struct rhock_context *context, rhock_addr pc)
{
    if (context->csp < RHOCK_CSTACK_SIZE) {
        context->cstack[context->csp] = context->pc;
        context->pc = pc;
        context->fpstack[context->csp] = context->fp;
        context->fp = context->vsp;
        context->csp++;
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_CSTACK_OVERFLOW);
    }
}

void rhock_context_call_event(struct rhock_context *context, rhock_value *values, int size)
{
    while (size > 0) {
        rhock_context_push(context, values[--size]);
    }
    context->state = RHOCK_THREAD_RUNNING;
}

void rhock_context_ret(struct rhock_context *context)
{
    if (context->csp > 0) {
        context->csp--;
        context->vsp = context->fp;
        context->fp = context->fpstack[context->csp];
        context->pc = context->cstack[context->csp];
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_CSTACK_UNDERFLOW);
    }
}

void rhock_context_start(struct rhock_context *context, rhock_entry id)
{
    if (context->state == RHOCK_THREAD_STOPPED) {
        rhock_context_reset(context, rhock_entry_addr(context->program->obj, id));
    } 
    if (context->state != RHOCK_THREAD_RUNNING) {
        context->state = RHOCK_THREAD_RUNNING;
        rhock_context_resume_native(context);
    }
}

void rhock_context_stop(struct rhock_context *context)
{
    if (context->state != RHOCK_THREAD_STOPPED) {
        context->state = RHOCK_THREAD_STOPPED;
        rhock_on_stop(context);
    }
}

void rhock_context_pause(struct rhock_context *context)
{
    if (context->state != RHOCK_THREAD_PAUSED) {
        context->state = RHOCK_THREAD_PAUSED;
        rhock_context_pause_native(context);
    }
}

void rhock_context_start_by_id(struct rhock_program *caller, struct rhock_program *target, rhock_entry id)
{
    struct rhock_context *context = rhock_program_ctx_by_id(target, id);
    if (context != NULL) {
        rhock_context_start(context, id);
    } else {
        rhock_program_crash(caller, RHOCK_ERROR_INVALID_PROCESS);
    }
}

void rhock_context_stop_by_id(struct rhock_program *caller, struct rhock_program *target, rhock_entry id)
{
    struct rhock_context *context = rhock_program_ctx_by_id(target, id);
    if (context != NULL) {
        rhock_context_stop(context);
    } else {
        rhock_program_crash(caller, RHOCK_ERROR_INVALID_PROCESS);
    }
}

void rhock_context_pause_by_id(struct rhock_program *caller, struct rhock_program *target, rhock_entry id)
{
    struct rhock_context *context = rhock_program_ctx_by_id(target, id);
    if (context != NULL) {
        rhock_context_pause(context);
    } else {
        rhock_program_crash(caller, RHOCK_ERROR_INVALID_PROCESS);
    }
}

#ifdef RHOCK_DEBUG_ENABLE
void rhock_context_dump(struct rhock_context *context)
{
    uint16_t s;
    printf("# stack: | ");
    for (s=0; s<context->vsp; s++) {
        rhock_value *val = rhock_context_stack_ptr(context, s);
        printf("%g | ", RHOCK_VALUE_TO_NUMBER(*val));
    }
    printf("\n");
}
#endif

void rhock_context_pause_native(struct rhock_context *context)
{
    // Store the time elapsed in the nativeStart value
    context->nativeStart = rhock_gettime()-context->nativeStart;
    rhock_on_pause(context);
}

void rhock_context_resume_native(struct rhock_context *context)
{
    // This will restore a "fake" nativeStart, to make the elapsed corect
    // even after a context resume
    context->nativeStart = rhock_gettime()-context->nativeStart;
    rhock_on_start(context);
}

void rhock_context_emit(struct rhock_context *context, int id, int args)
{
    int k;
    rhock_value values[args];
    for (k=args-1; k>=0; k--) {
        rhock_value value = rhock_context_stack_nth(context, k);
        values[k] = value;
    }
    rhock_vm_emit(id, values, args);
    rhock_context_smash(context, args);
}

void rhock_context_wait(struct rhock_context *context, int id)
{
    context->waitEvent = id;
    context->state = RHOCK_THREAD_WAITING;
}
