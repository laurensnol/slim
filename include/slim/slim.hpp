#ifndef SLIM_HPP_
#define SLIM_HPP_

/**
 * \defgroup core core
 * \brief Core components
 *
 * \defgroup platform platform
 * \brief Platform specific implementations
 *
 * \defgroup events events
 * \brief Events and related components
 *
 * \defgroup input input
 * \brief Input handling
 *
 * \defgroup renderer renderer
 * \brief Renderer and related components
 *
 * \defgroup scene scene
 * \brief Scene and related components
 */

// IWYU pragma: begin_exports

#include "slim/core/application.hpp"
#include "slim/core/window.hpp"

#include "slim/events/event.hpp"
#include "slim/events/window_events.hpp"
#include "slim/events/mouse_events.hpp"
#include "slim/events/key_events.hpp"
#include "slim/events/event_bus.hpp"
#include "slim/events/event_handler.hpp"

#include "slim/input/codes.hpp"
#include "slim/input/input.hpp"

#include "slim/renderer/renderer.hpp"

#include "slim/scene/scene.hpp"
#include "slim/scene/scene_manager.hpp"

// IWYU pragma: end_exports

#endif  // SLIM_HPP_
