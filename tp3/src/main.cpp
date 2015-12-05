#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h> // For option parsing.
#include <thread>
#include <mutex>

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

void print_usage() {
    cout << "Usage: horaire -f FILENAME [OPTIONS]\n"
            "  -p\tMode verbeux, afficher les solutions complete.\n"
            "  -s steps\tNombre de boucle que le recuit simule roule avant d'afficher une nouvelle solutions.\n"
            "  -h\tAffiche cette aide.\n"
            << std::flush;
}


int main(int argc, char *argv[])
{
    // "Globals"
    string filename;
    bool verbose_p = false;
    bool help_p = false;
    // Le nombre d'etape pour le recuit
    int steps = 100;
    
    // Parse command-line options
    int opt;
    while((opt = getopt(argc, argv, "hpf:s:")) != -1) {
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
            case 'h':
                help_p = true;
                break;
            case '?':
                exit(1);
        }
    }
    
    // Handle -h flag
    if(help_p) {
        print_usage();
        exit(0);
    }
    
    // Validate arguments
    if( filename == "" ) {
        print_usage();
        exit(1);
    }

    ProblemData data = make_problem_data(filename);
    
    Solution current_best;
    int current_best_std_dev = std::numeric_limits<int>::max();


    int nb_thread = 4;
    std::vector<std::thread> threads;
    
    // For each thread
    for(int i = 0; i < nb_thread; ++i) {
        // Create thread
        threads.push_back(thread( [&] () {
            AlgoRecuit algo(data, steps);

            // Timeout pour reset la temperature quand ca fait longtemps qu'on a pas trouver de meilleur solution.
            int timeout_temp = 0;
            int timeout_temp_thresh = 20;
            // Timeout quand ca fait plein de fois qu'on reset la temperature, on shuffle les employe de place.
            int timeout_restart = 0;
            int timeout_restart_thresh = 20;
            
            algo.init_solution(true);
            algo.best_sol->print(verbose_p);
            for(size_t j = 0; j < 100; ++j) {
                algo.run_one_loop();
                
                // si on a trouver une meilleur solution
                if(algo.new_solution) {
                    timeout_temp = 0;
                    algo.best_sol->print(verbose_p);
                    algo.new_solution = false;
                } else {
                    timeout_temp++;
                    if(timeout_temp == timeout_temp_thresh) {
                        timeout_restart++;
                        //cout << algo.temperature << endl;
                        algo.temperature = 20;
                        timeout_temp = 0;
                        if(timeout_restart == timeout_restart_thresh) {
                            //cout << "Thread "<< std::hex << std::this_thread::get_id() << " Restarting" << endl;
                            // Reinitialize l'algo.
                            algo.init_solution(false);
                            timeout_restart = 0;
                        }
                    }
                }
            }
        
        }));
    } // For each thread
    
    // Join all threads (Should never get here
    for(auto& t : threads) { t.join(); }

    return 0;
}
