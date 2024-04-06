#ifndef SLIM_CORE_FILESYSTEM_HPP_
#define SLIM_CORE_FILESYSTEM_HPP_

// IWYU pragma: no_include <__fwd/string_view.h>

#include <string>

namespace slim {
class Filesystem final {
public:
  static auto strFromFile(std::string_view path) noexcept -> std::string;
};
}  // namespace slim

#endif  // SLIM_CORE_FILESYSTEM_HPP_
