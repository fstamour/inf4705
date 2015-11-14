#ifndef ALGO_RECUIT_SIMULE_H
#define ALGO_RECUIT_SIMULE_H

#include <iostream>
#include "exemplaire_struct.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <random>
#include <ctime>
#include <cstdlib>

unsigned int generate_random_neighbor(struct exemplaire * e, std::vector<int> *sol, std::vector<int> * wip_sol);
int calculate_delta(std::vector<int> *current_best, std::vector<int> *new_try);
bool metropolis_criteria(int delta, float temperature);
int get_occupied_volume(std::vector<int> *sol);

void mise_en_boite_recuit_simule(exemplaire* e, int max_steps=1000, float initial_temperature=1.0, int palier_refroidissement=1, float coeficient_refroidissement=0.5) {

    std::vector<int> *solution = new std::vector<int>[e->nb_box];
    std::vector<int> *wip_solution = new std::vector<int>[e->nb_box];
    float temperature = initial_temperature;
    int delta = 0;
    unsigned int current_item = 0;


    for(int i = 0; i < max_steps; ++i) {
        for(int j = 0; i < palier_refroidissement; ++j) {
            generate_random_neighbor(e, solution, wip_solution);
            delta = calculate_delta(solution, wip_solution);
            if(metropolis_criteria(delta, temperature)) {
                //copy wip_solution to solution
                if(get_occupied_volume(wip_solution) > get_result_volume(e)) {
                        // copy solution in e->result
                }
            }
        }
        temperature = temperature * coeficient_refroidissement;
    }
}

bool metropolis_criteria(int delta, float temperature) {

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    if(delta > 0) {
        return true;
    }
    if(exp((float)delta/temperature) >= distribution(generator)) {
        return true;
    }

    return false;
}

unsigned int generate_random_neighbor(struct exemplaire * e, std::vector<int> *sol, std::vector<int> * wip_sol) {
    // select a random box to work with
    // ie, generated random int between [0, e->nb_box]
    int box_index = rand()%(e->nb_box-1) + 1;

    // select random item in remaining items to place

    unsigned int random_item = 0;
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(e->data_.begin(), e->data_.end());
    if(!e->data_.empty()) {
        random_item = e->data_.back();
        e->data_.pop_back();
    }

    // TODO try to insert random_item in e->space[box_index]
    // if it's overflow, pop an item from e->space[box_idex]
    // TODO need to chace e->space for a vector
    // until random_item can be iserted
    // make current state coherent and return

    return random_item;
}

int calculate_delta(std::vector<int> *current_best, std::vector<int> *new_try) {
    // TODO is this good?
    return get_occupied_volume(current_best) - get_occupied_volume(new_try);
}

int get_occupied_volume(std::vector<int> *sol) {
    int sum = 0;
    for(int i: *sol){
        sum += i;
    }
    return sum;
}
#endif /* end of include guard: ALGO_RECUIT_SIMULE_H */
