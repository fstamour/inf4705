#include <iostream>
#include <sstream>
#include <string>

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
    // TODO Parse command-line options
    AlgoRecuit algo(argv[1], 1000);

    algo.init_solution();
    while(true){
        algo.run_one_loop();
    }

//    general_stats();

    // Eval data

    // Print solutions
    // Loop!

    return 0;
}

