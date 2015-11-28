#include "algo_recuit.h"

AlgoRecuit::AlgoRecuit(string filename, int steps) {
    data = make_problem_data(filename);
    max_steps = steps;
    init();
}

AlgoRecuit::AlgoRecuit(ProblemData data_, int steps) {
    data = data_;
    max_steps = steps;
    init();
}

void AlgoRecuit::init() {
    wip_sol = new Solution();
    current_sol = new Solution();
    best_sol = new Solution();
    new_solution = false;
    uniform_real_distribution<float> distribution(0.0, 1.0);
}

AlgoRecuit::~AlgoRecuit() {
}

void AlgoRecuit::init_solution() {
    unsigned int sum = 0;
    // distribution of employe according to weight of each ecosystem
    unsigned int current_sum = 0;
    for(auto ecosystem: data.ecosystem) {
        for(auto animal_type: ecosystem.eco) {
            sum += animal_type;
        }
    }

    float weight = 0.0;
    int nb_employes;
    int total_employes = data.nb_employee;
    for(auto ecosystem: data.ecosystem){
        current_sum = accumulate(ecosystem.eco.begin(), ecosystem.eco.end(), 0);
        weight = (float)current_sum / (float)sum;
        nb_employes = (int)((float)total_employes * weight);
        auto e = ecosystem_sol_t();
        for(int i = 0; i < nb_employes; ++i){
            e[i] = vector<int>();
        }
        wip_sol->ecosystems.push_back(e);
        generate_ecosystem_solution(ecosystem, wip_sol);
        sum -= current_sum;
        total_employes -= nb_employes;

    }

}

void AlgoRecuit::init_solution(Solution *sol) {
    best_sol = sol;
    current_sol = sol;
}

void AlgoRecuit::generate_ecosystem_solution(ecosystem_t ecosystem, Solution * wip) {
    int employe_id = 0;
    int nb_employe = wip->ecosystems[ecosystem.id].size();
    ecosystem_sol_t & e = wip->ecosystems[ecosystem.id];
    for(auto animal_weight: ecosystem.eco) {
        e[employe_id].push_back(animal_weight);
        employe_id = (employe_id + 1) % nb_employe;
    }
}

void AlgoRecuit::print_solution(Solution * sol) {
    int eco_id = 0;
    for(auto eco_sol: sol->ecosystems) {
        cout << "eco : " << eco_id << endl;
        eco_id++;
        for(auto sol: eco_sol) {
            cout << "employe id : " << sol.first << " [ ";
            for(auto animal: sol.second) {
                cout << animal << " ";
            }
            cout << "]" << endl;
        }
    }
}

void AlgoRecuit::run_one_loop() {
    /* algorithm skeleton
     * loop
     *      generated neighboor solution
     *      calculate delta from current solution
     *      if metropolis criteria
     *          wip -> current
     *          if current better than best
     *              current -> best
     *      update temperature
     */
    int delta;
    for(int i = 0; i < max_steps; ++i){
        generate_neighboor_solution();
        delta = calculate_delta(wip_sol, current_sol);
        if(metropolis_criteria(delta, temperature)){
            current_sol = wip_sol;
            if(calculate_delta(current_sol, best_sol) > 0){
                best_sol = current_sol;
            }
        }
        temperature = temperature * coeficient_refroidissement;
    }
}

void AlgoRecuit::generate_neighboor_solution() {
}

float AlgoRecuit::calculate_delta(Solution * sol1, Solution * sol2) {
    return solution_standard_deviation(sol1) - solution_standard_deviation(sol2);
}

bool AlgoRecuit::metropolis_criteria(float delta, float temperature) {

    if(delta > 0)
        return true;
    if(exp(delta/temperature) >= distribution(generator))
        return true;

    return false;
}
