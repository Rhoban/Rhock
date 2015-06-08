#ifndef _RHOCK_OBJ_WRITE
#define _RHOCK_OBJ_WRITE

#ifdef __cplusplus
extern "C" {
#endif

#include "obj.h"

/**
 * Initializes the structure
 */
void rhock_obj_init(struct rhock_obj *obj);

/**
 * Sets the program id
 */
void rhock_set_id(struct rhock_obj *obj, uint32_t id);

/**
 * Sets the program name
 */
void rhock_set_name(struct rhock_obj *obj, const char *name);

/**
 * Sets the variable
 */
void rhock_set_variables(struct rhock_obj *obj, uint8_t *defaults, uint8_t size);

/**
 * Sets the entries
 */
void rhock_set_entries(struct rhock_obj *obj, uint8_t *entry, uint8_t size);

/**
 * Sets the data
 */
void rhock_set_data(struct rhock_obj *obj, uint8_t *data, rhock_addr size);

/**
 * Write the obj to an output buffer
 */
void rhock_write(struct rhock_obj *obj, uint8_t *buffer);

#ifdef __cplusplus
}
#endif

#endif
