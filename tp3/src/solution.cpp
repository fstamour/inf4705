#include <random>

#include "solution.h"

Solution::Solution(const Problem& prob):
    _problem(prob)
{
    auto N = _problem.ecosystem.size();
    _solution.resize(N);
    for(size_t i = 0; i < N; ++i) {
        _solution[i].resize(_problem.ecosystem[i].size(), 0);        
    }
    _employee_per_ecosystem.resize(N, 0);
    _nb_animals_per_employee.resize(N);
    _charge.resize(N);
}

Solution::Solution(const Solution& sol):
    _problem(sol._problem),
    _solution(sol._solution),
    _employee_per_ecosystem(sol._employee_per_ecosystem),
    _nb_animals_per_employee(sol._nb_animals_per_employee),
    _charge(sol._charge)
{}

double Solution::std_deviation() const {
    Stats<> s;
    for(auto c : _charge)
        s.add_data(c);
    return s.get_std_deviation();
}

/* Format demandé:
<écart type>
<nb employés dans écosystème 1>
<nb animaux premier employé écosystème 1> <contrib animal> ... <contrib animal>
...
<nb animaux dernier employé écosystème 1> <contrib animal> ... <contrib animal>
...
<nb employés dans écosystème n>
<nb animaux premier employé écosystème n> <contrib animal> ... <contrib animal>
...
<nb animaux dernier employé écosystème n> <contrib animal> ... <contrib animal>
*/
void Solution::print(std::ostream& out) const {
    out << std_deviation();
    size_t i = 0;
    // Pour chaque écosystème.
    for(; i < _solution.size(); ++i) {
        int nb_employee = _employee_per_ecosystem[i];
        // Affiche le nombre d'employé dans l'écosystème courant.
        out << "\n" << nb_employee;
        const ecosystem_solution_t& eco = _solution[i];
        // Pour chaque employé
        for(int j = 0; j < nb_employee; ++j) {
            out << "\n";
            // On affiche les la charges des animaux qui lui sont assignés.
            out << _nb_animals_per_employee[i][j];
            for(size_t k = 0; k < eco.size(); ++k) {
                int employee_id = eco[k];
                if(employee_id == j) {
                    out << " " << _problem.ecosystem[i][k];
                }
            }
        }
    }
    out << std::endl;
}


void Solution::add_employee(int ecosystem_idx) {
    // TODO Elaborate
    _employee_per_ecosystem[ecosystem_idx] += 1;
    _charge[ecosystem_idx].push_back(0);
    _nb_animals_per_employee[ecosystem_idx].push_back(0);
}

void Solution::remove_employee(int ecosystem_idx) {
    // TODO Elaborate
    _employee_per_ecosystem[ecosystem_idx] -= 1;
    _charge[ecosystem_idx].pop_back();
    _nb_animals_per_employee[ecosystem_idx].pop_back();
    //_solution[ecosystem_idx]
}

void Solution::add_animal(int ecosystem_idx, int employee_id, int animal_idx) {
    // TODO Elaborate
}

void Solution::remove_animal_employee(int ecosystem_idx, int employee_id, int animal_idx) {
    // TODO Elaborate
}

void Solution::assign_random_ecosystem(int ecosystem_idx, std::default_random_engine& generator) {
    // TOOD Mettre a zero _charge[ecosystem_idx] et _nb_animals_per_employee[ecosystem_idx]
    std::uniform_int_distribution<int> random_employee(0, _employee_per_ecosystem[ecosystem_idx] -1);
    auto& eco_sol = _solution[ecosystem_idx];
    auto eco_pro = _problem.ecosystem[ecosystem_idx];
    for(size_t i = 0; i < eco_sol.size(); ++i) {
        int employee = random_employee(generator);
        // Assignation
        eco_sol[i] = employee;
        _charge[ecosystem_idx][employee] += eco_pro[i];
        _nb_animals_per_employee[ecosystem_idx][employee] += 1;
    }
}

void Solution::assign_employee(std::default_random_engine& generator) {
    for(size_t i = 0; i < _problem.ecosystem.size(); ++i) {
        assign_random_ecosystem(i, generator);
    }
}

void Solution::distribute_employee(std::default_random_engine& generator) {
    size_t N = _problem.nb_employee;
    size_t M = _solution.size(); // Nombre d'écosystème.
    size_t i;
    // On assigne au moins un employee par écosystème.
    for(i = 0; i < M && i < N; ++i) {
        add_employee(i);
    }
    // Puis on assigne les autres de manière uniforme.
    std::uniform_int_distribution<int> random_ecosystem(0, _solution.size() -1);
    for(; i < N; ++i) {
        add_employee(random_ecosystem(generator));
    }
}

