// IWYU pragma: no_include <string>

#include <slim/slim.hpp>

#include "sandbox_scene.hpp"

auto main() -> int {
  slim::Application::init();

  slim::SceneManager::addScene<SandboxScene>("sandbox");
  slim::SceneManager::setScene("sandbox");

  slim::Application::run();

  return 0;
}
