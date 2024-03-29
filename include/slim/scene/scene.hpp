#ifndef SLIM_SCENE_SCENE_HPP_
#define SLIM_SCENE_SCENE_HPP_

namespace slim {
/**
 * \brief The abstract Scene interface.
 *
 * This abstract class defines an interface for a Scene to be used with slim.
 *
 * \ingroup scene
 */
class Scene {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
  virtual ~Scene() = default;

  /**
   * \brief This method will be called before the scene will become active.
   */
  virtual auto attach() noexcept -> void = 0;

  /**
   * \brief This method will be called once per frame.
   */
  virtual auto update() noexcept -> void = 0;

  /**
   * \brief This method will be called once per frame to allow ImGui draw calls.
   */
  virtual auto uiDraw() noexcept -> void = 0;

  /**
   * \brief This method will be called before the call to Scene::attach of the
   *        new Scene.
   */
  virtual auto detach() noexcept -> void = 0;
};
}  // namespace slim

#endif  // SLIM_SCENE_SCENE_HPP_
