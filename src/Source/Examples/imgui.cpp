#include "Examples/imgui.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
// Ensure glad is the only OpenGL loader
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <cmath>
#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace Twiz
{

    static void SetupImguiStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowRounding = 8.0f;
        style.ChildRounding = 5.0f;
        style.FrameRounding = 5.0f;
        style.PopupRounding = 5.0f;
        style.ScrollbarRounding = 5.0f;
        style.GrabRounding = 3.0f;
        style.TabRounding = 5.0f;

        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.WindowMenuButtonPosition = ImGuiDir_Right;

        style.FramePadding = ImVec2(8, 4);
        style.ItemSpacing = ImVec2(8, 4);
        style.ItemInnerSpacing = ImVec2(4, 4);
        style.WindowPadding = ImVec2(8, 8);

        ImVec4* colors = style.Colors;
        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_Button] = ImVec4(0.05f, 0.50f, 0.95f, 0.54f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.60f, 1.00f, 0.54f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    }

    void ShowImgui()
    {
        std::cout << "\n=== IMGUI SHOWCASE ===" << '\n';
        std::cout << "ImGui Version: " << IMGUI_VERSION << '\n';
        std::cout << "Beautiful, immediate mode GUI for C++" << '\n';
    }

    void ShowImguiDemoSuite()
    {
        static bool showDemo = true;
        static bool showMetrics = false;
        static bool showStackTool = false;
        static bool showAbout = false;

        if (showDemo)
        {
            ImGui::ShowDemoWindow(&showDemo);
        }

        if (showMetrics)
        {
            ImGui::ShowMetricsWindow(&showMetrics);
        }

        if (showStackTool)
        {
            ImGui::ShowIDStackToolWindow(&showStackTool);
        }

        if (showAbout)
        {
            ImGui::ShowAboutWindow(&showAbout);
        }

        ImGui::Begin("TWIZ ImGui Control Center");
        ImGui::Text("Welcome to the TWIZ Graphics Engine ImGui Showcase!");

        ImGui::Separator();
        ImGui::Text("Official ImGui Windows:");
        ImGui::Checkbox("Show Demo Window", &showDemo);
        ImGui::Checkbox("Show Metrics Window", &showMetrics);
        ImGui::Checkbox("Show Stack Tool", &showStackTool);
        ImGui::Checkbox("Show About Window", &showAbout);

        ImGui::End();
    }

    void ShowControlPanelDemo()
    {
        static float engineSpeed = 60.0f;
        static int qualityLevel = 2;
        static bool vsyncEnabled = true;
        static bool fullscreen = false;
        static float masterVolume = 0.8f;
        static float musicVolume = 0.6f;
        static float sfxVolume = 0.9f;
        static int selectedRenderer = 0;
        const char* renderers[] = {"OpenGL", "Vulkan", "DirectX 12", "Metal"};

        ImGui::Begin("🎮 Engine Control Panel", nullptr, ImGuiWindowFlags_MenuBar);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Scene", "Ctrl+N"))
                {
                }
                if (ImGui::MenuItem("Load Scene", "Ctrl+O"))
                {
                }
                if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                {
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4"))
                {
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Performance", "F1"))
                {
                }
                if (ImGui::MenuItem("Console", "F2"))
                {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (ImGui::CollapsingHeader("⚙️ Performance Settings", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::SliderFloat("Target FPS", &engineSpeed, 30.0f, 144.0f, "%.0f");
            ImGui::Combo("Quality Level", &qualityLevel, "Low\0Medium\0High\0Ultra\0");
            ImGui::Checkbox("VSync", &vsyncEnabled);
            ImGui::Checkbox("Fullscreen", &fullscreen);

            ImGui::Text("Renderer:");
            ImGui::Combo("##renderer", &selectedRenderer, renderers, IM_ARRAYSIZE(renderers));
        }

        if (ImGui::CollapsingHeader("🔊 Audio Settings"))
        {
            ImGui::SliderFloat("Master Volume", &masterVolume, 0.0f, 1.0f, "%.2f");
            ImGui::SliderFloat("Music Volume", &musicVolume, 0.0f, 1.0f, "%.2f");
            ImGui::SliderFloat("SFX Volume", &sfxVolume, 0.0f, 1.0f, "%.2f");

            if (ImGui::Button("Test Audio"))
            {
                std::cout << "🎵 Playing test sound..." << '\n';
            }
        }

        if (ImGui::CollapsingHeader("📊 System Info"))
        {
            ImGui::Text("GPU: NVIDIA RTX 4090");
            ImGui::Text("VRAM: 24GB");
            ImGui::Text("CPU: Intel i9-13900K");
            ImGui::Text("RAM: 32GB DDR5");

            static float fpsHistory[100] = {};
            static int fpsIndex = 0;
            fpsHistory[fpsIndex] = ImGui::GetIO().Framerate;
            fpsIndex = (fpsIndex + 1) % 100;

            ImGui::PlotLines("FPS", fpsHistory, 100, fpsIndex, nullptr, 0.0f, 200.0f, ImVec2(0, 50));
            ImGui::Text("Current FPS: %.1f", ImGui::GetIO().Framerate);
        }

        ImGui::End();
    }

    void ShowGraphicsSettingsDemo()
    {
        static float ambientLight[3] = {0.2f, 0.2f, 0.3f};
        static float fogDensity = 0.02f;
        static float exposure = 1.0f;
        static bool enableShadows = true;
        static bool enableReflections = true;
        static bool enableBloom = true;
        static int shadowQuality = 2;
        static float renderScale = 1.0f;

        ImGui::Begin("🎨 Graphics Settings");

        ImGui::Text("Lighting & Atmosphere");
        ImGui::Separator();

        ImGui::ColorEdit3("Ambient Light", ambientLight);
        ImGui::SliderFloat("Fog Density", &fogDensity, 0.0f, 0.1f, "%.3f");
        ImGui::SliderFloat("Exposure", &exposure, 0.1f, 5.0f, "%.2f");

        ImGui::Spacing();
        ImGui::Text("Post-Processing Effects");
        ImGui::Separator();

        ImGui::Checkbox("Enable Shadows", &enableShadows);
        if (enableShadows)
        {
            ImGui::SameLine();
            ImGui::SliderInt("Quality##shadows", &shadowQuality, 0, 4);
        }

        ImGui::Checkbox("Screen Space Reflections", &enableReflections);
        ImGui::Checkbox("Bloom Effect", &enableBloom);

        ImGui::Spacing();
        ImGui::Text("Rendering");
        ImGui::Separator();

        ImGui::SliderFloat("Render Scale", &renderScale, 0.5f, 2.0f, "%.2f");

        if (ImGui::Button("Apply Settings"))
        {
            std::cout << "Graphics settings applied!" << '\n';
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset to Default"))
        {
            ambientLight[0] = ambientLight[1] = 0.2f;
            ambientLight[2] = 0.3f;
            fogDensity = 0.02f;
            exposure = 1.0f;
            renderScale = 1.0f;
            std::cout << "Settings reset to default!" << '\n';
        }

        ImGui::End();
    }

    void ShowDataVisualizationDemo()
    {
        static std::vector<float> dataPoints;
        static float time = 0.0f;

        if (dataPoints.size() < 200)
        {
            time += 0.1f;
            float const value = (std::sin(time) * 50.0f) + (std::cos(time * 2.3f) * 30.0f) + 100.0f;
            dataPoints.push_back(value);
        }
        else
        {
            for (size_t i = 0; i < dataPoints.size() - 1; ++i)
            {
                dataPoints[i] = dataPoints[i + 1];
            }
            time += 0.1f;
            float const value = (std::sin(time) * 50.0f) + (std::cos(time * 2.3f) * 30.0f) + 100.0f;
            dataPoints.back() = value;
        }

        ImGui::Begin("📈 Data Visualization");

        if (!dataPoints.empty())
        {
            ImGui::PlotLines("Signal", dataPoints.data(), static_cast<int>(dataPoints.size()), 0, "Real-time Data", 0.0f, 200.0f, ImVec2(0, 100));

            ImGui::PlotHistogram("Histogram", dataPoints.data(), static_cast<int>(dataPoints.size()), 0, nullptr, 0.0f, 200.0f, ImVec2(0, 100));
        }

        static std::map<std::string, float> stats = {{"CPU Usage", 45.2f}, {"GPU Usage", 78.5f}, {"Memory", 62.1f}, {"Network", 23.7f}};

        ImGui::Separator();
        ImGui::Text("System Statistics");

        for (auto& [name, value] : stats)
        {
            ImGui::ProgressBar(value / 100.0f, ImVec2(0.0f, 0.0f), (name + ": " + std::to_string(static_cast<int>(value)) + "%").c_str());

            value += (rand() % 10 - 5) * 0.1f;
            value = std::max(0.0f, std::min(100.0f, value));
        }

        ImGui::End();
    }

    void ShowMaterialDesignDemo()
    {
        ImGui::Begin("🎭 Material Design Demo");

        static int const tab = 0;
        (void)tab; // Unused for now
        if (ImGui::BeginTabBar("MaterialTabs"))
        {
            if (ImGui::BeginTabItem("Colors"))
            {
                static float primaryColor[3] = {0.2f, 0.6f, 1.0f};
                static float secondaryColor[3] = {1.0f, 0.4f, 0.2f};
                static float accentColor[3] = {0.8f, 0.2f, 0.8f};

                ImGui::ColorEdit3("Primary", primaryColor);
                ImGui::ColorEdit3("Secondary", secondaryColor);
                ImGui::ColorEdit3("Accent", accentColor);

                ImGui::Separator();

                if (ImGui::Button("Primary Button", ImVec2(120, 40)))
                {
                    std::cout << "Primary action triggered!" << '\n';
                }
                ImGui::SameLine();

                if (ImGui::Button("Secondary", ImVec2(120, 40)))
                {
                    std::cout << "Secondary action triggered!" << '\n';
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Cards"))
            {
                ImGui::BeginChild("Card1", ImVec2(200, 150), true);
                ImGui::Text("📱 Mobile");
                ImGui::Separator();
                ImGui::Text("Responsive design");
                ImGui::Text("Touch-friendly");
                ImGui::Text("Cross-platform");
                if (ImGui::Button("Learn More"))
                {
                    std::cout << "Mobile card clicked!" << '\n';
                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginChild("Card2", ImVec2(200, 150), true);
                ImGui::Text("🖥️ Desktop");
                ImGui::Separator();
                ImGui::Text("High performance");
                ImGui::Text("Rich interactions");
                ImGui::Text("Multi-window");
                if (ImGui::Button("Explore"))
                {
                    std::cout << "Desktop card clicked!" << '\n';
                }
                ImGui::EndChild();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Forms"))
            {
                static char textInput[256] = "Sample text";
                static char password[256] = "";
                static bool checkboxState = false;
                static int radioSelection = 0;

                ImGui::InputText("Username", textInput, sizeof(textInput));
                ImGui::InputText("Password", password, sizeof(password), ImGuiInputTextFlags_Password);

                ImGui::Checkbox("Remember me", &checkboxState);

                ImGui::RadioButton("Option A", &radioSelection, 0);
                ImGui::RadioButton("Option B", &radioSelection, 1);
                ImGui::RadioButton("Option C", &radioSelection, 2);

                if (ImGui::Button("Submit", ImVec2(100, 30)))
                {
                    std::cout << "Form submitted!" << '\n';
                }

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();
    }

    void ShowGameHudDemo()
    {
        static int const health = 85;
        static int const mana = 120;
        static int const level = 42;
        static float const experience = 0.67f;
        static int const coins = 1337;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(300, 120), ImGuiCond_Always);
        ImGui::Begin("Player HUD", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

        ImGui::Text("🧙 Wizard Lvl %d", level);

        ImGui::Text("❤️ Health:");
        ImGui::SameLine();
        ImGui::ProgressBar(health / 100.0f, ImVec2(-1, 0), std::to_string(health).c_str());

        ImGui::Text("💙 Mana:");
        ImGui::SameLine();
        ImGui::ProgressBar(mana / 150.0f, ImVec2(-1, 0), std::to_string(mana).c_str());

        ImGui::Text("⭐ Experience:");
        ImGui::SameLine();
        ImGui::ProgressBar(experience, ImVec2(-1, 0), "");

        ImGui::Text("💰 Coins: %d", coins);

        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(viewport->Size.x - 200, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(180, 150), ImGuiCond_Always);
        ImGui::Begin("Minimap", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 const canvasP0 = ImGui::GetCursorScreenPos();
        ImVec2 const canvasSz = ImGui::GetContentRegionAvail();
        ImVec2 const canvasP1 = ImVec2(canvasP0.x + canvasSz.x, canvasP0.y + canvasSz.y);

        drawList->AddRectFilled(canvasP0, canvasP1, IM_COL32(50, 50, 50, 255));
        drawList->AddRect(canvasP0, canvasP1, IM_COL32(255, 255, 255, 255));

        static float playerX = canvasSz.x * 0.5f;
        static float playerY = canvasSz.y * 0.5f;

        playerX += (rand() % 5 - 2) * 0.5f;
        playerY += (rand() % 5 - 2) * 0.5f;

        playerX = std::max(5.0f, std::min(canvasSz.x - 5.0f, playerX));
        playerY = std::max(5.0f, std::min(canvasSz.y - 5.0f, playerY));

        drawList->AddCircleFilled(ImVec2(canvasP0.x + playerX, canvasP0.y + playerY), 4.0f, IM_COL32(0, 255, 0, 255));

        for (int i = 0; i < 3; ++i)
        {
            float const enemyX = canvasSz.x * (0.2f + i * 0.3f);
            float const enemyY = canvasSz.y * (0.3f + i * 0.2f);
            drawList->AddCircleFilled(ImVec2(canvasP0.x + enemyX, canvasP0.y + enemyY), 3.0f, IM_COL32(255, 0, 0, 255));
        }

        ImGui::End();
    }

    void RunImguiShowcase()
    {
        if (!glfwInit())
        {
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(1600, 1000, "TWIZ ImGui Showcase", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        /*
        if (!gladLoadGL(glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            return;
        }*/

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        SetupImguiStyle();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ShowImgui();

        std::cout << "\nStarting ImGui showcase with multiple beautiful UI demonstrations!" << '\n';
        std::cout << "Press ESC to exit" << '\n';

        while (!glfwWindowShouldClose(window))
        {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                break;
            }

            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ShowImguiDemoSuite();
            ShowControlPanelDemo();
            ShowGraphicsSettingsDemo();
            ShowDataVisualizationDemo();
            ShowMaterialDesignDemo();
            ShowGameHudDemo();

            ImGui::Render();
            int displayW = 0, displayH = 0;
            glfwGetFramebufferSize(window, &displayW, &displayH);
            glViewport(0, 0, displayW, displayH);
            glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();

        std::cout << "\n=== IMGUI SHOWCASE COMPLETE ===" << '\n';
    }

} // namespace Twiz
