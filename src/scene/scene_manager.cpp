#include "slim/scene/scene_manager.hpp"

#include <cassert>
#include <cstdint>
#include <string>
#include <utility>

#include "slim/core/log.hpp"

namespace slim {
auto SceneManager::removeScene(const SceneName& name) noexcept -> bool {
  if (name == currentScene_.first) {
    SLIM_CORE_WARN("Removing currently active scene {}", name);
  }

  return scenes_.erase(name) == 1;
}

auto SceneManager::setScene(const SceneName& name) noexcept -> void {
  auto iter = scenes_.find(name);
  assert(iter != scenes_.end());

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
  assert(currentScene_ != kNoScenePair);
  currentScene_.second->update();
}

auto SceneManager::uiDraw() noexcept -> void {
  assert(currentScene_ != kNoScenePair);
  currentScene_.second->uiDraw();
}
}  // namespace slim
