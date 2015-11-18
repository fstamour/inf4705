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

    std::cout << "execution time: " << e->time << std::endl;
    std::cout << "total volume: " << get_result_volume(e) << std::endl;
    if (opt.verbose_p) {
        std::cout << "Nombre d'element " << e->nb_element << "\n";
        std::cout << "Nombre de boite " << e->nb_box << "\n";
        std::cout << "Capacite " << e->capacity << "\n";
        print_solution(e);
        std::cout << std::flush;
    }

    free_exemplaire(e);
}
