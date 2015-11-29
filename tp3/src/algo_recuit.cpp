#include "algo_recuit.h"
#include <chrono>
#include <thread>

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
    uniform_real_distribution<float> float_distribution(0.0, 1.0);
    // TODO make them parametrisable
    temperature = 1.0;
    coeficient_refroidissement = 0.99;
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
        wip_sol->ecosystems.push_back(e);
        generate_ecosystem_solution(ecosystem, wip_sol, total_employes, nb_employes);
        sum -= current_sum;
        total_employes -= nb_employes;

    }
    *best_sol = *current_sol = *wip_sol;

}

void AlgoRecuit::init_solution(Solution *sol) {
    *best_sol = *sol;
    *current_sol = *sol;
}

void AlgoRecuit::generate_ecosystem_solution(ecosystem_t ecosystem, Solution * wip, int starting_id, int nb_employes) {
    int employe_id = starting_id - 1;
    ecosystem_sol_t & e = wip->ecosystems[ecosystem.id];
    for(int i = starting_id - nb_employes; i < starting_id; i++) {
        e[i] = vector<int>();
    }
    for(auto animal_weight: ecosystem.eco) {
        e[employe_id].push_back(animal_weight);
        employe_id--;
        if(employe_id < starting_id - nb_employes || employe_id < 0) {
            employe_id = starting_id - 1;
        }
    }
}

