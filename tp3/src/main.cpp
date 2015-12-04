#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h> // For option parsing.
#include <thread>

#include "data.h"
#include "stats.h"
#include "algo_recuit.h"

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
using std::thread;

// Calcul et affiche quelques statistiques sur toute les données.
void general_stats() {
}
void start_thread(ProblemData data, bool verbose_p);

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
    
    if( filename != "" )
    {
        ProblemData data = make_problem_data(filename);
        int nb_thread = 4;
        std::vector<std::thread> threads;
        
        // For each thread
        for(int i = 0; i < nb_thread; ++i)
        {
            threads.push_back(thread( [&] () 
            {
                AlgoRecuit algo(data, steps);

                // Timeout pour reset la temperature quand ca fait longtemps qu'on a pas trouver de meilleur solution.
                int timeout_temp = 0;
                int timeout_temp_thresh = 20;
                // Timeout quand ca fait plein de fois qu'on reset la temperature, on shuffle les employe de place.
                int timeout_restart = 0;
                int timeout_restart_thresh = 20;
                
                algo.init_solution(true);
                algo.print_solution(algo.best_sol, verbose_p);
                while(true){
                    algo.run_one_loop();
                    
                    // si on a trouver une meilleur solution
                    if(algo.new_solution) {
                        timeout_temp = 0;
                        algo.print_solution(algo.best_sol, verbose_p);
                        algo.new_solution = false;
                    }
                    else
                    {
                        timeout_temp++;
                        if(timeout_temp == timeout_temp_thresh)
                        {
                            timeout_restart++;
                            //cout << algo.temperature << endl;
                            algo.temperature = 20;
                            timeout_temp = 0;
                            if(timeout_restart == timeout_restart_thresh) {
                                cout << "Thread "<< std::this_thread::get_id() << " Restarting" << endl;
                                // Reinitialize l'algo.
                                algo.init_solution(false);
                                algo.print_solution(algo.best_sol, verbose_p);
                                timeout_restart = 0;
                            }
                        }
                    }
                }
            
            }));
        
        
        std::for_each(threads.begin(), threads.end(), [](std::thread &t) 
        {
            t.join();
        });
    }
    }
    else
    {
        cout << "File not found, enter valid filename" << endl;
    }

//    general_stats();

    // Eval data

    // Print solutions
    // Loop!

    return 0;
}
