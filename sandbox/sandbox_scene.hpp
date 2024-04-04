#ifndef SLIM_SANDBOX_SANDBOX_SCENE_HPP_
#define SLIM_SANDBOX_SANDBOX_SCENE_HPP_

#include <glad/gl.h>

#include <memory>
#include <slim/slim.hpp>

class SandboxScene : public slim::Scene {
public:
  auto attach() noexcept -> void override;
  auto update() noexcept -> void override;
  auto uiDraw() noexcept -> void override;
  auto detach() noexcept -> void override;

private:
  std::shared_ptr<slim::Shader> shader_;
  GLuint ebo_ = 0;

  // clang-format off
  // NOLINTNEXTLINE
  constexpr static const GLfloat vertices_[] = {
    // NE, white
     0.5F,  0.5F, 0.0F, 1.0F, 1.0F, 1.0F,
    // SE, yellow
     0.5F, -0.5F, 0.0F, 1.0F, 1.0F, 0.0F,
    // SW, red
    -0.5F, -0.5F, 0.0F, 1.0F, 0.0F, 0.0F,
    // NW, Magenta
    -0.5F,  0.5F, 0.0F, 1.0F, 0.0F, 1.0F
  };

  // NOLINTNEXTLINE
  constexpr static const GLuint indices_[] = {
    0, 1, 3,
    1, 2, 3
  };
  // clang-format on
};

#endif  // SLIM_SANDBOX_SANDBOX_SCENE_HPP_
