#ifndef SLIM_OPENGLINDEXBUFFER_H
#define SLIM_OPENGLINDEXBUFFER_H

#include "rendering/index_buffer.h"

namespace slim
{
  class OpenGLIndexBuffer : public IndexBuffer
  {
  public:
    OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    void bind() override;
    void unbind() override;
    uint32_t count() const override;

  private:
    uint32_t m_id;
    uint32_t m_count;
  };
}

#endif