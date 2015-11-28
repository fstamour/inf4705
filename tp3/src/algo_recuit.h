#ifndef ALGO_RECUIT_H_
#define ALGO_RECUIT_H_

#include <vector>
#include <iostream> // cout, endl
#include <string>
#include <algorithm> // for_each
#include <random>

#include "data.h"
#include "solution.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::accumulate;
using std::for_each;
using std::default_random_engine;
using std::uniform_real_distribution;

class AlgoRecuit
{
    public:
        // problem and solution data
        ProblemData data;
        Solution *best_sol;
        Solution *current_sol;
        Solution *wip_sol;
        bool new_solution;

        // algorithm data
        float temperature;
        int coeficient_refroidissement;
        int max_steps;
        default_random_engine generator;
        uniform_real_distribution<float> distribution;

        // method for managing external use
        AlgoRecuit(string filename, int steps=100);
        AlgoRecuit(ProblemData data, int steps=100);
        ~AlgoRecuit();
        void init();
        void init_solution();
        void init_solution(Solution *sol);
        void run_one_loop();
        bool is_new_solution();
        void print_solution();
        void print_solution(Solution * sol);
        void generate_ecosystem_solution(ecosystem_t eco, Solution * wip);

        // method for algorithm (should be private but privacy selfishness
        void generate_neighboor_solution();
        float calculate_delta(Solution * sol1, Solution * sol2);
        bool metropolis_criteria(float delta, float temperature);
};

#endif
