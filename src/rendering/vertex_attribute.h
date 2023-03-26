#ifndef SLIM_VERTEXATTRIBUTE_H
#define SLIM_VERTEXATTRIBUTE_H

#include "core/base.h"
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

  static uint32_t vertexAttributeTypeSize(VertexAttributeBaseType type)
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

    SLIM_ASSERT(false, "Unrecognized VertexAttributeBaseType")
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
    VertexAttribute(uint32_t index, VertexAttributeBaseType type, bool normalized, uint32_t strideCount, uint32_t offset = 0)
      : index(index),
        size(vertexAttributeTypeSize(type)),
        type(type),
        normalized(normalized),
        strideCount(strideCount),
        offset(offset) { }
    
    uint32_t index;
    uint32_t size;
    VertexAttributeBaseType type;
    bool normalized;
    uint32_t strideCount;
    uint32_t offset;
  };
}

#endif