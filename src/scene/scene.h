#ifndef SLIM_SCENE_H
#define SLIM_SCENE_H

namespace slim
{
  class Scene
  {
  public:
    virtual ~Scene() = default;

    virtual void onAttach() { };
    virtual void onUpdate() { };
    virtual void onUiDraw() { };
    virtual void onDetach() { };
  };
}

#endif