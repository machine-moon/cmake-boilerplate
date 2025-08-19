#include <GLFW/glfw3.h>
#include <stdio.h>

namespace twiz_examples {
void show_glfw() {
    if (!glfwInit()) {
        printf("GLFW init failed\n");
        return;
    }
    printf("GLFW init success\n");
    glfwTerminate();
}

void create_window() {
    if (!glfwInit()) {
        printf("GLFW init failed\n");
        return;
    }
    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Window", nullptr, nullptr);
    if (!window) {
        printf("Window creation failed\n");
        glfwTerminate();
        return;
    }
    printf("Window created\n");
    glfwDestroyWindow(window);
    glfwTerminate();
}

void poll_events_example() {
    if (!glfwInit()) {
        printf("GLFW init failed\n");
        return;
    }
    GLFWwindow* window = glfwCreateWindow(320, 240, "Poll Events", nullptr, nullptr);
    if (!window) {
        printf("Window creation failed\n");
        glfwTerminate();
        return;
    }
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
}
