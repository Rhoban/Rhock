#include <sstream>
#include <iostream>
#include <getopt.h>
#include <util/util.h>
#include "as.h"
#include "compile-space.h"

using namespace std;

void usage()
{
    cerr << "Usage:" << endl;
    cerr << "rhock-as [filename]" << endl;
    cerr << endl;
}

int main(int argc, char **argv)
{
    string mode("assemble");
    string filename("");
    string output("a.rhobj");
    int index;

    while ((index = getopt(argc, argv, "o:d")) != -1) {
        switch (index) {
            case 'o':
                output = string(optarg);
                break;
        }
    }

    if (optind != argc) {
        try {
            Rhock::CompileSpace space;
            // Parsing files
            for (int k=optind; k<argc; k++) {
                auto as = new Rhock::As;
                as->parseFile(string(argv[k]));
                space.addAssembler(as);
            }
            // Resolving symbols
            for (auto as : space.getAssemblers()) {
                as->resolveSymbols();
            }
            // Writing objects
            unsigned int k = 0;
            for (auto as : space.getAssemblers()) {
                std::stringstream ss;
                ss << (char)('a'+k) << ".rhobj";
                as->writeFile(ss.str());
                k++;
            }
        } catch (runtime_error error) {
            std::cerr << error.what() << std::endl;
            return EXIT_FAILURE;
        }
    } else {
        usage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
