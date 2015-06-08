#pragma once

#include <string>
#include <map>
#include <rhock/obj.h>
#include <insts/mnemonics.h>

namespace Rhock
{
    class CompileSpace;

#define RHOCK_SYM_VARIABLE  0
#define RHOCK_SYM_ADDR      1
#define RHOCK_SYM_ENTRY     2

    struct rhock_symbol
    {
        // Symbol name & type
        std::string name;
        int type;
        // Address and name
        rhock_addr addr;
        // If it's an entry
        rhock_entry entry;
        int entryState;
        // If it's a variable
        rhock_var variable;
    };

    struct rhock_resolve
    {
        // Id of the program
        uint32_t id;
        // Addr where the resolve should be wrote
        rhock_addr addr;
        // Line number from the resolve
        int line_number;
        // Symbol and type
        std::string symbol;
        int type;
    };

    struct rhock_variable
    {
        // Variable number
        rhock_var num;
        // Default value
        rhock_value def;
    };

    class As
    {
        public:
            As();

            // Run the assembling
            void assembleFile(std::string filename);
            void assemble(std::string inputData);
            std::string getBinary();
            void writeFile(std::string filename);
            void parseFile(std::string filename);

            void process(std::string inputData);
            std::string processError(std::string inputData);
            std::string resolveSymbolsError();
            void resolveSymbols();

            void setCompileSpace(CompileSpace *space);

            uint32_t getId();

        protected:
            // Obj Id
            uint32_t id;
            // Obj name
            std::string name;
            // Number of variables and entries
            int numVariables, numEntries;
            // Mnemonics mapping
            std::map<std::string, rhock_mnemonic*> mnemonics;
            // Symbols
            std::map<std::string, rhock_symbol> symbols;
            // Extern methods
            std::map<std::string, rhock_addr> natives;
            // Late resolve
            std::vector<rhock_resolve> resolves;
            // Variable
            std::map<std::string, rhock_variable> variables;
            // Binary
            std::string data;
            // Object
            rhock_obj obj;
            // Current address
            rhock_addr addr;
            // Current line
            uint32_t line_number;
            // Input name
            std::string input;
            // Compile space
            CompileSpace *space;
    
            rhock_symbol *resolveSymbol(rhock_resolve resolve);

            bool isEntry, isStopped;

            void initObject();
            void processLine(std::string line);
            void processMnemonic(std::string line);
            void error(std::string err);

            bool isString(std::string value);
            bool isVariable(std::string value);
            bool isNumber(std::string value);

            void appendByte(unsigned char byte, std::string &output);
            void appendString(std::string string, std::string &output);
            void appendNumber(double number, std::string &output);
            void appendInt(int value, std::string &output);
            void appendShort(unsigned short value, std::string &output);
    };
}
