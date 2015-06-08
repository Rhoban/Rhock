#include <stdlib.h>
#include "clock.h"
#include "event.h"
#include "context.h"
#include "chain.h"
#include "vm.h"
#include "stream.h"
#include "store.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
    
struct rhock_vm
{
    rhock_memory_addr objs;
    rhock_memory_addr programs;
    int monitor_last;
    int monitor_dt;
};

struct rhock_vm *rhock_get_vm()
{
    return (struct rhock_vm*)rhock_get(0,0);
}

void rhock_vm_init()
{
    // Resets all the memory
    rhock_memory_init();

    // Allocate space for the virtual machine itself
    rhock_alloc(sizeof(struct rhock_vm), 1);

    // Initializing the struct
    struct rhock_vm *vm = rhock_get_vm();

    // Sets the programs chain
    vm->objs = RHOCK_LAST;
    vm->programs = RHOCK_LAST;

    // Disabling monitoring
    vm->monitor_dt = 0;
    
    // Call the on-reset event one time
    rhock_on_reset();

    // Triggers the init of the store
    rhock_store_init();
}

void rhock_vm_monitor(int frequency)
{
    struct rhock_vm *vm = rhock_get_vm();
    vm->monitor_dt = 1000/frequency;
    vm->monitor_last = rhock_gettime();
}

void rhock_output_monitor()
{
    struct rhock_vm *vm = rhock_get_vm();
    rhock_memory_addr addr = vm->objs;

    // Sending states of programs
    rhock_stream_begin(RHOCK_STREAM_MONITOR);
    while (addr != RHOCK_LAST) {
        struct rhock_obj *obj = rhock_get_obj(addr);
        rhock_stream_append_int(obj->id);
        rhock_memory_addr prog = rhock_vm_get_program(obj->id);
        if (prog != RHOCK_NULL) {
            struct rhock_program *program = rhock_get_program(prog);
            rhock_stream_append(program->state);
            rhock_stream_append(program->error);
        } else {
            rhock_stream_append(0xff);
            rhock_stream_append(0x00);
        }
        addr = rhock_chain_next(addr);
    }
    rhock_stream_end();

    rhock_on_monitor();
}

uint8_t rhock_vm_tick()
{
    uint8_t ticked = 0;
    uint8_t should_clean = 0;
    struct rhock_vm *vm = rhock_get_vm();
    rhock_memory_addr prog = vm->programs;

    if (vm->monitor_dt != 0) {
        int t = rhock_gettime();
        if (t-vm->monitor_last > vm->monitor_dt) {
            vm->monitor_last = t;
            rhock_output_monitor();
        }
    }

    // For each program
    while (prog != RHOCK_LAST) {
        struct rhock_program *program = rhock_get_program(prog);
        rhock_memory_addr ctx = program->contexts;

        // For each context
        while (ctx != RHOCK_LAST) {
            struct rhock_context *context = rhock_get_context(ctx);
            ticked += rhock_context_tick(context);
            ctx = rhock_chain_next(ctx);
        }
        
        if (program->state == RHOCK_PROGRAM_KILLED) {
            should_clean = 1;
        }
        prog = rhock_chain_next(prog);
    }

    if (should_clean) {
        rhock_vm_clean();
    }

    return ticked;
}

void rhock_vm_add_program(rhock_memory_addr addr)
{
    struct rhock_vm *vm = rhock_get_vm();
    if (vm->programs == RHOCK_LAST) {
        rhock_on_reset();
        rhock_stream_begin(RHOCK_STREAM_RESET);
        rhock_stream_end();
    }

    rhock_chain_add(&vm->programs, addr);
}

void rhock_vm_remove_program(rhock_memory_addr addr)
{
    struct rhock_vm *vm = rhock_get_vm();
    rhock_chain_remove(&vm->programs, addr);

    if (vm->programs == RHOCK_LAST) {
        // When no program are running, let's call the on-reset event
        rhock_on_all_stopped();
    }
}

rhock_memory_addr rhock_vm_get_program(uint32_t id)
{
    struct rhock_vm *vm = rhock_get_vm();
    rhock_memory_addr prog = vm->programs;
    while (prog != RHOCK_LAST) {
        struct rhock_program *program = rhock_get_program(prog);
        if (program->obj->id == id) {
            return prog;
        }
        prog = rhock_chain_next(prog);
    }

    return RHOCK_NULL;
}

