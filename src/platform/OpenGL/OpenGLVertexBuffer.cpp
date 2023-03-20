#include "platform/OpenGL/OpenGLVertexBuffer.h"

#include <glad/gl.h>

namespace slim
{
  OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
  {
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer()
  {
    glDeleteBuffers(1, &_id);
  }

  void OpenGLVertexBuffer::bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
  }

  void OpenGLVertexBuffer::unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void OpenGLVertexBuffer::set(const void *data, uint32_t size)
  {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  }
}
