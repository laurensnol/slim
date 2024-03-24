#include "slim/ui/ui.hpp"

#include <imgui.h>

#if defined(SLIM_PLATFORM_WINDOWS) || defined(SLIM_PLATFORM_LINUX) || \
    defined(SLIM_PLATFORM_MACOS)
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif

namespace slim {
#if defined(SLIM_PLATFORM_WINDOWS) || defined(SLIM_PLATFORM_LINUX) || \
    defined(SLIM_PLATFORM_MACOS)
auto UI::init(GLFWwindow* window) noexcept -> void {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& imguiIo = ImGui::GetIO();
  imguiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
}

auto UI::shutdown() noexcept -> void {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
#endif

auto UI::drawBegin() noexcept -> void {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

auto UI::drawEnd() noexcept -> void {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

auto UI::capturesMouse() noexcept -> bool {
  const auto& imguiIo = ImGui::GetIO();
  return imguiIo.WantCaptureMouse;
}

auto UI::capturesKeyboard() noexcept -> bool {
  const auto& imguiIo = ImGui::GetIO();
  return imguiIo.WantCaptureKeyboard;
}
}  // namespace slim
