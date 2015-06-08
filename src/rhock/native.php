<?php
/**
 * Script that can be used to use a fancy number of native methods
 */

$possible = array(16, 32, 64, 128, 256);

echo '#include <stdio.h>
#include <stdlib.h>
#include "native.h"
#include "config.h"

uint8_t rhock_native_nop(struct rhock_context *context, uint8_t op, uint32_t elapsed)
{
    return RHOCK_NATIVE_CONTINUE;
}

';

foreach ($possible as $p) {
    echo "\n";
    echo "#ifdef RHOCK_NATIVE_MAX_$p\n";
    echo "#define RHOCK_NATIVE_MAX $p\n";
    for ($k=0; $k<$p; $k++) {
        echo "extern rhock_native rhock_native$k __attribute__((weak));\n";
        echo "rhock_native rhock_native$k = rhock_native_nop;\n";
    }

    echo "rhock_native rhock_native_get(uint8_t id)\n";
    echo "{\n";
    echo "switch (id) {\n";
    for ($k=0; $k<$p; $k++) {
        echo "case $k:\n";
        echo "return rhock_native$k;\n";
    }
    echo "default:\n";
    echo "return NULL;\n";
    echo "}\n";

    echo "};\n";
    echo "#endif\n";
}

echo "#include \"native_symbols.inc\"";
