#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h> // For option parsing.

#include "problem.h"
#include "solution.h"
#include "stats.h"
//#include "algo_recuit.h"


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

//// Calcul et affiche quelques statistiques sur toute les données.
void general_stats() {
    // Pour analyser les datasets: on les charges tous.
    // (Plus tard, on pourrait ajouter un flag pour faire cette operations)
    Stats<> s_employee, s_ecosystem;
    for(int i = 1; i <= 15; ++i) {
        string filename = "../Biodome/biodome" + to_string(i) + ".dat";
        cout << filename << "\n";
        for(size_t j = 0; j < filename.size(); ++j) { cout << "="; } cout << endl;
        Problem data = make_problem_data(filename);
       
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


////////////////////////////////////
//////////////// WIP ///////////////
////////////////////////////////////
void vorace_wip(Problem& data) {
    data.print(cout);

    data.sort();
    data.compute_stats();

    data.print(cout);

    cout << "N_employee:   " << data.nb_employee << "\n";
    cout << "N_ecosystem:  " << data.ecosystem.size() << "\n";
    Stats<> s;
    for(size_t i = 0; i < data.ecosystem.size(); ++i) {
        s.add_data(data.ecosystem[i]);
    }
    s.print_summary(cout);

    float ee = data.nb_employee/(float)data.ecosystem.size();
    float ce = s.get_sum()/data.nb_employee;
    cout << "\n\n";
    cout << ee << " employee/ecosystem\n";
    cout << ce << " charge/employee\n";
    cout << "================\n\n";
    

    return;


    Stats<> solution_stats;
    size_t employee_i = 0,
           ecosystem_i = 0;
    bool boucle = true;

    cout << "Ecosystem,Animal Employe charge cumulé\n";
    // On itere sur chaque employee
    while(boucle) {
        int charge = 0;
        // Pour chaque animal
        for(size_t i = 0; i < data.ecosystem[ecosystem_i].size(); ++i) {
            animal_contrib_t& a = data.ecosystem[ecosystem_i][i];
            
            
            charge += a;
            a = employee_i;
            if(employee_i != (size_t)data.nb_employee-1) { // On donne tous les animaux qui reste au dernier employe, too bad :P
                cout << ecosystem_i << "," << i << "  " <<  employee_i << "  " << charge << endl;
                if(charge > ce) {
                    solution_stats.add_data(charge);
                    charge = 0;
                    ++employee_i;
                }
            } else {
                // On a passer tous les employe.
                boucle = false;
            }
        }
        // Un employé ne peut pas travailler sur plusieurs ecosysteme.
        ++employee_i;
        ++ecosystem_i;
    }

    solution_stats.print_summary(cout, "Solutions");
    cout << "\n---\n" << endl;
    data.print(cout);
}
////////////////////////////////////
/////////// END  WIP ///////////////
////////////////////////////////////

int main(int argc, char *argv[])
{
    // "Globals"
    string filename;
    bool verbose_p = false;
    // Le nombre d'etape pour le recuit
    int steps = 100;

    // Parse command-line options
    int opt;
    while((opt = getopt(argc, argv, "pf:s:")) != -1) {
        switch(opt) {
            case 'p':
                verbose_p = true;
                break;
            case 'f':
                filename = optarg;
                break;
            case 's':
                steps = std::stoi(optarg);
                break;
            //case '?':
                //cerr << "Unrecognized option"
        }
    }
    // TODO Check if arguments are valid.
    // filename != ""
    
    //general_stats();
    
    // Eval data
    // TODO Generate a first solution from a greedy algorithm.
    
    /*
        AlgoRecuit(string filename, int steps=100);
        AlgoRecuit(Problem data, int steps=100);
        ~AlgoRecuit();
        void init();
        void init_solution();
        void init_solution(Solution *sol);
        void run_one_loop();
        bool is_new_solution();
        void print_solution();
        void print_solution(Solution * sol);
        void generate_ecosystem_solution(size_t eco_id, Solution * wip, int starting_id, int nb_employes);
    */

    Problem data = make_problem_data(filename);
    data.compute_stats();

    int seed = 42;
    std::default_random_engine generator(seed);
    Solution sol(data);
    sol.distribute_employee(generator);
    sol.assign_employee(generator);
    sol.print(cout);

    //AlgoRecuit ar(data, steps);
    //ar.initialize(nullptr);
    //ar.run_one_loop();
    //ar.print_solution();
    
    // Print solutions
    // Loop!
    
    return 0;
}

