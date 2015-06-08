#include <math.h>
#include <stdio.h>
#include "instructions.h"
#include "clock.h"
#include "program.h"
#include "opcode.h"
#include "config.h"

// #define RHOCK_DEBUG_OPCODES

#ifdef RHOCK_DEBUG_OPCODES
#define RHOCK_OP_DEBUG(...) \
    RHOCK_DEBUG("%04x: ", current_pc); \
    RHOCK_DEBUG(__VA_ARGS__); 
#else
#undef RHOCK_DEBUG
#define RHOCK_DEBUG(...)
#define RHOCK_OP_DEBUG(...)
#endif

#define UNARY_OP(name, operation) \
            RHOCK_OP_DEBUG(name); \
            int32_t value = rhock_context_popi(context); \
            rhock_context_push(context, operation);

#define UNARY_OPF(name, operation) \
            RHOCK_OP_DEBUG(name); \
            float value = rhock_context_popf(context); \
            rhock_context_pushf(context, operation);

#define BINARY_OP(name, operation) \
            RHOCK_OP_DEBUG(name); \
            int32_t value2 = rhock_context_popi(context); \
            int32_t value1 = rhock_context_popi(context); \
            rhock_context_push(context, operation);

#define BINARY_OPF(name, operation) \
            RHOCK_OP_DEBUG(name); \
            float value2 = rhock_context_popf(context); \
            float value1 = rhock_context_popf(context); \
            rhock_context_pushf(context, operation);

#define RHOCK_BOOL(b) \
    ((b)?(RHOCK_NUMBER_TO_VALUE(1)):(0))

static uint8_t readbyte(struct rhock_context *context)
{
    if (context->pc < context->data_size) {
        return context->data[context->pc++];
    } else {
        rhock_program_crash(context->program, RHOCK_ERROR_OUT_OF_MEMORY);
        return 0x00;
    }
}

static int8_t readsignedbyte(struct rhock_context *context)
{
    return (int8_t)readbyte(context);
}

static uint32_t readint(struct rhock_context *context)
{
    uint32_t i;
    i = readbyte(context)<<24;
    i |= readbyte(context)<<16;
    i |= readbyte(context)<<8;
    i |= readbyte(context)<<0;
    return i;
}

static uint16_t readshort(struct rhock_context *context)
{
    uint32_t i;
    i = readbyte(context)<<8;
    i |= readbyte(context)<<0;
    return i;
}

struct rhock_program *get_program(uint32_t id)
{
    rhock_memory_addr addr = rhock_vm_get_program(id);
    if (addr != RHOCK_NULL) {
        return rhock_get_program(addr);
    }

    return NULL;
}

