#ifndef _RHOCK_STD_H
#define _RHOCK_STD_H

#include "native.h"

// Sleeping method
RHOCK_NATIVE_DECLARE(sleep,   0)

// Debugging and output
RHOCK_NATIVE_DECLARE(prints,  1)
RHOCK_NATIVE_DECLARE(printv,  2)
RHOCK_NATIVE_DECLARE(println, 3)

// Math
RHOCK_NATIVE_DECLARE(cos,     10)
RHOCK_NATIVE_DECLARE(sin,     11)
RHOCK_NATIVE_DECLARE(sqrt,    12)
RHOCK_NATIVE_DECLARE(abs,     13)
RHOCK_NATIVE_DECLARE(neg,     14)

RHOCK_NATIVE_DECLARE(mod,     15)
RHOCK_NATIVE_DECLARE(atan2,   16)

RHOCK_NATIVE_DECLARE(randint,    17)
RHOCK_NATIVE_DECLARE(randfloat,  18)

// Timing
RHOCK_NATIVE_DECLARE(chrono_create,  20)
RHOCK_NATIVE_DECLARE(chrono_get,     21)
RHOCK_NATIVE_DECLARE(chrono_waitv,   22)

#endif
