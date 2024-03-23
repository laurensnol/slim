#ifndef SLIM_SCENE_SCENE_MANAGER_HPP_
#define SLIM_SCENE_SCENE_MANAGER_HPP_

#include <concepts>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "slim/scene/scene.hpp"

namespace slim {
class SceneManager {
  using SceneName = std::string;
  using ScenePtr = std::shared_ptr<Scene>;
  using SceneMap = std::unordered_map<SceneName, ScenePtr>;
  using ScenePair = std::pair<SceneName, ScenePtr>;

  inline static const ScenePair kNoScenePair = {"", nullptr};

public:
  template <typename SceneType>
    requires std::derived_from<SceneType, Scene>
  static auto addScene(const std::string& name) noexcept -> void {
    scenes_[name] = std::make_shared<SceneType>();
  }

  template <typename SceneType, typename... Args>
    requires std::derived_from<SceneType, Scene>
  static auto addScene(const std::string& name, Args... args) noexcept -> void {
    scenes_[name] = std::make_shared<SceneType>(std::forward(args...));
  }

  template <typename SceneType>
    requires std::derived_from<SceneType, Scene>
  static auto addScene(const std::string& name, ScenePtr scene) noexcept
      -> void {
    scenes_[name] = std::move(scene);
  }

  static auto removeScene(const std::string& name) noexcept -> bool;

  static auto setScene(const std::string& name) noexcept -> void;

  static auto getSceneCount() noexcept -> uint64_t;

  static auto onUpdate() noexcept -> void;

private:
  inline static SceneMap scenes_ = {};
  inline static ScenePair currentScene_ = kNoScenePair;
};
}  // namespace slim

#endif  // SLIM_SCENE_SCENE_MANAGER_HPP_
