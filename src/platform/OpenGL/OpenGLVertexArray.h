#ifndef SLIM_OPENGLVERTEXARRAY_H
#define SLIM_OPENGLVERTEXARRAY_H

#include "rendering/vertex_array.h"
#include "rendering/vertex_buffer.h"
#include "rendering/index_buffer.h"

#include <memory>
#include <vector>

namespace slim
{
  class OpenGLVertexArray : public VertexArray
  {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    void bind() override;
    void unbind() override;

    void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
    const std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers() const override;

    void setIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer) override;

  private:
    uint32_t m_id;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
  };
}

#endif