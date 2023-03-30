#include "utils/image.h"
#include "core/base.h"
#include <stb_image.h>

namespace slim
{
  Image::Image(_ImageKey, const std::string& path)
  {
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data)
      success = false;
    else
      success = true;
  }

  Image::~Image()
  {
    stbi_image_free(data);
  }

  std::shared_ptr<Image> Image::load(const std::string& path)
  {
    return std::make_shared<Image>(_ImageKey{}, path);
  }
}