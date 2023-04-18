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

    /**
     * \brief Checks whether the passed \ref slim::Key is pressed.
     * 
     * This method checks whether the passed \ref slim::Key has been pressed in the last frame.
     * \b Note: Since the UI might be capturing keyboard input and is therefore blocking the application's input, 
     * this method returning `false` does not mean that the key is not pressed.
     * For detecting a key being released, see \ref EventHandler.
     * 
     * \param key the key to be checked.
     * \return `true` if the key is pressed, `false` if not.
     */
    static bool getKeyDown(Key key);
 
    /**
     * \brief Checks whether the passed \ref slim::MouseButton is pressed.
     * 
     * This methods returns `true` if the passed \ref slim::MouseButton has been pressed in the last frame.
     * \b Note: Since the UI might be capturing mouse input and is therefore blocking the application's input, 
     * this method returning `false` does not mean that the mouse button is not pressed.
     * For detecting a mouse button being released, see \ref EventHandler.
     * 
     * \param mouseButton the mouseButton to be checked.
     * \return `true` if the mouse button is pressed, `false` if not.
     */
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