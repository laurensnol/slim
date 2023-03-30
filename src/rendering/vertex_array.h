#ifndef SLIM_VERTEXARRAY_H
#define SLIM_VERTEXARRAY_H

#include "rendering/vertex_buffer.h"
#include "rendering/index_buffer.h"
#include <memory>
#include <vector>

namespace slim
{
  class VertexArray
  {
  public:
    virtual ~VertexArray() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;
    
    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
    virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;

    virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

    static std::shared_ptr<VertexArray> create();
  };
}

#endif