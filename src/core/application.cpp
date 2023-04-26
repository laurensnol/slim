#include "core/application.h"
#include "core/time.h"
#include "core/input.h"
#include "scene/scene_manager.h"
#include "events/codes.h"
#include "rendering/renderer.h"
#include <glad/gl.h>

namespace slim
{
  Application* Application::s_instance = nullptr;
  
  void Application::start()
  {
    Renderer::init();
    Renderer::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});

    EventBus::init();
    Input::init();
    SceneManager::init();
    Time::init();
    
    while (m_running && !Input::getKeyDown(Key::Escape))
    {
      Time::start();

      // This will later be replaced by something like `Renderer::draw();` (see below),
      // which will call `Renderer::clear();` to seperate updating the scene from actual drawing the updated entities.
      Renderer::clear();

      SceneManager::s_currentScene->onUpdate();

      Renderer::beginUi();
      SceneManager::s_currentScene->onUiDraw();
      Renderer::endUi();

      m_window->onUpdate();
      Input::onUpdate();

      Time::end();
    }
  }

  void Application::quit()
  {
    m_running = false;
  }

  void Application::onEvent(const WindowCloseEvent& event)
  {
    m_running = false;
  }

  Window& Application::getWindow() const
  {
    return *m_window;
  }

  Application& Application::getInstance()
  {
    if (!s_instance)
      s_instance = new Application();

    return *s_instance;
  }

  Application::Application()
  {
    m_window = Window::create();
  }
}