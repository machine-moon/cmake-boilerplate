
#include "boost_example.h"
#include "cgal_example.h"
#include "glad_example.h"
#include "glfw_example.h"
#include "glm_example.h"
#include "imgui_example.h"
#include "jsoncons_example.h"
#include "lz4_example.h"

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>
int main()
{
    // Minimal GLFW + glad context setup for OpenGL info functions
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(640, 480, "TWIZ OpenGL Info", nullptr, nullptr);
    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize glad\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    twiz::show_gl_shading_language_version();
    glfwDestroyWindow(window);
    glfwTerminate();

    twiz::jsoncons_example();
    twiz::lz4_example();
    twiz::run_boost_networking_suite();
    twiz::fun();
    twiz::run_cgal_geometry_suite();
    twiz::show_gl_shading_language_version();
    twiz::run_glfw_windowing_suite();
    twiz::run_glm_math_suite();
    twiz::run_imgui_showcase();
    return 0;
}