#include <iostream>
#include <unistd.h>

#include "option_parse.h"

void Options::initialize(int argc, char** argv) {
    int opt;

    while((opt = getopt(argc, argv, "v:f:")) != -1) {
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
            << " -v              Verbose\n"
            << " -f <filename>   Examplaire"
            << std::endl;
    
        exit(1);
    }

    if(verbose_p){
        std::cout << "verbose_p: " << verbose_p << std::endl;
        std::cout << "filename:  " << filename << std::endl;
    }
}


Options::~Options() {

}

