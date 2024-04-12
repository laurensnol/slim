#ifndef SLIM_CORE_LOG_HPP_
#define SLIM_CORE_LOG_HPP_

#include <spdlog/common.h>   // IWYU pragma: export
#include <spdlog/fmt/fmt.h>  // IWYU pragma: export
#include <spdlog/spdlog.h>   // IWYU pragma: keep

// NOTE(laurensnol): Using macros here because inline functions might throw
// exceptions when using std::forward.
// NOLINTBEGIN(cppcoreguidelines-macro-usage)
// clang-format off
#define SLIM_CORE_LOG_TRACE(...)    ::spdlog::trace(__VA_ARGS__)
#define SLIM_CORE_LOG_INFO(...)     ::spdlog::info(__VA_ARGS__)
#define SLIM_CORE_LOG_WARN(...)     ::spdlog::warn(__VA_ARGS__)
#define SLIM_CORE_LOG_ERROR(...)    ::spdlog::error(__VA_ARGS__)
#define SLIM_CORE_LOG_CRITICAL(...) ::spdlog::critical(__VA_ARGS__)
// clang-format on
// NOLINTEND(cppcoreguidelines-macro-usage)

// TODO(laurensnol): Write proper core and user loggers

#endif  // SLIM_CORE_LOG_HPP_
