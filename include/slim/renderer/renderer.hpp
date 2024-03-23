#ifndef SLIM_RENDERER_RENDERER_HPP_
#define SLIM_RENDERER_RENDERER_HPP_

#include <glm/ext/vector_float4.hpp>
#include <memory>

#include "slim/renderer/renderer_api.hpp"

namespace slim {
class Renderer {
  using Api = RendererApi::Api;

public:
  static auto init(Api api = Api::OpenGL) noexcept -> void;

  static auto setClearColor(const glm::vec4& color) noexcept -> void;
  static auto clear() noexcept -> void;
  static auto draw() noexcept -> void;
  [[nodiscard]] static auto getApi() noexcept -> Api;

private:
  inline static std::unique_ptr<RendererApi> api_ = nullptr;
};
}  // namespace slim

#endif  // SLIM_RENDERER_RENDERER_HPP_
