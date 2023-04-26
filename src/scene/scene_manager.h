#ifndef SLIM_SCENEMANAGER_H
#define SLIM_SCENEMANAGER_H

#include "scene/scene.h"
#include "core/application.h"
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <string>
#include <memory>

namespace slim
{
  class SceneManager
  {
  public:
    friend Application;

    // `TScene` will be deduced.
    template <typename TScene>
    static void addScene(const std::string& name, std::shared_ptr<TScene> scene)
    {
      s_scenes[name] = scene;
    }

    template <typename TScene>
    static void addScene(const std::string& name)
    {
      s_scenes[name] = std::make_shared<TScene>();
    }

    static void removeScene(const std::string& name);
    static void setCurrentScene(std::string name);
    static std::shared_ptr<Scene> getCurrentScene();
    static std::shared_ptr<Scene> getScene(const std::string& name);

  private:
    SceneManager() { }

    static void init();

    static std::unordered_map<std::string, std::shared_ptr<Scene>> s_scenes;
    static std::shared_ptr<Scene> s_currentScene;
  };
}

#endif