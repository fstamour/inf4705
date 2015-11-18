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

struct wip_values {
    unsigned int box_index;
    unsigned int item;
    std::vector<int> item_to_reinsert;
    bool empty = false;
};

struct wip_values generate_random_neighbor(struct exemplaire * e, std::vector<int> *sol, std::vector<int> * wip_sol);
int calculate_delta(std::vector<int> *current_best, std::vector<int> *new_try, int nb_box);
bool metropolis_criteria(int delta, float temperature);
int get_occupied_volume(std::vector<int> *sol, int nb_box);

void mise_en_boite_recuit_simule(exemplaire* e, int max_steps, float initial_temperature, int palier_refroidissement, float coeficient_refroidissement) {

    std::vector<int> *solution = new std::vector<int>[e->nb_box];
    std::vector<int> *wip_solution = new std::vector<int>[e->nb_box];
    float temperature = initial_temperature;
    int delta = 0;
    struct wip_values wip;

    // TODO handle memory leaks
    for(int i = 0; i < max_steps; ++i) {
        for(int j = 0; j < palier_refroidissement; ++j) {
            // need box selected + item selected
            wip = generate_random_neighbor(e, solution, wip_solution);
            if(wip.empty){
                // no more data to process
                // all items are place
                // return
                return;
            }
            delta = calculate_delta(solution, wip_solution, e->nb_box);
            if(metropolis_criteria(delta, temperature)) {
                // copy wip_solution to solution
                solution[wip.box_index] = wip_solution[wip.box_index];
                // reinsert all item poped in generated_random_neighbor process
                for(int i: wip.item_to_reinsert){
                    e->data.push_back(i);
                }
                if(get_occupied_volume(wip_solution, e->nb_box) > get_result_volume(e)) {
                        // copy solution in e->result
                        for(int k = 0; k < e->nb_box; ++k) {
                            e->result[k] = solution[k];
                        }
                }
            }
            else {
                e->data.push_back(wip.item);
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

struct wip_values generate_random_neighbor(struct exemplaire * e, std::vector<int> *sol, std::vector<int> * wip_sol) {
    // select a random box to work with
    // ie, generated random int between [0, e->nb_box[
    struct wip_values wip;
    //wip.box_index = rand()%(e->nb_box);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, e->nb_box-1);
    wip.box_index = dis(gen);
    std::vector<int> item_to_reinsert;

    // randomize item to place
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(e->data.begin(), e->data.end());

    // item selected to insert (value is size of item)
    //unsigned int random_item = 0;
    // assigned to true when random_item is inserted
    bool inserted = false;
    // current total of selected box
    unsigned int current_total = 0;
    if(!e->data.empty()) {
        // select random item in remaining items to place
        wip.item = e->data.back();
        e->data.pop_back();

        //wip_sol[wip.box_index] = sol[wip.box_index];
        for(int i = 0; i < e->nb_box; ++i){
            wip_sol[i] = sol[i];
        }
        // current total
        for(auto item_size: wip_sol[wip.box_index]){
            current_total += item_size;
        }
        // loop until random_item is inserted in box
        while(!inserted) {

            if(current_total + wip.item <= (unsigned int)e->capacity) {
                // random item fit inside box
                inserted = true;
                wip_sol[wip.box_index].push_back(wip.item);
            }
            else{
                // pop random item to insert random_item in box
                // unsigned int random_item_to_pop = rand()%wip_sol->size();
                // wip_sol[box_index][random_item_to_pop];
                std::random_shuffle(wip_sol[wip.box_index].begin(), wip_sol[wip.box_index].end());
                wip.item_to_reinsert.push_back(wip_sol[wip.box_index].back());
                current_total -= wip_sol[wip.box_index].back();
                wip_sol[wip.box_index].pop_back();
            }
        }

    }
    else {
        wip.empty = true;
    }
    return wip;
}

int calculate_delta(std::vector<int> *current_best, std::vector<int> *new_try, int nb_box) {
    return get_occupied_volume(new_try, nb_box) - get_occupied_volume(current_best, nb_box);
}

int get_occupied_volume(std::vector<int> *sol, int nb_box) {
    int sum = 0;
    //for(std::vector<int> vec: *sol){
    for(int i = 0; i < nb_box; i++) {
        for(int size: sol[i]) {
            sum += size;
        }
    }
    return sum;
}

#endif /* end of include guard: ALGO_RECUIT_SIMULE_H */
