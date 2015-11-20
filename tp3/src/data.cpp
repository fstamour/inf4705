#include <fstream>

#include "data.h"

using std::string;

ProblemData make_problem_data(const string& filename) {
    ProblemData data;

    // Ouvre le fichier
    std::ifstream in(filename);

    // Lit le nombre d'écosystemes.
    int nb_ecosystem = -1;
    in >> nb_ecosystem;
    data.ecosystem.resize(nb_ecosystem);
    
    // Lit le nombre d'employés.
    in >> data.nb_employee;

    // Pour chaque écosystemes.
    for(int i = 0; i < nb_ecosystem; ++i) {
        // Lit le nombre d'animaux.
        int nb_animals = -1;
        in >> nb_animals;
        data.ecosystem[i].resize(nb_animals, -1);

        // Pour chaque animaux.
        for(int j = 0; j < nb_animals; ++j) {
            in >> data.ecosystem[i][j];
        }
    }

    return data;
}

