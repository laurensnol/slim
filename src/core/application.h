#ifndef SLIM_APPLICATION_H
#define SLIM_APPLICATION_H

#include "core/window.h"
#include "events/event.h"
#include <memory>

namespace slim
{
  class Application
  {
  public:
    Application(Application const&) = delete;
    void operator=(Application const&) = delete;

    void start();
    void quit();

    static Application& getInstance();

  private:
    Application();
    virtual ~Application() = default;

    std::unique_ptr<Window> m_window;
    bool m_running = true;
    static Application* s_instance;
  };
}

#endif