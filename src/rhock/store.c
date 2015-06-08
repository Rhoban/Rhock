#define RHOCK_STORE __attribute__((weak))
#include <stdlib.h>
#include "print.h"
#include "print.h"
#include "memory.h"
#include "stream.h"
#include "store.h"
#include "vm.h"

#define RHOCK_STORE_INIT     0
#define RHOCK_STORE_CHUNK_N  1
#define RHOCK_STORE_CHUNK    2
#define RHOCK_STORE_LOAD     3
#define RHOCK_STORE_RESET    4

int rhock_store_process()
{
    if (rhock_stream_available()) {
        uint8_t inst = rhock_stream_read();
        switch (inst) {
            case RHOCK_STORE_INIT:
                if (rhock_stream_available()==4) {
                    if (rhock_store_alloc(rhock_stream_read_int())) {
                        return RHOCK_OK;
                    }
                }
                return RHOCK_STORE_ALLOC_ERR;
                break;
            case RHOCK_STORE_CHUNK_N:
                rhock_store_append((char*)rhock_stream_data(), rhock_stream_available());
                return RHOCK_NO_ACK;
            case RHOCK_STORE_CHUNK:
                if (rhock_store_append((char*)rhock_stream_data(), rhock_stream_available())) {
                    return RHOCK_OK;
                }
                return RHOCK_STORE_CHUNK_ERR;
                break;
            case RHOCK_STORE_LOAD:
                if (rhock_store_load()) {
                    return RHOCK_OK;
                }
                return RHOCK_STORE_LOAD_ERR;
                break;
            case RHOCK_STORE_RESET:
                rhock_vm_clear_objs();
                rhock_store_reset();
                return RHOCK_OK;
                break;
        }
    }

    return RHOCK_UNKNOWN_COMMAND;
}

const uint32_t rhock_store_pages()
{
    return 0;
}

const uint32_t rhock_store_page_size()
{
    return 0;
}

const uint8_t *rhock_store_page_get(uint32_t page)
{
    return NULL;
}

void rhock_store_page_write(uint32_t n, uint8_t *data)
{
}

/**
 * Current upload page, buffer, position & size
 */
static uint32_t current_page;          // Current page being written
static uint32_t current_page_position; // Current position in the page
rhock_memory_addr current_buffer_addr = RHOCK_NULL; // Rhock memory buffer
static uint8_t  *current_buffer;        // Current buffer to store data before persiting it to the ram
static uint32_t current_position;      // Current position in that buffer
static uint32_t current_size = 0;      // Overall size of the target current obj

/**
 * Returns the number of pages that are needed to contain size
 */
uint32_t rhock_store_page_round(uint32_t size)
{
    uint32_t pages;
    if ((size % rhock_store_page_size()) == 0) {
        pages = size / rhock_store_page_size();
    } else {
        pages = (size / rhock_store_page_size())+1;
    }
    return pages;
}

/**
 * Tell if a page is free
 */
char rhock_store_page_is_free(uint32_t page)
{
    const uint8_t *data = rhock_store_page_get(page);

    return (data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 0);
}

/**
 * Tells how many free pages are following
 */
static int page_free_size(uint32_t n)
{
    int c = 0;
    while (n<rhock_store_pages() && rhock_store_page_is_free(n)) {
        c++;
        n++;
    }   

    return c;
}

/**
 * If a page contains an obj, tell how many pages are reserved
 */
static uint32_t page_obj_size(uint32_t n)
{
    int size = rhock_obj_guess_size((uint8_t*)rhock_store_page_get(n));

    return rhock_store_page_round(size);
}

/**
 * Free a page (writes 0 over it)
 */
static void page_free(uint32_t n)
{
    if (n < rhock_store_pages()) {
        uint8_t buffer[rhock_store_page_size()];
        int k;
        for (k=0; k<rhock_store_page_size(); k++) {
            buffer[k] = 0;
        }
        rhock_store_page_write(n, buffer);
    }
}

/**
 * Persist the current page
 */
void persist_current_data()
{
    rhock_store_page_write(current_page_position, current_buffer);
    current_page_position++;
}

