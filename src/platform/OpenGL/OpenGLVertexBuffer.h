#ifndef SLIM_OPENGLVERTEXBUFFER_H
#define SLIM_OPENGLVERTEXBUFFER_H

#include "rendering/vertex_buffer.h"
#include "rendering/vertex_attribute.h"
#include <vector>

namespace slim
{
  class OpenGLVertexBuffer : public VertexBuffer
  {
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    void bind() override;
    void unbind() override;
    void set(const void *data, uint32_t size) override;

    void addAttribute(const VertexAttribute& attribute) override;
    const std::vector<VertexAttribute>& getAttributes() const override;

  private:
    uint32_t m_id;
    std::vector<VertexAttribute> m_attributes;
  };
}

#endif