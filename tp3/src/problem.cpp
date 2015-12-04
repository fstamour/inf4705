#include <iostream>
#include <fstream>
#include <algorithm>

#include "problem.h"

using std::string;

Problem make_problem_data(const string& filename) {
    Problem data;

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
        e.resize(nb_animals, -1);
        data.stats.resize(nb_animals);

        // Pour chaque animaux.
        for(int j = 0; j < nb_animals; ++j) {
            // On lit l'animal
            in >> e[j];
        }
    }

    return data;
}


void Problem::print(std::ostream& out) const {
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


void Problem::compute_stats() {
    for(size_t i = 0; i < ecosystem.size(); ++i) {
        stats[i].add_data(ecosystem[i]);
    }
}


void Problem::sort() {
    for(auto& e : ecosystem) {
        std::sort(e.begin(), e.end());
    }
}


