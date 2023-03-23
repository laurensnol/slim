#include "rendering/vertex_array.h"

#include "rendering/renderer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include <spdlog/spdlog.h>

namespace slim
{
  std::shared_ptr<VertexArray> VertexArray::create()
  {
    if (Renderer::api() == RendererApi::OpenGL)
    {
      return std::make_shared<OpenGLVertexArray>();
    }
    else
    {
      spdlog::critical("API not implemented");
      assert(false);
    }
  }
}