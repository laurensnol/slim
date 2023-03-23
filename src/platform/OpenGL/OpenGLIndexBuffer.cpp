#include "platform/OpenGL/OpenGLIndexBuffer.h"

#include <glad/gl.h>

namespace slim
{
  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
  {
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    _count = count;
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer()
  {
    glDeleteBuffers(1, &_id);
  }

  void OpenGLIndexBuffer::bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
  }

  void OpenGLIndexBuffer::unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  uint32_t OpenGLIndexBuffer::count() const
  {
    return _count;
  }
}