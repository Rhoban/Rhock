#ifndef _RHOCK_NATIVE_H
#define _RHOCK_NATIVE_H

#ifdef __cplusplus
extern "C" {
#endif

struct rhock_context;

#include <stdint.h>

/**
 * Return values for native
 */
#define RHOCK_NATIVE_CONTINUE   0   // The execution will continue after the native
#define RHOCK_NATIVE_LOOP       1   // The execution will stay in the native
#define RHOCK_NATIVE_WAIT       2 

/**
 * Possible operation
 */
#define RHOCK_NATIVE_OP_ENTER   0
#define RHOCK_NATIVE_OP_TICK    1

/**
 * Tick function
 */
typedef uint8_t (*rhock_native)(struct rhock_context*, uint8_t op, uint32_t elapsed);

#include "context.h"

/**
 * Get a native method
 */
rhock_native rhock_native_get(uint8_t id);

/**
 * Define a native method overload the corresponding symbol
 */
#define RHOCK_2CAT(a, b) \
    a ## b

#ifdef __cplusplus
#define RHOCK_NATIVE_HEADER(name) \
    extern "C" { \
    extern uint8_t rhock_native_ ## name (struct rhock_context *context, uint8_t op, uint32_t elapsed); \
    }
#else
#define RHOCK_NATIVE_HEADER(name) \
    extern uint8_t rhock_native_ ## name (struct rhock_context *context, uint8_t op, uint32_t elapsed);
#endif

#ifdef RHOCK_NO_VM
#define RHOCK_NATIVE_ASSIGN(name, id)
#else
#define RHOCK_NATIVE_ASSIGN(name, id) \
    rhock_native rhock_native ## id = rhock_native_ ## name;
#endif

/**
 * Convenient structure to declare native symbols
 */
#ifdef RHOCK_NATIVE_SYMBOLS
struct rhock_native_symbol
{
    uint8_t id;
    const char *name;
};

extern struct rhock_native_symbol rhock_native_symbols[];
extern int rhock_native_symbols_count;

void rhock_native_symbol_register(const char *name, uint8_t id);

#define RHOCK_NATIVE_DECLARE(name, id) \
    __attribute__((constructor)) \
    void rhock_native_symbol_declare_ ## name () { \
        rhock_native_symbol_register(#name, id); \
    }  \
    RHOCK_NATIVE_HEADER(name) \
    RHOCK_NATIVE_ASSIGN(name, id) 
#else
#define RHOCK_NATIVE_DECLARE(name, id) \
    RHOCK_NATIVE_HEADER(name) \
    RHOCK_NATIVE_ASSIGN(name, id)
#endif

#ifdef __cplusplus
#define RHOCK_NATIVE(name) \
    RHOCK_NATIVE_HEADER(name); \
    uint8_t rhock_native_ ## name (struct rhock_context *context, uint8_t op, uint32_t elapsed)
#else
#define RHOCK_NATIVE(name) \
    uint8_t rhock_native_ ## name (struct rhock_context *context, uint8_t op, uint32_t elapsed)
#endif

/**
 * Pops a value from the stack
 */
#define RHOCK_POPF() \
    rhock_context_popf(context)

/**
 * Pops an int value from the stack
 */
#define RHOCK_POPI() \
    rhock_context_popi(context)

/**
 * Pushes a value on the stack
 */
#define RHOCK_PUSHF(f) \
    rhock_context_pushf(context, f)

/**
 * Pushes an integer on the stack
 */
#define RHOCK_PUSHI(i) \
    rhock_context_pushi(context, i)

/**
 * Pops a string, n is the size of the string and d should be
 * a char* that will point tot eh string (read only)
 */
#define RHOCK_POPS(n, d) \
    { \
        rhock_addr addr = RHOCK_POPI(); \
        if (addr == 0) { \
            d = NULL; \
            n = 0; \
        } else { \
            n = context->data[addr]; \
            d = &context->data[addr+1]; \
        } \
    }

/**
 * Gets the nth value on the stack, 0 is the top,
 * 1 the second value etc.
 */
#define RHOCK_VALUE(n) \
    RHOCK_VALUE_TO_NUMBER(rhock_context_stack_nth(context, n))

#define RHOCK_VALUEI(n) \
    rhock_context_stack_nth(context, n)

/**
 * Smashes the track, this will remove n value from it
 */
#define RHOCK_SMASH(n) \
    rhock_context_smash(context, n)

#define ON_ENTER() \
    if (op == RHOCK_NATIVE_OP_ENTER)

#define ON_TICK() \
    if (op == RHOCK_NATIVE_OP_TICK)

#define ON_ELAPSED() \
    if (RHOCK_VALUE(0) > elapsed) { \
        return RHOCK_NATIVE_WAIT; \
    } else 

#ifdef __cplusplus
}
#endif

#endif
