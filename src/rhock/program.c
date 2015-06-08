#include <stdio.h>
#include "program.h"
#include "context.h"
#include "chain.h"
#include "event.h"
#include "context.h"
#include "stream.h"

struct rhock_program *rhock_get_program(rhock_memory_addr addr)
{
    return (struct rhock_program *)rhock_get(addr, 0);
}

rhock_memory_addr rhock_program_load(struct rhock_obj *obj)
{
    uint16_t k;
    rhock_memory_addr addr = rhock_alloc(sizeof(struct rhock_program), 1);

    if (addr != RHOCK_NULL) {
        struct rhock_program *program = rhock_get_program(addr);
        program->obj = obj;
        program->state = RHOCK_PROGRAM_RUNNING;
        program->error = RHOCK_ERROR_NO_ERROR;
        program->variables = rhock_alloc(obj->variables*sizeof(rhock_value), 0);
        if (program->variables == RHOCK_NULL && obj->variables > 0) {
            rhock_program_crash(program, RHOCK_ERROR_ALLOCATE_VARS);
        }
        for (k=0; k<obj->variables; k++) {
            rhock_program_set_var(program, k, rhock_default_value(obj, k));
        }
        program->contexts = RHOCK_LAST;
        rhock_vm_add_program(addr);
        rhock_program_init(addr);
    }

    return addr;
}

uint8_t rhock_program_error(rhock_memory_addr addr)
{
    return rhock_get_program(addr)->error;
}

void rhock_program_crash(struct rhock_program *program, uint8_t error)
{
    if (program->state != RHOCK_PROGRAM_CRASHED) {
        // Marking the program as crashed with an error state
        program->state = RHOCK_PROGRAM_CRASHED;
        program->error = error;
        // Stopping all contexts
        rhock_memory_addr addr = program->contexts;
        while (addr != RHOCK_LAST) {
            struct rhock_context *context = rhock_get_context(addr);
            rhock_on_stop(context);
            if (context != NULL) {
                context->state = RHOCK_THREAD_STOPPED;
            }
            addr = rhock_chain_next(addr);
        }
    }
}
    
void rhock_program_free_contexts(rhock_memory_addr addr)
{
    struct rhock_program *program = (struct rhock_program *)rhock_get(addr, 0);

    rhock_memory_addr context = program->contexts;
    while (context != RHOCK_LAST) {
        // Call the context_free method for all context
        rhock_context_free(context);
        context = rhock_chain_next(context);
    }
    // And free all the chain
    rhock_chain_free(&program->contexts);
}

void rhock_program_unload(rhock_memory_addr addr)
{
    struct rhock_program *program = rhock_get_program(addr);

    // Free the contexts
    rhock_program_free_contexts(addr);

    // Remove the program from the vm
    rhock_vm_remove_program(addr);

    // Free the variables space
    rhock_free(program->variables);

    // Free the program memory
    rhock_free(addr);
}

void rhock_program_init(rhock_memory_addr addr)
{
    // Erase all contexts
    rhock_program_free_contexts(addr);

    rhock_entry e;
    struct rhock_program *program = rhock_get_program(addr);
    // We add the entries backward, because the chain reverses the order of elements
    // Thus, the nth entry will be the nth link of the chain
    for (e=program->obj->entries; e>0; e--) {
        // Allocate the new context
        rhock_memory_addr ctx = rhock_context_alloc();
        if (ctx == RHOCK_NULL) {
            rhock_program_crash(program, RHOCK_ERROR_ALLOCATE_CONTEXT);
        } else {
            rhock_chain_add(&program->contexts, ctx);
            struct rhock_context *context = rhock_get_context(ctx);
            // Configure the new context
            context->stack = rhock_alloc(RHOCK_VSTACK_SIZE*sizeof(rhock_value), 0);
            context->program = program;
            context->state = rhock_entry_initial(program->obj, e-1);
            context->data = program->obj->data;
            context->data_size = rhock_data_size(program->obj);
            rhock_context_reset(context, rhock_entry_addr(program->obj, e-1));
            if (context->stack == RHOCK_NULL) {
                rhock_program_crash(program, RHOCK_ERROR_ALLOCATE_STACK);
            }
        }
    }
}

struct rhock_context *rhock_program_ctx_by_id(struct rhock_program *program, uint8_t id)
{
    rhock_memory_addr ctx = program->contexts;

    while (ctx != RHOCK_LAST) {
        if (id == 0) {
            return rhock_get_context(ctx);
        }
        id--;
        ctx = rhock_chain_next(ctx);
    }

    return NULL;
}

