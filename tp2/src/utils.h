#ifndef UTILS_H_YBQGYRVA
#define UTILS_H_YBQGYRVA

#include <ostream>
#include <vector>

void print(const std::vector<int>& vi, std::ostream& out, bool newline = true);

template<typename T>
T factorial(T n, T result = 1) {
    if (n == 1)
        return result;
    else
        return factorial(n - 1, n * result);
}

class Combinatoric_generator {
private:
    // Size
    int n;
    // Max
    int m;
    // Nesting level.
    int level;

    // States
    int i;
    Combinatoric_generator *subgen = nullptr;

public:
    // Ctor
    Combinatoric_generator(int m, int n, int level = 0);
    

    // Dtor
    ~Combinatoric_generator();

    // Init
    void reinitialize(int m = -1);
    
    // Compute next state, return true if the next state is valid.
    // (Returns false when there is no more thing to generate.)
    bool next(bool verbose = false);

    void get_in_place(std::vector<int>& ret);
    
    std::vector<int> get();
};

#endif /* end of include guard: UTILS_H_YBQGYRVA */
