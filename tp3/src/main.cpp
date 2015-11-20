#include <iostream>
#include <string>

#include "data.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
    string filename = "../Biodome/biodome1.dat";
    // Parse command-line options
    

    // Read data
    
    ProblemData data = make_problem_data(filename);
    data.print(cout);
    
    // Eval data
    
    // Print solutions
    // Loop!
    
    return 0;
}

