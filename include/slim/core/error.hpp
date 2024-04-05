#ifndef SLIM_CORE_ERROR_HPP_
#define SLIM_CORE_ERROR_HPP_

#include <spdlog/common.h>   // IWYU pragma: export
#include <spdlog/fmt/fmt.h>  // IWYU pragma: export
#include <spdlog/spdlog.h>

#include <exception>  // IWYU pragma: export

#define SLIM_CORE_FATAL_ERROR(...) \
  ::spdlog::critical(__VA_ARGS__); \
  std::terminate()

#endif  // SLIM_CORE_ERROR_HPP_
