#include "rendering/renderer.h"

namespace slim
{
  RendererApi Renderer::_api = RendererApi::OpenGL;

  RendererApi Renderer::api()
  {
    return _api;
  }
}