#ifndef SLIM_CUBEMAP_H
#define SLIM_CUBEMAP_H

#include "rendering/texture.h"
#include <memory>
#include <string>

namespace slim
{
  class Cubemap : public Texture
  {
  public:
    static std::shared_ptr<Cubemap> create(const std::string& texturePath);
    static std::shared_ptr<Cubemap> create(
      const std::string& rightPath,
      const std::string& leftPath,
      const std::string& topPath,
      const std::string& bottomPath,
      const std::string& backPath,
      const std::string& frontPath
    );
  };
}

#endif