#ifndef ALGO_RECUIT_H_
#define ALGO_RECUIT_H_

#include <vector>
#include <set>
#include <iostream> // cout, endl
#include <string>
#include <algorithm> // for_each, accumulate
#include <random> // default_random_engine, uniform_real_distribution, random_device
#include <cmath>
#include <mutex>

#include "data.h"
#include "solution.h"

struct AlgoRecuit
{
    static std::mutex employee_distribution_mutex;
    static std::set<std::vector<int>> employee_distribution_taboo;
    static void generate_employee_distribution(std::vector<int>& distribution,
            size_t nb_ecosystem, size_t nb_employee);

    // problem and solution data
    ProblemData data;
    Solution *best_sol;
    Solution *current_sol;
    Solution *wip_sol;
    bool new_solution;

    // Simulated annealing algorithm data
    float temperature;
    float coeficient_refroidissement;
    int max_steps;

    // Random int generator.
    std::mt19937 int_gen{std::random_device{}()};
    // Random float generator (between 0 and 1).
    std::default_random_engine float_generator;
    // Uniform distribution.
    std::uniform_real_distribution<float> float_distribution;

    // method for managing external use
    AlgoRecuit(ProblemData data, int steps=100);
    virtual ~AlgoRecuit() {};
    void init_solution(bool new_best = false);
    void init_solution(Solution *sol);
    void run_one_loop();
    bool is_new_solution();
    void generate_ecosystem_solution(ecosystem_t eco, Solution * wip, int starting_id, int nb_employes);

    // Swap an animal between two employee.
    // probabilty of selection is proportionel to weigh
    // for employe selection and animal selection
    void generate_neighboor_solution_proportional_probabilty();

    float calculate_delta(Solution * sol1, Solution * sol2);
    bool metropolis_criteria(float delta, float temperature);

    int random_int(int min, int max);
    int random_employe_per_weight(ecosystem_sol_t * eco, bool min_or_not_max);
    int random_animal_per_weight(std::vector<int> * tasks);

};

#endif
