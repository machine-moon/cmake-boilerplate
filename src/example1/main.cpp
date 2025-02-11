#include <expected>
#include <iostream>
#include <tuple>

#include "include/example1.hpp"

using namespace std;

template <typename T>

class check_type;

int main() {
    int a = 0;
    auto t = make_tuple<int, int>(2, 3);

    cout << get<0>(t) << get<1>(t) << endl;
    cout << "stop, World!" << endl;
    return a;
}