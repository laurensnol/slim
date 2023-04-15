#ifndef SLIM_CAMERA_H
#define SLIM_CAMERA_H

#include <glm/glm.hpp>

namespace slim
{
  class Camera
  {
  public:
    Camera(float aspectRatio, float nearClip, float farClip)
      : m_aspectRatio(aspectRatio), m_nearClip(nearClip), m_farClip(farClip) { }
    virtual ~Camera() = default;

    virtual void onUpdate() = 0;
    virtual const glm::mat4& getView() const = 0;
    virtual const glm::mat4& getProjection() const = 0;
    virtual glm::mat4 getViewProjection() const = 0;

  protected:
    float m_aspectRatio;
    float m_nearClip, m_farClip;
  };
}

#endif