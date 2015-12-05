#ifndef ALGO_RECUIT_H_
#define ALGO_RECUIT_H_

#include <vector>
#include <iostream> // cout, endl
#include <string>
#include <algorithm> // for_each, accumulate
#include <random> // default_random_engine, uniform_real_distribution, random_device
#include <cmath>

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
using std::uniform_int_distribution;
using std::random_device;
using std::mt19937;
using std::advance;
using std::exp;
using std::pair;
using std::max_element;
using std::min_element;
using std::distance;
using std::discrete_distribution;

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
        float coeficient_refroidissement;
        int max_steps;
        // random selection of an ecosystem
        // or an employe
        //random_device rd;
        mt19937 int_gen{random_device{}()};
        // random float (0,1) for metropolis criteria
        default_random_engine float_generator;
        uniform_real_distribution<float> float_distribution;

        // method for managing external use
        AlgoRecuit(ProblemData data, int steps=100);
        ~AlgoRecuit();
        void init();
        void init_solution(bool new_best = false);
        void init_solution(Solution *sol);
        void run_one_loop();
        bool is_new_solution();
        void generate_ecosystem_solution(ecosystem_t eco, Solution * wip, int starting_id, int nb_employes);

        // method for algorithm (should be private but privacy selfishness

        // take one animal and change employe in same ecosystem
        void generate_neighboor_solution();
        // swap two animals from two employes in same ecosystem
        void generate_neighboor_solution_swap();
        // select employe1 with most weight and employe2 with least weight and transfer
        void generate_neighboor_solution_transfer();
        // select like generate_neighboor_solution_transfer but
        // probabilty of selection is proportionel to weigh
        // for employe selection and animal selection
        void generate_neighboor_solution_proportional_probabilty();

        float calculate_delta(Solution * sol1, Solution * sol2);
        bool metropolis_criteria(float delta, float temperature);
        int random_int(int min, int max);
        int random_employe_per_weight(ecosystem_sol_t * eco);
        int random_animal_per_weight(vector<int>* tasks);
};

#endif
