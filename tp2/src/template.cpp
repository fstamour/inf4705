#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime> // timing
#include <unistd.h> // For option parsing

#include "algo_ALGO.h"
#include "option_parse.h"

int main(int argc, char ** argv) {
    Options opt;
    opt.initialize(argc, argv);

    clock_t tStart = 0;
    clock_t tStop = 0;

    struct exemplaire * e = opt.getExemplaire();

    tStart = clock();
    mise_en_boite_ALGO(e);
    tStop = clock();
    e->time = tStop - tStart;

    if (opt.verbose_p) {
        print_solution(e);
    }

    free_exemplaire(e);
}
