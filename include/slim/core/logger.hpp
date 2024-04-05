#ifndef SLIM_CORE_LOGGER_HPP_
#define SLIM_CORE_LOGGER_HPP_

#include <spdlog/common.h>
#include <spdlog/fmt/fmt.h>  // IWYU pragma: export
#include <spdlog/spdlog.h>

#include <utility>

namespace slim {
class Logger final {
  friend class Application;

  template <typename... Args>
  using FormatString = spdlog::format_string_t<Args...>;

public:
  static auto init() noexcept -> void;

private:
};
}  // namespace slim

#endif  // SLIM_CORE_LOGGER_HPP_
