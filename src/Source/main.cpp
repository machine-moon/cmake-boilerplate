
#include "boost_example.h"
#include "cgal_example.h"
#include "glad_example.h"
#include "glfw_example.h"
#include "glm_example.h"
#include "imgui_example.h"

int main()
{
    twiz::run_boost_networking_suite();
    twiz::fun();
    twiz::run_cgal_geometry_suite();
    twiz::show_gl_shading_language_version();
    twiz::run_glfw_windowing_suite();
    twiz::run_glm_math_suite();
    twiz::run_imgui_showcase();
    return 0;
}