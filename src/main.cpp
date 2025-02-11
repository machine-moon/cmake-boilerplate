#include "iostream"

using namespace std;

class Blah {
    // Define the Blah class members here
};

template <class ANYTYPE>
void thing(int a, Blah other_thing, double c = 10, ANYTYPE f) {
    return;
}

int testFunction(double a, double b) {
    std::cout << "testing";
    return 0;
}

int main(int arg_num, char** vargs) {
    double c = 2.0;  // Declare 'c' with an initial value
    if (1 & 0) cout << "this is the and operator\n";
    if (true & (c > 1)) cout << "this is the and operator\n";
    if ((true) & (c > 1)) cout << "this is still the and operator\n";

    if (true | (c > 1)) cout << "this is the or operator\n";

    return 0;
}