void AlgoRecuit::print_solution(Solution * sol) {
    int eco_id = 0;
    int current_total = 0;
    for(auto eco_sol: sol->ecosystems) {
        cout << "eco : " << eco_id << " size: " << eco_sol.size() << endl;
        eco_id++;
        for(auto sol: eco_sol) {
            cout << "employe id : " << sol.first << " [ ";
            for(auto animal: sol.second) {
                cout << animal << " ";
                current_total += animal;
            }
            cout << "] = " << current_total << endl;
            current_total = 0;
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
    float delta;
    for(int i = 0; i < max_steps; ++i){
        *wip_sol = *current_sol;
        generate_neighboor_solution_transfer();
        delta = calculate_delta(current_sol, wip_sol);
        if(metropolis_criteria(delta, temperature)){
            *current_sol = *wip_sol;
            if(calculate_delta(best_sol, current_sol) > 0){
                *best_sol = *current_sol;
                print_solution(best_sol);
                new_solution = true;
            }
        }
        temperature = temperature * coeficient_refroidissement;
    }
}

void AlgoRecuit::generate_neighboor_solution() {
    // move random animal to random employe in same ecosystem

    // select random ecosystem
    int max = data.ecosystem.size() - 1;
    if(max == 0){
        cout << "\x1b[37mERROR DATA.ECOSYSTEM.SIZE IS 0\x1b[0m" << endl;
        cout << "\x1b[35m" << max << endl;
    }
    int index = random_int(0, max);
    auto * eco = &wip_sol->ecosystems[index];

    // random employe in ecosystem_solution
    max = eco->size() - 1;
    if(max == 0 || max == -1){
        cout << "\x1b[37mERROR ECO->SIZE IS 0\x1b[0m" << endl;
        cout << "\x1b[35m" << max << endl;
    }

    map<int, vector<int>>::iterator employe;
    do {
        employe = eco->begin();
        advance(employe, random_int(0, max));
    } while ( employe->second.size() == 0 );
    auto * employe_vector = &employe->second;

    // random selection of animal in vector
    max = employe_vector->size() - 1;
    //if(max == 0 || max == -1){
        //cout << "\x1b[37mERROR EMPLOYE_VECTOR->SIZE IS 0\x1b[0m" << endl;
        //cout << "\x1b[35m" << max << endl;
    //}
    index = random_int(0, max);
    auto animal = (*employe_vector)[index];
    employe_vector->erase(employe_vector->begin() + index);

    // random selection of employe to receive animal in same ecosystem
    auto employe2 = eco->begin();
    max = eco->size() - 1;
    if(max == -1){
        max = 0;
    }
    advance(employe2, random_int(0, max));
    auto *employe2_vector = &employe2->second;
    employe2_vector->push_back(animal);

}

void AlgoRecuit::generate_neighboor_solution_swap() {

    // select random ecosystem with a least 2 employe
    int max = data.ecosystem.size() - 1;
    if(max == 0){
        cout << "\x1b[37mERROR DATA.ECOSYSTEM.SIZE IS 0\x1b[0m" << endl;
        cout << "\x1b[35m" << max << endl;
    }
    int index;
    ecosystem_sol_t * eco;
    do {
        index = random_int(0, max);
        eco = &wip_sol->ecosystems[index];
    } while(eco->size() < 2);

    // random employe in ecosystem_solution
    max = eco->size() - 1;
    if(max == 0 || max == -1){
        cout << "\x1b[37mERROR ECO->SIZE IS 0\x1b[0m" << endl;
        cout << "\x1b[35m" << max << endl;
    }
    map<int, vector<int>>::iterator employe1;
    do {
        employe1 = eco->begin();
        advance(employe1, random_int(0, max));
    } while ( employe1->second.size() == 0 );
    auto * employe1_vector = &employe1->second;

    // random employe different than previous one in same ecosystem
    map<int, vector<int>>::iterator employe2;
    do {
        employe2 = eco->begin();
        advance(employe2, random_int(0, max));
    } while ( employe2->second.size() == 0 || employe2 == employe1 );
    auto * employe2_vector = &employe2->second;

    // random selection of one animal for each employe
    int index1 = random_int(0, employe1_vector->size() - 1);
    int index2 = random_int(0, employe2_vector->size() - 1);
    auto animal_employe1 = (*employe1_vector)[index1];
    auto animal_employe2 = (*employe2_vector)[index2];

    // swap animals from employe

    // erase animal from vectors
    employe1_vector->erase( employe1_vector->begin() + index1);
    employe2_vector->erase( employe2_vector->begin() + index2);

    // insert animal in vectors
    employe1_vector->push_back(animal_employe2);
    employe2_vector->push_back(animal_employe1);

}

void AlgoRecuit::generate_neighboor_solution_transfer() {

    // select random ecosystem with a least 2 employe
    int max = data.ecosystem.size() - 1;
    if(max == 0){
        cout << "\x1b[37mERROR DATA.ECOSYSTEM.SIZE IS 0\x1b[0m" << endl;
        cout << "\x1b[35m" << max << endl;
    }
    int index;
    ecosystem_sol_t * eco;
    do {
        index = random_int(0, max);
        eco = &wip_sol->ecosystems[index];
    } while(eco->size() < 2);

    // select employe with max and min charge
    //map<int, vector<int>>::iterator e_max = eco->begin();
    //vector<int> * e_min, * e_max;
    int min_key, max_key;

    int current_sum, sum_min, sum_max;
    current_sum = accumulate(eco->begin()->second.begin(), eco->begin()->second.end(), 0);
    sum_min = sum_max = current_sum;
    // initialise key in map
    min_key = max_key = eco->begin()->first;
    for(auto e: *eco){
        current_sum = accumulate(e.second.begin(), e.second.end(), 0);
        if(current_sum < sum_min) {
            sum_min = current_sum;
            min_key = e.first;
        }
        if(current_sum > sum_max) {
            sum_max = current_sum;
            max_key = e.first;
        }
    }
    if(min_key == max_key){
        // TODO fix this
        cout << "min == max" << endl;
        return;
    }

    // swap biggest charge from max with smallest charge from min

    // if one element in array just transfer to other employe
    // this shoudln't happend
    if((*eco)[max_key].size() == 0) {
        //cout << "NEEED DEBUGGING" << endl;
        //cout << max_key << endl;
        //print_solution(wip_sol);
        return;
    }
    if((*eco)[min_key].size() == 1 || (*eco)[min_key].size() == 0) {
        // just transfer from max to min, no swap

        auto iter_max = max_element((*eco)[max_key].begin(), (*eco)[max_key].end());
        int index_max = distance((*eco)[max_key].begin(), iter_max);
        auto max_animal = (*eco)[max_key][index_max];
        (*eco)[max_key].erase((*eco)[max_key].begin() + index_max);
        (*eco)[min_key].push_back(max_animal);
        return;
    }

    auto iter_max = max_element((*eco)[max_key].begin(), (*eco)[max_key].end());
    auto iter_min = min_element((*eco)[min_key].begin(), (*eco)[min_key].end());

    int index_max = distance((*eco)[max_key].begin(), iter_max);
    int index_min = distance((*eco)[min_key].begin(), iter_min);
    auto max_animal = (*eco)[max_key][index_max];
    auto min_animal = (*eco)[min_key][index_min];

    (*eco)[max_key].erase((*eco)[max_key].begin() + index_max);
    (*eco)[min_key].erase((*eco)[min_key].begin() + index_min);

    (*eco)[max_key].push_back(min_animal);
    (*eco)[min_key].push_back(max_animal);
}

float AlgoRecuit::calculate_delta(Solution * sol1, Solution * sol2) {
    float s1 = solution_standard_deviation(sol1);
    float s2 = solution_standard_deviation(sol2);
    //cout << "sol1 - sol2" << endl;
    //cout << s1 << " - " << s2 << " = " << s1 - s2 << endl;
    return s1 - s2;
}

bool AlgoRecuit::metropolis_criteria(float delta, float temperature) {

    if(delta > 0.0)
        return true;
    if(delta == 0){
        return false;
    }
    float test = float_distribution(float_generator);
    float e = exp(delta/temperature);
    if(e >= test)
        return true;

    return false;
}

bool AlgoRecuit::is_new_solution() {
    if(new_solution) {
        new_solution = false;
        return true;
    }
    return false;
}

int AlgoRecuit::random_int(int min, int max) {
    return uniform_int_distribution<int>{min, max}(int_gen);
}
