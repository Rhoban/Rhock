#ifndef _RHOCK_OBJ
#define _RHOCK_OBJ

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "memory.h"

/**
 * Converts a native method name to address
 */
#define RHOCK_NATIVE_TO_ADDR(n) \
    (0xff00|n)

#define RHOCK_IS_NATIVE(addr) \
    ((addr>>8)==0xff)

#define RHOCK_ADDR_TO_NATIVE(addr) \
    (0x00ff&addr)

/**
 * An address in the program
 */
#define rhock_addr uint16_t

/**
 * The identifier of a variable
 */
#define rhock_var uint8_t

/**
 * The identifier of a entry
 */
#define rhock_entry uint8_t

/**
 * A value
 */
typedef int32_t rhock_value;

/**
 * Values as it is encoded in the binary
 */
#define RHOCK_VALUE_TO_NUMBER(val) \
    (val/1000.0)
#define RHOCK_NUMBER_TO_VALUE(val) \
    (val*1000)

#define RHOCK_VALUE_TO_INT(val) \
    (val/1000)

/**
 * Bit-level value conversions
 */
#define RHOCK_FLOAT_TO_INT(val) \
    (*((int*)(val)))
#define RHOCK_INT_TO_FLOAT(val) \
    (*((float*)(int)))

/**
 * Entry points
 */
#define RHOCK_THREAD_RUNNING  0
#define RHOCK_THREAD_STOPPED  1
#define RHOCK_THREAD_PAUSED   2
#define RHOCK_THREAD_WAITING  3

#define RHOCK_OBJ_NAME_SIZE   16

/**
 * Structure of an object
 */
struct rhock_obj
{
    uint32_t id;                // 4
    uint16_t crc16;             // 2
    uint16_t size;              // 2
    const char *name;           // 16
    rhock_var variables;        // 1
    const uint8_t *defaults;    // 0
    rhock_entry entries;        // 1
    const uint8_t *entry;       // 0
    const uint8_t *data;        // 0
    const uint8_t *start;       // 0
                                // 26
} __attribute__((packed));

struct rhock_obj *rhock_get_obj(rhock_memory_addr addr);

/**
 * Size of the header without entries and data
 */
#define RHOCK_HEADER 26

/**
 * Computes the CRC16 sum for an object
 */
uint16_t rhock_obj_crc(struct rhock_obj *obj);

/**
 * Size of the data
 */
uint16_t rhock_data_size(struct rhock_obj *obj);

/**
 * This will try to read the data, check that the checksum is
 * correct and fill the appropriate struct.
 *
 * Return 1 if it was correctly loaded, 0 else.
 */
uint8_t rhock_obj_load(struct rhock_obj *obj, const uint8_t *data, uint32_t size);
uint16_t rhock_obj_guess_size(const uint8_t *data);

/**
 * Gets the type of the nth entry point
 */
uint8_t rhock_entry_initial(struct rhock_obj *obj, rhock_entry n);

/**
 * Gets the address of the nth entry point
 */
rhock_addr rhock_entry_addr(struct rhock_obj *obj, rhock_entry n);

/**
 * Gets the default value of a variable
 */
rhock_value rhock_default_value(struct rhock_obj *obj, rhock_var num);

#ifdef __cplusplus
}
#endif

#endif
