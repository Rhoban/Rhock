#include "mnemonics.h"
#include <rhock/instructions.h>

struct rhock_mnemonic rhock_mnemonics[] = {
    {INST_PUSHF,    "pushf",    "push",     "f"     },
    {INST_PUSHS,    "pushs",    "push",     "s"     },
    {INST_PUSHV,    "pushv",    "push",     "v"     },
    {INST_PUSHR,    "pushr",    "push",     "pv"    },
    {INST_LOAD,     "load",     "",         "b"     },
    {INST_STO,      "sto",      "",         "b"     },
    {INST_DUP,      "dup",      "",         ""      },

    {INST_POP,      "popv",     "pop",      "v"     },
    {INST_POPR,     "popr",     "pop",      "pv"    },
    {INST_SMASH,    "smash",    "",         "b"     },

    {INST_ARGS,     "args",     "",         "b"     },
    {INST_RET,      "ret",      "",         ""      },
    {INST_RETV,     "retv",     "",         ""      },
 
    {INST_STOPS,    "stops",    "stop",     ""      },
    {INST_PAUSES,   "pauses",   "pause",    ""      },
    {INST_STARTR,   "startr",   "start",    "pe"    },
    {INST_STOPR,    "stopr",    "stop",     "pe"    },
    {INST_PAUSER,   "pauser",   "pause",    "pe"    },
    {INST_START,    "start",    "start",    "e"     },
    {INST_STOP,     "stop",     "stop",     "e"     },
    {INST_PAUSE,    "pause",    "pause",    "e"     },

    {INST_FREEZES,  "freezes",  "freeze",  ""      },
    {INST_KILLS,    "kills",    "kill",    ""      },
    {INST_RUN,      "run",      "run",     "p"     },
    {INST_FREEZE,   "freeze",   "freeze",  "p"     },
    {INST_KILL,     "kill",     "kill",    "p"     },

    {INST_JMP,      "jmp",      "",         "a"     },
    {INST_JMPC,     "jmpc",     "",         "a"     },
    {INST_JMPN,     "jmpn",     "",         "a"     },
    {INST_CALL,     "call",     "",         "a"     },

    // Unary
    {INST_NOT,      "not",      "",         ""      },
    {INST_TESTZ,    "testz",    "",         ""      },
    {INST_TESTNZ,   "testnz",   "",         ""      },
    {INST_TESTGZ,   "testgz",   "",         ""      },
    {INST_TESTLZ,   "testlz",   "",         ""      },
    {INST_TESTGEZ,  "testgez",  "",         ""      },
    {INST_TESTLEZ,  "testlez",  "",         ""      },
    {INST_INC,      "inc",      "",         ""      },
    {INST_DEC,      "dec",      "",         ""      },

    // Binary
    {INST_ADD,      "add",      "",         ""      },
    {INST_SUB,      "sub",      "",         ""      },
    {INST_MUL,      "mul",      "",         ""      },
    {INST_DIV,      "div",      "",         ""      },
    {INST_AND,      "and",      "",         ""      },
    {INST_OR,       "or",       "",         ""      },
    {INST_TESTE,    "teste",    "",         ""      },
    {INST_TESTNE,   "testne",   "",         ""      },
    {INST_TESTL,    "testl",    "",         ""      },
    {INST_TESTLE,   "testle",   "",         ""      },
    {INST_TESTG,    "testg",    "",         ""      },
    {INST_TESTGE,   "testge",   "",         ""      },

    // Event
    {INST_EMITN,    "emitn",    "emit",     "E"     },
    {INST_EMITV,    "emitv",    "emit",     "Eb"    },
    {INST_WAIT,     "wait",     "",         "E"     }
};

unsigned int rhock_mnemonics_count = (sizeof(rhock_mnemonics)/sizeof(struct rhock_mnemonic));
