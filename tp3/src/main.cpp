#include <iostream>
#include <sstream>
#include <string>

#include "data.h"
#include "stats.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
    // TODO Parse command-line options
    
    // Pour analyser les datasets: on les charges tous.
    // (Plus tard, on pourrait ajouter un flag pour faire cette operations)
    Stats<> s_employee, s_ecosystem;
    for(int i = 1; i <= 15; ++i) {
        std::ostringstream oss;
        oss << "../Biodome/biodome" << i << ".dat";
        ProblemData data = make_problem_data(oss.str());
        //data.print(cout);
        auto nep = data.nb_employee;
        s_employee.add_data(nep);
        auto nec = data.ecosystem.size();
        s_ecosystem.add_data(nec);
    }
    s_employee.print_summary(cout, "Employee");
    cout << "\n";
    s_ecosystem.print_summary(cout, "Ecosystem");
    
    // Eval data
    
    // Print solutions
    // Loop!
    
    return 0;
}

