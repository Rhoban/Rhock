#include <stdio.h>
#include "chain.h"

void rhock_chain_add(rhock_memory_addr *chain, rhock_memory_addr item)
{
    rhock_attach(item, *chain);
    *chain = item;
}

void rhock_chain_remove(rhock_memory_addr *chain, rhock_memory_addr item)
{
    if (*chain == item) {
        // If the item is the head of the chain, sets the chain to the next block
        // of the item itself
        *chain = rhock_next_block(item);
        rhock_detach(item);
        rhock_free(item);
    } else {
        // Else, we search for the item in the list, and link its previous item
        // to its next
        rhock_memory_addr prev = RHOCK_LAST;
        rhock_memory_addr curr = *chain;

        while (curr != RHOCK_LAST) {
            if (curr == item) {
                // Item is found
                rhock_attach(prev, rhock_next_block(curr));
                rhock_detach(item);
                rhock_free(item);
                return;
            }
            prev = curr;
            curr = rhock_next_block(curr);
        }
    }
}

void rhock_chain_free(rhock_memory_addr *chain)
{
    // Freeing the chain is simply done using rhock_free()
    rhock_free(*chain);
    *chain = RHOCK_LAST;
}

rhock_memory_addr rhock_chain_next(rhock_memory_addr item)
{
    return rhock_next_block(item);
}
