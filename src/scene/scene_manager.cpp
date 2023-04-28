#include "scene_manager.h"
#include "core/base.h"
#include <spdlog/spdlog.h>
#include <algorithm>

namespace slim
{
  std::unordered_map<std::string, std::shared_ptr<Scene>> SceneManager::s_scenes = {};
  std::shared_ptr<Scene> SceneManager::s_currentScene = nullptr;

  void SceneManager::removeScene(const std::string& name)
  {
    s_scenes.erase(name);
  }

  void SceneManager::setCurrentScene(std::string name)
  {
    auto iter = s_scenes.find(name);
    SLIM_ASSERT((iter != s_scenes.end()), "No scene found for name {}.", name);

    if (s_currentScene)
      s_currentScene->onDetach();

    s_currentScene = s_scenes[name];
    s_currentScene->onAttach();
  }

  std::shared_ptr<Scene> SceneManager::getCurrentScene()
  {
    return s_currentScene;
  }

  std::shared_ptr<Scene> SceneManager::getScene(const std::string& name)
  {
    return s_scenes[name];
  }

  void SceneManager::init()
  {
    SLIM_ASSERT(s_scenes.size() != 0, "No scenes found. Slim needs at least one scene.");

    if (!s_currentScene)
    {
      spdlog::info("No scene set. Will use any.");
      setCurrentScene(s_scenes.begin()->first);
    }
  }
}