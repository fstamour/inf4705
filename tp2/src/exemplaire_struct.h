#ifndef EXEMPLAIRE_STRUCT_H_
#define EXEMPLAIRE_STRUCT_H_

#include <vector>

struct exemplaire {
    int *data;
    int *space;
    std::vector<int> *result;
    int nb_element;
    int nb_box;
    int capacity;
    clock_t time;
};

struct exemplaire * make_exemplaire(char * filename);
void free_exemplaire(struct exemplaire * e);
void print_solution(struct exemplaire * e);

#endif /* EXEMPLAIRE_STRUCT_H_ */
