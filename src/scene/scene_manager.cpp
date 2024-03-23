#include "slim/scene/scene_manager.hpp"

// IWYU pragma: no_include <spdlog/fmt/fmt.h>
// IWYU pragma: no_include "spdlog/common.h"

#include <spdlog/spdlog.h>

#include <cassert>
#include <cstdint>
#include <string>
#include <utility>

namespace slim {
auto SceneManager::removeScene(const std::string& name) noexcept -> bool {
  if (name == currentScene_.first) {
    spdlog::warn("Removing currently active scene {}", name);
  }

  return scenes_.erase(name) == 1;
}

auto SceneManager::setScene(const std::string& name) noexcept -> void {
  auto iter = scenes_.find(name);
  assert(iter != scenes_.end());

  if (currentScene_ != kNoScenePair) {
    currentScene_.second->onDetach();
  }

  iter->second->onAttach();
  currentScene_ = std::make_pair(name, iter->second);
}

auto SceneManager::getSceneCount() noexcept -> uint64_t {
  return scenes_.size();
}

auto SceneManager::onUpdate() noexcept -> void {
  currentScene_.second->onUpdate();
}
}  // namespace slim
