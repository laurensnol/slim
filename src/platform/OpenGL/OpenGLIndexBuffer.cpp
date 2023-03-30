#include "platform/OpenGL/OpenGLIndexBuffer.h"

#include <glad/gl.h>

namespace slim
{
  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
  {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    m_count = count;
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer()
  {
    glDeleteBuffers(1, &m_id);
  }

  void OpenGLIndexBuffer::bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
  }

  void OpenGLIndexBuffer::unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  uint32_t OpenGLIndexBuffer::count() const
  {
    return m_count;
  }
}