rhock_value rhock_program_get_var(struct rhock_program *program, uint8_t var)
{
    if (var < program->obj->variables) {
        // Getting the appropriate variable
        rhock_value *value_ptr = (rhock_value*)rhock_get(program->variables, var*4);
        rhock_value value = *value_ptr;
        return value;
    } else {
        // If the variable doesn't exists, crashes the program
        rhock_program_crash(program, RHOCK_ERROR_VARIABLE);
        return 0;
    }
}

void rhock_program_set_var(struct rhock_program *program, uint8_t var, rhock_value val)
{
    if (var < program->obj->variables) {
        // Sets the variable
        rhock_value *value_ptr = (rhock_value*)rhock_get(program->variables, var*4);
        *value_ptr = val;
    } else {
        // If the variable is not correct, the program crashes
        rhock_program_crash(program, RHOCK_ERROR_VARIABLE);
    }
}

void rhock_program_run(uint32_t id)
{
    rhock_memory_addr obj = rhock_vm_get_obj(id);
    if (obj != RHOCK_NULL) {
        rhock_memory_addr prog = rhock_vm_get_program(id);

        if (prog == RHOCK_NULL) {
            // Loading it
            rhock_program_load(rhock_get_obj(obj));
        } else {
            struct rhock_program *program = rhock_get_program(prog);
            if (program->state == RHOCK_PROGRAM_FREEZED) {
                program->state = RHOCK_PROGRAM_RUNNING;
               
                // This will resumes all the context
                rhock_memory_addr ctx = program->contexts;
                while (ctx != RHOCK_LAST) {
                    struct rhock_context *context = rhock_get_context(ctx);
                    if (context->state == RHOCK_THREAD_RUNNING) {
                        rhock_context_resume_native(context);
                    }
                    ctx = rhock_chain_next(ctx);
                }
            }
        }

        // Trigger the event
        rhock_on_run(rhock_get_program(prog));
    }
}

void rhock_program_freeze(uint32_t id)
{
    rhock_memory_addr addr = rhock_vm_get_program(id);
    if (addr != RHOCK_NULL) {
        // Marking the program as freezed
        struct rhock_program *program = rhock_get_program(addr);
        program->state = RHOCK_PROGRAM_FREEZED;
        // Callling the event
        rhock_on_freeze(program);
        // Pauses the native of all runnin process
        rhock_memory_addr ctx = program->contexts;
        while (ctx != RHOCK_LAST) {
            struct rhock_context *context = rhock_get_context(ctx);
            if (context->state == RHOCK_THREAD_RUNNING) {
                rhock_context_pause_native(context);
            }
            ctx = rhock_chain_next(ctx);
        }
    }
}

void rhock_program_kill(uint32_t id)
{
    rhock_memory_addr addr = rhock_vm_get_program(id);
    if (addr != RHOCK_NULL) {
        // Unload the program
        rhock_program_unload(addr);
    }
}

void rhock_program_killall()
{
    rhock_memory_addr addr;
    while ((addr = rhock_vm_get_programs()) != RHOCK_LAST) {
        rhock_program_unload(addr);
    }
}

#define RHOCK_PROGRAM_RUN       0
#define RHOCK_PROGRAM_FREEZE    1
#define RHOCK_PROGRAM_KILL      2
#define RHOCK_PROGRAM_UNLOAD    3
#define RHOCK_PROGRAM_GET_NAME  4

char rhock_program_process()
{
    if (rhock_stream_available()==5) {
        uint8_t inst = rhock_stream_read();
        uint32_t id = rhock_stream_read_int();
        switch (inst) {
            case RHOCK_PROGRAM_RUN:
                rhock_program_run(id);
                return 1;
            case RHOCK_PROGRAM_FREEZE:
                rhock_program_freeze(id);
                return 1;
            case RHOCK_PROGRAM_KILL:
                rhock_program_kill(id);
                return 1;
            case RHOCK_PROGRAM_UNLOAD: {
                rhock_program_kill(id);
                rhock_memory_addr addr = rhock_vm_get_obj(id);
                if (addr != RHOCK_NULL) {
                    rhock_vm_remove_obj(addr);
                }
                return 1;
               }
            case RHOCK_PROGRAM_GET_NAME: {
                rhock_memory_addr addr = rhock_vm_get_obj(id);
                if (addr != RHOCK_NULL) {
                    int k;
                    struct rhock_obj *obj = rhock_get_obj(addr);
                    rhock_stream_begin(RHOCK_STREAM_PROGRAM);
                    rhock_stream_append(RHOCK_PROGRAM_GET_NAME);
                    rhock_stream_append_int(id);
                    for (k=0; k<RHOCK_OBJ_NAME_SIZE; k++) {
                        rhock_stream_append(obj->name[k]);
                    }
                    rhock_stream_end();
                }
                return 1;
            }
        }
    }

    return 0;
}
