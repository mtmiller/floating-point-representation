#include <iostream>
#include "floating_point_representation.hpp"
#include "floating_point_representation_io.hpp"

int main(int argc, char* argv[]) {
    using namespace std;

    int value = 0;
    if (argc > 1) {
        value = atoi(argv[1]);
    }

    floating_point_representation fbits;
    cout << fbits << endl;
    fbits = float(value);
    cout << fbits << endl;
    fbits = double(value);
    cout << fbits << endl;
    fbits = (long double)(value);
    cout << fbits << endl;
}
