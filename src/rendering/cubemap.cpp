#include "rendering/cubemap.h"
#include "rendering/renderer.h"
#include "platform/OpenGL/OpenGLCubemap.h"
#include "core/base.h"
#include <initializer_list>

namespace slim
{
  std::shared_ptr<Cubemap> Cubemap::create(const std::string &texturePath)
  {
    if (Renderer::api() == RendererApi::OpenGL)
      return std::make_unique<OpenGLCubemap>(std::initializer_list<std::string>{texturePath});
    else
      SLIM_ASSERT(false, "API not implemented")
  }

  std::shared_ptr<Cubemap> Cubemap::create(const std::string &rightPath, const std::string &leftPath, const std::string &topPath, const std::string &bottomPath, const std::string &backPath, const std::string &frontPath)
  {
    if (Renderer::api() == RendererApi::OpenGL)
      return std::make_unique<OpenGLCubemap>(std::initializer_list<std::string>{rightPath, leftPath, topPath, bottomPath, backPath, frontPath});
    else
      SLIM_ASSERT(false, "API not implemented")
  }
}