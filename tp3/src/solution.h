#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <algorithm> // accumulate
#include <iostream>

// list of tasks(animal type) per employee
typedef std::vector<int> employe_task_t;

// map of employe_tasks_t per ecosystem
// employee id has his list of tasks
// TODO replace map with vector 
typedef std::map<int, employe_task_t> ecosystem_sol_t;

struct Solution {
    
    Solution(){}

    // Copy ctor
    Solution(const Solution& sol);

    // list of ecosystems
    std::vector<ecosystem_sol_t> ecosystems;

    double std_deviation = -1;

    double get_std_dev();

    void print(bool verbose_p, std::ostream& out = std::cout);
};

#endif
