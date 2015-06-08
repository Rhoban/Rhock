#ifndef _RHOCK_STORE_H
#define _RHOCK_STORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "obj.h"

#ifndef RHOCK_STORE
#define RHOCK_STORE
#endif

/**
 * Process a remote command
 */
int rhock_store_process();

/**
 * Abstraction layer
 */
const uint32_t rhock_store_pages() RHOCK_STORE;
const uint32_t rhock_store_page_size() RHOCK_STORE;
const uint8_t *rhock_store_page_get(uint32_t page) RHOCK_STORE;
void rhock_store_page_write(uint32_t page, uint8_t *data) RHOCK_STORE;

/**
 * Store abstraction layer
 */
char rhock_store_page_is_free(uint32_t page);
uint32_t rhock_store_page_round(uint32_t size);
char rhock_store_alloc(uint32_t size);
char rhock_store_append(char *data, uint32_t size);
char rhock_store_load();
void rhock_store_remove(struct rhock_obj *obj);
void rhock_store_reset();
void rhock_store_init();

#ifdef __cplusplus
}
#endif

#endif
