#include "rendering/free_camera.h"
#include "events/codes.h"
#include "core/input.h"
#include "core/time.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

namespace slim
{
  FreeCamera::FreeCamera(const glm::vec3 position, float pitch, float yaw, float fov, glm::vec3 worldUp, float aspectRatio, float nearClip, float farClip)
    : Camera(aspectRatio, nearClip, farClip), m_position(position), m_pitch(pitch), m_yaw(yaw), m_fov(fov), m_worldUp(worldUp)
  {
    update();
    updateProjection();
  }

  void FreeCamera::onUpdate()
  {
    float mul = 1.0f;
    if (Input::getKeyDown(Key::LeftShift))
      mul = 2.5f;

    if (Input::getKeyDown(Key::W))
    {
      m_position += m_front * m_moveSpeed * Time::deltaTime * mul;
      update();
    }

    if (Input::getKeyDown(Key::A))
    {
      m_position -= m_right * m_moveSpeed * Time::deltaTime * mul;
      update();
    }
    
    if (Input::getKeyDown(Key::S))
    {
      m_position -= m_front * m_moveSpeed * Time::deltaTime * mul;
      update();
    }
    
    if (Input::getKeyDown(Key::D))
    {
      m_position += m_right * m_moveSpeed * Time::deltaTime * mul;
      update();
    }

    if (Input::getMouseDown(MouseButton::Left))
    {
      m_yaw += -Input::mouseDelta.x * m_lookSensitivity;
      m_pitch += Input::mouseDelta.y * m_lookSensitivity;
      update();
    }
  }

  void FreeCamera::setPosition(const glm::vec3& position)
  {
    m_position = position;
    update();
  }

  void FreeCamera::setPitch(float pitch)
  {
    m_pitch = pitch;
    update();
  }

  void FreeCamera::setYaw(float yaw)
  {
    m_yaw = yaw;
    update();
  }

  void FreeCamera::setFov(float fov)
  {
    m_fov = fov;
    updateProjection();
  }

  const glm::vec3& FreeCamera::getPosition() const
  {
    return m_position;
  }

  float FreeCamera::getPitch() const
  {
    return m_pitch;
  }

  float FreeCamera::getYaw() const
  {
    return m_yaw;
  }

  float FreeCamera::getFov() const
  {
    return m_fov;
  }

  const glm::mat4& FreeCamera::getView() const
  {
    return m_view;
  }

  const glm::mat4& FreeCamera::getProjection() const
  {
    return m_projection;
  }

  glm::mat4 FreeCamera::getViewProjection() const
  {
    return m_projection * m_view;
  }

  void FreeCamera::update()
  {
    float yawRad = glm::radians(m_yaw);
    float pitchRad = glm::radians(m_pitch);

    glm::vec3 front;
    front.x = cos(yawRad) * cos(pitchRad);
    front.y = sin(pitchRad);
    front.z = sin(yawRad) * cos(pitchRad);

    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));

    updateView();
  }

  void FreeCamera::updateView()
  {
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
  }

  void FreeCamera::updateProjection()
  {
    m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearClip, m_farClip);
  }

  void FreeCamera::onEvent(const WindowResizeEvent& event)
  {
    m_aspectRatio = event.size.x / event.size.y;
    updateProjection();
  }
}