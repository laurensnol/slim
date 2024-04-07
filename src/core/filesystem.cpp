#include "slim/core/filesystem.hpp"

// IWYU pragma: no_include <__fwd/string_view.h>
// IWYU pragma: no_include <__fwd/ios.h>
// IWYU pragma: no_include <__fwd/fstream.h>
// IWYU pragma: no_include <filesystem>

#include <cstddef>
#include <fstream>
#include <ios>  // IWYU pragma: keep
#include <string>
#include <string_view>  // IWYU pragma: keep

#include "slim/core/assert.hpp"

namespace slim {
auto Filesystem::strFromFile(std::string_view path) noexcept -> std::string {
  auto file = std::ifstream(path.data(), std::ios::in);
  SLIM_CORE_ASSERT(file, "File {} not found", path);

  file.seekg(0, std::ios::end);
  const auto size = file.tellg();
  SLIM_CORE_ASSERT(size, "File {} is empty", path);

  auto buf = std::string(static_cast<size_t>(size), ' ');

  file.seekg(0);
  file.read(buf.data(), size);

  return buf;
}
}  // namespace slim
