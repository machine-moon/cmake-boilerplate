#include "Examples/jsoncons.h"
#include <iostream>
#include <jsoncons/json.hpp>

void Twiz::JsonconsExample()
{
    jsoncons::json myjson;
    myjson["key"] = "value";
    myjson["number"] = 42;
    std::cout << "[jsoncons example: " << myjson << "]\n";
}