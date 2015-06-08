#ifndef _RHOCK_INSTS
#define _RHOCK_INSTS

// Stack & variables control
#define INST_PUSHF      0x10
#define INST_PUSHS      0x11
#define INST_PUSHV      0x12
#define INST_PUSHR      0x13
#define INST_LOAD       0x14
#define INST_STO        0x15
#define INST_DUP        0x16

#define INST_POP        0x26
#define INST_POPR       0x27
#define INST_SMASH      0x28

// Execution control
#define INST_JMP        0x30
#define INST_JMPC       0x31
#define INST_JMPN       0x32
#define INST_CALL       0x33
#define INST_ARGS       0x34
#define INST_RET        0x35
#define INST_RETV       0x36

#define INST_START      0x3a
#define INST_STOP       0x3b
#define INST_PAUSE      0x3c
#define INST_STARTR     0x3d
#define INST_STOPR      0x3e
#define INST_PAUSER     0x3f
#define INST_STOPS      0x40
#define INST_PAUSES     0x41

#define INST_RUN        0x42
#define INST_FREEZE     0x43
#define INST_KILL       0x44
#define INST_FREEZES    0x45
#define INST_KILLS      0x46

// Unary operations
#define INST_NOT     0x60
#define INST_TESTZ   0x61
#define INST_TESTNZ  0x62
#define INST_TESTGZ  0x63
#define INST_TESTLZ  0x64
#define INST_TESTGEZ 0x65
#define INST_TESTLEZ 0x66
#define INST_INC     0x67
#define INST_DEC     0x68

// Binary operations
#define INST_ADD     0x80
#define INST_SUB     0x81
#define INST_MUL     0x82
#define INST_DIV     0x83
#define INST_AND     0x84
#define INST_OR      0x85
#define INST_TESTE   0x86
#define INST_TESTNE  0x87
#define INST_TESTL   0x88
#define INST_TESTLE  0x89
#define INST_TESTG   0x90
#define INST_TESTGE  0x91

// Events opcode
#define INST_EMITN  0xa0
#define INST_EMITV  0xa1
#define INST_WAIT   0xa2

#endif
