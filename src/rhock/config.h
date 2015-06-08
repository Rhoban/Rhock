#ifndef _RHOCK_CONFIG
#define _RHOCK_CONFIG

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Memory size, this will be allocated at the begining of the program,
 * and used by the virtual machine
 */
#define RHOCK_MEMORY    (5*1024)

/**
 * Number of elements in the value stack
 */
#define RHOCK_VSTACK_SIZE       8

/**
 * Nuber of elements in the call stack
 */
#define RHOCK_CSTACK_SIZE       8

/**
 * The number of maximum native methods that are defined
 * Can be 16, 32, 64, 128 or 256
 */
#define RHOCK_NATIVE_MAX_64

/**
 * The number of opcode to do at each tick
 */
#define RHOCK_OPCODE_PER_TICK   32

/**
 * Size of the stream packet buffer
 */
#define RHOCK_STREAM_BUFFER     128

/**
 * Debug all operations
 */
#define RHOCK_DEBUG_ENABLE

#ifdef RHOCK_DEBUG_ENABLE
#define RHOCK_DEBUG(...) \
    printf(__VA_ARGS__);
#else
#define RHOCK_DEBUG(...)
#endif

#ifdef __cplusplus
}
#endif

#endif
