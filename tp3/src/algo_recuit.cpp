#include "algo_recuit.h"

// Data structure
using std::map;
using std::vector;
using std::pair;
using std::set;

// IO
using std::cout;
using std::endl;
using std::string;

// Algo
using std::accumulate;
using std::for_each;
using std::advance;
using std::max_element;
using std::min_element;
using std::distance;

// Random
using std::default_random_engine;
using std::uniform_real_distribution;
using std::uniform_int_distribution;
using std::random_device;
using std::mt19937;
using std::discrete_distribution;

// Math
using std::exp;

std::mutex AlgoRecuit::employee_distribution_mutex;
std::set<std::vector<int>> AlgoRecuit::employee_distribution_taboo;

void AlgoRecuit::generate_employee_distribution(std::vector<int>& distribution,
        size_t nb_ecosystem, size_t nb_employee)
{
    bool generate_distribution_p = true;
    size_t n = 0;
    while(generate_distribution_p) {
        // At least one employee per ecosystem.   
        distribution.assign(nb_ecosystem, 1);
        
        for(size_t i = 0; i < nb_employee - nb_ecosystem; ++i) {
            // Choose random ecosystem
            size_t eco = rand() % nb_ecosystem;
            distribution[eco] += 1;
        }

        // Maybe mutex here?
        auto end = employee_distribution_taboo.end();
        auto it = employee_distribution_taboo.find(distribution);
        if(it == end) {
           generate_distribution_p = false; 
           employee_distribution_mutex.lock();
           employee_distribution_taboo.insert(distribution);
           employee_distribution_mutex.unlock();
        }
        if(n > 1000) {
            generate_distribution_p = false;
        }
    }

    // For debugging
    if(false) {
        cout << "Distribution: ";
        for(auto e : distribution) {
            cout << " " << e;
        }
        cout << "\n";
    }
}

AlgoRecuit::AlgoRecuit(ProblemData data_, int steps) {
    data = data_;
    max_steps = steps;
    wip_sol = new Solution();
    current_sol = new Solution();
    best_sol = new Solution();
    new_solution = false;
    uniform_real_distribution<float> float_distribution(0.0, 1.0);
    // TODO make them parametrisable
    temperature = 1.0;
    coeficient_refroidissement = 0.995;
}

void AlgoRecuit::init_solution(bool new_best) {
    
    // Nombre d'employe par ecosysteme.
    vector<int> distribution;
    generate_employee_distribution(distribution, data.ecosystem.size(), data.nb_employee);
    
    wip_sol->ecosystems.resize(0);
    
    size_t i = 0;
    for(auto ecosystem: data.ecosystem){
        auto e = ecosystem_sol_t();
        wip_sol->ecosystems.push_back(e);
        generate_ecosystem_solution(ecosystem, wip_sol, data.nb_employee, distribution[i]);
        ++i;
    }
    
    *current_sol = *wip_sol;
    if(new_best) {
        *best_sol = *current_sol;
    }
}

void AlgoRecuit::init_solution(Solution *sol) {
    *best_sol = *sol;
    *current_sol = *sol;
}

void AlgoRecuit::generate_ecosystem_solution(ecosystem_t ecosystem, Solution * wip,
        int starting_id, int nb_employes) {
    int employe_id = starting_id - 1;
    
    // initialise la map de tache par employe
    ecosystem_sol_t & e = wip->ecosystems[ecosystem.id];
    for(int i = starting_id - nb_employes; i < starting_id; i++) {
        e[i].resize(0);
    }
    
    for(auto animal_weight: ecosystem.eco) {
        e[employe_id].push_back(animal_weight);
        employe_id--;
        if(employe_id < starting_id - nb_employes || employe_id < 0) {
            employe_id = starting_id - 1;
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
        //generate_neighboor_solution_transfer();
        generate_neighboor_solution_proportional_probabilty();
        delta = calculate_delta(current_sol, wip_sol);
        if(metropolis_criteria(delta, temperature)){
            *current_sol = *wip_sol;
            if(calculate_delta(best_sol, current_sol) > 0){
                *best_sol = *current_sol;
                new_solution = true;
            }
        }
        temperature = temperature * coeficient_refroidissement;
    }
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
        // TODO bool upDown pour biaise le random vers une tandance souhaitee
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

float AlgoRecuit::calculate_delta(Solution * sol1, Solution * sol2) {
    float s1 = sol1->get_std_dev();
    float s2 = sol2->get_std_dev();
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
