#include "glfw_example.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <vector>

namespace twiz
{

static void error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (action == GLFW_PRESS)
    {
        std::cout << "Key pressed: " << key << std::endl;
    }
}

static void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
    std::cout << "Window resized to: " << width << "x" << height << std::endl;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        std::cout << "Mouse dragging at: " << xpos << ", " << ypos << std::endl;
    }
}

void show_glfw()
{
    std::cout << "\n=== GLFW WINDOWING SHOWCASE ===" << std::endl;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    std::cout << "GLFW Version: " << major << "." << minor << "." << rev << std::endl;

    const char* version = glfwGetVersionString();
    std::cout << "GLFW Version String: " << version << std::endl;

    glfwTerminate();
}

void create_basic_window()
{
    std::cout << "\n--- Basic Window Creation ---" << std::endl;

    if (!glfwInit())
        return;

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(800, 600, "TWIZ - Basic GLFW Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    std::cout << "Window created successfully! Press ESC to close." << std::endl;

    // Simple color cycling
    float time = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        time += 0.016f; // ~60 FPS

        float r = (sin(time) + 1.0f) / 2.0f;
        float g = (sin(time + 2.0f) + 1.0f) / 2.0f;
        float b = (sin(time + 4.0f) + 1.0f) / 2.0f;

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void create_resizable_window_with_callbacks()
{
    std::cout << "\n--- Resizable Window with Callbacks ---" << std::endl;

    if (!glfwInit())
        return;

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(1024, 768, "TWIZ - Interactive Window", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    std::cout << "Interactive window created!" << std::endl;
    std::cout << "- Press keys to see input" << std::endl;
    std::cout << "- Resize window to see callback" << std::endl;
    std::cout << "- Click and drag to see mouse input" << std::endl;
    std::cout << "- Press ESC to exit" << std::endl;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        double time = glfwGetTime();

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.5f, 0.2f);
        glVertex2f(-0.5f + sin(time) * 0.2f, -0.5f);
        glVertex2f(0.5f + sin(time) * 0.2f, -0.5f);
        glVertex2f(0.5f + sin(time) * 0.2f, 0.5f);
        glVertex2f(-0.5f + sin(time) * 0.2f, 0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void opengl_triangle_demo()
{
    std::cout << "\n--- OpenGL Triangle Demo ---" << std::endl;

    if (!glfwInit())
        return;

    GLFWwindow* window = glfwCreateWindow(800, 600, "TWIZ - OpenGL Triangle", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    std::cout << "Animated triangle rendering! Press ESC to exit." << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        float time = static_cast<float>(glfwGetTime());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glRotatef(time * 50.0f, 0.0f, 0.0f, 1.0f);
        float scale = 0.5f + 0.3f * sin(time);
        glScalef(scale, scale, 1.0f);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.5f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void multiple_windows_demo()
{
    std::cout << "\n--- Multiple Windows Demo ---" << std::endl;

    if (!glfwInit())
        return;

    std::vector<GLFWwindow*> windows;
    const char* titles[] = {"Window 1 - Red", "Window 2 - Green", "Window 3 - Blue"};
    float colors[][3] = {{1.0f, 0.2f, 0.2f}, {0.2f, 1.0f, 0.2f}, {0.2f, 0.2f, 1.0f}};

    for (int i = 0; i < 3; ++i)
    {
        GLFWwindow* window = glfwCreateWindow(400, 300, titles[i], nullptr, nullptr);
        if (window)
        {
            glfwSetWindowPos(window, 100 + i * 450, 100 + i * 50);
            windows.push_back(window);
        }
    }

    std::cout << "Created " << windows.size() << " windows. Close any to exit." << std::endl;

    while (!windows.empty())
    {
        for (auto it = windows.begin(); it != windows.end();)
        {
            GLFWwindow* window = *it;

            if (glfwWindowShouldClose(window))
            {
                glfwDestroyWindow(window);
                it = windows.erase(it);
                continue;
            }

            glfwMakeContextCurrent(window);

            int index = std::distance(windows.begin(), it);
            if (index < 3)
            {
                glClearColor(colors[index][0], colors[index][1], colors[index][2], 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                glfwSwapBuffers(window);
            }

            ++it;
        }

        glfwPollEvents();
    }

    glfwTerminate();
}

void input_handling_demo()
{
    std::cout << "\n--- Advanced Input Handling Demo ---" << std::endl;

    if (!glfwInit())
        return;

    GLFWwindow* window = glfwCreateWindow(800, 600, "TWIZ - Input Demo", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    auto joystick_callback = [](int jid, int event) {
        if (event == GLFW_CONNECTED)
            std::cout << "Joystick " << jid << " connected: " << glfwGetJoystickName(jid)
                      << std::endl;
        else if (event == GLFW_DISCONNECTED)
            std::cout << "Joystick " << jid << " disconnected" << std::endl;
    };

    glfwSetJoystickCallback(joystick_callback);

    std::cout << "Input demo active!" << std::endl;
    std::cout << "- Try connecting/disconnecting game controllers" << std::endl;
    std::cout << "- Use WASD keys to see keyboard input" << std::endl;
    std::cout << "- Mouse clicks and movement are tracked" << std::endl;

    double last_time = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        double current_time = glfwGetTime();

        if (current_time - last_time > 1.0) // Every second
        {
            // Check for connected joysticks
            for (int jid = GLFW_JOYSTICK_1; jid <= GLFW_JOYSTICK_LAST; ++jid)
            {
                if (glfwJoystickPresent(jid))
                {
                    int count;
                    const float* axes = glfwGetJoystickAxes(jid, &count);
                    if (count > 0)
                    {
                        std::cout << "Joystick " << jid << " axis 0: " << axes[0] << std::endl;
                    }
                }
            }
            last_time = current_time;
        }

        // Keyboard input
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            std::cout << "W pressed" << std::endl;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            std::cout << "A pressed" << std::endl;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            std::cout << "S pressed" << std::endl;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            std::cout << "D pressed" << std::endl;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void run_glfw_windowing_suite()
{
    show_glfw();

    std::cout << "\nRunning GLFW demonstrations..." << std::endl;
    std::cout << "Each demo will run for a few seconds or until you press ESC" << std::endl;

    create_basic_window();
    create_resizable_window_with_callbacks();
    opengl_triangle_demo();
    multiple_windows_demo();
    input_handling_demo();

    std::cout << "\n=== GLFW DEMO COMPLETE ===" << std::endl;
}

} // namespace twiz
