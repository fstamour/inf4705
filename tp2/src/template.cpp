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
    opt.initialize(Algo::ALGO, argc, argv);

    struct exemplaire * e = opt.get_exemplaire();

    clock_t& start_time = e->start_time;
    start_time = 0;
    clock_t stop_time = 0;

    start_time = clock();
    mise_en_boite_ALGO(opt);
    stop_time = clock();
    e->time = stop_time - start_time;

    std::cout << "execution time\t" << e->time << "\t";
    std::cout << "total volume\t" << get_result_volume(e) << "\t";
    if (opt.verbose_p) {
        std::cout << "Nombre d'element\t" << e->nb_element << "\t";
        std::cout << "Nombre de boite\t" << e->nb_box << "\t";
        std::cout << "Capacite\t" << e->capacity << "\t";
        print_solution(e);
        std::cout << std::flush;
        
        //std::cout << "element restant: " << std::endl;
        //for(unsigned int i = 0; i < e->data_.size(); i++){
            //std::cout << e->data_[i] << " ";
        //}
    }
}
