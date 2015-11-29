#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <algorithm> // accumulate

using std::vector;
using std::map;
using std::sqrt;
using std::accumulate;

// list of tasks(animal type) per employee
typedef vector<int> employe_task_t;

// map of employe_tasks_t per ecosystem
// employee id has his list of tasks
typedef map<int, employe_task_t> ecosystem_sol_t;

struct Solution {
    // list of ecosystems
    vector<ecosystem_sol_t> ecosystems;
};

double solution_standard_deviation(Solution * sol);

#endif
