#include "core/time.h"

namespace slim
{
  float Time::deltaTime = 0.0f;
  auto Time::s_previous = std::chrono::high_resolution_clock::now();

  void Time::update()
  {
    std::chrono::high_resolution_clock::duration delta = std::chrono::high_resolution_clock::now() - s_previous;
    deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(delta).count() * 0.000000001f;
    s_previous = std::chrono::high_resolution_clock::time_point(delta);
  }
}