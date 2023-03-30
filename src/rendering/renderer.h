#ifndef SLIM_RENDERER_H
#define SLIM_RENDERER_H

namespace slim
{
  enum RendererApi
  {
    None,
    OpenGL
  };

  // TODO: Implement
  class Renderer {
  public:
    static RendererApi api();

  private:
    static RendererApi s_api;
  };
}

#endif