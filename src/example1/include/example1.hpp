
#ifndef EXAMPLE1_HPP
#define EXAMPLE1_HPP

#include <string>

class Greeter {
   public:
    Greeter(const std::string& name);
    void greet() const;

   private:
    std::string name;
};

#endif  // EXAMPLE1_HPP