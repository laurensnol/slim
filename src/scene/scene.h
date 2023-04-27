#ifndef SLIM_SCENE_H
#define SLIM_SCENE_H

namespace slim
{
  /**
   * \brief The base class for scenes used with Slim.
   * 
   * This virtual class should serve as the base class for any scene implementation to be used with Slim.
   * Note about constructors: When implementing a constructor for your subclassed scene, ensure the constructor will either not use anything of Slim or will only be called after slim::Application is initialized (typically after slim::Application::start() was called).
   * 
   * \see slim::DemoScene
   */
  class Scene
  {
  public:
    virtual ~Scene() = default;

    /**
     * \brief This method will be called when the scene is about to become the currently active scene.
     * 
     * \see slim::SceneManager
     */
    virtual void onAttach() { };

    /**
     * \brief This method will be called every frame before drawing.
     * 
     * This method will be called once per frame before drawing and should be used to update the state of the scene.
     * 
     * \see slim::Application
     */
    virtual void onUpdate() { };

    /**
     * \brief This method will be called after drawing to draw UI elements.
     * 
     * This method will be called after drawing to handle ImGui calls.
     * ImGui calls should not be made outside of this function or else they might have no effect.
     * 
     * \see slim::Application
     */
    virtual void onUiDraw() { };

    /**
     * \brief This method will be called when the scene is about to stop being the currently active scene.
     * 
     * \see slim::SceneManager
     */
    virtual void onDetach() { };
  };
}

#endif