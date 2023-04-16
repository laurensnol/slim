#include "core/time.h"

namespace slim
{
  float Time::time = 0.0f;
  float Time::deltaTime = 0.0f;
  auto Time::s_start = std::chrono::high_resolution_clock::now();
  auto Time::s_loopStart = std::chrono::high_resolution_clock::now();

  void Time::init()
  {
    s_start = std::chrono::high_resolution_clock::now();
  }

  void Time::start()
  {
    s_loopStart = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::nanoseconds>(s_loopStart - s_start).count() * 0.000000001f;
  }

  void Time::end()
  {
    deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - s_loopStart).count() * 0.000000001f;
  }
}