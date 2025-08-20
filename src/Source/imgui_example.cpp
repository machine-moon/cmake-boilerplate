#include "imgui_example.h"
#include <imgui.h>
#include <stdio.h>

namespace twiz_examples {
void show_imgui() {
  ImGui::CreateContext();
  printf("ImGui context created\n");
  ImGui::DestroyContext();
}

void show_simple_window() {
  ImGui::CreateContext();
  ImGui::NewFrame();
  ImGui::Begin("Hello, ImGui");
  ImGui::Text("This is a simple window");
  ImGui::End();
  ImGui::Render();
  printf("Simple window rendered\n");
  ImGui::DestroyContext();
}

void show_button_example() {
  ImGui::CreateContext();
  ImGui::NewFrame();
  ImGui::Begin("Button Example");
  if (ImGui::Button("Click Me")) {
    printf("Button was clicked\n");
  }
  ImGui::End();
  ImGui::Render();
  ImGui::DestroyContext();
}
} // namespace twiz_examples
