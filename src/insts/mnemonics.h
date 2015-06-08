#ifndef _RHOCK_MNEMONICS
#define _RHOCK_MNEMONICS

#include <stdint.h>

// Immediate floating value (4 bytes)
#define FORMAT_IMMEDIATE_F  'f'
// Program id (4 bytes)
#define FORMAT_PROGRAM      'p'
// Immediate string value
#define FORMAT_STRING       's'
// Variable identifier (1 byte)
#define FORMAT_VARIABLE     'v'
// One unsigned signed byte
#define FORMAT_BYTE         'b'
// Address  (2 bytes)
#define FORMAT_ADDRESS      'a'
// An entry point (1 byte)
#define FORMAT_ENTRY        'e'
// An event id
#define FORMAT_EVENT        'E'

struct rhock_mnemonic
{
    // Opcode number
    uint8_t opcode;
    // Mnemonic name
    char name[16];
    // Guess name (for ambiguous names)
    char guess[16];
    // Format
    // m: immediate 32 bit value
    // s: immediate string value
    // v: variable reference
    // b: byte
    // a: address in the binary
    char format[33];
};

extern unsigned int rhock_mnemonics_count;
extern struct rhock_mnemonic rhock_mnemonics[];

#endif
