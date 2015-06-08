#include <stdio.h>
#include "memory.h"

static uint8_t memory_data[RHOCK_MEMORY] __attribute__((aligned(4)));

struct rhock_memory_chunk
{
    // The size of the data in the chunk
    rhock_memory_offset size;
    // Next chunk, contains an address to the chunk that follows, or
    // RHOCK_END if there is nothing more, or RHOCK_NULL
    // if the current chunk is an available chunk
    rhock_memory_addr next;
} __attribute__((__may_alias__, packed));

// The size of an header
#define CHUNK_HEADER (sizeof(rhock_memory_offset)+sizeof(rhock_memory_addr))
// The smallest chunk is an header+1
#define CHUNK_SMALLEST (CHUNK_HEADER+4)
// The chunk of a give naddress
#define CHUNK_AT(addr) ((struct rhock_memory_chunk*)(&memory_data[addr]))
// Is the chunk free ?
#define CHUNK_FREE(c) (c->next==RHOCK_NULL)
// Is the chunk last of a chain ?
#define CHUNK_LAST(c) (c->next==RHOCK_LAST)
// Data of a chunk
#define CHUNK_DATA(c) (((uint8_t *)c)+CHUNK_HEADER)

/**
 * Initializes the memory, this creates a simple chunk that contains all the memory
 */
void rhock_memory_init()
{
    struct rhock_memory_chunk *c = CHUNK_AT(0);
    c->size = RHOCK_MEMORY - CHUNK_HEADER;
    c->next = RHOCK_NULL;
}

/**
 * This will defrag free blocks that are contiguous in the memory
 */
void rhock_defrag()
{
    rhock_memory_addr addr = 0;
    rhock_memory_addr last_free = RHOCK_NULL;

    while (addr < RHOCK_MEMORY) {
        struct rhock_memory_chunk *c = CHUNK_AT(addr);

        if (CHUNK_FREE(c)) {
            // If a chunk is free, try to defrag it with the last free if it directly
            // follow it
            if (last_free == RHOCK_NULL) {
                last_free = addr;
            } else {
                struct rhock_memory_chunk *merge = CHUNK_AT(last_free);
                merge->size += CHUNK_HEADER+c->size;
            }
        } else {
            last_free = RHOCK_NULL;

            // This will happen when reallocating a block which is directly followed by
            // free space
            if (c->next == addr+CHUNK_HEADER+c->size) {
                struct rhock_memory_chunk *merge = CHUNK_AT(addr+CHUNK_HEADER+c->size);
                c->size += CHUNK_HEADER+merge->size;
                c->next = merge->next;
            }
        }

        addr += CHUNK_HEADER + c->size;
    }
}

/**
 * Allocates the given size in the memory
 */
rhock_memory_addr rhock_alloc(rhock_memory_offset size, uint8_t cont)
{
    if (size&0x3) {
        // This will keep the memory aligned on 4-bytes words
        size = ((size>>2)+1)<<2;
    }
    rhock_memory_addr addr = 0;
    rhock_memory_addr result = RHOCK_NULL;
    rhock_memory_addr prev = RHOCK_NULL;

    while (size > 0 && addr < RHOCK_MEMORY) {
        struct rhock_memory_chunk *c = CHUNK_AT(addr);
        rhock_memory_offset currentChunkSize = CHUNK_HEADER+c->size;
        if (CHUNK_FREE(c)) {
            uint8_t useChunk = 0;
            if (c->size >= size) {
                // Too much room in this chunk, let's try to split it
                rhock_memory_offset otherSize = c->size-size;
                if (otherSize >= CHUNK_SMALLEST) {
                    // We can break this chunk into parts
                    struct rhock_memory_chunk *next = CHUNK_AT(addr+CHUNK_HEADER+size);
                    next->size = otherSize-CHUNK_HEADER;
                    next->next = RHOCK_NULL;
                    c->size = size;
                    currentChunkSize = CHUNK_HEADER+size;
                }
                size = 0;
                useChunk = 1;
            } else if (!cont) {
                // Not enough room in this chunk
                size -= c->size;
                useChunk = 1;
            }
            if (useChunk) {
                c->next = RHOCK_LAST;
                if (result == RHOCK_NULL) {
                    result = addr;
                }
                if (prev != RHOCK_NULL) {
                    CHUNK_AT(prev)->next = addr;
                }
                prev = addr;
            }
        }
        addr += currentChunkSize;
    }

    if (size > 0 && result != RHOCK_NULL) {
        rhock_free(result);
        result = RHOCK_NULL;
    }

    return result;
}

