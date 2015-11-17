#include "exemplaire_struct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>


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
        e->space = new int[e->nb_box];
        for(int i = 0; i < e->nb_box; ++i){
            e->space[i] = e->capacity;
        }
        e->result = new std::vector<int>[e->nb_box];
        //std::cout << "number of element : " << e->nb_element << std::endl;
        //std::cout << "number of boxes : " << e->nb_box << std::endl;
        //std::cout << "capacity : " << e->capacity << std::endl;

        // second line
        getline(file, line);
        pos = 0;
        end = 0;
        index = 0;
        e->data.reserve(e->nb_element);
        while((pos = line.find(" ", end)) != std::string::npos) {
            unsigned poids = std::stoi(line.substr(end, pos));
            e->data[index++] = poids;
            pos++;
            end = pos;
        }

        file.close();
    } else {
        std::cerr << "Failed to open \"" << filename << "\"" << std::endl;
    }
    return e;
}

void free_exemplaire(struct exemplaire * e) {
    delete[] e->space;
    if(e->result != nullptr) {
        delete[] e->result;
    }
    delete e;
}

void print_solution(struct exemplaire * e) {
    for(int i = 0; i < e->nb_box; ++i) {
        std::cout << "boite " << i << ": ";
        for(unsigned int j = 0; j < e->result[i].size(); ++j) {
            std::cout << e->result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int get_result_volume(struct exemplaire * e){
    int sum = 0;
    for(int i = 0; i < e->nb_box; ++i) {
        std::for_each(e->result[i].begin(), e->result[i].end(), [&] (int value) {
                sum += value;
                });
    }
    return sum;
}
