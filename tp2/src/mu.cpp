/**
 * Test the "combinatoric generator"
 */

#include <iostream>
#include <vector>
#include <stdexcept>

#include "utils.h"

using std::vector;
using std::cout;
using std::endl;

void test(int m, int n, bool verbose) {
    Combinatoric_generator gen(m, n);

    int count = 1;
    if(verbose) print(gen.get(), cout);
    while(gen.next(count % 10000 == 0)) {
        if(verbose) print(gen.get(), cout);   
        count++;
    }

    cout << "Count: " << count << std::endl;
    cout << std::endl;
}

int main(int argc, char *argv[])
{
    for(int i = 1; i < 5; ++i) {
        test(5, i, true);
    }
//    test(5, 10, true);
//    test(5, 25, false);
//    test(4, 100, false);
//    test(100, 101, false);   

    return 0;
}
