#include "demo_scene.h"
#include "scene/scene_manager.h"
#include "core/application.h"

int main()
{
  slim::SceneManager::addScene<slim::DemoScene>("demo");

  slim::Application& app = slim::Application::getInstance();
  app.getWindow().setVsync(true);
  app.start();

  return 0;
}