uint8_t rhock_opcode_tick(struct rhock_context *context)
{
    if (context->native != NULL) {
        uint8_t ret = context->native(context, RHOCK_NATIVE_OP_TICK, rhock_gettime()-context->nativeStart);

        if (ret == RHOCK_NATIVE_CONTINUE) {
            context->native = NULL;
        } else if (ret == RHOCK_NATIVE_WAIT) {
            return 0;
        }

        return 1;
    } else {
#ifdef RHOCK_DEBUG_OPCODES
        rhock_addr current_pc = context->pc;
#endif
        uint8_t opcode = readbyte(context);

        switch (opcode) {
            case INST_START: {
                uint8_t id = readbyte(context);
                RHOCK_OP_DEBUG("start %d\n", id);
                rhock_context_start_by_id(context->program, context->program, id);
                break;
                }
            case INST_STOP: {
                uint8_t id = readbyte(context);
                RHOCK_OP_DEBUG("stop %d\n", id);
                rhock_context_stop_by_id(context->program, context->program, id);
                break;
                }
            case INST_PAUSE: {
                uint8_t id = readbyte(context);
                RHOCK_OP_DEBUG("pause %d\n", id);
                rhock_context_pause_by_id(context->program, context->program, id);
                break;
                }
            
            case INST_STARTR: {
                uint32_t pid = readint(context);
                uint8_t id = readbyte(context);
                struct rhock_program *program = get_program(pid);
                if (program != NULL) {
                    RHOCK_OP_DEBUG("startr %d %d\n", pid, id);
                    rhock_context_start_by_id(context->program, program, id);
                }
                break;
                }
            case INST_STOPR: {
                uint32_t pid = readint(context);
                uint8_t id = readbyte(context);
                struct rhock_program *program = get_program(pid);
                if (program != NULL) {
                    RHOCK_OP_DEBUG("stopr %d %d\n", pid, id);
                    rhock_context_stop_by_id(context->program, program, id);
                }
                break;
                }
            case INST_PAUSER: {
                uint32_t pid = readint(context);
                uint8_t id = readbyte(context);
                struct rhock_program *program = get_program(pid);
                if (program != NULL) {
                    RHOCK_OP_DEBUG("pauser %d %d\n", pid, id);
                    rhock_context_pause_by_id(context->program, program, id);
                }
                break;
                }
            
            case INST_STOPS: {
                RHOCK_OP_DEBUG("stops\n");
                rhock_context_stop(context);
                break;
                }
            case INST_PAUSES: {
                RHOCK_OP_DEBUG("pauses\n");
                rhock_context_pause(context);
                break;
                }

            // Programs control
            case INST_RUN: {
                uint32_t id = readint(context);
                RHOCK_OP_DEBUG("run %d\n", id);
                rhock_program_run(id);
                break;
            }
            case INST_FREEZE: {
                uint32_t id = readint(context);
                RHOCK_OP_DEBUG("freeze %d\n", id);
                rhock_program_freeze(id);
                break;
            }
            case INST_KILL: {
                uint32_t id = readint(context);
                RHOCK_OP_DEBUG("kill %d\n", id);
                rhock_program_kill(id);
                if (id == context->program->obj->id) {
                    return 0;
                }
                break;
            }
            case INST_FREEZES: {
                RHOCK_OP_DEBUG("freezes\n");
                rhock_program_freeze(context->program->obj->id);
                break;
            }
            case INST_KILLS: {
                RHOCK_OP_DEBUG("kills\n");
                rhock_program_kill(context->program->obj->id);
                return 0;
                break;
            }

            // Push
            case INST_PUSHF: {
                uint32_t value = readint(context);
                RHOCK_OP_DEBUG("pushf %g\n", RHOCK_VALUE_TO_NUMBER(value));
                rhock_context_push(context, value); 
                break;
                }
            case INST_PUSHS: {
                rhock_context_pushi(context, context->pc);
                uint8_t len = readbyte(context);
#ifdef RHOCK_DEBUG_OPCODES
                uint8_t k;
                RHOCK_OP_DEBUG("pushs \"");
                for (k=0; k<len; k++) {
                    RHOCK_DEBUG("%c", context->data[context->pc+k]);
                }
                RHOCK_DEBUG("\"\n");
#endif
                context->pc += len;
                break;
                }
            case INST_PUSHV: {
                uint8_t variable = readbyte(context);
                RHOCK_OP_DEBUG("pushv variable_%d\n", variable);
                rhock_context_push(context, rhock_program_get_var(context->program, variable));
                break;
                }
            case INST_PUSHR: {
                uint32_t pid = readint(context);
                uint8_t variable = readbyte(context);
                struct rhock_program *program = get_program(pid);
                RHOCK_OP_DEBUG("pushr %d variable_%d\n", pid, variable);
                if (program != NULL) {
                    rhock_context_push(context, rhock_program_get_var(program, variable));
                } else {
                    rhock_context_pushf(context, 0.0);
                }
                break;
                }
            case INST_LOAD: {
                int8_t arg = readsignedbyte(context);
                rhock_value *value_ptr = rhock_context_stack_frame(context, arg);
                if (value_ptr != NULL) {
                    rhock_value value = *value_ptr;
                    RHOCK_OP_DEBUG("load %d\t[fp=%02x, v=%g]\n", arg, context->fp, RHOCK_VALUE_TO_NUMBER(value));
                    rhock_context_push(context, value);
                }
                break;
                }
            case INST_STO: {
                int8_t arg = readsignedbyte(context);
                RHOCK_OP_DEBUG("sto %d\t[f=%02x]\n", arg, context->fp);
                rhock_value *value_ptr = rhock_context_stack_frame(context, arg);
                if (value_ptr != NULL) {
                    *value_ptr = rhock_context_pop(context);
                }
                break;
                }
            case INST_DUP: {
                RHOCK_OP_DEBUG("dup\n");
                rhock_context_push(context, rhock_context_stack_top(context));
                break;
                }

            // Pop
            case INST_POP: {
                uint8_t variable = readbyte(context);
                RHOCK_OP_DEBUG("pop variable_%d\n", variable);
                rhock_program_set_var(context->program, variable, rhock_context_pop(context));
                break;
                }
            case INST_POPR: {
                uint32_t pid = readint(context);
                uint8_t variable = readbyte(context);
                struct rhock_program *program = get_program(pid);
                RHOCK_OP_DEBUG("popr %d variable_%d\n", pid, variable);
                rhock_value value = rhock_context_pop(context);
                if (program != NULL) {
                    rhock_program_set_var(program, variable, value);
                }
                break;
                }
            case INST_SMASH: {
                uint8_t n = readbyte(context);
                RHOCK_OP_DEBUG("smash %d\n", n);
                if (context->vsp >= n) {
                    rhock_context_smash(context, n);
                } else {
                    rhock_program_crash(context->program, RHOCK_ERROR_STACK_ILLEGAL);
                }
                break;
                }

            // Jumping
            case INST_JMP: {
                rhock_addr addr = readshort(context);
                RHOCK_OP_DEBUG("jmp %04x\n", addr);
                if (addr < context->data_size) {
                    context->pc = addr;
                } else {
                    rhock_program_crash(context->program, RHOCK_ERROR_ILLEGAL_JUMP);
                }
                break;
                }
            case INST_JMPC: {
                int32_t value = rhock_context_popi(context);
                rhock_addr addr = readshort(context);
                RHOCK_OP_DEBUG("jmpc %04x\t", addr);
                if (value!=0) {
                    if (addr < context->data_size) {
                        RHOCK_DEBUG("[jumping]\n");
                        context->pc = addr;
                    } else {
                        rhock_program_crash(context->program, RHOCK_ERROR_ILLEGAL_JUMP);
                    }
                } else {
                    RHOCK_DEBUG("[not jumping]\n");
                }
                
                break;
                }
            case INST_JMPN: {
                int32_t value = rhock_context_popi(context);
                rhock_addr addr = readshort(context);
                RHOCK_OP_DEBUG("jmpn %04x\t", addr);
                if (value==0) {
                    if (addr < context->data_size) {
                        RHOCK_DEBUG("[jumping]\n");
                        context->pc = addr;
                    } else {
                        rhock_program_crash(context->program, RHOCK_ERROR_ILLEGAL_JUMP);
                    }
                } else {
                    RHOCK_DEBUG("[not jumping]\n");
                }
                
                break;
                }
            case INST_CALL: {
                rhock_addr addr = readshort(context);
                if (RHOCK_IS_NATIVE(addr)) {
                    uint8_t id = RHOCK_ADDR_TO_NATIVE(addr);
                    RHOCK_OP_DEBUG("call native_%d", id);
                    context->native = rhock_native_get(id);
                    if (context->native(context, RHOCK_NATIVE_OP_ENTER, 0) == RHOCK_NATIVE_CONTINUE) {
                        context->native = NULL;
                    } else {
                        context->nativeStart = rhock_gettime();
                    }
                } else {
                    RHOCK_OP_DEBUG("call %04x\t", addr);
                    if (addr < context->data_size) {
                        rhock_context_call(context, addr);
                        RHOCK_DEBUG("[fp=%02x, pc=%04x]", context->fp, context->pc);
                    } else {
                        rhock_program_crash(context->program, RHOCK_ERROR_ILLEGAL_CALL);
                    }
                }
                RHOCK_DEBUG("\n");
                break;
                }
            case INST_ARGS: {
                uint8_t value = readbyte(context);
                RHOCK_OP_DEBUG("args %d\n", value);
                if (context->fp >= value) {
                    context->fp -= value;
                } else {
                    rhock_program_crash(context->program, RHOCK_ERROR_FRAME_POINTER);
                }
                break;
                }
            case INST_RET: {
                RHOCK_OP_DEBUG("ret\t");
                rhock_context_ret(context);
                RHOCK_DEBUG("[fp=%02x, pc=%04x]\n", context->fp, context->pc);
                break;
                }
            case INST_RETV: {
                rhock_value value = rhock_context_pop(context);
                RHOCK_OP_DEBUG("retv\t[v=%g]\t", RHOCK_VALUE_TO_NUMBER(value));
                rhock_context_ret(context);
                rhock_context_push(context, value);
                RHOCK_DEBUG("[fp=%02x, pc=%04x]\n", context->fp, context->pc);
                break;
                }

            // Unary operations
            case INST_NOT:{
                UNARY_OP("not\n", RHOCK_BOOL(!value));
                break;
                }
            case INST_TESTZ:{
                UNARY_OP("testz\n", RHOCK_BOOL(value==0));
                break;
                }
            case INST_TESTNZ:{
                UNARY_OP("testnz\n", RHOCK_BOOL(value!=0));
                break;
                }
            case INST_TESTGZ:{
                UNARY_OP("testgz\n", RHOCK_BOOL(value>0));
                break;
                }
            case INST_TESTLZ:{
                UNARY_OP("testlz\n", RHOCK_BOOL(value<0));
                break;
                }
            case INST_TESTGEZ:{
                UNARY_OP("testgez\n", RHOCK_BOOL(value>=0));
                break;
                }
            case INST_TESTLEZ:{
                UNARY_OP("testlez\n", RHOCK_BOOL(value<=0));
                break;
                }
            case INST_INC:{
                UNARY_OP("add\n", value+RHOCK_NUMBER_TO_VALUE(1));
                break;
                }
            case INST_DEC:{
                UNARY_OP("dec\n", value-RHOCK_NUMBER_TO_VALUE(1));
                break;
                }

            // Binary operations
            case INST_ADD: {
                BINARY_OP("add\n", value1+value2);
                break;
                }
            case INST_SUB: {
                BINARY_OP("sub\n", value1-value2);
                break;
                }
            case INST_MUL: {
                BINARY_OPF("mul\n", value1*value2);
                break;
                }
            case INST_DIV: {
                BINARY_OPF("div\n", value1/value2);
                break;
                }
            case INST_AND: {
                BINARY_OP("and\n", RHOCK_BOOL(value1&&value2));
                break;
                }
            case INST_OR: {
                BINARY_OP("or\n", RHOCK_BOOL(value1||value2));
                break;
                }
            case INST_TESTE: {
                BINARY_OP("teste\n", RHOCK_BOOL(value1==value2));
                break;
                }
            case INST_TESTNE: {
                BINARY_OP("testne\n", RHOCK_BOOL(value1!=value2));
                break;
                }
            case INST_TESTL: {
                BINARY_OP("testl\n", RHOCK_BOOL(value1<value2));
                break;
                }
            case INST_TESTLE: {
                BINARY_OP("testle\n", RHOCK_BOOL(value1<=value2));
                break;
                }
            case INST_TESTG: {
                BINARY_OP("testg\n", RHOCK_BOOL(value1>value2));
                break;
                }
            case INST_TESTGE: {
                BINARY_OP("testge\n", RHOCK_BOOL(value1>=value2));
                break;
                }

            case INST_EMITN: {
                uint32_t n = readint(context);
                RHOCK_OP_DEBUG("emitn %u\n", n);
                rhock_context_emit(context, n, 0);
                break;
                }
            case INST_EMITV: {
                uint32_t n = readint(context);
                uint8_t s = readbyte(context);
                RHOCK_OP_DEBUG("emitv %u %d\n", n, s);
                rhock_context_emit(context, n, s);
                break;
                }
            case INST_WAIT: {
                uint32_t n = readint(context);
                RHOCK_OP_DEBUG("wait %u\n", n);
                rhock_context_wait(context, n);
                break;
                }

            default:
                RHOCK_OP_DEBUG("unknown opcode %02x\n", opcode);
                rhock_program_crash(context->program, RHOCK_ERROR_INVALID_OPCODE);
                break;
        }

        // rhock_context_dump(context);

        return 1;
    }
}
