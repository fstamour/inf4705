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
        e.reserve(nb_animals);

        // Pour chaque animaux.
        for(int j = 0; j < nb_animals; ++j) {
            // On lit l'animal
            animal_contrib_t animal;
            in >> animal;
            // On le merge-insert afin d'avoir la liste d'animal en ordre croissant.
            ecosystem_t::iterator it = std::find_if(e.begin(), e.end(),
                 [&animal] (const animal_contrib_t& a) { return a > animal; });
            e.insert(it, animal);
        }
    }

    return data;
}


void ProblemData::print(std::ostream& out) const {
    out << ecosystem.size() << " " << nb_employee << "\n";
    // Pour chaque ecosysteme.
    for(const ecosystem_t& e : ecosystem) {
        out << e.size();
        // Pour chaque animal.
        for(const animal_contrib_t& a : e) {
            out << " " << a;
        }
        out << std::endl;
    }
}

