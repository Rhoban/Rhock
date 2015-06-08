#include <map>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <rhock/obj.h>
#include <rhock/native.h>
#ifdef RHOCK_NO_VM
#include <rhock/std.h>
#endif
#include <insts/mnemonics.h>
#include <util/util.h>
#include "objdump.h"

namespace Rhock
{
    Objdump::Objdump(std::string filename_)
        : filename(filename_), data(NULL)
    {
        if (!file_exists(filename)) {
            std::cerr << "Can't open input file: " << filename << std::endl;
            return;
        }
        bin = file_get_contents(filename);

        for (int i=0; i<rhock_native_symbols_count; i++) {
            auto &symbol = rhock_native_symbols[i];
            natives[RHOCK_NATIVE_TO_ADDR(symbol.id)] = std::string(symbol.name);
        }
    }
            
    Objdump::~Objdump()
    {
        if (data != NULL) {
            delete[] data;
        }
    }

    void Objdump::disassemble()
    {
        data = new char[bin.size()];
        memcpy(data, bin.c_str(), bin.size());
        
        if (rhock_obj_load(&obj, (uint8_t*)data, bin.size())) {
            std::cout << "# name: " << obj.name << std::endl;
            std::cout << "# id: " << obj.id << std::endl;
            printf("# crc16: %04x ", obj.crc16);
            auto crc16 = rhock_obj_crc(&obj);
            if (obj.crc16 == crc16) {
                printf("[correct]");
            } else {
                printf("!bad, should be %04x!", crc16);
            }
            std::cout << std::endl;
            std::cout << "# variables: " << (int)obj.variables << std::endl;
            for (int k=0; k<obj.variables; k++) {
                std::cout << "# var" << k << ": " << RHOCK_VALUE_TO_NUMBER(rhock_default_value(&obj, k)) << std::endl;
            }
            std::cout << "# entries: " << (int)obj.entries << std::endl;

            readEntryPoints();
            readBytecode();
        } else {
            std::cerr << "Corrupted file " << filename << std::endl;
        }
    }
    
    void Objdump::cdump()
    {
        std::cout << "uint8_t program[" << bin.size() << "] = {" << std::endl;
        printf("  ");
        for (unsigned int i=0; i<bin.size(); i++) {
            printf("0x%02x", bin[i]&0xff);
            if ((i+1) != bin.size()) {
                printf(", ");
                if ((i%16) == 15) {
                    printf("\n  ");
                }
            }
        }
        std::cout << std::endl << "};" << std::endl;
    }
            
    void Objdump::readEntryPoints()
    {
        std::map<uint8_t, int> types;
        std::map<uint8_t, std::string> names;

        names[RHOCK_THREAD_RUNNING] = "entry";
        names[RHOCK_THREAD_STOPPED] = "stopped";

        for (rhock_entry k=0; k<obj.entries; k++) {
            auto type = rhock_entry_initial(&obj, k);
            auto addr = rhock_entry_addr(&obj, k);

            if (types.count(type)) {
                types[type]++;
            } else {
                types[type] = 0;
            }

            std::stringstream ss;
            if (type == RHOCK_THREAD_RUNNING && types[type]==0) {
                ss << "main";
            } else {
                if (names.count(type)) {
                    ss << names[type] << "_" << types[type];
                } else {
                    ss << (int)type << "_" << types[type];
                }
            }
            auto name = ss.str();

            symbols[addr] = name;
        }
    }
            
    void Objdump::readBytecode()
    {
        addr = 0;
        auto size = rhock_data_size(&obj);

        while (addr < size) {
            if (symbols.count(addr)) {
                std::cout << std::endl;
                std::cout << "      " << symbols[addr] << ":" << std::endl;
            }
            decodeOpcode();
        }
    }

    void Objdump::decodeOpcode()
    {
        uint8_t opcode = readByte();

        for (unsigned int k=0; k<rhock_mnemonics_count; k++) {
            auto &m = rhock_mnemonics[k];
            if (m.opcode == opcode) {
                displayOpcode(m);
                return;
            }
        }

        printf("%04x: Unknown opcode %02x\n", addr-1, opcode);
    }

    void Objdump::displayOpcode(struct rhock_mnemonic &m)
    {
        printf("%04x: ", addr-1);
        printf("%s ", m.name);
        int n = strlen(m.format);
        
        for (int i=0; i<n; i++) {
            switch (m.format[i]) {
                case FORMAT_IMMEDIATE_F:
                    printf("%g ", readNumber());
                    break;
                case FORMAT_PROGRAM:
                    printf("program_%d ", readInt());
                    break;
                case FORMAT_STRING:
                    std::cout << "\"" << readString() << "\" ";
                    break;
                case FORMAT_VARIABLE:
                    printf("var%d ", readByte());
                    break;
                case FORMAT_BYTE:
                    printf("%d ", readByte());
                    break;
                case FORMAT_ADDRESS: {
                    auto addr = readAddr();
                    if (RHOCK_IS_NATIVE(addr)) {
                        if (natives.count(addr)) {
                            printf("%s ", natives[addr].c_str());
                        } else {
                            printf("native_%d ", RHOCK_ADDR_TO_NATIVE(addr));
                        }
                    } else {
                        printf("%04x ", addr);
                    }
                    break;
                    }
                case FORMAT_ENTRY: {
                    rhock_entry entry = readByte();
                    auto addr = rhock_entry_addr(&obj, entry);
                    printf("%s ", symbols[addr].c_str());
                    break;
                    }
                case FORMAT_EVENT: {
                    printf("%u ", readInt());
                    break;
                    }
            }
        }

        printf("\n");
    }
            
    uint8_t Objdump::readByte()
    {
        if (addr > obj.size) {
            return 0x00;
        } else {
            return obj.data[addr++];
        }
    }
    
    uint16_t Objdump::readAddr()
    {
        uint16_t i;
        i = readByte()<<8;
        i |= readByte()<<0;

        return i;
    }

    uint16_t Objdump::readShort()
    {
        uint32_t s = 0;
        s |= readByte()<<8;
        s |= readByte()<<0;

        return s;
    }

    uint32_t Objdump::readInt()
    {
        uint32_t i;
        i = readByte()<<24;
        i |= readByte()<<16;
        i |= readByte()<<8;
        i |= readByte()<<0;

        return i;
    }
            
    double Objdump::readNumber()
    {
        return RHOCK_VALUE_TO_NUMBER(readInt());
    }

    std::string Objdump::readString()
    {
        auto size = readByte();
        std::string result;

        for (int n=0; n<size; n++) {
            result += readByte();
        }

        return result;
    }
}
