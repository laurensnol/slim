#include "platform/OpenGL/OpenGLCubemap.h"
#include "core/base.h"
#include "utils/image.h"
#include <glad/gl.h>
#include <memory>
#include <vector>

namespace slim
{
  uint32_t OpenGLCubemap::_sides[] = {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
  };

  OpenGLCubemap::OpenGLCubemap(std::initializer_list<std::string> paths)
  {
    size_t pathCount = paths.size();
    if (pathCount == 1)
    {
      auto path = paths.begin();
      std::shared_ptr<Image> image = Image::load(*path);
      
      if (!image->success)
        SLIM_ASSERT("Failed to load cubemap texture from {}", path->c_str());

      glGenTextures(1, &_id);
      glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
      
      for (auto side : _sides)
        glTexImage2D(side, 0, GL_RGB, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);

      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else if (pathCount == 6)
    {
      glGenTextures(1, &_id);
      glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
      
      // Create an std::vector since an std::initializer_list cannot be individually accessed.
      std::vector<std::string> pathsVec(paths);

      for (uint32_t i = 0; i < pathsVec.size(); i++)
      {
        std::shared_ptr<Image> image = Image::load(pathsVec[i]);
         
        if (!image->success)
          SLIM_ASSERT("Failed to load cubemap texture from {}", pathsVec[i]);

        glTexImage2D(_sides[i], 0, GL_RGB, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
      }

      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {
      SLIM_ASSERT(false, "Unknown amount of paths {}", pathCount);
    }
  }

  OpenGLCubemap::~OpenGLCubemap()
  {
    glDeleteTextures(1, &_id);
  }

  void OpenGLCubemap::bind()
  {
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
  }

  void OpenGLCubemap::unbind()
  {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  }
}