#ifndef SLIM_TIME_H
#define SLIM_TIME_H

#include <chrono>

namespace slim
{
  class Time
  {
  public:
    static float deltaTime;

    static void update();

  private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> _previous;
  };
}

#endif