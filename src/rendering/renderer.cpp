#include "rendering/renderer.h"

namespace slim
{
  RendererApi Renderer::s_api = RendererApi::OpenGL;

  RendererApi Renderer::api()
  {
    return s_api;
  }
}