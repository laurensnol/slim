#include "slim/scene/scene_manager.hpp"

#include <cstdint>
#include <utility>

#include "slim/core/assert.hpp"
#include "slim/core/log.hpp"

namespace slim {
auto SceneManager::removeScene(const SceneName& name) noexcept -> bool {
  if (name == currentScene_.first) {
    SLIM_CORE_LOG_WARN("Removing currently active scene {}", name);
  }

  return scenes_.erase(name) == 1;
}

auto SceneManager::setScene(const SceneName& name) noexcept -> void {
  auto iter = scenes_.find(name);
  SLIM_CORE_ASSERT(iter != scenes_.end(), "Name \"{}\" not found", name);

  if (currentScene_ != kNoScenePair) {
    currentScene_.second->detach();
  }

  iter->second->attach();
  currentScene_ = std::make_pair(name, iter->second);
}

auto SceneManager::getSceneCount() noexcept -> uint64_t {
  return scenes_.size();
}

auto SceneManager::update() noexcept -> void {
  SLIM_CORE_ASSERT(currentScene_ != kNoScenePair, "Current scene is not set");
  currentScene_.second->update();
}

auto SceneManager::uiDraw() noexcept -> void {
  SLIM_CORE_ASSERT(currentScene_ != kNoScenePair, "Current scene is not set");
  currentScene_.second->uiDraw();
}
}  // namespace slim
