#include "slim/ui/ui.hpp"

// IWYU pragma: no_include "slim/core/window.hpp"

#include <imgui.h>

#include "slim/core/application.hpp"

#if defined(SLIM_PLATFORM_WINDOWS) || defined(SLIM_PLATFORM_LINUX) || \
    defined(SLIM_PLATFORM_MACOS)
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "slim/platform/desktop/desktop_window.hpp"
#endif

namespace slim {
#if defined(SLIM_PLATFORM_WINDOWS) || defined(SLIM_PLATFORM_LINUX) || \
    defined(SLIM_PLATFORM_MACOS)
auto UI::init() noexcept -> void {
  const auto& window =
      dynamic_cast<const DesktopWindow&>(Application::getWindow());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& imguiIo = ImGui::GetIO();
  imguiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui_ImplGlfw_InitForOpenGL(window.window_, true);
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
