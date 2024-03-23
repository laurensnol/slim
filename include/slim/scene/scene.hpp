#ifndef SLIM_SCENE_SCENE_HPP_
#define SLIM_SCENE_SCENE_HPP_

namespace slim {
class Scene {  // NOLINT(cppcoreguidelines-special-member-functions)
public:
  virtual ~Scene() = default;

  virtual auto onAttach() noexcept -> void = 0;
  virtual auto onUpdate() noexcept -> void = 0;
  virtual auto onDetach() noexcept -> void = 0;
};
}  // namespace slim

#endif  // SLIM_SCENE_SCENE_HPP_
