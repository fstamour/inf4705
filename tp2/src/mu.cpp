
#include <iostream>
#include <vector>
#include <stdexcept>

using std::vector;
using std::cout;

void print(const vector<int>& vi, std::ostream& out) {
    for(auto i : vi) {
        out << i << " ";
    }
    out << std::endl;
}


struct Combinatoric_generator {
    // Parameters
    int n, m;

    // For debugging
    int level;

    // States
    int i;
    vector<int> it;
    Combinatoric_generator *subgen = nullptr;

    // Ctor
    Combinatoric_generator(int m, int n, int level = 0):
        m(m), n(n), i(0), level(level)
    {
        it.resize(n, 0);
        it[0] = m;
        if(n>2) {
            subgen = new Combinatoric_generator(m, n-1, level+1);
        }
    }

    // Dtor
    ~Combinatoric_generator() {
        delete subgen;
    }

    void reinitialize(int m) {
        // cout << "Reinit(" << level << ") " << m << std::endl;
        this->m = m;
        std::fill(it.begin(), it.end(), 0);
        i = 0;
        it[0] = m;
        if(subgen) {
            subgen->reinitialize(m);
        }
    }
    
    bool next() {
        switch(n) {
            case 1:
                --it[0];
                return it[0] > 0;
            case 2:
                --it[0];
                ++it[1];
                return it[0] > 0;
            default:
                if(!subgen->next()) {
                    ++i;
                    // cout << "not next(" << level << ") " << i << std::endl;
                    subgen->reinitialize(m-i);
                }
                auto g = subgen->it;
                std::copy(g.begin(), g.end(), it.begin());
                it[it.size()-1] = i;
                return i <= m;
        }
    }

    const vector<int>& get() { return it; }
};

int main(int argc, char *argv[])
{
    int m = 5;
    int n = 100;
    Combinatoric_generator gen(m, n);

    int count = 1;
    // print(gen.get(), cout);
    while(gen.next()) {
        // print(gen.get(), cout);   
        count++;
    }

    cout << "Count: " << count << std::endl;

    return 0;
}
