#ifndef SLIM_OPENGLVERTEXBUFFER_H
#define SLIM_OPENGLVERTEXBUFFER_H

#include "rendering/vertex_buffer.h"

namespace slim
{
  class OpenGLVertexBuffer : public VertexBuffer
  {
  public:
    OpenGLVertexBuffer(float *vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    void bind() override;
    void unbind() override;
    void set(const void *data, uint32_t size) override;

  private:
    uint32_t _id;
  };
}

#endif