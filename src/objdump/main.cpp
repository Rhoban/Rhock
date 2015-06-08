#include <iostream>
#include <getopt.h>
#include <util/util.h>
#include "objdump.h"

using namespace std;

void usage()
{
    cerr << "Usage:" << endl;
    cerr << "rhock-objdump [filename]" << endl;
    cerr << endl;
}

int main(int argc, char **argv)
{
    string filename("");
    string mode("disassemble");
    int index;

    while ((index = getopt(argc, argv, "c")) != -1) {
        switch (index) {
            case 'c':
                mode = "cdump";
                break;
        }
    }

    if (optind != argc) {
        filename = string(argv[optind]);
        try {
            Rhock::Objdump objdump(filename);
            if (mode == "disassemble") {
                objdump.disassemble();
            } else if (mode == "cdump") {
                objdump.cdump();
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
