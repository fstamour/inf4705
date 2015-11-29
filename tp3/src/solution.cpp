#include "solution.h"

double solution_standard_deviation(Solution * sol) {

    int sum = 0;
    int sum_square = 0;
    int n = 0;
    int charge = 0;
    for(auto eco: sol->ecosystems) {
        for(auto m: eco) {
            charge = accumulate(m.second.begin(), m.second.end(), 0);
            n++;
            sum += charge;
            sum_square += charge*charge;
        }
    }

    if(n == 0){
        return std::numeric_limits<double>::max();
    }
    double mean = (double)sum/(double)n;

    return (double)sum_square/(double)n - mean*mean;
    // just less calculus
    //return sqrt((float)sum_square/(float)n - mean*mean);
}
