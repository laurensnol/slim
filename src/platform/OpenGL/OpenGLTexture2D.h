#ifndef SLIM_OPENGLTEXTURE2D_H
#define SLIM_OPENGLTEXTURE2D_H

#include <rendering/texture2d.h>
#include <string>

namespace slim
{
  class OpenGLTexture2D : public Texture2D
  {
  public:
    OpenGLTexture2D(const std::string &path);
    virtual ~OpenGLTexture2D();

    void bind() override;
    void unbind() override;

  private:
    uint32_t _id;
  };
}

#endif