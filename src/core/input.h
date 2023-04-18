#ifndef SLIM_INPUT_H
#define SLIM_INPUT_H

#include "core/application.h"
#include "events/event_handler.h"
#include "events/mouse_events.h"
#include "events/codes.h"
#include <glm/glm.hpp>
#include <imgui.h>

namespace slim
{
  class Input
  {
  public:
    friend Application;

    Input(Input const&) = delete;
    void operator=(Input const&) = delete;

    static glm::vec2 mousePosition;
    static glm::vec2 mouseDelta;
    static glm::vec2 mouseScroll;

    static bool getKeyDown(Key key);
    static bool getMouseDown(MouseButton mouseButton);

  private:
    Input() { }

    static void init();
    static void onUpdate();

    static glm::vec2 s_lastMousePosition;
    static glm::vec2 s_mouseScrollSum;
    static void* s_nativeWindowPtr;
    static ImGuiIO* s_imguiIo;
  };
}

#endif