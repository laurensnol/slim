#include "rendering/index_buffer.h"

#include "rendering/renderer.h"
#include "platform/OpenGL/OpenGLIndexBuffer.h"
#include <spdlog/spdlog.h>

namespace slim
{
  std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t *indices, uint32_t count)
  {
    if (Renderer::api() == RendererApi::OpenGL)
    {
      return std::make_shared<OpenGLIndexBuffer>(indices, count);
    }
    else
    {
      spdlog::critical("API not implemented");
      assert(false);
    }
  }
}