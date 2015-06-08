#pragma once

#include <string>
#include <map>
#include <rhock/obj.h>
#include <insts/mnemonics.h>

namespace Rhock
{
    class Objdump
    {
        public:
            Objdump(std::string filename);
            virtual ~Objdump();
            

            void readEntryPoints();
            void readBytecode();
            void decodeOpcode();
            void displayOpcode(struct rhock_mnemonic &m);

            void disassemble();
            void cdump();

            uint8_t readByte();
            uint32_t readInt();
            uint16_t readShort();
            uint16_t readAddr();
            double readNumber();
            std::string readString();

        protected:
            rhock_addr addr;
            char *data;
            rhock_obj obj;
            std::string filename;
            std::string bin;

            std::map<rhock_addr, std::string> symbols;
            std::map<rhock_addr, std::string> natives;
    };
}
