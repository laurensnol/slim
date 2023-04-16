#ifndef SLIM_TIME_H
#define SLIM_TIME_H

#include <chrono>

namespace slim
{
  class Time
  {
  public:
    Time(Time const&) = delete;
    void operator=(Time const&) = delete;

    /**
     * \brief The time elapsed since the start of the application at the start of the current frame in seconds.
     * The start time will be set right before starting the application's main loop.
     */
    static float time;

    /**
     * \brief The time it took to render the last frame in seconds.
     */
    static float deltaTime;

    static void init();

    static void start();

    static void end();

  private:
    Time() {}

    static std::chrono::time_point<std::chrono::high_resolution_clock> s_start;
    static std::chrono::time_point<std::chrono::high_resolution_clock> s_loopStart;
  };
}

#endif