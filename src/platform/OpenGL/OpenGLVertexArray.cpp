#include "OpenGLVertexArray.h"

#include <glad/gl.h>

namespace slim
{
  OpenGLVertexArray::OpenGLVertexArray()
  {
    glGenVertexArrays(1, &_id);
  }

  OpenGLVertexArray::~OpenGLVertexArray()
  {
    glDeleteVertexArrays(1, &_id);
  }

  void OpenGLVertexArray::bind()
  {
    glBindVertexArray(_id);
  }

  void OpenGLVertexArray::unbind()
  {
    glBindVertexArray(0);
  }

  void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer)
  {
    glBindVertexArray(_id);
    buffer->bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    _vertexBuffers.push_back(buffer);
  }

  const std::vector<std::shared_ptr<VertexBuffer>> &OpenGLVertexArray::getVertexBuffers() const
  {
    return _vertexBuffers;
  }

  void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer)
  {
    glBindVertexArray(_id);
    buffer->bind();

    _indexBuffer = buffer;
  }
}