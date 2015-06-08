#ifndef _RHOCK_VM
#define _RHOCK_VM

#ifdef __cplusplus
extern "C" {
#endif

#include "program.h"
#include "config.h"
#include "memory.h"

/**
 * Initialize the rhock VM
 */
void rhock_vm_init();

/**
 * Tick all the programs, returns the number of thread that have been
 * ticked.
 */
uint8_t rhock_vm_tick();

/**
 * Sets the monitor frequency
 */
void rhock_vm_monitor(int frequency);

/**
 * Objects
 */
rhock_memory_addr rhock_vm_create_obj();
void rhock_vm_remove_obj(rhock_memory_addr addr);
rhock_memory_addr rhock_vm_get_objs();
rhock_memory_addr rhock_vm_get_obj(uint32_t id);
void rhock_vm_clear_objs();
char rhock_vm_obj_load(const uint8_t *ptr, uint32_t size);

/**
 * Programs
 */
void rhock_vm_add_program(rhock_memory_addr addr);
void rhock_vm_remove_program(rhock_memory_addr addr);
rhock_memory_addr rhock_vm_get_programs();
rhock_memory_addr rhock_vm_get_program(uint32_t id);
void rhock_vm_clean();

/**
 * Emit an events to the vm
 */
void rhock_vm_emit(int event, rhock_value *values, int size);

#ifdef __cplusplus
}
#endif

#endif
