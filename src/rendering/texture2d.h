#ifndef SLIM_TEXTURE2D_H
#define SLIM_TEXTURE2D_H

#include "rendering/texture.h"
#include <memory>
#include <string>

namespace slim
{
  class Texture2D : public Texture
  {
  public:
    static std::shared_ptr<Texture2D> create(const std::string &path);
  };
}

#endif