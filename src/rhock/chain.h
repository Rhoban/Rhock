#ifndef _RHOCK_CHAIN_H
#define _RHOCK_CHAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "memory.h"

void rhock_chain_add(rhock_memory_addr *chain, rhock_memory_addr item);
void rhock_chain_remove(rhock_memory_addr *chain, rhock_memory_addr item);
rhock_memory_addr rhock_chain_next(rhock_memory_addr item);
void rhock_chain_free(rhock_memory_addr *chain);

#ifdef __cplusplus
}
#endif

#endif
