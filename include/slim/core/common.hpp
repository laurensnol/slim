#ifndef SLIM_CORE_COMMON_HPP_
#define SLIM_CORE_COMMON_HPP_

#include <type_traits>

// Convert enum class to it's underlying type (integral promotion)
template <typename EnumType>
constexpr auto operator+(EnumType value) noexcept
    -> std::enable_if_t<std::is_enum_v<EnumType>,
                        std::underlying_type_t<EnumType>> {
  return static_cast<std::underlying_type_t<EnumType>>(value);
}

#endif  // SLIM_CORE_COMMON_HPP_
