#include <iostream>
#include <fstream>
#include <algorithm>

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

        // Alias pour l'écosystemes courant.
        ecosystem_t& e = data.ecosystem[i];
        e.eco.reserve(nb_animals);
        e.id = i;

        // Pour chaque animaux.
        for(int j = 0; j < nb_animals; ++j) {
            // On lit l'animal
            animal_contrib_t animal;
            in >> animal;
            // On le merge-insert afin d'avoir la liste d'animal en ordre croissant.
            auto it = std::find_if(e.eco.begin(), e.eco.end(),
                 [&animal] (const animal_contrib_t& a) { return a > animal; });
            e.eco.insert(it, animal);
        }
    }

    return data;
}


void ProblemData::print(std::ostream& out) const {
    out << ecosystem.size() << " " << nb_employee << "\n";
    // Pour chaque ecosysteme.
    for(const ecosystem_t& e : ecosystem) {
        out << e.eco.size();
        // Pour chaque animal.
        for(const animal_contrib_t& a : e.eco) {
            out << " " << a;
        }
        out << std::endl;
    }
}

