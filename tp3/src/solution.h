#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <algorithm> // accumulate

#include "problem.h"

class Solution {
protected:
    // Pointeur vers le problème
    const Problem& _problem;

    //// La solution courante
    // L'assignation de chaque employee
    std::vector<ecosystem_solution_t> _solution;

    // Le nombre d'employe pour chacun des écosystemes.
    std::vector<int> _employee_per_ecosystem;

    // Le nombre d'animaux assigné à chacun des employé dans chacun des écosystèmes.
    std::vector<std::vector<int>> _nb_animals_per_employee;

    // La charge de travail de chaque employé dans chacun des écosystème.
    std::vector<std::vector<int>> _charge;

public:

    Solution(const Problem& prob);
    Solution(const Solution& sol);
    virtual ~Solution() {};

    //// Ces méthodes servirait à générer une solution voisine (pour un recuit par exemple).
    //// Elles sont protected car elles feraient partie d'une méthode "shuffle_employee" ou qqch comme ça.

    /// Ces deux méthodes permetterait de swap deux employé.
    void add_employee(int ecosystem_idx);
    void remove_employee(int ecosystem_idx);

    /// Ces deux méthodes permetterait de swap deux animaux entre deux employé d'un même écosystème.
    void add_animal(int ecosystem_idx, int employee_id, int animal_idx);
    void remove_animal_employee(int ecosystem_idx, int employee_id, int animal_idx);


    // Méthode pour afficher les données de la solution dans un flux.
    void print(std::ostream& out) const;

    // TODO get_employee_charge  (Donne la charge total d'un employe en particulier)
    // TODO get_std_deviation  (Donne l'écart-type des charges des employés
    //  (i.e. Donne la qualité de la solution))
    //
    // TODO swap_employees(emp1, emp2)
    // TODO swap_animals(ecosystem, emp1, emp2)

    double std_deviation() const;

    // Assigne un employé à chaque animal d'un écosysteme de manière aléatoire
    void assign_random_ecosystem(int ecosystem_idx, std::default_random_engine& generator);
    // Assigne un employé à chaque animal de tous les écosystemes de manière aléatoire
    void assign_employee(std::default_random_engine& generator);
    
    // Associe un employé à un écosysteme de manière aléatoire
    void distribute_employee(std::default_random_engine& generator);
};


#endif
