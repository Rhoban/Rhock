#include <stdio.h>
#include <stdlib.h>
#include "store.h"
#include "vm.h"

#define PAGE_SIZE 1024
#define PAGES 10
static uint8_t rom_memory[1024*10];

const uint32_t rhock_store_page_size()
{
    return PAGE_SIZE;
}

const uint32_t rhock_store_pages()
{
    return PAGES;
}

const uint8_t *rhock_store_page_get(uint32_t n)
{
    return &rom_memory[n*PAGE_SIZE];
}

void rhock_store_page_write(uint32_t n, uint8_t *data)
{
    uint8_t *rom = &rom_memory[n*PAGE_SIZE];
    for (int k=0; k<PAGE_SIZE; k++) {
        rom[k] = data[k];
    }
}
