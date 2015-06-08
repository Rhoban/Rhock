#ifndef _RHOCK_PROGRAM
#define _RHOCK_PROGRAM

#ifdef __cplusplus
extern "C" {
#endif

struct rhock_program;

#include "obj.h"
#include "config.h"
#include "vm.h"
#include "memory.h"

#define RHOCK_PROGRAM_RUNNING           1
#define RHOCK_PROGRAM_FREEZED           2
#define RHOCK_PROGRAM_CRASHED           3
#define RHOCK_PROGRAM_KILLED            4
#define RHOCK_PROGRAM_WAITING           5

// There is no error here
#define RHOCK_ERROR_NO_ERROR            0
// An error has occured when trying to allocate the room for this program.
// This can happens if there is not enough room to store the 
#define RHOCK_ERROR_ALLOCATE_VARS       1
#define RHOCK_ERROR_ALLOCATE_CONTEXT    2
#define RHOCK_ERROR_ALLOCATE_STACK      3
// The memory was exhausted
#define RHOCK_ERROR_MEMORY              4
// The program tried to access an illegal variable
#define RHOCK_ERROR_VARIABLE            5
// The stack was over/underflowed
#define RHOCK_ERROR_STACK_OVERFLOW      6
#define RHOCK_ERROR_STACK_UNDERFLOW     7
// The program tried to access an illegal portion of the stack (for example,
// using dup when empty or load/sto with out-of-the stack indexes)
#define RHOCK_ERROR_STACK_ILLEGAL       8
// The call stack was over/underflowed
#define RHOCK_ERROR_CSTACK_OVERFLOW     9
#define RHOCK_ERROR_CSTACK_UNDERFLOW    10
// The process tried to start/pause/stop an invalid process
#define RHOCK_ERROR_INVALID_PROCESS     11
// The program counter went out of the memory
#define RHOCK_ERROR_OUT_OF_MEMORY       12
#define RHOCK_ERROR_ILLEGAL_JUMP        13
#define RHOCK_ERROR_ILLEGAL_CALL        14
// Bad frame pointer, this will happen if you try to get too much args for 
// instance
#define RHOCK_ERROR_FRAME_POINTER       15
// An invalid opcode was encountred
#define RHOCK_ERROR_INVALID_OPCODE      16

struct rhock_program
{
    // State
    uint8_t state;
    // Error
    uint8_t error;
    // Reference to obj
    struct rhock_obj *obj;
    // Reference to the vm
    struct rhock_vm *vm;
    // Variables
    rhock_memory_addr variables;
    // Contexts
    rhock_memory_addr contexts;
};

/**
 * Gets a program by its address
 */
struct rhock_program *rhock_get_program(rhock_memory_addr addr);
uint8_t rhock_program_error(rhock_memory_addr addr);
void rhock_program_crash(struct rhock_program *program, uint8_t error);

/**
 * Load and unload a program
 */
rhock_memory_addr rhock_program_load(struct rhock_obj *obj);
void rhock_program_unload(rhock_memory_addr addr);

/**
 * Initialize a program
 */
void rhock_program_init(rhock_memory_addr addr);

/**
 * Gets a context id
 */
struct rhock_context *rhock_program_ctx_by_id(struct rhock_program *, uint8_t id);

/**
 * Sets/get the variables
 */
rhock_value rhock_program_get_var(struct rhock_program *, uint8_t var);
void rhock_program_set_var(struct rhock_program *, uint8_t var, rhock_value val);

/**
 * Execution control
 */
void rhock_program_run(uint32_t id);
void rhock_program_freeze(uint32_t id);
void rhock_program_kill(uint32_t id);
void rhock_program_killall();

/**
 * Processing stream data
 */
char rhock_program_process();

#ifdef __cplusplus
}
#endif

#endif
