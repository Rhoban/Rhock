#pragma once

#include <vector>
#include <stdint.h>
#include "as.h"

namespace Rhock
{
    class CompileSpace
    {
        public:
            virtual ~CompileSpace();

            void addAssembler(As *assembler);
            void addAssemblerRef(As &assembler);
            As *getAssembler(uint32_t id);
            std::vector<As*> getAssemblers();

        protected:
            std::vector<As*> assemblers;
    };
}
