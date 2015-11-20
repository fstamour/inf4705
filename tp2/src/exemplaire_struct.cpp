#include "exemplaire_struct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stdexcept>

using std::cout;
using std::cerr;
using std::endl;

struct exemplaire * make_exemplaire(char * filename)
{
    struct exemplaire * e = new exemplaire;
    std::string line;
    std::ifstream file (filename);
    unsigned long pos = 0;
    unsigned long end = 0;
    unsigned index = 0;
    if(file.is_open())
    {
        // first line
        getline(file, line);
        pos = line.find(" ", end);
        e->nb_element = std::stoi(line.substr(end, pos));
        pos++;
        end = pos;
        pos = line.find(" ", end);
        e->nb_box = std::stoi(line.substr(end, pos));
        pos++;
        e->capacity = std::stoi(line.substr(pos, line.size()));
        e->space.resize(e->nb_box, e->capacity);
        /*e->space = new int[e->nb_box];
        for(int i = 0; i < e->nb_box; ++i){
            e->space[i] = e->capacity;
        }*/
        //e->result = new std::vector<std::vector<int>>[e->nb_box];
        e->result.resize(e->nb_box);
        //std::cout << "number of element : " << e->nb_element << std::endl;
        //std::cout << "number of boxes : " << e->nb_box << std::endl;
        //std::cout << "capacity : " << e->capacity << std::endl;

        // second line
        getline(file, line);
        pos = 0;
        end = 0;
        index = 0;
        e->data.resize(e->nb_element);
        while((pos = line.find(" ", end)) != std::string::npos) {
            // cout << index << endl;
            unsigned volume = std::stoi(line.substr(end, pos));
            e->data[index] = volume;
            ++index;
            ++pos;
            end = pos;
        }

        file.close();
    } else {
        std::cerr << "Failed to open \"" << filename << "\"" << std::endl;
    }
    return e;
}

void print_solution(struct exemplaire * e) {
    if(e == nullptr) {
        cerr << "[print_solution] Null exemplaire" << endl;
        return;
    }
    if(e->result.size() == 0) {
        cerr << "[print_solution] Empty solution" << endl;
        return;
    }
    for(int i = 0; i < e->nb_box; ++i) {
        std::cout << "boite " << i << "\t";
        for(unsigned int j = 0; j < e->result[i].size(); ++j) {
            std::cout << e->result[i][j] << " ";
        }
        std::cout << "\t";
        
    }
    std::cout << std::endl;
}

int get_result_volume(struct exemplaire * e){
    int sum = 0;
    if(e == nullptr) {
        cerr << "[get_result_volume] Null exemplaire" << endl;
        return -1;
    }
    if(e->result.size() == 0) {
        cerr << "[get_result_volume] Empty solution" << endl;
        return -1;
    }
    //for(int i = 0; i < e->nb_box; ++i) {
    for(auto box : e->result) {
        std::for_each(box.begin(), box.end(), [&] (int value) { sum += value; });
    }
    return sum;
}


bool is_timeout(struct exemplaire* e) {
    return float(clock() - e->start_time)/CLOCKS_PER_SEC > 5*60.0;
}

void exit_timeout() {
    //std::runtime_error("Timeout");
    cerr << "Timeout\n" << endl;
    exit(2);
}



