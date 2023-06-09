#include "OpenGLVertexArray.h"

#include <glad/gl.h>

namespace slim
{
  OpenGLVertexArray::OpenGLVertexArray()
  {
    glGenVertexArrays(1, &m_id);
  }

  OpenGLVertexArray::~OpenGLVertexArray()
  {
    glDeleteVertexArrays(1, &m_id);
  }

  void OpenGLVertexArray::bind()
  {
    glBindVertexArray(m_id);
  }

  void OpenGLVertexArray::unbind()
  {
    glBindVertexArray(0);
  }

  void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
  {
    glBindVertexArray(m_id);
    buffer->bind();

    for (auto attribute : buffer->getAttributes())
    {
      if (attribute.type <= VertexAttributeBaseType::Float4)
        glVertexAttribPointer(attribute.index, attribute.size, vertexAttributeGLType(attribute.type), attribute.normalized, attribute.strideCount * sizeof(float), (const void *)attribute.offset);
      else
        glVertexAttribIPointer(attribute.index, attribute.size, vertexAttributeGLType(attribute.type), attribute.strideCount * sizeof(uint32_t), (const void *)attribute.offset);

      glEnableVertexAttribArray(attribute.index);
    }

    m_vertexBuffers.push_back(buffer);
  }

  const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const
  {
    return m_vertexBuffers;
  }

  void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
  {
    glBindVertexArray(m_id);
    buffer->bind();

    m_indexBuffer = buffer;
  }
}