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

void mise_en_boite_recuit_simule(exemplaire* e, int max_steps=1000, float initial_temperature=1.0, int palier_refroidissement=10, float coeficient_refroidissement=0.5) {

    std::vector<int> *solution = new std::vector<int>[e->nb_box];
    std::vector<int> *wip_solution = new std::vector<int>[e->nb_box];
    float temperature = initial_temperature;
    int delta = 0;
    unsigned int current_item = 0;

    // TODO handle memory leaks
    for(int i = 0; i < max_steps; ++i) {
        for(int j = 0; j < palier_refroidissement; ++j) {
            generate_random_neighbor(e, solution, wip_solution);
            delta = calculate_delta(solution, wip_solution);
            if(metropolis_criteria(delta, temperature)) {
                // copy wip_solution to solution
                // TODO copy just modified vector instead of all
                *solution = *wip_solution;
                if(get_occupied_volume(wip_solution) > get_result_volume(e)) {
                        // copy solution in e->result
                        e->result = solution;
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
    // ie, generated random int between [0, e->nb_box[
    int box_index = rand()%(e->nb_box);

    // randomize item to place
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(e->data_.begin(), e->data_.end());

    // item selected to insert (value is size of item)
    unsigned int random_item = 0;
    // assigned to true when random_item is inserted
    bool inserted = false;
    // current total of selected box
    unsigned int current_total = 0;
    if(!e->data_.empty()) {
        // select random item in remaining items to place
        random_item = e->data_.back();
        e->data_.pop_back();

        *wip_sol = *sol;
        // loop until random_item is inserted in box
        for(auto item_size: wip_sol[box_index]){
            current_total += item_size;
        }
        while(!inserted) {

            if(current_total + random_item <= e->capacity) {
                // random item fit inside box
                inserted = true;
                wip_sol[box_index].push_back(random_item);
            }
            else{
                // pop random item to insert random_item in box
                // unsigned int random_item_to_pop = rand()%wip_sol->size();
                // wip_sol[box_index][random_item_to_pop];
                std::random_shuffle(wip_sol[box_index].begin(), wip_sol[box_index].end());
                current_total -= wip_sol[box_index].back();
                wip_sol[box_index].pop_back();
            }
        }

    }
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