static void dismiss()
{
    if (current_size > 0) {
        int count = rhock_store_page_round(current_size);
        int k;
        for (k=0; k<count; k++) {
            if (!rhock_store_page_is_free(current_page+k)) {
                page_free(current_page+k);
            }
        }
    }
    current_size = 0;
    if (current_buffer_addr != RHOCK_NULL) {
        rhock_free(current_buffer_addr);
        current_buffer_addr = RHOCK_NULL;
        current_buffer = NULL;
    }
}


char rhock_store_alloc(uint32_t size)
{
    if (!size) {
        return 0;
    }
    dismiss();

    // Try to allocate a flash page in the rhock ram
    current_buffer_addr = rhock_alloc(rhock_store_page_size(), 1);
    if (current_buffer_addr == RHOCK_NULL) {
        return 0;
    }
    current_buffer = rhock_get(current_buffer_addr, 0);

    // Compute the number of required pages
    uint32_t pages = rhock_store_page_round(size);

    uint32_t page = 0;
    char found = 0;
    while (page<rhock_store_pages() && !found) {
        if (rhock_store_page_is_free(page)) {
            // If the page is free, let's check if there is 
            uint32_t available = page_free_size(page);
            if (available >= pages) {
                // We found the right place
                found = 1;
            } else {
                // Skipping the available pages
                page += available;
            }
        } else {
            // If the page is allocated, skipping objects in it
            page += page_obj_size(page);
        }
    }

    if (found) {
        current_page = page;
        current_page_position = page;
        current_position = 0;
        current_size = size;
        return 1;
    } else {
        dismiss();
        return 0;
    }
}

char rhock_store_append(char *data, uint32_t size)
{
    if (current_size == 0 || current_buffer == NULL) {
        return 0;
    }

    if (current_position+size > current_size) {
        dismiss();
        return 0;
    } else {
        uint32_t k;
        for (k=0; k<size; k++) {
            current_buffer[current_position%rhock_store_page_size()] = data[k];
            if (((current_position+1)%rhock_store_page_size()) == 0) {
                // We are going to overflow the buffer, so let's persist data to
                // the current page
                persist_current_data();
            }
            current_position++;
        }
        return 1;
    }
}

char rhock_store_load()
{
    if (current_size == 0 || current_buffer == NULL) {
        return 0;
    }

    // If there is still pending chunk, persisting them
    if ((current_position%rhock_store_page_size())!=0) {
        persist_current_data();
    }

    if (current_position != current_size) {
        dismiss();
        return 0;
    }

    char result = rhock_vm_obj_load(rhock_store_page_get(current_page), current_size);
    if (result) {
        if (current_buffer_addr != RHOCK_NULL) {
            rhock_free(current_buffer_addr);
            current_buffer_addr = RHOCK_NULL;
            current_buffer = NULL;
        }
        current_size = 0;
        return 1;
    } else {
//        dismiss();
        return 0;
    }
}

void rhock_store_remove(struct rhock_obj *obj)
{
    int pages = rhock_store_page_round(obj->size);
    int start_page;
    for (start_page=0; start_page<rhock_store_pages(); start_page++) {
        if (obj->start == rhock_store_page_get(start_page)) {
            if (start_page >= 0) {
                int k;
                for (k=0; k<pages; k++) {
                    page_free(start_page+k);
                }
            }
            return;
        }
    }
}

void rhock_store_init()
{
    uint32_t k = 0;
    current_buffer_addr = RHOCK_NULL;
    current_buffer = NULL;
    while (k < rhock_store_pages()) {
        if (!rhock_store_page_is_free(k)) {
            int size = rhock_obj_guess_size(rhock_store_page_get(k));
            if ((size+k*rhock_store_page_size()) < (rhock_store_page_size()*rhock_store_pages())) {
                char result = rhock_vm_obj_load(rhock_store_page_get(k), size);
                if (!result) {
                    page_free(k++);
                } else {
                    k += rhock_store_page_round(size);
                }
            } else {
                page_free(k);
                k++;
            }
        } else {
            k++;
        }
    }
}

void rhock_store_reset()
{
    int k;
    for (k=0; k<rhock_store_pages(); k++) {
        if (!rhock_store_page_is_free(k)) {
            page_free(k);
        }
    }
}