rhock_memory_addr rhock_vm_get_programs()
{
    struct rhock_vm *vm = rhock_get_vm();

    return vm->programs;
}

rhock_memory_addr rhock_vm_create_obj()
{
    struct rhock_vm *vm = rhock_get_vm();
    rhock_memory_addr obj = rhock_alloc(sizeof(struct rhock_obj), 1);
    if (obj != RHOCK_NULL) {
        // Adding the object to the chain
        rhock_chain_add(&vm->objs, obj);
    }

    return obj;
}

void rhock_vm_remove_obj(rhock_memory_addr addr)
{
    struct rhock_vm *vm = rhock_get_vm();
    rhock_chain_remove(&vm->objs, addr);
    rhock_store_remove(rhock_get_obj(addr));
    rhock_free(addr);
}

rhock_memory_addr rhock_vm_get_objs()
{
    struct rhock_vm *vm = rhock_get_vm();

    return vm->objs;
}

rhock_memory_addr rhock_vm_get_obj(uint32_t id)
{
    rhock_memory_addr addr = rhock_vm_get_objs();

    // Searching the objects chain for a matching object
    while (addr != RHOCK_LAST) {
        struct rhock_obj *obj = rhock_get_obj(addr);
        if (obj->id == id) {
            return addr;
        }
        addr = rhock_chain_next(addr);
    }

    return RHOCK_NULL;
}

void rhock_vm_clear_objs()
{
    struct rhock_vm *vm = rhock_get_vm();
    rhock_memory_addr addr = vm->objs;

    // Removing every program
    while (addr != RHOCK_LAST) {
        struct rhock_obj *obj = rhock_get_obj(addr);
        rhock_program_kill(obj->id);
        rhock_memory_addr prog = rhock_vm_get_program(obj->id);
        if (prog != RHOCK_NULL) {
            rhock_program_unload(prog);
        }
        rhock_store_remove(obj);
        addr = rhock_chain_next(addr);
    }

    // Clearing the objects chain
    while (vm->objs != RHOCK_LAST) {
        rhock_chain_free(&vm->objs);
    }
}

char rhock_vm_obj_load(const uint8_t *ptr, uint32_t size)
{
    struct rhock_vm *vm = rhock_get_vm();
    rhock_memory_addr addr = rhock_alloc(sizeof(struct rhock_obj), 1);

    if (addr != RHOCK_NULL) {
        struct rhock_obj *obj = rhock_get_obj(addr);

        if (rhock_obj_load(obj, ptr, size)) {
            rhock_program_kill(obj->id);
            rhock_memory_addr other = rhock_vm_get_obj(obj->id);
            if (other != RHOCK_NULL) {
                rhock_vm_remove_obj(other);
            }
            rhock_chain_add(&vm->objs, addr);
            return 1;
        } else {
            rhock_free(addr);
        }
    }

    return 0;
}

void rhock_vm_clean()
{
    struct rhock_vm *vm = rhock_get_vm();
    uint8_t removed = 0;

    do {
        rhock_memory_addr prog = vm->programs;
        while (prog != RHOCK_LAST) {
            struct rhock_program *program = rhock_get_program(prog);
            if (program->state ==  RHOCK_PROGRAM_KILLED) {
                rhock_chain_remove(&vm->programs, prog);
                removed = 1;
                break;
            }
            prog = rhock_chain_next(prog);
        }
    } while (removed > 0);
}

void rhock_vm_emit(int event, rhock_value *values, int size)
{
    struct rhock_vm *vm = rhock_get_vm();
    rhock_memory_addr prog = vm->programs;

    // For each program
    while (prog != RHOCK_LAST) {
        struct rhock_program *program = rhock_get_program(prog);
        rhock_memory_addr ctx = program->contexts;

        // For each context
        while (ctx != RHOCK_LAST) {
            struct rhock_context *context = rhock_get_context(ctx);
            if (context->state == RHOCK_THREAD_WAITING && context->waitEvent == event) {
                rhock_context_call_event(context, values, size);
            }
            ctx = rhock_chain_next(ctx);
        }
        prog = rhock_chain_next(prog);
    }
}
