#include "rendering/renderer.h"
#include "core/application.h"
#include "core/base.h"
#include <glad/gl.h>
#include <imgui.h>

#ifdef SLIM_PLATFORM_MACOS
  #include <backends/imgui_impl_glfw.h>
#endif

#include <backends/imgui_impl_opengl3.h>

namespace slim
{
  RendererApi Renderer::s_api = RendererApi::OpenGL;

  void Renderer::init()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    #ifdef SLIM_PLATFORM_MACOS
      ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNative()), true);
      ImGui_ImplOpenGL3_Init("#version 410");
    #else
      SLIM_ASSERT(false, "Platform not implemented")
    #endif
  }

  void Renderer::setClearColor(const glm::vec4& color)
  {
    if (s_api == RendererApi::OpenGL)
      glClearColor(color.r, color.g, color.b, color.a);
    else
      SLIM_ASSERT(false, "API not implemented")
  }

  void Renderer::clear()
  {
    if (s_api == RendererApi::OpenGL)
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else
      SLIM_ASSERT(false, "API not implemented")
  }

  void Renderer::beginUi()
  {
    ImGui_ImplOpenGL3_NewFrame();

    #ifdef SLIM_PLATFORM_MACOS
      ImGui_ImplGlfw_NewFrame();
    #else
      SLIM_ASSERT(false, "Platform not implemented")
    #endif

    ImGui::NewFrame();
  }

  void Renderer::endUi()
  {
    ImGui::Render();

    #ifdef SLIM_PLATFORM_MACOS
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    #else
      SLIM_ASSERT(false, "Platform not implemented")
    #endif
  }

  RendererApi Renderer::api()
  {
    return s_api;
  }
}