#include <iostream>
#include <algorithm>
#include <climits>

#include "exemplaire_struct.h"
#include "option_parse.h"

int get_best_fit_box(struct exemplaire * e, int item_size);

void mise_en_boite_vorace(Options& options)
{
    struct exemplaire * e = options.get_exemplaire();
    std::sort(e->data.begin(), e->data.end());
    int index = -1;
    for(int i = e->nb_element - 1; i >= 0; --i){
        //std ::cout << e->data[i] << " ";
        index = get_best_fit_box(e, e->data[i]);
        if(index == -1) continue;
        e->result[index].push_back(e->data[i]);
        e->space[index] -= e->data[i];
    }
}

int get_best_fit_box(struct exemplaire * e, int item_size)
{
    unsigned residual_space = UINT_MAX;
    int diff;
    int index = -1;
    for(int i = 0; i < e->nb_box; ++i){
        diff = e->space[i] - item_size;
        if(diff > 0 && (unsigned)diff < residual_space){
            residual_space = diff;
            index = i;
        }
    }
    return index;
}
