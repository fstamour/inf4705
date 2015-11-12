#include <string>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime> // timing
#include "exemplaire_struct.h"
#include "algo_vorace.h"

int main(int argc, char ** argv)
{
    bool do_print = false;
    char *filename = nullptr;
    int algo = -1;
    int opt;
    srand(time(0));
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

            case 'a':
                if(strncmp(optarg, "vorace", 6) == 0){
                    algo = 1;
                }
                else{
                    std::cout << "algo not implemented" << std::endl;
                    exit(1);
                }

        }
    }
    if(do_print){
        std::cout << "print : " << do_print << std::endl;
        std::cout << "filename : " << filename << std::endl;
    }

    struct exemplaire * e;
    e = make_exemplaire(filename);

    if(algo == 1) {
        tStart = clock();
        vorace(e);
        tStop = clock();
        e->time = tStop - tStart;
        if(do_print) print_solution(e);
    }

    free_exemplaire(e);
}
