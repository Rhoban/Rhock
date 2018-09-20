#include <sstream>
#include <stdexcept>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <rhock/obj.h>
#include <rhock/obj_write.h>
#include <rhock/native.h>
#ifdef RHOCK_NO_VM
#include <rhock/std.h>
#endif
#include <insts/mnemonics.h>
#include <util/util.h>
#include "compile-space.h"
#include "as.h"

namespace Rhock
{
    std::string stripQuotes(std::string string)
    {
        if (string.size() >= 2 && string[0]=='"' && string[string.size()-1]=='"') {
            string = string.substr(1, string.size()-2);
        }

        return string;
    }

    std::string removeComment(std::string line)
    {
        auto parts = split(line, '#');

        if (parts.size()) {
            return parts[0];
        } else {
            return "";
        }
    }

    As::As()
        : input(""), addr(0), isEntry(false), isStopped(false), 
        numEntries(0), numVariables(0)
    {
        for (unsigned int k=0; k<rhock_mnemonics_count; k++) {
            auto &mnemonic = rhock_mnemonics[k];
            auto name = std::string(mnemonic.name);
            auto guess = std::string(mnemonic.guess);
            mnemonics[std::string(mnemonic.name)] = &mnemonic;
        }

        for (int i=0; i<rhock_native_symbols_count; i++) {
            auto &symbol = rhock_native_symbols[i];
            natives[std::string(symbol.name)] = RHOCK_NATIVE_TO_ADDR(symbol.id);
        }
    }
            
    void As::setCompileSpace(CompileSpace *space_)
    {
        space = space_;
    }
            
    uint32_t As::getId()
    {
        return id;
    }

    void As::assembleFile(std::string filename)
    {
        parseFile(filename);
        resolveSymbols();
    }

    void As::parseFile(std::string filename)
    {
        if (!file_exists(filename)) {
            std::cerr << "Can't open input file: " << filename << std::endl;
            return;
        }
        
        input = filename;
        process(file_get_contents(filename));
    }

    void As::assemble(std::string inputData)
    {
        process(inputData);
        resolveSymbols();
    }

    void As::process(std::string inputData)
    {
        initObject();

        data = "";

        auto lines = split(inputData, '\n');
        line_number = 0;
        for (auto line : lines) {
            line_number++;
            processLine(line);
        }
    }
            
    std::string As::processError(std::string inputData)
    {
        try {
            process(inputData);
        } catch (std::runtime_error exc) {
            return exc.what();
        }

        return "";
    }

    rhock_symbol *As::resolveSymbol(rhock_resolve resolve)
    {
        if (resolve.id == 0 || resolve.id == id) {
            if (symbols.count(resolve.symbol)) {
                auto &symbol = symbols[resolve.symbol];
                return &symbol;
            }
        } else {
            if (space != NULL) {
                auto as = space->getAssembler(resolve.id);
                if (as != NULL) {
                    return as->resolveSymbol(resolve);
                }
            }
        }

        return NULL;
    }

    std::string As::resolveSymbolsError()
    {
        try {
            resolveSymbols();
        } catch (std::runtime_error exc) {
            return exc.what();
        }

        return "";
    }

    void As::resolveSymbols()
    {
        // Resolve references
        for (auto resolve : resolves) {
            line_number = resolve.line_number;
            rhock_symbol *symbol;

            if ((symbol = resolveSymbol(resolve)) != NULL) {
                auto target = symbols[resolve.symbol];
                if (resolve.type == RHOCK_SYM_ENTRY) {
                    data[resolve.addr] = symbol->entry;
                } else if (resolve.type == RHOCK_SYM_VARIABLE) {
                    data[resolve.addr] = symbol->variable;
                } else {
                    data[resolve.addr+0] = (symbol->addr>>8)&0xff;
                    data[resolve.addr+1] = (symbol->addr>>0)&0xff;
                }
            } else {
                if (resolve.type == RHOCK_SYM_ADDR && natives.count(resolve.symbol)) {
                    data[resolve.addr+0] = (natives[resolve.symbol]>>8)&0xff;
                    data[resolve.addr+1] = (natives[resolve.symbol]>>0)&0xff;
                } else {
                    std::stringstream ss;
                    ss << "Unknown symbol: " << resolve.symbol;
                    if (resolve.id != id && resolve.id != 0) {
                        ss << " (program " << resolve.id << ")";
                    }
                    error(ss.str());
                }
            }
        }
    }

    std::vector<unsigned char> As::getBinaryBytes()
    {
        auto str = getBinary();
        std::vector<unsigned char> bytes;

        for (int k=0; k<str.size(); k++) {
            bytes.push_back(str[k]&0xff);
        }

        return bytes;
    }

