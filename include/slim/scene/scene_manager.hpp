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
/**
 * \brief This class manages scenes.
 *
 * This class manages and handles scenes across the slim Application.
 *
 * \ingroup scene
 */
class SceneManager {
  using SceneName = std::string;
  using ScenePtr = std::shared_ptr<Scene>;
  using SceneMap = std::unordered_map<SceneName, ScenePtr>;
  using ScenePair = std::pair<SceneName, ScenePtr>;

  inline static const ScenePair kNoScenePair = {"", nullptr};

public:
  /**
   * \brief Adds a \ref Scene by instantiating it.
   *
   * This method adds the given \ref Scene by instantiating it using \ref
   * std::make_shared.
   *
   * \tparam SceneType The type of Scene to add.
   * \param name The name of the scene.
   */
  template <typename SceneType>
    requires std::derived_from<SceneType, Scene>
  static auto addScene(const SceneName& name) noexcept -> void {
    scenes_[name] = std::make_shared<SceneType>();
  }

  /**
   * \brief Adds a \ref Scene by instantiating it with the given arguments.
   *
   * This method adds the given \ref Scene by instantiating it using \ref
   * std::make_shared and forwaring the arguments.
   *
   * \tparam SceneType The type of scene to add.
   * \tparam Args Template parameter pack of arguments.
   * \param name The name of the scene.
   * \param args The arguments to be forwarded.
   */
  template <typename SceneType, typename... Args>
    requires std::derived_from<SceneType, Scene>
  static auto addScene(const SceneName& name, Args... args) noexcept -> void {
    scenes_[name] = std::make_shared<SceneType>(std::forward(args...));
  }

  /**
   * \brief Adds an existing \ref Scene.
   *
   * This method adds the given \ref ScenePtr.
   *
   * \tparam SceneType The type of the scene to add.
   * \param name The name of the scene.
   * \param scene The \ref ScenePtr to add.
   */
  template <typename SceneType>
    requires std::derived_from<SceneType, Scene>
  static auto addScene(const SceneName& name, ScenePtr scene) noexcept -> void {
    scenes_[name] = std::move(scene);
  }

  /**
   * \brief Removes a \ref Scene if it exists.
   *
   * \param name The name of the \ref Scene to remove.
   *
   * \return Returns `true` if found and removed, `false` if not.
   */
  static auto removeScene(const SceneName& name) noexcept -> bool;

  /**
   * \brief Sets the current \ref Scene if the name exists.
   *
   * \param name The name of the \ref Scene to make current.
   */
  static auto setScene(const SceneName& name) noexcept -> void;

  /**
   * \brief Returns the number of managed Scenes.
   *
   * \return The number of managed scenes.
   */
  [[nodiscard]] static auto getSceneCount() noexcept -> uint64_t;

  /**
   * \brief Calls \ref Scene::onUpdate for the current \ref Scene.
   */
  static auto onUpdate() noexcept -> void;

private:
  inline static SceneMap scenes_ = {};
  inline static ScenePair currentScene_ = kNoScenePair;
};
}  // namespace slim

#endif  // SLIM_SCENE_SCENE_MANAGER_HPP_
