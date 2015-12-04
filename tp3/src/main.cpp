#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h> // For option parsing.

#include "data.h"
#include "stats.h"
#include "algo_recuit.h"


template<typename T>
std::string to_string(const T& x) {
    std::ostringstream oss;
    oss << x;
    return oss.str();
}


using std::cout;
using std::cerr;
using std::endl;
using std::string;

// Calcul et affiche quelques statistiques sur toute les données.
void general_stats() {
}

int main(int argc, char *argv[])
{
    // "Globals"
    string filename;
    bool verbose_p = false;
    // Le nombre d'etape pour le recuit
    int steps = 100;
    
    // Parse command-line options
    int opt;
    while((opt = getopt(argc, argv, "pf:s:")) != -1) {
        switch(opt) {
            case 'p':
                verbose_p = true;
                break;
            case 'f':
                filename = optarg;
                break;
            case 's':
                steps = std::stoi(optarg);
                break;
            //case '?':
                //cerr << "Unrecognized option"
        }
    }
    // TODO Check if arguments are valid.

    AlgoRecuit algo(filename, steps);

    algo.init_solution();
    while(true){
        algo.run_one_loop();
        if(algo.new_solution) {
            algo.print_solution(algo.best_sol, verbose_p);
            algo.new_solution = false;
        }
    }

//    general_stats();

    // Eval data

    // Print solutions
    // Loop!

    return 0;
}

