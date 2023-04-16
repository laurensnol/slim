#include "core/application.h"
#include "core/time.h"
#include "core/input.h"
#include "events/codes.h"
#include "demo.h"
#include <glad/gl.h>

namespace slim
{
  Application* Application::s_instance = nullptr;
  
  void Application::start()
  {
    EventBus::init();
    Input::init();

    Demo demo{};

    Time::init();
    while (m_running && !Input::getKeyDown(Key::Escape))
    {
      Time::start();

      demo.update();
      m_window->update();
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