#include <iostream>
#include <unistd.h>

#include "option_parse.h"

void Options::initialize(int argc, char** argv) {
    int opt;

    while((opt = getopt(argc, argv, "vf:")) != -1) {
        switch(opt) {
            case 'v':
                verbose_p = true;
                break;
            case 'f':
                filename = optarg;
                break;
        }
    }

    if(filename == nullptr) {
        std::cerr
            << "Usage: \n"
            << " -p              Affiche les resultats\n"
            << " -f <filename>   Examplaire"
            << std::endl;

        exit(1);
    }

}


Options::~Options() {

}

struct recuit_simule_args RecuitOptions::initialize(int argc, char ** argv){
    struct recuit_simule_args recuit_args;
    int opt;
    recuit_args.k_max = 1000;
    recuit_args.t = 1.0;
    recuit_args.p = 100;
    recuit_args.a = 0.9;

    while((opt = getopt(argc, argv, "k:t:p:a:vf:")) != -1) {
        switch(opt) {
            case 'v':
                verbose_p = true;
                break;
            case 'f':
                filename = optarg;
                break;
            case 'k':
                recuit_args.k_max = std::stoi(optarg);
                break;
            case 't':
                recuit_args.t = std::stof(optarg);
                break;
            case 'p':
                recuit_args.p = std::stoi(optarg);
                break;
            case 'a':
                recuit_args.a = std::stof(optarg);
                break;

        }
    }

    // TODO assert for given value
    if(filename == nullptr) {
        std::cerr
            << "Usage: \n"
            << " -k <int>        nombre de pas maximums, valeur par default 1000\n"
            << " -t <float>      temperature initial, valeur par defaut 1.0\n"
            << " -p <int>        palier de refroidissement, valeur par default 100\n"
            << " -a <float>      coeficient de refroidissement, valeur par default 0.9\n"
            << " -v              Verbose\n"
            << " -f <filename>   Examplaire"
            << std::endl;

        exit(1);
    }

    return recuit_args;
}
