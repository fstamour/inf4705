#include <iostream>
#include <unistd.h>

#include "option_parse.h"

void Options::initialize(Algo algo, int argc, char** argv) {
    switch(algo) {
        case Algo::dynamique:
        case Algo::vorace:
            {
            int opt;
            while((opt = getopt(argc, argv, "pf:")) != -1) {
                switch(opt) {
                    case 'p':
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
            break;
        case Algo::recuit_simule:
            initialize_recuit(argc, argv);
            break;
    }
}


Options::~Options() {
    delete exemplaire;
}

void Options::initialize_recuit(int argc, char ** argv){
    int opt;
    k_max = 1000;
    t = 1.0;
    p = 100;
    a = 0.9;

    while((opt = getopt(argc, argv, "k:t:l:a:pf:")) != -1) {
        switch(opt) {
            case 'p':
                verbose_p = true;
                break;
            case 'f':
                filename = optarg;
                break;
            case 'k':
                k_max = std::stoi(optarg);
                break;
            case 't':
                t = std::stof(optarg);
                break;
            case 'l':
                p = std::stoi(optarg);
                break;
            case 'a':
                a = std::stof(optarg);
                break;

        }
    }

    // TODO assert for given value
    if(filename == nullptr) {
        std::cerr
            << "Usage: \n"
            << " -k <int>        nombre de pas maximums, valeur par default 1000\n"
            << " -t <float>      temperature initial, valeur par defaut 1.0\n"
            << " -l <int>        palier de refroidissement, valeur par default 100\n"
            << " -a <float>      coeficient de refroidissement, valeur par default 0.9\n"
            << " -p              Affiche les resultats\n"
            << " -f <filename>   Examplaire"
            << std::endl;

        exit(1);
    }
}

