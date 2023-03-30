#include "platform/OpenGL/OpenGLTexture2D.h"
#include "core/base.h"
#include <stb_image.h>
#include <glad/gl.h>

namespace slim
{
  OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
  {
    int32_t width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data)
      SLIM_ASSERT(false, "Failed to load texture source: {}", path)

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
  }

  OpenGLTexture2D::~OpenGLTexture2D()
  {
    glDeleteTextures(1, &m_id);
  }

  void OpenGLTexture2D::bind()
  {
    glBindTexture(GL_TEXTURE_2D, m_id);
  }

  void OpenGLTexture2D::unbind()
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}