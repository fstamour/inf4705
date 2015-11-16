#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime> // timing
#include <unistd.h> // For option parsing

#include "algo_recuit_simule.h"
#include "option_parse.h"

int main(int argc, char ** argv) {
    RecuitOptions opt;
    struct recuit_simule_args args = opt.initialize(argc, argv);

    clock_t tStart = 0;
    clock_t tStop = 0;

    struct exemplaire * e = opt.getExemplaire();

    tStart = clock();
    mise_en_boite_recuit_simule(e, args.k_max, args.t, args.p, args.a);
    tStop = clock();
    e->time = tStop - tStart;

    std::cout << "execution time: " << e->time << std::endl;
    std::cout << "total volume: " << get_result_volume(e) << std::endl;
    if (opt.verbose_p) {
        print_solution(e);
        //std::cout << "element restant: " << std::endl;
        //for(unsigned int i = 0; i < e->data_.size(); i++){
            //std::cout << e->data_[i] << " ";
        //}
    }

    free_exemplaire(e);
}
