#include "Examples/glfw.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
    void ErrorCallback(int error, const char* pdescription)
    {
        std::cerr << "GLFW Error " << error << ": " << pdescription << '\n';
    }

    void KeyCallback(GLFWwindow* pwindow, int key, int /*scancode*/, int action, int /*mods*/)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(pwindow, GLFW_TRUE);
        }

        if (action == GLFW_PRESS)
        {
            std::cout << "Key pressed: " << key << '\n';
        }
    }

    void FramebufferSizeCallback(GLFWwindow* /*window*/, int width, int height)
    {
        glViewport(0, 0, width, height);
        std::cout << "Window resized to: " << width << "x" << height << '\n';
    }

    void CursorPositionCallback(GLFWwindow* pwindow, double xpos, double ypos)
    {
        if (glfwGetMouseButton(pwindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            std::cout << "Mouse dragging at: " << xpos << ", " << ypos << '\n';
        }
    }

} // namespace

namespace Twiz
{
    void ShowGlfw()
    {
        std::cout << "\n=== GLFW WINDOWING SHOWCASE ===" << '\n';

        if (glfwInit() == 0)
        {
            std::cerr << "Failed to initialize GLFW" << '\n';
            return;
        }

        int major = 0;
        int minor = 0;
        int rev = 0;
        glfwGetVersion(&major, &minor, &rev);
        std::cout << "GLFW Version: " << major << "." << minor << "." << rev << '\n';

        const char* version = glfwGetVersionString();
        std::cout << "GLFW Version String: " << version << '\n';

        glfwTerminate();
    }

