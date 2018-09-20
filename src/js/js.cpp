#include <vector>
#include <as/as.h>
#include <as/compile-space.h>
#include <errors/errors.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <rhock/obj.h>
#include <rhock/event.h>
#include <rhock/chain.h>
#include <rhock/vm.h>
#include <rhock/program.h>
#include <rhock/print.h>
#include <rhock/clock.h>
#include <rhock/stream.h>

using namespace emscripten;
using namespace Rhock;

/**
 * Time is handled using getTime
 */
uint32_t rhock_gettime()
{
    return EM_ASM_INT({
        return (new Date()).getTime()%0xffffffff;
    }, 0);
}

int main()
{
    emscripten_exit_with_live_runtime();
    return 1;
}

// Getting a vector containg all obj ids
std::vector<uint32_t> rhock_get_obj_ids()
{
    std::vector<uint32_t> objs;
    rhock_memory_addr obj = rhock_vm_get_objs();
    while (obj != RHOCK_LAST) {
        auto o = rhock_get_obj(obj);
        objs.push_back(o->id);
        obj = rhock_chain_next(obj);
    }

    return objs;
}

// Getting the state of a program
int rhock_get_program_state(uint32_t id)
{
    rhock_memory_addr addr = rhock_vm_get_program(id);
    if (addr == RHOCK_NULL) {
        return RHOCK_PROGRAM_KILLED;
    } else {
        auto program = rhock_get_program(addr);
        return program->state;
    }
}

EMSCRIPTEN_BINDINGS(rhock) {
    // Types
    register_vector<uint32_t>("vector_int");

    // Control vm
    function("rhock_vm_init", &rhock_vm_init);
    function("rhock_vm_tick", &rhock_vm_tick);
    function("rhock_vm_monitor", &rhock_vm_monitor);
    // Cntrol objs
    function("rhock_vm_get_objs", &rhock_vm_get_objs);
    function("rhock_vm_get_obj", &rhock_vm_get_obj);
    function("rhock_vm_clear_objs", &rhock_vm_clear_objs);
    function("rhock_get_obj_ids", &rhock_get_obj_ids);
    // Control programs
    function("rhock_vm_get_program", &rhock_vm_get_program);
    function("rhock_program_run", &rhock_program_run);
    function("rhock_program_freeze", &rhock_program_freeze);
    function("rhock_program_kill", &rhock_program_kill);
    function("rhock_get_program_state", &rhock_get_program_state);
    // Stream
    function("rhock_stream_recv", &rhock_stream_recv);
    // Events
    function("rhock_on_reset", &rhock_on_reset);
    // Errors
    function("rhock_program_error_str", &rhock_program_error_str);
    function("rhock_stream_error_str", &rhock_stream_error_str);

    // Assembler
    class_<CompileSpace>("CompileSpace")
        .constructor<>()
        .function("addAssembler", &CompileSpace::addAssemblerRef)
        ;

    class_<As>("As")
        .constructor<>()
        .function("process", &As::processError)
        .function("resolve", &As::resolveSymbolsError)
        .function("getBinary", &As::getBinary)
        .function("getBinaryBytes", &As::getBinaryBytes)
        ;
}

EMSCRIPTEN_BINDINGS(stl_wrappers) {
    register_vector<unsigned char>("VectorChar");
}