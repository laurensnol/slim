#ifndef SLIM_CORE_ASSERT_HPP_
#define SLIM_CORE_ASSERT_HPP_

#include <spdlog/common.h>   // IWYU pragma: export
#include <spdlog/fmt/fmt.h>  // IWYU pragma: export
#include <spdlog/spdlog.h>

#include <cassert>

#ifndef NDEBUG
#define SLIM_CORE_ASSERT(value, ...) \
  if (!(value)) {                    \
    ::spdlog::critical(__VA_ARGS__); \
    assert(value);                   \
  }
#else
#define SLIM_CORE_ASSERT(value, ...)
#endif

#endif  // SLIM_CORE_ASSERT_HPP_
