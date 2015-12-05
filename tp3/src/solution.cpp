#include "solution.h"

using std::vector;
using std::map;
using std::sqrt;
using std::accumulate;

Solution::Solution(const Solution& sol):
    ecosystems(sol.ecosystems),
    std_deviation(-1)
{}

double Solution::get_std_dev() {
    if(std_deviation < 0) {
        int sum = 0;
        int sum_square = 0;
        int n = 0;
        int charge = 0;
        for(auto eco: ecosystems) {
            for(auto m: eco) {
                charge = accumulate(m.second.begin(), m.second.end(), 0);
                n++;
                sum += charge;
                sum_square += charge*charge;
            }
        }

        if(n == 0) {
            return std::numeric_limits<double>::max();
        }

        double mean = (double)sum/(double)n;
        double mean_of_square = (double)sum_square/(double)n;
        double variance = mean_of_square - mean*mean;
        std_deviation = sqrt(variance);
    }
    return std_deviation;
}

void Solution::print(bool verbose_p, std::ostream& out) {
    out << get_std_dev() << "\n";
    if(verbose_p) {
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
    out << std::flush;
}

