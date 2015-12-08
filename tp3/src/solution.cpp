#include "solution.h"

using std::vector;
using std::map;
using std::sqrt;
using std::accumulate;

double Solution::compute_variance() {
    double sum = 0;
    double sum_of_square = 0;
    double n = 0;
    double charge = 0;
    for(auto eco: ecosystems) {
        for(auto m: eco) {
            charge = accumulate(m.second.begin(), m.second.end(), 0);
            n++;
            sum += charge;
            sum_of_square += charge*charge;
        }
    }

    if(n == 0) {
        return std::numeric_limits<double>::max();
    }

    double mean = sum/n;
    double mean_of_squares = sum_of_square/n;
    double variance = mean_of_squares - mean*mean;

    return variance;
}

void Solution::print_details(std::ostream& out) {
    for(auto eco_sol: ecosystems) {
        out << eco_sol.size() << "\n";
        for(auto sol: eco_sol) {
            out << sol.second.size() << " ";
            for(auto animal: sol.second) {
                out << animal << " ";
            }
            out << "\n";
        }
    }
}

