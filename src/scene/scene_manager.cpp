#include "slim/scene/scene_manager.hpp"

// IWYU pragma: no_include <spdlog/fmt/fmt.h>
// IWYU pragma: no_include "spdlog/common.h"

#include <spdlog/spdlog.h>

#include <cassert>
#include <cstdint>
#include <string>
#include <utility>

namespace slim {
auto SceneManager::removeScene(const SceneName& name) noexcept -> bool {
  if (name == currentScene_.first) {
    spdlog::warn("Removing currently active scene {}", name);
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
