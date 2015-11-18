#include <iostream>

#include "utils.h"

using std::vector;
using std::cout;
using std::endl;

void print(const vector<int>& vi, std::ostream& out, bool newline) {
    for(auto i : vi) {
        out << i << " ";
    }
    out << endl;
}

Combinatoric_generator::Combinatoric_generator(int m, int n, int level):
    n(n), level(level)
{
    if(n>1) {
        subgen = new Combinatoric_generator(m, n-1, level+1);
    }
    reinitialize(m);
}

// Dtor
Combinatoric_generator::~Combinatoric_generator() {
    delete subgen;
}

// Init
void Combinatoric_generator::reinitialize(int _m) {
    // cout << "Reinit(" << level << ") " << m << endl;
    if( _m >= 0 ) {
        m = _m;
    }
    i = m;
    if(subgen) {
        subgen->reinitialize(m-i);
    }
}

// Compute next state, return true if the next state is valid.
// (Returns false when there is no more thing to generate.)
bool Combinatoric_generator::next(bool verbose) {
    if(verbose) {
        cout << "." << std::flush;
    }
    if(n == 1) {
        return false;
    }
    if(!subgen->next()) {
        --i;
        subgen->reinitialize(m-i);
    }
    return i >= 0;
}

void Combinatoric_generator::get_in_place(vector<int>& ret) { 
    ret[level] = i;
    if(subgen) {
        subgen->get_in_place(ret);
    }
}

vector<int> Combinatoric_generator::get() { 
    vector<int> v(n);
    get_in_place(v);
    return v;
}
