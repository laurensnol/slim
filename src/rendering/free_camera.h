#ifndef SLIM_FREECAMERA_H
#define SLIM_FREECAMERA_H

#include "rendering/camera.h"
#include "events/event_handler.h"
#include "events/key_events.h"
#include "events/mouse_events.h"
#include "events/window_events.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace slim
{
  class FreeCamera : public Camera, EventHandler<WindowResizeEvent>
  {
  public:
    FreeCamera(const glm::vec3 position = {0, 0, 0}, float pitch = 0.0f, float yaw = 0.0f, float fov = 60.0f, glm::vec3 worldUp = {0, 1, 0}, float aspectRatio = 1.7778f, float nearClip = 0.1f, float farClip = 100.0f);
    virtual ~FreeCamera() = default;

    void onUpdate() override;

    void setPosition(const glm::vec3& position);
    void setPitch(float pitch);
    void setYaw(float yaw);
    void setFov(float fov);

    const glm::vec3& getPosition() const;
    float getPitch() const;
    float getYaw() const;
    float getFov() const;

    const glm::mat4& getView() const override;
    const glm::mat4& getProjection() const override;
    glm::mat4 getViewProjection() const override;

    void onEvent(const WindowResizeEvent& event) override;

  private:
    float m_minFov = 20.0f;
    float m_maxFov = 90.0f;

    float m_moveSpeed = 10.0f;
    float m_lookSensitivity = 0.15f;

    float m_fov;
    float m_pitch, m_yaw;

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    glm::mat4 m_view;
    glm::mat4 m_projection;

    void update();
    void updateView();
    void updateProjection();
  };
}

#endif