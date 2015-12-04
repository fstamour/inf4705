#include <chrono>
#include <thread>
#include <stdexcept>

#include "algo_recuit.h"

AlgoRecuit::AlgoRecuit(const ProblemData& data_, int steps):
    data(data),
    max_steps = steps;
{
    wip_sol = new Solution();
    current_sol = new Solution();
    best_sol = new Solution();
    new_solution = false;
    uniform_real_distribution<float> float_distribution(0.0, 1.0);
    // TODO make them parametrisable
    temperature = 1.0;
    coeficient_refroidissement = 0.99;
}

void AlgoRecuit::init_solution(Solution *sol) {
    if(sol == nullptr) {
        throw std:logic_error("Initializing with NULL solution");
    }
    *best_sol = *sol;
    *current_sol = *sol;
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
    for(int i = 0; i < max_steps; ++i) {
        *wip_sol = *current_sol;
        //generate_neighboor_solution_transfer();
        generate_neighboor_solution_proportional_probabilty();
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

void AlgoRecuit::generate_neighboor_solution_proportional_probabilty() {

    // select random ecosystem_sol_t
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


    // random select two employe
    int key_employe1, key_employe2;
    do {
        key_employe1 = random_employe_per_weight(eco);
        key_employe2 = random_employe_per_weight(eco);
    }
    while (key_employe1 == key_employe2);

    vector<int> &tasks_employe1 = (*eco)[key_employe1];
    vector<int> &tasks_employe2 = (*eco)[key_employe2];

    // random select animals to swap
    int task1_index, task2_index;
    task1_index = random_animal_per_weight(&tasks_employe1);
    task2_index = random_animal_per_weight(&tasks_employe2);

    // swap animals
    int animal_value1 = tasks_employe1[task1_index];
    int animal_value2 = tasks_employe2[task2_index];

    tasks_employe1.erase(tasks_employe1.begin() + task1_index);
    tasks_employe2.erase(tasks_employe2.begin() + task2_index);

    tasks_employe1.push_back(animal_value2);
    tasks_employe2.push_back(animal_value1);
}

float AlgoRecuit::calculate_delta(const Solution& sol1, const Solution& sol2) {
    float s1 = sol1->std_deviation();
    float s2 = sol2->std_deviation();
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
    // FIXME MAYBE Creation of a new PRNG is really coslty.
    return uniform_int_distribution<int>{min, max}(int_gen);
}

int AlgoRecuit::random_employe_per_weight(ecosystem_sol_t * eco){
    // vector of <employe_id, sum of hours>
    vector<pair<int,int>> sums;
    int total_sum = 0;
    int current_sum = 0;
    for(auto i: (*eco)){
        current_sum = accumulate(i.second.begin(), i.second.end(), 0);
        sums.push_back(pair<int, int>(i.first, current_sum));
        total_sum += current_sum;
    }

    vector<float> weights;
    for(auto sum: sums){
        weights.push_back((float)sum.second / (float)total_sum);
    }

    discrete_distribution<> dist(weights.begin(), weights.end());
    mt19937 gen(random_device{}());
    auto employe = sums[dist(gen)];
    return employe.first;
}

int AlgoRecuit::random_animal_per_weight(vector<int> * tasks) {

    int sum = accumulate(tasks->begin(), tasks->end(), 0);
    vector<float> weights;
    for(auto w: *tasks){
        weights.push_back((float)w/(float)sum);
    }

    discrete_distribution<> dist(weights.begin(), weights.end());
    mt19937 gen(random_device{}());
    return dist(gen);
}

