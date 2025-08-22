#include "jsoncons_example.h"
#include <iostream>
#include <jsoncons/json.hpp>

void twiz::jsoncons_example()
{
    jsoncons::json j;
    j["key"] = "value";
    j["number"] = 42;
    std::cout << "[jsoncons example: " << j << "]\n";
}