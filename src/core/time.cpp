#include "core/time.h"

namespace slim
{
  float Time::deltaTime = 0.0f;
  auto Time::_previous = std::chrono::high_resolution_clock::now();

  void Time::update()
  {
    std::chrono::high_resolution_clock::duration delta = std::chrono::high_resolution_clock::now() - _previous;
    deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(delta).count() * 0.000000001f;
    _previous = std::chrono::high_resolution_clock::time_point(delta);
  }
}