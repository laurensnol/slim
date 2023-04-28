#ifndef SLIM_RENDERER_H
#define SLIM_RENDERER_H

#include <glm/glm.hpp>

namespace slim
{
  enum RendererApi
  {
    None,
    OpenGL
  };

  // TODO: Implement
  class Renderer
  {
  public:
    static void init();
    static void setClearColor(const glm::vec4& color);

    static void clear();
    static void beginUi();
    static void endUi();

    static RendererApi api();

  private:
    static RendererApi s_api;
  };
}

#endif