    std::string As::getBinary()
    {
        rhock_set_id(&obj, id);

        auto nameBin = new char[RHOCK_OBJ_NAME_SIZE];
        if (name.size() > RHOCK_OBJ_NAME_SIZE) {
            name = name.substr(0, RHOCK_OBJ_NAME_SIZE);
        }
        while (name.size() < RHOCK_OBJ_NAME_SIZE) {
            name += '\0';
        }
        memcpy(nameBin, name.c_str(), name.size());
        rhock_set_name(&obj, nameBin);

        auto varBin = new uint8_t[numVariables*4];
        for (auto entry : variables) {
            auto variable = entry.second;
            int value = variable.def;
            varBin[variable.num*4+0] = (value>>24)&0xff;
            varBin[variable.num*4+1] = (value>>16)&0xff;
            varBin[variable.num*4+2] = (value>>8)&0xff;
            varBin[variable.num*4+3] = (value>>0)&0xff;
        }
        rhock_set_variables(&obj, varBin, numVariables);
        
        auto entryBin = new uint8_t[numEntries*3];
        for (auto entry : symbols) {
            auto symbol = entry.second;
            if (symbol.type == RHOCK_SYM_ENTRY) {
                entryBin[symbol.entry*3+0] = symbol.entryState;
                entryBin[symbol.entry*3+1] = (symbol.addr>>8)&0xff;
                entryBin[symbol.entry*3+2] = (symbol.addr>>0)&0xff;
            }
        }
        rhock_set_entries(&obj, entryBin, numEntries);

        auto dataBin = new uint8_t[data.size()];
        memcpy(dataBin, data.c_str(), data.size());
        rhock_set_data(&obj, dataBin, data.size());

        auto buffer = new char[obj.size];
        rhock_write(&obj, (uint8_t*)buffer);

        std::string binary(buffer, obj.size);

        delete[] nameBin;
        delete[] varBin;
        delete[] entryBin;
        delete[] dataBin;
        delete[] buffer;

        return binary;
    }

    void As::writeFile(std::string output)
    {
        file_put_contents(output, getBinary());
    }

    void As::initObject()
    {
        // Object file
        rhock_obj_init(&obj);

        // Setting object id to the UNIX timestamp
        id = time(NULL);

        // Object name
        name = "main";
    }
    
    void As::processLine(std::string line)
    {
        line = trim(removeComment(line));

        if (line != "") {
            if (endswith(line, ":")) {
                // New symbol
                rhock_symbol s;
                s.name = line.substr(0, line.size()-1);
                if (s.name == "main") {
                    isEntry = true;
                }
                s.addr = addr;
                if (isEntry) {
                    s.type = RHOCK_SYM_ENTRY;
                    s.entry = (numEntries++);
                } else {
                    s.type = RHOCK_SYM_ADDR;
                }
                s.entryState = isStopped ? RHOCK_THREAD_STOPPED : RHOCK_THREAD_RUNNING;
                symbols[s.name] = s;
                isEntry = false;
                isStopped = false;
            } else if (startswith(line, ".")) {
                // New special op
                auto parts = splitCSV(line.substr(1));
                auto op = parts[0];
                if (op == "variable") {
                    if (parts.size()!=2 && parts.size()!=3) {
                        error(".variable invalid");
                    } 

                    auto variable = parts[1];
                    if (variables.count(variable)) {
                        std::stringstream ss;
                        ss << ".variable " << variable << " defined multiple times";
                        error(ss.str());
                    }
                    rhock_variable var;
                    var.num = numVariables++;
                    var.def = 0;

                    if (parts.size()>2) {
                        var.def = RHOCK_NUMBER_TO_VALUE(atof(parts[2].c_str()));
                    }
                    variables[parts[1]] = var;

                    rhock_symbol sym;
                    sym.type = RHOCK_SYM_VARIABLE;
                    sym.name = variable;
                    sym.variable = var.num;
                    symbols[variable] = sym;
                } else if (op == "thread") {
                    if (parts.size()!=1) {
                        error(".thread invalid, no arguments are needed");
                    }
                    isEntry = true;
                } else if (op == "native") {
                    if (parts.size()!=3) {
                        error(".native invalid, arguments are name and number");
                    }
                    std::string name = parts[1];
                    int number = atof(parts[2].c_str());
                    natives[name] = RHOCK_NATIVE_TO_ADDR(number);
                } else if (op == "stopped") {
                    if (parts.size()!=1) {
                        error(".stopped invalid, no arguments are needed");
                    }
                    isStopped = true;
                } else if (op == "name") {
                    if (parts.size()!=2) {
                        error(".name without argument");
                    }
                    name = stripQuotes(parts[1]);
                } else if (op == "id") {
                    if (parts.size()!=2) {
                        error(".id without argument");
                    }
                    id = atoi(parts[1].c_str());
                } else {
                    std::stringstream ss;
                    ss << "Unknown operation: ." << op;
                    error(ss.str());
                }
            } else {
                processMnemonic(line);
            }
        }
    }
            
    void As::error(std::string err)
    {
        std::stringstream ss;
        ss << input << ":L" << line_number << " " << err;

        throw std::runtime_error(ss.str());
    }
            
