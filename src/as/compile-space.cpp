#include "compile-space.h"

namespace Rhock
{
    CompileSpace::~CompileSpace()
    {
        for (auto as : assemblers) {
            delete as;
        }
    }

    void CompileSpace::addAssembler(As *assembler)
    {
        assemblers.push_back(assembler);
        assembler->setCompileSpace(this);
    }
            
    void CompileSpace::addAssemblerRef(As &assembler)
    {
        addAssembler(&assembler);
    }

    As *CompileSpace::getAssembler(uint32_t id)
    {
        for (auto as : assemblers) {
            if (as->getId() == id) {
                return as;
            }
        }

        return NULL;
    }
            
    std::vector<As*> CompileSpace::getAssemblers()
    {
        return assemblers;
    }
}
