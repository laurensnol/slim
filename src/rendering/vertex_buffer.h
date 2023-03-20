#ifndef SLIM_VERTEX_BUFFER_H
#define SLIM_VERTEX_BUFFER_H

#include <memory>

namespace slim
{
  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void set(const void *data, uint32_t size) = 0;

    static std::shared_ptr<VertexBuffer> create(float *vertices, uint32_t size);
  };
}

#endif