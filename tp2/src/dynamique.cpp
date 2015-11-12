#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime> // timing
#include <unistd.h> // For option parsing

#include "exemplaire_struct.h"
#include "algo_dynamic.h"

int main(int argc, char ** argv)
{
    // Pour le "parsing" des arguments.
    bool do_print = false;
    char *filename = nullptr;
    int opt;

    clock_t tStart = 0;
    clock_t tStop = 0;

    while((opt = getopt(argc, argv, "pa:f:")) != -1) {
        switch(opt) {
            case 'p':
                do_print = true;
                break;

            case 'f':
                filename = optarg;
                break;
        }
    }

    if(filename == nullptr) {
        std::cout << "Usage: " << std::endl;
    }

    if(do_print){
        std::cout << "print : " << do_print << std::endl;
        std::cout << "filename : " << filename << std::endl;
    }

    struct exemplaire * e;
    e = make_exemplaire(filename);

    tStart = clock();
    mise_en_boite_dynamic(e);
    tStop = clock();
    e->time = tStop - tStart;
    if(do_print) print_solution(e);

    free_exemplaire(e);
}
