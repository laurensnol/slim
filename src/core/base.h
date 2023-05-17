#ifndef SLIM_BASE_H
#define SLIM_BASE_H

#include <spdlog/spdlog.h>
#include <assert.h>

#define SLIM_ASSERT(value, msg, ...)        \
  if (!(value))                             \
  {                                         \
    spdlog::critical(msg, ##__VA_ARGS__);   \
    assert(value);                          \
  }

#ifdef SLIM_DEBUG
#define SLIM_DEBUG_ASSERT(value, msg, ...) SLIM_ASSERT(value, msg, ...)
#else
#define SLIM_DEBUG_ASSERT(value, msg, ...)
#endif

#endif