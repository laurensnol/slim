#include "rendering/texture2d.h"
#include "rendering/renderer.h"
#include "platform/OpenGL/OpenGLTexture2D.h"
#include "core/base.h"

namespace slim
{
  std::shared_ptr<Texture2D> slim::Texture2D::create(const std::string& path)
  {
    if (Renderer::api() == RendererApi::OpenGL)
      return std::make_shared<OpenGLTexture2D>(path);
    else
      SLIM_ASSERT(false, "API not implemented")
  }
}