#include <iostream>

#include "include/example1.hpp"

Greeter::Greeter(const std::string& name) : name(name) {}

void Greeter::greet() const {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {
    Greeter greeter("world");
    greeter.greet();
    return 0;
}