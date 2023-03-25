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

    for (auto attribute : buffer->getAttributes())
    {
      if (attribute.type < 4)
        glVertexAttribPointer(attribute.index, attribute.count, vertexAttributeGLType(attribute.type), attribute.normalized, attribute.size, (const void *)attribute.offset);
      else
        glVertexAttribIPointer(attribute.index, attribute.count, vertexAttributeGLType(attribute.type), attribute.size, (const void *)attribute.offset);

      glEnableVertexAttribArray(attribute.index);
    }

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