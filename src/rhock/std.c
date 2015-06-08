#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "clock.h"
#include "native.h"
#include "std.h"
#include "program.h"
#include "print.h"

// Conversions
#ifndef DEG2RAD
#define DEG2RAD(x) (((x)/180.0)*M_PI)
#endif
#ifndef RAD2DEG
#define RAD2DEG(x) (((x)/M_PI)*180.0)
#endif

// Sleeping
RHOCK_NATIVE(sleep) 
{
    ON_ELAPSED() {
        RHOCK_SMASH(1);
        return RHOCK_NATIVE_CONTINUE;
    }
}

// Debugging and printing
RHOCK_NATIVE(prints)
{
    uint8_t i, n;
    const uint8_t *d;
    RHOCK_POPS(n, d);
    for (i=0; i<n; i++) {
        rhock_print(d[i]);
    }

    return RHOCK_NATIVE_CONTINUE;
}

RHOCK_NATIVE(printv)
{
    rhock_print_value(RHOCK_POPF());

    return RHOCK_NATIVE_CONTINUE;
}

RHOCK_NATIVE(println)
{
    rhock_println();

    return RHOCK_NATIVE_CONTINUE;
}

// Math
#define UNARY_NATIVE_F(name, operation) \
    RHOCK_NATIVE(name) \
    { \
        float value = RHOCK_POPF(); \
        RHOCK_PUSHF(operation); \
        \
        return RHOCK_NATIVE_CONTINUE; \
    }

#define UNARY_NATIVE(name, operation) \
    RHOCK_NATIVE(name) \
    { \
        rhock_value value = RHOCK_POPI(); \
        RHOCK_PUSHI(operation); \
        \
        return RHOCK_NATIVE_CONTINUE; \
    }

UNARY_NATIVE_F(cos,  cos(DEG2RAD(value)))
UNARY_NATIVE_F(sin,  sin(DEG2RAD(value)))
UNARY_NATIVE_F(sqrt, sqrt(value))
UNARY_NATIVE(abs, abs(value))
UNARY_NATIVE(neg, -(value))

#define BINARY_NATIVE_F(name, operation) \
    RHOCK_NATIVE(name) \
    { \
        float value2 = RHOCK_POPI(); \
        float value1 = RHOCK_POPI(); \
        RHOCK_PUSHF(operation); \
        \
        return RHOCK_NATIVE_CONTINUE; \
    }
#define BINARY_NATIVE(name, operation) \
    RHOCK_NATIVE(name) \
    { \
        int value2 = RHOCK_POPI(); \
        int value1 = RHOCK_POPI(); \
        RHOCK_PUSHF(operation); \
        \
        return RHOCK_NATIVE_CONTINUE; \
    }

BINARY_NATIVE(mod, (value1%value2))
BINARY_NATIVE(atan2, RAD2DEG(atan2(value1, value2)))

RHOCK_NATIVE(randint)
{
    int max = RHOCK_VALUE_TO_INT(RHOCK_POPI());
    int min = RHOCK_VALUE_TO_INT(RHOCK_POPI());
    int number = rand()%(1+max-min)+min;
    RHOCK_PUSHI(RHOCK_NUMBER_TO_VALUE(number));

    return RHOCK_NATIVE_CONTINUE;
}

RHOCK_NATIVE(randfloat)
{
    rhock_value max = RHOCK_POPI();
    rhock_value min = RHOCK_POPI();
    rhock_value number = rand()%(1+max-min)+min;
    RHOCK_PUSHI(number);

    return RHOCK_NATIVE_CONTINUE;
}

RHOCK_NATIVE(chrono_create)
{
    RHOCK_PUSHI(rhock_gettime());
    return RHOCK_NATIVE_CONTINUE;
}

RHOCK_NATIVE(chrono_get)
{
    uint32_t ts = RHOCK_POPI();
    RHOCK_PUSHF(rhock_gettime()-ts);

    return RHOCK_NATIVE_CONTINUE;
}

RHOCK_NATIVE(chrono_waitv)
{
    float chrono_elapsed = rhock_gettime()-RHOCK_VALUEI(1);

    if (chrono_elapsed >= RHOCK_VALUE(0)) {
        RHOCK_SMASH(2);
        return RHOCK_NATIVE_CONTINUE;
    } 

    return RHOCK_NATIVE_WAIT;
}
