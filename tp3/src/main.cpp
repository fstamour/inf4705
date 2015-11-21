#include <iostream>
#include <sstream>
#include <string>

#include "data.h"
#include "stats.h"


template<typename T>
std::string to_string(const T& x) {
    std::ostringstream oss;
    oss << x;
    return oss.str();
}


using std::cout;
using std::cerr;
using std::endl;
using std::string;

// Calcul et affiche quelques statistiques sur toute les données.
void general_stats() {
    // Pour analyser les datasets: on les charges tous.
    // (Plus tard, on pourrait ajouter un flag pour faire cette operations)
    Stats<> s_employee, s_ecosystem;
    for(int i = 1; i <= 15; ++i) {
        string filename = "../Biodome/biodome" + to_string(i) + ".dat";
        cout << filename << "\n";
        for(size_t j = 0; j < filename.size(); ++j) { cout << "="; } cout << endl;
        ProblemData data = make_problem_data(filename);
       
        // Accumulation de statistique "global" (sur tous les datasets).
        auto nep = data.nb_employee;
        s_employee.add_data(nep);
        auto nec = data.ecosystem.size();
        s_ecosystem.add_data(nec);

        cout << "Nb employe:   " << nep << endl;

        // Stastistique sur le dataset courant.
        for(size_t j = 0; j < data.ecosystem.size(); ++j) {
            Stats<> s;
            s.add_data(data.ecosystem[j]);
            s.print_summary(cout, "Ecosystem " + to_string(j));
        }
        cout << "\n";
    }
    cout << "=================\n\n";
    s_employee.print_summary(cout, "Employee");
    cout << "\n";
    s_ecosystem.print_summary(cout, "EcosystemS");
}

int main(int argc, char *argv[])
{
    // TODO Parse command-line options
    
    general_stats();
    
    // Eval data
    
    // Print solutions
    // Loop!
    
    return 0;
}

