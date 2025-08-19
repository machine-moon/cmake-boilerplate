
#include "CGAL/Simple_cartesian.h"
#include <iostream>

namespace twiz_examples {
void show_cgal() {
    typedef CGAL::Simple_cartesian<double> Kernel;
    Kernel::Point_2 p(1, 2);
    std::cout << "CGAL Point: " << p << std::endl;
}
}
