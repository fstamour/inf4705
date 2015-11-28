#include "solution.h"

float solution_standard_deviation(Solution * sol) {

    int sum = 0;
    int sum_square = 0;
    int n = 0;
    for(auto eco: sol->ecosystems) {
        for(auto m: eco) {
            for(auto value: m.second){
                sum += value;
                sum_square += value*value;
                n++;
            }
        }
    }

    float mean = (float)sum/(float)n;
    return sqrt((float)sum_square/(float)n - mean*mean);
}