    void As::processMnemonic(std::string line)
    {
        auto parts = splitCSV(line);
        auto mnemonic = parts[0];

        for (unsigned int k=0; k<rhock_mnemonics_count; k++) {
            uint32_t pid = 0;
            auto &m = rhock_mnemonics[k];
            auto name = std::string(m.name);
            auto guess = std::string(m.guess);

            bool matchName = (name == mnemonic);
            bool matchGuess = (guess == mnemonic);
 
            if (matchName || matchGuess) {
                std::string buffer = "";

                bool invalid = false;

                // Adding mnemonic opcode
                auto args = strlen(m.format);

                if ((parts.size()-1) != args) {
                    invalid = true;
                }

                // Reading format
                for (unsigned int i=0; (!invalid) && i<args; i++) {
                    auto fmt = m.format[i];
                    auto value = parts[i+1];
                    switch (fmt) {
                        case FORMAT_IMMEDIATE_F:
                            if (!isNumber(value)) {
                                invalid = true;
                                break;
                            } else {
                                appendNumber(atof(value.c_str()), buffer);
                            }
                            break;
                        case FORMAT_PROGRAM:
                            if (!isNumber(value)) {
                                invalid = true;
                                break;
                            } else {
                                pid = atoi(value.c_str());
                                appendInt(pid, buffer);
                            }
                            break;
                        case FORMAT_STRING:
                            if (!isString(value)) {
                                invalid = true;
                                break;
                            } else {
                                appendString(value, buffer);
                            }
                            break;
                        case FORMAT_VARIABLE:
                            if (isNumber(value)) {
                                appendByte(atoi(value.c_str()), buffer);
                            } else {
                                rhock_resolve r;
                                r.id = pid;
                                r.line_number = line_number;
                                r.addr = addr+1+buffer.size();
                                r.type = RHOCK_SYM_VARIABLE;
                                r.symbol = value;
                                appendByte(0x00, buffer);
                                resolves.push_back(r);
                            }
                            break;
                        case FORMAT_BYTE:
                            if (!isNumber(value)) {
                                invalid = true;
                                break;
                            } else {
                                appendByte(atoi(value.c_str()), buffer);
                            }
                            break;
                        case FORMAT_ADDRESS: {
                            if (isNumber(value)) {
                                appendShort(atoi(value.c_str()), buffer);
                            } else {
                                rhock_resolve r;
                                r.id = pid;
                                r.line_number = line_number;
                                r.addr = addr+1+buffer.size();
                                r.type = RHOCK_SYM_ADDR;
                                r.symbol = value;
                                appendByte(0x00, buffer);
                                appendByte(0x00, buffer);
                                resolves.push_back(r);
                            }
                            break;
                            }
                        case FORMAT_ENTRY: {
                            if (isNumber(value)) {
                                appendByte(atoi(value.c_str()), buffer);
                            } else {
                                rhock_resolve r;
                                r.id = pid;
                                r.line_number = line_number;
                                r.addr = addr+1+buffer.size();
                                r.type = RHOCK_SYM_ENTRY;
                                r.symbol = value;
                                appendByte(0x00, buffer);
                                resolves.push_back(r);
                            }
                            break;
                            }
                        case FORMAT_EVENT: {
                            if (isNumber(value)) {
                                appendInt(atoi(value.c_str()), buffer);
                            } else {
                                invalid = true;
                            }
                            break;
                            }
                    }
                }
                    
                if (invalid) {
                    if (matchName) {
                        // We can't process this opcode, which is an exact name
                        std::stringstream ss;
                        ss << "Invalid argument for mnemonic " << mnemonic;
                        error(ss.str());
                    } else {
                        // We can't process this opcode, maybe the guess is wrong, let's
                        // try another one
                        continue;
                    }
                } else {
                    // We processed this opcode successfully
                    data += (char)m.opcode;
                    data += buffer;
                    addr += buffer.size() + 1;
                    return;
                }
            }
        }

        std::stringstream ss;
        ss << "Unknown mnemonic: " << mnemonic;
        error(ss.str());
    }
            
    void As::appendByte(unsigned char byte, std::string &output)
    {
        output += byte;
    }

    void As::appendString(std::string string, std::string &output)
    {
        string = stripQuotes(string);
        appendByte(string.size(), output);
        for (unsigned int i=0; i<string.size(); i++) {
            appendByte(string[i], output);
        }
    }

    void As::appendNumber(double number, std::string &output)
    {
        appendInt(RHOCK_NUMBER_TO_VALUE(number), output);
    }

    void As::appendInt(int value, std::string &output)
    {
        appendByte((value>>24)&0xff, output);
        appendByte((value>>16)&0xff, output);
        appendByte((value>>8)&0xff, output);
        appendByte(value&0xff, output);
    }
            
    void As::appendShort(unsigned short value, std::string &output)
    {
        appendByte((value>>8)&0xff, output);
        appendByte(value&0xff, output);
    }
            
    bool As::isString(std::string value)
    {
        return (value.size()>=2 && value[0]=='"' && value[value.size()-1]=='"');
    }

    bool As::isVariable(std::string value)
    {
        return variables.count(value);
    }

    bool As::isNumber(std::string value)
    {
        for (unsigned int i=0; i<value.size(); i++) {
            auto c = value[i];
            if ((c<'0' || c>'9') && c!='.' && c!='-') {
                return false;
            }
        }

        return true;
    }
}
