#include "imgui_example.h"
// #define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
// #include <glad/gl.h>
#include <cmath>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace twiz
{

static void setup_imgui_style()
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

void show_imgui()
{
    std::cout << "\n=== IMGUI SHOWCASE ===" << std::endl;
    std::cout << "ImGui Version: " << IMGUI_VERSION << std::endl;
    std::cout << "Beautiful, immediate mode GUI for C++" << std::endl;
}

void show_imgui_demo_suite()
{
    static bool show_demo = true;
    static bool show_metrics = false;
    static bool show_stack_tool = false;
    static bool show_about = false;

    if (show_demo)
        ImGui::ShowDemoWindow(&show_demo);

    if (show_metrics)
        ImGui::ShowMetricsWindow(&show_metrics);

    if (show_stack_tool)
        ImGui::ShowIDStackToolWindow(&show_stack_tool);

    if (show_about)
        ImGui::ShowAboutWindow(&show_about);

    ImGui::Begin("TWIZ ImGui Control Center");
    ImGui::Text("Welcome to the TWIZ Graphics Engine ImGui Showcase!");

    ImGui::Separator();
    ImGui::Text("Official ImGui Windows:");
    ImGui::Checkbox("Show Demo Window", &show_demo);
    ImGui::Checkbox("Show Metrics Window", &show_metrics);
    ImGui::Checkbox("Show Stack Tool", &show_stack_tool);
    ImGui::Checkbox("Show About Window", &show_about);

    ImGui::End();
}

void show_control_panel_demo()
{
    static float engine_speed = 60.0f;
    static int quality_level = 2;
    static bool vsync_enabled = true;
    static bool fullscreen = false;
    static float master_volume = 0.8f;
    static float music_volume = 0.6f;
    static float sfx_volume = 0.9f;
    static int selected_renderer = 0;
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
        ImGui::SliderFloat("Target FPS", &engine_speed, 30.0f, 144.0f, "%.0f");
        ImGui::Combo("Quality Level", &quality_level, "Low\0Medium\0High\0Ultra\0");
        ImGui::Checkbox("VSync", &vsync_enabled);
        ImGui::Checkbox("Fullscreen", &fullscreen);

        ImGui::Text("Renderer:");
        ImGui::Combo("##renderer", &selected_renderer, renderers, IM_ARRAYSIZE(renderers));
    }

    if (ImGui::CollapsingHeader("🔊 Audio Settings"))
    {
        ImGui::SliderFloat("Master Volume", &master_volume, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat("Music Volume", &music_volume, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat("SFX Volume", &sfx_volume, 0.0f, 1.0f, "%.2f");

        if (ImGui::Button("Test Audio"))
        {
            std::cout << "🎵 Playing test sound..." << std::endl;
        }
    }

    if (ImGui::CollapsingHeader("📊 System Info"))
    {
        ImGui::Text("GPU: NVIDIA RTX 4090");
        ImGui::Text("VRAM: 24GB");
        ImGui::Text("CPU: Intel i9-13900K");
        ImGui::Text("RAM: 32GB DDR5");

        static float fps_history[100] = {};
        static int fps_index = 0;
        fps_history[fps_index] = ImGui::GetIO().Framerate;
        fps_index = (fps_index + 1) % 100;

        ImGui::PlotLines("FPS", fps_history, 100, fps_index, nullptr, 0.0f, 200.0f, ImVec2(0, 50));
        ImGui::Text("Current FPS: %.1f", ImGui::GetIO().Framerate);
    }

    ImGui::End();
}

void show_graphics_settings_demo()
{
    static float ambient_light[3] = {0.2f, 0.2f, 0.3f};
    static float fog_density = 0.02f;
    static float exposure = 1.0f;
    static bool enable_shadows = true;
    static bool enable_reflections = true;
    static bool enable_bloom = true;
    static int shadow_quality = 2;
    static float render_scale = 1.0f;

    ImGui::Begin("🎨 Graphics Settings");

    ImGui::Text("Lighting & Atmosphere");
    ImGui::Separator();

    ImGui::ColorEdit3("Ambient Light", ambient_light);
    ImGui::SliderFloat("Fog Density", &fog_density, 0.0f, 0.1f, "%.3f");
    ImGui::SliderFloat("Exposure", &exposure, 0.1f, 5.0f, "%.2f");

    ImGui::Spacing();
    ImGui::Text("Post-Processing Effects");
    ImGui::Separator();

    ImGui::Checkbox("Enable Shadows", &enable_shadows);
    if (enable_shadows)
    {
        ImGui::SameLine();
        ImGui::SliderInt("Quality##shadows", &shadow_quality, 0, 4);
    }

    ImGui::Checkbox("Screen Space Reflections", &enable_reflections);
    ImGui::Checkbox("Bloom Effect", &enable_bloom);

    ImGui::Spacing();
    ImGui::Text("Rendering");
    ImGui::Separator();

    ImGui::SliderFloat("Render Scale", &render_scale, 0.5f, 2.0f, "%.2f");

    if (ImGui::Button("Apply Settings"))
    {
        std::cout << "Graphics settings applied!" << std::endl;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset to Default"))
    {
        ambient_light[0] = ambient_light[1] = 0.2f;
        ambient_light[2] = 0.3f;
        fog_density = 0.02f;
        exposure = 1.0f;
        render_scale = 1.0f;
        std::cout << "Settings reset to default!" << std::endl;
    }

    ImGui::End();
}

void show_data_visualization_demo()
{
    static std::vector<float> data_points;
    static float time = 0.0f;

    if (data_points.size() < 200)
    {
        time += 0.1f;
        float value = sin(time) * 50.0f + cos(time * 2.3f) * 30.0f + 100.0f;
        data_points.push_back(value);
    }
    else
    {
        for (size_t i = 0; i < data_points.size() - 1; ++i)
        {
            data_points[i] = data_points[i + 1];
        }
        time += 0.1f;
        float value = sin(time) * 50.0f + cos(time * 2.3f) * 30.0f + 100.0f;
        data_points.back() = value;
    }

    ImGui::Begin("📈 Data Visualization");

    if (!data_points.empty())
    {
        ImGui::PlotLines("Signal", data_points.data(), static_cast<int>(data_points.size()), 0,
                         "Real-time Data", 0.0f, 200.0f, ImVec2(0, 100));

        ImGui::PlotHistogram("Histogram", data_points.data(), static_cast<int>(data_points.size()),
                             0, nullptr, 0.0f, 200.0f, ImVec2(0, 100));
    }

    static std::map<std::string, float> stats = {
        {"CPU Usage", 45.2f}, {"GPU Usage", 78.5f}, {"Memory", 62.1f}, {"Network", 23.7f}};

    ImGui::Separator();
    ImGui::Text("System Statistics");

    for (auto& [name, value] : stats)
    {
        ImGui::ProgressBar(value / 100.0f, ImVec2(0.0f, 0.0f),
                           (name + ": " + std::to_string(static_cast<int>(value)) + "%").c_str());

        value += (rand() % 10 - 5) * 0.1f;
        value = std::max(0.0f, std::min(100.0f, value));
    }

    ImGui::End();
}

void show_material_design_demo()
{
    ImGui::Begin("🎭 Material Design Demo");

    static int tab = 0;
    (void)tab; // Unused for now
    if (ImGui::BeginTabBar("MaterialTabs"))
    {
        if (ImGui::BeginTabItem("Colors"))
        {
            static float primary_color[3] = {0.2f, 0.6f, 1.0f};
            static float secondary_color[3] = {1.0f, 0.4f, 0.2f};
            static float accent_color[3] = {0.8f, 0.2f, 0.8f};

            ImGui::ColorEdit3("Primary", primary_color);
            ImGui::ColorEdit3("Secondary", secondary_color);
            ImGui::ColorEdit3("Accent", accent_color);

            ImGui::Separator();

            if (ImGui::Button("Primary Button", ImVec2(120, 40)))
            {
                std::cout << "Primary action triggered!" << std::endl;
            }
            ImGui::SameLine();

            if (ImGui::Button("Secondary", ImVec2(120, 40)))
            {
                std::cout << "Secondary action triggered!" << std::endl;
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
                std::cout << "Mobile card clicked!" << std::endl;
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
                std::cout << "Desktop card clicked!" << std::endl;
            }
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Forms"))
        {
            static char text_input[256] = "Sample text";
            static char password[256] = "";
            static bool checkbox_state = false;
            static int radio_selection = 0;

            ImGui::InputText("Username", text_input, sizeof(text_input));
            ImGui::InputText("Password", password, sizeof(password), ImGuiInputTextFlags_Password);

            ImGui::Checkbox("Remember me", &checkbox_state);

            ImGui::RadioButton("Option A", &radio_selection, 0);
            ImGui::RadioButton("Option B", &radio_selection, 1);
            ImGui::RadioButton("Option C", &radio_selection, 2);

            if (ImGui::Button("Submit", ImVec2(100, 30)))
            {
                std::cout << "Form submitted!" << std::endl;
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void show_game_hud_demo()
{
    static int health = 85;
    static int mana = 120;
    static int level = 42;
    static float experience = 0.67f;
    static int coins = 1337;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 120), ImGuiCond_Always);
    ImGui::Begin("Player HUD", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

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
    ImGui::Begin("Minimap", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

    static float player_x = canvas_sz.x * 0.5f;
    static float player_y = canvas_sz.y * 0.5f;

    player_x += (rand() % 5 - 2) * 0.5f;
    player_y += (rand() % 5 - 2) * 0.5f;

    player_x = std::max(5.0f, std::min(canvas_sz.x - 5.0f, player_x));
    player_y = std::max(5.0f, std::min(canvas_sz.y - 5.0f, player_y));

    draw_list->AddCircleFilled(ImVec2(canvas_p0.x + player_x, canvas_p0.y + player_y), 4.0f,
                               IM_COL32(0, 255, 0, 255));

    for (int i = 0; i < 3; ++i)
    {
        float enemy_x = canvas_sz.x * (0.2f + i * 0.3f);
        float enemy_y = canvas_sz.y * (0.3f + i * 0.2f);
        draw_list->AddCircleFilled(ImVec2(canvas_p0.x + enemy_x, canvas_p0.y + enemy_y), 3.0f,
                                   IM_COL32(255, 0, 0, 255));
    }

    ImGui::End();
}

void run_imgui_showcase()
{
    if (!glfwInit())
        return;

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

    setup_imgui_style();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    show_imgui();

    std::cout << "\nStarting ImGui showcase with multiple beautiful UI demonstrations!"
              << std::endl;
    std::cout << "Press ESC to exit" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        show_imgui_demo_suite();
        show_control_panel_demo();
        show_graphics_settings_demo();
        show_data_visualization_demo();
        show_material_design_demo();
        show_game_hud_demo();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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

    std::cout << "\n=== IMGUI SHOWCASE COMPLETE ===" << std::endl;
}

} // namespace twiz
