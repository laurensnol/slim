#ifndef SLIM_UI_UI_HPP_
#define SLIM_UI_UI_HPP_

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace slim::UI {
inline auto drawBegin() noexcept -> void {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

inline auto drawEnd() noexcept -> void {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
}  // namespace slim::UI

#endif  // SLIM_UI_UI_HPP_
