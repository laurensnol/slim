#ifndef SLIM_VERTEXATTRIBUTE_H
#define SLIM_VERTEXATTRIBUTE_H

#include <spdlog/spdlog.h>
#include <glad/gl.h>

namespace slim
{
  enum VertexAttributeBaseType
  {
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Int2,
    Int3,
    Int4
  };

  static uint32_t vertexAttributeTypeCount(VertexAttributeBaseType type)
  {
    switch (type)
    {
      case VertexAttributeBaseType::Float:  return 1;
      case VertexAttributeBaseType::Float2: return 2;
      case VertexAttributeBaseType::Float3: return 3;
      case VertexAttributeBaseType::Float4: return 4;

      case VertexAttributeBaseType::Int:    return 1;
      case VertexAttributeBaseType::Int2:   return 2;
      case VertexAttributeBaseType::Int3:   return 3;
      case VertexAttributeBaseType::Int4:   return 4;
    }

    spdlog::error("Unrecognized VertexAttributeBaseType");
    assert(false);
  }

  static uint32_t vertexAttributeTypeSize(VertexAttributeBaseType type)
  {
    switch (type)
    {
      case VertexAttributeBaseType::Float:  return 4;
      case VertexAttributeBaseType::Float2: return 4 * 2;
      case VertexAttributeBaseType::Float3: return 4 * 3;
      case VertexAttributeBaseType::Float4: return 4 * 4;

      case VertexAttributeBaseType::Int:    return 4;
      case VertexAttributeBaseType::Int2:   return 4 * 2;
      case VertexAttributeBaseType::Int3:   return 4 * 3;
      case VertexAttributeBaseType::Int4:   return 4 * 4;
    }

    spdlog::error("Unrecognized VertexAttributeBaseType");
    assert(false);
  }

  static GLenum vertexAttributeGLType(VertexAttributeBaseType type)
  {
    if (type < 4)
      return GL_FLOAT;
    else
      return GL_INT;
  }

  struct VertexAttribute
  {
    VertexAttribute(uint32_t index, VertexAttributeBaseType type, bool normalized)
      : index(index),
        count(vertexAttributeTypeCount(type)),
        size(vertexAttributeTypeSize(type)),
        type(type),
        normalized(normalized) {}

    uint32_t index;
    uint32_t count;
    uint32_t size;
    VertexAttributeBaseType type;
    bool normalized;
  };
}

#endif