    void CreateBasicWindow()
    {
        std::cout << "\n--- Basic Window Creation ---" << '\n';

        if (glfwInit() == 0)
        {
            return;
        }

        glfwSetErrorCallback(ErrorCallback);

        GLFWwindow* window = glfwCreateWindow(800, 600, "TWIZ - Basic GLFW Window", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cerr << "Failed to create window" << '\n';
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        std::cout << "Window created successfully! Press ESC to close." << '\n';

        // Simple color cycling
        float time = 0.0F;
        while (glfwWindowShouldClose(window) == 0)
        {
            time += 0.016F; // ~60 FPS

            float const red = (std::sin(time) + 1.0F) / 2.0F;
            float const green = (std::sin(time + 2.0F) + 1.0F) / 2.0F;
            float const blue = (std::sin(time + 4.0F) + 1.0F) / 2.0F;

            glClearColor(red, green, blue, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                break;
            }
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void CreateResizableWindowWithCallbacks()
    {
        std::cout << "\n--- Resizable Window with Callbacks ---" << '\n';

        if (glfwInit() == 0)
        {
            return;
        }

        glfwSetErrorCallback(ErrorCallback);

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        GLFWwindow* window = glfwCreateWindow(1024, 768, "TWIZ - Interactive Window", nullptr, nullptr);
        if (window == nullptr)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        glfwSetKeyCallback(window, KeyCallback);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
        glfwSetCursorPosCallback(window, CursorPositionCallback);

        std::cout << "Interactive window created!" << '\n';
        std::cout << "- Press keys to see input" << '\n';
        std::cout << "- Resize window to see callback" << '\n';
        std::cout << "- Click and drag to see mouse input" << '\n';
        std::cout << "- Press ESC to exit" << '\n';

        glEnable(GL_DEPTH_TEST);

        while (glfwWindowShouldClose(window) == 0)
        {
            double const time = glfwGetTime();

            glClearColor(0.1F, 0.1F, 0.2F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBegin(GL_QUADS);
            glColor3f(1.0F, 0.5F, 0.2F);
            glVertex2d(-0.5 + (sin(time) * 0.2), -0.5);
            glVertex2d(0.5 + (sin(time) * 0.2), -0.5);
            glVertex2d(0.5 + (sin(time) * 0.2), 0.5);
            glVertex2d(-0.5 + (sin(time) * 0.2), 0.5);
            glEnd();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void OpenglTriangleDemo()
    {
        std::cout << "\n--- OpenGL Triangle Demo ---" << '\n';

        if (glfwInit() == 0)
        {
            return;
        }

        GLFWwindow* window = glfwCreateWindow(800, 600, "TWIZ - OpenGL Triangle", nullptr, nullptr);
        if (window == nullptr)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, KeyCallback);

        std::cout << "Animated triangle rendering! Press ESC to exit." << '\n';

        while (glfwWindowShouldClose(window) == 0)
        {
            auto const time = static_cast<float>(glfwGetTime());

            glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
            glRotatef(time * 50.0F, 0.0F, 0.0F, 1.0F);
            float const scale = 0.5F + (0.3F * std::sin(time));
            glScalef(scale, scale, 1.0F);

            glBegin(GL_TRIANGLES);
            glColor3f(1.0F, 0.0F, 0.0F);
            glVertex2f(0.0F, 0.5F);

            glColor3f(0.0F, 1.0F, 0.0F);
            glVertex2f(-0.5F, -0.5F);

            glColor3f(0.0F, 0.0F, 1.0F);
            glVertex2f(0.5F, -0.5F);
            glEnd();

            glPopMatrix();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void MultipleWindowsDemo()
    {
        std::cout << "\n--- Multiple Windows Demo ---" << '\n';

        if (glfwInit() == 0)
        {
            return;
        }

        std::vector<GLFWwindow*> windows;
        const char* titles[] = {"Window 1 - Red", "Window 2 - Green", "Window 3 - Blue"};
        float const colors[][3] = {{1.0F, 0.2F, 0.2F}, {0.2F, 1.0F, 0.2F}, {0.2F, 0.2F, 1.0F}};

        for (int i = 0; i < 3; ++i)
        {
            GLFWwindow* window = glfwCreateWindow(400, 300, titles[i], nullptr, nullptr);
            if (window != nullptr)
            {
                glfwSetWindowPos(window, 100 + (i * 450), 100 + (i * 50));
                windows.push_back(window);
            }
        }

        std::cout << "Created " << windows.size() << " windows. Close any to exit." << '\n';

        while (!windows.empty())
        {
            for (auto it = windows.begin(); it != windows.end();)
            {
                GLFWwindow* window = *it;

                if (glfwWindowShouldClose(window) != 0)
                {
                    glfwDestroyWindow(window);
                    it = windows.erase(it);
                    continue;
                }

                glfwMakeContextCurrent(window);

                int const index = static_cast<int>(std::distance(windows.begin(), it));
                if (index < 3)
                {
                    glClearColor(colors[index][0], colors[index][1], colors[index][2], 1.0F);
                    glClear(GL_COLOR_BUFFER_BIT);
                    glfwSwapBuffers(window);
                }

                ++it;
            }

            glfwPollEvents();
        }

        glfwTerminate();
    }

    void InputHandlingDemo()
    {
        std::cout << "\n--- Advanced Input Handling Demo ---" << '\n';

        if (glfwInit() == 0)
        {
            return;
        }

        GLFWwindow* window = glfwCreateWindow(800, 600, "TWIZ - Input Demo", nullptr, nullptr);
        if (window == nullptr)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        auto joystickCallback = [](int jid, int event) {
            if (event == GLFW_CONNECTED)
            {
                std::cout << "Joystick " << jid << " connected: " << glfwGetJoystickName(jid) << '\n';
            }
            else if (event == GLFW_DISCONNECTED)
            {
                std::cout << "Joystick " << jid << " disconnected" << '\n';
            }
        };

        glfwSetJoystickCallback(joystickCallback);

        std::cout << "Input demo active!" << '\n';
        std::cout << "- Try connecting/disconnecting game controllers" << '\n';
        std::cout << "- Use WASD keys to see keyboard input" << '\n';
        std::cout << "- Mouse clicks and movement are tracked" << '\n';

        double lastTime = glfwGetTime();

        while (glfwWindowShouldClose(window) == 0)
        {
            double const currentTime = glfwGetTime();

            if (currentTime - lastTime > 1.0) // Every second
            {
                // Check for connected joysticks
                for (int jid = GLFW_JOYSTICK_1; jid <= GLFW_JOYSTICK_LAST; ++jid)
                {
                    if (glfwJoystickPresent(jid) != 0)
                    {
                        int count = 0;
                        const float* axes = glfwGetJoystickAxes(jid, &count);
                        if (count > 0)
                        {
                            std::cout << "Joystick " << jid << " axis 0: " << axes[0] << '\n';
                        }
                    }
                }
                lastTime = currentTime;
            }

            // Keyboard input
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                std::cout << "W pressed" << '\n';
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                std::cout << "A pressed" << '\n';
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                std::cout << "S pressed" << '\n';
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                std::cout << "D pressed" << '\n';
            }

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                break;
            }

            glClearColor(0.1F, 0.1F, 0.1F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void RunGlfwWindowingSuite()
    {
        ShowGlfw();

        std::cout << "\nRunning GLFW demonstrations..." << '\n';
        std::cout << "Each demo will run for a few seconds or until you press ESC" << '\n';

        CreateBasicWindow();
        CreateResizableWindowWithCallbacks();
        OpenglTriangleDemo();
        MultipleWindowsDemo();
        InputHandlingDemo();

        std::cout << "\n=== GLFW DEMO COMPLETE ===" << '\n';
    }

} // namespace Twiz
