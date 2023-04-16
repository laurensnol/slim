#include "core/application.h"
#include "core/time.h"
#include <glad/gl.h>

namespace slim
{
  Application* Application::s_instance = nullptr;
  
  void Application::start()
  {    
    // GL calls will be moved.
    // They're just here to prevent flickering.
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    Time::init();
    while (m_running)
    {
      Time::start();

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      m_window->update();

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

  Application& Application::getInstance()
  {
    if (!s_instance)
      s_instance = new Application();

    return *s_instance;
  }

  Application::Application()
  {
    m_window = Window::create();
    EventBus::init();
  }
}