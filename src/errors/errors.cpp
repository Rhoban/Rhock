#include "errors.h"
#include <rhock/program.h>
#include <rhock/stream.h>

std::string rhock_program_error_str(int code)
{
    switch (code) {
        case RHOCK_ERROR_ALLOCATE_VARS:
            return "unable to allocate enough memory for variables";
            break;
        case RHOCK_ERROR_ALLOCATE_CONTEXT:
            return "unable to allocate enough memory for context";
            break;
        case RHOCK_ERROR_ALLOCATE_STACK:
            return "unable to allocate enough memory for stack";
            break;
        case RHOCK_ERROR_MEMORY:
            return "memory overflow";
            break;
        case RHOCK_ERROR_VARIABLE:
            return "trying to access an illegal variable";
            break;
        case RHOCK_ERROR_STACK_OVERFLOW:
            return "stack overflow";
            break;
        case RHOCK_ERROR_STACK_UNDERFLOW:
            return "stack underflow";
            break;
        case RHOCK_ERROR_STACK_ILLEGAL:
            return "illegal stack access";
            break;
        case RHOCK_ERROR_CSTACK_OVERFLOW:
            return "call stack overflow";
            break;
        case RHOCK_ERROR_CSTACK_UNDERFLOW:
            return "call stack underflow";
            break;
        case RHOCK_ERROR_INVALID_PROCESS:
            return "attempt to control an invalid process";
            break;
        case RHOCK_ERROR_OUT_OF_MEMORY:
            return "reached out of memory";
            break;
        case RHOCK_ERROR_ILLEGAL_JUMP:
            return "jumped out of memory";
            break;
        case RHOCK_ERROR_ILLEGAL_CALL:
            return "called out of memory";
            break;
        case RHOCK_ERROR_FRAME_POINTER:
            return "bad frame pointer";
            break;
        case RHOCK_ERROR_INVALID_OPCODE:
            return "invalid opcode";
            break;
    }

    return "unknown error";
}

std::string rhock_stream_error_str(int code)
{
    switch (code) {
        case RHOCK_STORE_ALLOC_ERR:
            return "not enough room to allocate such program";
            break;
        case RHOCK_STORE_CHUNK_ERR:
            return "error while transmitting a program";
            break;
        case RHOCK_STORE_LOAD_ERR:
            return "error when loading a program";
            break;
        case RHOCK_UNKNOWN_COMMAND:
            return "received an unknown command";
            break;
    }

    return "unknown error";
}
