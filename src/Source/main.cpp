
#include "boost_example.h"
#include "cgal_example.h"
#include "glad_example.h"
#include "glfw_example.h"
#include "glm_example.h"
#include "imgui_example.h"
#include "something.h"
#include <iostream>

namespace twiz {
void print_message() {
  std::cout << "Hello from the twiz library!" << std::endl;
}
} // namespace twiz

int main() {
  twiz::print_message();
  twiz_examples::show_glm();
  twiz_examples::show_glad();
  twiz_examples::show_glfw();
  twiz_examples::show_boost();
  twiz_examples::show_imgui();
  twiz_examples::show_cgal();
  return 0;
}