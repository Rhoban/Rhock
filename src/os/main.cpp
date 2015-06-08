#include <unistd.h>
#include <string.h>
#include <iostream>
#include <getopt.h>
#include <util/util.h>
#include <rhock/obj.h>
#include <rhock/program.h>
#include <rhock/vm.h>
#include <rhock/config.h>
#include <rhock/memory.h>
#include <rhock/chain.h>
#include <errors/errors.h>

using namespace std;

#define FREQUENCY   1000

void usage()
{
    cerr << "Usage:" << endl;
    cerr << "rhock [filename]" << endl;
    cerr << endl;
}

int main(int argc, char **argv)
{
    string filename("");
    int index;
    bool error_code = false;
    float max_time = 0;

    while ((index = getopt(argc, argv, "t:e")) != -1) {
        switch (index) {
            case 't':
                max_time = atof(optarg);
                break;
            case 'e':
                error_code = true;
                break;
        }
    }

    if (optind != argc) {
        rhock_vm_init();

        for (int k=optind; k<argc; k++) {
            bool start = true;
            filename = string(argv[k]);
            if (startswith(filename, "=")) {
                start = false;
                filename = filename.substr(1);
            }

            if (!file_exists(filename)) {
                std::cout << "Can't open the file: " << filename << std::endl;
                return EXIT_FAILURE;
            }

            std::string bin = file_get_contents(filename);
            char *data = new char[bin.size()];
            memcpy(data, bin.c_str(), bin.size());
        
            rhock_memory_addr objAddr = rhock_vm_create_obj();

            if (objAddr == RHOCK_NULL) {
                printf("Error: unable to allocate the object\n");
                return EXIT_FAILURE;
            }
        
            rhock_obj *obj = rhock_get_obj(objAddr);
            if (!rhock_obj_load(obj, (uint8_t*)data, bin.size())) {
                std::cerr << "Failing to load binary file" << std::endl;
                return EXIT_FAILURE;
            }
        
            if (start) {
               rhock_program_load(obj);
            }
        }

        // Loading object
        float t = 0;
        int ticks = 1000000/FREQUENCY;
        while (true) {
            if (!rhock_vm_tick()) {
                break;
            }
            usleep(ticks);
            t += 1.0/FREQUENCY;
            if (max_time!=0 && t>max_time) {
                break;
            }
        }

        rhock_memory_addr prog = rhock_vm_get_programs();
        while (prog != RHOCK_LAST) {
            auto error = rhock_program_error(prog);
            if (error != RHOCK_ERROR_NO_ERROR) {
                if (error_code) {
                    printf("ERROR[%d]", error);
                } else {
                    std::cout << "Program crashed: " << rhock_program_error_str(error);
                }
                printf("\n");
            }
            rhock_program_unload(prog);

            prog = rhock_chain_next(prog);
        }
    } else {
        usage();
        return EXIT_FAILURE;
    }

    /*
    int total, used, overhead;
    rhock_meminfo(&total, &used, &overhead);
    printf("Memory: %d/%d\n", used, total);
    */

    return EXIT_SUCCESS;
}
