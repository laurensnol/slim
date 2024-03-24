#ifndef SLIM_SANDBOX_SANDBOX_SCENE_HPP_
#define SLIM_SANDBOX_SANDBOX_SCENE_HPP_

#include <glad/gl.h>

#include <slim/slim.hpp>

class SandboxScene : public slim::Scene {
public:
  auto onAttach() noexcept -> void override;
  auto onUpdate() noexcept -> void override;
  auto onUiDraw() noexcept -> void override;
  auto onDetach() noexcept -> void override;

private:
  GLuint vao_ = 0;
  GLuint shader_ = 0;

  // NOLINTNEXTLINE
  constexpr static const GLfloat vertices_[] = {
      0.0F, 0.5F, 0.0F, 0.5F, -0.5F, 0.0F, -0.5F, -0.5F, 0.0F,
  };

  inline static const char* vertexShaderSource_ =
      "#version 410\n"
      "in vec3 vp;\n"
      "void main() {\n"
      "  gl_Position = vec4(vp, 1.0);\n"
      "}\n";

  inline static const char* fragmentShaderSource_ =
      "#version 410\n"
      "out vec4 frag_color;\n"
      "void main() {\n"
      "  frag_color = vec4(0.5, 0.0, 0.5, 1.0);\n"
      "}\n";
};

#endif  // SLIM_SANDBOX_SANDBOX_SCENE_HPP_
