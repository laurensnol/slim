#include <slim/slim.hpp>

auto main() -> int {
  slim::Application::init();
  // slim::SceneManager::addScene<SandboxScene>("sandbox");
  slim::Application::run();

  return 0;
}
