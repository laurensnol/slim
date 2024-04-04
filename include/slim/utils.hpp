#ifndef SLIM_UTILS_HPP_
#define SLIM_UTILS_HPP_

// IWYU pragma: no_include <__fwd/string_view.h>
// IWYU pragma: no_include <__fwd/ios.h>
// IWYU pragma: no_include <__fwd/fstream.h>
// IWYU pragma: no_include <filesystem>

#include <cassert>
#include <cstddef>
#include <fstream>
#include <ios>  // IWYU pragma: keep
#include <string>
#include <string_view>  // IWYU pragma: keep
#include <type_traits>

// Convert enum class to it's underlying type (integral promotion)
template <typename EnumType>
constexpr auto operator+(EnumType value) noexcept
    -> std::enable_if_t<std::is_enum_v<EnumType>,
                        std::underlying_type_t<EnumType>> {
  return static_cast<std::underlying_type_t<EnumType>>(value);
}

namespace slim::utils {
inline auto readFile(std::string_view path) noexcept -> std::string {
  auto file = std::ifstream(path, std::ios::in);
  assert(file);

  file.seekg(0, std::ios::end);
  const auto size = file.tellg();
  assert(size != 0);

  auto buf = std::string(static_cast<size_t>(size), ' ');

  file.seekg(0);
  file.read(&buf[0], size);  // NOLINT

  return buf;
}
}  // namespace slim::utils

#endif  // SLIM_UTILS_HPP_
