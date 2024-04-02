#ifndef SLIM_UTILS_HPP_
#define SLIM_UTILS_HPP_

// IWYU pragma: no_include <__fwd/string_view.h>

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
auto readFile(std::string_view path) noexcept -> std::string;
}

#endif  // SLIM_UTILS_HPP_
