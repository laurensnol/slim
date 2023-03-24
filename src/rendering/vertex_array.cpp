#include "rendering/vertex_array.h"

#include "rendering/renderer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "core/base.h"

namespace slim
{
  std::shared_ptr<VertexArray> VertexArray::create()
  {
    if (Renderer::api() == RendererApi::OpenGL)
      return std::make_shared<OpenGLVertexArray>();
    else
      SLIM_ASSERT(false, "API not implemented")
  }
}