/**
 * Re-allocation
 */
uint8_t rhock_realloc(rhock_memory_addr addr, int32_t new_size)
{
    struct rhock_memory_chunk *c = NULL;

    // Count the size of the current chain
    while (addr < RHOCK_MEMORY) {
        c = CHUNK_AT(addr);
        new_size -= c->size;
        addr = c->next;
        if (addr == RHOCK_LAST) {
            break;
        }
    }
    if (c == NULL) {
        return 0;
    }

    // If we are not OK, allocate memory elsewhere and chain it
    if (new_size > 0) {
        rhock_memory_addr missing = rhock_alloc(new_size, 0);
        if (missing == RHOCK_NULL) {
            return 0;
        }
        c->next = missing;
    }

    rhock_defrag();

    return 1;
}

/**
 * Gets a pointer to the given memory address/offset
 */
uint8_t *rhock_get(rhock_memory_addr addr, rhock_memory_offset offset)
{
    while (addr < RHOCK_MEMORY && addr != RHOCK_LAST) {
        struct rhock_memory_chunk *c = CHUNK_AT(addr);

        if (c->size > offset) {
            return CHUNK_DATA(c)+offset;
        } else {
            offset -= c->size;
        }

        addr = c->next;
    }

    return NULL;
}

/**
 * De-allocate the given addr in the memory
 */
void rhock_free(rhock_memory_addr addr)
{
    if (addr == RHOCK_NULL || addr == RHOCK_LAST) {
        return;
    }

    while (addr < RHOCK_MEMORY) {
        // Getting the chunk and marking it as free
        struct rhock_memory_chunk *c = CHUNK_AT(addr);
        addr = c->next;
        c->next = RHOCK_NULL;

        // Going to the next chunk
        if (addr == RHOCK_LAST) {
            break;
        }
    }

    // Arrange memory
    rhock_defrag();
}

rhock_memory_addr rhock_next_block(rhock_memory_addr block)
{
    struct rhock_memory_chunk *c = CHUNK_AT(block);

    if (CHUNK_LAST(c) || CHUNK_FREE(c)) {
        return RHOCK_LAST;
    } else {
        return c->next;
    }
}

void rhock_attach(rhock_memory_addr block1, rhock_memory_addr block2)
{
    struct rhock_memory_chunk *c1 = CHUNK_AT(block1);
    c1->next = block2;
}

void rhock_detach(rhock_memory_addr block)
{
    struct rhock_memory_chunk *c = CHUNK_AT(block);
    c->next = RHOCK_LAST;
}

#ifdef RHOCK_DEBUG_ENABLE
void rhock_memory_dump()
{
    rhock_memory_addr addr = 0;

    while (addr < RHOCK_MEMORY) {
        struct rhock_memory_chunk *c = CHUNK_AT(addr);
        if (addr&0x3) {
            printf("!NOT ALIGNED! ");
        }
        printf("CHUNK [%04x: dsize=%d, ", addr, c->size);
        if (CHUNK_FREE(c)) {
            printf("free]\n");
        } else if (CHUNK_LAST(c)) {
            printf("last]\n");
        } else {
            printf("next: %04x]\n", c->next);
        }
        addr += CHUNK_HEADER + c->size;
    }
}

void rhock_meminfo(int *total_o, int *used_o, int *overhead_o)
{
    rhock_memory_addr addr = 0;
    uint32_t overhead = 0;
    uint32_t used = 0;

    while (addr < RHOCK_MEMORY) {
        struct rhock_memory_chunk *c = CHUNK_AT(addr);

        if (!CHUNK_FREE(c)) {
            overhead += CHUNK_HEADER;
            used += (CHUNK_HEADER+c->size);
        }
        addr += CHUNK_HEADER + c->size;
    }
    if (total_o != NULL) *total_o = RHOCK_MEMORY;
    if (used_o != NULL) *used_o = used;
    if (overhead_o != NULL) *overhead_o = overhead;
}
#endif
