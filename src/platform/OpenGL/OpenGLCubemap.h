#ifndef SLIM_OPENGLCUBEMAP_H
#define SLIM_OPENGLCUBEMAP_H

#include "rendering/cubemap.h"
#include <string>
#include <initializer_list>
#include <functional>

namespace slim
{
  class OpenGLCubemap : public Cubemap
  {
  public:
    OpenGLCubemap(std::initializer_list<std::string> paths);
    virtual ~OpenGLCubemap();

    void bind() override;
    void unbind() override;

  private:
    uint32_t m_id;

    static uint32_t s_sides[];
  };
}

#endif