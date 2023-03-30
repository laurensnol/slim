#ifndef SLIM_IMAGE_H
#define SLIM_IMAGE_H

#include <memory>
#include <string>

namespace slim
{
  class Image
  {
    // Passkey idiom to restrict initializing Image directly while still allowing
    // std::make_shared.
    // See: https://abseil.io/tips/134
    class _ImageKey
    {
    private:
      explicit _ImageKey() = default;
      friend Image;
    };

  public:
    Image(_ImageKey, const std::string& path);
    virtual ~Image();

    int32_t width;
    int32_t height;
    int32_t channels;
    unsigned char *data;
    bool success;

    static std::shared_ptr<Image> load(const std::string& path);
  };
}

#endif