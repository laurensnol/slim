#ifndef SLIM_TEXTURE_H
#define SLIM_TEXTURE_H

namespace slim
{
  class Texture
  {
  public:
    virtual ~Texture() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;
  };
}

#endif