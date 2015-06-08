#ifndef _RHOCK_MEMORY_H
#define _RHOCK_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "config.h"

#if RHOCK_MEMORY>0xfff0
typedef uint32_t rhock_memory_addr;
typedef uint32_t rhock_memory_offset;
#else
typedef uint16_t rhock_memory_addr;
typedef uint16_t rhock_memory_offset;
#endif

#define RHOCK_LAST   ((rhock_memory_addr)(-2))
#define RHOCK_NULL   ((rhock_memory_addr)(-1))

/**
 * Initializes the memory
 */
void rhock_memory_init();

/**
 * Allocates the given size in the memory
 * Returns RHOCK_NULL if it is not possible
 */
rhock_memory_addr rhock_alloc(rhock_memory_offset size, uint8_t cont);

/**
 * Re-allocate the given pointer
 * Returns 1 if the operation was a success, 0 else
 */
uint8_t rhock_realloc(rhock_memory_addr addr, int32_t new_size);

/**
 * Gets a pointer to the given memory address/offset
 * Returns NULL if there is an error
 */
uint8_t *rhock_get(rhock_memory_addr addr, rhock_memory_offset offset);

/**
 * Gets the next memory block
 */
rhock_memory_addr rhock_next_block(rhock_memory_addr block);

/**
 * Attach a memory block to another
 */
void rhock_attach(rhock_memory_addr block1, rhock_memory_addr block2);
void rhock_detach(rhock_memory_addr block);

/**
 * De-allocate the given addr in the memory
 */
void rhock_free(rhock_memory_addr addr);

#ifdef RHOCK_DEBUG_ENABLE
void rhock_memory_dump();
void rhock_meminfo(int *total, int *used, int *overhead);
#endif

#ifdef __cplusplus
}
#endif

#endif
