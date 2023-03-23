#ifndef SLIM_INDEXBUFFER_H
#define SLIM_INDEXBUFFER_H

#include <memory>

namespace slim
{
  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual uint32_t count() const = 0;

    static std::shared_ptr<IndexBuffer> create(uint32_t *indices, uint32_t count);
  };
}

#endif