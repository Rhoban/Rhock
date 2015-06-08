cmake_minimum_required(VERSION 2.8)
project(rhock)

option(JS
    "Generate javascript" OFF
    )

if (JS)
    set(CMAKE_C_COMPILER emcc)
    set(CMAKE_CXX_COMPILER em++)
    set(CMAKE_AR emar)
    set(CMAKE_RANLIB emranlib)
    set(CMAKE_C_FLAGS -g)
    set(CMAKE_CXX_FLAGS -g)
endif (JS)
    
set (CMAKE_C_FLAGS "-Wall")
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-reorder -pedantic")
    
add_definitions (-DRHOCK_NATIVE_SYMBOLS)

set (SRC_RHOCK_OBJ
    rhock/memory.c
    rhock/obj.c
    rhock/obj_write.c
    rhock/crc16.c
)

set (SRC_RHOCK
    ${SRC_RHOCK_OBJ}
    rhock/obj.c
    rhock/crc16.c
    rhock/chain.c
    rhock/context.c
    rhock/event.c
    rhock/native.c
    rhock/print.c
    rhock/opcode.c
    rhock/program.c
    rhock/stream.c
    rhock/store.c
    rhock/vm.c
    rhock/std.c
)

set (SRC_AS_LIB
    ${SRC_RHOCK_OBJ}
    errors/errors.cpp
    rhock/native.c
    insts/mnemonics.cpp
    as/as.cpp
    as/compile-space.cpp
    util/util.cpp
    )

set (SRC_AS
    ${SRC_AS_LIB}
    as/main.cpp
    )

set (SRC_OBJDUMP
    ${SRC_RHOCK_OBJ}
    rhock/native.c
    insts/mnemonics.cpp
    objdump/objdump.cpp
    objdump/main.cpp

    util/util.cpp
    )

set (SRC_VM
    ${SRC_RHOCK}

    errors/errors.cpp
    util/util.cpp
    os/main.cpp
    os/hal.c
    )

set (SRC_JS
    ${SRC_RHOCK}
    ${SRC_AS_LIB}
    js/js.cpp
    rhock/store_ram.cpp
    )

include_directories ("${CMAKE_SOURCE_DIR}")

if (JS)
    #    add_library (rhocklib.js ${SRC_RHOCK} ${SRC_AS_LIB} rhock/js.cpp)
    set (ALL_SOURCES)
    foreach (SOURCE ${SRC_JS})
        set (ALL_SOURCES
            ${ALL_SOURCES}
            ${PROJECT_SOURCE_DIR}/${SOURCE}
            )
    endforeach ()

    set (RHOCK_JS ${ALL_SOURCES}
        CACHE STRING "Rhock js sources")
else ()
    add_executable (rhock-as ${SRC_AS})
    add_executable (rhock-objdump ${SRC_OBJDUMP})
    set_target_properties (rhock-as PROPERTIES COMPILE_DEFINITIONS "RHOCK_NO_VM")
    set_target_properties (rhock-objdump PROPERTIES COMPILE_DEFINITIONS "RHOCK_NO_VM")
    add_executable (rhock ${SRC_VM})
endif ()
