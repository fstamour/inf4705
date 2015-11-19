#ifndef EXEMPLAIRE_STRUCT_H_
#define EXEMPLAIRE_STRUCT_H_

#include <vector>
#include <ctime>

typedef std::vector<unsigned> data_t;

struct exemplaire {
    // Liste des items
    data_t data;
    // Liste des boites
    std::vector<int> space;
    // Solution courante
    std::vector<std::vector<int>> result;
    // Nombre d'element
    int nb_element;
    // Nombre de boite
    int nb_box;
    // Capacite de chaque boite
    int capacity;
    // Le temps ou l'algo a demarrer
    clock_t start_time;
    // Le temps pris pour executer l'algo
    clock_t time;

    virtual ~exemplaire() {}
};

// Charge un exemplaire.
struct exemplaire * make_exemplaire(char * filename);

// Affiche la solution trouve pour un exemplaire.
void print_solution(struct exemplaire * e);

// Optenir la quantite total d'espace occuper
int get_result_volume(struct exemplaire * e);

// Afin de determiner si l'algo roule depuis plus de 5 minutes.
bool is_timeout(struct exemplaire* e);

// Quitte le programme prematurement.
void exit_timeout();

#endif /* EXEMPLAIRE_STRUCT_H_ */
