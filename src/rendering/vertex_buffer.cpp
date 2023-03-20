#include "rendering/vertex_buffer.h"

#include "rendering/renderer.h"
#include "platform/OpenGL/OpenGLVertexBuffer.h"

#include <spdlog/spdlog.h>

namespace slim
{
  std::shared_ptr<VertexBuffer> VertexBuffer::create(float *vertices, uint32_t size)
  {
    if (Renderer::api() == RendererApi::OpenGL)
    {
      return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    }
    else
    {
      spdlog::critical("API not implemented");
      assert(false);
    }
  }
}