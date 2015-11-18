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
    test(5, 1, true);
    test(5, 2, true);
    test(5, 3, true);
    test(5, 4, true);
//    test(5, 10, true);
//    test(5, 25, false);
//    test(4, 100, false);

    return 0;
}
