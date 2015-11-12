#include <iostream>
#include "exemplaire_struct.h"
#include <algorithm>
#include <climits>

int get_best_fit_box(struct exemplaire * e, int item_size);

void vorace(struct exemplaire * e)
{
    std::sort(e->data, e->data + e->nb_element);
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
    unsigned int residual_space = UINT_MAX;
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
